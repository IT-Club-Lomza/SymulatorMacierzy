#ifndef HEADERS
#define HEADERS
#include "raylib.h"
#include "raygui.h"

enum screen{
    screenWidth = 800,
    screenHeight = 450
};


//      Use when working with drag n drop
typedef struct Mouse{
    bool mouseDraggs;
    bool mouseDrops;
} Mouse;


//      Matrix module functions
void initMatrix(int size);
void drawMatrixFrame();
void updateMatrixLogic();
void closeMatrix();


//      MichalsPart functions
int michalsPartLoop(void);


//      Drag n drop functions
int handleDragPosition(Rectangle *space, Vector2 *position, Vector2 defPosition, bool *dragged, bool *mouseDraggs);


#endif //HEADERS