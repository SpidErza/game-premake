/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#define NUM_FRAMES 3

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 450;
Sound fxButton = LoadSound("resources/buttonfx.wav");   // Load button sound
Texture2D button = LoadTexture("resources/button.png"); // Load button texture


//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

float frameHeight = (float)button.height / NUM_FRAMES;
Rectangle sourceRec = { 0, 0, (float)button.width, frameHeight };
// Define button bounds on screen
Rectangle btnBounds = { screenWidth / 2.0f - button.width / 2.0f, screenHeight / 2.0f - button.height / NUM_FRAMES / 2.0f, (float)button.width, frameHeight };

int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
bool btnAction = false;         // Button action should be activated

Vector2 mousePoint = { 0.0f, 0.0f };

static int framesCounter = 0;
static int finishScreen = 0;

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
	// Update
		//----------------------------------------------------------------------------------
	mousePoint = GetMousePosition();
	btnAction = false;

	// Check button state
	if (CheckCollisionPointRec(mousePoint, btnBounds))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
		else btnState = 1;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
	}
	else btnState = 0;

	if (btnAction)
	{
		PlaySound(fxButton);

		// TODO: Any desired action
	}

	// Calculate button frame rectangle to draw depending on button state
	sourceRec.y = btnState * frameHeight;
	//----------------------------------------------------------------------------------

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };
	DrawTextureRec(button, sourceRec, (Vector2){ btnBounds.x, btnBounds.y }, WHITE); // Draw button frame
    DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}