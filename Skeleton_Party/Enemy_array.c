
#include <stdlib.h>
#include <stdio.h>
#include "cprocessing.h"
#include "game.h"

#define ENEMY_SIZE 20.0f
#define ENEMY_CIRCLE_COUNT 10
#define ENEMY_SPEED 5

struct Enemy enemy_pool[MAX_ENEMY] = { 0 };
struct spawn spawn_pool[MAX_ENEMY] = { 0 };
struct mother_enemy mother_enemy_pool[MAX_MOTHER_ENEMY] = { 0 };

struct Enemy enemy_set(CP_Vector position, int alive, float size, int type) {
	struct Enemy temp = { position, alive, size, type};
	return temp;
}
struct spawn spawn_set(CP_Vector position, float time, int type) {
	struct spawn temp = { position, time, type };
	return temp;
}
struct mother_enemy mother_enemy_set(CP_Vector position, float time, int alive, int type) {
	struct mother_enemy temp = { position, time, alive, type, 0};
	return temp;
}

//1 for straight line, 2 for left diagonal, 3 for right diagonal, 5 for horizontal enemy, 101 for circle
//Max screen is WDITH/1.5

void preload_spawn_map(void) { //Put in game_init
	//first wave
	CP_Vector line_1 = CP_Vector_Set(WIDTH/3, -5);
	spawn_pool_assigner(line_1, 50.0f, 50.0f, 30, 1);

	CP_Vector line_2 = CP_Vector_Set(((WIDTH/3)+50), -5);
	spawn_pool_assigner(line_2, 50.0f, 10.0f, 30, 1);

	CP_Vector line_3 = CP_Vector_Set(((WIDTH / 3) -50), -5);
	spawn_pool_assigner(line_3, 50.0f, 50.0f, 30, 1);

	CP_Vector line_4 = CP_Vector_Set(((WIDTH / 3) + 100), -5);
	spawn_pool_assigner(line_4, 50.0f, 10.0f, 30, 1);
	

	//second wave
	CP_Vector line_5 = CP_Vector_Set(-180, -400);
	spawn_pool_assigner(line_5, 20.0f, 100.0f, 50, 5);

	CP_Vector line_6 = CP_Vector_Set(((WIDTH / 4) + 50), -400);
	spawn_pool_assigner(line_6, 50.0f, 1600.0f, 50, 5);

	CP_Vector line_7 = CP_Vector_Set((WIDTH/4), -400);
	spawn_pool_assigner(line_7, 20.0f, 1600.0f, 50, 5);

	CP_Vector line_8 = CP_Vector_Set(((WIDTH/4) + 100), -400);
	spawn_pool_assigner(line_8, 50.0f, 1600.0f, 50, 5);

	//third wave
	CP_Vector line_9 = CP_Vector_Set((WIDTH / 2)+150, -400);
	spawn_pool_assigner(line_9, 20.0f, 4300.0f, 50, 101);

	CP_Vector line_10 = CP_Vector_Set(WIDTH / 2, -400);
	spawn_pool_assigner(line_10, 20.0f, 4300.0f, 3, 101);
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
					initialise_basic_movement(i);
					break;
				case 2:
					initialise_basic_movement(i);
					break;
				case 3:
					initialise_basic_movement(i);
					break;
				case 4:
					initialise_circle_shape(spawn_pool[i].position, 5, 100);
					break;
				case 5:
					initialise_horizontal_line(spawn_pool[i].position, 5, WIDTH/1.1f, 1);
					break;
				case 101:
					initialise_basic_movement(i);
					break;
			}

		}
	}
}

//----------------- Initialise Enemy ------------------
void initialise_basic_movement(int spawn_pool_i) {
	if (0 < spawn_pool[spawn_pool_i].type && spawn_pool[spawn_pool_i].type < 100) {
		for (int i = 0; i < MAX_ENEMY; i++) {
			if (enemy_pool[i].alive) continue;

			enemy_pool[i] = enemy_set(spawn_pool[spawn_pool_i].position, 1, ENEMY_SIZE, spawn_pool[spawn_pool_i].type);
			//printf("enemy %d position: %f|%f\n", i, enemy_pool[i].position.x, enemy_pool[i].position.y);
			break;
		}
	} else {
		for (int i = 0; i < MAX_MOTHER_ENEMY; i++) {
			if (mother_enemy_pool[i].alive) continue;

			mother_enemy_pool[i] = mother_enemy_set(spawn_pool[spawn_pool_i].position, spawn_pool[spawn_pool_i].time ,1, spawn_pool[spawn_pool_i].type);

			for (int j = 0; j < MAX_CHILDREN; j++) {
				mother_enemy_pool[i].children[j].alive = 1;
			}

			//printf("mother %d position: %f|%f, mother type: %d, mother alive: %d\n", i, mother_enemy_pool[i].position.x, mother_enemy_pool[i].position.y, mother_enemy_pool[i].type, mother_enemy_pool[i].alive);
			break;
		}
	}
}

void initialise_circle_shape(CP_Vector mid_position, int enemy_count, float radius) {
	float angle = 0;
	for (int i = 0; i < enemy_count; i++) {
		for (int j = 0; j < MAX_ENEMY; j++) {
			//printf("enemy_pool[%d] position: %f | %f, alive: %d, type: %d\n", enemy_pool[i].position.x, enemy_pool[i].position.y, enemy_pool[i].alive, enemy_pool[i].type);

			if (enemy_pool[j].alive) continue;

			CP_Vector enemy_direction = rotate_vector(radius, angle, E1);
			CP_Vector enemy_position = CP_Vector_Add(mid_position, enemy_direction);
			enemy_pool[j] = enemy_set(enemy_position, 1, ENEMY_SIZE, 4);
			angle += 360.0f / enemy_count;
			break;
		}
	}
}

void initialise_horizontal_line(CP_Vector start_position, int enemy_count, float end_of_horizontal, int type) {

	float total_distance_apart = end_of_horizontal - start_position.x;
	float distance_apart = total_distance_apart / enemy_count;
	CP_Vector position = start_position;
	
	for (int i = 0; i < enemy_count; i++) {
		for (int j = 0; j < MAX_ENEMY; j++) {
			if (enemy_pool[j].alive) continue;
			position.x += (distance_apart);
			enemy_pool[j] = enemy_set(position, 1, ENEMY_SIZE, type);
			printf("position of %d: %f|%f\n", i, position.x, position.y);
			//printf("enemy %d position: %f|%f\n", i, enemy_pool[i].position.x, enemy_pool[i].position.y);
			break;
		}
	}
}

//void initialise_advance_movement(CP_Vector position, int type) {
//	float ENEMY_SIZE = WIDTH / 25;
//	for (int i = 0; i < MAX_ENEMY; i++) {
//		if (enemy_pool[i].alive) continue;
//		enemy_pool[i] = enemy_set(position, 1, ENEMY_SIZE, type);
//		//printf("enemy %d position: %f|%f\n", i, enemy_pool[i].position.x, enemy_pool[i].position.y);
//		break;
//	}
//}

//------------------ Enemy Patterns ------------------- (Should run continously in game_update)
void movement_pattern_vertical_and_diagonal(void) {
	CP_Settings_Fill(COLOR_BLUE);
	for (int i = 0; i < MAX_ENEMY; i++) {

		enemy_out_of_screen(1,i);

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

		//CP_Graphics_DrawCircle(enemy_pool[i].position.x, enemy_pool[i].position.y, enemy_pool[i].size * 2); //Prints enemy
		print_enemy(enemy_pool[i].position, enemy_pool[i].size);
	}
}

void movement_pattern_spinning_circle(void) {
	CP_Settings_Fill(COLOR_BLUE);
	int children_alive;

	for (int i = 0; i < MAX_MOTHER_ENEMY; i++) {
		enemy_out_of_screen(0, i);
		if (!(mother_enemy_pool[i].alive)) continue;
		
		//Check if chilrens are alive in mother, to decide whether mother is dead or not
		children_alive = 0;
		for (int j = 0; j < MAX_CHILDREN; j++) {
			if (mother_enemy_pool[i].children[j].alive) {
				children_alive = 1;
				break;
			}
		}
		if (!(children_alive)) mother_enemy_pool[i].alive = 0;
		
		mother_enemy_pool[i].position = enemy_moving_up_down_left_right(mother_enemy_pool[i].position, ENEMY_SPEED, DOWN); //Updates position

		switch (mother_enemy_pool[i].type) {
			case 101:
				spin_enemy(i, ENEMY_CIRCLE_COUNT, 100, mother_enemy_pool[i].position);
				break;
		}
	}
}

void spin_enemy(int mother_i, int enemy_count, float radius, CP_Vector position) {
	float angle = 0;
	int spin_speed = 100;
	int randomizer = (int)mother_enemy_pool[mother_i].time % 36;
	if (randomizer != 0) angle = 360.0f / randomizer;

	for (int i = 0; i < enemy_count; i++) {
		//printf("this enemy's alive or dead state: %d\n", mother_enemy_pool[mother_i].children[i].alive);

		mother_enemy_pool[mother_i].spare += spin_speed;

		CP_Vector enemy_direction = rotate_vector(radius, angle + mother_enemy_pool[mother_i].spare, E1);
		CP_Vector enemy_position = CP_Vector_Add(position, enemy_direction);
		angle += 360.0f / enemy_count;
		mother_enemy_pool[mother_i].children[i].position = enemy_position;
		mother_enemy_pool[mother_i].children[i].size = ENEMY_SIZE;


		if (!(mother_enemy_pool[mother_i].children[i].alive)) continue;
		print_enemy(mother_enemy_pool[mother_i].children[i].position, mother_enemy_pool[mother_i].children[i].size);
		//CP_Graphics_DrawCircle(mother_enemy_pool[mother_i].children[i].position.x, mother_enemy_pool[mother_i].children[i].position.y, mother_enemy_pool[mother_i].children[i].size * 2); //Prints enemy
	}
}


void enemy_out_of_screen(int enemy_not_mother, int enemy_i) {
	if (enemy_not_mother == 1) {
		if (enemy_pool[enemy_i].position.y > HEIGHT * 1.1) {
			if (!(enemy_pool[enemy_i].alive)) return;
			enemy_pool[enemy_i].alive = 0;
			printf("normal enemy out of screen!\n");
		}
	} else {
		for (int i = 0; i < MAX_CHILDREN; i++) {
			if (mother_enemy_pool[enemy_i].children[i].position.y > HEIGHT * 1.1) {
				if (!(mother_enemy_pool[enemy_i].children[i].alive)) continue;
				mother_enemy_pool[enemy_i].children[i].alive = 0;
				printf("child of a mother enemy out of screen!\n");
			}
		}
	}
}

void print_enemy(CP_Vector position, float size) {
	CP_Image enemy_pic = CP_Image_Load("./Assets/enemy.png");
	CP_Image_Draw(enemy_pic, position.x, position.y, size*2, size*2, 255);
}
