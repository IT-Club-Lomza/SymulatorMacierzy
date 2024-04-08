#include "headers.h"

//      this is the matrix itself
typedef struct Table{
    Vector2 position;
    int value;
} Table;

//      thats the box you drag around with your mouse
typedef struct DragBox{
    DragData dragData;
} DragBox;

//      those are the boxes that show up once you drag something with your mouse, they perform calculations when dropped on
typedef struct DragSlot{
    Vector2 position;
    Rectangle space;
    Color color;
    int operant;
    bool isVisible;
} DragSlot;

typedef struct Wrapper{
    Table **table;
    DragBox *dragBox;
    DragSlot **dragSlot;
} Wrapper;


static bool signSwapped = false;
static int tableSize;


static Wrapper wrapper;
static Mouse mouse = {0};


void initMatrix(int size){
    tableSize = size;
    mouse.mouseDraggs = false;
    mouse.mouseDrops = false;

    //      sets the memory for the structures
    wrapper.table = MemAlloc(sizeof(Table *)*tableSize);
    for (int i = 0; i < tableSize; i++){
        wrapper.table[i] = MemAlloc(sizeof(Table)*tableSize);
    }

    wrapper.dragBox = MemAlloc(sizeof(DragBox)*tableSize);

    wrapper.dragSlot = MemAlloc(sizeof(DragSlot *)*tableSize);
    for (int i = 0; i < tableSize; i++){
        wrapper.dragSlot[i] = MemAlloc(sizeof(DragSlot)*tableSize);
    }
    

    //      sets parametrs for the numbers in the matrix
    for (int i = 0; i < tableSize; i++){
        for (int j = 0; j < tableSize; j++){
            wrapper.table[i][j].position = (Vector2){200+30*i, 200+30*j};
            wrapper.table[i][j].value = GetRandomValue(1, 9);
        }
    }

    //      sets parametrs for dragboxes
    for (int i = 0; i < tableSize; i++){
        wrapper.dragBox[i].dragData.position = (Vector2){wrapper.table[0][i].position.x - 60, wrapper.table[0][i].position.y};
        wrapper.dragBox[i].dragData.defPosition = wrapper.dragBox[i].dragData.position;
        wrapper.dragBox[i].dragData.dragged = false;
        wrapper.dragBox[i].dragData.space = (Rectangle){wrapper.dragBox[i].dragData.position.x, wrapper.dragBox[i].dragData.position.y, 20, 20};
    }
    
    //      sets parametrs for dragslots
    for (int i = 0; i < tableSize; i++){
        wrapper.dragSlot[i][0].operant = 0;
        wrapper.dragSlot[i][0].color = BLUE;
        wrapper.dragSlot[i][0].position = (Vector2){wrapper.dragBox[i].dragData.position.x - 60, wrapper.dragBox[i].dragData.position.y};
        wrapper.dragSlot[i][0].space = (Rectangle){wrapper.dragSlot[i][0].position.x, wrapper.dragSlot[i][0].position.y, 20, 20};
    
        wrapper.dragSlot[i][1].operant = 1;
        wrapper.dragSlot[i][1].color = RED;
        wrapper.dragSlot[i][1].position = (Vector2){wrapper.dragBox[i].dragData.position.x - 30, wrapper.dragBox[i].dragData.position.y};
        wrapper.dragSlot[i][1].space = (Rectangle){wrapper.dragSlot[i][1].position.x, wrapper.dragSlot[i][1].position.y, 20, 20};

        wrapper.dragSlot[i][2].operant = 2;
        wrapper.dragSlot[i][2].color = YELLOW;
        wrapper.dragSlot[i][2].position = (Vector2){wrapper.table[tableSize-1][i].position.x + 30, wrapper.table[tableSize-1][i].position.y};
        wrapper.dragSlot[i][2].space = (Rectangle){wrapper.dragSlot[i][2].position.x, wrapper.dragSlot[i][2].position.y, 20, 20};
    }
}

void updateMatrixLogic(){
    for (int i = 0; i < tableSize; i++){
        switch (handleDragPosition(&wrapper.dragBox[i].dragData, &mouse.mouseDraggs)){
            //      handles visibility of slots
            case 1:{
                for (int j = 0; j < tableSize; j++){
                    for (int k = 0; k < tableSize; k++){
                        wrapper.dragSlot[j][k].isVisible = true;
                    }
                }
                for (int j = 0; j < 3; j++){
                    wrapper.dragSlot[i][j].isVisible = false;
                }
                break;
            }
            //      handles addition, subtraction and row swapping
            case 2:{
                for (int j = 0; j < tableSize; j++){
                    for (int k = 0; k < 3; k++){
                        if (CheckCollisionPointRec(GetMousePosition(), wrapper.dragSlot[j][k].space) && wrapper.dragSlot[j][k].isVisible){
                            if (wrapper.dragSlot[j][k].operant == 0){
                                for (int l = 0; l < tableSize; l++){
                                    wrapper.table[l][j].value = wrapper.table[l][j].value - wrapper.table[l][i].value;
                                }
                            } else if(wrapper.dragSlot[j][k].operant == 1){
                                for (int l = 0; l < tableSize; l++){
                                    wrapper.table[l][j].value = wrapper.table[l][j].value + wrapper.table[l][i].value;
                                }
                            } else if(wrapper.dragSlot[j][k].operant == 2){
                                for (int l = 0; l < tableSize; l++){
                                    int x = wrapper.table[l][i].value;
                                    wrapper.table[l][i].value = wrapper.table[l][j].value;
                                    wrapper.table[l][j].value = x;
                                }
                                if (signSwapped){
                                    signSwapped = false;
                                } else{
                                    signSwapped = true;
                                }
                            }
                        }
                    }
                }

                for (int j = 0; j < tableSize; j++){
                    wrapper.dragSlot[j][0].isVisible = false;
                }
                break;
            }
        }
    }
}

void drawMatrixFrame(){
    BeginDrawing();
        ClearBackground(WHITE);

        //      renders the table
        for (int i = 0; i < tableSize; i++){
            for (int j = 0; j < tableSize; j++){
                DrawText(TextFormat("%d", wrapper.table[i][j].value), wrapper.table[i][j].position.x, wrapper.table[i][j].position.y, 20, BLACK);
            }
        }

        //      renders hideable slots
        for (int i = 0; i < tableSize; i++){
            if (wrapper.dragSlot[i][0].isVisible){
                DrawRectangleRec(wrapper.dragSlot[i][0].space, wrapper.dragSlot[i][0].color);
                DrawRectangleRec(wrapper.dragSlot[i][1].space, wrapper.dragSlot[i][1].color);
                DrawRectangleRec(wrapper.dragSlot[i][2].space, wrapper.dragSlot[i][2].color);

                DrawText(TextFormat("+"), wrapper.dragSlot[i][1].position.x+5, wrapper.dragSlot[i][1].position.y+1, 20, WHITE);
                DrawText(TextFormat("-"), wrapper.dragSlot[i][0].position.x+6, wrapper.dragSlot[i][0].position.y+1, 20, WHITE);
            }
        }
        
        //      renders draggable boxes
        for (int i = 0; i < tableSize; i++){
            if (!wrapper.dragBox[i].dragData.dragged){
                DrawRectangleRec(wrapper.dragBox[i].dragData.space, BLACK);
            } else{
                DrawRectangleRec(wrapper.dragBox[i].dragData.space, GREEN);
            }
            DrawText(TextFormat("="), wrapper.dragBox[i].dragData.position.x+6, wrapper.dragBox[i].dragData.position.y+1, 20, WHITE);
        }

        //      renders "-" after swapping rows
        if (signSwapped){
            DrawText("-", wrapper.table[0][0].position.x - 30, wrapper.table[0][0].position.y + ((wrapper.table[0][tableSize-1].position.y - wrapper.table[0][0].position.y)/2), 30, BLACK);
        }
        
    EndDrawing();
}

void closeMatrix(){
    for (int i = 0; i < tableSize; i++){
        MemFree(wrapper.table[i]);
        MemFree(wrapper.dragSlot[i]);
    }
    MemFree(wrapper.table);
    MemFree(wrapper.dragSlot);
    MemFree(wrapper.dragBox);
    
}