
#include <stdlib.h>
#include <stdio.h>
#include "cprocessing.h"
#include "game.h"
#include <math.h>
#define ENEMY_SIZE 20.0f
#define ENEMY_CIRCLE_COUNT 10
#define ENEMY_SPEED 2

struct Enemy enemy_pool[MAX_ENEMY] = { 0 };
struct spawn spawn_pool[MAX_ENEMY] = { 0 };
struct mother_enemy mother_enemy_pool[MAX_MOTHER_ENEMY] = { 0 };

//These functions are used to reinitialise structs with other values
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

//Coordinate declarations, all of these has y = -5 and x = their respective name, except high_mid
CP_Vector one_third, two_third, mid, one_tenth, nine_tenth, minus_two_third, zero, one_fourth, three_fourth, one_fifth, two_fifth, three_fifth, four_fifth, width, high_mid;

//1 for straight line, 2 for left diagonal, 3 for right diagonal, 5 for horizontal enemy, 101 for circle
//Max screen is WDITH/1.5

//Go to sine() and change the multipler for angle to adjust range of the graph
//For pattern 5, you can add side way movement to it to make it cooler, search for 'store1', go there and add some value to the x axis movement

/*!
@brief	contains spawning information for level 1
@param  NIL
@return NIL
*//*______________________________________________________________*/
void level_1(void) {
	//12 spawns in 4 horizontal enemies, 11 spawn in 5 instead

	spawn_pool_assigner(one_third, 15.0f, 50.0f, 10, 1);
	spawn_pool_assigner(two_third, 15.0f, 50.0f, 10, 1);

	spawn_pool_assigner(one_third, 15.0f, 250.0f, 10, 1);
	spawn_pool_assigner(two_third, 15.0f, 250.0f, 10, 1);

	spawn_pool_assigner(one_third, 15.0f, 450.0f, 10, 1);
	spawn_pool_assigner(two_third, 15.0f, 450.0f, 10, 1);

	spawn_pool_assigner(one_third, 15.0f, 700.0f, 10, 1);
	spawn_pool_assigner(two_third, 15.0f, 700.0f, 10, 1);

	spawn_pool_assigner(mid, 15.0f, 900.0f, 10, 1);
	spawn_pool_assigner(one_fourth, 15.0f, 900.0f, 10, 1);
	spawn_pool_assigner(three_fourth, 15.0f, 900.0f, 10, 1);

	spawn_pool_assigner(mid, 15.0f, 1100.0f, 10, 1);
	spawn_pool_assigner(one_fourth, 15.0f, 1100.0f, 10, 1);
	spawn_pool_assigner(three_fourth, 15.0f, 1100.0f, 10, 1);

	spawn_pool_assigner(mid, 15.0f, 1300.0f, 10, 1);
	spawn_pool_assigner(one_fourth, 15.0f, 1300.0f, 10, 1);
	spawn_pool_assigner(three_fourth, 15.0f, 1300.0f, 10, 1);

	spawn_pool_assigner(mid, 15.0f, 1500.0f, 10, 1);
	spawn_pool_assigner(one_fourth, 15.0f, 1500.0f, 10, 1);
	spawn_pool_assigner(three_fourth, 15.0f, 1500.0f, 10, 1);

	spawn_pool_assigner(one_fifth, 15.0f, 1700.0f, 10, 1);
	spawn_pool_assigner(two_fifth, 15.0f, 1700.0f, 10, 1);
	spawn_pool_assigner(three_fifth, 15.0f, 1700.0f, 10, 1);
	spawn_pool_assigner(four_fifth, 15.0f, 1700.0f, 10, 1);

	spawn_pool_assigner(one_fifth, 15.0f, 1900.0f, 10, 1);
	spawn_pool_assigner(two_fifth, 15.0f, 1900.0f, 10, 1);
	spawn_pool_assigner(three_fifth, 15.0f, 1900.0f, 10, 1);
	spawn_pool_assigner(four_fifth, 15.0f, 1900.0f, 10, 1);

	spawn_pool_assigner(one_fifth, 15.0f, 2100.0f, 10, 1);
	spawn_pool_assigner(two_fifth, 15.0f, 2100.0f, 10, 1);
	spawn_pool_assigner(three_fifth, 15.0f, 2100.0f, 10, 1);
	spawn_pool_assigner(four_fifth, 15.0f, 2100.0f, 10, 1);

	spawn_pool_assigner(one_fifth, 15.0f, 2300.0f, 10, 1);
	spawn_pool_assigner(two_fifth, 15.0f, 2300.0f, 10, 1);
	spawn_pool_assigner(three_fifth, 15.0f, 2300.0f, 10, 1);
	spawn_pool_assigner(four_fifth, 15.0f, 2300.0f, 10, 1);

	CP_Vector level_0120 = CP_Vector_Set(WIDTH / 10 * 1.8f, -5);
	spawn_pool_assigner(level_0120, 20.0f, 2500.0f, 10, 12);
	spawn_pool_assigner(level_0120, 20.0f, 2800.0f, 10, 12);
	spawn_pool_assigner(level_0120, 20.0f, 3100.0f, 10, 12);
	spawn_pool_assigner(level_0120, 20.0f, 3400.0f, 10, 12);

	spawn_pool_assigner(level_0120, 20.0f, 3700.0f, 20, 12);
	spawn_pool_assigner(one_tenth, 20.0f, 3750.0f, 20, 11);
	spawn_pool_assigner(level_0120, 20.0f, 4200.0f, 20, 12);
	spawn_pool_assigner(one_tenth, 20.0f, 4250.0f, 20, 11);
	spawn_pool_assigner(level_0120, 20.0f, 4700.0f, 20, 12);
	spawn_pool_assigner(one_tenth, 20.0f, 4750.0f, 20, 11);
	spawn_pool_assigner(level_0120, 20.0f, 5200.0f, 20, 12);
	spawn_pool_assigner(one_tenth, 20.0f, 5250.0f, 20, 11);

	winning_condition = 500;
}

/*!
@brief	contains spawning information for level 2
@param  NIL
@return NIL
*//*______________________________________________________________*/
void level_2(void) {
	spawn_pool_assigner(one_third, 25.0f, 50.0f, 30, 1);
	spawn_pool_assigner(two_third, 25.0f, 50.0f, 30, 1);
	spawn_pool_assigner(mid, 50.0f, 50.0f, 15, 14);

	spawn_pool_assigner(one_third, 25.0f, 850.0f, 30, 1);
	spawn_pool_assigner(two_third, 25.0f, 850.0f, 30, 1);
	spawn_pool_assigner(minus_two_third, 50.0f, 850.0f, 15, 15);

	spawn_pool_assigner(one_tenth, 15.0f, 1700.0f, 50, 11);
	spawn_pool_assigner(zero, 50.0f, 1700.0f, 15, 16);

	spawn_pool_assigner(one_tenth, 15.0f, 2550.0f, 50, 11);
	spawn_pool_assigner(minus_two_third, 50.0f, 2550.0f, 15, 17);

	spawn_pool_assigner(one_tenth, 15.0f, 3400.0f, 50, 11);
	spawn_pool_assigner(zero, 50.0f, 3400.0f, 15, 18);

	spawn_pool_assigner(one_tenth, 15.0f, 4250.0f, 50, 11);
	spawn_pool_assigner(minus_two_third, 50.0f, 4250.0f, 15, 19);

	spawn_pool_assigner(one_third, 25.0f, 5100.0f, 30, 1);
	spawn_pool_assigner(two_third, 25.0f, 5100.0f, 30, 1);
	spawn_pool_assigner(mid, 50.0f, 5100.0f, 15, 14);
	spawn_pool_assigner(minus_two_third, 50.0f, 5100.0f, 15, 15);

	spawn_pool_assigner(one_tenth, 15.0f, 5950.0f, 50, 11);
	spawn_pool_assigner(zero, 50.0f, 5950.0f, 15, 16);
	spawn_pool_assigner(minus_two_third, 50.0f, 5925.0f, 15, 17);

	spawn_pool_assigner(one_tenth, 15.0f, 6800.0f, 50, 11);
	spawn_pool_assigner(zero, 50.0f, 6800.0f, 15, 16);
	spawn_pool_assigner(minus_two_third, 50.0f, 6825.0f, 15, 17);

	spawn_pool_assigner(one_tenth, 15.0f, 7650.0f, 50, 11);
	spawn_pool_assigner(zero, 50.0f, 7650.0f, 15, 18);
	spawn_pool_assigner(minus_two_third, 50.0f, 7675.0f, 15, 19);

	winning_condition = 8600;
}

/*!
@brief	contains spawning information for level 3
@param  NIL
@return NIL
*//*______________________________________________________________*/
void level_3(void) {
	spawn_pool_assigner(one_third, 50.0f, 50.0f, 15, 6);
	spawn_pool_assigner(two_third, 50.0f, 50.0f, 15, 6);
	spawn_pool_assigner(one_tenth, 50.0f, 50.0f, 15, 13);

	spawn_pool_assigner(one_third, 50.0f, 900.0f, 15, 5);
	spawn_pool_assigner(two_third, 50.0f, 900.0f, 15, 5);
	spawn_pool_assigner(one_tenth, 50.0f, 900.0f, 15, 12);

	spawn_pool_assigner(zero, 50.0f, 1750.0f, 15, 51);
	spawn_pool_assigner(width, 50.0f, 1750.0f, 15, 50);
	spawn_pool_assigner(one_tenth, 50.0f, 1750.0f, 15, 12);

	spawn_pool_assigner(zero, 50.0f, 2600.0f, 15, 51);
	spawn_pool_assigner(width, 50.0f, 2600.0f, 15, 50);
	spawn_pool_assigner(one_third, 50.0f, 2600.0f, 15, 51);
	spawn_pool_assigner(two_third, 50.0f, 2600.0f, 15, 50);
	spawn_pool_assigner(one_tenth, 50.0f, 2600.0f, 15, 12);


	spawn_pool_assigner(zero, 50.0f, 3450.0f, 15, 51);
	spawn_pool_assigner(width, 50.0f, 3450.0f, 15, 50);
	spawn_pool_assigner(one_third, 50.0f, 3450.0f, 15, 51);
	spawn_pool_assigner(two_third, 50.0f, 3450.0f, 15, 50);
	spawn_pool_assigner(one_third, 50.0f, 3450.0f, 15, 5);
	spawn_pool_assigner(two_third, 50.0f, 3450.0f, 15, 5);


	spawn_pool_assigner(one_fifth, 50.0f, 4300.0f, 15, 11);
	spawn_pool_assigner(zero, 50.0f, 4300.0f, 15, 53);
	spawn_pool_assigner(width, 50.0f, 4300.0f, 15, 52);

	spawn_pool_assigner(zero, 50.0f, 5150.0f, 15, 53);
	spawn_pool_assigner(width, 50.0f, 5150.0f, 15, 52);
	spawn_pool_assigner(one_fifth, 50.0f, 5150.0f, 15, 11);
	spawn_pool_assigner(one_fourth, 50.0f, 5150.0f, 15, 53);
	spawn_pool_assigner(three_fourth, 50.0f, 5150.0f, 15, 52);

	spawn_pool_assigner(high_mid, 0.0f, 6000.0f, 1, 107);
	spawn_pool_assigner(zero, 100.0f, 6100.0f, 5, 22);

	winning_condition = 7000;


	//spawn_pool_assigner(level_031, 60.0f, 50.0f, 10, 20);

	//spawn_pool_assigner(level_031, 60.0f, 50.0f, 10, 21);

	//spawn_pool_assigner(level_031, 150.0f, 0.0f, 10, 104);

	//
	//--------------------------------------------------------




	//spawn_pool_assigner(one_third, 5.0f, 50.0f, 50, 4); //This makes enemies move left and right in sine graph pattern
}

/*!
@brief	contains spawning information for level 4
@param  NIL
@return NIL
*//*______________________________________________________________*/
void level_4(void) {

	spawn_pool_assigner(mid, 1.0f, 100.0f, 1, 109);

	spawn_pool_assigner(mid, 1.0f, 700.0f, 1, 109);
	spawn_pool_assigner(one_fourth, 1.0f, 925.0f, 1, 109);
	spawn_pool_assigner(three_fourth, 1.0f, 925.0f, 1, 109);

	spawn_pool_assigner(one_fifth, 900.0f, 800.0f, 2, 110);
	spawn_pool_assigner(two_fifth, 900.0f, 950.0f, 2, 110);
	spawn_pool_assigner(three_fifth, 900.0f, 1100.0f, 2, 110);
	spawn_pool_assigner(four_fifth, 900.0f, 1250.0f, 2, 111);
	spawn_pool_assigner(three_fifth, 900.0f, 1400.0f, 2, 111);
	spawn_pool_assigner(two_fifth, 900.0f, 1550.0f, 2, 111);

	spawn_pool_assigner(one_third, 300.0f, 3400.0f, 6, 112);
	spawn_pool_assigner(two_third, 300.0f, 3550.0f, 6, 113);

	spawn_pool_assigner(zero, 300.0f, 5600.0f, 6, 114);
	spawn_pool_assigner(width, 300.0f, 5750.0f, 6, 115);

	winning_condition = 8500;
}

/*!
@brief	contains spawning information for level 5
@param  NIL
@return NIL
*//*______________________________________________________________*/
void level_5(void) {
	spawn_pool_assigner(one_tenth, 1.0f, 50.0f, 1, 104);
	spawn_pool_assigner(one_tenth, 1.0f, 150.0f, 1, 104);
	spawn_pool_assigner(one_tenth, 1.0f, 250.0f, 1, 104);
	spawn_pool_assigner(one_tenth, 1.0f, 350.0f, 1, 104);
	spawn_pool_assigner(one_tenth, 1.0f, 450.0f, 1, 104);
	spawn_pool_assigner(one_tenth, 1.0f, 550.0f, 1, 104);

	spawn_pool_assigner(nine_tenth, 1.0f, 50.0f, 1, 105);
	spawn_pool_assigner(nine_tenth, 1.0f, 150.0f, 1, 105);
	spawn_pool_assigner(nine_tenth, 1.0f, 250.0f, 1, 105);
	spawn_pool_assigner(nine_tenth, 1.0f, 350.0f, 1, 105);
	spawn_pool_assigner(nine_tenth, 1.0f, 450.0f, 1, 105);
	spawn_pool_assigner(nine_tenth, 1.0f, 550.0f, 1, 105);

	spawn_pool_assigner(one_fourth, 250.0f, 1100.0f, 5, 116);
	spawn_pool_assigner(three_fourth, 250.0f, 1100.0f, 5, 116);
	spawn_pool_assigner(mid, 250.0f, 1100.0f, 5, 117);

	spawn_pool_assigner(one_fifth, 300.0f, 2900.0f, 5, 118);
	spawn_pool_assigner(four_fifth, 300.0f, 2900.0f, 5, 118);
	spawn_pool_assigner(two_fifth, 300.0f, 2625.0f, 5, 118);
	spawn_pool_assigner(three_fifth, 300.0f, 2625.0f, 5, 118);
	spawn_pool_assigner(mid, 300.0f, 2900.0f, 5, 119);

	spawn_pool_assigner(mid, 1.0f, 4900.0f, 300, 5);

	spawn_pool_assigner(one_third, 1.0f, 5500.0f, 200, 5);
	spawn_pool_assigner(two_third, 1.0f, 5500.0f, 200, 5);

	spawn_pool_assigner(mid, 1.0f, 5700.0f, 300, 54);
	spawn_pool_assigner(mid, 1.0f, 6200.0f, 300, 54);
	spawn_pool_assigner(mid, 1.0f, 6700.0f, 300, 54);

	spawn_pool_assigner(mid, 1.0f, 7200.0f, 1000, 54);
	spawn_pool_assigner(mid, 300.0f, 7000.0f, 3, 118);

	winning_condition = 8800;
}

/*!
@brief	The brain memory of this spawning system.
		Calls the level indicated and prepare spawning information 
@param  NIL
@return NIL
*//*______________________________________________________________*/
void preload_spawn_map(int level) {
	//reinitialisation of commonly used coordinates
	one_third = CP_Vector_Set(WIDTH / 3, -5);
	two_third = CP_Vector_Set(WIDTH / 3 * 2, -5);
	mid = CP_Vector_Set(WIDTH / 2, -5);
	one_tenth = CP_Vector_Set(WIDTH / 10, -5);
	nine_tenth = CP_Vector_Set(WIDTH / 10 * 9, -5);
	minus_two_third = CP_Vector_Set(-WIDTH / 3 * 2, -5);
	zero = CP_Vector_Set(0, -5);
	one_fourth = CP_Vector_Set(WIDTH / 4, -5);
	three_fourth = CP_Vector_Set(WIDTH / 4 * 3, -5);
	one_fifth = CP_Vector_Set(WIDTH / 5, -5);
	two_fifth = CP_Vector_Set(WIDTH / 5 * 2, -5);
	three_fifth = CP_Vector_Set(WIDTH / 5 * 3, -5);
	four_fifth = CP_Vector_Set(WIDTH / 5 * 4, -5);
	width = CP_Vector_Set(WIDTH, -5);

	//Launch respective level
	if (level == LEVEL_1) level_1();
	if (level == LEVEL_2) level_2();
	if (level == LEVEL_3) level_3();
	if (level == LEVEL_4) level_4();
	if (level == LEVEL_5) level_5();
}

/*!
@brief	The brain logic of this spawning system.
		Transforms a set enemy spawn design loaded into spawn_pool. This would 
		usually be called multiple times in a level, since a level usually 
		consists of many enemy spawn designs. 
		(All spawning follows tick as the timing system)
@param  position - position of where enemy spawns
		spawn_speed_delay - delay between spawning of each spawn enemy designs (higher number = slower spawn rate)
		start_spawn_tick - tick of when the enemy spawn design starts spawning
		spawn_amount - amount of enemy spawn design to spawn
		type - the type of enemy pattern to spawn
@return NIL
*//*______________________________________________________________*/
void spawn_pool_assigner(CP_Vector position, float spawn_speed_delay, float start_spawn_tick, int spawn_amount, int type) {
	float spawn_tick = start_spawn_tick;
	int start_count = 0;
	
	//This for loop segregates each enemy spawn design from each other
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!(spawn_pool[i].type == 0)) continue;
		start_count = i;
		break;
	}

	//Using the start_count from above, it continues spawning from where the last enemy spawn left off
	for (int i = start_count; i < start_count + spawn_amount; i++) {
		spawn_tick = spawn_tick + spawn_speed_delay;
		spawn_pool[i] = spawn_set(position, spawn_tick, type);
	}
}

/*!
@brief	The main muscle of this spawning system.
		transfers each spawning information to other functions, to transfer that information
		into enemy_pool and mother_enemy_pool
@param  NIL
@return NIL
*//*______________________________________________________________*/
void spawn_map(void) {
	for (int i = 0; i < MAX_ENEMY; i++) {

		//if (*tick == winning_condition) gameState = WIN;

		//Loops through each tick and check for spawn_pool that fits the current tick, then allocate space to spawn
		//In accordance to the type indicated, different type has different enemy pattern
		//Some enemie patterns such as horizontal line have special movement pattern, thus each of them are in switch case
		//Others like circle or vertical would go to initialise basic movement 
		if (spawn_pool[i].time == *tick) {
			int ran = 0;
			switch (spawn_pool[i].type) {
				case 11: //5 horizontal
					initialise_horizontal_line(spawn_pool[i].position, 5, 200, 1);
					ran = 1;
					break;
				case 12: //4 horizontal
					initialise_horizontal_line(spawn_pool[i].position, 4, 200, 1);
					ran = 1;
					break;
				case 13: //10 horizontal
					initialise_horizontal_line(spawn_pool[i].position, 10, 150, 1);
					ran = 1;
					break;
				case 14: //10 horizontal moving left
					initialise_horizontal_line(spawn_pool[i].position, 10, 200, 9);
					ran = 1;
					break;
				case 15: //10 horizontal moving right
					initialise_horizontal_line(spawn_pool[i].position, 10, 200, 10);
					ran = 1;
					break;
				case 16: //Same as case 12, just tighter a bit
					initialise_horizontal_line(spawn_pool[i].position, 15, 100, 9);
					ran = 1;
					break;
				case 17: //Same as case 13, just tighter a bit
					initialise_horizontal_line(spawn_pool[i].position, 15, 100, 10);
					ran = 1;
					break;
				case 18://Spawn enemy, but moving left and right
					initialise_horizontal_line(spawn_pool[i].position, 10, 150, 7);
					ran = 1;
					break;
				case 19://Spawn enemy, but moving right and left, reverse of case 18
					initialise_horizontal_line(spawn_pool[i].position, 10, 150, 8);
					ran = 1;
					break;
				case 20:
					initialise_horizontal_line(spawn_pool[i].position, 10, 150, 6);
					ran = 1;
					break;
				case 21:
					initialise_horizontal_line(spawn_pool[i].position, 10, 100, 6);
					ran = 1;
					break;
				case 22: //horizontal in horizontal sine pattern
					initialise_horizontal_line(spawn_pool[i].position, 10, 100, 4);
					ran = 1;
					break;
			}
			if (!(ran)) initialise_basic_movement(i);
		}
	}
}

//----------------- Initialise Enemy ------------------

/*!
@brief	The arm muscle of this spawning system
		Takes in spawn_pool and turn it into enemy_pool or mother_enemy_pool
@param  spawn_pool_i - the index of the spawn_pool
@return NIL
*//*______________________________________________________________*/
void initialise_basic_movement(int spawn_pool_i) {
	if (spawn_pool[spawn_pool_i].type == 0) return;

	//Loops through each enemy_pool and mother_enemy_pool to find empty space to allocate them
	if (0 < spawn_pool[spawn_pool_i].type && spawn_pool[spawn_pool_i].type < 100) {
		for (int i = 0; i < MAX_ENEMY; i++) {
			if (enemy_pool[i].alive) continue;
			enemy_pool[i] = enemy_set(spawn_pool[spawn_pool_i].position, 1, ENEMY_SIZE, spawn_pool[spawn_pool_i].type);
			break;
		}
	} else {
		for (int i = 0; i < MAX_MOTHER_ENEMY; i++) {

			if (mother_enemy_pool[i].alive) continue;
			mother_enemy_pool[i] = mother_enemy_set(spawn_pool[spawn_pool_i].position, spawn_pool[spawn_pool_i].time ,1, spawn_pool[spawn_pool_i].type);
			mother_enemy_pool[i].spare2 = 1;
			for (int j = 0; j < MAX_CHILDREN; j++) {
				mother_enemy_pool[i].children[j].alive = 1;
			}
			break;
		}
	}
}

/*!
@brief	The arm muscle of this spawning system
		Takes in spawn_pool and turn it into enemy_pool
@param  start_position - the most left enemy that should spawn for a horizontal line
		enemy_count - amount of enemy to spawn
		distance_apart - distance between each horizontal enemies
		type - movement pattern of the enemy
@return NIL
*//*______________________________________________________________*/
void initialise_horizontal_line(CP_Vector start_position, int enemy_count, float distance_apart, int type) {

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

//------------------ Enemy Patterns ------------------- (Should run continously in game_update)
/*!
@brief	The fingers of this spawning system
		It goes through each standard enemies and update their position according to their movement type
@param  NIL
@return NIL
*//*______________________________________________________________*/
void movement_pattern_vertical_and_diagonal(void) {
	double speed, range;
	static int pattern_const;

	CP_Settings_Fill(COLOR_BLUE);
	for (int i = 0; i < MAX_ENEMY; i++) {

		enemy_out_of_screen(1,i); //eliminate enemies out of screen

		if (!(enemy_pool[i].alive)) continue;
		enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, DOWN); //Updates position
		
		switch (enemy_pool[i].type) {
			case 2: //Move left
				enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, LEFT); 
				break;
			case 3: //Move right
				enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, RIGHT); 
				break;
			case 4: //Enemy move left to right while in a sine graph formation
				range = 10;
				speed = sine(range, 0, 1);
				//enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, LEFT);
				enemy_pool[i].position.x += (float)speed;
				break;
			case 5: //pendulum wave pattern
				range = 10;
				speed = sine(range, i, 1);
				//enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, LEFT);
				enemy_pool[i].position.x += (float)speed; //store1
				break;
			case 6: //make enemy go bouncing while coming down
				range = 10;
				speed = sine(range, i, 1);
				//enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, LEFT);
				enemy_pool[i].position.y += (float)speed;
				break;
			case 7: //move left, move right at half-way point
				if (enemy_pool[i].position.y < HEIGHT/2) enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, LEFT);
				else enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, RIGHT);
				break;
			case 8: //reverse of case 7
				if (enemy_pool[i].position.y > HEIGHT / 2) enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, LEFT);
				else enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, RIGHT);
				break;
			case 9: //Move left
				enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 3, LEFT); 
				break;
			case 10: //Move right
				enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 3, RIGHT); 
				break;
			case 50: //bouncing vertically while moving left
				range = 10;
				speed = sine(range, i, 1);
				enemy_pool[i].position.y += (float)speed;
				enemy_pool[i].position.x -= 3;
				break;
			case 51: //bouncing vertically while moving left
				range = 10;
				speed = sine(range, i, 1);
				enemy_pool[i].position.y += (float)speed;
				enemy_pool[i].position.x += 3;
				break;
			case 52: //bouncing vertically and move left, move right at half-way point
				if (enemy_pool[i].position.y < HEIGHT / 2) enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, LEFT);
				else enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, RIGHT);
				range = 10;
				speed = sine(range, i, 1);
				enemy_pool[i].position.y += (float)speed;
				break;
			case 53: //reverse of case 52
				if (enemy_pool[i].position.y > HEIGHT / 2) enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, LEFT);
				else enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, RIGHT);
				range = 10;
				speed = sine(range, i, 1);
				enemy_pool[i].position.y += (float)speed;
				break;
			case 54: //pendulum wave pattern intensified
				range = 10;
				speed = sine(range, i, 10);
				//enemy_pool[i].position = enemy_moving_up_down_left_right(enemy_pool[i].position, 5, LEFT);
				enemy_pool[i].position.x += (float)speed; //store1
				break;
		}
		print_enemy(enemy_pool[i].position, enemy_pool[i].size);
	}

}

/*!
@brief	The fingers of this spawning system
		It goes through each mother enemies and update their movement pattern according to their movemnt type
@param  spawn_pool_i - the index of the spawn_pool
@return NIL
*//*______________________________________________________________*/
void movement_pattern_spinning_circle(void) {
	CP_Settings_Fill(COLOR_BLUE);
	int children_alive;
	double range, speed;

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
		
		mother_enemy_pool[i].position = enemy_moving_up_down_left_right(mother_enemy_pool[i].position, ENEMY_SPEED, DOWN); //Updates every movment's position, to move downwards

		//Switch to their respective movement pattern and update their position
		switch (mother_enemy_pool[i].type) {
			case 101:
				spin_enemy(i, ENEMY_CIRCLE_COUNT, 100, 0.5f, mother_enemy_pool[i].position);
				break;
			case 102: // makes circle follow a sine graph path
				range = 10;
				speed = sine(range, i, 1);
				//printf("sine: %f, speed: %f\n", angle, speed);
				mother_enemy_pool[i].position.x += (float)speed;
				spin_enemy(i, ENEMY_CIRCLE_COUNT, 100, 0.5f, mother_enemy_pool[i].position);
				break;
			case 103: //makes spinning circle grow in and out
				range = 10;
				speed = sine(range, i, 1);
				mother_enemy_pool[i].position.x += (float)speed;
				spin_enemy(i, ENEMY_CIRCLE_COUNT, 100 + (float)speed*10, 0.5f, mother_enemy_pool[i].position);
				break;
			case 104: //giant spinning circle
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 800;
				spin_enemy(i, 50, 0.01f, 800, mother_enemy_pool[i].position);
				//printf("mother_enemy %d: position: %f | %f\n", i, mother_enemy_pool[i].position.x, mother_enemy_pool[i].position.y);
				break;
			case 105: //giant spinning circle (reversed)
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 800;
				spin_enemy(i, 50, -0.01f, 800, mother_enemy_pool[i].position);
				break;
			case 106: //vertical enemy
				vertical_enemy(i, 10, 15.0f);
				break;
			case 107: //giant spinning circle (width of screen)
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 470;
				spin_enemy(i, 50, 0.01f, 470, mother_enemy_pool[i].position);
				break;
			case 108: //one third spinning circle cw
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 160;
				spin_enemy(i, 12, 0.02f, 160, mother_enemy_pool[i].position);
				break;
			case 109: //two third spinning circle ccw
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 310;
				spin_enemy(i, 25, -0.02f, 310, mother_enemy_pool[i].position);
				break;
			case 110: //half spinning circle cw
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 230;
				spin_enemy(i, 20, 0.02f, 230, mother_enemy_pool[i].position);
				break;
			case 111: //half spinning circle ccw
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 230;
				spin_enemy(i, 20, -0.02f, 230, mother_enemy_pool[i].position);
				break;
			case 112: //half spinning circle ccw
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 230;
				range = 5;
				speed = sine(range, i, 5);
				mother_enemy_pool[i].position.x += (float)speed;
				spin_enemy(i, 20, -0.02f, 230, mother_enemy_pool[i].position);
				break;
			case 113: //Same as case 112, but opposite
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 230;
				range = -5;
				speed = sine(range, i, 5);
				mother_enemy_pool[i].position.x += (float)speed;
				spin_enemy(i, 20, 0.02f, 230, mother_enemy_pool[i].position);
				break;
			case 114: //half spinning circle ccw
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 230;
				range = 2;
				speed = sine(range, i, 10);
				mother_enemy_pool[i].position.y += (float)speed;
				mother_enemy_pool[i].position.x += 1;
				spin_enemy(i, 20, -0.02f, 230, mother_enemy_pool[i].position);
				break;
			case 115: //Same as case 112, but opposite
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 230;
				range = -2;
				speed = sine(range, i, 10);
				mother_enemy_pool[i].position.y += (float)speed;
				mother_enemy_pool[i].position.x -= 1;
				spin_enemy(i, 20, 0.02f, 230, mother_enemy_pool[i].position);
				break;
			case 116: //makes spinning circle grow in and out
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 230;
				range = 10;
				speed = sine(range, 0, 5);
				spin_enemy(i, 20, 0.02f, 150 + (float)speed * 10, mother_enemy_pool[i].position);
				break;
			case 117: //makes spinning circle grow in and out
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 230;
				range = 20;
				speed = sine(range, 0, 5);
				spin_enemy(i, 20, 0.02f, 200 + (float)speed * 10, mother_enemy_pool[i].position);
				break;
			case 118: //makes spinning circle grow in and out
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 230;
				range = 7;
				speed = sine(range, 0, 1);
				mother_enemy_pool[i].position.y += (float)speed;
				spin_enemy(i, 20, 0.02f, 200 + (float)speed * 10, mother_enemy_pool[i].position);
				break;
			case 119: //makes spinning circle grow in and out
				if (mother_enemy_pool[i].spare2) mother_enemy_pool[i].spare2 = 0, mother_enemy_pool[i].position.y -= 230;
				range = 1;
				speed = sine(range, 0, 0.1);
				mother_enemy_pool[i].position.y += (float)speed;
				spin_enemy(i, 20, 0.02f, 200 + (float)speed * 10, mother_enemy_pool[i].position);
				break;
		}
	}
}

/*!
@brief	The finger bone of this spawning system
		It spawns in child enemies in a circle shape, with mother enemy's position as the center
@param  mother_i - the index of the mother_enemy_pool
		enemy_count - the amount of child enemy
		spin_speed - the spinning speed of the circle
		radius - the distance between child and mother
		position - the position of mother enemy
@return NIL
*//*______________________________________________________________*/
void spin_enemy(int mother_i, int enemy_count, float spin_speed, float radius, CP_Vector position) {
	float angle = 0;

	//randomises the circle enemy so that every circles will spin and form differently
	int randomizer = (int)mother_enemy_pool[mother_i].time % 36;
	if (randomizer != 0) angle = 360.0f / randomizer;

	//goes through each child of a mother and spawn their respective position
	for (int i = 0; i < enemy_count; i++) {

		mother_enemy_pool[mother_i].spare += spin_speed;

		CP_Vector enemy_direction = rotate_vector(radius, angle + mother_enemy_pool[mother_i].spare, E1);
		CP_Vector enemy_position = CP_Vector_Add(position, enemy_direction);
		angle += 360.0f / enemy_count;
		mother_enemy_pool[mother_i].children[i].position = enemy_position;
		mother_enemy_pool[mother_i].children[i].size = ENEMY_SIZE;

		if (!(mother_enemy_pool[mother_i].children[i].alive)) continue;

		print_enemy(mother_enemy_pool[mother_i].children[i].position, mother_enemy_pool[mother_i].children[i].size);
	}
}

/*!
@brief	Spawns enemy vertically (Not complete due to lack of time)
@param  mother_i - the index of the mother_enemy_pool
		enemy_count - the amount of enemy to spawn
		distance_apart - the distance between each child
@return NIL
*//*______________________________________________________________*/
void vertical_enemy(int mother_i, int enemy_count, float distance_apart) {
	/*int randomizer = (int)mother_enemy_pool[mother_i].time % 36;
	if (randomizer != 0) angle = 360.0f / randomizer;*/
	printf("it ran here!!");
	float distance = 0;
	for (int i = 0; i < enemy_count; i++, distance += distance_apart) {
		if (!(mother_enemy_pool[mother_i].children[i].alive)) continue;
		//printf("this enemy's alive or dead state: %d\n", mother_enemy_pool[mother_i].children[i].alive);
		mother_enemy_pool[mother_i].children[i].position = mother_enemy_pool[mother_i].position;
		mother_enemy_pool[mother_i].children[i].position.y -= distance;
		mother_enemy_pool[mother_i].children[i].size = ENEMY_SIZE;

		print_enemy(mother_enemy_pool[mother_i].children[i].position, mother_enemy_pool[mother_i].children[i].size);
		//CP_Graphics_DrawCircle(mother_enemy_pool[mother_i].children[i].position.x, mother_enemy_pool[mother_i].children[i].position.y, mother_enemy_pool[mother_i].children[i].size * 2); //Prints enemy
	}
}

/*!
@brief	Sets child enemy or standard enemy to dead if they are out of the screen
@param  enemy_i - the index of the standard enemy or child enemy
		enemy_not_mother - to differentiate whether the function should test for child enemy or standard enemy
@return NIL
*//*______________________________________________________________*/
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

/*!
@brief	Prints enemy
@param  position - position of where to print the enemy
		size - the size of enemy
@return NIL
*//*______________________________________________________________*/
void print_enemy(CP_Vector position, float size) {
	CP_Image enemy_pic = CP_Image_Load("./Assets/enemy.png");
	CP_Image_Draw(enemy_pic, position.x, position.y, size*2, size*2, 255);
}


/*!
@brief	To obtain varying number in the form of sine graph
@param  range - the magnitude of sine graph
		randomiser - this is more of a seed than randomiser
		speed - changes the wavelength of the sine graph
@return NIL
*//*______________________________________________________________*/
double sine(double range, int randomiser, double speed) {
	double angle = *tick * PI / 360.0 / speed;
	return range * sin(randomiser + angle * 10);
}

