#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "raylib/include/raylib.h"

#define RADIUS 10

typedef struct {
    float x;
    float y;
} Pivot;

typedef struct {
    Pivot* pivots;
    int pivotCount;
} Line;

float calculate_line(float x, float a, float b) {
    return a * x + b;
}

float distance(float x0, float y0, float x1, float y1) {
    float x = pow(x0 - x1, 2);
    float y = pow(y0 - y1, 2);
    return sqrt(x + y);
}

bool is_point_inside_pivot(float x, float y, float x0, float y0, float radius) {
    return distance(x, y, x0, y0) < radius;
}

Line create_line(Pivot start, Pivot stop, int steps) {
    int total_length = 2 + steps;
    float step = (stop.x - start.x) / steps;
    float a = (stop.y - start.y) / (stop.x - start.x);
    float b = start.y - a * start.x;
    Pivot* pivots = malloc(sizeof(Pivot) * total_length);
    pivots[0] = start;
    for (int pivotIndex = 1; pivotIndex < total_length - 1; ++pivotIndex) {
        float x = start.x + step * pivotIndex;
        float y = calculate_line(x, a, b);
        Pivot pivot = { .x = x, .y = y };
        pivots[pivotIndex] = pivot;
    }
    pivots[total_length - 1] = stop;
    Line line = { .pivots = pivots, .pivotCount = total_length };
    return line;
}

Line allocate_line(int length) {
    Pivot* pivots = malloc(sizeof(Pivot) * length);
    Line line = { .pivots = pivots, .pivotCount = length };
    return line;
}

void delete_line(Line line) {
    free(line.pivots);
}

Line create_spline(Pivot start, Pivot stop, Pivot middle, int steps) {
    Line line = allocate_line(steps);
    return line;
}

void main() {
    Pivot start = { .x = 100, .y = 100 };
    Pivot stop = { .x = 500, .y = 100 };
    Line line = create_line(start, stop, 10);

    Pivot middle = { .x = 300, .y = 300 };
    Line spline = create_spline(start, stop, middle, 10); 

    InitWindow(800, 600, "Hello, raylib");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(DARKGRAY);

            for (int pivotIndex = 0; pivotIndex < line.pivotCount - 1; ++pivotIndex) {
                Pivot currentPivot = line.pivots[pivotIndex];
                Pivot nextPivot = line.pivots[pivotIndex  + 1];
                DrawLine(
                    currentPivot.x, currentPivot.y,
                    nextPivot.x, nextPivot.y,
                    BLACK
                );
            }

            for (int pivotIndex = 0; pivotIndex < line.pivotCount - 1; ++ pivotIndex) {
                Pivot currentPivot = spline.pivots[pivotIndex];
                Pivot nextPivot = spline.pivots[pivotIndex + 1];
                DrawLine(
                    currentPivot.x, currentPivot.y,
                    nextPivot.x, nextPivot.y,
                    BLACK
                );
            }

            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            for (int pivotIndex = 0; pivotIndex < line.pivotCount; ++pivotIndex) {
                Pivot pivot = line.pivots[pivotIndex];
                Color color = BLUE;
                if (is_point_inside_pivot(mouseX, mouseY, pivot.x, pivot.y, RADIUS)) {
                    color = RED;
                    if (IsMouseButtonDown(0)) {
                        pivot.x = mouseX;
                        pivot.y = mouseY;
                        line.pivots[pivotIndex] = pivot;
                    }
                }
                DrawCircle(pivot.x, pivot.y, RADIUS, color);
            }

            for (int pivotIndex = 0; pivotIndex < spline.pivotCount; ++pivotIndex) {
                Pivot pivot = spline.pivots[pivotIndex];
                Color color = BLUE;
                if (is_point_inside_pivot(mouseX, mouseY, pivot.x, pivot.y, RADIUS)) {
                    color = RED;
                    if (IsMouseButtonDown(0)) {
                        pivot.x = mouseX;
                        pivot.y = mouseY;
                        line.pivots[pivotIndex] = pivot;
                    }
                }
                DrawCircle(pivot.x, pivot.y, RADIUS, color);
            }

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

    delete_line(line);
}
