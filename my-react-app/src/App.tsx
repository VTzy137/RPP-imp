import React from "react";
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import "./App.css";
import Navbar from "./components/Navbar/Navbar";
import Home from "./pages/Home";
import Chart from "./pages/Chart";

const App: React.FC = () => {
  return (
    <Router>
      <div className="App">
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
