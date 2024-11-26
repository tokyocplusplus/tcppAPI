#include "raylib.h"

int main() {
    // Initialize window and camera
    InitWindow(800, 600, "3D Cube with Shader");
    Camera camera = { 0 };
    camera.position = (Vector3){ 4.0f, 4.0f, 4.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };   // Looking at the origin
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       // Up direction
    camera.fovy = 45.0f;                             // Field of view
    camera.projection = CAMERA_PERSPECTIVE;

    // Load the shader
    Shader shader = LoadShader(NULL, "frag.glsl");

    // Get the uniform location for "time"
    int timeLoc = GetShaderLocation(shader, "time");

    float time = 0.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update time for the shader
        time += GetFrameTime();
        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Apply the shader and draw the cube
        BeginShaderMode(shader);
        DrawCube((Vector3){ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, WHITE);
        DrawCubeWires((Vector3){ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, BLACK);
        EndShaderMode();

        EndMode3D();

        DrawText("3D Cube with Shader Effect", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Cleanup
    UnloadShader(shader);
    CloseWindow();

    return 0;
}