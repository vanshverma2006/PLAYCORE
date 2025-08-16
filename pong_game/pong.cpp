#include "raylib.h"
#include <iostream>

const float screenWidth = 800;
const float screenHeight = 600;
int playerScore = 0;
int playerScore2 = 0;
int aiScore = 0;
char howToPlay='\0';

Color DARK_TEAL = {0, 128, 128, 255};
Color LIGHT_TEAL = {0, 160, 160, 255};
Color BALL_COLOR = {255, 255, 255, 255};
Color PADDLE_COLOR = {255, 255, 255, 255};

class Ball {
public:
    float posX, posY;
    int speedX, speedY;
    float radius;
    Ball(){}
    Ball(float posX, float posY, int speedX, int speedY, float radius) {
        this->posX = posX;
        this->posY = posY;
        this->speedX = speedX;
        this->speedY = speedY;
        this->radius = radius;
    }
    void draw() {
        DrawCircle(posX, posY, radius, BALL_COLOR);
    }
    void speed() {
        posX += speedX;
        posY += speedY;

        if (howToPlay == 'l') {
            if (posX - radius < 0) {
                playerScore2++;
                posX = screenWidth / 2;
                posY = GetRandomValue(radius, screenHeight-radius);
                speedX = 5; speedY = 5;
                return;
            }
        }
        if (howToPlay == 'o') {
            if (posX - radius < 0) {
                aiScore++;
                posX = screenWidth / 2;
                posY = GetRandomValue(radius, screenHeight-radius);
                speedX = 5; speedY = 5;
                return;
            }
        }
        if (posX + radius > screenWidth) {
            playerScore++;
            posX = screenWidth / 2;
            posY = GetRandomValue(radius,screenHeight-radius);
            speedX = -5; speedY = 5;
            return;
        }
        if (posY + radius >= screenHeight || posY - radius <= 0) {
            speedY *= -1;
        }
    }
};

class Paddle {
public:
    int posX, posY, width, height;
    Paddle(){}
    Paddle(int posX, int posY, int width, int height) {
        this->posX = posX;
        this->posY = posY;
        this->width = width;
        this->height = height;
    }
    void draw() {
        DrawRectangle(posX, posY, width, height, PADDLE_COLOR);
    }
    void update(int option) {
        if (option == 0) {
            if (IsKeyDown(KEY_W)) posY -= 5;
            if (IsKeyDown(KEY_S)) posY += 5;
        }
        if (option == 1) {
            if (IsKeyDown(KEY_I)) posY -= 5;
            if (IsKeyDown(KEY_K)) posY += 5;
        }
        if (posY < 0) posY = 0;
        if (posY + height > screenHeight) posY = screenHeight - height;
    }
};

class Ai : public Paddle {
public:
    Ai(){}
    Ai(int posX, int posY, int width, int height) {
        this->posX = posX;
        this->posY = posY;
        this->width = width;
        this->height = height;
    }
    void trackBall(float ballY) {
        if (ballY < posY && posY > 0) posY -= 5;
        else if (ballY > posY + height && posY + height < screenHeight) posY += 5;
    }
};

int main() {
    Ball ball(screenWidth / 2, screenHeight / 2, 6, 6, 10);
    Paddle sq1(1, 300, 10, 75);
    Ai sq2(790, 300, 10, 75);
    Paddle sq3(790, 300, 10, 75);

    InitWindow(screenWidth, screenHeight, "Pong Minimal");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

   
        ClearBackground(DARK_TEAL);
        DrawRectangle(screenWidth/2, 0, screenWidth/2, screenHeight, LIGHT_TEAL);

        if (howToPlay != 'l' && howToPlay != 'o') {
            Rectangle friendBox = {250, 250, 300, 60};
            Rectangle aiBox = {250, 350, 300, 60};
            
            Vector2 mousePos = GetMousePosition();

            Color friendColor = DARK_TEAL;
            Color aiColor = LIGHT_TEAL;

            if (CheckCollisionPointRec(mousePos, friendBox)) {
                friendColor = {0, 180, 180, 255}; 
            }
            if (CheckCollisionPointRec(mousePos, aiBox)) {
                aiColor = {0, 210, 210, 255};
            }

            DrawRectangleRec(friendBox, friendColor);
            DrawText("Play with Friend", friendBox.x + 20, friendBox.y + 15, 30, BLACK);

            DrawRectangleRec(aiBox, aiColor);
            DrawText("Play vs AI", aiBox.x + 20, aiBox.y + 15, 30, BLACK);

            DrawRectangleLinesEx(friendBox, 3, BLACK);
            DrawRectangleLinesEx(aiBox, 3, BLACK);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mousePos, friendBox)) {
                    howToPlay = 'l';
                }
                if (CheckCollisionPointRec(mousePos, aiBox)) {
                    howToPlay = 'o';
                }
            }
        }

        if (howToPlay == 'l') {
            sq1.draw();
            sq3.draw();
            ball.draw();
            ball.speed();
            Rectangle paddle1 = {(float)sq1.posX, (float)sq1.posY, (float)sq1.width, (float)sq1.height};
            Rectangle paddle3 = {(float)sq3.posX, (float)sq3.posY, (float)sq3.width, (float)sq3.height};
            if (CheckCollisionCircleRec(Vector2{ball.posX, ball.posY}, ball.radius, paddle1) ||
                CheckCollisionCircleRec(Vector2{ball.posX, ball.posY}, ball.radius, paddle3)) {
                ball.speedX *= -1;
            }
            DrawText(TextFormat("%i", playerScore), screenWidth / 4, 20, 40, WHITE);
            DrawText(TextFormat("%i", playerScore2), screenWidth * 3 / 4, 20, 40, WHITE);
            sq1.update(0);
            sq3.update(1);
        }

        if (howToPlay == 'o') {
            sq1.draw();
            sq2.draw();
            ball.draw();
            ball.speed();
            Rectangle paddle1 = {(float)sq1.posX, (float)sq1.posY, (float)sq1.width, (float)sq1.height};
            Rectangle paddle2 = {(float)sq2.posX, (float)sq2.posY, (float)sq2.width, (float)sq2.height};
            if (CheckCollisionCircleRec(Vector2{ball.posX, ball.posY}, ball.radius, paddle1) ||
                CheckCollisionCircleRec(Vector2{ball.posX, ball.posY}, ball.radius, paddle2)) {
                ball.speedX *= -1;
            }
            DrawText(TextFormat("%i", playerScore), screenWidth / 4, 20, 40, WHITE);
            DrawText(TextFormat("%i", aiScore), screenWidth * 3 / 4, 20, 40, WHITE);
            sq1.update(0);
            sq2.trackBall(ball.posY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}