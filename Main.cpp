#include "raylib.h"
#include "Character.h"
#include "rcamera.h"
#include <iostream>
using namespace std;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------




int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 640;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

    // Define the camera to look into our 3d world (position, target, up vector)
    Character Arda = Character();
    Camera camera = { 0 };
    camera.position = { 0.0f, 2.0f, 4.0f };    // Camera position
    camera.target = { 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second

    float initialYPosition = 2.0f; // Store the initial Y position of the camera
    float jumpHeight = 1.0f; // Adjust the jump height as needed
    float jumpSpeed = 0.5f; // Adjust the jump speed as needed
    bool jumping = false; // Store the jumping state of the camera

    Vector3 wall1Position = { -8.0f, 2.5f, 0.0f };
    Vector3 wall1Size = { 1.0f, 5.0f, 16.0f };
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);  // Update camera in first person mode
        
        if (IsKeyDown(KEY_SPACE) && !(jumping))
        {
            jumping = true;
        }
        if (jumping)
        {
            camera.position.y += jumpSpeed;
            if (camera.position.y >= initialYPosition + jumpHeight)
            {
                jumpSpeed -= 0.01f;
                cout << jumpSpeed << endl;
            }
            if (jumpSpeed < 0 && camera.position.y <= initialYPosition)
            {
                jumping = false;
                camera.position.y = initialYPosition; // Reset the camera's Y position
                jumpSpeed = 0.2f; // Reset jump speed
            }
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawPlane({ 0.0f, 0.0f, 0.0f }, { 16.0f, 16.0f }, LIGHTGRAY); // Draw ground
        DrawCube(wall1Position, wall1Size.x, wall1Size.y, wall1Size.z, BLUE);     // Draw a blue wall

        Ray ray = GetMouseRay(GetMousePosition(), camera);
        cout << "Ray: " << ray.position.x << " " << ray.position.y << " " << ray.position.z << endl;
        cout << "Wall: " << wall1Position.x << " " << wall1Position.y << " " << wall1Position.z << endl;
        cout << "Target: " << camera.target.x << " " << camera.target.y << " " << camera.target.z << endl;

        bool isCollide = (ray.position.x >= wall1Position.x - wall1Size.x / 2 && ray.position.x <= wall1Position.x + wall1Size.x / 2) &&
			(ray.position.y >= wall1Position.y - wall1Size.y / 2 && ray.position.y <= wall1Position.y + wall1Size.y / 2) &&
			(ray.position.z >= wall1Position.z - wall1Size.z / 2 && ray.position.z <= wall1Position.z + wall1Size.z / 2);
        if (isCollide)
        {
            camera.position = camera.target; // Reset camera position to target position
        }



        EndMode3D();

        // Draw info boxes
        DrawRectangle(5, 5, 330, 100, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(5, 5, 330, 100, BLUE);
        DrawText("Camera controls:", 15, 15, 10, BLACK);
        DrawText("- Move keys: W, A, S, D, Space, Left-Ctrl", 15, 30, 10, BLACK);
        DrawText("- Look around: arrow keys or mouse", 15, 45, 10, BLACK);
        DrawText("- Camera projection key: P", 15, 60, 10, BLACK);
        DrawRectangle(600, 5, 195, 120, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(600, 5, 195, 120, BLUE);
        DrawText("Camera status:", 610, 15, 10, BLACK);
        DrawText(TextFormat("- Mode: FIRST_PERSON"), 610, 30, 10, BLACK);
        DrawText(TextFormat("- Projection: %s", (camera.projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" : (camera.projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"), 610, 45, 10, BLACK);
        DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, BLACK);
        DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z), 610, 75, 10, BLACK);
        DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z), 610, 90, 10, BLACK);
        DrawText(TextFormat("- Jump: (%d)", jumping), 610, 110, 10, BLACK);


        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
