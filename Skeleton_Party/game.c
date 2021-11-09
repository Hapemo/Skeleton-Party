#include <stdio.h>
#include "cprocessing.h"
#include "game.h"

/* Feel free to declare your own variables here */
int gamePause;
struct character knight, mage, archer;


void game_init(void)
{
	gamePause = 0;
	gameState = MAIN_MENU;
    CP_System_SetFrameRate(60);
    /* Initialization of your other variables here */

	init_PlayerHP(); // playerHp init


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

			// player hP bar printer to be added when the actual game starts. not to be included in title screen
			Player_Redheartprinter();
			Player_Emptyheartprinter();
			//DrawPlayerHealth();
			enemy_movement();
			enemy_damage();
			activate_melee_by_mouse(knight.position);
			lightbulb();
			movement_1();
			tick();
<<<<<<< Updated upstream
			game_control(&knight);
=======
			shooting_check(knight.position);
			game_control();
>>>>>>> Stashed changes

			if (bug.alive == 1)
			{
				if (CheckIfBoxesOverlap(bug.enemyPosition.x, bug.enemyPosition.y, bug.width, bug.height, knight.position.x, knight.position.y, knight.width, knight.height))
				{
					Playertakedamage(1);
				}
			}
			DrawItem();

			break;
		case PAUSED:
			if (CP_Input_KeyTriggered(KEY_P)) // press p to pause/ unpause
			{
				
				gamePause = !gamePause;
				gameState = PLAYING;
				//DrawPauseCanvas();

			}
			
			break;

		case MAIN_MENU:

			DrawMenuButton();

			DrawMenuCanvas();

			ButtonClicked();
			break;


		}
	//}

}

void game_exit(void)
{
	exit_PlayerHP();
}
