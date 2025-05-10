const WebSocket = require('ws');
const http = require('http');
const url = require('url');
const fs = require('fs');
const path = require('path');

// Path to data.json file
const DATA_FILE_PATH = path.join(__dirname, 'data.json');

// Create WebSocket server on port 8080
const wss = new WebSocket.Server({ port: 8080 });

console.log('JSON File Watch Server started on port 8080');
console.log(`Watching file: ${DATA_FILE_PATH}`);

// This simulates a C++ vector<DataPoint>
class DataPointVector {
  constructor() {
    this.data = [];
    this.listeners = new Set();
  }
  
  // Push a new data point (like C++ vector.push_back())
  push_back(dataPoint) {
    this.data.push(dataPoint);
    this.notifyListeners(dataPoint);
    return this.data.length;
  }
  
  // Access element at index (like C++ vector[i])
  at(index) {
    return this.data[index];
  }
  
  // Get vector size (like C++ vector.size())
  size() {
    return this.data.length;
  }
  
  // Replace all data (reload from file)
  setData(newData) {
    // Track old size to only send new points
    const oldSize = this.data.length;
    
    // Update data
    this.data = newData;
    
    // Notify listeners about any new data points
    if (newData.length > oldSize) {
      for (let i = oldSize; i < newData.length; i++) {
        this.notifyListeners(newData[i]);
      }
    }
    
    // If the data got shorter, we won't notify 
    // (in a real app, you might want to send a reset signal)
  }
  
  // Clear the vector (like C++ vector.clear())
  clear() {
    this.data = [];
  }
  
  // Add a listener for data changes
  addListener(callback) {
    this.listeners.add(callback);
  }
  
  // Remove a listener
  removeListener(callback) {
    this.listeners.delete(callback);
  }
  
  // Notify all listeners of a data change
  notifyListeners(dataPoint) {
    this.listeners.forEach(listener => listener(dataPoint));
  }
  
  // For debugging - show contents
  dump() {
    console.log("Vector contents:");
    this.data.forEach((point, i) => {
      console.log(`  [${i}]: ${JSON.stringify(point)}`);
    });
  }
}

// Create our C++-style vector
const test_data = new DataPointVector();

// Read data from JSON file
function readDataFromFile() {
  try {
    const rawData = fs.readFileSync(DATA_FILE_PATH, 'utf8');
    const jsonData = JSON.parse(rawData);
    console.log(`Read ${jsonData.length} data points from file`);
    return jsonData;
  } catch (error) {
    console.error(`Error reading data file: ${error.message}`);
    return [];
  }
}

// Initialize our test data from file
function loadDataFromFile() {
  const fileData = readDataFromFile();
  test_data.setData(fileData);
  console.log(`Loaded ${test_data.size()} data points from file`);
}

// Load initial data
loadDataFromFile();

// Watch file for changes
fs.watch(DATA_FILE_PATH, (eventType, filename) => {
  if (eventType === 'change') {
    console.log(`File ${filename} changed, reloading data...`);
    // Wait a short time to ensure file is completely written
    setTimeout(() => {
      try {
        loadDataFromFile();
      } catch (error) {
        console.error(`Error reloading data: ${error.message}`);
      }
    }, 100);
  }
});

// Handle new WebSocket connections
wss.on('connection', (ws) => {
  console.log('New client connected');
  
  // First, send all existing data points
  for (let i = 0; i < test_data.size(); i++) {
    const point = test_data.at(i);
    console.log(`Sending initial data [${i}]: ${JSON.stringify(point)}`);
    ws.send(JSON.stringify(point));
  }
  
  // Then add this connection as a listener for future updates
  const updateListener = (dataPoint) => {
    if (ws.readyState === WebSocket.OPEN) {
      console.log(`Sending update: ${JSON.stringify(dataPoint)}`);
      ws.send(JSON.stringify(dataPoint));
    }
  };
  
  test_data.addListener(updateListener);
  
  // Clean up when client disconnects
  ws.on('close', () => {
    console.log('Client disconnected');
    test_data.removeListener(updateListener);
  });
  
  ws.on('error', (error) => {
    console.error('WebSocket error:', error);
    test_data.removeListener(updateListener);
  });
});

// API to manipulate data.json directly
http.createServer((req, res) => {
  const parsedUrl = url.parse(req.url, true);
  
  // Add a single data point to data.json
  if (parsedUrl.pathname === '/push') {
    const value = parseInt(parsedUrl.query.value);
    if (!isNaN(value)) {
      try {
        // Read current data
        const data = readDataFromFile();
        
        // Add new point
        const timestamp = new Date().toISOString();
        data.push({ value, timestamp });
        
        // Write back to file
        fs.writeFileSync(DATA_FILE_PATH, JSON.stringify(data, null, 2), 'utf8');
        
        res.writeHead(200, { 'Content-Type': 'text/plain' });
        res.end(`Added new data point with value: ${value}\nCurrent data size: ${data.length}\n`);
      } catch (error) {
        res.writeHead(500, { 'Content-Type': 'text/plain' });
        res.end(`Error: ${error.message}\n`);
      }
    } else {
      res.writeHead(400, { 'Content-Type': 'text/plain' });
      res.end('Invalid value parameter\n');
    }
  }
  // Add a multi-dataset point to data.json
  else if (parsedUrl.pathname === '/push-multi') {
    const valuesStr = parsedUrl.query.values;
    if (valuesStr) {
      const values = valuesStr.split(',').map(v => parseInt(v));
      if (values.every(v => !isNaN(v))) {
        try {
          // Read current data
          const data = readDataFromFile();
          
          // Add new multi-point
          const timestamp = new Date().toISOString();
          data.push({ value: values, timestamp });
          
          // Write back to file
          fs.writeFileSync(DATA_FILE_PATH, JSON.stringify(data, null, 2), 'utf8');
          
          res.writeHead(200, { 'Content-Type': 'text/plain' });
          res.end(`Added new multi-dataset point with values: ${values.join(', ')}\nCurrent data size: ${data.length}\n`);
        } catch (error) {
          res.writeHead(500, { 'Content-Type': 'text/plain' });
          res.end(`Error: ${error.message}\n`);
        }
      } else {
        res.writeHead(400, { 'Content-Type': 'text/plain' });
        res.end('Invalid values parameter\n');
      }
    } else {
      res.writeHead(400, { 'Content-Type': 'text/plain' });
      res.end('Missing values parameter\n');
    }
  }
  // Show current data in data.json
  else if (parsedUrl.pathname === '/dump') {
    try {
      const data = readDataFromFile();
      res.writeHead(200, { 'Content-Type': 'text/plain' });
      res.end(`Data file contains ${data.length} points.\nCheck console for details.\n`);
      console.log(JSON.stringify(data, null, 2));
    } catch (error) {
      res.writeHead(500, { 'Content-Type': 'text/plain' });
      res.end(`Error: ${error.message}\n`);
    }
  }
  // Clear data.json file
  else if (parsedUrl.pathname === '/clear') {
    try {
      fs.writeFileSync(DATA_FILE_PATH, '[]', 'utf8');
      res.writeHead(200, { 'Content-Type': 'text/plain' });
      res.end('Data file cleared\n');
    } catch (error) {
      res.writeHead(500, { 'Content-Type': 'text/plain' });
      res.end(`Error: ${error.message}\n`);
    }
  }
  // Unknown endpoint
  else {
    res.writeHead(404, { 'Content-Type': 'text/plain' });
    res.end('Not found\n');
  }
}).listen(3001);

console.log('JSON File API running on port 3001');
console.log('Available commands:');
console.log('  - Add a single value:     curl "http://localhost:3001/push?value=42"');
console.log('  - Add multiple values:    curl "http://localhost:3001/push-multi?values=30,45,20"');
console.log('  - View data.json contents: curl "http://localhost:3001/dump"');
console.log('  - Clear data.json:        curl "http://localhost:3001/clear"');
console.log('\nYou can also edit data.json directly and the server will detect changes');

// Handle process termination
process.on('SIGINT', () => {
  console.log('Shutting down server...');
  wss.close();
  process.exit(0);
}); 