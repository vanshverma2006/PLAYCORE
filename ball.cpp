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

class Wall{
    public:
    int posx,posy,speedx;
    int height,width;
Wall(){}
Wall(int posx,int posy,int width,int height,int speedx){
    this->posx=posx;
    this->posy=posy;
    this->width=width;
    this->height=height;
    this->speedx=speedx;
}
void draw(){
    DrawRectangle(posx,posy,width,height,BLACK);
}
void update() {
    posx -= speedx; // move wall left
    // If you want to reset it when it leaves screen, you can do:
    if (posx + width < 0) {
        posx = screenWidth; // reset to right edge
    }

    }

};
    Ball ball(screenWidth/2,screenHeight/2,10);
    Wall wall(screenWidth,screenHeight-100,20,100,5);
int main() {

    InitWindow(screenWidth, screenHeight, "Basic Raylib Window");

    SetTargetFPS(60); 


    while (WindowShouldClose()==false) {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        ball.draw();
        ball.update();
        wall.draw();
        wall.update();

    

        EndDrawing();
    }


    CloseWindow();

    return 0;
}