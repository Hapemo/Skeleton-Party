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
CP_Image playButtonImage = NULL;
CP_Image titleImage = NULL;
CP_Image creditButtonImage = NULL;
CP_Image quitButtonImage = NULL;
BOOL fullScreen = FALSE;

CP_Font myFont;


//BOOL clicked = FALSE;

struct PlayButton {

	float posX;
	float posY;
	float width;
	float height;
}playButton;

struct CreditsButton {

	float posX;
	float posY;
	float width;
	float height;
}creditButton;

struct QuitButton {

	float posX;
	float posY;
	float width;
	float height;
}quitButton;


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
	playButtonImage = CP_Image_Load("./Assets/play.png");
	titleImage = CP_Image_Load("./Assets/skele_party.png");
	creditButtonImage = CP_Image_Load("./Assets/credits.png");
	quitButtonImage = CP_Image_Load("./Assets/quit.png");
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


BOOL CheckCollisionWithBoxImage(float posX, float posY, float widthBox, float heightBox, float posBoxX, float posBoxY)
{
	posBoxX = posBoxX - widthBox / 2;
	posBoxY = posBoxY - heightBox / 2;
	

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
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Settings_Fill(COLOR_BLACK);
		CP_Graphics_DrawRect(menu.posX + menu.width/2, menu.posY + menu.height/2,
			menu.width, menu.height);

		CP_Settings_Fill(COLOR_GREEN);
		playButton.posX = menu.width / 2.0f;
		playButton.posY = menu.height * (3.0f / 7.0f);
		playButton.width = menu.width / 4.0f;
		playButton.height = menu.height / 6.4f;

		creditButton.posX = menu.width / 2.0f;
		creditButton.posY = menu.height * (4.0f / 7.0f) + 25.0f;
		creditButton.width = menu.width / 4.0f;
	    creditButton.height = menu.height / 6.4f;

		quitButton.posX = menu.width / 2.0f;
		quitButton.posY = menu.height * (5.0f / 7.0f) + 50.0f;
		quitButton.width = menu.width / 4.0f;
		quitButton.height = menu.height / 6.4f;

		CP_Image_Draw(playButtonImage, playButton.posX, playButton.posY, playButton.width, playButton.height, 255);
		CP_Image_Draw(creditButtonImage, creditButton.posX , creditButton.posY, creditButton.width, creditButton.height, 255);
		CP_Image_Draw(quitButtonImage, quitButton.posX, quitButton.posY, quitButton.width, quitButton.height, 255);
		CP_Image_Draw(titleImage, creditButton.posX, menu.height / 8.0f + 50.0f , menu.width * 0.75f, menu.height/ 6.0f ,255);
		//CP_Settings_TextSize(6 * (playButton.width / menu.width * 100));

		CP_Settings_Fill(COLOR_WHITE);
		//CP_Font_DrawTextBox("Play", playButton.posX + playButton.width / 6.5f, playButton.posY + playButton.height / 1.5f, playButton.width);
		CP_Settings_RectMode(CP_POSITION_CORNER);
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
		printf("%f", mousePosX);
		//if (CheckCollisionWithBox(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		//{
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		{
			menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_GRAY);
			gameState = PLAYING;
		}
		//}
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, quitButton.width, quitButton.height, quitButton.posX, quitButton.posY))
		{
			gameState = EXIT;
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

		int widthOfDisplay = CP_System_GetDisplayWidth();
		float newWidthOfDisplay = widthOfDisplay / 2.0f;
		int heightOfDisplay = CP_System_GetDisplayHeight();
		CP_System_SetWindowSize((int)newWidthOfDisplay, heightOfDisplay);
	}
}

void TerminateFullscreen()
{
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}
}

void EnableMenu()
{
	menu.enabled = TRUE;
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
				knight.speedbuff = TRUE;
				item.enabled = 0;

			}

			break;
		}
	}
}

void SpeedBuffEffect()
{
	static float originalSpeed = 0;
	if (knight.speedbuff == TRUE)
	{
		/*BOOL hasActivated = TRUE;

		if (hasActivated)
		{
			originalSpeed = knight.speed;
			hasActivated = FALSE;
		}*/



		static float timer;
		float duration = 3.0f;
		if (knight.speed == originalSpeed)
		{
			knight.speed *= 3.0f;

		}


		if (timer < duration)
		{

			timer += CP_System_GetDt();
			printf("Timer: %f\n", timer);
		}
		else
		{
			timer = 0;
			knight.speed = originalSpeed;

			knight.speedbuff = FALSE;

		}

		printf("Speed: %f\n",knight.speed);

	}
	else
	{
		originalSpeed = knight.speed;

	}
}