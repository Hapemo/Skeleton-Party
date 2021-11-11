
#include <stdio.h>
#include "cprocessing.h"

//#define speed 400 
struct character
{
    CP_Vector position;
    CP_Image sprite;
    float width;
    float height;
    float speed;

};




void init_char(struct character *spritename, float spawnx, float spawny, char* pathname)
{
    spritename->position = CP_Vector_Set(spawnx, spawny);
    spritename->sprite = CP_Image_Load(pathname);
    spritename->width = 200;
    spritename->height = 200;
    spritename->speed = 100;

}

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
    CP_Image_Draw(spritename->sprite, spritename->position.x, spritename->position.y, spritename->width, spritename->height, 255);
}
