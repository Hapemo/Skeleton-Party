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

#pragma once

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "cprocessing.h"
#include "game.h"

#define SWORD_CRIT_CHANCE 10

//These variables are for melee attacks, for function 'melee_attack' and 'activate_melee_by_mouse'
int first_time = 1, * pfirst_time = &first_time; //First time running the function
float melee_start_angle = 45, melee_angle = 0; //Determines where the melee attack is facing. 45 is when it's facing north.
int melee_max_angle = 90; //starting melee angle
int melee_anticlockwise = TRUE; //clockwise or anti clockwise melee
int melee_speed = 10; //speed of melee animation
int melee_angle_upgrade = 0; //angle upgrade for melee
float sword_length = 0;
float sword_width = 0;
int sword_cooldown = 0;
int sword_attack_speed = 60/2;

int melee_or_not = 0, * pmelee_or_not = &melee_or_not; //Determine if should melee or not
CP_Vector melee_position; //Position of where the melee animation happens

int collide = 0, *pcollide = &collide;
int lightbulb_i = 0;


//-------------------------------------------------------
//Sword explosion
#define MAX_SWORD_EXPLOSION (100)
CP_Vector sword_explosion_pool[MAX_SWORD_EXPLOSION] = { 0 };
float sword_explosion_radius_pool[MAX_SWORD_EXPLOSION] = { 0 };
float sword_explosion_speed = 15, max_sword_explosion_radius = 200;

//-------------------------------------------------------
//Bullet
#define MAX_BULLET (20)
#define BULLET_SIZE (WIDTH / 50)
CP_Vector bullet_pool[MAX_BULLET] = { 0 };
int fireball_attack_speed = 60 / 4;
int fireball_cooldown = 0;


//-------------------------------------------------------
//Explosion
#define MAX_EXPLOSION (100)
CP_Vector explosion_pool[MAX_EXPLOSION] = { 0 };
float explosion_radius_pool[MAX_EXPLOSION] = { 0 };
float explosion_speed = 10, max_explosion_radius = 100;

//-------------------------------------------------------
//Shrapnel
#define SHRAPNEL_SPEED 5.0f

typedef struct sharpnel_item {
	CP_Vector position;
	float angle;
	int alive;
} sharpnel_item;

#define MAX_SHRAPNEL (50)
float max_shrapnels = 5;
sharpnel_item shrapnel_pool[MAX_SHRAPNEL] = { 0 };



//-------------------------------------------------------
//Arrow
#define MAX_PIERCING_BULLET (20)
#define BULLET_WIDTH (WIDTH / 1000 * 14)
#define BULLET_LENGTH (WIDTH / 1000 * 69)
#define BULLET_ANGLE 0
#define PIERCING_BULLET_SPEED 25.0f
CP_Vector piercing_bullet_pool[MAX_BULLET] = { 0 };

#define MAX_CHARGE (50.0f)
#define MAX_CHARGE_POOL (20)
float piercing_charge = 0, max_piercing_charge = 500.0f, charge_pool[MAX_CHARGE_POOL] = { 0 };


extern int CurrentCharacter; 


void melee_attack(CP_Vector position) {
	//Set the melee angle for the first time
	if (first_time) {
		//Set sword size
		sword_width = WIDTH / 8;
		sword_length = HEIGHT / 50;

		*pfirst_time = 0;

		melee_start_angle -= melee_angle_upgrade;
		melee_max_angle += (int)melee_start_angle + 2 * melee_angle_upgrade;
		melee_angle = melee_start_angle;
	}

	//This determines the speed of the rectangle swinging. **Beware, it skips some areas, so might not hit enemies that are too small**
	melee_angle += melee_speed;

	//This determines if the attack is counter clockwise or clockwise
	if (melee_anticlockwise) melee_angle *= -1;

	print_melee_weapon(position, melee_angle);

	CP_Vector temp_vec = CP_Vector_Set(1, 0); //This CP_Vector is specially for sword. For some reason, when use E1, it will become inaccurate.
	CP_Vector vec1 = rotate_vector(sword_length, melee_angle - 90, temp_vec); //-90 because the lines are initialised to pointing downwards, resetting them to point towards y = 0
	CP_Vector vec2 = rotate_vector(sword_width, melee_angle - 90, E2);

	int killed;
	for (int j = 0; j < MAX_MOTHER_ENEMY; j++) {
		if (!(mother_enemy_pool[j].alive)) continue;

		for (int k = 0; k < MAX_CHILDREN; k++) {
			if (!(mother_enemy_pool[j].children[k].alive)) continue;
			killed = 0;

			if (rect_collision(mother_enemy_pool[j].children[k].position, position, vec1, vec2, mother_enemy_pool[j].children[k].size)) killed = 1;
			if (killed) {
				*pcollide = 1;
				shockwavestate = 1;
				if (shockwavestate) {
					play_crit();
					printf("explosion is activated");
					unsigned int random_int = CP_Random_RangeInt(0, 100);
					if (random_int < (SWORD_CRIT_CHANCE + additionalcrit)) sword_explosion(mother_enemy_pool[j].children[k].position);
				}
				mother_enemy_pool[j].children[k].alive = 0;
				DropStuffs(mother_enemy_pool[j].children[k].position);
			}
		}
	}


	for (int j = 0; j < MAX_ENEMY; j++) {
		if (!(enemy_pool[j].alive)) continue;
		killed = 0;

		if (rect_collision(enemy_pool[j].position, position, vec1, vec2, enemy_pool[j].size)) killed = 1;

		if (killed) {
			*pcollide = 1;
			shockwavestate = 1;
			if (shockwavestate) {
				play_crit();
				printf("explosion is activated");
				unsigned int random_int = CP_Random_RangeInt(0, 100);
				if (random_int < (SWORD_CRIT_CHANCE + additionalcrit)) sword_explosion(enemy_pool[j].position);
			}
			DropStuffs(enemy_pool[j].position);
			enemy_pool[j].alive = 0;
		}
	}

	//Resets the animation of the attack
	if (!(-melee_max_angle < melee_angle && melee_angle < melee_max_angle)) {
		melee_angle = melee_start_angle;
		*pmelee_or_not = 0;
	}
	//Resets the melee angle back to positive
	if (melee_angle < 0) melee_angle *= -1;
}


void print_melee_weapon(CP_Vector position, float angle) {

	CP_Image sword_pic = CP_Image_Load("./Assets/sword.png");
	//CP_Vector sword_position = CP_Vector_Set(position.x, position.y);
	// Create transform matrices
	CP_Matrix translate = CP_Matrix_Translate(position); //bring attack to position
	CP_Matrix rotate = CP_Matrix_Rotate(angle+90);



	// Combine transfrom -> translation and rotation
	CP_Matrix transform = CP_Matrix_Multiply(translate, rotate);

	// Set the camera transfrom to the created matrix
	CP_Settings_ApplyMatrix(transform);

	// Draw a blue rectangle that rotates
	//CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	//CP_Graphics_DrawRect(0, 0, sword_width, sword_length);
	CP_Image_Draw(sword_pic, 0, -sword_width / 2, sword_length, sword_width, 255);

	// Reset the matrix to the identity matrix
	CP_Settings_ResetMatrix();
}


void weapon_to_enemy_collision(void) {
	float distance_apart;

	//enemy_pool
	for (int j = 0; j < MAX_ENEMY; j++) {
		if (!(enemy_pool[j].alive)) continue; //Enemy not alive
		if (out_of_screen(enemy_pool[j].position))continue;

		//Sword
		//Placed in melee_attack

		//Sword explosion
		for (int i = 0; i < MAX_SWORD_EXPLOSION; i++) {
			if (!(enemy_pool[j].alive)) break;
			if (sword_explosion_pool[i].y == 0 && sword_explosion_pool[i].x == 0) continue;

			distance_apart = CP_Vector_Distance(sword_explosion_pool[i], enemy_pool[j].position);
			if (distance_apart <= (enemy_pool[j].size + sword_explosion_radius_pool[i])) {
				
				enemy_pool[j].alive = 0;
				DropStuffs(enemy_pool[j].position);
			}
		}

		//Bullet
		for (int i = 0; i < MAX_BULLET; i++) {
			if (!(enemy_pool[j].alive)) break;
			if (bullet_pool[i].y == 0 && bullet_pool[i].x == 0) continue;

			distance_apart = CP_Vector_Distance(bullet_pool[i], enemy_pool[j].position);
			if (distance_apart <= (BULLET_SIZE + enemy_pool[j].size * 34.0f / 50.0f)) {
				enemy_pool[j].alive = 0;
				explode(bullet_pool[i]);
				if (shrapnelstate) shrapnel(bullet_pool[i]);

				bullet_pool[i] = CP_Vector_Set(0, 0);
				DropStuffs(enemy_pool[j].position);
			}
		}

		//Explosion
		for (int i = 0; i < MAX_EXPLOSION; i++) {
			if (!(enemy_pool[j].alive)) break;
			if (explosion_pool[i].y == 0 && explosion_pool[i].x == 0) continue;
			distance_apart = CP_Vector_Distance(explosion_pool[i], enemy_pool[j].position);

			if (distance_apart <= (enemy_pool[j].size + explosion_radius_pool[i])) {
				//DropStuffs(enemy_pool[j].position);
				enemy_pool[j].alive = 0;
				DropStuffs(enemy_pool[j].position);

			}
		}

		////Shrapnel
		//for (int i = 0; i < MAX_SHRAPNEL; i++) {
		//	if (!(enemy_pool[j].alive)) break;
		//	if (shrapnel_pool[i].y == 0 && shrapnel_pool[i].x == 0) continue;
		//	distance_apart = CP_Vector_Distance(shrapnel_pool[i], enemy_pool[j].position);
		//	if (distance_apart <= (enemy_pool[j].size + BULLET_SIZE)) {
		//		printf("distance apart: %f, enemy_pool[j].size: %f, BULLET_SIZE: %f\n", distance_apart, enemy_pool[j].size, BULLET_SIZE);
		//		DropStuffs(enemy_pool[j].position);
		//		shrapnel_pool[i] = CP_Vector_Set(0, 0);
		//		shrapnel_vector_pool[i] = CP_Vector_Set(0, 0);
		//		enemy_pool[j].alive = 0;
		//	}
		//}

		//Arrow
		for (int i = 0; i < MAX_PIERCING_BULLET; i++) {
			if (!(enemy_pool[j].alive)) break;
			if (piercing_bullet_pool[i].y == 0 && piercing_bullet_pool[i].x == 0) continue; //If bullet is not active, skip.

			CP_Vector vec1 = rotate_vector(BULLET_WIDTH * charge_pool[i], BULLET_ANGLE, E1); //-90 because the lines are initialised to pointing downwards, resetting them to point towards y = 0
			CP_Vector vec2 = rotate_vector(BULLET_LENGTH * charge_pool[i], BULLET_ANGLE, E2);

			if (rect_collision(enemy_pool[j].position, piercing_bullet_pool[i], vec1, vec2, enemy_pool[j].size)) {
				enemy_pool[j].alive = 0;

				DropStuffs(enemy_pool[j].position);

			}
		}
	}

	//mother_enemy_pool
	for (int j = 0; j < MAX_MOTHER_ENEMY; j++) {
		if (!(mother_enemy_pool[j].alive)) continue;
		for (int k = 0; k < MAX_CHILDREN; k++) {
			if (!(mother_enemy_pool[j].children[k].alive)) continue;

			if (mother_enemy_pool[j].children[k].position.y < -30) continue; //Enemy not yet in screen 

			//Sword
			//Placed in melee_attack

			//Sword explosion
			for (int i = 0; i < MAX_SWORD_EXPLOSION; i++) {
				if (!(mother_enemy_pool[j].children[k].alive)) break;
				if (sword_explosion_pool[i].y == 0 && sword_explosion_pool[i].x == 0) continue;

				distance_apart = CP_Vector_Distance(sword_explosion_pool[i], mother_enemy_pool[j].children[k].position);
				if (distance_apart <= (mother_enemy_pool[j].children[k].size + sword_explosion_radius_pool[i])) {
					
					mother_enemy_pool[j].children[k].alive = 0;

					DropStuffs(mother_enemy_pool[j].children[k].position);
					
				}
			}
			//Bullet
			for (int i = 0; i < MAX_BULLET; i++) {
				if (!(mother_enemy_pool[j].children[k].alive)) break;
				if (bullet_pool[i].y == 0 && bullet_pool[i].x == 0) continue;

				distance_apart = CP_Vector_Distance(bullet_pool[i], mother_enemy_pool[j].children[k].position);
				if (distance_apart <= (BULLET_SIZE + mother_enemy_pool[j].children[k].size * 34.0f / 50.0f)) {
					explode(bullet_pool[i]); 
					//printf("bullet_pool position: %f | %f\n", bullet_pool[i].x, bullet_pool[i].y);
					//if (shrapnelstate) shrapnel(bullet_pool[i]);

					bullet_pool[i] = CP_Vector_Set(0, 0);
					
					mother_enemy_pool[j].children[k].alive = 0;

					DropStuffs(mother_enemy_pool[j].children[k].position);

				}
			}

			//Explosion
			for (int i = 0; i < MAX_EXPLOSION; i++) {
				if (!(mother_enemy_pool[j].children[k].alive)) break;
				if (explosion_pool[i].y == 0 && explosion_pool[i].x == 0) continue;
				distance_apart = CP_Vector_Distance(explosion_pool[i], mother_enemy_pool[j].children[k].position);

				if (distance_apart <= (mother_enemy_pool[j].children[k].size + explosion_radius_pool[i])) {
					
					mother_enemy_pool[j].children[k].alive = 0;
					DropStuffs(mother_enemy_pool[j].children[k].position);
				}
			}

			//Shrapnel
			//for (int i = 0; i < MAX_BULLET; i++) {
			//	if (!(mother_enemy_pool[j].children[k].alive)) break;
			//	if (shrapnel_pool[i].y == 0 && shrapnel_pool[i].x == 0) continue;
			//	distance_apart = CP_Vector_Distance(shrapnel_pool[i], mother_enemy_pool[j].children[k].position);
			//	//printf("shrapnel_pool[i]: %f | %f, mother_enemy_pool[j].children[k].position: %f | %f\n", shrapnel_pool[i].x, shrapnel_pool[i].y, mother_enemy_pool[j].children[k].position.x, mother_enemy_pool[j].children[k].position.y);
			//	if (distance_apart <= (mother_enemy_pool[j].children[k].size + BULLET_SIZE)) {
			//		printf("it collided here!!");
			//		DropStuffs(mother_enemy_pool[j].children[k].position);
			//		shrapnel_pool[i] = CP_Vector_Set(0, 0);
			//		shrapnel_vector_pool[i] = CP_Vector_Set(0, 0);
			//		mother_enemy_pool[j].children[k].alive = 0;
			//	}
			//}

			//Arrow
			for (int i = 0; i < MAX_PIERCING_BULLET; i++) {
				if (!(mother_enemy_pool[j].children[k].alive)) break;
				if (piercing_bullet_pool[i].y == 0 && piercing_bullet_pool[i].x == 0) continue; //If bullet is not active, skip.

				CP_Vector vec1 = rotate_vector(BULLET_WIDTH * charge_pool[i], BULLET_ANGLE, E1); //-90 because the lines are initialised to pointing downwards, resetting them to point towards y = 0
				CP_Vector vec2 = rotate_vector(BULLET_LENGTH * charge_pool[i], BULLET_ANGLE, E2);

				if (rect_collision(mother_enemy_pool[j].children[k].position, piercing_bullet_pool[i], vec1, vec2, mother_enemy_pool[j].children[k].size)) {
					mother_enemy_pool[j].children[k].alive = 0;
					DropStuffs(mother_enemy_pool[j].children[k].position);
					
				}
			}
		}
	}
}

int rect_collision(CP_Vector enemy1, CP_Vector position, CP_Vector vec1, CP_Vector vec2, float enemy_radius) {
	//Following the formula drawn on the iPad
	CP_Vector half_vec1 = CP_Vector_Scale(vec1, 0.5f);
	CP_Vector half_vec2 = CP_Vector_Scale(vec2, 0.5f);

	CP_Vector weapon_center = CP_Vector_Add(CP_Vector_Subtract(position, half_vec1), half_vec2);
	CP_Vector weapon_to_enemy = CP_Vector_Subtract(enemy1, weapon_center);

	//CP_Graphics_DrawCircle(weapon_center.x, weapon_center.y, 5);
	//CP_Graphics_DrawCircle(position.x, position.y, 10);
	//CP_Graphics_DrawLine(weapon_center.x, weapon_center.y, weapon_center.x + half_vec1.x, weapon_center.y + half_vec1.y);
	//CP_Graphics_DrawLine(weapon_center.x, weapon_center.y, weapon_center.x + half_vec2.x, weapon_center.y + half_vec2.y);

	CP_Vector normalised_vec1 = CP_Vector_Normalize(half_vec1);
	float vec1_dot_product = CP_Vector_DotProduct(weapon_to_enemy, normalised_vec1);
	if (vec1_dot_product < 0) vec1_dot_product *= -1;

	if (!(vec1_dot_product <= CP_Vector_Length(half_vec1) + enemy_radius)) return 0;

	CP_Vector normalised_vec2 = CP_Vector_Normalize(half_vec2);
	float vec2_dot_product = CP_Vector_DotProduct(weapon_to_enemy, normalised_vec2);
	if (vec2_dot_product < 0) vec2_dot_product *= -1;

	if (vec2_dot_product <= CP_Vector_Length(half_vec2) + enemy_radius) {
		//This is when collision happens!
		play_swordHit();
		return 1;
	}
	else return 0;
}


CP_Vector rotate_vector(float scalar, float angle, CP_Vector unit_vector) {
	CP_Vector vector = CP_Vector_Scale(unit_vector, scalar);

	CP_Matrix rotate = CP_Matrix_Rotate(angle);

	vector = CP_Vector_MatrixMultiply(rotate, vector);

	return vector;
}

void initiate_melee(void) {
	if (sword_cooldown++ < sword_attack_speed) return;
	if (CP_Input_KeyTriggered(KEY_SPACE)) {
		*pmelee_or_not = 1;
		play_swordSwing();
		sword_cooldown = 0;
	}
}

void melee_update(CP_Vector position) {
	if (*pmelee_or_not) {
		melee_attack(position);
	} else {
		if (!(CurrentCharacter == knightint))return;
		if (sword_cooldown > sword_attack_speed) return;
		print_cooldown(position, 0);
	}
}

void print_cooldown(CP_Vector position, int weapon) {
	float ratio;
	if (weapon) ratio = fireball_cooldown/ (float)fireball_attack_speed;
	else ratio = sword_cooldown/(float)sword_attack_speed;

	// Create transform matrices
	CP_Matrix translate = CP_Matrix_Translate(position); //bring attack to position

	// Set the camera transfrom to the created matrix
	CP_Settings_ApplyMatrix(translate);

	// Draw a blue rectangle that rotates
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(-50, 70, 100, 20);

	CP_Settings_Fill(CP_Color_Create(0, 0, 100, 255));
	CP_Graphics_DrawRect(-50, 70, 100 - 100 * ratio, 20);

	// Reset the matrix to the identity matrix
	CP_Settings_ResetMatrix();
}


void sword_explosion(CP_Vector position) {
	for (int i = 0; i < MAX_SWORD_EXPLOSION; i++) { //loops through each explosion in explosion pool
		if (sword_explosion_pool[i].y == 0 && sword_explosion_pool[i].x == 0) { //to find explosion = 0
			sword_explosion_pool[i] = position;
			sword_explosion_radius_pool[i] = 1;

			break;
		}
	}
}

void sword_explosion_update(void) {
	for (int i = 0; i < MAX_SWORD_EXPLOSION; i++) {
		if (!(sword_explosion_pool[i].y == 0 && sword_explosion_pool[i].x == 0)) {
			sword_explosion_radius_pool[i] += sword_explosion_speed; //Increase radius of explosion each frame
		}

		if (sword_explosion_radius_pool[i] >= max_sword_explosion_radius) {
			sword_explosion_radius_pool[i] = 0; //Until it reaches the max radius, then zero it out
			sword_explosion_pool[i] = CP_Vector_Set(0, 0);
		}
	}
	sword_explosion_print();
}


void sword_explosion_print(void) {
	for (int i = 0; i < MAX_SWORD_EXPLOSION; i++) {
		if (!(sword_explosion_pool[i].y == 0 && sword_explosion_pool[i].x == 0)) {
			CP_Image explosion_pic = CP_Image_Load("./Assets/explosion.png");
			CP_Image_Draw(explosion_pic, sword_explosion_pool[i].x, sword_explosion_pool[i].y, sword_explosion_radius_pool[i] * 1.5f, sword_explosion_radius_pool[i] * 1.5f, 255);
			/*
			static float critical_hit = 0;
			if (critical_hit++ > max_sword_explosion_radius) critical_hit = 0;*/

			CP_Image critical_pic = CP_Image_Load("./Assets/critical.png");
			CP_Image_Draw(critical_pic, sword_explosion_pool[i].x, sword_explosion_pool[i].y, 30 * 2.81f, 30, 255);
		}
	}
}


void lightbulb(void) {
	if (collide) {
		//CP_Settings_Fill(COLOR_GREEN);
		lightbulb_i++;
		if (lightbulb_i > 10) {
			collide = 0;
			lightbulb_i = 0;
		}
	} else {
		//CP_Settings_Fill(COLOR_WHITE);
	}
	//CP_Graphics_DrawRect(WIDTH/10, HEIGHT/10, WIDTH / 10, HEIGHT / 10 );
}

float tick_p = 0, * tick = &tick_p;

void timer(void) {
	
	*tick += 1;
	//printf("GAME_TIMER: %f", *tick);
	//printf("tick count: %f\n", *tick);
	if (*tick == INT_MAX) *tick = 0;
}

void timer_reset(void)
{
	*tick = 0;
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

int out_of_screen(CP_Vector sprite_position) {
	if (sprite_position.x > WIDTH || sprite_position.y > HEIGHT || sprite_position.x < 0 || sprite_position.y < 0) return 1;
	return 0;
}

void shooting_check(CP_Vector position) {

	if (fireball_cooldown++ < fireball_attack_speed) {
		print_cooldown(position, 1);
	} else if (CP_Input_KeyDown(KEY_SPACE)) {
		shoot_bullet(position);
		fireball_cooldown = 0;
	}

	//CP_Vector position = CP_Vector_Set(WIDTH*(3.0f/4),HEIGHT * (3.0f / 4)); //Position of character
	/*if (CP_Input_KeyDown(KEY_SPACE)) {
		shoot_bullet(position);
	}*/
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

			bullet_pool[i] = enemy_moving_up_down_left_right(bullet_pool[i], bullet_speed, UP); //update it's position
			
			if (out_of_screen(bullet_pool[i])) bullet_pool[i] = CP_Vector_Set(0, 0);
		}
	}
	print_bullet();
	//bullet_collision();
}

void print_bullet(void) {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (!(bullet_pool[i].y == 0 && bullet_pool[i].x == 0)) { //If bullet is active

			CP_Image fireball_pic = CP_Image_Load("./Assets/fireball.png");
			//CP_Vector sword_position = CP_Vector_Set(position.x, position.y);
			// Create transform matrices
			CP_Matrix translate = CP_Matrix_Translate(bullet_pool[i]); //bring attack to position
			CP_Matrix rotate = CP_Matrix_Rotate(90);

			// Combine transfrom -> translation and rotation
			CP_Matrix transform = CP_Matrix_Multiply(translate, rotate);

			// Set the camera transfrom to the created matrix
			CP_Settings_ApplyMatrix(transform);

			// Draw a blue rectangle that rotates
			//CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
			//CP_Graphics_DrawRect(0, 0, sword_width, sword_length);
			CP_Image_Draw(fireball_pic, 0, 0, BULLET_SIZE*1.47f, BULLET_SIZE, 255);

			CP_Settings_ResetMatrix();
			//CP_Settings_Fill(COLOR_BLUE);
			//CP_Graphics_DrawCircle(bullet_pool[i].x, bullet_pool[i].y, BULLET_SIZE *2); //This is in diameter so need to times 2
		}
	}
}


void explode(CP_Vector position) { //position where the bullet killed the enemy 
	//Pass this function only to when enemy was killed by bullet

	for (int i = 0; i < MAX_EXPLOSION; i++) { //loops through each explosion in explosion pool
		if (explosion_pool[i].y == 0 && explosion_pool[i].x == 0) { //to find explosion = 0
			explosion_pool[i] = position;
			explosion_radius_pool[i] = 1;
			play_crit();
			break;
		}
	}
}

void explosion_update(void) {
	for (int i = 0; i < MAX_EXPLOSION; i++) {
		if (!(explosion_pool[i].y == 0 && explosion_pool[i].x == 0)) {
			explosion_radius_pool[i] += explosion_speed; //Increase radius of explosion each frame
		}

		if (explosion_radius_pool[i] >= max_explosion_radius) {
			explosion_radius_pool[i] = 0; //Until it reaches the max radius, then zero it out
			explosion_pool[i] = CP_Vector_Set(0, 0);
		}
	}

	//explosion_collision();
	explosion_print();
}

void explosion_print(void) {
	for (int i = 0; i < MAX_EXPLOSION; i++) {
		if (!(explosion_pool[i].y == 0 && explosion_pool[i].x == 0)) {
			CP_Image shrapnel_pic = CP_Image_Load("./Assets/explosion.png");
			// Create transform matrices

			CP_Image_Draw(shrapnel_pic, explosion_pool[i].x, explosion_pool[i].y, explosion_radius_pool[i]*2, explosion_radius_pool[i]*2, 255);
		}
	}
}


void shrapnel(CP_Vector position) {
	for (int i = 0; i < max_shrapnels; i++) {
		for (int j = 0; j < MAX_SHRAPNEL; j++) {
			if (shrapnel_pool[j].alive) continue;
			shrapnel_pool[j].angle = (i / max_shrapnels) * 360;
			shrapnel_pool[j].position = position;
			shrapnel_pool[j].alive = 1;

			break;
		}
	}
}

void shrapnel_update(void) {
	for (int i = 0; i < MAX_SHRAPNEL; i++) {

		if (shrapnel_pool[i].alive) {
			//if ("shrapnel_pool[i].x += shrapnel_vector_pool[i].x;")
			CP_Vector vector = rotate_vector(SHRAPNEL_SPEED, shrapnel_pool[i].angle, E1); 
			shrapnel_pool[i].position.x += vector.x;
			shrapnel_pool[i].position.y += vector.y;
			//printf("vector: %f | %f, position: %f | %f\n", vector.x, vector.y, shrapnel_pool[i].position.x, shrapnel_pool[i].position.y);
			if (out_of_screen(shrapnel_pool[i].position)) shrapnel_pool[i].alive = 0;
		}
	}
	print_shrapnel();
	shrapnel_collision();
}

void print_shrapnel(void) {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (shrapnel_pool[i].alive) { //If bullet is active
			CP_Image shrapnel_pic = CP_Image_Load("./Assets/bullet.png");
			// Create transform matrices

			CP_Matrix translate = CP_Matrix_Translate(shrapnel_pool[i].position); //bring attack to position 
			CP_Matrix rotate = CP_Matrix_Rotate(shrapnel_pool[i].angle - 90.0f);

			// Combine transfrom -> translation and rotation
			CP_Matrix transform = CP_Matrix_Multiply(translate, rotate);

			// Set the camera transfrom to the created matrix
			CP_Settings_ApplyMatrix(transform);

			
			CP_Image_Draw(shrapnel_pic, 0, 0, BULLET_SIZE/1.5f, BULLET_SIZE/1.5f*2.9f, 255);

			CP_Settings_ResetMatrix();


			//CP_Settings_Fill(COLOR_BLUE);
			//CP_Graphics_DrawCircle(bullet_pool[i].x, bullet_pool[i].y, BULLET_SIZE *2); //This is in diameter so need to times 2
			
		}
	}


}

void shrapnel_collision(void) {
	//Check array of bullet with array of enemy
	float distance_apart;

	for (int i = 0; i < MAX_BULLET; i++) {
		if (shrapnel_pool[i].alive) { //If bullet is active

			for (int j = 0; j < MAX_MOTHER_ENEMY; j++) {
				if (mother_enemy_pool[j].alive == 0) continue;
				for (int k = 0; k < MAX_CHILDREN; k++) {
					if (mother_enemy_pool[j].children[k].alive == 0) continue;

					distance_apart = CP_Vector_Distance(shrapnel_pool[i].position, mother_enemy_pool[j].children[k].position);
					if (distance_apart <= (mother_enemy_pool[j].children[k].size + BULLET_SIZE)) {
						//printf("distance apart: %f, enemy_size: %f, bullet_size: %f, total size: %f\n", distance_apart, mother_enemy_pool[j].children[k].size, BULLET_SIZE, mother_enemy_pool[j].children[k].size + explosion_radius_pool[i]);
						shrapnel_pool[i].alive = 0;
						mother_enemy_pool[j].children[k].alive = 0;
						DropStuffs(mother_enemy_pool[j].children[k].position);
					}
				}
			}
		}
	}
}


void piercing_shooting_check(CP_Vector position) {

	if (CP_Input_KeyDown(KEY_SPACE)) {
		if (!(piercing_charge >= MAX_CHARGE)) piercing_charge++;
		print_charge(position, piercing_charge);
		printf("charge: %f", piercing_charge);
	} 

	if (CP_Input_KeyReleased(KEY_SPACE)) {
		shoot_piercing_bullet(position, piercing_charge);
		piercing_charge = 0;
	}

	update_piercing_bullet_travel();
}

void shoot_piercing_bullet(CP_Vector position, float charge) {
	for (int i = 0; i < MAX_PIERCING_BULLET; i++) {
		if (piercing_bullet_pool[i].y == 0 && piercing_bullet_pool[i].x == 0) {
			piercing_bullet_pool[i] = position;
			charge_pool[i] = charge/10;
			piercing_bullet_pool[i].x = piercing_bullet_pool[i].x - (BULLET_WIDTH / 2.0f)* charge / 10; //if not the collision will be wrong
			break;
		}
	}
}

void print_charge(CP_Vector position, float charge) {

	float ratio = charge / MAX_CHARGE;

	// Create transform matrices
	CP_Matrix translate = CP_Matrix_Translate(position); //bring attack to position

	// Set the camera transfrom to the created matrix
	CP_Settings_ApplyMatrix(translate);

	// Draw a blue rectangle that rotates
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(-50, 70, 100, 20);

	CP_Settings_Fill(CP_Color_Create(0, 0, 100, 255));
	CP_Graphics_DrawRect(-50, 70, 100*ratio, 20);

	// Reset the matrix to the identity matrix
	CP_Settings_ResetMatrix();
}

void update_piercing_bullet_travel(void) {
	for (int i = 0; i < MAX_PIERCING_BULLET; i++) {

		if (!(piercing_bullet_pool[i].y == 0 && piercing_bullet_pool[i].x == 0)) { //If bullet is active
			piercing_bullet_pool[i] = enemy_moving_up_down_left_right(piercing_bullet_pool[i], PIERCING_BULLET_SPEED, UP); //update it's position

			if (out_of_screen(piercing_bullet_pool[i])) piercing_bullet_pool[i] = CP_Vector_Set(0, 0);
		}
	}
	print_piercing_bullet();
	//piercing_bullet_collision();
}

void print_piercing_bullet(void) {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (!(piercing_bullet_pool[i].y == 0 && piercing_bullet_pool[i].x == 0)) { //If bullet is active

			CP_Image arrow_pic = CP_Image_Load("./Assets/arrow.png");

			CP_Settings_Fill(COLOR_BLUE);
			// Create transform matrices
			CP_Matrix translate = CP_Matrix_Translate(piercing_bullet_pool[i]); //bring attack to position
			CP_Matrix rotate = CP_Matrix_Rotate(BULLET_ANGLE);

			// Combine transfrom -> translation and rotation
			CP_Matrix transform = CP_Matrix_Multiply(translate, rotate);

			// Set the camera transfrom to the created matrix
			CP_Settings_ApplyMatrix(transform);

			// Draw a blue rectangle that rotates
			/*CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
			CP_Graphics_DrawRect(0, 0, BULLET_WIDTH * charge_pool[i], BULLET_LENGTH * charge_pool[i]);*/
			CP_Image_Draw(arrow_pic, BULLET_WIDTH * charge_pool[i] / 2, 0, BULLET_WIDTH * charge_pool[i], BULLET_LENGTH * charge_pool[i], 255);

			// Reset the matrix to the identity matrix
			CP_Settings_ResetMatrix();
		}
	}
}

void reset_enemy_and_weapon(void) {
	//enemy_pool
	printf("resets enemy and weapon!!!\n");
	memset(enemy_pool, '0', sizeof(enemy_pool));
	memset(spawn_pool, '0', sizeof(spawn_pool));
	memset(mother_enemy_pool, '0', sizeof(mother_enemy_pool));

	memset(bullet_pool, '0', sizeof(bullet_pool));
	memset(explosion_pool, '0', sizeof(explosion_pool));
	memset(shrapnel_pool, '0', sizeof(shrapnel_pool));
	memset(sword_explosion_pool, '0', sizeof(sword_explosion_pool));
	memset(piercing_bullet_pool, '0', sizeof(piercing_bullet_pool));

	memset(charge_pool, '0', sizeof(charge_pool));
	memset(explosion_radius_pool, '0', sizeof(explosion_radius_pool));
	memset(sword_explosion_radius_pool, '0', sizeof(sword_explosion_radius_pool));

	memset(item_pool, '0', sizeof(item_pool));
}