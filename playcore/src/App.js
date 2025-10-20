// src/App.js
import React from "react";
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";

// Import all your pages
import Intro from "./pages/intro";
import SignIn from "./pages/signIn";
import SignUp from "./pages/signUp";
import Pong from "./pages/pong";
import Front from "./pages/front";
import Dodge from "./pages/dodge";


function App() {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<Intro />} />
        <Route path="/signin" element={<SignIn />} />
        <Route path="/signup" element={<SignUp />} />
        <Route path="/pong" element={<Pong />} />
        <Route path="/front" element={<Front />} />
        <Route path="/dodge" element={<Dodge />} />
      </Routes>
    </Router>
  );
}

export default App;