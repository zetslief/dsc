#include "stdio.h"
#include "raylib/include/raylib.h"

void main() {
    InitWindow(800, 600, "Hello, raylib");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(DARKGRAY);
            int width = GetScreenWidth();
            int height = GetScreenHeight();
            int textHeight = 20;
            const char* text = "Hello, Raylib!";
            int textWidth = MeasureText(text, textHeight);
            int x = width / 2 - textWidth / 2;
            int y = height / 2 - textHeight / 2;
            DrawText(text, x, y, textHeight, BLACK);
        EndDrawing();
    }

    CloseWindow();
}
