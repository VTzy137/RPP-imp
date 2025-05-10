import React from "react";
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import Navbar from "./components/Navbar/Navbar";
import Home from "./pages/Home";
import Chart from "./pages/Chart";

const App: React.FC = () => {
  return (
    <Router basename="/RPP-imp">
      <div className="bg-gray-800 text-center min-h-screen flex flex-col">
        <Navbar />
          <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/chart" element={<Chart />} />
          </Routes>
      </div>
    </Router>
  );
};

export default App;
