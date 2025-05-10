import React from "react";
import logo from "../logo.svg";
import "./Home.css";

const Home: React.FC = () => {
  return (
    <div className="home-container">
      <div className="home-content">
        <div className="header">
          <img src={logo} className="logo" alt="logo" />
          <h1 className="title">
            Welcome to <span className="title-highlight">RPP-imp</span>
          </h1>
          <p className="subtitle">
            Revolutionary Particle Population Implementation for Evolutionary Computing
          </p>
        </div>

        <div className="card-grid">
          <div className="card">
            <div className="card-header">
              <h3 className="card-title">Features</h3>
            </div>
            <div className="card-body">
              <ul className="feature-list">
                <li className="feature-item">
                  <svg className="feature-icon" width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
                    <path
                      fillRule="evenodd"
                      d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z"
                      clipRule="evenodd"
                    />
                  </svg>
                  Advanced evolutionary algorithms
                </li>
                <li className="feature-item">
                  <svg className="feature-icon" width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
                    <path
                      fillRule="evenodd"
                      d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z"
                      clipRule="evenodd"
                    />
                  </svg>
                  Particle Swarm Optimization
                </li>
                <li className="feature-item">
                  <svg className="feature-icon" width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
                    <path
                      fillRule="evenodd"
                      d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z"
                      clipRule="evenodd"
                    />
                  </svg>
                  Genetic Algorithms
                </li>
              </ul>
            </div>
          </div>

          <div className="card">
            <div className="card-header">
              <h3 className="card-title">Performance</h3>
            </div>
            <div className="card-body">
              <ul className="feature-list">
                <li className="feature-item">
                  <svg className="feature-icon" width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
                    <path
                      fillRule="evenodd"
                      d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z"
                      clipRule="evenodd"
                    />
                  </svg>
                  High-performance C++ core
                </li>
                <li className="feature-item">
                  <svg className="feature-icon" width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
                    <path
                      fillRule="evenodd"
                      d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z"
                      clipRule="evenodd"
                    />
                  </svg>
                  Optimized for multi-dimensional problems
                </li>
                <li className="feature-item">
                  <svg className="feature-icon" width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
                    <path
                      fillRule="evenodd"
                      d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z"
                      clipRule="evenodd"
                    />
                  </svg>
                  Fast convergence rates
                </li>
              </ul>
            </div>
          </div>

          <div className="card">
            <div className="card-header">
              <h3 className="card-title">Visualization</h3>
            </div>
            <div className="card-body">
              <ul className="feature-list">
                <li className="feature-item">
                  <svg className="feature-icon" width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
                    <path
                      fillRule="evenodd"
                      d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z"
                      clipRule="evenodd"
                    />
                  </svg>
                  Interactive charts
                </li>
                <li className="feature-item">
                  <svg className="feature-icon" width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
                    <path
                      fillRule="evenodd"
                      d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z"
                      clipRule="evenodd"
                    />
                  </svg>
                  Real-time convergence monitoring
                </li>
                <li className="feature-item">
                  <svg className="feature-icon" width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
                    <path
                      fillRule="evenodd"
                      d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z"
                      clipRule="evenodd"
                    />
                  </svg>
                  Solution space visualization
                </li>
              </ul>
            </div>
          </div>
        </div>

        <div className="cta-container">
          <a href="/chart" className="cta-button">
            View Charts
            <svg
              className="cta-icon"
              width="20"
              height="20"
              xmlns="http://www.w3.org/2000/svg"
              viewBox="0 0 20 20"
              fill="currentColor"
              aria-hidden="true"
            >
              <path
                fillRule="evenodd"
                d="M10.293 3.293a1 1 0 011.414 0l6 6a1 1 0 010 1.414l-6 6a1 1 0 01-1.414-1.414L14.586 11H3a1 1 0 110-2h11.586l-4.293-4.293a1 1 0 010-1.414z"
                clipRule="evenodd"
              />
            </svg>
          </a>
        </div>
      </div>
    </div>
  );
};

export default Home;
