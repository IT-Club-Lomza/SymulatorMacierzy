#ifndef HEADERS
#define HEADERS
#include "raylib.h"
#include "raygui.h"

enum screen{
    screenWidth = 800,
    screenHeight = 450
};


//      implement this into your object to make it draggable
typedef struct DragData{
    Vector2 position;            //  this is elements dynamic position
    Vector2 defPosition;         //  this is the default position of the element
    Rectangle space;             //  this is the elements position comibined with its dimenstions
    bool dragged;                //  true when element is being dragged
} DragData;


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
int handleDragPosition(DragData *dragData, bool *mouseDraggs);


#endif //HEADERS