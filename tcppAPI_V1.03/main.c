// https://github.com/tokyocplusplus
#include<raylib.h> // raylib/not really raylib (tokyoC EDIT FOR CULLING)
#include<raymath.h>
#define GRAPHICS_API_OPENGL_43
#include<rlgl.h> // implementation of lowest level OpenGL API
#include<stdint.h> // integers (uint32_t, uint16_t, UINT16_MAX
#include<stdio.h> // standard input and output
#define screenTitle "raylib 3d engine test" // screen title
int main()
{

    uint32_t screenWidth = 1280;
    uint32_t screenHeight = 720;
    InitWindow(screenWidth, screenHeight, screenTitle);

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 1.5f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 90.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_CUSTOM;  // Camera mode type

    Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };
    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    Vector3 cubeSize1 = { 2.0f, 2.0f, 2.0f };
    Vector3 cubePosition1 = { 2.0f, 0.0f, 0.0f };  // Set our game to run at 60 frames-per-second
    Vector3 cubeSize2 = { 2.0f, 2.0f, 2.0f };
    Vector3 cubePosition2 = { 0.0f, 2.0f, 0.0f };
    Vector3 cubeSize3 = { 2.0f, 2.0f, 2.0f };
    Vector3 cubePosition3 = { 2.0f, 2.0f, 0.0f };

    //--------------------------------------------------------------------------------------
    DisableCursor();
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // rlFrustum(2.5, 2.5, 2.5, 2.5, 90, 200);
        int camCurrentX = camera.position.x;
        int camCurrentZ = camera.position.z;
        Vector3 camTargetPast = camera.target;
        if (IsKeyPressed(KEY_LEFT_CONTROL)) {
            camera.position.y = 0.5f;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
            camera.target = camTargetPast;
        }
        if (IsKeyReleased(KEY_LEFT_CONTROL)) {
            camera.position.y = 1.5f;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
            camera.target = camTargetPast;
        }
        // rlFrustrum( // x, y, z, etc.., )
        // setup frustrum culling

        if (IsKeyPressed(KEY_RIGHT_SHIFT)) {
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
            camera.target = camTargetPast;
        }
        if (IsKeyPressed(KEY_SPACE)) {
            rlEnableWireMode();
        }
        if (IsKeyReleased(KEY_SPACE)) {
            rlDisableWireMode();
        }
        rlEnableBackfaceCulling();

        UpdateCamera(&camera, CAMERA_FIRST_PERSON);// Move to target (zoom
    // Draw
    //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(camera);
        DrawCubeV(cubePosition, cubeSize, PINK);
        DrawCubeWiresV(cubePosition, cubeSize, WHITE);
        DrawCubeV(cubePosition1, cubeSize1, PURPLE);
        DrawCubeWiresV(cubePosition1, cubeSize1, WHITE);
        DrawCubeV(cubePosition2, cubeSize2, DARKPURPLE);
        DrawCubeWiresV(cubePosition2, cubeSize2, WHITE);
        DrawCubeV(cubePosition3, cubeSize3, MAGENTA);
        DrawCubeWiresV(cubePosition3, cubeSize3, WHITE);
        EndMode3D();

        DrawText("tokyoC", screenWidth / 2 - 25, 20, 20, BLACK);
        DrawText("RESET camera.up WITH RIGHT SHIFT", screenWidth / 2 - 200, 50, 20, BLACK);

        DrawFPS(5, 5);

        EndDrawing();
    //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();

    return 0;
}
