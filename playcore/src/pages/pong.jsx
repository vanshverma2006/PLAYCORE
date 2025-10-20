// src/pages/Pong.jsx
import React, { useRef, useEffect, useState } from "react";
import "../styles/pong.css"; // use your old pong.css here
import { Link } from "react-router-dom";

export default function Pong() {
  const canvasRef = useRef(null);
  const [mode, setMode] = useState(null);

  useEffect(() => {
    const canvas = canvasRef.current;
    const ctx = canvas.getContext("2d");

    let screenWidth = canvas.clientWidth;
    let screenHeight = canvas.clientHeight;
    canvas.width = screenWidth;
    canvas.height = screenHeight;

    let playerScore = 0;
    let playerScore2 = 0;
    let aiScore = 0;

    const BALL_COLOR = "white";
    const PADDLE_COLOR = "white";
    let keys = {};
    let animationFrame;

    class Ball {
      constructor(x, y, speedX, speedY, radius) {
        this.posX = x;
        this.posY = y;
        this.speedX = speedX;
        this.speedY = speedY;
        this.radius = radius;
      }
      draw() {
        ctx.beginPath();
        ctx.arc(this.posX, this.posY, this.radius, 0, Math.PI * 2);
        ctx.fillStyle = BALL_COLOR;
        ctx.fill();
        ctx.closePath();
      }
      update() {
        this.posX += this.speedX;
        this.posY += this.speedY;

        if (mode === "l") {
          if (this.posX - this.radius < 0) {
            playerScore2++;
            this.reset(5, 5);
            return;
          }
        }
        if (mode === "o") {
          if (this.posX - this.radius < 0) {
            aiScore++;
            this.reset(5, 5);
            return;
          }
        }
        if (this.posX + this.radius > screenWidth) {
          playerScore++;
          this.reset(-5, 5);
          return;
        }
        if (
          this.posY + this.radius >= screenHeight ||
          this.posY - this.radius <= 0
        ) {
          this.speedY *= -1;
        }
      }
      reset(vx, vy) {
        this.posX = screenWidth / 2;
        this.posY =
          Math.random() * (screenHeight - this.radius * 2) + this.radius;
        this.speedX = vx;
        this.speedY = vy;
      }
    }

    class Paddle {
      constructor(x, y, width, height) {
        this.posX = x;
        this.posY = y;
        this.width = width;
        this.height = height;
      }
      draw() {
        ctx.fillStyle = PADDLE_COLOR;
        ctx.fillRect(this.posX, this.posY, this.width, this.height);
      }
      update(option) {
        if (option === 0) {
          if (keys["w"]) this.posY -= 5;
          if (keys["s"]) this.posY += 5;
        }
        if (option === 1) {
          if (keys["i"]) this.posY -= 5;
          if (keys["k"]) this.posY += 5;
        }
        if (this.posY < 0) this.posY = 0;
        if (this.posY + this.height > screenHeight)
          this.posY = screenHeight - this.height;
      }
    }

    class Ai extends Paddle {
      trackBall(ballY) {
        if (ballY < this.posY && this.posY > 0) this.posY -= 5;
        else if (
          ballY > this.posY + this.height &&
          this.posY + this.height < screenHeight
        )
          this.posY += 5;
      }
    }

    let ball = new Ball(screenWidth / 2, screenHeight / 2, 6, 6, 10);
    let sq1 = new Paddle(1, 300, 10, 75);
    let sq2 = new Ai(790, 300, 10, 75);
    let sq3 = new Paddle(790, 300, 10, 75);

    function checkCollision(ball, paddle) {
      return (
        ball.posX - ball.radius < paddle.posX + paddle.width &&
        ball.posX + ball.radius > paddle.posX &&
        ball.posY - ball.radius < paddle.posY + paddle.height &&
        ball.posY + ball.radius > paddle.posY
      );
    }

    function drawScore(score, x, size) {
      ctx.fillStyle = "white";
      ctx.font = size + "px monospace";
      ctx.fillText(score, x, 50);
    }

    function gameLoop() {
      ctx.clearRect(0, 0, screenWidth, screenHeight);

      // background halves
      ctx.fillStyle = "#0d7377";
      ctx.fillRect(0, 0, screenWidth / 2, screenHeight);
      ctx.fillStyle = "#14ffec";
      ctx.fillRect(screenWidth / 2, 0, screenWidth / 2, screenHeight);

      if (mode === "l") {
        sq1.draw();
        sq3.draw();
        ball.draw();
        ball.update();
        if (checkCollision(ball, sq1) || checkCollision(ball, sq3)) {
          ball.speedX *= -1;
        }
        drawScore(playerScore, screenWidth / 4, 40);
        drawScore(playerScore2, (screenWidth * 3) / 4, 40);
        sq1.update(0);
        sq3.update(1);
      }

      if (mode === "o") {
        sq1.draw();
        sq2.draw();
        ball.draw();
        ball.update();
        if (checkCollision(ball, sq1) || checkCollision(ball, sq2)) {
          ball.speedX *= -1;
        }
        drawScore(playerScore, screenWidth / 4, 40);
        drawScore(aiScore, (screenWidth * 3) / 4, 40);
        sq1.update(0);
        sq2.trackBall(ball.posY);
      }

      animationFrame = requestAnimationFrame(gameLoop);
    }

    // key listeners
    const handleKeyDown = (e) => (keys[e.key] = true);
    const handleKeyUp = (e) => (keys[e.key] = false);
    window.addEventListener("keydown", handleKeyDown);
    window.addEventListener("keyup", handleKeyUp);

    // resize listener
    const handleResize = () => {
      screenWidth = canvas.clientWidth;
      screenHeight = canvas.clientHeight;
      canvas.width = screenWidth;
      canvas.height = screenHeight;
    };
    window.addEventListener("resize", handleResize);

    // start loop
    gameLoop();

    return () => {
      cancelAnimationFrame(animationFrame);
      window.removeEventListener("keydown", handleKeyDown);
      window.removeEventListener("keyup", handleKeyUp);
      window.removeEventListener("resize", handleResize);
    };
  }, [mode]);

  return (
    <div id="game-container">
      <canvas ref={canvasRef} id="gameCanvas" width={800} height={600}></canvas>

      {!mode && (
        <div id="menu">
          <h1>Paddle Clash</h1>
          <p>Choose your mode:</p>
          <button className="menu-btn" onClick={() => setMode("l")}>
            👬 Play with Friend
          </button>
          <button className="menu-btn" onClick={() => setMode("o")}>
            🤖 Play vs AI
          </button>
        </div>
      )}

      <div id="bottom-buttons">
        <Link to="/dodge" className="bottom-btn">
          Dodge Master
        </Link>
        <a href="#" className="bottom-btn">
          Flappy Bird
        </a>
        <Link to="/" className="bottom-btn">
          Front
        </Link>
      </div>
    </div>
  );
}