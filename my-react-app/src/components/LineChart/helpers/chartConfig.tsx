export const dataConfig = {
  borderWidth: 1.7,
  fill: true,
  tension: 0.45,
  pointStyle: "circle",
  pointRadius: 0,
  pointHoverRadius: 4,
  pointHoverBorderWidth: 3,
  pointHoverBorderColor: "#ffffff",
};

export const crosshair = {
  id: "crosshair",
  beforeDatasetsDraw: (chart: any) => {
    if (chart.tooltip?._active?.length) {
      const ctx = chart.ctx;
      const active = chart.tooltip._active[0];
      const x = active.element.x;
      const topY = chart.scales.y.top;
      const bottomY = chart.scales.y.bottom;

      ctx.save();
      ctx.beginPath();
      ctx.moveTo(x, topY);
      ctx.lineTo(x, bottomY);
      ctx.lineWidth = 0.2;
      ctx.strokeStyle = "#000000";
      ctx.stroke();

      ctx.restore();
    }
  },
};

export const tooltipConfig = {
  enabled: true,
  mode: "index",
  intersect: false,
  backgroundColor: "rgba(255, 255, 255, 0.8)",
  titleColor: "#000000",
  bodyColor: "#000000",
  borderColor: "#000000",
  borderWidth: 0.1,
  boxHeight: 0.7,
  boxWidth: 9,
  padding: 7,
  displayColors: true,
  position: "myCustomPositioner",
  xAlign: "left",
  yAlign: "bottom",
  caretSize: 0,
  titleFont: {
    size: 10,
  },
  bodyFont: {
    size: 10,
  },
};

export const layoutConfig = {
  size: 4,
  padding: {
    top: 20,
    left: 45,
    right: 0,
    bottom: -8,
  },
};

export const legendConfig = {
  position: "bottom" as const,
  align: "center" as const,
  labels: {
    usePointStyle: true,
    font: {
      size: 11,
    },
    padding: 11,
    pointStyle: "line",
  },
};

export const xAxisConfig = {
  other: {
    grid: {
      display: false,
    },
    border: {
      display: false,
    },
  },
  ticks: {
    maxRotation: 0,
    labelOffset: -17,
    padding: 6,
    autoSkip: false,
    font: {
      size: 11,
    },
  },
};

export const yAxisConfig = {
  other: {
    beginAtZero: true,
    border: {
      display: false,
    },
  },
  ticks: {
    maxTicksLimit: 5,
    mirror: true,
    padding: -16.4,
    font: {
      size: 11,
    },
  },
};
