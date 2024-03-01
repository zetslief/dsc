#include "stdio.h"
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

void delete_line(Line line) {
    free(line.pivots);
}

Line create_spline(Pivot start, Pivot stop, Pivot middle, int steps) {
    Line first = create_line(start, middle, steps / 2);
    Line second = create_line(middle, stop, steps / 2);
    int length = first.pivotCount + second.pivotCount - 1;
    Pivot* output = malloc(sizeof(Pivot) * length);
    memcpy(output, first.pivots, sizeof(Pivot) * first.pivotCount);
    memcpy(
        output + first.pivotCount,
        second.pivots + 1,
        sizeof(Pivot) * (second.pivotCount - 1)
    );
    delete_line(first);
    delete_line(second);
    Line result = { .pivots = output, .pivotCount = length };
    return result;
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

            for (int pivotIndex = 0; pivotIndex < line.pivotCount; ++pivotIndex) {
                Pivot pivot = line.pivots[pivotIndex];
                DrawCircle(pivot.x, pivot.y, RADIUS, RED);
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
