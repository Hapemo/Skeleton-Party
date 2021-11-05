
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

struct character knight;
struct character enemey;

void init_char(void)
{
    knight.position = CP_Vector_Set(200, 200);
    knight.sprite = CP_Image_Load("./Assets/unknown.jpeg");
    knight.width = 200;
    knight.height = 200;
    knight.speed = 100;
}

void game_control(void)
{

    if (CP_Input_KeyDown(KEY_W))
    {
        knight.position.y -= CP_System_GetDt() * knight.speed;
    }

    if (CP_Input_KeyDown(KEY_A))
    {
        knight.position.x -= CP_System_GetDt() * knight.speed;
    }

    if (CP_Input_KeyDown(KEY_S))
    {
        knight.position.y += CP_System_GetDt() * knight.speed;
    }

    if (CP_Input_KeyDown(KEY_D))
    {
        knight.position.x += CP_System_GetDt() * knight.speed;
    }

    if (knight.position.x < 0)
    {
        knight.position.x = 0;
    }
    else if (knight.position.x >  CP_System_GetWindowWidth())
    {
        knight.position.x = (float) CP_System_GetWindowWidth();
    }

    if (knight.position.y < 0)
    {
        knight.position.y = 0;
    }
    else if (knight.position.y > CP_System_GetWindowHeight())
    {
        knight.position.y = (float)CP_System_GetWindowHeight();
    }
   
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 0));
    CP_Image_Draw(knight.sprite, knight.position.x, knight.position.y, knight.width, knight.height, 255);
}
