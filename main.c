#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include "raylib/include/raylib.h"

#define RADIUS 20

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

Line allocate_line(int length) {
    Pivot* pivots = malloc(sizeof(Pivot) * length);
    Line line = { .pivots = pivots, .pivotCount = length };
    return line;
}

void delete_line(Line line) {
    free(line.pivots);
}

float interpolate(float a, float b, float t) {
    return a + (b - a) * t;
}

Line create_spline(Pivot start, Pivot stop, Pivot middle, uint steps) {
    Line line = allocate_line(steps + 1);
    for (uint step = 0; step < steps; ++step) {
        float t = (float)step / steps;
        float firstX = interpolate(start.x, middle.x, t);
        float firstY = interpolate(start.y, middle.y, t);
        float secondX = interpolate(middle.x, stop.x, t); 
        float secondY = interpolate(middle.y, stop.y, t); 
        float x = interpolate(firstX, secondX, t);
        float y = interpolate(firstY, secondY, t);
        line.pivots[step] = (Pivot) { .x = x, .y = y };
    }
    line.pivots[steps] = stop;
    return line;
}

void main() {
    Pivot start = { .x = 100, .y = 100 };
    Pivot stop = { .x = 700, .y = 100 };
    Pivot middle = { .x = 400, .y = 450 };

    const uint numberOfPivots = 3;
    Pivot* movablePivots[] = {&start, &stop, &middle};

    InitWindow(800, 600, "Hello, raylib");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(DARKGRAY);
            Line spline1 = create_spline(start, stop, middle, 30);
            Line spline2 = create_spline(stop, middle, start, 30);
            Line spline3 = create_spline(middle, start, stop, 30);

            for (int pivotIndex = 0; pivotIndex < spline1.pivotCount - 1; ++pivotIndex) {
                Pivot currentPivot = spline1.pivots[pivotIndex];
                Pivot nextPivot = spline1.pivots[pivotIndex  + 1];
                DrawLine(
                    currentPivot.x, currentPivot.y,
                    nextPivot.x, nextPivot.y,
                    GREEN
                );
                if (pivotIndex < spline1.pivotCount - 2) {
                    DrawCircle(nextPivot.x, nextPivot.y, RADIUS / 5, GREEN);
                }
            }

            for (int pivotIndex = 0; pivotIndex < spline2.pivotCount - 1; ++pivotIndex) {
                Pivot currentPivot = spline2.pivots[pivotIndex];
                Pivot nextPivot = spline2.pivots[pivotIndex  + 1];
                DrawLine(
                    currentPivot.x, currentPivot.y,
                    nextPivot.x, nextPivot.y,
                    GREEN
                );
                if (pivotIndex < spline2.pivotCount - 2) {
                    DrawCircle(nextPivot.x, nextPivot.y, RADIUS / 3, GREEN);
                }
            }

            for (int pivotIndex = 0; pivotIndex < spline3.pivotCount - 1; ++pivotIndex) {
                Pivot currentPivot = spline3.pivots[pivotIndex];
                Pivot nextPivot = spline3.pivots[pivotIndex  + 1];
                DrawLine(
                    currentPivot.x, currentPivot.y,
                    nextPivot.x, nextPivot.y,
                    GREEN
                );
                if (pivotIndex < spline3.pivotCount - 2) {
                    DrawCircle(nextPivot.x, nextPivot.y, RADIUS / 3, GREEN);
                }
            }

            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            for (int pivotIndex = 0; pivotIndex < numberOfPivots; ++pivotIndex) {
                Pivot* pivot = movablePivots[pivotIndex];
                Color color = BLUE;
                if (is_point_inside_pivot(mouseX, mouseY, pivot->x, pivot->y, RADIUS)) {
                    color = RED;
                    if (IsMouseButtonDown(0)) {
                        pivot->x = mouseX;
                        pivot->y = mouseY;
                    }
                }
                DrawCircle(pivot->x, pivot->y, RADIUS, color);
            }

            int width = GetScreenWidth();
            int height = GetScreenHeight();
            int textHeight = 20;
            const char* text = "Hello, Raylib!";
            int textWidth = MeasureText(text, textHeight);
            int x = width / 2 - textWidth / 2;
            int y = height / 2 - textHeight / 2;
            DrawText(text, x, y, textHeight, BLACK);
            delete_line(spline1);
            delete_line(spline2);
            delete_line(spline3);
        EndDrawing();
    }

    CloseWindow();
}
