#include<iostream>
#include<raylib.h>
const int screenHeight=800;
const int screenWidth=1000;
class Food{
    public:
    int x,y,height,width;
    Food(){
        x=GetRandomValue(30,970);
        y=GetRandomValue(30,770);
        height=10;
        width=10;
    }
    void draw(){
        DrawRectangle(x,y,width,height,RED);
    }
    void update(){
        x=GetRandomValue(30,970);
        y=GetRandomValue(30,770);
    }
    
};
class Snake{
public:
    int x,y;
    int height,width;
    int speedX,speedY;
    Snake(int x,int y,int height,int width,int speedX,int speedY){
        this->height=height;
        this->width=width;
        this->speedX=speedX;
        this->speedY=speedY;
        this->x=x;
        this->y=y;
    }
    void draw(){
        DrawRectangle(x,y,width,height,BLACK);
        
        
    }
    void update(){
        if(IsKeyDown(KEY_A)) x-=speedX;
        if(IsKeyDown(KEY_D)) x+=speedX;
        if(IsKeyDown(KEY_W)) y-=speedY;
        if(IsKeyDown(KEY_S)) y+=speedY;
    }
};
Snake snake(screenWidth/2,screenHeight/2,20,20,7,7);
Food food;
int main(){
     InitWindow(screenWidth, screenHeight, "Basic Raylib Window");

    SetTargetFPS(60); 


    while (WindowShouldClose()==false) {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        snake.draw();
        snake.update();
        food.draw();

        if (CheckCollisionRecs(
        Rectangle{(float)snake.x, (float)snake.y, (float)snake.width, (float)snake.height},
        Rectangle{(float)food.x, (float)food.y, (float)food.width, (float)food.height}
    )) 
{
    food.update();
}



        EndDrawing();
    }


    CloseWindow();
    return 0;
}