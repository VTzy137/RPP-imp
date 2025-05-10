import React, { useState } from "react";
import LineChart from "../components/LineChart/LineChart";

const Chart: React.FC = () => {
  const [socketUrl, setSocketUrl] = useState("ws://localhost:8080");
  const [demoMode, setDemoMode] = useState(false);

  return (
    <div className="chart-page">
      <h1 className="text-white font-bold text-2xl">Real-time Data Chart</h1>
      
      <div className="chart-container" style={{ 
        height: '500px', 
        margin: '20px 0',
        borderRadius: '6px',
        padding: '15px',
      }}>
        <LineChart 
          socketUrl={socketUrl}
          demoMode={demoMode}
          height={450}
          maxReconnectAttempts={5}
          autoReconnect={true}
        />
      </div>
      
    </div>
  );
};

export default Chart; 