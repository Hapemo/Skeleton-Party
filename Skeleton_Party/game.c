#include <stdio.h>
#include "cprocessing.h"
#include "game.h"

/* Feel free to declare your own variables here */
//int gamePause;

int CurrentCharacter = 0;



void game_init(void)
{
	gamePause = 0;
	gameState = LOGO;
	currentState = LEVEL_1;
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
	
	CP_System_ShowConsole();
	float width = (float)CP_System_GetWindowWidth();
	float height = (float)CP_System_GetWindowHeight();
	originalPlayerPositionX = width * 1.25f;
	originalPlayerPositionY = height * 2.25f;

	init_char(&knight, originalPlayerPositionX, originalPlayerPositionY, "./Assets/knightpa.png");
	

	preload_spawn_map(); //This is for declarations in enemy_array
	load_audio(); //load audio
}

void game_update(void)
{
	
	//TerminateFullscreen();

	//FullscreenKeyPressed();

	FullscreenMode();
	//if (gamePause)
	//{
		//DrawPauseCanvas();
	//}
	//else {


		
		switch (gameState)
		{
		case LOGO:
		DrawLogoScreen();

		break;


		case LEVEL_1:
			LoadBackgroundImage(1);
			DeathCondition();
			TerminateFullscreen();
			if (CP_Input_KeyTriggered(KEY_P)) // press p to pause/ unpause
			{
				gamePause = !gamePause;
				gameState = PAUSED;
			}
			DrawGameCanvas();
			if (CP_Input_KeyTriggered(KEY_1))
			{
				CurrentCharacter = knightint;
				
			}
			if (CP_Input_KeyTriggered(KEY_2))
			{
				CurrentCharacter = mageint;
			}
			if (CP_Input_KeyTriggered(KEY_3))
			{
				CurrentCharacter = archerint;
			}
			update_char(CurrentCharacter, &knight);
			// class skill restriction 
			if (CurrentCharacter == knightint)
			{
				initiate_melee();
			}
			else if (CurrentCharacter == mageint)
			{
				shooting_check(knight.position);			
			}
			else if (CurrentCharacter == archerint)
			{
				piercing_shooting_check(knight.position);
				
			}
			update_bullet_travel();
			weapon_to_enemy_collision();
			lightbulb();
			game_control(&knight);
			spawn_map();

			//Attack updates
			if (shrapnelstate == TRUE) shrapnel_update();

			if (shockwavestate== TRUE) sword_explosion_update();

			melee_update(knight.position);
			explosion_update();
			update_piercing_bullet_travel();
			// enemy movement patterns
			movement_pattern_vertical_and_diagonal();
			movement_pattern_spinning_circle();
			timer();

			SpeedBuffEffect();
			player_touch_enemy();
			EnemyCollision();
			DrawItem();
			// player hP bar printer to be added when the actual game starts. not to be included in title screen
			Player_Redheartprinter();
			Player_Emptyheartprinter();
			CP_Settings_TextSize(100);
			CP_Settings_Fill(darkviolet);
			ScorePrinter(Exp, 690, 80);
			CP_Settings_Fill(darkviolet);
			ScorePrinter(Gold, 850, 80);
			Screen_Currency_Print();
			WinCondition();
			break;

		case LEVEL_2:
			LoadBackgroundImage(2);
			DeathCondition();
			TerminateFullscreen();
			if (CP_Input_KeyTriggered(KEY_P)) // press p to pause/ unpause
			{
				gamePause = !gamePause;
				gameState = PAUSED;
			}
			DrawGameCanvas();
			if (CP_Input_KeyTriggered(KEY_1))
			{
				CurrentCharacter = knightint;

			}
			if (CP_Input_KeyTriggered(KEY_2))
			{
				CurrentCharacter = mageint;
			}
			if (CP_Input_KeyTriggered(KEY_3))
			{
				CurrentCharacter = archerint;
			}
			update_char(CurrentCharacter, &knight);
			// class skill restriction 
			if (CurrentCharacter == knightint)
			{
				initiate_melee();
			}
			else if (CurrentCharacter == mageint)
			{
				shooting_check(knight.position);
			}
			else if (CurrentCharacter == archerint)
			{
				piercing_shooting_check(knight.position);

			}
			update_bullet_travel();
			weapon_to_enemy_collision();
			lightbulb();
			game_control(&knight);
			spawn_map();

			//Attack updates
			if (shrapnelstate == TRUE) shrapnel_update();

			if (shockwavestate == TRUE) sword_explosion_update();

			melee_update(knight.position);
			explosion_update();
			update_piercing_bullet_travel();
			// enemy movement patterns
			movement_pattern_vertical_and_diagonal();
			movement_pattern_spinning_circle();
			timer();
			SpeedBuffEffect();
			player_touch_enemy();
			EnemyCollision();
			DrawItem();
			// player hP bar printer to be added when the actual game starts. not to be included in title screen
			Player_Redheartprinter();
			Player_Emptyheartprinter();
			CP_Settings_TextSize(100);
			CP_Settings_Fill(darkviolet);
			ScorePrinter(Exp, 690, 80);
			CP_Settings_Fill(darkviolet);
			ScorePrinter(Gold, 850, 80);
			Screen_Currency_Print();

			WinCondition();
			break;

		case LEVEL_3:
			LoadBackgroundImage(3);
			DeathCondition();
			TerminateFullscreen();
			if (CP_Input_KeyTriggered(KEY_P)) // press p to pause/ unpause
			{
				gamePause = !gamePause;
				gameState = PAUSED;
			}
			DrawGameCanvas();
			if (CP_Input_KeyTriggered(KEY_1))
			{
				CurrentCharacter = knightint;

			}
			if (CP_Input_KeyTriggered(KEY_2))
			{
				CurrentCharacter = mageint;
			}
			if (CP_Input_KeyTriggered(KEY_3))
			{
				CurrentCharacter = archerint;
			}
			update_char(CurrentCharacter, &knight);
			// class skill restriction 
			if (CurrentCharacter == knightint)
			{
				initiate_melee();
			}
			else if (CurrentCharacter == mageint)
			{
				shooting_check(knight.position);
			}
			else if (CurrentCharacter == archerint)
			{
				piercing_shooting_check(knight.position);

			}
			update_bullet_travel();
			weapon_to_enemy_collision();
			lightbulb();
			game_control(&knight);
			spawn_map();

			//Attack updates
			if (shrapnelstate == TRUE) shrapnel_update();

			if (shockwavestate == TRUE) sword_explosion_update();

			melee_update(knight.position);
			explosion_update();
			update_piercing_bullet_travel();
			// enemy movement patterns
			movement_pattern_vertical_and_diagonal();
			movement_pattern_spinning_circle();
			timer();
			SpeedBuffEffect();
			player_touch_enemy();
			EnemyCollision();
			DrawItem();
			// player hP bar printer to be added when the actual game starts. not to be included in title screen
			Player_Redheartprinter();
			Player_Emptyheartprinter();
			CP_Settings_TextSize(100);
			CP_Settings_Fill(darkviolet);
			ScorePrinter(Exp, 690, 80);
			CP_Settings_Fill(darkviolet);
			ScorePrinter(Gold, 850, 80);
			Screen_Currency_Print();

			WinCondition();
			break;

		case PAUSED:
			
			
			Screen_PAUSE_Print();
			Screen_PAUSE_ButtonClicked();
			//DrawPauseCanvas();
			//PauseButtonClicked();


			if (CP_Input_KeyTriggered(KEY_P)) // press p to pause/ unpause
			{
			
				gamePause = !gamePause;
				gameState = currentState;
				
			}
			
			break;

		case MAIN_MENU:
			
			
			TerminateFullscreen();
			EnableMenu();
			play_menubg();
			DrawMenuButton();

			DrawMenuCanvas();
		
		
			ButtonClicked();
			break;
		case INSTRUCTIONS:
			DrawInstructionsCanvas();
			ReturnMainMenuClicked();
			break;
		case WIN:
			ResetState();
			if (RewardGiven == FALSE)
			{
				RewardGiven = TRUE;
				if (DoubleDrop == TRUE)
				{
					Exp += (additionalExp * 2);
					Gold += (additionalGold * 2);
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
			ResetState();
			//TerminateFullscreen();
			Screen_GAMEOVER_Print();
			Screen_GAMEOVER_ButtonClicked();

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
		//case RETRY : 


			
			//exit_PlayerHP();
			//exit_skilltreepictures();
			//free_audio();



			//gamePause = 0;
			//gameState = LOGO;
			//CP_System_SetFrameRate(60);
			/* Initialization of your other variables here */

			//isaac's init function calls 
			//init_PlayerHP();	// defn in isaac.c
			//init_EnemySprite();	// def in Enemy_arrays.c

			
			//InitializeSkillShopUI();

			//LoadBackgroundImage();
			//LoadFont();

			//CP_Font_Set(CP_Font_GetDefault());
			//CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			//init_enemy();
			//CP_System_ShowConsole();
			/*float width = (float)CP_System_GetWindowWidth();
			float height = (float)CP_System_GetWindowHeight();*/
			//originalXposition = width * 1.25f;
			//originalYposition = height * 2.25f;
			//init_char(&knight, originalXposition, originalYposition, "./Assets/knightpa.png");
			//preload_spawn_map(); //This is for declarations in enemy_array
			//load_audio(); //load audio
			//

			//Player_FullHeal();
			//gameState = PREPROOM;

			break;
		}

		

	//}

}



void game_exit(void)
{
	//exit_EnemySprite();
	exit_PlayerHP();
	exit_skilltreepictures();
	free_audio();
}
