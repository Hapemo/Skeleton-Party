
#include <stdlib.h>
#include <stdio.h>
#include "cprocessing.h"
#include "game.h"
#include <math.h>
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

void level_1(void) {
	CP_Vector level_011 = CP_Vector_Set(WIDTH / 3, -5);
	CP_Vector level_012 = CP_Vector_Set(WIDTH / 3 * 2, -5);

	spawn_pool_assigner(level_011, 15.0f, 50.0f, 10, 1);
	spawn_pool_assigner(level_012, 15.0f, 50.0f, 10, 1);

	spawn_pool_assigner(level_011, 15.0f, 250.0f, 10, 1);
	spawn_pool_assigner(level_012, 15.0f, 250.0f, 10, 1);

	spawn_pool_assigner(level_011, 15.0f, 450.0f, 10, 1);
	spawn_pool_assigner(level_012, 15.0f, 450.0f, 10, 1);

	spawn_pool_assigner(level_011, 15.0f, 700.0f, 10, 1);
	spawn_pool_assigner(level_012, 15.0f, 700.0f, 10, 1);

	CP_Vector level_013 = CP_Vector_Set(WIDTH / 2, -5);
	CP_Vector level_014 = CP_Vector_Set(WIDTH / 4, -5);
	CP_Vector level_015 = CP_Vector_Set(WIDTH / 4 * 3, -5);

	spawn_pool_assigner(level_013, 15.0f, 900.0f, 10, 1);
	spawn_pool_assigner(level_014, 15.0f, 900.0f, 10, 1);
	spawn_pool_assigner(level_015, 15.0f, 900.0f, 10, 1);

	spawn_pool_assigner(level_013, 15.0f, 1100.0f, 10, 1);
	spawn_pool_assigner(level_014, 15.0f, 1100.0f, 10, 1);
	spawn_pool_assigner(level_015, 15.0f, 1100.0f, 10, 1);

	spawn_pool_assigner(level_013, 15.0f, 1300.0f, 10, 1);
	spawn_pool_assigner(level_014, 15.0f, 1300.0f, 10, 1);
	spawn_pool_assigner(level_015, 15.0f, 1300.0f, 10, 1);

	spawn_pool_assigner(level_013, 15.0f, 1500.0f, 10, 1);
	spawn_pool_assigner(level_014, 15.0f, 1500.0f, 10, 1);
	spawn_pool_assigner(level_015, 15.0f, 1500.0f, 10, 1);

	CP_Vector level_016 = CP_Vector_Set(WIDTH / 5, -5);
	CP_Vector level_017 = CP_Vector_Set(WIDTH / 5 * 2, -5);
	CP_Vector level_018 = CP_Vector_Set(WIDTH / 5 * 3, -5);
	CP_Vector level_019 = CP_Vector_Set(WIDTH / 5 * 4, -5);

	spawn_pool_assigner(level_016, 15.0f, 1700.0f, 10, 1);
	spawn_pool_assigner(level_017, 15.0f, 1700.0f, 10, 1);
	spawn_pool_assigner(level_018, 15.0f, 1700.0f, 10, 1);
	spawn_pool_assigner(level_019, 15.0f, 1700.0f, 10, 1);

	spawn_pool_assigner(level_016, 15.0f, 1900.0f, 10, 1);
	spawn_pool_assigner(level_017, 15.0f, 1900.0f, 10, 1);
	spawn_pool_assigner(level_018, 15.0f, 1900.0f, 10, 1);
	spawn_pool_assigner(level_019, 15.0f, 1900.0f, 10, 1);

	spawn_pool_assigner(level_016, 15.0f, 2100.0f, 10, 1);
	spawn_pool_assigner(level_017, 15.0f, 2100.0f, 10, 1);
	spawn_pool_assigner(level_018, 15.0f, 2100.0f, 10, 1);
	spawn_pool_assigner(level_019, 15.0f, 2100.0f, 10, 1);

	spawn_pool_assigner(level_016, 15.0f, 2300.0f, 10, 1);
	spawn_pool_assigner(level_017, 15.0f, 2300.0f, 10, 1);
	spawn_pool_assigner(level_018, 15.0f, 2300.0f, 10, 1);
	spawn_pool_assigner(level_019, 15.0f, 2300.0f, 10, 1);

	CP_Vector level_0120 = CP_Vector_Set(WIDTH / 10 * 1.8f, -5);
	spawn_pool_assigner(level_0120, 20.0f, 2500.0f, 10, 012);
	spawn_pool_assigner(level_0120, 20.0f, 2800.0f, 10, 012);
	spawn_pool_assigner(level_0120, 20.0f, 3100.0f, 10, 012);
	spawn_pool_assigner(level_0120, 20.0f, 3400.0f, 10, 012);

	CP_Vector level_0121 = CP_Vector_Set(WIDTH / 10, -5);
	spawn_pool_assigner(level_0120, 20.0f, 3700.0f, 20, 012);
	spawn_pool_assigner(level_0121, 20.0f, 3750.0f, 20, 011);
	spawn_pool_assigner(level_0120, 20.0f, 4200.0f, 20, 012);
	spawn_pool_assigner(level_0121, 20.0f, 4250.0f, 20, 011);
	spawn_pool_assigner(level_0120, 20.0f, 4700.0f, 20, 012);
	spawn_pool_assigner(level_0121, 20.0f, 4750.0f, 20, 011);
	spawn_pool_assigner(level_0120, 20.0f, 5200.0f, 20, 012);
	spawn_pool_assigner(level_0121, 20.0f, 5250.0f, 20, 011);
}

void preload_spawn_map(void) { //Put in game_init
	//first wave
	//-------------------------------------------------
	//Standard lines
	if (1) level_1();



	/*CP_Vector level_0150 = CP_Vector_Set(WIDTH / 10, -5);
	spawn_pool_assigner(level_012, 30.0f, 0.0f, 10, 011);*/

	//-------------------------------------------------
	//Web pattern
	/*CP_Vector level_012 = CP_Vector_Set(WIDTH/10, -5);
	spawn_pool_assigner(level_012, 30.0f, 0.0f, 10, 011);

	CP_Vector level_013 = CP_Vector_Set(WIDTH/10*1.8f, -5);
	spawn_pool_assigner(level_013, 30.0f, 15.0f, 10, 012);*/
	//-------------------------------------------------
	
	

	//CP_Vector line_11 = CP_Vector_Set(WIDTH / 2, -5);
	//spawn_pool_assigner(line_11, 80.0f, 50.0f, 30, 103);

	//CP_Vector line_2 = CP_Vector_Set(((WIDTH/3)+50), -5);
	//spawn_pool_assigner(line_2, 50.0f, 10.0f, 30, 1);

	//CP_Vector line_3 = CP_Vector_Set(((WIDTH / 3) -50), -5);
	//spawn_pool_assigner(line_3, 50.0f, 50.0f, 30, 1);

	//CP_Vector line_4 = CP_Vector_Set(((WIDTH / 3) + 100), -5);
	//spawn_pool_assigner(line_4, 50.0f, 10.0f, 30, 1);
	//

	////second wave
	//CP_Vector line_5 = CP_Vector_Set(-180, -400);
	//spawn_pool_assigner(line_5, 20.0f, 100.0f, 50, 5);

	//CP_Vector line_6 = CP_Vector_Set(((WIDTH / 4) + 50), -400);
	//spawn_pool_assigner(line_6, 50.0f, 1600.0f, 50, 5);

	//CP_Vector line_7 = CP_Vector_Set((WIDTH/4), -400);
	//spawn_pool_assigner(line_7, 20.0f, 1600.0f, 50, 5);

	//CP_Vector line_8 = CP_Vector_Set(((WIDTH/4) + 100), -400);
	//spawn_pool_assigner(line_8, 50.0f, 1600.0f, 50, 5);

	////third wave
	//CP_Vector line_9 = CP_Vector_Set((WIDTH / 2)+150, -400);
	//spawn_pool_assigner(line_9, 20.0f, 4300.0f, 50, 101);

	//CP_Vector line_10 = CP_Vector_Set(WIDTH / 2, -400);
	//spawn_pool_assigner(line_10, 20.0f, 4300.0f, 3, 101);
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

		if (*tick == 500) {
			reset_enemy_and_weapon();
		}

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
					initialise_basic_movement(i);
					break;
				case 011:
					initialise_horizontal_line(spawn_pool[i].position, 5, WIDTH/1.1f, 1);
					break;
				case 012:
					initialise_horizontal_line(spawn_pool[i].position, 4, WIDTH / 1.2f, 1);
					break;
				case 101:
					initialise_basic_movement(i);
					break;
				case 102:
					initialise_basic_movement(i);
					break;
				case 103:
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
	
	for (int i = 0; i <= enemy_count; i++) {
		for (int j = 0; j < MAX_ENEMY; j++) {
			if (enemy_pool[j].alive) continue;
			enemy_pool[j] = enemy_set(position, 1, ENEMY_SIZE, type);
			position.x += (distance_apart);
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
	/*float multiplier;
	int timer, duration;*/
	double speed;


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
			case 4:
				speed = 10;
				speed = sine(speed, i);
				enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, LEFT);
				enemy_pool[i].position.x += (float)speed;
				break;
		}

		//CP_Graphics_DrawCircle(enemy_pool[i].position.x, enemy_pool[i].position.y, enemy_pool[i].size * 2); //Prints enemy
		print_enemy(enemy_pool[i].position, enemy_pool[i].size);
	}

}

void movement_pattern_spinning_circle(void) {
	CP_Settings_Fill(COLOR_BLUE);
	int children_alive;
	double speed;

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
			case 102:
				speed = 10;
				speed = sine(speed, i);
				//printf("sine: %f, speed: %f\n", angle, speed);
				mother_enemy_pool[i].position.x += (float)speed;
				spin_enemy(i, ENEMY_CIRCLE_COUNT, 100, mother_enemy_pool[i].position);
				break;
			case 103:
				speed = 10;
				speed = sine(speed, i);
				mother_enemy_pool[i].position.x += (float)speed;
				spin_enemy(i, ENEMY_CIRCLE_COUNT, 100 + (float)speed*10, mother_enemy_pool[i].position);
				break;
		}
	}
}

void spin_enemy(int mother_i, int enemy_count, float radius, CP_Vector position) {
	float angle = 0;
	float spin_speed = 0.5f;
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
		}
	} else {
		for (int i = 0; i < MAX_CHILDREN; i++) {
			if (mother_enemy_pool[enemy_i].children[i].position.y > HEIGHT * 1.1) {
				if (!(mother_enemy_pool[enemy_i].children[i].alive)) continue;
				mother_enemy_pool[enemy_i].children[i].alive = 0;
			}
		}
	}
}

void print_enemy(CP_Vector position, float size) {
	CP_Image enemy_pic = CP_Image_Load("./Assets/enemy.png");
	CP_Image_Draw(enemy_pic, position.x, position.y, size*2, size*2, 255);
}



double sine(double speed, int randomiser) {
	double angle = *tick * PI / 360.0;
	return speed * sin(randomiser + angle * 10);
}

