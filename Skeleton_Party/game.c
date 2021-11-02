#include <stdio.h>
#include "cprocessing.h"
#include "game.h"

/* Feel free to declare your own variables here */
float melee_frame = 1; //For melee attack

void game_init(void)
{
    CP_System_SetFrameRate(50);
    CP_System_SetFrameRate(60);
    /* Initialization of your other variables here */

	init_PlayerHP(); // playerHp init


    CP_System_Fullscreen();
    InitializeVariables();
    LoadBackgroundImage();
    LoadFont();

	CP_Font_Set(CP_Font_GetDefault());
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	init_char(); 

	init_enemy();
	
	CP_System_ShowConsole();
	melee_frame++;//For melee attack
}

void game_update(void)
{
	TerminateFullscreen();

	FullscreenKeyPressed();

	FullscreenMode();

	DrawGameCanvas();

	// player hP bar printer to be added when the actual game starts. not to be included in title screen
	Player_Redheartprinter();
	Player_Emptyheartprinter();
	//DrawPlayerHealth();

	

	enemy_movement();

	enemy_damage();

	activate_melee_by_mouse(&melee_frame, knight.position);

	//lightbulb();

	game_control();
	
	/*float enemyPosX = 500;
	float enemyPosY = 500;
	
	CP_Graphics_DrawRect(enemyPosX, enemyPosY, 100, 100);*/


	if (CheckIfBoxesOverlap(bug.enemyPosition.x, bug.enemyPosition.y, bug.width, bug.height, knight.position.x, knight.position.y, knight.width, knight.height))
	{
		Playertakedamage(1);
	}


	DrawMenuButton();

	DrawMenuCanvas();

	ButtonClicked();


	

}

void game_exit(void)
{
	exit_PlayerHP();
}
