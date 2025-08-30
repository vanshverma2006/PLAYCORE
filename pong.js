const canvas = document.getElementById("gameCanvas");
const ctx = canvas.getContext("2d");

const screenWidth = 800;
const screenHeight = 600;

let playerScore = 0;
let playerScore2 = 0;
let aiScore = 0;
let howToPlay = null;

const BALL_COLOR = "white";
const PADDLE_COLOR = "white";

// 🎱 Ball Class
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

        // scoring
        if (howToPlay === 'l') {
            if (this.posX - this.radius < 0) {
                playerScore2++;
                this.reset(5, 5);
                return;
            }
        }
        if (howToPlay === 'o') {
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

        // bounce off top/bottom
        if (this.posY + this.radius >= screenHeight || this.posY - this.radius <= 0) {
            this.speedY *= -1;
        }
    }
    reset(vx, vy) {
        this.posX = screenWidth / 2;
        this.posY = Math.random() * (screenHeight - this.radius * 2) + this.radius;
        this.speedX = vx;
        this.speedY = vy;
    }
}

// 🏓 Paddle Class
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
        if (this.posY + this.height > screenHeight) this.posY = screenHeight - this.height;
    }
}

// 🤖 AI Paddle extends Paddle
class Ai extends Paddle {
    trackBall(ballY) {
        if (ballY < this.posY && this.posY > 0) this.posY -= 5;
        else if (ballY > this.posY + this.height && this.posY + this.height < screenHeight) this.posY += 5;
    }
}

// 🎮 Game objects
let ball = new Ball(screenWidth/2, screenHeight/2, 6, 6, 10);
let sq1 = new Paddle(1, 300, 10, 75);
let sq2 = new Ai(790, 300, 10, 75);
let sq3 = new Paddle(790, 300, 10, 75);

// ⌨️ Input handling
let keys = {};
window.addEventListener("keydown", e => keys[e.key] = true);
window.addEventListener("keyup", e => keys[e.key] = false);

// 🌀 Main loop
function gameLoop() {
    ctx.clearRect(0, 0, screenWidth, screenHeight);

    // background halves
    ctx.fillStyle = "#0d7377";
    ctx.fillRect(0, 0, screenWidth/2, screenHeight);
    ctx.fillStyle = "#14ffec";
    ctx.fillRect(screenWidth/2, 0, screenWidth/2, screenHeight);

    // friend mode
    if (howToPlay === 'l') {
        sq1.draw();
        sq3.draw();
        ball.draw();
        ball.update();
        if (checkCollision(ball, sq1) || checkCollision(ball, sq3)) {
            ball.speedX *= -1;
        }
        drawScore(playerScore, screenWidth/4, 40);
        drawScore(playerScore2, screenWidth*3/4, 40);
        sq1.update(0);
        sq3.update(1);
    }

    // AI mode
    if (howToPlay === 'o') {
        sq1.draw();
        sq2.draw();
        ball.draw();
        ball.update();
        if (checkCollision(ball, sq1) || checkCollision(ball, sq2)) {
            ball.speedX *= -1;
        }
        drawScore(playerScore, screenWidth/4, 40);
        drawScore(aiScore, screenWidth*3/4, 40);
        sq1.update(0);
        sq2.trackBall(ball.posY);
    }

    requestAnimationFrame(gameLoop);
}

// 🏆 Draw Score
function drawScore(score, x, size) {
    ctx.fillStyle = "white";
    ctx.font = size + "px 'Press Start 2P', monospace";
    ctx.fillText(score, x, 50);
}

// 🎯 Collision Detection
function checkCollision(ball, paddle) {
    return (
        ball.posX - ball.radius < paddle.posX + paddle.width &&
        ball.posX + ball.radius > paddle.posX &&
        ball.posY - ball.radius < paddle.posY + paddle.height &&
        ball.posY + ball.radius > paddle.posY
    );
}

// 🕹️ Menu buttons
document.getElementById("friendBtn").addEventListener("click", () => {
    howToPlay = 'l';
    document.querySelector("#menu h1").classList.add("hidden");
    document.querySelector("#menu p").classList.add("hidden");
    document.getElementById("friendBtn").classList.add("hidden");
    document.getElementById("aiBtn").classList.add("hidden");
});
document.getElementById("aiBtn").addEventListener("click", () => {
    howToPlay = 'o';
    document.querySelector("#menu h1").classList.add("hidden");
    document.querySelector("#menu p").classList.add("hidden");
    document.getElementById("friendBtn").classList.add("hidden");
    document.getElementById("aiBtn").classList.add("hidden");
});

gameLoop();