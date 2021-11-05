/*---------------------------------------------------------
 * file:	game.c
 * author:	
 * email:	
*
 * brief:	
*
 * documentation link:
 * https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
*
 * Copyright © 2020 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include <stdio.h>
#include "cprocessing.h"
#include "game.h"
#include <stdlib.h>

#define COLOR_GRAY CP_Color_Create(127, 127, 127, 255)
#define COLOR_GREEN CP_Color_Create(0, 255, 0, 255)
#define COLOR_BLUE CP_Color_Create(0, 0, 255, 255)
#define COLOR_WHITE CP_Color_Create(255, 255, 255, 255)
#define COLOR_RED CP_Color_Create(255, 0, 0, 255)
#define COLOR_BLACK CP_Color_Create(0, 0, 0, 255)

CP_Image gameBackground = NULL;


BOOL fullScreen = FALSE;

CP_Font myFont;


//BOOL clicked = FALSE;

struct PlayButton {

	float posX;
	float posY;
	float width;
	float height;
}playButton;

struct Menu {
	
	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}menu;

struct MenuButton {

	float posX;
	float posY;
	float width;
	float height;
}menuButton;

struct HealthBar {
	float maxHealth;
	float currentHealth;


}healthBar;


void InitializeVariables()
{
	item.height = 50;
	item.width = 50;
	item.enabled = 0;
	healthBar.maxHealth = 5.0f;
	healthBar.currentHealth = 5.0f;
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	fullScreen = TRUE;
	menu.enabled = TRUE;
	menu.width = width;
	menu.height = height;
}

void Damage(float damage)
{
	if (healthBar.currentHealth > 0)
	{
		healthBar.currentHealth -= damage;
	}
	DrawHP(healthBar.currentHealth, healthBar.maxHealth);
}

void DrawPlayerHealth()
{
	DrawHP(healthBar.currentHealth, healthBar.maxHealth);
}

void DrawHP(float currentHealth, float maxHealth)
{

	CP_Settings_Fill(COLOR_BLACK);
	CP_Graphics_DrawRect(10, 10, (250 / maxHealth) * maxHealth, 25);
	CP_Settings_Fill(COLOR_RED);
	CP_Graphics_DrawRect(10, 10, (250 / maxHealth) * currentHealth, 25);
}


void LoadBackgroundImage()
{
	gameBackground = CP_Image_Load("./Assets/BackgroundTest.png");
}


void LoadFont()
{
	myFont = CP_Font_GetDefault();
}

BOOL CheckIfBoxesOverlap(float posX1, float posY1, float width1, float height1, float posX2, float posY2, float width2, float height2)
{
	posX1 = posX1 - width1 / 2;
	posY1 = posY1 - height1 / 2;
	posX2 = posX2 - width2 / 2;
	posY2 = posY2 - height2 / 2;

	float bottomRightX1 = posX1 + width1;
	float bottomRightY1 = posY1 + height1;
	float bottomRightX2 = posX2 + width2;
	float bottomRightY2 = posY2 + height2;

	if (bottomRightX1 < posX2 || bottomRightX2 < posX1)
	{
		return FALSE;
	}
	else if (bottomRightY1 < posY2 || bottomRightY2 < posY1)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}

}


BOOL CheckCollisionWithBox(float posX, float posY, float widthBox, float heightBox, float posBoxX, float posBoxY)
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

void DrawMenuCanvas()
{
	CP_Font_Set(myFont);
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	menu.width = width;
	menu.height = height;
	if (menu.enabled ==  TRUE)
	{
		CP_Settings_Fill(COLOR_GRAY);
		CP_Graphics_DrawRect(menu.posX, menu.posY,
			menu.width, menu.height);

		CP_Settings_Fill(COLOR_GREEN);
		playButton.posX = menu.width / 8 * 3;
		playButton.posY = menu.height / 8 * 5;
		playButton.width = menu.width / 4;
		playButton.height = menu.height / 4;
		CP_Graphics_DrawRect(playButton.posX, playButton.posY,
			playButton.width, playButton.height);
		CP_Settings_TextSize(6 * (playButton.width / menu.width * 100));

		CP_Settings_Fill(COLOR_WHITE);
		CP_Font_DrawTextBox("Play", playButton.posX + playButton.width / 6.5f, playButton.posY + playButton.height / 1.5f, playButton.width);

	}
}

void DrawMenuButton()
{
	CP_Font_Set(myFont);
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	CP_Settings_Fill(COLOR_GRAY);
	menuButton.posX = width / 8 * 7;
	menuButton.posY = height / 8;

	menuButton.width = width / 16;
	menuButton.height = height / 16;
	CP_Graphics_DrawRect(menuButton.posX, menuButton.posY,
		menuButton.width, menuButton.height);
	CP_Settings_TextSize(3.0f * (menuButton.width / width * 100));

	CP_Settings_Fill(COLOR_WHITE);
	CP_Font_DrawTextBox("To Menu", menuButton.posX + menuButton.width / 7.0f, menuButton.posY + menuButton.height / 1.75f, menuButton.width);

	CP_Graphics_ClearBackground(COLOR_GRAY);
}

void DrawGameCanvas()
{
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(gameBackground, width / 2, height / 2, width, height, 255);
}


void ButtonClicked()
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		if (CheckCollisionWithBox(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		{
			menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_GRAY);
		}

		if (CheckCollisionWithBox(mousePosX, mousePosY, menuButton.width, menuButton.height, menuButton.posX, menuButton.posY))
		{
			menu.enabled = TRUE;
			CP_Graphics_ClearBackground(COLOR_GRAY);
		}
	}
}

void FullscreenKeyPressed()
{
	if (CP_Input_KeyTriggered(KEY_E))
	{
		fullScreen = !fullScreen;
	}
}

void FullscreenMode()
{
	if (fullScreen == FALSE)
	{
		CP_System_Fullscreen();
	}
	else
	{
		CP_System_SetWindowSize(1280, 720);
	}
}

void TerminateFullscreen()
{
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}
}

void DropStuff(float posX, float posY)
{

	item.position.x = posX;
	item.position.y = posY;

	
	//item.id = id;
	int randomChance = rand() % 2;
	item.id = randomChance;
	item.enabled = 1;
}

void DrawItem()
{
	if (item.enabled == 1)
	{
		switch (item.id)
		{
		case 0:
			item.sprite = CP_Image_Load("./Assets/item1.png");
			CP_Image_Draw(item.sprite, item.position.x, item.position.y, item.width, item.height, 255);
			if (CheckIfBoxesOverlap(item.position.x, item.position.y, item.width, item.height, knight.position.x, knight.position.y, knight.width, knight.height))
			{
				PlayerHealed(1);
				item.enabled = 0;
			}
			break;
		case 1:
			item.sprite = CP_Image_Load("./Assets/item2.png");
			CP_Image_Draw(item.sprite, item.position.x, item.position.y, item.width, item.height, 255);
			if (CheckIfBoxesOverlap(item.position.x, item.position.y, item.width, item.height, knight.position.x, knight.position.y, knight.width, knight.height))
			{
				knight.speed = 200;
				item.enabled = 0;

			}

			break;
		}
	}
}