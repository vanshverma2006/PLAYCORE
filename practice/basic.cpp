#include "raylib.h"
#include<iostream>
int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Basic Raylib Window");

    SetTargetFPS(60); // Set desired frame rate

    // Main game loop
    while (WindowShouldClose()==false) {
        // Start drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Hello from Raylib!", 190, 200, 20, LIGHTGRAY);
        DrawCircle(screenWidth / 2, screenHeight / 2, 50, MAROON);

        EndDrawing();
    }

    // De-initialization
    CloseWindow();

    return 0;
}