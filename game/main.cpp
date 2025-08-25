#include "raylib.h" //window, drawing, input, audio

int main()
{
    InitWindow(1024, 768, "DCEngine");
    SetTargetFPS(60);

    // Game Loop: runs until ESC is pressed or the window is closed.
    while (!WindowShouldClose())
    {
        BeginDrawing(); // start frame
        ClearBackground(BLACK);
        DrawText("Hello, Dark Cloud clone!", 32, 32, 28, RAYWHITE);
        EndDrawing(); // end frame
    }

    CloseWindow(); // release OS resources
    return 0;
}