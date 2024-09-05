#include<stdio.h>
#include<stdlib.h>
#include<raylib.h>
#include<raymath.h>
#include<rlgl.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main() {
    SetTargetFPS(60);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib 3D Engine Test");
    
    Camera3D camera = {
        (Vector3) {0.0f, 1.5f, 10.0f},
        (Vector3) { 0.0f, 1.5f, 0.0f },
        (Vector3) {0.0f, 1.0f, 0.0f},
        90.0f,
        CAMERA_PERSPECTIVE,
    };
	Mesh cubeMesh = GenMeshCube(2.0f,2.0f,2.0f);
	Matrix modelMatrix = MatrixIdentity();
	Material defaultMaterial = LoadMaterialDefault();
    defaultMaterial.maps->color = PINK;
    Material pink = LoadMaterialDefault();
    pink.maps->color = RED;
	
    DisableCursor();

    float jumpVelocity = 0.0f;
    const float jumpStrength = 3.8f;
    const float gravity = -0.1f;
    bool isGrounded = true;
    float groundLevel = 1.5f;

    bool isCrouching = false;
    const float crouchHeight = 0.75f;
    const float standHeight = 1.5f;

    float pitch = 0.0f; // Camera pitch
    float yaw = 0.0f;   // Camera yaw
    float mouseSensitivity = 0.1f; // Adjust sensitivity if needed
    Shader shader = LoadShader("shader.glsl", NULL);
    rlEnableBackfaceCulling();
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Input Handling
        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            isCrouching = true; // Activate crouch while key is held
        }
        else {
            isCrouching = false; // Deactivate crouch when key is not held
        }
        
        if (IsKeyPressed(KEY_TAB)) {
            rlEnableWireMode();
        }
        if (IsKeyReleased(KEY_TAB)) {
            rlDisableWireMode();
        }

        // Adjust camera height based on crouching
        if (isCrouching) {
            camera.position.y = crouchHeight;
            groundLevel = crouchHeight; // Adjust ground level for crouching
        }
        else {
            camera.position.y = standHeight;
            groundLevel = standHeight; // Reset ground level for standing
        }

        // Jump Handling
        if (IsKeyPressed(KEY_SPACE) && isGrounded) {
            jumpVelocity = jumpStrength;
            isGrounded = false;
        }

        jumpVelocity += gravity;
        camera.position.y += jumpVelocity;

        if (camera.position.y <= groundLevel) {
            camera.position.y = groundLevel;
            isGrounded = true;
            jumpVelocity = 0.0f;
        }

        // Camera Rotation
        Vector2 mouseDelta = GetMouseDelta();
        yaw += mouseDelta.x * mouseSensitivity;
        pitch -= mouseDelta.y * mouseSensitivity;

        // Clamp pitch
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        // Calculate camera direction
        Vector3 direction;
        direction.x = cosf(DEG2RAD * yaw) * cosf(DEG2RAD * pitch);
        direction.y = sinf(DEG2RAD * pitch);
        direction.z = sinf(DEG2RAD * yaw) * cosf(DEG2RAD * pitch);
        direction = Vector3Normalize(direction);
        camera.target = Vector3Add(camera.position, direction);
        
        // Camera Movement
        Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
        Vector3 right = Vector3Normalize(Vector3CrossProduct(camera.up, forward));
        Vector3 up = Vector3Normalize(Vector3CrossProduct(forward, right));

        Vector3 movement = { 0.0f, 0.0f, 0.0f };
        if (IsKeyDown(KEY_W)) movement = Vector3Add(movement, forward);
        if (IsKeyDown(KEY_S)) movement = Vector3Subtract(movement, forward);
        if (IsKeyDown(KEY_A)) movement = Vector3Add(movement, right); // move left
        if (IsKeyDown(KEY_D)) movement = Vector3Subtract(movement, right); // move right

        // Normalize the movement vector
        if (Vector3Length(movement) > 0) {
            movement = Vector3Normalize(movement);
        }

        // Apply movement to the camera
        camera.position = Vector3Add(camera.position, Vector3Scale(movement, 5.0f * deltaTime));

        // Recalculate camera target
        camera.target = Vector3Add(camera.position, direction);

        // Rendering
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
        BeginShaderMode(shader);
        /* ---------- RENDERING ---------- */
		DrawMesh(cubeMesh, pink, MatrixTranslate(2.0f, 0.0f, 0.0f));
        DrawMesh(cubeMesh, defaultMaterial, modelMatrix);
        DrawCubeWires((Vector3) { 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RAYWHITE);
        DrawCubeWires((Vector3) { 2.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RAYWHITE);
        /* ---------- RENDERING ---------- */
        EndShaderMode();
        EndMode3D();
        DrawText("tokyoC", SCREEN_WIDTH / 2 - 25, 20, 20, RED);
        DrawText("hey man, playing my game actually means so much to me. Thank you.", 925, 700, 10, RED);
        DrawFPS(5, 5);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
