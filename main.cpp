#include "raylib.h"
#include <iostream>

using namespace std;

struct Ball {
    float x, y;
    float speedx, speedy;
    float radius;

    void Draw() {
        DrawCircle(x,y,radius, WHITE);
    }
};

struct Paddle {
    float x, y;
    float speed;
    float width, height;

    Rectangle GetRect() {
        return Rectangle{x - width / 2, y - height / 2, 10, 100};
    }

    void Draw() {
        DrawRectangleRec(GetRect(), WHITE);
    }
};

int main() {

    InitWindow(800, 600, "Pong");
    SetTargetFPS(60);
    Ball ball;
    ball.x = GetScreenWidth() / 2.0f;
    ball.y = GetScreenHeight() / 2.0f;
    ball.radius =5;
    ball.speedx =300;
    ball.speedy = 300;

    Paddle leftPaddle;
    leftPaddle.x = 50;
    leftPaddle.y = GetScreenHeight() / 2;
    leftPaddle.width = 10;
    leftPaddle.height = 100;
    leftPaddle.speed = 500;

    Paddle rightPaddle;
    rightPaddle.x = GetScreenWidth()-50;
    rightPaddle.y = GetScreenHeight() / 2;
    rightPaddle.width = 10;
    rightPaddle.height = 100;
    rightPaddle.speed = 500;

    const char* winText = nullptr;

    while (!WindowShouldClose()) {

        ball.x += ball.speedx *GetFrameTime();
        ball.y += ball.speedy *GetFrameTime();

        if (ball.y < 0) {
            ball.y = 0;
            ball.speedy *= -1;
        }
        if (ball.y > GetScreenHeight()) {
            ball.y = GetScreenHeight();
            ball.speedy *= -1;
        }

        if (IsKeyDown(KEY_W)) {
            leftPaddle.y -= leftPaddle.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_S)) {
            leftPaddle.y += leftPaddle.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_UP)) {
            rightPaddle.y -= rightPaddle.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_DOWN)) {
            rightPaddle.y += rightPaddle.speed * GetFrameTime();
        }

        if (CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,rightPaddle.GetRect())) {
            if (ball.speedx > 0) {
                ball.speedx *= -1.1f;
            }
        }
        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, leftPaddle.GetRect())) {
            if (ball.speedx < 0) {
                ball.speedx *= -1.1f;
            }
        }

        if (ball.x < 0) {
            winText = "Right win!";
        }
        if (ball.x > GetScreenWidth()) {
            winText = "Left win!";
        }
        if (winText && IsKeyPressed(KEY_SPACE)) {
            ball.x = GetScreenWidth() / 2;
            ball.y = GetScreenHeight() / 2;
            ball.speedx = 300;
            ball.speedy = 300;
            winText = nullptr;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        ball.Draw();
        leftPaddle.Draw();
        rightPaddle.Draw();

        if (winText) {
            DrawText(winText, 250, GetScreenHeight() / 2 - 30, 60, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}