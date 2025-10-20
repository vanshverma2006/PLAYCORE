// src/pages/Front.jsx
import React from "react";
import { Link } from "react-router-dom";
import "../styles/front.css";

// ✅ Import your images
import pongImg from "../assets/images/pong1.png";
import dodgeImg from "../assets/images/space-invaders.png";
import flappyImg from "../assets/images/bird.png";

export default function Front() {
  return (
    <div className="front-page">
      <header>PlayCore</header>
      <div className="game-grid">
        <Link to="/pong" className="game-card">
          <img src={pongImg} alt="Paddle Clash" />
          <h3>Paddle Clash</h3>
        </Link>

        <Link to="/dodge" className="game-card">
          <img src={dodgeImg} alt="Dodge Master" />
          <h3>Dodge Master</h3>
        </Link>

        <Link to="/flappy" className="game-card">
          <img src={flappyImg} alt="Flappy Bird" />
          <h3>Flappy Bird</h3>
        </Link>
      </div>
    </div>
  );
}