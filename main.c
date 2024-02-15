#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "raylib/include/raylib.h"

#define RADIUS 10

typedef struct Pivot {
    float x;
    float y;
} Pivot;

typedef struct Line {
    Pivot* pivots;
    int pivotCount;
} Line;

Pivot create_pivot(float x, float y ) {
    Pivot pivot = { .x = x, .y = y };
    return pivot;
}

Line create_line(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    Pivot* pivots = malloc(sizeof(Line) * 4);
    pivots[0] = create_pivot(x1, y1);
    pivots[1] = create_pivot(x2, y2);
    pivots[2] = create_pivot(x3, y3);
    pivots[3] = create_pivot(x4, y4);
    Line line = { .pivots = pivots, .pivotCount = 4 };
    return line;
}

void delete_line(Line* line) {
    assert(false && "delete_line is not implemented");
}

void main() {
    Line line = create_line(
            100, 100,
            700, 100,
            700, 500,
            100, 500);

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

            for (int pivotIndex = 0; pivotIndex < line.pivotCount; ++pivotIndex) {
                Pivot pivot = line.pivots[pivotIndex];
                DrawCircle(pivot.x, pivot.y, RADIUS, RED);
            }
        EndDrawing();
    }

    CloseWindow();

    delete_line(&line);
}
