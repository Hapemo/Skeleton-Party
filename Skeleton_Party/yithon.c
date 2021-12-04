/*---------------------------------------------------------
 * file:	game.c
 * author:	yithon
 * email:	yithon.goh@digipen.edu
*
 * brief:	This file contains functions for audio, credit and pause
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
	//BOOL hover;
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

/*in case image cannot be found game would not return error*/
CP_Image creditScreen1DP = NULL;
CP_Image creditScreen2TSL = NULL;
CP_Image creditScreen3SP = NULL;
CP_Image creditMenubtn = NULL;
CP_Image creditNextbtn = NULL;

/*!
@brief  - this function is called to load all image
@return - this function does not return a value, just a function called to execute and load the image 
*/
void load_Credit_Image() {
	creditScreen1DP = CP_Image_Load("./Assets/creditspg1.png");
	creditScreen2TSL = CP_Image_Load("./Assets/creditspg2.png");
	creditScreen3SP = CP_Image_Load("./Assets/creditspg3.png");
	creditMenubtn = CP_Image_Load("./Assets/return.png");
	creditNextbtn = CP_Image_Load("./Assets/next.png");
}
//-------------------------------------------------------------------------------------------------

//in case audio file is not found, gamme will not prompt error instead no audio will play
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
CP_Sound coinsSound = NULL;

/*!
@brief  - this function is called to load all audio file
@return - this function does not return a value, just a function called to execute to load the audio
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
	coinsSound= CP_Sound_Load("./Assets/coins.wav");
}

/*!
@brief  - this function is called to play the background music
@return - this function does not return a value, just a function called to the music when game is started
*/
void play_menubg() {
	CP_Sound_PlayAdvanced(menubg, 1.0f, 1.0f, TRUE, CP_SOUND_GROUP_1);
}

/*!
@brief  - this function is called to play when sword hits a critical hit
@return - this function does not return a value, just a function called when knight hit a crit
*/
void play_crit() {
	CP_Sound_PlayAdvanced(crit, 0.1f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}

/*!
@brief  - this function is called to play when state is game over
@return - this function does not return a value, just a function called when game over screen appear
*/
void play_death() {
	CP_Sound_PlayAdvanced(death, 0.1f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}

/*!
@brief  - this function is called to play when knight attack hit an enemy
@return - this function does not return a value, just a function called when collision happen between sword and enemy
*/
void play_swordHit() {
	CP_Sound_PlayAdvanced(meleeHit, 0.4f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}

/*!
@brief  - this function is called to play when player pick up health bottle
@return - this function does not return a value, just a function called when player and health boost collide 
*/
void play_healthDrop() {
	CP_Sound_PlayAdvanced(heathDrop, 0.3f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}

/*!
@brief  - this function is called to play when player pick up speed bottle
@return - this function does not return a value, just a function called when player and speed boost collide
*/
void play_speedDrop() {
	CP_Sound_PlayAdvanced(speedDrop, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}

/*!
@brief  - this function is called to play when player click attack for knight
@return - this function does not return a value, just a function called when player click attack when using knight
*/
void play_swordSwing() {
	CP_Sound_PlayAdvanced(swordSwing, 0.1f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}

/*!
@brief  - this function is called to play when player click btn 
@return - this function does not return a value, just a function called when player click button 
*/
void play_click() {
	CP_Sound_PlayAdvanced(click, 0.1f, 1.0f, FALSE, CP_SOUND_GROUP_4);
}

/*!
@brief  - this function is called to play when player switch between playstyle
@return - this function does not return a value, just a function called when player click button
*/
void play_charswitch() {
	CP_Sound_PlayAdvanced(switchChar, 0.1f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}

/*!
@brief  - this function is called to play when player didnt have enough coin when trying to purchase upgrades from shop/skill
@return - this function does not return a value, just a function called when player click button and is denied from buying
*/
void play_denied() {
	CP_Sound_PlayAdvanced(deniedNoMoney, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}

/*!
@brief  - this function is called to play when player get coins while fighting or purchasing an upgrade
@return - this function does not return a value, just a function called when player click purchase or recieve money in game
*/
void play_coins() {
	CP_Sound_PlayAdvanced(coinsSound, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_3);
}

/*!
@brief  - this function is called to free audio, to prevent memory leak
@return - this function does not return a value, just a function called to free the audio after game is closed
*/
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
	CP_Sound_Free(&coinsSound);
}

//was upgraded better by Issac after 
/*!
@brief  - this function is called when pause is pressed
@return - this function does not return a value, just a function called when player click pause
*/
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
/*!
@brief  - this function is for collision in pause state
@return - this function does not return a value, just a function called when player click on the buttons in paused state
*/
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

/*!
@brief  - this function is called draw the 1st screen for credit when credit is pressed in menu
@return - this function does not return a value, just a function called when player click on credit
*/
void drawCreditScreenpg1() {
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(creditScreen1DP, WIDTH / 2.0, HEIGHT / 2.0, WIDTH, HEIGHT, 255);
	// draw menu button on right
	credMenuBtn.posX = width / 7.0f;
	credMenuBtn.posY = height * (0.925f);
	credMenuBtn.width = width / 5.0f;
	credMenuBtn.height = height / 15.0f;
	CP_Image_Draw(creditMenubtn, credMenuBtn.posX, credMenuBtn.posY, credMenuBtn.width, credMenuBtn.height, 255);
	//draw next button on the left
	credNextBtn.posX = 810.0f;
	credNextBtn.posY = height * (0.925f);
	credNextBtn.width = width / 5.0f;
	credNextBtn.height = height / 15.0f;
	CP_Image_Draw(creditNextbtn, credNextBtn.posX, credNextBtn.posY, credNextBtn.width, credNextBtn.height, 255);
}

/*!
@brief  - this function is called draw the 2nd screen for credit when player press next in page 1 of credit
@return - this function does not return a value, just a function called when player click on next in page 1 of credit
*/
void drawCreditScreenpg2() {
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(creditScreen2TSL, WIDTH / 2.0, HEIGHT / 2.0, WIDTH, HEIGHT, 255);
	// draw menu button on right
	credMenuBtn.posX = width / 7.0f;
	credMenuBtn.posY = height * (0.925f);
	credMenuBtn.width = width / 5.0f;
	credMenuBtn.height = height / 15.0f;
	CP_Image_Draw(creditMenubtn, credMenuBtn.posX, credMenuBtn.posY, credMenuBtn.width, credMenuBtn.height, 255);
	//draw next button on the left
	credNextBtn.posX = 810.0f;
	credNextBtn.posY = height * (0.925f);
	credNextBtn.width = width / 5.0f;
	credNextBtn.height = height / 15.0f;
	CP_Image_Draw(creditNextbtn, credNextBtn.posX, credNextBtn.posY, credNextBtn.width, credNextBtn.height, 255);
}

/*!
@brief  - this function is called draw the 3rd screen for credit when player press next in page 2 of credit
@return - this function does not return a value, just a function called when player click on next in page 2 of credit
*/
void drawCreditScreenpg3() {
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(creditScreen3SP, WIDTH / 2.0, HEIGHT / 2.0, WIDTH, HEIGHT, 255);

	credMenuBtn.posX = width / 7.0f;
	credMenuBtn.posY = height * (0.925f);
	credMenuBtn.width = width / 5.0f;
	credMenuBtn.height = height / 15.0f;
	CP_Image_Draw(creditMenubtn, credMenuBtn.posX, credMenuBtn.posY, credMenuBtn.width, credMenuBtn.height, 255);
}

/*!
@brief  - this function is used for collision of button in credit screen
@return - this function does not return a value, just a function called to change between screen in credit
*/
void creditBtnClicked()
{
	float mousePosX = CP_Input_GetMouseX();
	float mousePosY = CP_Input_GetMouseY();
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		//for menu
		if (CheckCollisionWithBoxImage(mousePosX, mousePosY, credMenuBtn.width, credMenuBtn.height, credMenuBtn.posX, credMenuBtn.posY))
		{
			EnableMenu();
			gameState = MAIN_MENU;
		}
		//for 2nd page
		else if (CheckCollisionWithBoxImage(mousePosX, mousePosY, credNextBtn.width, credNextBtn.height, credNextBtn.posX, credNextBtn.posY) && (gameState == CREDIT1))
		{
			gameState = CREDIT2;
		}
		//for 3rd page
		else if (CheckCollisionWithBoxImage(mousePosX, mousePosY, credNextBtn.width, credNextBtn.height, credNextBtn.posX, credNextBtn.posY) && (gameState == CREDIT2))
		{
			gameState = CREDIT3;
		}
	}
}
/*!
@brief  - this function is called to free the image to prevent memory leak
@return - this function does not return a value, just a function called to free the images used to prevent leak when game is closed
*/
void free_IMAGE() {
	CP_Image_Free(&creditScreen1DP);
	CP_Image_Free(&creditScreen2TSL);
	CP_Image_Free(&creditScreen3SP);
	CP_Image_Free(&creditMenubtn);
	CP_Image_Free(&creditNextbtn);
}
