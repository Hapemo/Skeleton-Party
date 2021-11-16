
#include <stdlib.h>
#include <stdio.h>
#include "cprocessing.h"
#include "game.h"

struct spawn {
	CP_Vector position;
	float time;
	int type;
};

struct Enemy enemy_pool[MAX_ENEMY] = { 0 };
struct Enemy* to_enemy_pool = enemy_pool;

struct spawn spawn_pool[MAX_ENEMY] = { 0 };

struct Enemy enemy_set(CP_Vector position, int alive, float size, int type) {
	struct Enemy temp = { position, alive, size, type};
	return temp;
}
struct spawn spawn_set(CP_Vector position, float time, int type) {
	struct spawn temp = { position, time, type };
	return temp;
}

void preload_spawn_map(void) { //Put in game_init
	CP_Vector line_1 = CP_Vector_Set(WIDTH / 4, 0);
	spawn_pool_assigner(line_1, 20.0f, 15.0f, 20, 1);

	CP_Vector line_2 = CP_Vector_Set(WIDTH / 8, 0);
	spawn_pool_assigner(line_2, 20.0f, 200.0f, 20, 1);

	CP_Vector line_3 = CP_Vector_Set(WIDTH / 16, 0);
	spawn_pool_assigner(line_3, 20.0f, 50.0f, 20, 1);

	CP_Vector line_4 = CP_Vector_Set(WIDTH / 32, 0);
	spawn_pool_assigner(line_4, 20.0f, 400.0f, 20, 1);

	CP_Vector line_5 = CP_Vector_Set(WIDTH/1.5f, 0);
	spawn_pool_assigner(line_5, 20.0f, 20.0f, 20, 2);
}

void spawn_pool_assigner(CP_Vector position, float spawn_speed_delay, float start_spawn_tick, int spawn_amount, int type) {
	float spawn_tick = start_spawn_tick;

	int start_count = 0;
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (spawn_pool[i].type) continue;
		start_count = i;
		break;
	}

	for (int i = start_count; i < start_count + spawn_amount; i++) {
		spawn_tick = spawn_tick + spawn_speed_delay;
		spawn_pool[i] = spawn_set(position, spawn_tick, type);
	}
}

void spawn_map(void) { //Should run continuously

	/*for (int i = 0; i < 100; i++) {
		printf("spawn_pool position: %f | %f, time: %f\n", spawn_pool[i].position.x, spawn_pool[i].position.y, spawn_pool[i].time);
	}*/

	for (int i = 0; i < MAX_ENEMY; i++) {
		if (spawn_pool[i].time == *tick) {
			//printf("time: %f | tick: %f\n", spawn_pool[i].time, *tick);
			switch (spawn_pool[i].type) {
				case 1:
					initialise_basic_movement(spawn_pool[i].position, 1);
					break;
				case 2:
					initialise_basic_movement(spawn_pool[i].position, 2);
					break;
				case 3:
					initialise_basic_movement(spawn_pool[i].position, 3);
					break;
			}

		}
	}
}

//----------------- Initialise Enemy ------------------
void initialise_basic_movement(CP_Vector position, int type) {
	float enemy_size = WIDTH/25;
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (enemy_pool[i].alive) continue;
		enemy_pool[i] = enemy_set(position, 1, enemy_size, type);
		//printf("enemy %d position: %f|%f\n", i, enemy_pool[i].position.x, enemy_pool[i].position.y);
		break;
	}
}

//------------------ Enemy Patterns ------------------- (Should run continously in game_update)
void movement_pattern_vertical_and_diagonal(void) {
	CP_Settings_Fill(COLOR_BLUE);
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!(enemy_pool[i].alive)) continue;
		enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, DOWN); //Updates position

		switch (enemy_pool[i].type) {
			case 2:
				enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, LEFT); //Updates position
				break;
			case 3:
				enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, RIGHT); //Updates position
				break;
		}

		CP_Graphics_DrawCircle(enemy_pool[i].position.x, enemy_pool[i].position.y, enemy_pool[i].size * 2); //Prints enemy
	}
}




//int imageIndex;
//static CP_Image EnemyspriteSheetImage;
//
//#define DROPSPEED 2.0f
//static const float Enemy_FRAME_DIMENSIONx = 59.0f;
//static const float Enemy_FRAME_DIMENSIONy = 59.0f;
//static  float Enemy_size_windowsx;
//static  float Enemy_size_windowsy;
//static float EnemylocationX;
//static float EnemylocationY;
////int ticks = 0;
//CP_Vector vector_from_starting, position, add_position, * p_vector_from_starting = &vector_from_starting, starting_position /*enemy_position*/;
//int movement_1_start = 1, spin = 0, * p_spin = &spin, spin_speed;
//float enemy_count, radius, enemy_speed_x, enemy_speed_y;
//CP_Vector e1, e2;
//CP_Vector rotate_vector(float scalar, float angle, CP_Vector unit_vector);
//int vector_1, vector_2;
//
//
//// Enemy decleration --------------------------------------------------------------------------
//
//
//
//EnemySprite* enemy[MAX_ENEMY] = { NULL }; // when used, if first one is null, all othjers will be set to 0 
//EnemySprite* enemycircle[MAX_ENEMY][ShapeSizecircle] = { NULL };
//EnemySprite* enemyline[MAX_ENEMY][ShapeSizeline] = { NULL };
//
//void addEnemy(float x, float y, float dx)
//{
//	int found = -1;
//	for (int i = 0; i < MAX_ENEMY; i++)
//	{
//		if (enemy[i] == NULL)
//		{
//			found = i;
//			break;
//		}
//	}
//
//	if (found >= 0)
//	{
//		enemy[found] = malloc(sizeof(enemy));
//		enemy[found]->x = x;
//		enemy[found]->y = y;
//		enemy[found]->dx = dx;
//	}
//}
//
//void removeEnemy(int i)
//{
//
//	if (enemy[i] == NULL)
//	{
//		free(enemy[i]);
//		enemy[i] = NULL;
//	}
//
//	if (enemycircle[i][0] == NULL)
//	{
//		for (int p = 0; p < ShapeSizecircle; p++)
//		{
//			free(enemycircle[i][p]);
//			enemycircle[i][p] = NULL;
//		}
//	}
//}
//
//void cycleEnemyRemove(void)
//{
//	for (int a = 0; a < MAX_ENEMY; a++)
//	{
//		// add if statement to choose the shape 
//		removeEnemy(a);
//	}
//}
//
//void Enemy_printer(void)
//{
//
//	imageIndex = 0;
//	imageIndex = (imageIndex + 1) % 1; // decides which spritte to take on the sheet, adjust hard coded initialising at the top 
//
//	//spriteSheetImage = CP_Image_Load("./Assets/HeartSptite.png");
//	for (int y = 0; y < MAX_ENEMY; y++)
//	{
//		//single printer
//		if (enemy[y] != NULL) {
//			CP_Image_DrawSubImage(EnemyspriteSheetImage, // image used 
//				enemy[y]->x, enemy[y]->y, // coordinates of where the sprite is drawn
//				Enemy_size_windowsx, Enemy_size_windowsy,   // image size on window 
//				imageIndex * Enemy_FRAME_DIMENSIONx, 0, // image selection  by parts. first image = 0 + 1 % 4 = 1, second image = 1 + 1 % 4 = 2, third image = 2 + 1 % 4 = 3 , forth image = 3+1 % 4 = 0 
//				// image 4 / 4 is the first one on the sprite sheet
//				// horizontal movement, vertical movement
//				// frame diemnsion is 1 sprite on the sprite sheet
//				// left most pixel, top most pixel (top left corner )
//				Enemy_FRAME_DIMENSIONx, Enemy_FRAME_DIMENSIONy, // right most pixel, bottom most pixel (bottom right corner )
//				255); // alpha value that affects transpaarency
//		}
//		//circle printer
//		if (enemycircle[y][0] != NULL) {
//			float angle = 0;
//			//spin = 0;
//			for (int p = 0; p < ShapeSizecircle; p++)
//			{
//				if (enemycircle[y][p]->x == 0 && enemycircle[y][p]->y == 0) continue;
//				CP_Vector mid_position = CP_Vector_Set(enemycircle[y][p]->x, enemycircle[y][p]->y);
//				CP_Vector enemy_direction = rotate_vector(radius, angle + *p_spin, e1); // causes rotation 
//				CP_Vector enemy_position = CP_Vector_Add(mid_position, enemy_direction); // affine P hat 
//				// make mini enemy sprite next time
//				CP_Image_DrawSubImage(EnemyspriteSheetImage, // image used 
//					/*enemycircle[y][p]->x, enemycircle[y][p]->y,*/
//					enemy_position.x, enemy_position.y, // coordinates of where the sprite is drawn
//					ENEMY_SIZE_2, ENEMY_SIZE_2,   // image size on window 
//					imageIndex * Enemy_FRAME_DIMENSIONx, 0, // image selection  by parts. first image = 0 + 1 % 4 = 1, second image = 1 + 1 % 4 = 2, third image = 2 + 1 % 4 = 3 , forth image = 3+1 % 4 = 0 
//					// image 4 / 4 is the first one on the sprite sheet
//					// horizontal movement, vertical movement
//					// frame diemnsion is 1 sprite on the sprite sheet
//					// left most pixel, top most pixel (top left corner )
//					Enemy_FRAME_DIMENSIONx, Enemy_FRAME_DIMENSIONy, // right most pixel, bottom most pixel (bottom right corner )
//					255); // alpha value that affects transpaarency
//				angle += 360.0f / ShapeSizecircle;
//			}
//			*p_spin += spin_speed;
//		}
//	}
//
//	//CP_Image_Free(&spriteSheetImage);
//}
//
//void movement_1(float x, float y, float C_radius) {
//	//if (movement_1_start) {
//	e1 = CP_Vector_Set(-1, 0);
//	e2 = CP_Vector_Set(0, 1);
//	//For general 
//	starting_position = CP_Vector_Set(x, y); // starting position x,y for now cp get mouse coord
//	position = starting_position;
//	//movement_1_start = 0;
//	vector_from_starting = e2;
//
//	//For enemy_moving_down
//	enemy_speed_y = 2;
//	enemy_speed_x = 10;
//	vector_1 = 2; //1 = up, 2 = down, 3 = left, 4 = right  // direction 
//	vector_2 = 3;
//
//	//For enemy_pattern_circle
//	radius = C_radius;
//	spin_speed = 2;
//	//}
//
//}
//
//
//CP_Vector Enemy_rotate_vector(float scalar, float angle, CP_Vector unit_vector) {
//	CP_Vector vector = CP_Vector_Scale(unit_vector, scalar);
//
//	CP_Matrix rotate = CP_Matrix_Rotate(angle);
//
//	vector = CP_Vector_MatrixMultiply(rotate, vector);
//
//	return vector;
//}
//
//void enemy_pattern_circle(CP_Vector mid_position, float big_radius, int speed, int enemynum) { //Update
//	float angle = 0;
//	for (int i = 0; i < ShapeSizecircle; i++) { // each i is one enemy 
//		if (enemycircle[enemynum][i]->x == 0 && enemycircle[enemynum][i]->y == 0) continue;
//		CP_Vector enemy_direction = Enemy_rotate_vector(big_radius, angle + *p_spin, e1); // causes rotation 
//		CP_Vector enemy_position = CP_Vector_Add(mid_position, enemy_direction); // affine P hat 
//		enemycircle[enemynum][i]->x = enemy_position.x;
//		enemycircle[enemynum][i]->y = enemy_position.y;
//
//		angle += 360.0f / ShapeSizecircle; // angle increment for next enemy 
//	}
//	*p_spin += speed; // speed of rotation
//}
//
//void addenemy_pattern_circle(CP_Vector mid_position, float big_radius, int speed) { //Initialise
//	float angle = 0;
//	//printf("enemycircle added\n");
//	//int groupchecker=0, groupavailable=0;
//	int found = -1;
//	for (int i = 0; i < MAX_ENEMY; i++)
//	{
//		if (enemycircle[i][0] == NULL)
//		{
//			found = i;
//			break;
//		}
//	}
//	if (found >= 0)
//	{
//		for (unsigned int p = 0; p < ShapeSizecircle; p++) { // each i is one enemy 
//			CP_Vector enemy_direction = Enemy_rotate_vector(big_radius, angle + *p_spin, e1); // causes rotation 
//			CP_Vector enemy_position = CP_Vector_Add(mid_position, enemy_direction); // affine P hat 
//
//			enemycircle[found][p] = (EnemySprite*)malloc(sizeof(enemycircle));
//			enemycircle[found][p]->x = enemy_position.x;
//			enemycircle[found][p]->y = enemy_position.y;
//			enemycircle[found][p]->dx = DROPSPEED;
//			//printf("enemycircle added at %f\n", enemycircle[found][p]->y);
//
//			// add enemy needs 1 more identifer 
//			// need to chain up with my enemy printer 
//			//print_enemy(enemy_position);
//			angle += 360.0f / ShapeSizecircle; // angle increment for next enemy 
//		}
//		*p_spin += spin_speed; // speed of rotation
//	}
//}
//
//void init_EnemySprite(void)
//{
//	EnemyspriteSheetImage = CP_Image_Load("./Assets/Enemydot.png");
//
//	Enemy_size_windowsx = (CP_System_GetWindowWidth()) / 20.0f;
//	Enemy_size_windowsy = (CP_System_GetWindowHeight()) / 20.0f;
//	EnemylocationX = 0.f;
//	EnemylocationY = 0.f;
//}
//
//
//void SpawnEnemyCircle(float Positionx, float Positiony)
//{
//	add_position = CP_Vector_Set(Positionx, Positiony);
//	addenemy_pattern_circle(add_position, radius, spin_speed);
//	movement_1(Positionx, Positiony, (Enemy_size_windowsx / 2));
//}
//
//void SpawnEnemySingle(float Positionx, float Positiony)
//{
//	addEnemy(Positionx, Positiony, DROPSPEED);
//}
//
//void UpdateEnemyMovement(void)
//{
//	for (int i = 0; i < MAX_ENEMY; i++)
//	{
//		//update for single
//		if (enemy[i] != NULL)
//		{
//			enemy[i]->y += enemy[i]->dx;
//			if (enemy[i]->y < -1000 || enemy[i]->y >1000)
//			{
//				//printf("enemylocation Exceeded\n");
//				enemy[i] = NULL;
//				removeEnemy(i); // might change to removeenemy once if statement added
//			}
//		}
//
//		//update for circle 
//		if (enemycircle[i][0] != NULL)
//		{
//			// add player homing here 
//			for (int p = 0; p < ShapeSizecircle; p++)
//			{
//				if (enemycircle[i][p]->x == 0 && enemycircle[i][p]->y == 0) continue;
//				enemycircle[i][p]->y += enemycircle[i][p]->dx;
//			}
//
//			CP_Vector current_enemy = CP_Vector_Set(enemycircle[i][ShapeSizecircle - 1]->x, enemycircle[i][ShapeSizecircle - 1]->y);
//			
//			if (out_of_screen(current_enemy))
//			{
//				//printf("enemylocation Exceeded\n");
//				enemycircle[i][0] = NULL;
//				removeEnemy(i); // might change to removeenemy once if statement added
//
//			}
//		}
//	}
//}
//
//void exit_EnemySprite(void)
//{
//	CP_Image_Free(&EnemyspriteSheetImage);
//}
