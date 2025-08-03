#include "raylib.h"
#include<iostream>
    const int screenWidth = 800;
    const int screenHeight = 600;

class Ball{
    public:
    int posX,posY,radius;
    float gravity,velocityY;
    Ball(){}
    Ball(int posX,int posY,int radius){
        this->posX=posX;
        this->posY=posY;
        this->radius=radius;
        gravity=0.5f;
        velocityY=0;
    }
    void draw(){
        DrawCircle(posX,posY,radius,BLACK);
    }
    void update(){
        if (posY + radius >= screenHeight) posY = screenHeight - radius;
        if (IsKeyPressed(KEY_SPACE)) velocityY = -10.0f;
        velocityY += gravity;
        // posY += static_cast<int>(velocityY);
        posY += velocityY;
    }
};
    Ball ball(screenWidth/2,screenHeight/2,10);
int main() {

    InitWindow(screenWidth, screenHeight, "Basic Raylib Window");

    SetTargetFPS(60); 


    while (WindowShouldClose()==false) {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        ball.draw();
        ball.update();

    

        EndDrawing();
    }


    CloseWindow();

    return 0;
}