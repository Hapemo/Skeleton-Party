
#include <stdlib.h>
#include <stdio.h>
#include "cprocessing.h"
#include "game.h"
//
//
//#define MAX_ENEMY 500
//
//static CP_Image spriteSheetImage;
//static CP_Image EnemyspriteSheetImage;
//
//static const float Enemy_FRAME_DIMENSIONx = 59.0f;
//static const float Enemy_FRAME_DIMENSIONy = 59.0f;
//
//static  float Enemy_size_windowsx;
//static  float Enemy_size_windowsy;
//
//static int imageIndex;
//
//static float EnemylocationX;
//static float EnemylocationY;
//
//typedef struct Enemy
//{
//    float x, y, dx; // where dx is the velocity 
//}Enemy;
//
//// enemy data and pos will be stored in array of pointers
//Enemy* enemy[MAX_ENEMY] = { NULL }; // when used, if first one is null, all othjers will be set to 0 
//
//void addEnemy(float x, float y, float dx)
//{
//    //("enemyadded\n");
//    // go through array to look for first avai enemy stored 
//    int found = -1;
//    for (int i = 0; i < MAX_ENEMY; i++)
//    {
//        if (enemy[i] == NULL)
//        {
//            found = i;
//            break;
//        }
//    }
//    // if found, use the enemy storage
//    if (found >= 0)
//    {
//        //printf("enemyfound\n");
//
//        enemy[found] = malloc(sizeof(enemy));
//        enemy[found]->x = x;
//        enemy[found]->y = y;
//        enemy[found]->dx = dx;
//
//    }
//}
//
//void removeEnemy(int i)
//{
//
//    if (enemy[i] == NULL)
//    {
//        free(enemy[i]);
//        enemy[i] = NULL;
//    }
//}
//
//void cycleEnemyRemove(void)
//{
//    for (int a = 0; a < MAX_ENEMY; a++)
//    {
//        removeEnemy(a);
//    }
//}
//void Enemy_printer(void)
//{
//
//    imageIndex = 0;
//    imageIndex = (imageIndex + 1) % 1; // decides which spritte to take on the sheet, adjust hard coded initialising at the top 
//
//    //spriteSheetImage = CP_Image_Load("./Assets/HeartSptite.png");
//    for (int y = 0; y < MAX_ENEMY; y++)
//    {
//        if (enemy[y] != NULL) {
//            CP_Image_DrawSubImage(EnemyspriteSheetImage, // image used 
//                enemy[y]->x, enemy[y]->y, // coordinates of where the sprite is drawn
//                Enemy_size_windowsx, Enemy_size_windowsy,   // image size on window 
//                imageIndex * Enemy_FRAME_DIMENSIONx, 0, // image selection  by parts. first image = 0 + 1 % 4 = 1, second image = 1 + 1 % 4 = 2, third image = 2 + 1 % 4 = 3 , forth image = 3+1 % 4 = 0 
//                // image 4 / 4 is the first one on the sprite sheet
//                // horizontal movement, vertical movement
//                // frame diemnsion is 1 sprite on the sprite sheet
//                // left most pixel, top most pixel (top left corner )
//                Enemy_FRAME_DIMENSIONx, Enemy_FRAME_DIMENSIONy, // right most pixel, bottom most pixel (bottom right corner )
//                255); // alpha value that affects transpaarency
//        }
//    }
//
//    //CP_Image_Free(&spriteSheetImage);
//}
//
//
//// insert movement here below 
//
//CP_Vector vector_from_starting, position, * p_vector_from_starting = &vector_from_starting, starting_position;
//int movement_1_start = 1, spin = 0, * p_spin = &spin, spin_speed;
//float enemy_count, radius, enemy_speed_x, enemy_speed_y;
//CP_Vector e1, e2;
//
//
//int vector_1, vector_2;
//void movement_1(void) {
//    if (movement_1_start) {
//        e1 = CP_Vector_Set(-1, 0);
//        e2 = CP_Vector_Set(0, 1);
//        //For general 
//        starting_position = CP_Vector_Set(WIDTH / 2, 0);
//        position = starting_position;
//        movement_1_start = 0;
//        vector_from_starting = e2;
//
//        //For enemy_moving_down
//        enemy_speed_y = 2;
//        enemy_speed_x = 10;
//        vector_1 = 2; //1 = up, 2 = down, 3 = left, 4 = right
//        vector_2 = 3;
//
//        //For enemy_pattern_circle
//        enemy_count = 5, radius = 50;
//        spin_speed = 2;
//    }
//
//    position = enemy_moving_up_down_left_right(position, p_vector_from_starting, enemy_speed_y, vector_1);
//
//    position = enemy_moving_up_down_left_right(position, p_vector_from_starting, enemy_speed_y, vector_2);
//
//    enemy_pattern_circle(position, enemy_count, radius, spin_speed);
//
//    printf("position x|y: %f|%f\nheight: %f\n\n", position.x, position.y, HEIGHT);
//    if (position.x > WIDTH || position.y > HEIGHT) {
//        position = starting_position;
//    }
//}
//
//void enemy_pattern_circle(CP_Vector mid_position, float enemy_number, float big_radius, int speed) {
//    float angle = 0;
//    for (int i = 0; i < enemy_count; i++) {
//        CP_Vector enemy_direction = rotate_vector(big_radius, angle + *p_spin, e1);
//        CP_Vector enemy_position = CP_Vector_Add(mid_position, enemy_direction);
//
//        print_enemy(enemy_position);
//        angle += 360.0f / enemy_count;
//    }
//    *p_spin += speed;
//}
//
//int ticks = 0;
//int tick(void) {
//    ticks++;
//    if (ticks == INT_MAX) ticks = 0;
//    return ticks;
//}
//
//void backnforth_multiplier(void) {
//
//}
//
//CP_Vector enemy_moving_up_down_left_right(CP_Vector enemy_current, CP_Vector* vector, float velocity_scale, int direction) {
//    switch (direction) {
//    case 1:
//        enemy_current.y -= velocity_scale;
//        break;
//    case 2:
//        enemy_current.y += velocity_scale;
//        break;
//    case 3:
//        enemy_current.x -= velocity_scale;
//        break;
//    case 4:
//        enemy_current.x += velocity_scale;
//        break;
//    }
//    return enemy_current;
//}
//
////insert movement here above 
//
//
//void somethingelse(void) { // init
//    EnemyspriteSheetImage = CP_Image_Load("./Assets/Enemydot.png");
//
//    Enemy_size_windowsx = (CP_System_GetWindowWidth()) / 20.0f;
//    Enemy_size_windowsy = (CP_System_GetWindowHeight()) / 20.0f;
//    EnemylocationX = 0.f;
//    EnemylocationY = 0.f;
//}
//
////insert to game update
//void something(void){
//    EnemylocationX = CP_Input_GetMouseX();
//    EnemylocationY = CP_Input_GetMouseY();
//
//    if (CP_Input_MouseTriggered(MOUSE_BUTTON_2))
//    {
//
//        addEnemy(CP_Input_GetMouseX() + (float)40.0, CP_Input_GetMouseY() + (float)15.0, (float)5.0);
//
//    }
//
//    for (int i = 0; i < MAX_ENEMY; i++) {
//
//
//        if (enemy[i] != NULL)// if (enemy[i])
//        {
//            // add player homing here 
//            //printf("updated enemy locatrion\n");
//
//            enemy[i]->x += enemy[i]->dx;
//
//            printf("enenmy %d x location is %f\n", i, enemy[i]->x);
//
//
//            if (enemy[i]->x < -1000 || enemy[i]->x >1000)
//            {
//                //printf("enemylocation Exceeded\n");
//                enemy[i] = NULL;
//                removeEnemy(i);
//            }
//        }
//    }
//
//    Enemy_printer();
//    cycleEnemyRemove();
//}
//// exit
//void erferfrefer(void)
//{
//    CP_Image_Free(&EnemyspriteSheetImage);
//
//}