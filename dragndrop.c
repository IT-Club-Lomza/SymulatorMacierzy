#include "headers.h"

//      handles position during drag and drop for given element
//          returns 1 when element is being dragged
//          returns 2 when element has been dropped
//      create draggable object by making a stuct with DragData inside
//      initialize Mouse struct for mouseDraggs
int handleDragPosition(DragData *dragData, bool *mouseDraggs){
    dragData->space = (Rectangle){dragData->position.x, dragData->position.y, dragData->space.width, dragData->space.height};
    
    if (!*mouseDraggs && IsMouseButtonDown(0) && CheckCollisionPointRec(GetMousePosition(), dragData->space)){
        dragData->dragged = true;
        *mouseDraggs = true;
    }

    if (dragData->dragged && IsMouseButtonReleased(0)){
        dragData->position = dragData->defPosition;
        dragData->dragged = false;
        *mouseDraggs = false;
        return 2;
    }
        
    if (dragData->dragged){
        dragData->position = GetMousePosition();
        return 1;
    }
}