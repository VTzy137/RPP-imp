import React, { useState, useEffect } from "react";

const Path: React.FC = () => {
  const [pathData, setPathData] = useState<string>("");
  const [isAnimating, setIsAnimating] = useState(false);

  // Generate a sequence of connected lines forming a path
  const generatePath = () => {
    const points = [];
    let x = 50;
    let y = 50;
    
    // Generate 10 points that form a connected path
    for (let i = 0; i < 10; i++) {
      points.push(`${x},${y}`);
      x += Math.random() * 80 + 20; // Random horizontal movement
      y += (Math.random() - 0.5) * 60; // Random vertical movement
      
      // Keep within bounds
      y = Math.max(30, Math.min(270, y));
      x = Math.min(450, x);
    }
    
    return `M ${points.join(' L ')}`;
  };

  useEffect(() => {
    setPathData(generatePath());
  }, []);

  const animatePath = () => {
    setIsAnimating(true);
    setTimeout(() => setIsAnimating(false), 2000);
  };

  const regeneratePath = () => {
    setPathData(generatePath());
  };

  return (
    <div className="min-h-screen bg-gradient-to-b from-gray-100 to-gray-200 py-12 px-4 sm:px-6 lg:px-8">
      <div className="max-w-6xl mx-auto">
        <div className="text-center mb-8">
          <h1 className="text-4xl font-extrabold text-gray-900 tracking-tight sm:text-5xl md:text-6xl">
            <span className="text-indigo-600">Path</span> Visualization
          </h1>
          <p className="mt-4 max-w-2xl mx-auto text-xl text-gray-500">
            Interactive SVG path with animated line sequences
          </p>
        </div>

        <div className="bg-white rounded-lg shadow-lg p-8">
          <div className="flex justify-center mb-6">
            <div className="flex gap-4">
              <button
                onClick={animatePath}
                disabled={isAnimating}
                className="px-6 py-3 bg-indigo-600 text-white rounded-md hover:bg-indigo-700 disabled:opacity-50 disabled:cursor-not-allowed transition-colors"
              >
                {isAnimating ? "Animating..." : "Animate Path"}
              </button>
              <button
                onClick={regeneratePath}
                className="px-6 py-3 bg-green-600 text-white rounded-md hover:bg-green-700 transition-colors"
              >
                Generate New Path
              </button>
            </div>
          </div>

          <div className="flex justify-center">
            <svg
              width="500"
              height="300"
              className="border border-gray-300 rounded-lg bg-gray-50"
              viewBox="0 0 500 300"
            >
              {/* Grid lines for reference */}
              <defs>
                <pattern id="grid" width="50" height="50" patternUnits="userSpaceOnUse">
                  <path d="M 50 0 L 0 0 0 50" fill="none" stroke="#e5e7eb" strokeWidth="1"/>
                </pattern>
              </defs>
              <rect width="100%" height="100%" fill="url(#grid)" />
              
              {/* Main path */}
              <path
                d={pathData}
                fill="none"
                stroke="#3b82f6"
                strokeWidth="3"
                strokeLinecap="round"
                strokeLinejoin="round"
                className={isAnimating ? "animate-dash" : ""}
                style={{
                  strokeDasharray: isAnimating ? "10,5" : "none",
                  animation: isAnimating ? "dash 2s linear infinite" : "none"
                }}
              />
              
              {/* Path points */}
              {pathData.split(' L ').map((point, index) => {
                if (index === 0) {
                  const [x, y] = point.replace('M ', '').split(',').map(Number);
                  return (
                    <circle
                      key={`point-${index}`}
                      cx={x}
                      cy={y}
                      r="6"
                      fill="#ef4444"
                      stroke="#dc2626"
                      strokeWidth="2"
                    />
                  );
                } else {
                  const [x, y] = point.split(',').map(Number);
                  return (
                    <circle
                      key={`point-${index}`}
                      cx={x}
                      cy={y}
                      r="4"
                      fill="#10b981"
                      stroke="#059669"
                      strokeWidth="2"
                    />
                  );
                }
              })}
              
              {/* Start and end labels */}
              {pathData.split(' L ').length > 0 && (
                <>
                  <text
                    x={pathData.split(' L ')[0].replace('M ', '').split(',')[0]}
                    y={Number(pathData.split(' L ')[0].replace('M ', '').split(',')[1]) - 15}
                    textAnchor="middle"
                    className="text-sm font-semibold fill-red-600"
                  >
                    Start
                  </text>
                  <text
                    x={pathData.split(' L ')[pathData.split(' L ').length - 1].split(',')[0]}
                    y={Number(pathData.split(' L ')[pathData.split(' L ').length - 1].split(',')[1]) - 15}
                    textAnchor="middle"
                    className="text-sm font-semibold fill-green-600"
                  >
                    End
                  </text>
                </>
              )}
            </svg>
          </div>

          <div className="mt-6 text-center">
            <div className="inline-flex items-center gap-4 text-sm text-gray-600">
              <div className="flex items-center gap-2">
                <div className="w-3 h-3 bg-red-500 rounded-full"></div>
                <span>Start Point</span>
              </div>
              <div className="flex items-center gap-2">
                <div className="w-3 h-3 bg-green-500 rounded-full"></div>
                <span>Path Points</span>
              </div>
              <div className="flex items-center gap-2">
                <div className="w-3 h-3 bg-blue-500 rounded-full"></div>
                <span>Path Line</span>
              </div>
            </div>
          </div>
        </div>

        <div className="mt-8 bg-white rounded-lg shadow-lg p-6">
          <h3 className="text-lg font-semibold text-gray-900 mb-4">Path Information</h3>
          <div className="grid grid-cols-1 md:grid-cols-3 gap-4 text-sm">
            <div className="bg-gray-50 p-4 rounded-lg">
              <div className="font-medium text-gray-700">Total Points</div>
              <div className="text-2xl font-bold text-indigo-600">
                {pathData.split(' L ').length}
              </div>
            </div>
            <div className="bg-gray-50 p-4 rounded-lg">
              <div className="font-medium text-gray-700">Path Length</div>
              <div className="text-2xl font-bold text-indigo-600">
                {Math.round(pathData.split(' L ').length * 50)}px
              </div>
            </div>
            <div className="bg-gray-50 p-4 rounded-lg">
              <div className="font-medium text-gray-700">Status</div>
              <div className="text-2xl font-bold text-indigo-600">
                {isAnimating ? "Animating" : "Static"}
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Path; 