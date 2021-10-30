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
 * Copyright � 2020 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include <stdio.h>
#include "cprocessing.h"
#include "game.h"


#define COLOR_GRAY CP_Color_Create(127, 127, 127, 255)
#define COLOR_GREEN CP_Color_Create(0, 255, 0, 255)
#define COLOR_BLUE CP_Color_Create(0, 0, 255, 255)
#define COLOR_WHITE CP_Color_Create(255, 255, 255, 255)
#define COLOR_RED CP_Color_Create(255, 0, 0, 255)
#define COLOR_BLACK CP_Color_Create(255, 255, 255, 255)

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
	if (fullScreen == TRUE)
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

