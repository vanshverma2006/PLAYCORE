#include "raylib.h"
#include<iostream>
    const int screenWidth = 800;
    const int screenHeight = 600;
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
Wall wall(screenWidth,screenHeight-100,20,100,10);
int main() {
    // Initialization
    InitWindow(screenWidth, screenHeight, "Basic Raylib Window");

    SetTargetFPS(60); // Set desired frame rate

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        wall.draw();
        wall.update();
    


        EndDrawing();
    }

    // De-initialization
    CloseWindow();

    return 0;
}