import { useState, useEffect, useCallback } from 'react';

// Define the data structure
interface ChartDataPoint {
  value: number;
  timestamp?: string | number;
}

interface ChartDataset {
  label: string;
  data: number[];
  borderColor: string;
  pointHoverBackgroundColor: string;
  backgroundColor: any;
  [key: string]: any; // For additional dataset properties
}

interface ChartData {
  labels: (string | number)[];
  datasets: ChartDataset[];
}

// WebSocket connection state
type ConnectionStatus = 'disconnected' | 'connecting' | 'connected' | 'error';

// Create a singleton to manage WebSocket connection
class DataStreamManager {
  private static instance: DataStreamManager;
  private socket: WebSocket | null = null;
  private listeners: Set<(data: ChartDataPoint) => void> = new Set();
  private status: ConnectionStatus = 'disconnected';
  private url: string = '';
  private reconnectAttempts: number = 0;
  private maxReconnectAttempts: number = 5;
  private reconnectTimeout: number | null = null;
  private autoReconnect: boolean = true;

  private constructor() {}

  public static getInstance(): DataStreamManager {
    if (!DataStreamManager.instance) {
      DataStreamManager.instance = new DataStreamManager();
    }
    return DataStreamManager.instance;
  }

  public connect(url: string): ConnectionStatus {
    if (this.socket && this.status === 'connected') {
      return this.status;
    }

    this.url = url;
    this.status = 'connecting';
    
    try {
      this.socket = new WebSocket(url);
      
      this.socket.onopen = () => {
        this.status = 'connected';
        this.reconnectAttempts = 0;
        console.log('WebSocket connected');
      };
      
      this.socket.onmessage = (event) => {
        try {
          const data = JSON.parse(event.data);
          this.notifyListeners(data);
        } catch (error) {
          console.error('Error parsing WebSocket data:', error);
        }
      };
      
      this.socket.onerror = (error) => {
        console.error('WebSocket error:', error);
        this.status = 'error';
      };
      
      this.socket.onclose = () => {
        this.status = 'disconnected';
        if (this.autoReconnect) {
          this.attemptReconnect();
        }
      };
    } catch (error) {
      console.error('Failed to create WebSocket:', error);
      this.status = 'error';
    }
    
    return this.status;
  }

  private attemptReconnect() {
    if (!this.autoReconnect) return;
    
    if (this.reconnectAttempts < this.maxReconnectAttempts) {
      this.reconnectAttempts++;
      const delay = Math.min(1000 * 2 ** this.reconnectAttempts, 30000);
      
      console.log(`Attempting to reconnect (${this.reconnectAttempts}/${this.maxReconnectAttempts}) in ${delay}ms`);
      
      this.reconnectTimeout = window.setTimeout(() => {
        this.connect(this.url);
      }, delay) as unknown as number;
    } else {
      console.log(`Maximum reconnection attempts (${this.maxReconnectAttempts}) reached. Stopping reconnection.`);
      this.autoReconnect = false;
    }
  }

  public disconnect() {
    this.autoReconnect = false;
    
    if (this.socket) {
      this.socket.close();
      this.socket = null;
    }
    if (this.reconnectTimeout) {
      window.clearTimeout(this.reconnectTimeout);
      this.reconnectTimeout = null;
    }
    this.status = 'disconnected';
  }

  public setAutoReconnect(value: boolean) {
    this.autoReconnect = value;
    if (value && this.status === 'disconnected') {
      this.reconnectAttempts = 0;
      this.connect(this.url);
    }
  }

  public resetReconnectAttempts() {
    this.reconnectAttempts = 0;
  }
  
  public setMaxReconnectAttempts(value: number) {
    this.maxReconnectAttempts = value;
  }

  public subscribe(callback: (data: ChartDataPoint) => void) {
    this.listeners.add(callback);
    return () => {
      this.listeners.delete(callback);
    };
  }

  private notifyListeners(data: ChartDataPoint) {
    this.listeners.forEach(listener => listener(data));
  }

  public getStatus(): ConnectionStatus {
    return this.status;
  }
}

// Hook to use the WebSocket data in components
export function useDataStream(socketUrl: string, initialData?: ChartData) {
  const [chartData, setChartData] = useState<ChartData>(initialData || {
    labels: [],
    datasets: []
  });
  
  const [connectionStatus, setConnectionStatus] = useState<ConnectionStatus>('disconnected');
  const dataManager = DataStreamManager.getInstance();

  // Maximum number of data points to keep (to prevent performance issues)
  const maxDataPoints = 100;
  
  // Update chart data with new point
  const updateChartData = useCallback((newPoint: ChartDataPoint) => {
    setChartData(prevData => {
      // Create deep copy to avoid mutating state
      const newData = JSON.parse(JSON.stringify(prevData));
      
      // If no datasets, initialize the first one
      if (!newData.datasets || newData.datasets.length === 0) {
        newData.datasets = [{
          label: 'Algorithm Output',
          data: [],
          borderColor: 'rgba(19, 172, 240, 1)',
          pointHoverBackgroundColor: 'rgba(19, 172, 240, 1)',
          fill: true,
          tension: 0.4,
          pointRadius: 0,
          pointHitRadius: 10,
        }];
      }
      
      // Add new timestamp/label
      const newLabel = newPoint.timestamp || (newData.labels.length > 0 ? newData.labels.length : 0);
      newData.labels = [...newData.labels, newLabel];

      // Add new value to each dataset
      if (Array.isArray(newPoint.value)) {
        // Handle multiple values (one for each dataset)
        newPoint.value.forEach((val, index) => {
          if (!newData.datasets[index]) {
            // Create new dataset if needed
            newData.datasets[index] = {
              ...newData.datasets[0],
              label: `Dataset ${index + 1}`,
              data: [],
              borderColor: `rgba(${Math.floor(Math.random() * 255)}, ${Math.floor(Math.random() * 255)}, ${Math.floor(Math.random() * 255)}, 1)`,
            };
          }
          newData.datasets[index].data.push(val);
        });
      } else {
        // Handle single value
        newData.datasets[0].data.push(newPoint.value);
      }

      // Trim data if exceeding max points
      if (newData.labels.length > maxDataPoints) {
        const sliceIndex = newData.labels.length - maxDataPoints;
        newData.labels = newData.labels.slice(sliceIndex);
        newData.datasets.forEach((dataset: any) => {
          dataset.data = dataset.data.slice(sliceIndex);
        });
      }

      return newData;
    });
  }, []);

  // Connect to WebSocket when component mounts
  useEffect(() => {
    if (!socketUrl) return;
    
    setConnectionStatus(dataManager.connect(socketUrl));
    
    const unsubscribe = dataManager.subscribe(updateChartData);
    
    // Check connection status periodically
    const statusCheck = window.setInterval(() => {
      setConnectionStatus(dataManager.getStatus());
    }, 1000);
    
    return () => {
      unsubscribe();
      window.clearInterval(statusCheck);
    };
  }, [socketUrl, updateChartData]);

  // Method to manually add data (useful for testing or fallback)
  const addDataPoint = useCallback((value: number, timestamp?: string | number) => {
    updateChartData({ value, timestamp });
  }, [updateChartData]);

  // Manually control reconnection
  const toggleAutoReconnect = useCallback((enabled: boolean) => {
    dataManager.setAutoReconnect(enabled);
  }, [dataManager]);

  return {
    chartData,
    connectionStatus,
    addDataPoint,
    resetData: () => setChartData({ labels: [], datasets: [] }),
    disconnect: () => dataManager.disconnect(),
    reconnect: () => {
      dataManager.resetReconnectAttempts();
      dataManager.setAutoReconnect(true);
      return dataManager.connect(socketUrl);
    },
    toggleAutoReconnect
  };
}

// Export the singleton for direct access if needed
export const getDataManager = () => DataStreamManager.getInstance();
