#define RAYGUI_IMPLEMENTATION
#include "headers.h"

int matrixLoop(int size){
    initMatrix(size);
    while (!WindowShouldClose()){
        updateMatrixLogic();
        drawMatrixFrame();
    }
    closeMatrix();
    return 0;
}

int matrixMenu(){
    int size = 0;
    bool edit = false;
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(WHITE);
            if (GuiDropdownBox((Rectangle){400, 50, 80, 45}, ";3x3;4x4;5x5", &size, edit)) edit = !edit;
            switch (size){
                case 1:{
                    size += 2;
                    matrixLoop(size);
                    return 0;
                }
                case 2:{
                    size += 2;
                    matrixLoop(size);
                    return 0;
                }
                case 3:{
                    size += 2;
                    matrixLoop(size);
                    return 0;
                }
                case 4:{
                    size += 2;
                    matrixLoop(size);
                    return 0;
                }
            }
        EndDrawing();
    }
    return 0;
}

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
            while (!WindowShouldClose()){
                matrixMenu();
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