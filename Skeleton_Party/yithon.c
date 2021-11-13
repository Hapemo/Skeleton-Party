/*---------------------------------------------------------
 * file:	game.c
 * author:	yithon
 * email:	yithon.goh@digipen.edu
*
 * brief:	This file contains functions for enemy.
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
struct MenuButton {

	float posX;
	float posY;
	float width;
	float height;
}menuPauseButton;

CP_Sound backGroundMusic;

void load_audio() {
	backGroundMusic = CP_Sound_LoadMusic("./Assets/newBGLoop"); //still testing
}

void play_audio() {
	CP_Sound_PlayMusic(backGroundMusic);
}
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

//struct enemy bug={ 500, 500, "./Assets/Enemydot.png", 100, 100, 1 };

void init_enemy() {
	bug.enemyPosition = CP_Vector_Set(500, 500);
	//CP_Settings_ImageMode(CP_POSITION_CENTER);
	bug.enemyDesign = CP_Image_Load("./Assets/Enemydot.png");
	bug.width = 100;
	bug.height = 100;
	bug.alive = 1;

}
//check for collision 
/*BOOL check_enemy_collide(float posX, float posY, float widthBox, float heightBox, float posBoxX, float posBoxY)
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
}*/

/*void enemy_dies()
{u
	if (collide) {
		DropStuff(bug.enemyPosition.x, bug.enemyPosition.y);
		bug.alive = 0;
	}
}*/
//enemy touching player, player losing health
void player_touch_enemy() {

	if (bug.alive == 1)
	{
		CP_Image_Draw(bug.enemyDesign, bug.enemyPosition.x, bug.enemyPosition.y, bug.width, bug.height, 255);
		//CP_Graphics_ClearBackground(COLOR_GRAY);

		if (CheckIfBoxesOverlap(bug.enemyPosition.x, bug.enemyPosition.y, bug.width, bug.height, knight.position.x, knight.position.y, knight.width, knight.height))
		{
				Playertakedamage(1);
				bug.alive = 0;
				DropStuff(bug.enemyPosition.x, bug.enemyPosition.y);
		}
	}
	
}



//Pause state
void DrawPauseCanvas()
{
	CP_Font_Set(myFont);
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	if (gameState == PAUSED)
	{
		/*CP_Settings_Fill(COLOR_GRAY);
		CP_Graphics_DrawRect(pause.posX, pause.posY, pause.width, pause.height);*/

		CP_Settings_Fill(COLOR_GRAY);
		continueButton.posX = width / 8 * 3;
		continueButton.posY = height / 8 * 5;
		continueButton.width = width / 6;
		continueButton.height = height /6;

		menuPauseButton.posX = continueButton.posX;
		menuPauseButton.posY = continueButton.posY + continueButton.height + 10.f;
		menuPauseButton.width = width / 6;
		menuPauseButton.height = height / 6;

		//return to Game
		CP_Graphics_DrawRect(continueButton.posX, continueButton.posY, continueButton.width, continueButton.height);
		CP_Settings_TextSize(3 * (continueButton.width / width * 100));
		CP_Settings_Fill(COLOR_WHITE);
		CP_Font_DrawTextBox("Continue", continueButton.posX + continueButton.width / 6.5f, continueButton.posY + continueButton.height / 1.5f, continueButton.width);

		CP_Settings_Fill(COLOR_GRAY);
		//return to Menu
		CP_Graphics_DrawRect(menuPauseButton.posX, menuPauseButton.posY, menuPauseButton.width, menuPauseButton.height);
		CP_Settings_TextSize(3 * (menuPauseButton.width / width * 100));
		CP_Settings_Fill(COLOR_WHITE);
		CP_Font_DrawTextBox("MENU", menuPauseButton.posX + menuPauseButton.width / 6.5f, menuPauseButton.posY + menuPauseButton.height / 1.5f, menuPauseButton.width );
	}
}

void PauseButtonClicked()
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		if (CheckCollisionWithBox(mousePosX, mousePosY, continueButton.width, continueButton.height, continueButton.posX, continueButton.posY))
		{

			pause.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_GRAY);
			gameState = PLAYING;
		}

		if (CheckCollisionWithBox(mousePosX, mousePosY, menuPauseButton.width, menuPauseButton.height, menuPauseButton.posX, menuPauseButton.posY))
		{
			pause.enabled = TRUE;
			CP_Graphics_ClearBackground(COLOR_GRAY);
			gameState = MAIN_MENU;
		}
	}
}

//enemy collision with player attack
/*void enemy_damage() {

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
	
}*/




