/*---------------------------------------------------------
 * file:	jazz.c
 * author:	jazz
 * email:	j.teoh@digipen.edu
*
 * brief:	This file contains functions 
*
 * documentation link:
 * https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
*
 * Copyright © 2020 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "cprocessing.h"
#include "game.h"

#define COLOR_GRAY CP_Color_Create(127, 127, 127, 255)
#define COLOR_GREEN CP_Color_Create(0, 255, 0, 255)
#define COLOR_BLUE CP_Color_Create(0, 0, 255, 255)
#define COLOR_WHITE CP_Color_Create(255, 255, 255, 255)

//These variables are for melee attacks, for function 'melee_attack' and 'activate_melee_by_mouse'
int first_time = 1, * pfirst_time = &first_time; //First time running the function
float melee_start_angle = 45, melee_angle = 0; //Determines where the melee attack is facing. 45 is when it's facing north.
int melee_max_angle = 90; //starting melee angle
int melee_anticlockwise = TRUE; //clockwise or anti clockwise melee
int melee_speed = 10; //speed of melee animation
int melee_angle_upgrade = 20; //angle upgrade for melee
float sword_length = 0;
float sword_width = 0;

CP_Vector e1, e2;

int melee_or_not = 0, * pmelee_or_not = &melee_or_not; //Determine if should melee or not
CP_Vector melee_position; //Position of where the melee animation happens

int collide = 0, *pcollide = &collide;
int lightbulb_i = 0;


void melee_attack(CP_Vector position, CP_Vector *enemy) {
	//Set the melee angle for the first time
	if (first_time) {
		//Set sword size
		sword_width = WIDTH / 5;
		sword_length = HEIGHT / 25;

		*pfirst_time = 0;
		
		melee_start_angle -= melee_angle_upgrade;
		melee_max_angle += (int)melee_start_angle + 2*melee_angle_upgrade;
		melee_angle = melee_start_angle;

		//Set univector
		e1 = CP_Vector_Set(-1, 0);
		e2 = CP_Vector_Set(0, 1);
	}

	//This determines the speed of the rectangle swinging. **Beware, it skips some areas, so might not hit enemies that are too small**
	melee_angle += melee_speed;

	//This determines if the attack is counter clockwise or clockwise
	if (melee_anticlockwise) melee_angle *= -1; 

	print_melee_weapon(position, melee_angle);

	CP_Vector vec1 = rotate_vector(sword_length, melee_angle - 90, e1); //-90 because the lines are initialised to pointing downwards, resetting them to point towards y = 0
	CP_Vector vec2 = rotate_vector(sword_width, melee_angle - 90, e2);

	sword_collision(*enemy, position, vec1, vec2);


	//Resets the animation of the attack
	if (!(-melee_max_angle < melee_angle && melee_angle < melee_max_angle)) {
		melee_angle = melee_start_angle;
		*pmelee_or_not = 0;
	}
	//Resets the melee angle back to positive
	if (melee_angle < 0) melee_angle *= -1;
}


void print_melee_weapon(CP_Vector position, float angle) {
	// Create transform matrices
	CP_Matrix translate = CP_Matrix_Translate(position); //bring attack to position
	CP_Matrix rotate = CP_Matrix_Rotate(angle);

	// Combine transfrom -> translation and rotation
	CP_Matrix transform = CP_Matrix_Multiply(translate, rotate);

	// Set the camera transfrom to the created matrix
	CP_Settings_ApplyMatrix(transform);

	// Draw a blue rectangle that rotates
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	CP_Graphics_DrawRect(0, 0, sword_width, sword_length);

	// Reset the matrix to the identity matrix
	CP_Settings_ResetMatrix();
}

//void sword_collision_checker(void) {
//	enemy[];
//	loop through every enemy in enemy[];
//	if dead, ignore
//	if alive, parse the CP_vector of the alive enemy into sword_collision()
//	to check the collision of enemy with sword.
//
//	if collide, sword_collision returns killed (int killed = 10)
//	then update enemy alive state to 0 or 1 accordingly.
//}
//
//for every level, we would have a .c file containing enemy_array[], it is fixed size
//Another way is we can assign a lot of enemy (eg. 5000) to array. 


void sword_collision(CP_Vector enemy, CP_Vector position, CP_Vector vec1, CP_Vector vec2) {
	//Following the formula drawn on the iPad
	CP_Vector half_vec1 = CP_Vector_Scale(vec1, 0.5f);
	CP_Vector half_vec2 = CP_Vector_Scale(vec2, 0.5f);

	CP_Vector weapon_center = CP_Vector_Add(CP_Vector_Add(position, half_vec1), half_vec2);
	CP_Vector weapon_to_enemy = CP_Vector_Subtract(enemy, weapon_center);

	CP_Vector normalised_vec1 = CP_Vector_Normalize(half_vec1);
	float vec1_dot_product = CP_Vector_DotProduct(weapon_to_enemy, normalised_vec1);
	if (vec1_dot_product < 0) vec1_dot_product *= -1;

	if (!(vec1_dot_product <= CP_Vector_Length(half_vec1))) return;

	CP_Vector normalised_vec2 = CP_Vector_Normalize(half_vec2);
	float vec2_dot_product = CP_Vector_DotProduct(weapon_to_enemy, normalised_vec2);
	if (vec2_dot_product < 0) vec2_dot_product *= -1;

	if (vec2_dot_product <= CP_Vector_Length(half_vec2)) {
		*pcollide = 1;
	}
}


CP_Vector rotate_vector(float scalar, float angle, CP_Vector unit_vector) {
	CP_Vector vector = CP_Vector_Scale(unit_vector, scalar);

	CP_Matrix rotate = CP_Matrix_Rotate(angle);

	vector = CP_Vector_MatrixMultiply(rotate, vector);

	return vector;
}


void activate_melee_by_mouse(CP_Vector position) {

	CP_Vector enemy = CP_Vector_Set(WIDTH / 2, HEIGHT / 2);
	CP_Graphics_DrawCircle(enemy.x, enemy.y, WIDTH / 500);

	//melee_position = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	//Check for mouse input
	if (!(*pmelee_or_not)) {
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
			*pmelee_or_not = 1;
			//Get mouse input position and parse into melee_attack
		}
	}
	if (*pmelee_or_not) {
		melee_attack(position, &enemy);
	}
}


void lightbulb(void) {
	if (collide) {
		CP_Settings_Fill(COLOR_GREEN);
		lightbulb_i++;
		if (lightbulb_i > 10) {
			collide = 0;
			lightbulb_i = 0;
		}
	} else {
		CP_Settings_Fill(COLOR_WHITE);
	}
	CP_Graphics_DrawRect(WIDTH/10, HEIGHT/10, WIDTH / 10, HEIGHT / 10 );
}


CP_Vector vector_from_starting, movement_1_position, * p_vector_from_starting = &vector_from_starting, starting_position;
int movement_1_start = 1, spin = 0, *p_spin = &spin, spin_speed;
float enemy_count, radius, enemy_speed_x, enemy_speed_y;


int vector_1, vector_2;
void movement_1(void) {
	if (movement_1_start) {
		//For general 
		starting_position = CP_Vector_Set(WIDTH / 2, 0);
		movement_1_position = starting_position;
		movement_1_start = 0;
		vector_from_starting = e2;

		//For enemy_moving_down
		enemy_speed_y = 2;
		enemy_speed_x = 10;
		vector_1 = 2; //1 = up, 2 = down, 3 = left, 4 = right
		vector_2 = 3;

		//For enemy_pattern_circle
		enemy_count = 5, radius = 50;
		spin_speed = 2;
	}
	CP_Vector position = movement_1_position;

	position = enemy_moving_up_down_left_right(position, enemy_speed_y, vector_1);

	position = enemy_moving_up_down_left_right(position, enemy_speed_y, vector_2);
	
	enemy_pattern_circle(position, enemy_count, radius, spin_speed);

	if (out_of_screen(position)) position = starting_position;

	movement_1_position = position;
}

void enemy_pattern_circle(CP_Vector mid_position, float enemy_number, float big_radius, int speed) {
	float angle = 0;
	for (int i = 0; i < enemy_count; i++) {
		CP_Vector enemy_direction = rotate_vector(big_radius, angle + *p_spin, e1);
		CP_Vector enemy_position = CP_Vector_Add(mid_position, enemy_direction);

		print_enemy(enemy_position);
		angle += 360.0f / enemy_count;
	}
	*p_spin += speed;
}

int ticks = 0; 
int tick(void) {
	ticks++;
	if (ticks == INT_MAX) ticks = 0;
	return ticks;
}

void backnforth_multiplier(void) {
	
}

CP_Vector enemy_moving_up_down_left_right(CP_Vector enemy_current, float velocity_scale, int direction) {
	switch (direction) {
	case 1:
		enemy_current.y -= velocity_scale;
		break;
	case 2:
		enemy_current.y += velocity_scale;
		break;
	case 3:
		enemy_current.x -= velocity_scale;
		break;
	case 4:
		enemy_current.x += velocity_scale;
		break;
	}
	return enemy_current;
}

void print_enemy(CP_Vector sprite_position) {
	CP_Graphics_DrawCircle(sprite_position.x, sprite_position.y, WIDTH / 50);
}

int out_of_screen(CP_Vector sprite_position) {
	if (sprite_position.x > WIDTH || sprite_position.y > HEIGHT || sprite_position.x < 0 || sprite_position.y < 0) return 1;
	return 0;
}

#define MAX_BULLET (20)
CP_Vector bullet_pool[MAX_BULLET] = { 0 };

//CP_Vector [0,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1,1]


void shooting_check(CP_Vector position) {
	float bullet_size = WIDTH / 50;

	//CP_Vector position = CP_Vector_Set(WIDTH*(3.0f/4),HEIGHT * (3.0f / 4)); //Position of character
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_2)) {
		shoot_bullet(position);
	}

	update_bullet_travel();
	print_bullet(bullet_size);
	bullet_collision(bullet_size);
}

void shoot_bullet(CP_Vector position) {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullet_pool[i].y == 0 && bullet_pool[i].x == 0) {
			bullet_pool[i] = position;
			break;
		}
	}
}

void update_bullet_travel(void) {
	float bullet_speed = 10.0f;

	for (int i = 0; i < MAX_BULLET; i++) {

		if (!(bullet_pool[i].y == 0 && bullet_pool[i].x == 0)) { //If bullet is active
			bullet_pool[i] = enemy_moving_up_down_left_right(bullet_pool[i], bullet_speed, 1); //update it's position
			
			if (out_of_screen(bullet_pool[i])) bullet_pool[i] = CP_Vector_Set(0, 0);
		}

	}
}

void print_bullet(float bullet_size) {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (!(bullet_pool[i].y == 0 && bullet_pool[i].x == 0)) { //If bullet is active
			CP_Settings_Fill(COLOR_BLUE);
			CP_Graphics_DrawCircle(bullet_pool[i].x, bullet_pool[i].y, bullet_size*2); //This is in diameter so need to times 2
		}
	}
}

void bullet_collision(float bullet_size) {
	//Check array of bullet with array of enemy
	int killed;

	//Placeholder for enemy
	CP_Vector enemy_position = CP_Vector_Set(WIDTH * (3.0f / 4), HEIGHT * (1.0f / 4));
	float enemy_size = WIDTH / 25.0f; //This is in radius
	CP_Settings_Fill(COLOR_GREEN);
	CP_Graphics_DrawCircle(enemy_position.x, enemy_position.y, enemy_size*2); //This is in diameter, so needed to times 2

	for (int i = 0; i < MAX_BULLET; i++) {
		if (!(bullet_pool[i].y == 0 && bullet_pool[i].x == 0)) { //If bullet is active
			killed = 0;
			//Supposed to have another loop here to loop through every active enemy, but I'll just use a place holder here, enemy shall have size of WIDTH/25.

			float distance_apart = CP_Vector_Distance(bullet_pool[i], enemy_position);
			if (distance_apart <= (enemy_size + bullet_size)) killed = 1;

			printf("distance apart: %f, enemy_size: %f, bullet_size: %f, total size: %f\n", distance_apart, enemy_size, bullet_size, enemy_size + bullet_size);

			if (killed) {
				bullet_pool[i] = CP_Vector_Set(0, 0);
				//Suppose to change enemy alive or dead state here
			}
		}
	}
}

//bullet_trajectory() {
//	CP_Vector current_bullet;
//	for (int i = 0; i < MAX_BULLET; i++) {
//		current_bullet = bullet_pool[i];
//
//
//	take the bullet cp vector as a pointer
//	moving the bullet
//	update the pointer
//}
//
//
//
//void use_bullet(void) {
//	CP_Vector current_bullet;
//	for (int i = 0; i < MAX_BULLET; i++) {
//		current_bullet = bullet_pool[i];
//
//		//if button is clicked, activate shoot bullet
//		//shoot bullet draw the earliest possible bullet and activate it
//		//pass the CP_vector of that bullet into bullet trajectory
//		//Bullet trajectory will keep on updating the position of that bullet until it expires
//		//and print the location of the bullet
//		//When expires, Set CP_Vector to 0
//	}
//}



//int basic_projectile_start = 1;
//CP_Vector bullet_vector_p, * bullet_vector = &bullet_vector_p;
//void basic_projectile(void) {
//	CP_Vector starting_position = CP_Vector_Set(WIDTH * (3 / 4.0f), HEIGHT * (3 / 4.0f)); //set starting position of projectile
//
//	if (basic_projectile_start) {
//		*bullet_vector = starting_position;
//		basic_projectile_start = 0;
//	}
//
//	*bullet_vector = enemy_moving_up_down_left_right(position, 1.0f, 1);
//
//	print_sprite(*bullet_vector);
//
//	if (out_of_screen(*bullet_vector)) *bullet_vector = starting_position;
//}


