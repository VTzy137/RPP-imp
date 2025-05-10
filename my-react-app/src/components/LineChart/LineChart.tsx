import React, { useState, useEffect, useCallback } from "react";
import {
  Chart,
  Filler,
  Tooltip,
  LineElement,
  PointElement,
  LineController,
  CategoryScale,
  LinearScale,
} from "chart.js";
import { Line } from "react-chartjs-2";
import type { ChartType, TooltipItem, TooltipPositionerFunction } from "chart.js";

import {
  crosshair,
  dataConfig,
  layoutConfig,
  legendConfig,
  tooltipConfig,
  xAxisConfig,
  yAxisConfig,
} from "./helpers/chartConfig";

import { useDataStream } from "./helpers/trackingData";

declare module "chart.js" {
  interface TooltipPositionerMap {
    myCustomPositioner: TooltipPositionerFunction<ChartType>;
  }
}

Tooltip.positioners.myCustomPositioner = function (elements, eventPosition) {
  return {
    x: eventPosition.x,
    y: eventPosition.y,
  };
};

Chart.register(Filler);
Chart.register(crosshair);

// Register Chart.js components
Chart.register(
  Filler,
  Tooltip,
  LineElement,
  PointElement,
  LineController,
  CategoryScale,
  LinearScale,
);

interface LineChartProps {
  socketUrl?: string;
  demoMode?: boolean;
  height?: string | number;
  maxReconnectAttempts?: number;
  autoReconnect?: boolean;
}

const LineChart: React.FC<LineChartProps> = ({ 
  socketUrl = "ws://localhost:8080", 
  demoMode = false,
  height = 400,
  maxReconnectAttempts = 5,
  autoReconnect = false
}) => {
  const compareColor = "rgba(120, 201, 255, 1)";
  const referenceColor = "rgba(19, 172, 240, 1)";
  const [reconnecting, setReconnecting] = useState(false);

  // Connect to data stream
  const { 
    chartData, 
    connectionStatus, 
    addDataPoint, 
    resetData, 
    disconnect, 
    reconnect,
    toggleAutoReconnect
  } = useDataStream(socketUrl);

  // Set auto-reconnect preference
  useEffect(() => {
    toggleAutoReconnect(autoReconnect);
  }, [autoReconnect, toggleAutoReconnect]);

  // Default demo data for display when not connected
  const demoData = {
    labels: ["Jan", "Feb", "Mar", "Apr", "May"],
    datasets: [
      {
        label: "Demo Data",
        data: [12, 19, 3, 5, 2],
        borderColor: referenceColor,
        pointHoverBackgroundColor: referenceColor,
        backgroundColor: (context: any) => {
          if (!context.chart.chartArea) return referenceColor;
          const {
            ctx,
            chartArea: { top, bottom },
          } = context.chart;
          const gradient = ctx.createLinearGradient(0, top, 0, bottom);
          gradient.addColorStop(0, referenceColor.replace(", 1)", ", 0.2)"));
          gradient.addColorStop(1, referenceColor.replace(", 1)", ", 0.02)"));
          return gradient;
        },
        ...dataConfig,
      },
      {
        label: "Demo Data",
        data: [12, 19, 3, 5, 2],
        borderColor: compareColor,
        pointHoverBackgroundColor: compareColor,
        backgroundColor: (context: any) => {
          const colorBase = compareColor.replace(", 1)", ", 0.15)");
          const colorBaseBottom = compareColor.replace(", 1)", ", 0.03)");
          if (!context.chart.chartArea) return colorBase;
          const {
            ctx,
            chartArea: { top, bottom },
          } = context.chart;
          const gradient = ctx.createLinearGradient(0, top, 0, bottom);
          gradient.addColorStop(0, `${colorBase}`);
          gradient.addColorStop(1, `${colorBaseBottom}`);
          return gradient;
        },
        borderDash: [2, 2],
        ...dataConfig,
      },
    ],
  };

  // Use demo data in demo mode, otherwise use streaming data
  const data = demoMode ? demoData : (
    chartData.datasets && chartData.datasets.length > 0 ? chartData : demoData
  );

  // Simulate data for testing (only in demo mode)
  const simulateDataPoint = useCallback(() => {
    if (demoMode) {
      const value = Math.floor(Math.random() * 100);
      addDataPoint(value);
    }
  }, [demoMode, addDataPoint]);

  // Add a demo point (for testing)
  useEffect(() => {
    if (demoMode) {
      const interval = window.setInterval(() => {
        simulateDataPoint();
      }, 1000);

      return () => window.clearInterval(interval);
    }
  }, [demoMode, simulateDataPoint]);

  // Handle manual reconnection
  const handleReconnect = () => {
    setReconnecting(true);
    resetData(); // Clear previous data to avoid growing chart
    reconnect();
    
    // Reset reconnecting state after a delay
    setTimeout(() => setReconnecting(false), 2000);
  };

  // Handle stopping connection
  const handleDisconnect = () => {
    disconnect();
    resetData(); // Clear data when disconnecting
  };

  const options = {
    maintainAspectRatio: false,
    layout: {
      ...layoutConfig,
    },
    interaction: {
      mode: "index",
      axis: "x",
      intersect: false,
    },
    scales: {
      x: {
        ticks: {
          ...xAxisConfig.ticks,
          callback: (index: number) => {
            const labels = data.labels;
            return [0, Math.floor(labels.length / 2), labels.length - 1].includes(index)
              ? labels[index]
              : "";
          },
        },
        ...xAxisConfig.other,
      },
      y: {
        ticks: {
          ...yAxisConfig.ticks,
          callback: (value: number) => {
            return `${value}`;
          },
        },
        ...yAxisConfig.other,
      },
    },
    plugins: {
      filler: {
        propagate: true,
      },
      tooltip: {
        ...tooltipConfig,
        callbacks: {
          title: () => {
            return "Chart";
          },
          label: (context: TooltipItem<"line">) => {
            const value = context.parsed.y;
            return `${value}`;
          },
        },
      },
      legend: {
        ...legendConfig,
        onHover: (event: any, legendItem: any, legend: any) => {
          const index = legendItem.datasetIndex;
          const ci = legend.chart;
          ci.data.datasets.forEach((dataset: any, i: number) => {
            if (i !== index) {
              dataset.borderColor = dataset.borderColor.replace(
                /rgba\((\d+), (\d+), (\d+), [^)]+\)/,
                "rgba($1, $2, $3, 0.1)",
              );
            }
          });
          ci.options.plugins.tooltip.enabled = false;
          ci.update();
        },
        onLeave: (event: any, legendItem: any, legend: any) => {
          const index = legendItem.datasetIndex;
          const ci = legend.chart;
          ci.data.datasets.forEach((dataset: any, i: number) => {
            if (i !== index) {
              dataset.borderColor = dataset.borderColor.replace(
                /rgba\((\d+), (\d+), (\d+), [^)]+\)/,
                "rgba($1, $2, $3, 1)",
              );
            }
          });
          ci.options.plugins.tooltip.enabled = true;
          ci.update();
        },
      },
    },
  };

  return (
    <div>
      {!demoMode && (
        <div style={{ marginBottom: '10px', display: 'flex', gap: '10px', alignItems: 'center' }}>
          <div style={{ 
            color: connectionStatus === 'connected' ? 'green' : connectionStatus === 'connecting' ? 'orange' : 'red',
            fontWeight: 'bold' 
          }}>
            {connectionStatus === 'connected' 
              ? 'Connected to data source' 
              : connectionStatus === 'connecting' 
                ? 'Connecting to data source...' 
                : 'Not connected to data source'}
          </div>
          
          {connectionStatus !== 'connected' && !reconnecting && (
            <button 
              onClick={handleReconnect}
              style={{
                padding: '4px 8px',
                backgroundColor: '#4285f4',
                color: 'white',
                border: 'none',
                borderRadius: '4px',
                cursor: 'pointer'
              }}
            >
              Reconnect
            </button>
          )}
          
          {connectionStatus === 'connected' && (
            <button 
              onClick={handleDisconnect}
              style={{
                padding: '4px 8px',
                backgroundColor: '#ff5252',
                color: 'white',
                border: 'none',
                borderRadius: '4px',
                cursor: 'pointer'
              }}
            >
              Disconnect
            </button>
          )}
        </div>
      )}
      
      <div style={{ height, width: '100%', position: 'relative' }}>
        <Line data={data} options={options as any} />
      </div>
    </div>
  );
};

export default LineChart;
