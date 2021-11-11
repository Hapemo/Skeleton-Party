/*---------------------------------------------------------
 * file:	game.c
 * author:	yithon
 * email:	yithon.goh@digipen.edu
*
 * brief:	This file contains functions for enemy,
			enemy health and collision.
*
 * documentation link:
 * https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
*
 * Copyright � 2020 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include <stdio.h>
#include "cprocessing.h"
#include "game.h"


#define COLOR_GRAY CP_Color_Create(127, 127, 127, 255)
#define COLOR_GREEN CP_Color_Create(1, 255, 10, 255)
#define COLOR_WHITE CP_Color_Create(255, 255, 255, 255)

CP_Font myFont;
struct Pause {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}pause;

struct Continue {

	float posX;
	float posY;
	float width;
	float height;
}continueButton;

/*I have  made the structs global by adding it to the header file*/
//These variables are for enemyHealth and damage taking, for function 'enemy_taking_dmg' 
//struct enemy
//{
//	CP_Vector enemyPosition;
//	CP_Image enemyDesign;
//	CP_Image enemyDead;
//	float width;
//	float height;
//}bug;

void init_enemy() {
	bug.enemyPosition = CP_Vector_Set(500, 500);
	//CP_Settings_ImageMode(CP_POSITION_CENTER);
	bug.enemyDesign = CP_Image_Load("./Assets/Enemydot.png");
	bug.enemyDead = CP_Image_Load("./Assets/deadenemy.jpg");
	bug.width = 100;
	bug.height = 100;
	bug.alive = 1;

}
//check for collision 
BOOL check_enemy_collide(float posX, float posY, float widthBox, float heightBox, float posBoxX, float posBoxY)
{

	float boundaryX = posBoxX + widthBox;
	float boundaryY = posBoxY + heightBox;
	if ((posX < boundaryX && posX > posBoxX)
		&& (posY < boundaryY && posY > posBoxY))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//draw enemy & possible algo for the enemy future movement 
void enemy_movement() {

	if (bug.alive == 1)
	{
		CP_Image_Draw(bug.enemyDesign, bug.enemyPosition.x, bug.enemyPosition.y, bug.width, bug.height, 255);
		//CP_Graphics_ClearBackground(COLOR_GRAY);


		if (CheckIfBoxesOverlap(bug.enemyPosition.x, bug.enemyPosition.y, bug.width, bug.height, knight.position.x, knight.position.y, knight.width, knight.height))
		{
			
			DropStuff(bug.enemyPosition.x, bug.enemyPosition.y);
			bug.alive = 0;
		}
	}

}

//Pause state
void DrawPauseCanvas()
{
	CP_Font_Set(myFont);
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	pause.width = width;
	pause.height = height;
	if (pause.enabled == TRUE)
	{
		CP_Settings_Fill(COLOR_GRAY);
		CP_Graphics_DrawRect(pause.posX, pause.posY, pause.width, pause.height);

		CP_Settings_Fill(COLOR_GREEN);
		continueButton.posX = pause.width / 8 * 3;
		continueButton.posY = pause.height / 8 * 5;
		continueButton.width = pause.width / 4;
		continueButton.height = pause.height / 4;
		CP_Graphics_DrawRect(continueButton.posX, continueButton.posY,
			continueButton.width, continueButton.height);
		CP_Settings_TextSize(6 * (continueButton.width / pause.width * 100));

		CP_Settings_Fill(COLOR_WHITE);
		CP_Font_DrawTextBox("Continue", continueButton.posX + continueButton.width / 6.5f, continueButton.posY + continueButton.height / 1.5f, continueButton.width);

	}
}

//enemy collision with player attack
void enemy_damage() {

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		if (CheckCollisionWithBox(mousePosX, mousePosY, 100, 100, bug.enemyPosition.x, bug.enemyPosition.y))
		{
			CP_Image_Draw(bug.enemyDead, bug.enemyPosition.x, bug.enemyPosition.y, bug.width, bug.height, 255);
			//CP_Image_Free(enemyDesign);
			CP_Graphics_ClearBackground(COLOR_GRAY);
		}
	}
	
}




