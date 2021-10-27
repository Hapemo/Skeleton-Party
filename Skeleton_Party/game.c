#include <stdio.h>
#include "cprocessing.h"
#include "game.h"

/* Feel free to declare your own variables here */

void game_init(void)
{
    CP_System_SetFrameRate(30);
    /* Initialization of your other variables here */
    CP_System_Fullscreen();
    InitializeVariables();
    LoadBackgroundImage();
    LoadFont();
}

void game_update(void)
{
	TerminateFullscreen();

	FullscreenKeyPressed();

	FullscreenMode();

	DrawGameCanvas();

	DrawMenuButton();

	DrawMenuCanvas();

	ButtonClicked();
}

void game_exit(void)
{

}
