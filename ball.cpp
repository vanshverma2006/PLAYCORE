#include "raylib.h"
#include <iostream>
#include <vector>

const int screenWidth = 800;
const int screenHeight = 600;

class Bird {
public:
    int posX, posY, radius;
    float gravity, velocityY;
    Texture2D texture;
    Bird() {}
    Bird(int posX, int posY, int radius, Texture2D texture) {
        this->posX = posX;
        this->posY = posY;
        this->radius = radius;
        this->texture = texture;
        gravity = 0.5f;
        velocityY = 0;
    }
    void draw() {
        float scale = 0.1f;
        float scaledWidth = texture.width * scale;
        float scaledHeight = texture.height * scale;

        Vector2 position = { posX - scaledWidth / 2.0f, posY - scaledHeight / 2.0f };
        DrawTextureEx(texture, position, 0.0f, scale, WHITE);
    }
    void update() {
        if (IsKeyPressed(KEY_SPACE)) velocityY = -10.0f;
        velocityY += gravity;
        posY += static_cast<int>(velocityY);

        if (posY - radius < 0) posY = radius; // Ceiling collision
        if (posY + radius > screenHeight) posY = screenHeight - radius; // Ground collision
    }
    Rectangle getBounds() {
        return Rectangle{ (float)(posX - radius), (float)(posY - radius), (float)(radius * 2), (float)(radius * 2) };
    }
};

class Wall {
public:
    int posx, topPipeHeight, width, gapHeight;
    int speedx;

    Wall() {}
    Wall(int gapHeight, int width, int speedx) {
        this->posx = screenWidth;
        this->width = width;
        this->gapHeight = gapHeight;
        this->speedx = speedx;
        this->topPipeHeight = GetRandomValue(50, screenHeight - gapHeight - 50);
    }

    void draw() {

        DrawRectangle(posx, 0, width, topPipeHeight, GREEN);

        DrawRectangle(posx, topPipeHeight + gapHeight, width, screenHeight - (topPipeHeight + gapHeight), GREEN);
    }

    void update() {
        posx -= speedx;
        if (posx + width < 0) {
            posx = screenWidth;
            topPipeHeight = GetRandomValue(50, screenHeight - gapHeight - 50);
        }
    }

    Rectangle getTopBounds() {
        return Rectangle{ (float)posx, 0.0f, (float)width, (float)topPipeHeight };
    }

    Rectangle getBottomBounds() {
        return Rectangle{ (float)posx, (float)(topPipeHeight + gapHeight), (float)width, (float)(screenHeight - (topPipeHeight + gapHeight)) };
    }
};

int main() {
    InitWindow(screenWidth, screenHeight, "Flappy Bird");

    SetTargetFPS(60);

    Texture2D birdTexture = LoadTexture("bird.png");

    Bird bird(screenWidth / 4, screenHeight / 2, 12, birdTexture);

    const int pipeCount = 3;
    const int pipeSpacing = 300;
    const int pipeWidth = 60;
    const int pipeSpeed = 4;
    const int gapHeight = 200;

    std::vector<Wall> pipes;
    for (int i = 0; i < pipeCount; i++) {
        Wall pipe(gapHeight, pipeWidth, pipeSpeed);
        pipe.posx = screenWidth + i * pipeSpacing;
        pipes.push_back(pipe);
    }

    int score = 0;
    bool gameOver = false;
    bool gameStarted = false;

    while (!WindowShouldClose()) {
        if (!gameStarted) {
            if (IsKeyPressed(KEY_ENTER)) {
                gameStarted = true;
                gameOver = false;
                bird.posX = screenWidth / 4;
                bird.posY = screenHeight / 2;
                bird.velocityY = 0;
                score = 0;
                for (int i = 0; i < pipeCount; i++) {
                    pipes[i].posx = screenWidth + i * pipeSpacing;
                    pipes[i].topPipeHeight = GetRandomValue(50, screenHeight - gapHeight - 50);
                }
            }
        }

        if (gameStarted && !gameOver) {
            bird.update();

            for (int i = 0; i < pipeCount; i++) {
                pipes[i].update();


                if (CheckCollisionRecs(bird.getBounds(), pipes[i].getTopBounds()) ||
                    CheckCollisionRecs(bird.getBounds(), pipes[i].getBottomBounds())) {
                    gameOver = true;
                }


                if (pipes[i].posx + pipes[i].width == bird.posX) {
                    score++;
                }
            }


            if (bird.posY + bird.radius >= screenHeight || bird.posY - bird.radius <= 0) {
                gameOver = true;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!gameStarted) {
            DrawText("Press ENTER to Start", screenWidth / 2 - MeasureText("Press ENTER to Start", 20) / 2, screenHeight / 2 - 10, 20, BLACK);
        }
        else {
            bird.draw();
            for (int i = 0; i < pipeCount; i++) {
                pipes[i].draw();
            }

            DrawText(TextFormat("Score: %d", score), screenWidth / 2 - MeasureText(TextFormat("Score: %d", score), 20) / 2, 10, 20, BLACK);

            if (gameOver) {
                DrawText("Game Over! Press R to Restart", screenWidth / 2 - MeasureText("Game Over! Press R to Restart", 20) / 2, screenHeight / 2 - 20, 20, RED);
                if (IsKeyPressed(KEY_R)) {

                    bird.posX = screenWidth / 4;
                    bird.posY = screenHeight / 2;
                    bird.velocityY = 0;
                    score = 0;
                    gameOver = false;
                    gameStarted = false;
                    for (int i = 0; i < pipeCount; i++) {
                        pipes[i].posx = screenWidth + i * pipeSpacing;
                        pipes[i].topPipeHeight = GetRandomValue(50, screenHeight - gapHeight - 50);
                    }
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(birdTexture);

    CloseWindow();

    return 0;
}