
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
    spritename->width = 50;
    spritename->height = 100;
    spritename->speed = 100;

}

/*void enemypattern1(void)
{
    struct character enemy;
    
    float x = CP_System_GetWindowWidth() / 3;
    float y = CP_System_GetWindowHeight() / 3;
    for (int i = 0; i < 3; i++)
    {
        init_char(enemy, (x+(x*i)), (y+(y*i)), "./Assets/Enemydot.png");
        
    }
}
*/

void begintext(void)
{
    float x = (float)CP_System_GetWindowWidth() / 2;
    float y = (float)CP_System_GetWindowHeight() / 2;
    //color fill
    CP_Graphics_DrawRect((x / 2), (y / 2), x, y);
    CP_Font_DrawText("Welcome to the skeleton party, please save our princess!", ((x / 2) - 50), ((y / 2) - 50));
}

void endtext(void)
{
    float x = (float)CP_System_GetWindowWidth() / 2;
    float y = (float)CP_System_GetWindowHeight() / 2;
    //color fill
    CP_Graphics_DrawRect((x / 2), (y / 2), x, y);
    CP_Font_DrawText("Thank you for saving our princess! ", ((x / 2) - 50), ((y / 2) - 50));
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
