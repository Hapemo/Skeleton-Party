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

CP_Image instructionScreen  = NULL;
CP_Image gameBackground = NULL;
CP_Image playButtonImage = NULL;
CP_Image titleImage = NULL;
CP_Image creditButtonImage = NULL;
CP_Image quitButtonImage = NULL;
CP_Image instructionsButtonImage = NULL;
CP_Image returnImage = NULL;
CP_Image digipenLogo = NULL;

BOOL fullScreen = FALSE;

CP_Font myFont;


//BOOL clicked = FALSE;

struct Button {

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



void ReturnMainMenuClicked();

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
		playButton.posY = menu.height * (2.0f / 6.0f);
		playButton.width = menu.width / 3.0f;
		playButton.height = menu.height / 8.0f;

		instructionsButton.posX = menu.width/ 2.0f;
		instructionsButton.posY = menu.height * (3.0f / 6.0f) + 15.0f;
		instructionsButton.width = menu.width / 3.0f;
		instructionsButton.height = menu.height / 8.0f;

		creditButton.posX = menu.width / 2.0f;
		creditButton.posY = menu.height * (4.0f / 6.0f) + 30.0f;
		creditButton.width = menu.width / 3.0f;
	    creditButton.height = menu.height / 8.0f;

		quitButton.posX = menu.width / 2.0f;
		quitButton.posY = menu.height * (5.0f / 6.0f) + 45.0f;
		quitButton.width = menu.width / 3.0f;
		quitButton.height = menu.height / 8.0f;



		CP_Image_Draw(playButtonImage, playButton.posX, playButton.posY, playButton.width, playButton.height, 255);
		CP_Image_Draw(creditButtonImage, creditButton.posX , creditButton.posY, creditButton.width, creditButton.height, 255);
		CP_Image_Draw(quitButtonImage, quitButton.posX, quitButton.posY, quitButton.width, quitButton.height, 255);
		CP_Image_Draw(instructionsButtonImage, instructionsButton.posX, instructionsButton.posY, instructionsButton.width, instructionsButton.height, 255);
		CP_Image_Draw(titleImage, creditButton.posX, menu.height / 8.0f + 50.0f , menu.width * 0.75f, menu.height/ 6.0f ,255);
		//CP_Settings_TextSize(6 * (playButton.width / menu.width * 100));

		//CP_Settings_Fill(COLOR_WHITE);
		//CP_Font_DrawTextBox("Play", playButton.posX + playButton.width / 6.5f, playButton.posY + playButton.height / 1.5f, playButton.width);
		CP_Settings_RectMode(CP_POSITION_CORNER);
	}
}

void DrawLogoScreen()
{
	static float timer = 3.0f;

	if (timer > 0)
	{
		timer -= CP_System_GetDt();
		float width = (float)CP_System_GetWindowWidth();
		float height = (float)CP_System_GetWindowHeight();
		CP_Settings_Fill(COLOR_BLACK);
		CP_Graphics_DrawRect(0, 0, width, height);


		CP_Image_Draw(digipenLogo, width / 2, height / 2, width / 1.5f, height / 2, (int)(255 * timer));



	}
	else
	{
		gameState = MAIN_MENU;
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


void DrawInstructionsCanvas()
{

	instructionScreen = CP_Image_Load("./Assets/tutScreen.png");
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(instructionScreen, width / 2, height / 2, width, height, 255);

	returnButton.posX = width / 10.0f;
	returnButton.posY = height *(0.925f);
	returnButton.width = width / 7.0f;
	returnButton.height = height / 15.0f;
	CP_Image_Draw(returnImage, returnButton.posX, returnButton.posY, returnButton.width, returnButton.height, 255);

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
			gameState = LEVEL_1;
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
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, instructionsButton.width, instructionsButton.height, instructionsButton.posX, instructionsButton.posY))
		{
			gameState = INSTRUCTIONS;
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

		//int widthOfDisplay = CP_System_GetDisplayWidth();
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
	ResetItemPool();
	timer_reset();
	knight.position.x = originalPlayerPositionX;
	knight.position.y = originalPlayerPositionY;
	knight.transparency = 255;
	knight.invulnerability = FALSE;
	//init_char(&knight, originalXposition, originalYposition, "./Assets/knightpa.png");
	
	//preload_spawn_map(); //This is for declarations in enemy_array
	load_audio(); //load audio
	Player_FullHeal();

}


void WinCondition()
{
	//static float timer = 300.0f;

	//if (timer > 0)
	//{
	//	timer -= CP_System_GetDt();
	//	printf("survive timer: %f\n", timer);
	//}
	//else
	//{
	//	currentState++;
	//	timer = 300.0f;
	//	gameState = WIN;
	//}
	if (*tick == 10000)
	{
		if (currentState < LEVEL_5)
		{
			currentState++;
		}
		gameState = WIN;

	}

}

void DropStuffs(CP_Vector position) {
	DropStuff(position.x, position.y);
}


void DropStuff(float posX, float posY)
{
	for (int i = 0, j = 0; i <= j && j < MAX_DROP; i++)
	{
		if (item_pool[i].enabled == 0)
		{
			int randomChanceSpawnRate = CP_Random_RangeInt(0, 99);

			if (randomChanceSpawnRate >= 0 && randomChanceSpawnRate < 19)
			{
				item_pool[i].position.x = posX;
				item_pool[i].position.y = posY;
				item_pool[i].width = 45;
				item_pool[i].height = 50;
				item_pool[i].enabled = 1;
				
				int randomChance = CP_Random_RangeInt(0, 2);
				item_pool[i].id = randomChance;
				j++;
				printf("Spawned: %d", item_pool[i].enabled);
			}
		}
		else
		{
			j++;
		}
	}

}

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
				CP_Image_Draw(item_pool[i].sprite, item_pool[i].position.x, item_pool[i].position.y, item_pool[i].width, item_pool[i].height, 255);
				if (CheckIfBoxesOverlap(item_pool[i].position.x, item_pool[i].position.y, item_pool[i].width, item_pool[i].height, knight.position.x, knight.position.y, knight.width, knight.height))
				{
					play_healthDrop();
					if (DoubleHeal == TRUE)
					{
						PlayerHealed(2);
						item_pool[i].enabled = 0;
					}
					else
					{
						PlayerHealed(1);
						item_pool[i].enabled = 0;
					}

				}
				break;
			case 1:
				item_pool[i].sprite = CP_Image_Load("./Assets/speedBoost.png");
				CP_Image_Draw(item_pool[i].sprite, item_pool[i].position.x, item_pool[i].position.y, item_pool[i].width, item_pool[i].height, 255);
				if (CheckIfBoxesOverlap(item_pool[i].position.x, item_pool[i].position.y, item_pool[i].width, item_pool[i].height, knight.position.x, knight.position.y, knight.width, knight.height))
				{
					play_speedDrop();
					knight.speedbuff = TRUE;
					item_pool[i].enabled = 0;

				}

				break;
			default:
				/*item_pool[i].position.x = 0;
				item_pool[i].position.y = 0;
				item_pool[i].width = 0;
				item_pool[i].height = 0;
				item_pool[i].enabled = 0;*/
				//printf
				break;

			}
		}
		
	}
	
	
}



void InvulnerabilityFrame()
{
	static float timer = 500.0f;
	static float lerpTimer = 0.f;
	//static float lerp = 1.0f;
	if (timer > 0)
	{

		timer -= CP_System_GetDt();
		
		//lerp = CP_Math_ClampFloat(1 * CP_System_GetDt(), 0.0f, 1.0f);
		if (lerpTimer > 0.25f)
		{ 
			
			knight.transparency = 255;
			lerpTimer = 0.0f;
		}
		else
		{
			lerpTimer += CP_System_GetDt();
			knight.transparency = 127;
			
		}
		//printf("lt: %f\n", lerpTimer);
		//timer -= CP_System_GetMillis();
		//printf("timer: %f\n", timer);
	}
	else
	{	
		knight.invulnerability = FALSE;
		knight.transparency = 255;
		lerpTimer = 0.f;
		timer = 500.0f;
		return;
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
			//printf("Timer: %f\n", timer);
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

void ResetItemPool()
{
	for (int i = 0; i < MAX_DROP; i++)
	{
		item_pool[i].enabled = 0;
		item_pool[i].position.x = 0;
		item_pool[i].position.y = 0;

	}
}

void EnemyCollision()
{

	//for (int i = 0; i < MAX_ENEMY; i++)
	//{
	//	if (enemy_pool[i].alive == 1)
	//	{
	//		if (CheckIfBoxesOverlap(enemy_pool[i].position.x, enemy_pool[i].position.y, enemy_pool[i].size, enemy_pool[i].size, knight.position.x, knight.position.y, knight.width, knight.height) && knight.invulnerability == FALSE)
	//		{
	//			Playertakedamage(1);
	//			printf("Damage Taken: %d\n", 1);
	//			knight.invulnerability = TRUE;
	//		}
	//		if (knight.invulnerability == TRUE)
	//		{
	//			InvulnerabilityFrame();
	//			//printf("knight.invulnerability: %u\n", knight.invulnerability);
	//		}
	//	}
	//}
	for (int i = 0; i < MAX_MOTHER_ENEMY; i++)
	{
		for (int j = 0; j < MAX_CHILDREN; j++)
		{
			if (mother_enemy_pool[i].children[j].alive == 1)
			{
				if (CheckIfBoxesOverlap(mother_enemy_pool[i].children[j].position.x, mother_enemy_pool[i].children[j].position.y, mother_enemy_pool[i].children[j].size, mother_enemy_pool[i].children[j].size, knight.position.x, knight.position.y, knight.width, knight.height) && knight.invulnerability == FALSE)
				{
					Playertakedamage(1);
					printf("Damage Taken: %d\n", 1);
					knight.invulnerability = TRUE;
				}
				if (knight.invulnerability == TRUE)
				{
					InvulnerabilityFrame();
					//printf("knight.invulnerability: %u\n", knight.invulnerability);
				}
			}
		}
	}

}