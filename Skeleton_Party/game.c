/*---------------------------------------------------------
 * file:	game.c
 * author:	jazz, isaac, keith, yi thon, qiu hui
 * email:	j.teoh@digipen.edu,i.yeo@digipen.edu, weijiekeith.lua@digipen.edu,yithon.goh@digipen.edu,qiuhui.tan@digipen.edu   
*
 * brief:	This file is the main brain of the game. It constantly runs and updates to run the game
*
 * documentation link:
 * https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
*
 * Copyright © 2020 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include <stdio.h>
#include "cprocessing.h"
#include "game.h"


//int CurrentCharacter = 0;

void PlayGame();


void game_init(void)
{
	gamePause = 0;
	gameState = LOGO;
	currentLevel = MAIN_MENU;
    CP_System_SetFrameRate(60);
    /* Initialization of your other variables here */

	//isaac's init function calls 
	init_PlayerHP();	// defn in isaac.c
	//init_EnemySprite();	// def in Enemy_arrays.c


    InitializeVariables();
	InitializeSkillShopUI();

    LoadBackgroundImage(1);
    LoadFont();

	CP_Font_Set(CP_Font_GetDefault());
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	
	//init_enemy();
	
	//CP_System_ShowConsole();
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	originalPlayerPositionX = width * 1.25f;
	originalPlayerPositionY = height * 2.25f;
 
	
	//@purpose initialise the first character to knight 
	init_char(&knight, originalPlayerPositionX, originalPlayerPositionY, "./Assets/knightpa.png");
	originalPlayerSpeed = knight.speed;

	//preload_spawn_map(LEVEL_1); //This is for declarations in enemy_array
	load_audio(); //load audio
	load_Credit_Image();
}

void game_update(void)
{
	
	//TerminateFullscreen();

	//FullscreenKeyPressed();

	FullscreenMode();
		
		switch (gameState)
		{
		case LOGO:
		DrawLogoScreen();

		break;
		case LEVEL_SELECTION:

			DrawLevelSelectionCanvas();
			ReturnMainMenuClicked();
			ButtonLevelSelectionClicked();
			break;

		case LEVEL_1:
			
			PlayGame();
			break;

		case LEVEL_2:
			
			PlayGame();
			break;

		case LEVEL_3:
			
			PlayGame();
			break;
		case LEVEL_4:
			PlayGame();
			break;
		case LEVEL_5:
			PlayGame();
			break;
	

		case PAUSED:
			
			
			Screen_PAUSE_Print();
			Screen_PAUSE_ButtonClicked();
			//DrawPauseCanvas();
			//PauseButtonClicked();


			if (CP_Input_KeyTriggered(KEY_P)) // press p to pause/ unpause
			{
			
				gamePause = !gamePause;
				gameState = currentLevel;
				
			}
			
			break;

		case MAIN_MENU:

			MainMenuState = TRUE;
			TerminateFullscreen();
			EnableMenu();
			play_menubg();
			DrawMenuCanvas();
			ButtonClicked();
			break;
		case INSTRUCTIONS:
			DrawInstructionsCanvas();
			ReturnMainMenuClicked();
			break;
		case WIN:

			if (RewardGiven == FALSE)
			{
				RewardGiven = TRUE;
				if (DoubleDrop == TRUE)
				{
					Exp += (additionalExp * 2);
					//Gold += (additionalGold * 2);
				}
				else
				{
					Exp += additionalExp;
					Gold += additionalGold;
				}
			}

			Screen_WIN_Print();
			Screen_WIN_ButtonClicked();

			break;
		case LOSE:
			play_death();
			
			//TerminateFullscreen();
			Screen_GAMEOVER_Print();
			Screen_GAMEOVER_ButtonClicked();

			break;
		case CREDIT1:
			drawCreditScreenpg1();
			creditBtnClicked();
			break;

		case CREDIT2:
			drawCreditScreenpg2();
			creditBtnClicked();
			break;

		case CREDIT3:
			drawCreditScreenpg3();
			creditBtnClicked();
			break;
		case EXIT:

			CP_Engine_Terminate();
			break;

		case PREPROOM : 
			gamePause = !gamePause;

			Screen_PREPROOM_Print();
			Screen_PREPROOM_ButtonClicked();

			break;

		case UPGRADES :
			Screen_UPGRADES_Print();
			Screen_UPGRADE_ButtonClicked();

			break;

		case SHOP :
			Screen_SHOP_Print();
			Screen_SHOP_ButtonClicked();

			break;

		case SKILL :
			Screen_SKILL_Print();
			Screen_SKILL_ButtonClicked();

			break;

		case YOUDIED:
			gamePause = 1;
			Screen_YOUDIED_Print();
			Screen_YOUDIED_ButtonClicked();

			break;

		case REVIVE:
			Screen_REVIVE_Print();
			Screen_REVIVE_ButtonClicked();

			break;
		case THANKS:
			Screen_THANKS_Print();

			Screen_Thanks_ButtonClicked();

			break;
		}
		


}


void PlayGame()
{
	//SWORD_CRIT_CHANCE += additionalcrit;
	shrapnel_update();
	LoadBackgroundImage(currentLevel);
	
	//DeathCondition();
	
	if (PlayerGethealth() == 0 )
		if (revivetoken == 0)
		{
			DeathCondition();
		}
		else
		{
		gameState = YOUDIED;
		}
	

	//TerminateFullscreen();
	if (CP_Input_KeyTriggered(KEY_P)) // press p to pause/ unpause
	{
		Gold = 99;
		Exp = 99;
		revivetoken = 3;

	}
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) // press esc to pause/ unpause
	{
		gamePause = !gamePause;
		gameState = PAUSED;

	}
	DrawGameCanvas();

	DrawBuffIndicator();

	//@purpose character switching 
	if (CP_Input_KeyTriggered(KEY_1))
	{
		play_charswitch();
		CurrentCharacterKeith = knightint;

	}
	if (CP_Input_KeyTriggered(KEY_2))
	{
		play_charswitch();
		CurrentCharacterKeith = mageint;
	}
	if (CP_Input_KeyTriggered(KEY_3))
	{
		play_charswitch();
		CurrentCharacterKeith = archerint;
	}
	update_char(CurrentCharacterKeith, &knight);

	// class skill restriction 
	if (CurrentCharacterKeith == knightint)
	{
		initiate_melee();
	}
	else if (CurrentCharacterKeith == mageint)
	{
		shooting_check(knight.position);
	}
	else if (CurrentCharacterKeith == archerint)
	{
		piercing_shooting_check(knight.position);

	}
	
	update_bullet_travel();
	weapon_to_enemy_collision();
	// render and control movement of knight
	game_control(&knight);
	spawn_map();

	//Attack updates
	if (shrapnelstate == TRUE) shrapnel_update();
	shrapnel_update();
	if (shockwavestate == TRUE) sword_explosion_update();

	melee_update(knight.position);
	explosion_update();
	update_piercing_bullet_travel();
	movement_pattern_vertical_and_diagonal();
	movement_pattern_spinning_circle();
	timer();

	SpeedBuffEffect();
	//player_touch_enemy();
	EnemyCollision();
	DrawItem();
	DespawnTimer();
	// player hP bar printer to be added when the actual game starts. not to be included in title screen
	Player_Redheartprinter();
	Player_Emptyheartprinter();
	CP_Settings_TextSize(60);
	
	CP_Settings_Fill(COLOR_WHITE);

	ScorePrinter(Exp, 690, 65);


	ScorePrinter(Gold, 850, 65);
	

	ScorePrinter(revivetoken, 695, 145);

	Screen_Currency_Print();	
	
	DrawObjectiveText();
	WinCondition();
}


void game_exit(void)
{
	//exit_EnemySprite();
	exit_PlayerHP();
	exit_skilltreepictures();
	free_audio();
	free_IMAGE();
}
