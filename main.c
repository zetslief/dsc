#include "stdio.h"
#include "raylib/include/raylib.h"

#define RADIUS 10

typedef struct Pivot {
    float x;
    float y;
} Pivot;

typedef struct Line {
    Pivot first;
    Pivot second;;
} Line;

Line create_line(float x1, float y1, float x2, float y2) {
    Line line = {
        .first = { .x = x1, .y = y1 },
        .second = { .x = x2, .y = y2 },
    };
    return line;
}

void main() {
    Line line = create_line(100, 100, 700, 500);

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

            DrawLine(
                line.first.x,
                line.first.y,
                line.second.x,
                line.second.y,
                BLACK
            );
            DrawCircle(line.first.x, line.first.y, RADIUS, RED);
            DrawCircle(line.second.x, line.second.y, RADIUS, RED);
        EndDrawing();
    }

    CloseWindow();
}
