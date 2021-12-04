/*---------------------------------------------------------
 * file:	keith.c
 * author:	Keith Lua
 * email:	weijiekeith.lua@digipen.edu
*
 * brief:	This file contains functions
*
 * documentation link:
 * https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
*
 * Copyright � 2020 DigiPen, All rights reserved.
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

#define BUFF_TIME 3.0f

static float objectiveDisplayTimer = 3.0f;
static float originalSpeed = 0;
CP_Image instructionScreen  = NULL;
CP_Image gameBackground = NULL;
CP_Image playButtonImage = NULL;
CP_Image titleImage = NULL;
CP_Image creditButtonImage = NULL;
CP_Image quitButtonImage = NULL;
CP_Image instructionsButtonImage = NULL;
CP_Image returnImage = NULL;
CP_Image digipenLogo = NULL;
CP_Image level1Image = NULL;
CP_Image level2Image = NULL;
CP_Image level3Image = NULL;
CP_Image level4Image = NULL;
CP_Image level5Image = NULL;
CP_Image buffIndicatorImage = NULL;
CP_Image upgradesButtonImage = NULL;

BOOL fullScreen = FALSE;

CP_Font myFont;

//BOOL clicked = FALSE;

struct Button {
	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
};


struct Button playButton;
struct Button creditButton;
struct Button quitButton;
struct Button instructionsButton;
struct Button returnButton;
struct Button upgradesButton;
struct Button level1;
struct Button level2;
struct Button level3;
struct Button level4;
struct Button level5;
struct Button buffIndicator;


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
	knight.speedbuff = FALSE;
	knight.invulnerability = FALSE;
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
	returnImage = CP_Image_Load("./Assets/return.png");
	instructionsButtonImage = CP_Image_Load("./Assets/Instructions.png");
	digipenLogo = CP_Image_Load("./Assets/DigiPen_WHITE.png");
	level1Image = CP_Image_Load("./Assets/level1.png");
	level2Image = CP_Image_Load("./Assets/level2.png");
	level3Image = CP_Image_Load("./Assets/level3.png");
	level4Image = CP_Image_Load("./Assets/level4.png");
	level5Image = CP_Image_Load("./Assets/level5.png");
	buffIndicatorImage = CP_Image_Load("./Assets/speedBoostSym.png");
	upgradesButtonImage = CP_Image_Load("./Assets/upgradeBtn.png");
}


//Old legacy Damage function for testing
void Damage(float damage)
{
	if (healthBar.currentHealth > 0)
	{
		healthBar.currentHealth -= damage;
	}
	DrawHP(healthBar.currentHealth, healthBar.maxHealth);
}
//Old legacy DrawPlayerHealth function for testing
void DrawPlayerHealth()
{
	DrawHP(healthBar.currentHealth, healthBar.maxHealth);
}


//Old legacy DrawHP function for testing
void DrawHP(float currentHealth, float maxHealth)
{

	CP_Settings_Fill(COLOR_BLACK);
	CP_Graphics_DrawRect(10, 10, (250 / maxHealth) * maxHealth, 25);
	CP_Settings_Fill(COLOR_RED);
	CP_Graphics_DrawRect(10, 10, (250 / maxHealth) * currentHealth, 25);
}


void LoadBackgroundImage(int level)
{
	
	switch (level)
	{
	case LEVEL_1:

		gameBackground = CP_Image_Load("./Assets/bgpic.jpg");
		break;
	case LEVEL_2:
		gameBackground = CP_Image_Load("./Assets/bg.png");
		break;

	case LEVEL_3:
		gameBackground = CP_Image_Load("./Assets/bg2.png");
		break;
	case LEVEL_4:
		gameBackground = CP_Image_Load("./Assets/bgpic.jpg");
		break;
	case LEVEL_5:
		gameBackground = CP_Image_Load("./Assets/bg.png");
		break;

	}
	
}

void LoadFont()
{
	myFont = CP_Font_Load("./Assets/Font/BikerBones.ttf");
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
		play_click();
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

		playButton.posX = menu.width / 2.0f;
		playButton.posY = menu.height * (2.5f / 7.0f);
		playButton.width = menu.width / 3.0f;
		playButton.height = menu.height / 8.0f;

		instructionsButton.posX = menu.width/ 2.0f;
		instructionsButton.posY = menu.height * (3.5f / 7.0f) + 15.0f;
		instructionsButton.width = menu.width / 3.0f;
		instructionsButton.height = menu.height / 8.0f;

		upgradesButton.posX = menu.width / 2.0f;
		upgradesButton.posY = menu.height * (4.5f / 7.0f) + 30.0f;
		upgradesButton.width = menu.width / 3.0f;
		upgradesButton.height = menu.height / 8.0f;

		creditButton.posX = menu.width / 8.0f;
		creditButton.posY = menu.height * (6.5f / 7.0f);
		creditButton.width = menu.width / 6.0f;
		creditButton.height = menu.height / 15.0f;


		quitButton.posX = menu.width / 2.0f;
		quitButton.posY = menu.height * (5.5f / 7.0f) + 45.0f;
		quitButton.width = menu.width / 3.0f;
		quitButton.height = menu.height / 8.0f;



		CP_Image_Draw(playButtonImage, playButton.posX, playButton.posY, playButton.width, playButton.height, 255);
		CP_Image_Draw(upgradesButtonImage, upgradesButton.posX, upgradesButton.posY, upgradesButton.width, upgradesButton.height, 255);
		CP_Image_Draw(creditButtonImage, creditButton.posX , creditButton.posY, creditButton.width, creditButton.height, 255);
		CP_Image_Draw(quitButtonImage, quitButton.posX, quitButton.posY, quitButton.width, quitButton.height, 255);
		CP_Image_Draw(instructionsButtonImage, instructionsButton.posX, instructionsButton.posY, instructionsButton.width, instructionsButton.height, 255);
		CP_Image_Draw(titleImage, menu.width / 2.0f, menu.height *( 0.75f/ 7.0f) + 50.0f , menu.width * 0.75f, menu.height/ 6.0f ,255);
		CP_Settings_RectMode(CP_POSITION_CORNER);
	}
}

void DrawLogoScreen()
{
	static float timer = 5.0f;

	if (timer > 0)
	{
		timer -= CP_System_GetDt();
		float width = (float)CP_System_GetWindowWidth();
		float height = (float)CP_System_GetWindowHeight();
		CP_Settings_Fill(COLOR_BLACK);
	    CP_Graphics_DrawRect(0, 0, width, height);
		CP_Image_Draw(digipenLogo, width / 2, height / 2, width / 1.2f, height / 2, (int)(255 * timer));

	}
	else
	{
		gameState = MAIN_MENU;
	}
}


void DrawMenuButton()
{
	
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


void DrawInstructionsCanvas()
{

	instructionScreen = CP_Image_Load("./Assets/tutScreen.png");
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(instructionScreen, width / 2, height / 2, width, height, 255);

	returnButton.posX = width / 7.5f;
	returnButton.posY = height *(0.925f);
	returnButton.width = width / 5.0f;
	returnButton.height = height / 15.0f;
	CP_Image_Draw(returnImage, returnButton.posX, returnButton.posY, returnButton.width, returnButton.height, 255);

}

void DrawLevelSelectionCanvas()
{
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	menu.width = width;
	menu.height = height;

	CP_Settings_RectMode(CP_POSITION_CENTER);
	static float timer = 3.0f;

	CP_Settings_Fill(COLOR_BLACK);
	
	CP_Graphics_DrawRect(menu.posX + menu.width / 2, menu.posY + menu.height / 2,
		menu.width, menu.height);

	level1.posX = menu.width *(1.0f/ 4.0f);
	level1.posY = menu.height * (0.5f / 6.0f) + 20;
	level1.width = menu.width / 3.0f;
	level1.height = menu.height / 8.0f;

	level2.posX = menu.width * (3.0f / 4.0f);
	level2.posY = menu.height * (0.5f / 6.0f) + 20;
	level2.width = menu.width / 3.0f;
	level2.height = menu.height / 8.0f;

	level3.posX = menu.width * (1.0f / 4.0f);
	level3.posY = menu.height * (1.5f / 6.0f) + 20;
	level3.width = menu.width / 3.0f;
	level3.height = menu.height / 8.0f;

	level4.posX = menu.width * (3.0f / 4.0f);
	level4.posY = menu.height * (1.5f / 6.0f) + 20;
	level4.width = menu.width / 3.0f;
	level4.height = menu.height / 8.0f;

	level5.posX = menu.width * (1.0f / 4.0f);
	level5.posY = menu.height * (2.5f / 6.0f) + 20;
	level5.width = menu.width / 3.0f;
	level5.height = menu.height / 8.0f;


	CP_Image_Draw(level1Image, level1.posX, level1.posY, level1.width, level1.height, 255);
	CP_Image_Draw(level2Image, level2.posX, level2.posY, level2.width, level2.height, 255);
	CP_Image_Draw(level3Image, level3.posX, level3.posY, level3.width, level3.height, 255);
	CP_Image_Draw(level4Image, level4.posX, level4.posY, level4.width, level4.height, 255);
	CP_Image_Draw(level5Image, level5.posX, level5.posY, level5.width, level5.height, 255);

	returnButton.posX = width / 7.5f;
	returnButton.posY = height * (0.925f);
	returnButton.width = width / 5.0f;
	returnButton.height = height / 15.0f;

	CP_Image_Draw(returnImage, returnButton.posX, returnButton.posY, returnButton.width, returnButton.height, 255);
	
	CP_Settings_RectMode(CP_POSITION_CORNER);

}

void DrawBuffIndicator()
{
	if (knight.speedbuff == TRUE)
	{
		float width = (float)CP_System_GetWindowWidth();
		float height = (float)CP_System_GetWindowHeight();

		buffIndicator.posX = width * (1.0f / 25.0f);
		buffIndicator.posY = height * (1.0f / 8);
		buffIndicator.width = width / 20.0f;
		buffIndicator.height = height / 20.0f;
		CP_Image_Draw(buffIndicatorImage, buffIndicator.posX, buffIndicator.posY, buffIndicator.width, buffIndicator.height, 255);
	}
}


void ReturnMainMenuClicked()
{
	float mousePosX = CP_Input_GetMouseX();
	float mousePosY = CP_Input_GetMouseY();
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, returnButton.width, returnButton.height, returnButton.posX, returnButton.posY))
		{
			gameState = MAIN_MENU;
		}
	}
}

void ButtonLevelSelectionClicked()
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, level1.width, level1.height, level1.posX, level1.posY))
		{
			reset_enemy_and_weapon();
			ResetState();
			currentLevel = LEVEL_1;
			gameState = currentLevel;
			preload_spawn_map(currentLevel);
		}
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, level2.width, level2.height, level2.posX, level2.posY))
		{
			reset_enemy_and_weapon();
			ResetState();
			currentLevel = LEVEL_2;
			gameState = currentLevel;
			preload_spawn_map(currentLevel);
		}
	
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, level3.width, level3.height, level3.posX, level3.posY))
		{
			reset_enemy_and_weapon();
			ResetState();
			currentLevel = LEVEL_3;
			gameState = currentLevel;
			preload_spawn_map(currentLevel);
		}
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, level4.width, level4.height, level4.posX, level4.posY))
		{
			reset_enemy_and_weapon();
			ResetState();
			currentLevel = LEVEL_4;
			gameState = currentLevel;
			preload_spawn_map(currentLevel);
		}
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, level5.width, level5.height, level5.posX, level5.posY))
		{
			reset_enemy_and_weapon();
			ResetState();
			currentLevel = LEVEL_5;
			gameState = currentLevel;
			preload_spawn_map(currentLevel);
		}



	}
}


void DrawObjectiveText()
{
	if (objectiveDisplayTimer > 0)
	{
		objectiveDisplayTimer -= CP_System_GetDt();
		CP_Color fade = CP_Color_Create(255, 255, 255, (int)(255 * objectiveDisplayTimer));
		CP_Settings_Fill(fade);

		float width = (float)CP_System_GetWindowWidth();
		float height = (float)CP_System_GetWindowHeight();
		CP_Font_Set(myFont);
		CP_Settings_TextSize(75);
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_BASELINE);

		char levelText[] = "Level 1\n";
		
		int level = 0;
		switch (currentLevel)
		{
		case LEVEL_1:
			level = 1;
			break;
		case LEVEL_2:
			level = 2;
			break;
		case LEVEL_3:
			level = 3;
			break;
		case LEVEL_4:
			level = 4;
			break;
		case LEVEL_5:
			level = 5;
			break;
		default:
			break;
		}
		levelText[6] = (char)(level + '0');


		CP_Font_DrawTextBox(levelText, width /6.5f, height / 10, (float)strlen(levelText) * 75);
		CP_Settings_TextSize(50);
		char objectiveText[] = "Objective:\nSurvive Waves Of Enemy";
		CP_Font_DrawTextBox(objectiveText, -width /2.5f, height / 6, (float)strlen(objectiveText) * 50);
		
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
	}
}


void ButtonClicked()
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
	
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		{
			menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_GRAY);
			MainMenuState = FALSE;
			gameState = LEVEL_SELECTION;
		}
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, quitButton.width, quitButton.height, quitButton.posX, quitButton.posY))
		{
			gameState = EXIT;
		}

		if (CheckCollisionWithBox(mousePosX, mousePosY, menuButton.width, menuButton.height, menuButton.posX, menuButton.posY))
		{
			menu.enabled = TRUE;
			CP_Graphics_ClearBackground(COLOR_GRAY);
		}
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, instructionsButton.width, instructionsButton.height, instructionsButton.posX, instructionsButton.posY))
		{
			gameState = INSTRUCTIONS;
		}
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, creditButton.width, creditButton.height, creditButton.posX, creditButton.posY))
		{
			gameState = CREDIT1;
		}
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, upgradesButton.width, upgradesButton.height, upgradesButton.posX, upgradesButton.posY))
		{
			gameState = UPGRADES;
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
		float newWidthOfDisplay = WIDTH;
		float heightOfDisplay = HEIGHT;
		CP_System_SetWindowSize((int)newWidthOfDisplay, (int)heightOfDisplay);
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


void ResetState()
{
	CurrentCharacterKeith = knightint;
	objectiveDisplayTimer = 3.0f;
	ResetItemPool();
	timer_reset();
	knight.position.x = originalPlayerPositionX;
	knight.position.y = originalPlayerPositionY;
	knight.speed = originalPlayerSpeed;
	knight.transparency = 255;
	knight.invulnerability = FALSE;
	knight.speedbuff = FALSE;

	load_audio(); //load audio
	Player_FullHeal();

}


void WinCondition()
{
	if (*tick == winning_condition)
	{
		if (currentLevel < LEVEL_5)
		{
			currentLevel++;
			ResetState();
		}
		gameState = WIN;
	}
}



void DespawnTimer()
{
	for (int i = 0; i < MAX_DROP; i++)
	{
		if (item_pool[i].enabled == 1)
		{

			

			if (item_pool[i].despawnTimer > 0)
			{
				item_pool[i].despawnTimer -= CP_System_GetDt();
			}
			else
			{
				item_pool[i].enabled = 0;
			}
			
		}
	}



}

void DropStuffs(CP_Vector position) {
	DropStuff(position.x, position.y);
}

// specification for DropStuff
/*!
@brief This function will iterate through the item_pool which
	   contains an array of item structs. When the item in the
	   array is disabled (0), we will set it generate a random
	   number, if the number is within a certain range, we will
	   enable an item, different range corresponds to different
	   items marked by their ids. The range is the represents 
	   the estimated probability of the item drop.

@param word float posX, float posY
@return void
*//*______________________________________________________________*/

void DropStuff(float posX, float posY)
{
	
	for (int i = 0, j = 0; i <= j && j < MAX_DROP; i++)
	{
		if (item_pool[i].enabled == 0)
		{
			int randomChanceSpawnRate = CP_Random_RangeInt(0, 99);
			if (randomChanceSpawnRate >= 0 && randomChanceSpawnRate <= 4) //around 5% chance of spawning a health potion
			{
				item_pool[i].position.x = posX;
				item_pool[i].position.y = posY;
				item_pool[i].width = 45;
				item_pool[i].height = 50;
				item_pool[i].enabled = 1;
				item_pool[i].transparency = 255;
				item_pool[i].despawnTimer = 3.0f;
				item_pool[i].id = 0;
				
			}
			else if (randomChanceSpawnRate >= 5 && randomChanceSpawnRate <= 9) //around 5% chance of spawning a speed potion
			{
				item_pool[i].position.x = posX;
				item_pool[i].position.y = posY;
				item_pool[i].width = 45;
				item_pool[i].height = 50;
				item_pool[i].enabled = 1;
				item_pool[i].transparency = 255;
				item_pool[i].despawnTimer = 3.0f;
				item_pool[i].id = 1;
			}
		    else if(randomChanceSpawnRate >= 10 && randomChanceSpawnRate <= 11) //around 2% chance of spawning gold
			{
				item_pool[i].position.x = posX;
				item_pool[i].position.y = posY;
				item_pool[i].width = 45;
				item_pool[i].height = 50;
				item_pool[i].enabled = 1;
				item_pool[i].transparency = 255;
				item_pool[i].despawnTimer = 10.0f;
				item_pool[i].id = 2;
			}
		}
		else if (item_pool[i].enabled == 1)
		{
			j++;
		}

		
	}
	
}

// specification for DrawItem
/*!
@brief This function iterate through the item_pool which
	   contains an array of item structs to draw an item based
	   their state, if the item struct is enabled (1) we will load
	   and draw the sprite health potion, speed potion, gold based 
	   on their respective ids 0,1 and 2.They wil also be drawn 
	   based on the  vector postion, width, height
	   transparency variables of knight struct set by 
	   DropStuff function.

@param word void
@return void
*//*______________________________________________________________*/

void DrawItem()
{
	
	for (int i = 0; i < MAX_DROP; i++)
	{
		
		if (item_pool[i].enabled == 1)
		{

			switch (item_pool[i].id)
			{
			case 0:
				item_pool[i].sprite = CP_Image_Load("./Assets/healthBoost.png");
				CP_Image_Draw(item_pool[i].sprite, item_pool[i].position.x, item_pool[i].position.y, item_pool[i].width, item_pool[i].height, item_pool[i].transparency);
				if (CheckIfBoxesOverlap(item_pool[i].position.x, item_pool[i].position.y, item_pool[i].width, item_pool[i].height, knight.position.x, knight.position.y, knight.width, knight.height))
				{
					play_healthDrop();
					if (DoubleHeal == TRUE)
					{
	
						Checkoverheal(2);
						item_pool[i].enabled = 0;
					}
					else
					{
						Checkoverheal(1);
						item_pool[i].enabled = 0;
					}

				}
				break;
			case 1:
				item_pool[i].sprite = CP_Image_Load("./Assets/speedBoost.png");
				CP_Image_Draw(item_pool[i].sprite, item_pool[i].position.x, item_pool[i].position.y, item_pool[i].width, item_pool[i].height, item_pool[i].transparency);
				if (CheckIfBoxesOverlap(item_pool[i].position.x, item_pool[i].position.y, item_pool[i].width, item_pool[i].height, knight.position.x, knight.position.y, knight.width, knight.height))
				{
					play_speedDrop();
					knight.speedbuff = TRUE;
					item_pool[i].enabled = 0;

				}

				break;
			case 2:
				item_pool[i].sprite = CP_Image_Load("./Assets/gold.png");
				CP_Image_Draw(item_pool[i].sprite, item_pool[i].position.x, item_pool[i].position.y, item_pool[i].width, item_pool[i].height, item_pool[i].transparency);
				if (CheckIfBoxesOverlap(item_pool[i].position.x, item_pool[i].position.y, item_pool[i].width, item_pool[i].height, knight.position.x, knight.position.y, knight.width, knight.height))
				{
					play_coins();
					Gold++;
					printf("Gold: %d", Gold);
					item_pool[i].enabled = 0;
				}

				break;

			default:
				break;

			}
		}
		
	}
	
	
}

// specification for InvulnerabilityFrame
/*!
@brief This function will set a timer for the invulnerability
	   effect which will tick based on system time till teaches 0
	   then the invulerability variable in knight struct will set
	   to false, timer will be reset, and the alpha value/ 
	   transparency member variable of knight struct
	   will become 255 for opaque and the alpha/transparency 
	   will change between translucent 127 and opaque 255 while 
	   invulnerability is in effect.

@param word void
@return void
*//*______________________________________________________________*/

void InvulnerabilityFrame()
{
	static float InvulnerabilityTimer = 3.0f;

	static float flickerTimer = 0.f;

	if (InvulnerabilityTimer > 0)
	{

		InvulnerabilityTimer -= CP_System_GetDt();
		if (flickerTimer > 0.25f)
		{

			knight.transparency = 255; //The alpha value player is opaque
			flickerTimer = 0.0f; //Reset lerp timer
		}
		else
		{
			flickerTimer += CP_System_GetDt();
			knight.transparency = 127; //The alpha value player is translucent/faded

		}
	}
	else
	{

		knight.invulnerability = FALSE;
		knight.transparency = 255;
		flickerTimer = 0.f;
		InvulnerabilityTimer = 3.0f;
	}
}

// specification for SpeedBuffEffect
/*!
@brief This function will check if the member variable speedbuff
`	   in knight struct is true, if this the case, check if the 
	   current speed of knight struct is the same as the 
	   original player speed if this is the case we multiply 
	   the player speed by two times. We then will decrease the
	   timer by system time till it reaches 0. When timer ends,
	   we set the current player speed to the orignal player speed
	   as well as set the speedbuff to false, when its false
	   the timer will be set toits original timer value 3.

@param word void
@return void
*//*______________________________________________________________*/

void SpeedBuffEffect()
{
	static float timer;
	if (knight.speedbuff == TRUE)
	{
		if (knight.speed == originalPlayerSpeed)
		{
			knight.speed *= 2.0f;

		}

		if (timer > 0)
		{
			timer -= CP_System_GetDt();
		}
		else
		{
			knight.speed = originalPlayerSpeed;

			knight.speedbuff = FALSE;

		}

	}
	else
	{
		timer = BUFF_TIME;
		knight.speed = originalPlayerSpeed;
	}
}

// specification for ResetItemPool
/*!
@brief This function iterates through the item pool struct and
	   sets the member variable enabled to 0. So that it will not
	   be drawn.

@param word void
@return void
*//*______________________________________________________________*/

void ResetItemPool()
{
	for (int i = 0; i < MAX_DROP; i++)
	{
		item_pool[i].enabled = 0;
	}
}

// specification for EnemyCollision
/*!
@brief This function iterates through the enemy_pools as well as
	   the children in the mother_enemy and checks if they are 
	   still alive, if this is the case we detect if they overlap
	   through another function, if this is the player will 
	   take damage and call  Playertakedamage() and the
	   member variable invulnerability of knight struct will be 
	   set to true. Then we call the
	   InvulnerabilityFrame function to set a timer for the 
	   invulnerability state.

@param word void
@return void
*//*______________________________________________________________*/

void EnemyCollision()
{

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (enemy_pool[i].alive == 1)
		{
			if (CheckIfBoxesOverlap(enemy_pool[i].position.x, enemy_pool[i].position.y, enemy_pool[i].size, enemy_pool[i].size, knight.position.x, knight.position.y, knight.width, knight.height) && knight.invulnerability == FALSE)
			{
				Playertakedamage(1);
				knight.invulnerability = TRUE;
			}
		}
	}
	for (int i = 0; i < MAX_MOTHER_ENEMY; i++)
	{
		for (int j = 0; j < MAX_CHILDREN; j++)
		{
			if (mother_enemy_pool[i].alive == 1)
			{
				if (mother_enemy_pool[i].children[j].alive == 1)
				{
					if (CheckIfBoxesOverlap(mother_enemy_pool[i].children[j].position.x, mother_enemy_pool[i].children[j].position.y, mother_enemy_pool[i].children[j].size, mother_enemy_pool[i].children[j].size, knight.position.x, knight.position.y, knight.width, knight.height) && knight.invulnerability == FALSE)
					{
						Playertakedamage(1);
						knight.invulnerability = TRUE;

					}


				}
			}
		}
	}
	if (knight.invulnerability == TRUE)
	{
		InvulnerabilityFrame();
	}
}