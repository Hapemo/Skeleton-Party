/*---------------------------------------------------------
 file:	qh.c
 author:	qiuhui tan
 email:	qiuhui.tan@digipen.edu

 brief:	This file contains struct for character and functions for game controls 
 and rendering of various characters. 
*
 documentation link:
 https://inside.digipen.edu/main/GSDP:GAM100/CProcessing

* Copyright © 2020 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include <stdio.h>
#include "cprocessing.h"
#include "game.h"



//struct character
//{
//    CP_Vector position;
//    CP_Image sprite;
//    float width;
//    float height;
//    float speed;
//
//};




//@purpose enemy movement 
float Lerp(float start, float end, float percentage)
{
    return ((1.f - percentage) * start + (percentage * end));
}


//@purpose spawn sprite
void init_char(struct character *spritename, float spawnx, float spawny, char* pathname)
{
    spritename->position = CP_Vector_Set(spawnx, spawny);
    spritename->sprite = CP_Image_Load(pathname);
    spritename->width = 50;
    spritename->height = 100;
    spritename->speed = 200;
    spritename->transparency = 255;
    
}


//@purpose sprite character switching
void update_char(int CurrentCharacter, struct character* spritename)
{
    
    if (CurrentCharacter == knightint)
    {
        //if (knight.invulnerability && ((int)*tick %20 >10)) spritename->sprite = CP_Image_Load("./Assets/knightpaRED.png");
        spritename->sprite = CP_Image_Load("./Assets/knightpa.png");
    }
    else if (CurrentCharacter == mageint)
    {
        
        spritename->sprite = CP_Image_Load("./Assets/magepa.png");

    }
    else if (CurrentCharacter == archerint)
    {
        spritename->sprite = CP_Image_Load("./Assets/archerpa.png");
    }
}


void begintext(void)
{
    float x = (float)CP_System_GetWindowWidth() / 2;
    float y = (float)CP_System_GetWindowHeight() / 2;
    CP_Settings_Fill(COLOR_WHITE);
    CP_Graphics_DrawRect((x / 2), (y / 2), x, y);
    CP_Settings_Fill(COLOR_BLACK);
    CP_Font_DrawText("Welcome to the skeleton party, please save our princess!", ((x / 2) - 50), ((y / 2) - 50));
}

void endtext(void)
{
    float x = (float)CP_System_GetWindowWidth() / 2;
    float y = (float)CP_System_GetWindowHeight() / 2;
    CP_Settings_Fill(COLOR_WHITE);
    CP_Graphics_DrawRect((x / 2), (y / 2), x, y);
    CP_Settings_Fill(COLOR_BLACK);
    CP_Font_DrawText("Thank you for saving our princess! ", ((x / 2) - 50), ((y / 2) - 50));
}

//@purpose sprite movement control in game
void game_control(struct character *spritename )
{
    
    if (CP_Input_KeyDown(KEY_W))
    {
        spritename->position.y -= CP_System_GetDt() * spritename->speed;
    }

    if (CP_Input_KeyDown(KEY_A))
    {
        spritename->position.x -= CP_System_GetDt() * spritename->speed;
    }

    if (CP_Input_KeyDown(KEY_S))
    {
        spritename->position.y += CP_System_GetDt() * spritename->speed;
    }

    if (CP_Input_KeyDown(KEY_D))
    {
        spritename->position.x += CP_System_GetDt() * spritename->speed;
    }

    if (spritename->position.x < 0)
    {
        spritename->position.x = 0;
    }
    else if (spritename->position.x >  CP_System_GetWindowWidth())
    {
        spritename->position.x = (float) CP_System_GetWindowWidth();
    }

    if (spritename->position.y < 0)
    {
        spritename->position.y = 0;
    }
    else if (spritename->position.y > CP_System_GetWindowHeight())
    {
        spritename->position.y = (float)CP_System_GetWindowHeight();
    }
   
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 0));
    CP_Image_Draw(spritename->sprite, spritename->position.x, spritename->position.y, spritename->width, spritename->height, spritename->transparency);
}

void drawenemy(struct character* spritename)
{
    CP_Image_Draw(spritename->sprite, spritename->position.x, spritename->position.y, spritename->width, spritename->height, 255);
}
