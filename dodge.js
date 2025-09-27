
let screenWidth = document.documentElement.clientWidth * 0.95;
let screenHeight = document.documentElement.clientHeight * 0.75;

const canvas = document.getElementById("gameCanvas");
const ctx = canvas.getContext("2d");

canvas.width = screenWidth;
canvas.height = screenHeight;

let W = screenWidth;
let H = screenHeight;

const spaceshipImg = new Image();
spaceshipImg.src = "imageFolder/spaceship.png";


const overlay = document.getElementById("overlay");
const overlayMessage = document.getElementById("overlayMessage");

let keys = {};
window.addEventListener("keydown", (e) => {
  keys[e.key.toLowerCase()] = true;
  if (e.key === "Enter" && game.state !== "playing") game.start();
});
window.addEventListener("keyup", (e) => keys[e.key.toLowerCase()] = false);

class Player {
  constructor() {
    this.width = 60;
    this.height = 60;
    this.x = W / 2 - this.width / 2;
    this.y = H - this.height - 10;
    this.speed = 6;
  }
  draw() {
    ctx.drawImage(spaceshipImg, this.x, this.y, this.width, this.height);
  }
  update() {
    if (keys["a"] || keys["arrowleft"]) this.x -= this.speed;
    if (keys["d"] || keys["arrowright"]) this.x += this.speed;
    this.x = Math.max(0, Math.min(W - this.width, this.x));
  }
}

class Bullet {
  constructor(x, y) {
    this.width = 5;
    this.height = 10;
    this.x = x;
    this.y = y;
    this.speed = 7;
  }
  draw() {
    ctx.fillStyle = "#ffeb3b";
    ctx.fillRect(this.x, this.y, this.width, this.height);
  }
  update() {
    this.y -= this.speed;
  }
}

class Block {
  constructor() {
    this.width = 40;
    this.height = 20;
    this.x = Math.random() * (W - this.width);
    this.y = -this.height;
    this.speed = 2 + Math.random() * 3;
  }
  draw() {
    ctx.fillStyle = "#ff1744";
    ctx.fillRect(this.x, this.y, this.width, this.height);
  }
  update() {
    this.y += this.speed;
  }
}

class Game {
  constructor() {
    this.reset();
  }
  reset() {
    this.player = new Player();
    this.blocks = [];
    this.bullets = [];
    this.score = 0;
    this.state = "start"; 
    this.lastSpawn = 0;
    this.lastShot = 0;
  }
  start() {
    overlay.style.display = "none";
    this.reset();
    this.state = "playing";
  }
  update() {
    this.player.update();


    if (keys[" "] && Date.now() - this.lastShot > 300) {
      this.bullets.push(new Bullet(this.player.x + this.player.width / 2, this.player.y));
      this.lastShot = Date.now();
    }


    if (Date.now() - this.lastSpawn > 1000) {
      this.blocks.push(new Block());
      this.lastSpawn = Date.now();
    }


    for (let b of this.bullets) b.update();
    this.bullets = this.bullets.filter(b => b.y > -b.height);


    for (let bl of this.blocks) bl.update();
    this.blocks = this.blocks.filter(bl => bl.y < H);


    for (let i = this.blocks.length - 1; i >= 0; i--) {
      for (let j = this.bullets.length - 1; j >= 0; j--) {
        let bl = this.blocks[i];
        let b = this.bullets[j];
        if (b.x < bl.x + bl.width &&
            b.x + b.width > bl.x &&
            b.y < bl.y + bl.height &&
            b.y + b.height > bl.y) {
          this.blocks.splice(i, 1);
          this.bullets.splice(j, 1);
          this.score += 10;
          break;
        }
      }
    }


    for (let bl of this.blocks) {
      if (this.player.x < bl.x + bl.width &&
          this.player.x + this.player.width > bl.x &&
          this.player.y < bl.y + bl.height &&
          this.player.y + this.player.height > bl.y) {
        this.state = "gameover";
        overlay.style.display = "grid";
        overlayMessage.textContent = `Game Over! Score: ${this.score} (Press ENTER)`;
      }
    }
  }
  draw() {
    ctx.clearRect(0, 0, W, H);
    this.player.draw();
    for (let b of this.bullets) b.draw();
    for (let bl of this.blocks) bl.draw();

    ctx.fillStyle = "white";
    ctx.font = "20px Arial";
    ctx.fillText(`Score: ${this.score}`, 20, 30);
  }
}

const game = new Game();

function loop() {
  if (game.state === "playing") {
    game.update();
    game.draw();
  }
  requestAnimationFrame(loop);
}

window.addEventListener("resize", () => {
  screenWidth = document.documentElement.clientWidth * 0.95;
  screenHeight = document.documentElement.clientHeight * 0.75;

  canvas.width = screenWidth;
  canvas.height = screenHeight;

  W = screenWidth;
  H = screenHeight;

  if (game && game.player) {

    game.player.x = Math.max(0, Math.min(W - game.player.width, game.player.x));
    game.player.y = Math.max(0, Math.min(H - game.player.height, game.player.y));
  }
});

window.dispatchEvent(new Event("resize"));
loop();