#include <stdio.h>
#include "cprocessing.h"
#include "game.h"

/* Feel free to declare your own variables here */
float melee_frame = 1; //For melee attack

void game_init(void)
{
    CP_System_SetFrameRate(50);
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

	activate_melee_by_mouse(&melee_frame);

	//lightbulb();

	game_control();

	DrawMenuButton();

	DrawMenuCanvas();

	ButtonClicked();


	

}

void game_exit(void)
{
	exit_PlayerHP();
}
