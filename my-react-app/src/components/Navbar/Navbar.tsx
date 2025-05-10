import React from "react";
import { Link } from "react-router-dom";

const Navbar: React.FC = () => {
  return (
    <nav className="bg-gray-800 h-[60px] flex justify-center items-center text-base sticky top-0 z-50">
      <div className="flex justify-between h-[60px] w-full max-w-6xl px-6">
        <div className="text-white flex items-center text-2xl font-bold no-underline">React App</div>
        <ul className="flex items-center list-none text-center m-0 p-0">
          <li className="h-[60px] flex items-center mx-4">
            <Link to="/" className="text-white flex items-center no-underline px-4 h-full cursor-pointer transition-all duration-200 ease-in-out hover:text-[#61dafb]">Home</Link>
          </li>
          <li className="h-[60px] flex items-center mx-4">
            <Link to="/chart" className="text-white flex items-center no-underline px-4 h-full cursor-pointer transition-all duration-200 ease-in-out hover:text-[#61dafb]">Chart</Link>
          </li>
        </ul>
      </div>
    </nav>
  );
};

export default Navbar; 