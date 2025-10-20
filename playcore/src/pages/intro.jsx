// src/pages/Intro.jsx
import React from "react";
import "../styles/intro.css";
import { Link } from "react-router-dom";

export default function Intro() {
  return (
    <>
      <nav className="navbar">
        <div className="logo">PlayCore</div>
        <ul className="nav-links">
          <li><a href="#home">Home</a></li>
          <li><a href="#about">About</a></li>
          <li><a href="#contact">Contact</a></li>
        </ul>
        <div className="nav-buttons">
          <Link to="/signin" className="btn-outline">Sign In</Link>
          <Link to="/signup" className="btn">Sign Up</Link>
        </div>
      </nav>

      <header className="hero" id="home">
        <div className="hero-text">
          <h1>Discover Endless Fun with <span>PlayCore</span></h1>
          <p>
            PlayCore is your ultimate hub for online games. 
            Sign up, log in, and unlock access to an exciting library of games across genres.
          </p>
          <div className="hero-buttons">
            <Link to="/signup" className="btn">Get Started</Link>
            <a href="#about" className="btn-outline">Learn More</a>
          </div>
        </div>
      </header>

      <section className="why">
        <h2>Why Choose PlayCore?</h2>
        <p>
          We bring together fun, competition, and community. 
          Join players worldwide and enjoy games that are exciting, engaging, and free to play.
        </p>
        <ul>
          <li>🎮 Vast collection of casual, arcade, and strategy games</li>
          <li>🌍 Play and compete with friends across the globe</li>
          <li>⚡ Smooth performance and mobile-friendly design</li>
          <li>🔒 Secure accounts with personalized profiles</li>
        </ul>
      </section>

      <section id="about" className="about">
        <h2>About PlayCore</h2>
        <p>
          PlayCore is more than just a gaming site - it's a community. 
          Our goal is to provide players of all ages with a safe, fun, and interactive platform 
          to explore new games and connect with others. 
        </p>
        <div className="about-content">
          <div>
            <h3>Our Mission</h3>
            <p>
              To create a space where gamers of all skill levels can enjoy, learn, and compete together.
            </p>
          </div>
          <div>
            <h3>Our Features</h3>
            <ul>
              <li>✔️ Curated library of hand-picked games</li>
              <li>✔️ Regular updates with fresh content</li>
              <li>✔️ Player profiles, achievements & leaderboards</li>
              <li>✔️ Lightweight design - works even on low-end devices</li>
            </ul>
          </div>
        </div>
      </section>

      <section id="contact" className="contact">
        <h2>Contact Us</h2>
        <p>
          Have questions, feedback, or suggestions? We'd love to hear from you!  
          Reach out through the form below or connect with us on social media.
        </p>
        <form className="contact-form" onSubmit={(e) => e.preventDefault()}>
          <input type="text" placeholder="Your Name" required />
          <input type="email" placeholder="Your Email" required />
          <textarea placeholder="Your Message" rows="5" required></textarea>
          <button type="submit" className="btn">Send Message</button>
        </form>
        <div className="social-links">
          <p>Follow us:</p>
          <a href="#">🌐 Facebook</a> |{" "}
          <a href="#">🐦 Twitter</a> |{" "}
          <a href="#">📸 Instagram</a>
        </div>
      </section>

      <footer>
        <p>© 2025 PlayCore. All rights reserved.</p>
      </footer>
    </>
  );
}