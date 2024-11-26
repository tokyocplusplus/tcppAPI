#include "raylib.h"

int main() {
    // Initialize the window
    InitWindow(800, 600, "raylib Shaders Example");

    // Load the shader
    Shader shader = LoadShader(NULL, "simple.fs");

    // Get the location of the "time" uniform
    int timeLoc = GetShaderLocation(shader, "time");

    float time = 0.0f;

    while (!WindowShouldClose()) {
        // Update the time value
        time += GetFrameTime();
        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Use the shader
        BeginShaderMode(shader);
        DrawRectangle(200, 150, 400, 300, WHITE); // Shader modifies this
        EndShaderMode();

        EndDrawing();
    }

    // Cleanup
    UnloadShader(shader);
    CloseWindow();

    return 0;
}