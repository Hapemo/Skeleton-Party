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




