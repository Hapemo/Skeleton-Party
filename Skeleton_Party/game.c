#include <stdio.h>
#include "cprocessing.h"
#include "game.h"

/* Feel free to declare your own variables here */
//int gamePause;
struct character knight, mage, archer;
int CurrentCharacter = 0;



void game_init(void)
{
	gamePause = 0;
	gameState = MAIN_MENU;
    CP_System_SetFrameRate(60);
    /* Initialization of your other variables here */

	//isaac's init function calls 
	init_PlayerHP();	// defn in isaac.c
	//init_EnemySprite();	// def in Enemy_arrays.c


    InitializeVariables();
	InitializeSkillShopUI();

    LoadBackgroundImage();
    LoadFont();

	CP_Font_Set(CP_Font_GetDefault());
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	

	init_enemy();
	
	CP_System_ShowConsole();

	init_char(&knight, 200, 200, "./Assets/knightpa.png");
	init_char(&mage, 200, 200, "./Assets/mage.png");
	init_char(&archer, 200, 200, "./Assests/archer.png");

	preload_spawn_map(); //This is for declarations in enemy_array
	load_audio(); //load audio
}

void game_update(void)
{
	
	TerminateFullscreen();

	//FullscreenKeyPressed();

	FullscreenMode();
	//if (gamePause)
	//{
		//DrawPauseCanvas();
	//}
	//else {


		
		switch (gameState)
		{
		case PLAYING:
			if (CP_Input_KeyTriggered(KEY_P)) // press p to pause/ unpause
			{
				gamePause = !gamePause;
				//gameState = PAUSED;
				//gameState = PREPROOM;
				//gameState = UPGRADES ;
				//gameState = SHOP;
				//gameState = SKILL;
				gameState = WIN;


			
			}
			
			DrawGameCanvas();
			
			if (CP_Input_KeyTriggered(KEY_1))
			{
				play_crit();//temp
				CurrentCharacter = knightint;
				
			}

			if (CP_Input_KeyTriggered(KEY_2))
			{
				play_crit();//temp
				CurrentCharacter = mageint;
			}

			if (CP_Input_KeyTriggered(KEY_3))
			{
				play_crit();//temp
				CurrentCharacter = archerint;
			}


			// class skill restriction 
			if (CurrentCharacter == knightint)
			{
				initiate_melee();
			}
			else if (CurrentCharacter == mageint)
			{
				shooting_check(knight.position);			
				update_bullet_travel();

			}
			else if (CurrentCharacter == archerint)
			{
				//piercing_shooting_check(knight.position);
			}
			
			//DrawPlayerHealth();
			//enemy_movement();
			//enemy_damage();
			lightbulb();
			
			spawn_map();

			//Attack updates
			// 
			//if (shrapnelstate == TRUE)
				shrapnel_update();

			melee_update(knight.position);
			explosion_update();
			
			sword_explosion_update();
	
			
			
			// enemy movement patterns
			movement_pattern_vertical_and_diagonal();
			movement_pattern_spinning_circle();


			timer();
			game_control(&knight);

			SpeedBuffEffect();
			
			player_touch_enemy();
			/*if (bug.alive == 1)
			{
				if (CheckIfBoxesOverlap(bug.enemyPosition.x, bug.enemyPosition.y, bug.width, bug.height, knight.position.x, knight.position.y, knight.width, knight.height))
				{
					Playertakedamage(1);
				}
			}*/

			/***********************************************************PRINTing*****************************************************************/

			DrawItem();
			// isaac's enemy movement functions. Update enemy and print 
			/*UpdateEnemyMovement();
			Enemy_printer();
			cycleEnemyRemove();*/

			// player hP bar printer to be added when the actual game starts. not to be included in title screen
			Player_Redheartprinter();
			Player_Emptyheartprinter();

			break;
		case PAUSED:
			
			
			Screen_PAUSE_Print();
			Screen_PAUSE_ButtonClicked();
			//DrawPauseCanvas();
			//PauseButtonClicked();


			if (CP_Input_KeyTriggered(KEY_P)) // press p to pause/ unpause
			{
			
				gamePause = !gamePause;
				gameState = PLAYING;
				
			}
			
			break;

		case MAIN_MENU:

			EnableMenu();
			play_menubg();
			DrawMenuButton();

			DrawMenuCanvas();
		
		
			ButtonClicked();
			break;
		case WIN:

			Screen_WIN_Print();
			Screen_WIN_ButtonClicked();

			break;
		case LOSE:

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
