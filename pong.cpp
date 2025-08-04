#include "raylib.h"
#include<iostream>
    const float screenWidth = 800;
    const float screenHeight = 600;
    int playerScore=0;
    int playerScore2=0;
    int aiScore=0;
    char howToPlay;
    

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
        if (howToPlay=='l'){

        if(posX - radius < 0){
            playerScore2++;
            posX = screenWidth / 2;
            posY = screenHeight / 2;
            speedX = 5;
            speedY = 5;
            return;
        }
        }
        if (howToPlay=='o'){
        if(posX - radius < 0){
            aiScore++;
            posX = screenWidth / 2;
            posY = screenHeight / 2;
            speedX = 5;
            speedY = 5;
            return;
        }
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

    void update(int option){
        if(option == 0){
        if (IsKeyDown(KEY_W)) posY -= 5;
        if (IsKeyDown(KEY_S)) posY += 5;
        }
        if(option == 1){
        if (IsKeyDown(KEY_UP)) posY -= 5;
        if (IsKeyDown(KEY_DOWN)) posY += 5;
        }
        if (posY < 0) posY = 0;
        if (posY + height > screenHeight) posY = screenHeight - height;
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
    pedal sq3(790,300,10,75);

   
    

    InitWindow(screenWidth, screenHeight, "Basic Raylib Window");

    SetTargetFPS(60); 


    while (WindowShouldClose()==false) {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleGradientV(0, 0, screenWidth, screenHeight, SKYBLUE, DARKBLUE);

        if (howToPlay != 'l' && howToPlay != 'o') {
            DrawText("Press 1 to to play with Friend", 250, 250, 30, BLACK);
            DrawText("Press 2 to play vs AI", 250, 300, 30, BLACK);
        }

        if (IsKeyPressed(KEY_ONE)) howToPlay = 'l';
        if (IsKeyPressed(KEY_TWO)) howToPlay = 'o';
// to play with friend
        if (howToPlay=='l'){
        sq1.draw();
        sq3.draw();
        ball.draw();
        ball.speed();
        Rectangle paddle1 = { (float)sq1.posX, (float)sq1.posY, (float)sq1.width, (float)sq1.height };
        Rectangle paddle3 = { (float)sq3.posX, (float)sq3.posY, (float)sq3.width, (float)sq3.height };
        if (CheckCollisionCircleRec(Vector2{ball.posX, ball.posY}, ball.radius, paddle1) ||
            CheckCollisionCircleRec(Vector2{ball.posX, ball.posY}, ball.radius, paddle3)) {
            ball.speedX *= -1;
        }
        for (int i = 0; i < screenHeight; i += 40) {
            DrawRectangle(398, i, 4, 20, RED);
        }
        DrawText(TextFormat("Player: %i", playerScore), 100, 20, 30, BLACK);
        DrawText(TextFormat("Player2: %i", playerScore2), 600, 20, 30, BLACK);
        sq1.update(0);
        sq3.update(1);
        }

// to play with ai
        if(howToPlay=='o'){
        sq1.draw();
        sq2.draw();
        ball.draw();
        ball.speed();
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

        sq1.update(0);
        sq2.trackBall(ball.posY);
        }
        
        
        EndDrawing();
    }

    // De-initialization
    CloseWindow();

    return 0;
}