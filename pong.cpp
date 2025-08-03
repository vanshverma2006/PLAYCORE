#include "raylib.h"
#include<iostream>
    const float screenWidth = 800;
    const float screenHeight = 600;
    int playerScore=0;
    int aiScore=0;

class Ball{
    public:
    float posX;
    float posY;
    int speedX,speedY;
    float radius;
    Ball(){}
    Ball(float posX,float posY,int speedX,int speedY,float radius){
        this->posX=posX;
        this->posY=posY;
        this->speedX=speedX; 
        this->speedY=speedY;
        this->radius=radius;
    }
    void draw(){
        DrawCircleGradient(posX, posY, radius, RED, RED);
    }
    void speed(){
        posX += speedX;
        posY += speedY;

        // Scoring logic
        if(posX - radius < 0){
            aiScore++;
            posX = screenWidth / 2;
            posY = screenHeight / 2;
            speedX = 5;
            speedY = 5;
            return;
        }
        if(posX + radius > screenWidth){
            playerScore++;
            posX = screenWidth / 2;
            posY = screenHeight / 2;
            speedX = -5;
            speedY = 5;
            return;
        }

        // Wall collision (top and bottom only)
        if (posY + radius >= screenHeight || posY - radius <= 0){
            speedY *= -1;
        }
    }
};

class pedal{
    public:
    int posX;
    int posY;
    int width,height;
    char key;
    pedal(){}
    pedal(int posX,int posY,int width,int height){
        this-> posX=posX;
        this-> posY=posY;
        this-> width=width;
        this-> height=height;
    }
    void draw(){
        DrawRectangleRounded((Rectangle){(float)posX, (float)posY, (float)width, (float)height}, 0.3f, 10, BLUE);
        DrawRectangleLinesEx((Rectangle){(float)posX, (float)posY, (float)width, (float)height}, 2, BLACK);
    }

    //     void update(bool isPlayerOne){
    //     if (isPlayerOne) {
    //         if (IsKeyDown(KEY_W)) posY -= 5;
    //         if (IsKeyDown(KEY_S)) posY += 5;
    //     } else {
    //         if (IsKeyDown(KEY_UP)) posY -= 5;
    //         if (IsKeyDown(KEY_DOWN)) posY += 5;
    //     }
    // }
    void update(){
        if (IsKeyDown(KEY_W)) posY -= 5;
        if (IsKeyDown(KEY_S)) posY += 5;
    }
    
};

class Ai : public pedal{
    public:
    Ai(){}
    Ai(int posX,int posY,int width,int height){
        this-> posX=posX;
        this-> posY=posY;
        this-> width=width;
        this-> height=height;
    }
    void trackBall(float ballY) {
    if (ballY < posY && posY > 0) posY -= 4;
    else if (ballY > posY + height && posY + height < screenHeight) posY += 4;
}
    
};
int main() {

    
    
    
    Ball ball(screenWidth/2,screenHeight/2,5,5,10);
    pedal sq1(1,300,10,75);
    Ai sq2(790,300,10,75);

    InitWindow(screenWidth, screenHeight, "Basic Raylib Window");

    SetTargetFPS(60); 

    while (WindowShouldClose()==false) {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleGradientV(0, 0, screenWidth, screenHeight, SKYBLUE, DARKBLUE);
        sq1.draw();
        sq2.draw();
        // DrawCircle(screenWidth/2,screenHeight/2,5,BLUE);
        ball.draw();
        ball.speed();
        // Collision detection between ball and paddles
        Rectangle paddle1 = { (float)sq1.posX, (float)sq1.posY, (float)sq1.width, (float)sq1.height };
        Rectangle paddle2 = { (float)sq2.posX, (float)sq2.posY, (float)sq2.width, (float)sq2.height };
        if (CheckCollisionCircleRec(Vector2{ball.posX, ball.posY}, ball.radius, paddle1) ||
            CheckCollisionCircleRec(Vector2{ball.posX, ball.posY}, ball.radius, paddle2)) {
            ball.speedX *= -1;
        }
        for (int i = 0; i < screenHeight; i += 40) {
            DrawRectangle(398, i, 4, 20, RED);
        }
        DrawText(TextFormat("Player: %i", playerScore), 100, 20, 30, BLACK);
        DrawText(TextFormat("AI: %i", aiScore), 600, 20, 30, BLACK);
        // if (IsKeyDown(KEY_W)) sq1.posY -= 5;
        // if (IsKeyDown(KEY_S)) sq1.posY += 5;
        // if (IsKeyDown(KEY_UP)) sq2.posY -= 5;
        // if (IsKeyDown(KEY_DOWN)) sq2.posY += 5;
        sq1.update();
        sq2.trackBall(ball.posY);
        
        EndDrawing();
    }

    // De-initialization
    CloseWindow();

    return 0;
}