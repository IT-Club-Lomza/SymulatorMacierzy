#define RAYGUI_IMPLEMENTATION
#include "headers.h"


int mainMenu(){
    BeginDrawing();
    ClearBackground(WHITE);
        if (GuiButton((Rectangle){100, 200, 100, 100}, "Michals Part")){
            while (!WindowShouldClose()){
                michalsPartLoop();
            }
            return 0;
        }

        if (GuiButton((Rectangle){300, 200, 100, 100}, "Matrix Calculator")){
            initMatrix();
            while (!WindowShouldClose()){
                updateMatrixLogic();
                drawMatrixFrame();
            }
            return 0;
        }
    EndDrawing();
}

int main(){
    InitWindow(screenWidth, screenHeight, "Matrix Calculator");

    SetTargetFPS(60);
    while (!WindowShouldClose()){
        mainMenu();
    }

    CloseWindow();
    return 0;
}