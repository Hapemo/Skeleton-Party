#include <stdio.h>
#include "cprocessing.h"
#include "game.h"

/* Feel free to declare your own variables here */
float melee_frame = 1; //For melee attack

void game_init(void)
{
    CP_System_SetFrameRate(50);
    /* Initialization of your other variables here */

    CP_System_Fullscreen();
    InitializeVariables();
    LoadBackgroundImage();
    LoadFont();

	CP_Font_Set(CP_Font_GetDefault());
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	init_char(); 
	
	melee_frame++;//For melee attack
}

void game_update(void)
{
	TerminateFullscreen();

	FullscreenKeyPressed();

	FullscreenMode();

	DrawGameCanvas();
	
	DrawPlayerHealth();

	activate_melee_by_mouse(&melee_frame);

	//lightbulb();

	game_control();

	DrawMenuButton();

	DrawMenuCanvas();

	ButtonClicked();

	

}

void game_exit(void)
{

}
