#include<iostream>
#include<raylib.h>
const int screenHeight=600;
const int screenWidth=800;
class Food{
    public:
    int x,y,height,width;
    Food(){
        x=GetRandomValue(20,screenWidth-20);
        y=GetRandomValue(30,screenHeight-20);
        height=10;
        width=10;
    }
    void draw(){
        DrawRectangle(x,y,width,height,RED);
    }
    void update(){
        x=GetRandomValue(20,screenWidth-20);
        y=GetRandomValue(30,screenHeight-20);
    }
    
};
class Snake{
public:
    std::vector<Vector2> body;
    int height, width;
    int speedX, speedY;

    Snake(int startX, int startY, int height, int width, int speedX, int speedY) {
        this->height = height;
        this->width = width;
        this->speedX = speedX;
        this->speedY = speedY;
        body.push_back({(float)startX, (float)startY}); // head
    }

    void draw() {
        for (auto &segment : body) {
            DrawRectangle(segment.x, segment.y, width, height, BLACK);
        }
    }

    void update() {
        // Change direction
        if (IsKeyPressed(KEY_A)) { speedX = -4; speedY = 0; }
        if (IsKeyPressed(KEY_D)) { speedX = 4; speedY = 0; }
        if (IsKeyPressed(KEY_W)) { speedX = 0; speedY = -4; }
        if (IsKeyPressed(KEY_S)) { speedX = 0; speedY = 4; }

        // Move body segments (from tail to head)
        for (int i = body.size() - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }

        // Move head
        body[0].x += speedX;
        body[0].y += speedY;
    }

    void grow() {
        Vector2 tail = body.back();
        body.push_back(tail); // add new segment at tail position
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
            Rectangle{snake.body[0].x, snake.body[0].y, (float)snake.width, (float)snake.height},
            Rectangle{(float)food.x, (float)food.y, (float)food.width, (float)food.height}
        )) 
        {
            food.update();
            snake.grow();
        }



        EndDrawing();
    }


    CloseWindow();
    return 0;
}