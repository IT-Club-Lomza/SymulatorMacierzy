#include "raylib.h"


int main (void)
{
	const int screenWidth = 800;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "wizualizator wektora");
//-----------------------------------------------------------------	
	//Prawa kamera 3D
	Camera3D camera3d = { 0 };
	camera3d.position = (Vector3){ 0.0f, 10.0f, 10.0f};
	camera3d.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera3d.up = (Vector3){ 0.0f, 1.0f, 0.0f };  //rotation towards target
	camera3d.fovy = 45.0f; 						//feald of view
	camera3d.projection = CAMERA_PERSPECTIVE;
	
	Vector3 PozycjaZero = { 0.0f, 0.0f, 0.0f };
	
	//Lewa Kamera 2D
	Camera2D camera2d = { 0 };
    camera2d.target = (Vector2){ 0, 0 };
    camera2d.offset = (Vector2){ 0, 0 };
    camera2d.rotation = 0.0f;
    camera2d.zoom = 1.0f;
	
	
	
	//tu wstawie wartości z Vektorów dawida
	Vector3 PozycjaRandom1 = { GetRandomValue(-5, 5), GetRandomValue(-5, 5), GetRandomValue(-5, 5), };
	Vector3 PozycjaRandom2 = { GetRandomValue(-5, 5), GetRandomValue(-5, 5), GetRandomValue(-5, 5), };
	Vector3 PozycjaRandom3 = { GetRandomValue(-5, 5), GetRandomValue(-5, 5), GetRandomValue(-5, 5), };
	
	//SetTargetFPS(60);
	
	RenderTexture screancamera = LoadRenderTexture(screenWidth/2, screenHeight);
	RenderTexture screancamera2 = LoadRenderTexture(screenWidth / 2, screenHeight);
	Rectangle splitScreenRect = { 0.0f, 0.0f, (float)screancamera.texture.width, (float)-screancamera.texture.height };



	//Main game loop
	while (!WindowShouldClose())
	{
	BeginTextureMode(screancamera);
		
		
			ClearBackground(RAYWHITE);
			
			BeginMode3D(camera3d);
				//DrawCube(PozycjaZero, 2.0f, 2.0f, 2.0f, RED);  //wypełnienine kloca
				//DrawCubeWires(PozycjaZero, 2.0f, 2.0f, 2.0f, MAROON); //do okoła
		
				DrawLine3D(PozycjaZero, PozycjaRandom1, RED);    
				DrawLine3D(PozycjaZero, PozycjaRandom2, GREEN); 
				DrawLine3D(PozycjaZero, PozycjaRandom3, BLUE);                                   // Draw a line in 3D world space
				DrawGrid(10, 1.0f);
			
			//EndMode3D();
			
	EndTextureMode();
	BeginTextureMode(screancamera2);
			ClearBackground(LIGHTGRAY);
			BeginMode2D(camera2d);
			DrawFPS(10, 10);
			// komendy dawida dla prawej strony
			EndMode2D();
	EndTextureMode();


		BeginDrawing();
		DrawTextureRec(screancamera2.texture, splitScreenRect, (Vector2){ 0, 0 }, WHITE);
		DrawTextureRec(screancamera.texture, splitScreenRect, (Vector2){ screenWidth/2.0f, 0 }, WHITE);
		EndDrawing();
	}
	UnloadRenderTexture(screancamera);
	UnloadRenderTexture(screancamera2);
	CloseWindow(); //zakończ
	return 0;
}
