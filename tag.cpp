#include<raylib.h>
#include<iostream>
int screenHeight=600;
int screenWidth=800;
int playerHeight=30,playerWidth=30;
class Path{
    public:
    int x, y, size;
    Path(int px, int py, int s){
        x = px;
        y = py;
        size = s;
    }
    void draw(){
        DrawRectangleLines(x, y, size, size, RED);
    }
};
class Player{
    public:
    int x,y,speedx,speedy;
    float gravity , velocityY;
    Player(){
        x=screenWidth/2;
        y=screenHeight/2;
        speedx=10;
        speedy=10;
        gravity = 0.5f;
        velocityY = 0;
    };
    void draw(){
        DrawRectangle(x,y,playerWidth,playerHeight,BLACK);
    }
    void update(){
        if(IsKeyDown(KEY_A)) x -= speedx;
        if(IsKeyDown(KEY_D)) x += speedx;

        if(IsKeyPressed(KEY_W)) velocityY = -10.0f;
        velocityY += gravity;
        y += static_cast<int>(velocityY);
        if((int)IsKeyPressed(KEY_W)>2) velocityY=0;
        if (y < 0) {
            y = 0;
            velocityY = 0;
        }
        if (y + playerHeight > screenHeight) {
            y = screenHeight - playerHeight;
            velocityY = 0;
        }

    }

    
};
Player player;
int main(){
    InitWindow(screenWidth,screenHeight,"TAG");
    SetTargetFPS(60);
    Path squarePath(100, 100, 200);
    while(WindowShouldClose()==false){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        squarePath.draw();
        player.draw();
        player.update();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}