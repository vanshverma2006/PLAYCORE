#include<iostream>
#include<raylib.h>
#include<vector>
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

        // DrawCircle(x + width/2, y + height/2, width/2 + 4, (Color){255, 255, 100, 80});
        // DrawCircle(x + width/2, y + height/2, width/2 + 2, (Color){255, 255, 150, 150});
        DrawCircle(x + width/2, y + height/2, width/2, (Color){255, 193, 20, 255});

        // int spikes = 8;
        // float centerX = x + width/2;
        // float centerY = y + height/2;
        // float radius = width/2;
        // for (int i = 0; i < spikes; i++) {
        //     float angle = i * (2 * PI / spikes);
        //     float spikeX1 = centerX + cos(angle) * radius;
        //     float spikeY1 = centerY + sin(angle) * radius;
        //     float spikeX2 = centerX + cos(angle) * (radius + 6);
        //     float spikeY2 = centerY + sin(angle) * (radius + 6);
        //     DrawLine(spikeX1, spikeY1, spikeX2, spikeY2, (Color){255, 213, 79, 200});
        // }
    }
    void update(const std::vector<Vector2>& snakeBody, int snakeWidth, int snakeHeight){
        bool validPosition = false;
        while (!validPosition) {
            x = GetRandomValue(20, screenWidth - 20);
            y = GetRandomValue(30, screenHeight - 20);
            validPosition = true;
            for (const auto& segment : snakeBody) {
                Rectangle foodRect = {(float)x, (float)y, (float)width, (float)height};
                Rectangle segmentRect = {segment.x, segment.y, (float)snakeWidth, (float)snakeHeight};
                if (CheckCollisionRecs(foodRect, segmentRect)) {
                    validPosition = false;
                    break;
                }
            }
        }
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
        for (int i = 0; i < body.size(); i++) {
            float drawWidth = width * 1.5f;
            float drawHeight = height * 1.5f;
            float offsetX = (drawWidth - width) / 2;
            float offsetY = (drawHeight - height) / 2;
            int rectX = body[i].x - offsetX;
            int rectY = body[i].y - offsetY;
            int rectW = drawWidth;
            int rectH = drawHeight;
            if (i == 0) {
                // Head: filled DARKER TEAL, outlined BLACK
                DrawRectangle(rectX, rectY, rectW, rectH, (Color){0, 105, 92, 255});
                DrawRectangleLines(rectX, rectY, rectW, rectH, BLACK);
                float eyeRadius = drawWidth * 0.12f;
                float eyeX = body[i].x - offsetX + drawWidth * 0.75f;
                float eyeY = body[i].y - offsetY + drawHeight * 0.35f;
                DrawCircle(eyeX, eyeY, eyeRadius, BLACK);
                DrawCircle(eyeX, eyeY, eyeRadius * 0.5f, WHITE);
            } else {
                // Body: filled SOFTER TEAL, outlined BLACK
                DrawRectangle(rectX, rectY, rectW, rectH, (Color){77, 182, 172, 255});
                DrawRectangleLines(rectX, rectY, rectW, rectH, BLACK);
            }
        }
    }

    void update() {

        if (IsKeyPressed(KEY_A)) { speedX = -4; speedY = 0; }
        if (IsKeyPressed(KEY_D)) { speedX = 4; speedY = 0; }
        if (IsKeyPressed(KEY_W)) { speedX = 0; speedY = -4; }
        if (IsKeyPressed(KEY_S)) { speedX = 0; speedY = 4; }


        for (int i = body.size() - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }


        body[0].x += speedX;
        body[0].y += speedY;


        if (body[0].x >= screenWidth) body[0].x = 0;
        else if (body[0].x < 0) body[0].x = screenWidth - width;

        if (body[0].y >= screenHeight) body[0].y = 0;
        else if (body[0].y < 0) body[0].y = screenHeight - height;
    }

    void grow() {
        Vector2 tail = body.back();
        body.push_back(tail); 
    }
};
Snake snake(screenWidth/2,screenHeight/2,20,20,7,7);
Food food;
int main(){
    InitWindow(screenWidth, screenHeight, "Basic Raylib Window");
    SetTargetFPS(60); 

    int score = 0; 
    bool gameStarted = false;
    while (WindowShouldClose() == false) {
        BeginDrawing();
        if (!gameStarted) {
            // Draw teal background and pattern
            ClearBackground((Color){0, 121, 107, 255});
            int patternCount = 40;
            for (int i = 0; i < patternCount; i++) {
                int size = GetRandomValue(10, 20);
                int posX = GetRandomValue(0, screenWidth - size);
                int posY = GetRandomValue(0, screenHeight - size);
                DrawRectangle(posX, posY, size, size, (Color){0, 150, 136, 30});
            }
            // Draw "Press ENTER to Start" message centered with shadow
            const char* startMsg = "Press ENTER to Start";
            int fontSize = 48;
            int textWidth = MeasureText(startMsg, fontSize);
            int textX = (screenWidth - textWidth) / 2;
            int textY = screenHeight / 2 - fontSize;
            int shadowOffset = 3;
            DrawText(startMsg, textX + shadowOffset, textY + shadowOffset, fontSize, (Color){0, 0, 0, 120});
            DrawText(startMsg, textX, textY, fontSize, WHITE);
            // Start on ENTER
            if (IsKeyPressed(KEY_ENTER)) {
                gameStarted = true;
            }
        } else {
            // Main gameplay logic
            ClearBackground((Color){0, 121, 107, 255});
            int patternCount = 40;
            for (int i = 0; i < patternCount; i++) {
                int size = GetRandomValue(10, 20);
                int posX = GetRandomValue(0, screenWidth - size);
                int posY = GetRandomValue(0, screenHeight - size);
                DrawRectangle(posX, posY, size, size, (Color){0, 150, 136, 30});
            }
            const int fontSize = 36;
            const char* scoreText = TextFormat("Score: %d", score);
            int shadowOffset = 2;
            DrawText(scoreText, 20 + shadowOffset, 10 + shadowOffset, fontSize, (Color){0, 150, 136, 180});
            DrawText(scoreText, 20, 10, fontSize, (Color){0, 77, 64, 255});
            snake.draw();
            snake.update();
            food.draw();
            if (CheckCollisionRecs(
                Rectangle{snake.body[0].x, snake.body[0].y, (float)snake.width, (float)snake.height},
                Rectangle{(float)food.x, (float)food.y, (float)food.width, (float)food.height}
            )) 
            {
                food.update(snake.body, snake.width, snake.height);
                snake.grow();
                score += 1;
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}