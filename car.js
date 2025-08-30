const playerCar = document.getElementById('playerCar');
const gameContainer = document.querySelector('.game-container');
const scoreDisplay = document.getElementById('score');

let playerPosition = 130;
let score = 0;
let obstacles = [];
let gameInterval;

// Move player car
document.addEventListener('keydown', (e) => {
    if (e.key === 'ArrowLeft' && playerPosition > 0) {
        playerPosition -= 20;
    }
    if (e.key === 'ArrowRight' && playerPosition < 260) {
        playerPosition += 20;
    }
    playerCar.style.left = playerPosition + 'px';
});

// Create obstacles
function createObstacle() {
    const obstacle = document.createElement('div');
    obstacle.classList.add('obstacle');
    obstacle.style.left = Math.floor(Math.random() * 7) * 40 + 'px';
    obstacle.style.top = '0px';
    gameContainer.appendChild(obstacle);
    obstacles.push(obstacle);
}

// Move obstacles
function moveObstacles() {
    for (let i = 0; i < obstacles.length; i++) {
        let top = parseInt(obstacles[i].style.top);
        if (top > 500) {
            gameContainer.removeChild(obstacles[i]);
            obstacles.splice(i, 1);
            i--;
            score++;
            scoreDisplay.textContent = "Score: " + score;
        } else {
            obstacles[i].style.top = top + 5 + 'px';

            // Collision detection
            const obsLeft = parseInt(obstacles[i].style.left);
            const obsTop = top;
            if (
                obsTop + 70 >= 430 && // bottom of player
                obsLeft < playerPosition + 40 &&
                obsLeft + 40 > playerPosition
            ) {
                alert("Game Over! Your score: " + score);
                clearInterval(gameInterval);
                location.reload();
            }
        }
    }
}

// Game loop
gameInterval = setInterval(() => {
    createObstacle();
    moveObstacles();
}, 200);
