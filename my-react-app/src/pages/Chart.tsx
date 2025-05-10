import React from "react";
import LineChart from "../components/LineChart/LineChart";

const Chart: React.FC = () => {
  return (
    <div className="chart-page">
      <h1>Line Chart Page</h1>
      <div className="chart-container">
        <LineChart />
      </div>
    </div>
  );
};

export default Chart; 