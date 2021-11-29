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

struct ResetButton 
{
	float posX;
	float posY;
	float width;
	float height;
}resetPauseButton;

struct MenuButton {

	float posX;
	float posY;
	float width;
	float height;
}menuPauseButton;

struct CreditButton {

	float posX;
	float posY;
	float width;
	float height;
}credMenuBtn, credNextBtn;

CP_Image creditScreen1DP = NULL;
CP_Image creditScreen2SP = NULL;
CP_Image creditMenubtn = NULL;
CP_Image creditNextbtn = NULL;

/*
 load credit screen assets
 */
void load_Credit_Image() {
	creditScreen1DP = CP_Image_Load("./Assets/creditspg1.png");
	creditScreen2SP = CP_Image_Load("./Assets/creditspg2.png");
	creditMenubtn = CP_Image_Load("./Assets/Menubtn.png");
	creditNextbtn = CP_Image_Load("./Assets/next.png");
}

CP_Sound menubg = NULL;
CP_Sound crit = NULL;
CP_Sound death = NULL;
CP_Sound meleeHit = NULL;
CP_Sound heathDrop = NULL;
CP_Sound speedDrop = NULL;
CP_Sound swordSwing = NULL;
CP_Sound click = NULL;
CP_Sound switchChar = NULL;
CP_Sound deniedNoMoney = NULL;
/*
load audio 
*/
void load_audio() {
	menubg = CP_Sound_LoadMusic("./Assets/newBGLoop.wav");
	crit = CP_Sound_Load("./Assets/critHit.wav");
	death = CP_Sound_Load("./Assets/dead.wav");
	meleeHit = CP_Sound_Load("./Assets/swordHit.wav");
	heathDrop = CP_Sound_Load("./Assets/healthBoostUp.wav");
	speedDrop = CP_Sound_Load("./Assets/SpeedBoostUp.wav");
	swordSwing = CP_Sound_Load("./Assets/sword.wav");
	click = CP_Sound_Load("./Assets/clickSound.wav");
	switchChar = CP_Sound_Load("./Assets/switchChar.wav");
	deniedNoMoney = CP_Sound_Load("./Assets/denied.wav");
}

//play menusound 
void play_menubg() {
	//CP_Sound_PlayMusic(menubg);
	CP_Sound_PlayAdvanced(menubg, 1.0f, 1.0f, TRUE, CP_SOUND_GROUP_1);
	/*if (gameState == PREPROOM) {
		//CP_Sound_PauseAll();
		CP_Sound_PauseGroup(CP_SOUND_GROUP_1);
	}
	else
	{
		//CP_Sound_ResumeAll();
		CP_Sound_ResumeGroup(CP_SOUND_GROUP_1);
	}*/
	//CP_Sound_PlayMusic(menubg, 1.0f, 1.0f, TRUE, CP_SOUND_GROUP_1);
}

/*play crit sound*/
void play_crit() {
	CP_Sound_PlayAdvanced(crit, 0.1f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}

//play when player dies
void play_death() {
	CP_Sound_PlayAdvanced(death, 0.1f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}

//play when sword hit enemy
void play_swordHit() {
	CP_Sound_PlayAdvanced(meleeHit, 0.4f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}

//play when player get health boost
void play_healthDrop() {
	CP_Sound_PlayAdvanced(heathDrop, 0.3f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}
//speed drop collect
void play_speedDrop() {
	CP_Sound_PlayAdvanced(speedDrop, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}
// when player swing sword 
void play_swordSwing() {
	CP_Sound_PlayAdvanced(swordSwing, 0.1f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}
//clickSound for buttona
void play_click() {
	CP_Sound_PlayAdvanced(click, 0.1f, 1.0f, FALSE, CP_SOUND_GROUP_4);
}
void play_charswitch() {
	CP_Sound_PlayAdvanced(switchChar, 0.1f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}
void play_denied() {
	CP_Sound_PlayAdvanced(deniedNoMoney, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}
void free_audio() {
	CP_Sound_Free(&menubg);
	CP_Sound_Free(&crit);
	CP_Sound_Free(&death);
	CP_Sound_Free(&meleeHit);
	CP_Sound_Free(&heathDrop);
	CP_Sound_Free(&swordSwing);
	CP_Sound_Free(&click);
	CP_Sound_Free(&switchChar);
	CP_Sound_Free(&deniedNoMoney);
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

/*void init_enemy() {
	bug.enemyPosition = CP_Vector_Set(500, 500);
	//CP_Settings_ImageMode(CP_POSITION_CENTER);
	bug.enemyDesign = CP_Image_Load("./Assets/Enemydot.png");
	bug.width = 100;
	bug.height = 100;
	bug.alive = 1;
}*/
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

void drawWinScreen() {
	CP_Font_Set(myFont);
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	if (gameState == WIN) {
		CP_Settings_Fill(COLOR_BLACK);
		CP_Graphics_DrawRect(width +width / 2, height +height / 2, width, height);
		CP_Font_DrawTextBox("YOU WIN!",( width / 8 * 3) + (width / 6) / 6.5f, (height / 8 * 3) + (height / 8) / 1.5f, (width / 6));
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

		continueButton.posX = width / 8 * 3;
		continueButton.posY = height / 8 * 3;
		continueButton.width = width / 6;
		continueButton.height = height /8;

		resetPauseButton.posX = continueButton.posX;
		resetPauseButton.posY = continueButton.posY + continueButton.height + 10.f;
		resetPauseButton.width = width / 6;
		resetPauseButton.height = height / 8;

		menuPauseButton.posX = continueButton.posX;
		menuPauseButton.posY = resetPauseButton.posY + resetPauseButton.height + 10.f;
		menuPauseButton.width = width / 6;
		menuPauseButton.height = height / 8;

		CP_Settings_Fill(COLOR_PURPLE);
		//return to Game
		CP_Graphics_DrawRect(continueButton.posX, continueButton.posY, continueButton.width, continueButton.height);
		CP_Settings_TextSize(3 * (continueButton.width / width * 100));
		CP_Settings_Fill(COLOR_WHITE);
		CP_Font_DrawTextBox("Continue", continueButton.posX + continueButton.width / 6.5f, continueButton.posY + continueButton.height / 1.5f, continueButton.width);

		CP_Settings_Fill(COLOR_PURPLE);
		//reset
		CP_Graphics_DrawRect(resetPauseButton.posX, resetPauseButton.posY, resetPauseButton.width, resetPauseButton.height);
		CP_Settings_TextSize(3 * (menuPauseButton.width / width * 100));
		CP_Settings_Fill(COLOR_WHITE);
		CP_Font_DrawTextBox("Restart", resetPauseButton.posX + resetPauseButton.width / 6.5f, resetPauseButton.posY + resetPauseButton.height / 1.5f, resetPauseButton.width);

		CP_Settings_Fill(COLOR_PURPLE);
		//return to Menu
		CP_Graphics_DrawRect(menuPauseButton.posX, menuPauseButton.posY, menuPauseButton.width, menuPauseButton.height);
		CP_Settings_TextSize(3 * (menuPauseButton.width / width * 100));
		CP_Settings_Fill(COLOR_WHITE);
		CP_Font_DrawTextBox("Menu", menuPauseButton.posX + menuPauseButton.width / 6.5f, menuPauseButton.posY + menuPauseButton.height / 1.5f, menuPauseButton.width );
	}
}
//clicking buttons in pause state
void PauseButtonClicked()
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		if (CheckCollisionWithBox(mousePosX, mousePosY, continueButton.width, continueButton.height, continueButton.posX, continueButton.posY))
		{
			play_click();
			pause.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_GRAY);
			gameState = currentLevel;
		}
		if (CheckCollisionWithBox(mousePosX, mousePosY, resetPauseButton.width, resetPauseButton.height, resetPauseButton.posX, resetPauseButton.posY))
		{
			play_click();
			pause.enabled = TRUE;
			CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = RESET;
		}
		if (CheckCollisionWithBox(mousePosX, mousePosY, menuPauseButton.width, menuPauseButton.height, menuPauseButton.posX, menuPauseButton.posY))
		{
			play_click();
			pause.enabled = TRUE;
			CP_Graphics_ClearBackground(COLOR_GRAY);
			EnableMenu();
			gameState = MAIN_MENU;
		}
	}
}

void drawCreditScreenpg1() {
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(creditScreen1DP, WIDTH / 2.0, HEIGHT / 2.0, WIDTH, HEIGHT, 255);

	credMenuBtn.posX = width / 7.0f;
	credMenuBtn.posY = height * (0.925f);
	credMenuBtn.width = width / 5.0f;
	credMenuBtn.height = height / 15.0f;
	CP_Image_Draw(creditMenubtn, credMenuBtn.posX, credMenuBtn.posY, credMenuBtn.width, credMenuBtn.height, 255);

	credNextBtn.posX = 850.0f;
	credNextBtn.posY = height * (0.925f);
	credNextBtn.width = width / 5.0f;
	credNextBtn.height = height / 15.0f;
	CP_Image_Draw(creditNextbtn, credNextBtn.posX, credNextBtn.posY, credNextBtn.width, credNextBtn.height, 255);
}

void drawCreditScreenpg2() {
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(creditScreen2SP, WIDTH / 2.0, HEIGHT / 2.0, WIDTH, HEIGHT, 255);

	credMenuBtn.posX = width / 7.0f;
	credMenuBtn.posY = height * (0.925f);
	credMenuBtn.width = width / 5.0f;
	credMenuBtn.height = height / 15.0f;
	CP_Image_Draw(creditMenubtn, credMenuBtn.posX, credMenuBtn.posY, credMenuBtn.width, credMenuBtn.height, 255);
}

void creditBtnClicked()
{
	float mousePosX = CP_Input_GetMouseX();
	float mousePosY = CP_Input_GetMouseY();
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, credMenuBtn.width, credMenuBtn.height, credMenuBtn.posX, credMenuBtn.posY))
		{
			EnableMenu();
			gameState = MAIN_MENU;
		}
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, credNextBtn.width, credNextBtn.height, credNextBtn.posX, credNextBtn.posY) && (gameState == CREDIT1))
		{
			gameState = CREDIT2;
		}
	}
}

void free_IMAGE() {
	CP_Image_Free(&creditScreen1DP);
	CP_Image_Free(&creditScreen2SP);
	CP_Image_Free(&creditMenubtn);
	CP_Image_Free(&creditNextbtn);
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




