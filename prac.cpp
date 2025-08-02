#include "raylib.h"
#include<iostream>
int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    int ballX=400;
    int ballY=300;
    InitWindow(screenWidth, screenHeight, "Basic Raylib Window");

    SetTargetFPS(60); // Set desired frame rate

    // Main game loop
    while (!WindowShouldClose()) {
        // Start drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
    if(IsKeyDown(KEY_RIGHT)){
        ballX+=5;
    }
    if(IsKeyDown(KEY_LEFT)){
        ballX-=5;
    }
    if(IsKeyDown(KEY_UP)){
        ballY-=5;
    }
    if(IsKeyDown(KEY_DOWN)){
        ballY+=5;
    }

    
        DrawCircle(ballX, ballY / 2, 10, MAROON);

        EndDrawing();
    }

    // De-initialization
    CloseWindow();

    return 0;
}