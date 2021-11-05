

#include <stdlib.h>
#include <stdio.h>
#include "cprocessing.h"
#include "game.h"


#define MAX_ENEMY 500

static CP_Image spriteSheetImage;
static CP_Image EnemyspriteSheetImage;

static const float Enemy_FRAME_DIMENSIONx = 59.0f;
static const float Enemy_FRAME_DIMENSIONy = 59.0f;

static  float Enemy_size_windowsx;
static  float Enemy_size_windowsy;

static int imageIndex;

static float EnemylocationX;
static float EnemylocationY;

typedef struct Enemy
{
    float x, y, dx; // where dx is the velocity 
}Enemy;

// enemy data and pos will be stored in array of pointers
Enemy* enemy[MAX_ENEMY] = { NULL }; // when used, if first one is null, all othjers will be set to 0 

void addEnemy(float x, float y, float dx)
{
    //("enemyadded\n");
    // go through array to look for first avai enemy stored 
    int found = -1;
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (enemy[i] == NULL)
        {
            found = i;
            break;
        }
    }
    // if found, use the enemy storage
    if (found >= 0)
    {
        //printf("enemyfound\n");

        enemy[found] = malloc(sizeof(enemy));
        enemy[found]->x = x;
        enemy[found]->y = y;
        enemy[found]->dx = dx;

    }
}

void removeEnemy(int i)
{

    if (enemy[i] == NULL)
    {
        free(enemy[i]);
        enemy[i] = NULL;
    }
}

void cycleEnemyRemove(void)
{
    for (int a = 0; a < MAX_ENEMY; a++)
    {
        removeEnemy(a);
    }
}
void Enemy_printer(void)
{

    imageIndex = 0;
    imageIndex = (imageIndex + 1) % 1; // decides which spritte to take on the sheet, adjust hard coded initialising at the top 

    //spriteSheetImage = CP_Image_Load("./Assets/HeartSptite.png");
    for (int y = 0; y < MAX_ENEMY; y++)
    {
        if (enemy[y] != NULL) {
            CP_Image_DrawSubImage(EnemyspriteSheetImage, // image used 
                enemy[y]->x, enemy[y]->y, // coordinates of where the sprite is drawn
                Enemy_size_windowsx, Enemy_size_windowsy,   // image size on window 
                imageIndex * Enemy_FRAME_DIMENSIONx, 0, // image selection  by parts. first image = 0 + 1 % 4 = 1, second image = 1 + 1 % 4 = 2, third image = 2 + 1 % 4 = 3 , forth image = 3+1 % 4 = 0 
                // image 4 / 4 is the first one on the sprite sheet
                // horizontal movement, vertical movement
                // frame diemnsion is 1 sprite on the sprite sheet
                // left most pixel, top most pixel (top left corner )
                Enemy_FRAME_DIMENSIONx, Enemy_FRAME_DIMENSIONy, // right most pixel, bottom most pixel (bottom right corner )
                255); // alpha value that affects transpaarency
        }
    }

    //CP_Image_Free(&spriteSheetImage);
}


void somethingelse(void) {
    EnemyspriteSheetImage = CP_Image_Load("./Assets/Enemydot.png");

    Enemy_size_windowsx = (CP_System_GetWindowWidth()) / 20.0f;
    Enemy_size_windowsy = (CP_System_GetWindowHeight()) / 20.0f;
    EnemylocationX = 0.f;
    EnemylocationY = 0.f;
}

//insert to game update
void something(void){
    EnemylocationX = CP_Input_GetMouseX();
    EnemylocationY = CP_Input_GetMouseY();

    if (CP_Input_MouseTriggered(MOUSE_BUTTON_2))
    {

        addEnemy(CP_Input_GetMouseX() + (float)40.0, CP_Input_GetMouseY() + (float)15.0, (float)5.0);

    }

    for (int i = 0; i < MAX_ENEMY; i++) {


        if (enemy[i] != NULL)// if (enemy[i])
        {
            // add player homing here 
            //printf("updated enemy locatrion\n");

            enemy[i]->x += enemy[i]->dx;

            printf("enenmy %d x location is %f\n", i, enemy[i]->x);


            if (enemy[i]->x < -1000 || enemy[i]->x >1000)
            {
                //printf("enemylocation Exceeded\n");
                enemy[i] = NULL;
                removeEnemy(i);
            }
        }
    }

    Enemy_printer();
    cycleEnemyRemove();
}