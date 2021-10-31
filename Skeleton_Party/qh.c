
#include <stdio.h>
#include "cprocessing.h"

#define speed 400 
struct character
{
    CP_Vector position;
    CP_Image sprite;

};

struct character knight;

void init_char(void)
{
    knight.position = CP_Vector_Set(200, 200);
    knight.sprite = CP_Image_Load("./Assets/unknown.jpeg");
}

void game_control(void)
{

    if (CP_Input_KeyDown(KEY_W))
    {
        knight.position.y -= CP_System_GetDt() * speed;
    }

    if (CP_Input_KeyDown(KEY_A))
    {
        knight.position.x -= CP_System_GetDt() * speed;
    }

    if (CP_Input_KeyDown(KEY_S))
    {
        knight.position.y += CP_System_GetDt() * speed;
    }

    if (CP_Input_KeyDown(KEY_D))
    {
        knight.position.x += CP_System_GetDt() * speed;
    }

    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 0));
    CP_Image_Draw(knight.sprite, knight.position.x, knight.position.y, 200, 200, 255);
}
