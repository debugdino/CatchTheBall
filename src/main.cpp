#include "game.h"
#include<raylib.h>

Color CYAN = {0, 255, 255, 255};


int main() {
    InitWindow(WindowX,WindowY,"Catch The Balls");
    InitWindowCustom();

    while(!WindowShouldClose()) {
        Event();

        Update();

        BeginDrawing();
            ClearBackground(CYAN);
            Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

