#include <stdio.h>
#include "cprocessing.h"
#include "game.h"

/* Feel free to declare your own variables here */
int gamePause;
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


    CP_System_Fullscreen();
    InitializeVariables();
    LoadBackgroundImage();
    LoadFont();

	CP_Font_Set(CP_Font_GetDefault());
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	

	init_enemy();
	
	CP_System_ShowConsole();

	init_char(&knight, 200, 200, "./Assets/knight.png");
	init_char(&mage, 200, 200, "./Assets/mage.png");
	init_char(&archer, 200, 200, "./Assests/archer");

	preload_spawn_map(); //This is for declarations in enemy_array

}

void game_update(void)
{
	
	TerminateFullscreen();

	FullscreenKeyPressed();

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


			// class skill restriction 
			if (CurrentCharacter == knightint)
			{
				activate_melee_by_mouse(knight.position);
				sword_explosion_update();
			}
			else if (CurrentCharacter == mageint)
			{
				shooting_check(knight.position);
				explosion_update();
				shrapnel_update();
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
			
			DrawPauseCanvas();
			PauseButtonClicked();

			if (CP_Input_KeyTriggered(KEY_P)) // press p to pause/ unpause
			{
			
				gamePause = !gamePause;
				gameState = PLAYING;
				
			}
			
			break;

		case MAIN_MENU:

			DrawMenuButton();

			DrawMenuCanvas();

			ButtonClicked();
			break;
		
		case EXIT:

			CP_Engine_Terminate();
			break;

		}

		

	//}

}

void game_exit(void)
{
	//exit_EnemySprite();
	exit_PlayerHP();
}
