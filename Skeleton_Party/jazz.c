/*---------------------------------------------------------
 * file:	jazz.c
 * author:	jazz
 * email:	j.teoh@digipen.edu
*
 * brief:	This file contains functions for various operations such as printing weapon, initialising position of weapon and 
			checking collision of weapon with enemies. In addition, it include helper functions to assist the skills tree button
			in isaac.c
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

#define SWORD_CRIT_CHANCE 90

//These variables are for melee attacks, for function 'melee_attack' and 'activate_melee_by_mouse'
int first_time = 1, * pfirst_time = &first_time; //First time running the function
float melee_start_angle = 45, melee_angle = 0; //Determines where the melee attack is facing. 45 is when it's facing north.
int melee_anticlockwise = TRUE; //clockwise or anti clockwise melee
int melee_speed = 10; //speed of melee animation
int melee_angle_upgrade = 0; //angle upgrade for melee
int melee_max_angle = 90; //starting melee angle
float base_sword_width = WIDTH / 8;
float base_sword_length = HEIGHT / 50;
float sword_width;
float sword_length;
int sword_cooldown = 0; //counting of cooldown
float base_sword_attack_speed = 60 / 2;
float sword_attack_speed; //new attackspeed after calculation with upgrades

int melee_or_not = 0, * pmelee_or_not = &melee_or_not; //Determine if should melee or not
CP_Vector melee_position; //Position of where the melee animation happens


//The followings are variables for each weapons
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
float base_fireball_attack_speed = 60 / 4;
float fireball_attack_speed;
int fireball_cooldown = 0;

//-------------------------------------------------------
//Explosion
#define MAX_EXPLOSION (100)
CP_Vector explosion_pool[MAX_EXPLOSION] = { 0 };
float explosion_radius_pool[MAX_EXPLOSION] = { 0 };
float explosion_speed = 10, max_explosion_radius = 50;

//-------------------------------------------------------
//Shrapnel
#define SHRAPNEL_SPEED 5.0f

//Struct for shrapnel
typedef struct sharpnel_item {
	CP_Vector position; //Position of shrapnel
	float angle; //Angle at which shrapnel is moving towards
	int alive; //If the shrapnel is live or not
} sharpnel_item;

#define MAX_SHRAPNEL (50)
int max_shrapnels;
sharpnel_item shrapnel_pool[MAX_SHRAPNEL] = { 0 };



//-------------------------------------------------------
//Arrow
#define MAX_PIERCING_BULLET (20)
#define BULLET_WIDTH (WIDTH / 1000 * 14)
#define BULLET_LENGTH (WIDTH / 1000 * 69)
#define BULLET_ANGLE 0
#define PIERCING_BULLET_SPEED 25.0f
CP_Vector piercing_bullet_pool[MAX_BULLET] = { 0 };

#define MAX_CHARGE_POOL (20)
float MAX_CHARGE, base_max_charge = 50.0f;
float piercing_charge = 0, charge_pool[MAX_CHARGE_POOL] = { 0 }, increase_charge = 1;

//-------------------------------------------------------
//Skill upgrades
float max_arrow_size = 150; //define max_charge
float max_explosion_radius_upgrade = 200; //max explosion radius




/*!
@brief  Performs melee attack from position of character
@param  position - character position, the coordinate at which the attack is performed
@return NIL
*//*______________________________________________________________*/
void melee_attack(CP_Vector position) {
	//Set the melee angle for the first time
	if (first_time) {
		//Set sword size

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
	
	//This part checks for collision with mother enemy
	int killed;
	for (int j = 0; j < MAX_MOTHER_ENEMY; j++) {
		if (!(mother_enemy_pool[j].alive)) continue;

		for (int k = 0; k < MAX_CHILDREN; k++) {
			if (!(mother_enemy_pool[j].children[k].alive)) continue;
			killed = 0;

			if (rect_collision(mother_enemy_pool[j].children[k].position, position, vec1, vec2, mother_enemy_pool[j].children[k].size)) killed = 1;
			if (killed) {
				if (shockwavestate) { //This is active if shockwave upgrade is bought
					play_crit();
					printf("explosion is activated");
					unsigned int random_int = CP_Random_RangeInt(0, 100) + 5 * skill_sword_crit.state;
					if (random_int > SWORD_CRIT_CHANCE ) sword_explosion(mother_enemy_pool[j].children[k].position);
				}
				mother_enemy_pool[j].children[k].alive = 0;
				DropStuffs(mother_enemy_pool[j].children[k].position);
			}
		}
	}

	//This part checks for collision with enemy
	for (int j = 0; j < MAX_ENEMY; j++) {
		if (!(enemy_pool[j].alive)) continue;
		killed = 0;

		if (rect_collision(enemy_pool[j].position, position, vec1, vec2, enemy_pool[j].size)) killed = 1;

		if (killed) {
			shockwavestate = 1;
			if (shockwavestate) {
				play_crit();
				printf("explosion is activated");
				unsigned int random_int = CP_Random_RangeInt(0, 100) + 5 * skill_sword_crit.state;
				if (random_int > SWORD_CRIT_CHANCE) {
					sword_explosion(enemy_pool[j].position);
				}
			}
			DropStuffs(enemy_pool[j].position);
			enemy_pool[j].alive = 0;
		}
	}

	//Resets the animation of the attack
	if (!(-melee_max_angle - (10 * skill_sword_swing.state) < melee_angle && melee_angle < melee_max_angle)) {
		printf("melee_angle: %f", melee_angle);
		melee_angle = melee_start_angle;
		*pmelee_or_not = 0;
	}
	//Resets the melee angle back to positive
	if (melee_angle < 0) melee_angle *= -1;
}


/*!
@brief  Prints sword for melee attack
@param  position - character position, the coordinate at which the attack is performed
		angle - The angle which the sword is swinging at specific point in time
@return NIL
*//*______________________________________________________________*/
void print_melee_weapon(CP_Vector position, float angle) {

	CP_Image sword_pic = CP_Image_Load("./Assets/sword.png");
	CP_Matrix translate = CP_Matrix_Translate(position); //bring attack to position
	CP_Matrix rotate = CP_Matrix_Rotate(angle+90);

	// Combine transfrom -> translation and rotation
	CP_Matrix transform = CP_Matrix_Multiply(translate, rotate);

	// Set the camera transfrom to the created matrix
	CP_Settings_ApplyMatrix(transform);

	CP_Image_Draw(sword_pic, 0, -sword_width / 2, sword_length, sword_width, 255);

	// Reset the matrix to the identity matrix
	CP_Settings_ResetMatrix();
}


/*!
@brief  Checks for collision between all weapons and all enemies. How this works is, it loops through each enemmies,
		followed by each weapon, an check for their collision using respective methods. Some might trigger effects such as
		shock wave or shrapnel, depending on if upgrade is present etc.
@param  NIL
@return NIL
*//*______________________________________________________________*/
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
					if (shrapnelstate) shrapnel(bullet_pool[i]);

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

/*!
@brief  Checks for collision between rectangle and circle
@param  enemy1 - position of item 1, must be a circle or a point
		position - position of item 2, must be a rectangle or square
		vec1 - vector 1 of rectangle (width)
		vec2 - vector 2 of rectangle (height)
		enemy_radius - the radius of the circle
@return boolean value, 1 for collision true, 0 for no collision
*//*______________________________________________________________*/
int rect_collision(CP_Vector enemy1, CP_Vector position, CP_Vector vec1, CP_Vector vec2, float enemy_radius) {
	//Following the formula drawn on the iPad
	CP_Vector half_vec1 = CP_Vector_Scale(vec1, 0.5f);
	CP_Vector half_vec2 = CP_Vector_Scale(vec2, 0.5f);

	CP_Vector weapon_center = CP_Vector_Add(CP_Vector_Subtract(position, half_vec1), half_vec2);
	CP_Vector weapon_to_enemy = CP_Vector_Subtract(enemy1, weapon_center);

	CP_Vector normalised_vec1 = CP_Vector_Normalize(half_vec1);
	float vec1_dot_product = CP_Vector_DotProduct(weapon_to_enemy, normalised_vec1);
	if (vec1_dot_product < 0) vec1_dot_product *= -1;

	if (!(vec1_dot_product <= CP_Vector_Length(half_vec1) + enemy_radius)) return 0;

	CP_Vector normalised_vec2 = CP_Vector_Normalize(half_vec2);
	float vec2_dot_product = CP_Vector_DotProduct(weapon_to_enemy, normalised_vec2);
	if (vec2_dot_product < 0) vec2_dot_product *= -1;

	if (vec2_dot_product <= CP_Vector_Length(half_vec2) + enemy_radius) {
		play_swordHit();
		return 1;
	}
	else return 0;
}

/*!
@brief  Checks for collision between mouse click and rectangle
@param  mouse - position of item 1, must be a point
		position - position of item 2, must be a rectangle or square
		x - width of rectangle 
		y - height 2 of rectangle
@return boolean value, 1 for collision true, 0 for no collision
*//*______________________________________________________________*/
int button_collision(CP_Vector mouse, CP_Vector button, float x, float y) {
	float x_comparison = button.x - mouse.x;
	if (x_comparison < 0) x_comparison *= -1;

	if (!(x_comparison < x / 2)) return 0;

	float y_comparison = button.y - mouse.y;
	if (y_comparison < 0) y_comparison *= -1;

	if (!(y_comparison < y / 2)) return 0;
	return 1;
}

/*!
@brief  Rotates a unit vector and scales it, then return it back 
@param  scalar - amount to scale the rotated unit_vector
		angle - the angle of rotation
		unit_vector - the unit vector at which rotation begins
@return final vector that has been scaled and rotated
*//*______________________________________________________________*/
CP_Vector rotate_vector(float scalar, float angle, CP_Vector unit_vector) {
	CP_Vector vector = CP_Vector_Scale(unit_vector, scalar);

	CP_Matrix rotate = CP_Matrix_Rotate(angle);

	vector = CP_Vector_MatrixMultiply(rotate, vector);

	return vector;
}

/*!
@brief  Checks for egibility to initiate the sword attack
@param  NIL
@return NIL
*//*______________________________________________________________*/
void initiate_melee(void) {
	//These are upgrade variables from skills tree
	sword_width = base_sword_width*powf(1.1f, (float)skill_sword_range.state);
	sword_length = base_sword_length * powf(1.1f, (float)skill_sword_range.state);
	sword_attack_speed = base_sword_attack_speed * powf(0.9f, (float)skill_attack_speed.state);
	
	//Checks if sword is on cooldown, if not, trigger attack
	if (sword_cooldown++ < sword_attack_speed) return;
	if (CP_Input_KeyTriggered(KEY_SPACE)) {
		*pmelee_or_not = 1;
		play_swordSwing();
		sword_cooldown = 0;
	}
}

/*!
@brief  Triggers sword attack
@param  position - position at which sword attack take place
@return NIL
*//*______________________________________________________________*/
void melee_update(CP_Vector position) {
	if (*pmelee_or_not) {
		melee_attack(position);
	} else {
		if (!(CurrentCharacterKeith == knightint))return;
		if (sword_cooldown > sword_attack_speed) return;
		print_cooldown(position, 0);
	}
}

/*!
@brief  Prints the cooldown bar for sword or fireball attacl
@param  position - position at which player is at
		weapon - to select the weapon to print for (0 for sword, 1 for fireball)
@return NIL
*//*______________________________________________________________*/
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

/*!
@brief  Allocate explosion to take place
@param  position - position at which player is at
@return NIL
*//*______________________________________________________________*/
void sword_explosion(CP_Vector position) {
	for (int i = 0; i < MAX_SWORD_EXPLOSION; i++) { //loops through each explosion in explosion pool
		if (sword_explosion_pool[i].y == 0 && sword_explosion_pool[i].x == 0) { //to find explosion = 0
			sword_explosion_pool[i] = position;
			sword_explosion_radius_pool[i] = 1;

			break;
		}
	}
}

/*!
@brief  Updates explosion at every frame
@param  NIL
@return NIL
*//*______________________________________________________________*/
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

/*!
@brief  prints explosion art
@param  NIL
@return NIL
*//*______________________________________________________________*/
void sword_explosion_print(void) {
	for (int i = 0; i < MAX_SWORD_EXPLOSION; i++) {
		if (!(sword_explosion_pool[i].y == 0 && sword_explosion_pool[i].x == 0)) {
			CP_Image explosion_pic = CP_Image_Load("./Assets/explosion.png");
			CP_Image_Draw(explosion_pic, sword_explosion_pool[i].x, sword_explosion_pool[i].y, sword_explosion_radius_pool[i] * 1.5f, sword_explosion_radius_pool[i] * 1.5f, 255);
			
			//Gives the effect that the critical strike symbol grows higher
			static float critical_hit = 0;
			if (critical_hit++ > max_sword_explosion_radius) critical_hit = 0;

			CP_Image critical_pic = CP_Image_Load("./Assets/critical.png");
			CP_Image_Draw(critical_pic, sword_explosion_pool[i].x, sword_explosion_pool[i].y - critical_hit/3, 30 * 2.81f, 30, 255);
		}
	}
}



/*!
@brief  Timer in terms of tick, one tick = 1 frame. Didn't know cprocessing has a clock already, so made my own
@param  NIL
@return NIL
*//*______________________________________________________________*/
float tick_p = 0, * tick = &tick_p;
void timer(void) {
	
	*tick += 1;
	//printf("GAME_TIMER: %f", *tick);
	//printf("tick count: %f\n", *tick);
	if (*tick == INT_MAX) *tick = 0;
}
void timer_reset(void) {
	*tick = 0;
}

/*!
@brief  Moves a position towards UP, DOWN, LEFT or RIGHT
@param  enemy_current - position of sprite
		velocity_scale - magnitude to move by
		direction - consist of LEFT, RIGHT, UP, DOWN, in enum
@return adjusted position of sprite
*//*______________________________________________________________*/
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

/*!
@brief  Checks if a sprite position is out of the screen
@param  sprite_position - position of sprite
@return 1 of out of screen, 0 if not
*//*______________________________________________________________*/
int out_of_screen(CP_Vector sprite_position) {
	if (sprite_position.x > WIDTH || sprite_position.y > HEIGHT || sprite_position.x < 0 || sprite_position.y < 0) return 1;
	return 0;
}

/*!
@brief  Checks if fireball is triggered
@param  position - position of where fireball should be launched
@return NIL
*//*______________________________________________________________*/
void shooting_check(CP_Vector position) {
	//This is the upgrades for fireball, upgrading the attack speed
	fireball_attack_speed = base_fireball_attack_speed * powf(0.9f, (float)skill_attack_speed.state);

	//Checks if the fireball is on cool down. If not, trigger the attack
	if (fireball_cooldown++ < fireball_attack_speed) {
		print_cooldown(position, 1);
	} else if (CP_Input_KeyDown(KEY_SPACE)) {
		shoot_bullet(position);
		fireball_cooldown = 0;
	}
}

/*!
@brief  Allocates an empty slot to a life fireball
@param  position - position of where fireball should be launched
@return NIL
*//*______________________________________________________________*/
void shoot_bullet(CP_Vector position) {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullet_pool[i].y == 0 && bullet_pool[i].x == 0) {
			bullet_pool[i] = position;
			break;
		}
	}
}

/*!
@brief  updates bullet position at every frame
@param  NIL
@return NIL
*//*______________________________________________________________*/
void update_bullet_travel(void) {
	float bullet_speed = 10.0f;

	for (int i = 0; i < MAX_BULLET; i++) {
		if (!(bullet_pool[i].y == 0 && bullet_pool[i].x == 0)) { //If bullet is active

			bullet_pool[i] = enemy_moving_up_down_left_right(bullet_pool[i], bullet_speed, UP); //update it's position
			
			if (out_of_screen(bullet_pool[i])) bullet_pool[i] = CP_Vector_Set(0, 0); //Set the vector to 0 if it's not live, 0 vector is standard for non-live bullets
		}
	}
	print_bullet();
}

/*!
@brief  prints bullet at every frame
@param  NIL
@return NIL
*//*______________________________________________________________*/
void print_bullet(void) {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (!(bullet_pool[i].y == 0 && bullet_pool[i].x == 0)) { //If bullet is active

			CP_Image fireball_pic = CP_Image_Load("./Assets/fireball.png");

			// Create transform matrices
			CP_Matrix translate = CP_Matrix_Translate(bullet_pool[i]); //bring attack to position
			CP_Matrix rotate = CP_Matrix_Rotate(90);

			// Combine transfrom -> translation and rotation
			CP_Matrix transform = CP_Matrix_Multiply(translate, rotate);

			// Set the camera transfrom to the created matrix
			CP_Settings_ApplyMatrix(transform);

			CP_Image_Draw(fireball_pic, 0, 0, BULLET_SIZE*1.47f, BULLET_SIZE, 255);

			CP_Settings_ResetMatrix();
		}
	}
}

/*!
@brief  Initiate explosion for fireball 
@param  position - position of where explosion should happen
@return NIL
*//*______________________________________________________________*/
void explode(CP_Vector position) {
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

/*!
@brief  updates the position of explosion at every frame
@param  NIL
@return NIL
*//*______________________________________________________________*/
void explosion_update(void) {
	for (int i = 0; i < MAX_EXPLOSION; i++) {

		//Code is quite ugly, using 2 arrays and position 0,0 to do things, that's because I've yet to learn struct
		if (!(explosion_pool[i].y == 0 && explosion_pool[i].x == 0)) {
			explosion_radius_pool[i] += explosion_speed; //Increase radius of explosion each frame
		}

		if (explosion_radius_pool[i] >= max_explosion_radius + ((max_explosion_radius_upgrade - max_explosion_radius)*skill_blast_range.state/ max_skill_upgrade)) {
			explosion_radius_pool[i] = 0; //Until it reaches the max radius, then zero it out
			explosion_pool[i] = CP_Vector_Set(0, 0);
		}
	}

	//explosion_collision();
	explosion_print();
}

/*!
@brief  Prints active explosion at every frame
@param  NIL
@return NIL
*//*______________________________________________________________*/
void explosion_print(void) {
	for (int i = 0; i < MAX_EXPLOSION; i++) {
		if (!(explosion_pool[i].y == 0 && explosion_pool[i].x == 0)) {
			CP_Image shrapnel_pic = CP_Image_Load("./Assets/explosion.png");
			// Create transform matrices

			CP_Image_Draw(shrapnel_pic, explosion_pool[i].x, explosion_pool[i].y, explosion_radius_pool[i]*2, explosion_radius_pool[i]*2, 255);
		}
	}
}

/*!
@brief	Initiates shrapnel attack 
@param  NIL
@return NIL
*//*______________________________________________________________*/
void shrapnel(CP_Vector position) {
	//This is the upgrade for shrapnel, increases count of shrapnel spawned for each fireball
	max_shrapnels = 5 + skill_shrapnels.state;

	//Goes through each shrapnels to spawn and rotate them to the correct angle
	for (int i = 0; i < max_shrapnels; i++) {
		for (int j = 0; j < MAX_SHRAPNEL; j++) {
			if (shrapnel_pool[j].alive) continue;
			shrapnel_pool[j].angle = (i / (float)max_shrapnels) * 360;
			shrapnel_pool[j].position = position;
			shrapnel_pool[j].alive = 1;

			break;
		}
	}
}

/*!
@brief	Updates every shrapnel attack at every frames
@param  NIL
@return NIL
*//*______________________________________________________________*/
void shrapnel_update(void) {
	for (int i = 0; i < MAX_SHRAPNEL; i++) {

		if (shrapnel_pool[i].alive) {
			CP_Vector vector = rotate_vector(SHRAPNEL_SPEED, shrapnel_pool[i].angle, E1); 
			shrapnel_pool[i].position.x += vector.x;
			shrapnel_pool[i].position.y += vector.y;
			if (out_of_screen(shrapnel_pool[i].position)) shrapnel_pool[i].alive = 0;
		}
	}
	print_shrapnel();
	shrapnel_collision();
}

/*!
@brief	Prints every shrapnel at every frame
@param  NIL
@return NIL
*//*______________________________________________________________*/
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
			
		}
	}


}

/*!
@brief	Checks for collision of shrapnel with enemies
@param  NIL
@return NIL
*//*______________________________________________________________*/
void shrapnel_collision(void) {
	//Check array of bullet with array of enemy, there was a bug when placed in the general collision function, thus this is made
	float distance_apart;

	//Loops through each bullets
	for (int i = 0; i < MAX_BULLET; i++) {
		if (shrapnel_pool[i].alive) { //If bullet is active

			//Loops through each enemy
			for (int j = 0; j < MAX_ENEMY; j++) {
				if (!(enemy_pool[j].alive)) continue; //Enemy not alive
				if (out_of_screen(enemy_pool[j].position))continue;

				//Check for collision
				distance_apart = CP_Vector_Distance(shrapnel_pool[i].position, enemy_pool[j].position);
				if (distance_apart <= (enemy_pool[j].size + BULLET_SIZE)) {
					//printf("distance apart: %f, enemy_size: %f, bullet_size: %f, total size: %f\n", distance_apart, mother_enemy_pool[j].children[k].size, BULLET_SIZE, mother_enemy_pool[j].children[k].size + explosion_radius_pool[i]);
					shrapnel_pool[i].alive = 0;
					enemy_pool[j].alive = 0;
					DropStuffs(enemy_pool[j].position);
				}
			}
			//Loops through each mother enemy
			for (int j = 0; j < MAX_MOTHER_ENEMY; j++) {
				if (mother_enemy_pool[j].alive == 0) continue;
				for (int k = 0; k < MAX_CHILDREN; k++) {
					if (mother_enemy_pool[j].children[k].alive == 0) continue;

					//Check for collision
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

/*!
@brief	Checks for piercing arrow attack
@param  position - position of where the arrow should be shot from
@return NIL
*//*______________________________________________________________*/
void piercing_shooting_check(CP_Vector position) {
	//This is the upgrade for arrow, for it's max charge size and also charge speed
	MAX_CHARGE = base_max_charge + (max_arrow_size - base_max_charge) * (skill_arrow_size.state / max_skill_upgrade);
	increase_charge = 1 + skill_arrow_charge.state * 0.5f;

	//Charges arrow when attack key is hold down
	if (CP_Input_KeyDown(KEY_SPACE)) {
		if (!(piercing_charge >= MAX_CHARGE)) piercing_charge += increase_charge;
		print_charge(position, piercing_charge);
	} 
	
	//And shoots when attack key is released
	if (CP_Input_KeyReleased(KEY_SPACE)) {
		shoot_piercing_bullet(position, piercing_charge);
		piercing_charge = 0;
	}

	update_piercing_bullet_travel();
}

/*!
@brief	Initialise piercing arrow attack
@param  position - position of where arrow attack begans
		charge - charge amount of arrow attack
@return NIL
*//*______________________________________________________________*/
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

/*!
@brief	prints the charge bar for piercing attack right below the character
@param  position - position of character
		charge - amount of charge
@return NIL
*//*______________________________________________________________*/
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
	CP_Graphics_DrawRect(-50 - (float)skill_arrow_charge.state, 70 , 100*ratio, 20);

	// Reset the matrix to the identity matrix
	CP_Settings_ResetMatrix();
}

/*!
@brief	Updates piercing attack at every frame
@param  NIL
@return NIL
*//*______________________________________________________________*/
void update_piercing_bullet_travel(void) {
	for (int i = 0; i < MAX_PIERCING_BULLET; i++) {

		if (!(piercing_bullet_pool[i].y == 0 && piercing_bullet_pool[i].x == 0)) { //If bullet is active
			piercing_bullet_pool[i] = enemy_moving_up_down_left_right(piercing_bullet_pool[i], PIERCING_BULLET_SPEED, UP); //update it's position

			if (piercing_bullet_pool[i].y < -HEIGHT / 2) {
				piercing_bullet_pool[i] = CP_Vector_Set(0, 0);
			}
		}
	}
	print_piercing_bullet();
	//piercing_bullet_collision();
}

/*!
@brief	Prints the piercing attack at every frame
@param  NIL
@return NIL
*//*______________________________________________________________*/
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
			CP_Image_Draw(arrow_pic, BULLET_WIDTH * charge_pool[i] / 2, 0, BULLET_WIDTH * charge_pool[i], BULLET_LENGTH * charge_pool[i], 255);

			// Reset the matrix to the identity matrix
			CP_Settings_ResetMatrix();
		}
	}
}

/*!
@brief	Resets all variables, struct and pool as indicated in the function
@param  NIL
@return NIL
*//*______________________________________________________________*/
void reset_enemy_and_weapon(void) {
	//enemy_pool
	printf("resets enemy and weapon!!!\n");
	memset(enemy_pool, 0, sizeof(enemy_pool));
	memset(spawn_pool, 0, sizeof(spawn_pool));
	memset(mother_enemy_pool, 0, sizeof(mother_enemy_pool));

	memset(bullet_pool, 0, sizeof(bullet_pool));
	memset(explosion_pool, 0, sizeof(explosion_pool));
	memset(shrapnel_pool, 0, sizeof(shrapnel_pool));
	memset(sword_explosion_pool, 0, sizeof(sword_explosion_pool));
	memset(piercing_bullet_pool, 0, sizeof(piercing_bullet_pool));

	memset(charge_pool, 0, sizeof(charge_pool));
	memset(explosion_radius_pool, 0, sizeof(explosion_radius_pool));
	memset(sword_explosion_radius_pool, 0, sizeof(sword_explosion_radius_pool));

	memset(item_pool, 0, sizeof(item_pool));
}


float num_position_x = SKILLS_BUTTON_WIDTH * ((0.5f - NUM_POSITION_RATIO) / 2 + NUM_POSITION_RATIO);
/*!
@brief	Prints the number of upgrade purchased from the skill tree
@param  current_button - button that was triggered
@return NIL
*//*______________________________________________________________*/
void skills_num_printer(button current_button) {
	switch (current_button.state) {
		case 0:
			break;
		case 1:
			CP_Image_Draw(Image_num_1, current_button.position.x + num_position_x, current_button.position.y, SKILLS_BUTTON_HEIGHT, SKILLS_BUTTON_HEIGHT, 255);
			break;
		case 2:
			CP_Image_Draw(Image_num_2, current_button.position.x + num_position_x, current_button.position.y, SKILLS_BUTTON_HEIGHT, SKILLS_BUTTON_HEIGHT, 255);
			break;
		case 3:
			CP_Image_Draw(Image_num_3, current_button.position.x + num_position_x, current_button.position.y, SKILLS_BUTTON_HEIGHT, SKILLS_BUTTON_HEIGHT, 255);
			break;
		case 4:
			CP_Image_Draw(Image_num_4, current_button.position.x + num_position_x, current_button.position.y, SKILLS_BUTTON_HEIGHT, SKILLS_BUTTON_HEIGHT, 255);
			break;
		case 5:
			CP_Image_Draw(Image_num_5, current_button.position.x + num_position_x, current_button.position.y, SKILLS_BUTTON_HEIGHT, SKILLS_BUTTON_HEIGHT, 255);
			break;
		case 6:
			CP_Image_Draw(Image_num_6, current_button.position.x + num_position_x, current_button.position.y, SKILLS_BUTTON_HEIGHT, SKILLS_BUTTON_HEIGHT, 255);
			break;
		case 7:
			CP_Image_Draw(Image_num_7, current_button.position.x + num_position_x, current_button.position.y, SKILLS_BUTTON_HEIGHT, SKILLS_BUTTON_HEIGHT, 255);
			break;
		case 8:
			CP_Image_Draw(Image_num_8, current_button.position.x + num_position_x, current_button.position.y, SKILLS_BUTTON_HEIGHT, SKILLS_BUTTON_HEIGHT, 255);
			break;
		case 9:
			CP_Image_Draw(Image_num_9, current_button.position.x + num_position_x, current_button.position.y, SKILLS_BUTTON_HEIGHT, SKILLS_BUTTON_HEIGHT, 255);
			break;
		case 10:
			CP_Image_Draw(Image_num_10, current_button.position.x + num_position_x, current_button.position.y, SKILLS_BUTTON_HEIGHT, SKILLS_BUTTON_HEIGHT, 255);
			break;
		default:
			CP_Image_Draw(Image_num_10, current_button.position.x + num_position_x, current_button.position.y, SKILLS_BUTTON_HEIGHT, SKILLS_BUTTON_HEIGHT, 255);
			break;
	}
}

/*!
@brief	refunds skill point when triggered
@param  current_button - pointer to button that was triggered
		mouse - position of mouse
@return NIL
*//*______________________________________________________________*/
void refund_skill(button* current_button, CP_Vector mouse) {
	if (current_button -> state) {
		if (button_collision(mouse, current_button -> position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) {
			Exp++;
			current_button -> state--;
			play_click();
		}
	}
}

/*!
@brief	buys skill with skill point when triggered
@param  current_button - pointer to button that was triggered
		mouse - position of mouse
		max_upgrade - the max upgrade for the button clicked
@return NIL
*//*______________________________________________________________*/
void buy_skill(button* current_button, CP_Vector mouse, int max_upgrade) {
	if (Exp > 0 && current_button -> state < max_upgrade) {
		if (button_collision(mouse, current_button -> position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) {
			Exp--;
			current_button -> state++;
			play_coins();
		}
	}
}

/*!
@brief	prints description when mouse is hovering over skills button
@param  NIL
@return NIL
*//*______________________________________________________________*/
void skill_description_printer(void) {
	CP_Vector mouse = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());

	//This is the setting for the text
	CP_Settings_TextSize(20);
	CP_Settings_Fill(COLOR_GOLD);
	CP_Font_Set(CP_Font_GetDefault());

	float printing_location_x = mouse.x + 30;
	float printing_location_y = mouse.y - 30;

	//If the text prints out of the screen, make sure it stays inside the screen
	if (mouse.x + SKILLS_BUTTON_WIDTH / 2 > WIDTH) printing_location_x = mouse.x - 30 - SKILLS_BUTTON_WIDTH / 2;

	if (button_collision(mouse, skill_arrow_charge.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) CP_Font_DrawTextBox(skill_arrow_charge.description, printing_location_x, printing_location_y, SKILLS_BUTTON_WIDTH / 2);
	if (button_collision(mouse, skill_arrow_size.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) CP_Font_DrawTextBox(skill_arrow_size.description, printing_location_x, printing_location_y, SKILLS_BUTTON_WIDTH / 2);
	if (button_collision(mouse, skill_attack_speed.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) CP_Font_DrawTextBox(skill_attack_speed.description, printing_location_x, printing_location_y, SKILLS_BUTTON_WIDTH / 2);
	if (button_collision(mouse, skill_blast_range.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) CP_Font_DrawTextBox(skill_blast_range.description, printing_location_x, printing_location_y, SKILLS_BUTTON_WIDTH / 2);
	if (button_collision(mouse, skill_health.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) CP_Font_DrawTextBox(skill_health.description, printing_location_x, printing_location_y, SKILLS_BUTTON_WIDTH / 2);
	if (button_collision(mouse, skill_movement.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) CP_Font_DrawTextBox(skill_movement.description, printing_location_x, printing_location_y, SKILLS_BUTTON_WIDTH / 2);
	if (button_collision(mouse, skill_shrapnels.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) CP_Font_DrawTextBox(skill_shrapnels.description, printing_location_x, printing_location_y, SKILLS_BUTTON_WIDTH / 2);
	if (button_collision(mouse, skill_sword_range.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) CP_Font_DrawTextBox(skill_sword_range.description, printing_location_x, printing_location_y, SKILLS_BUTTON_WIDTH / 2);
	if (button_collision(mouse, skill_sword_swing.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) CP_Font_DrawTextBox(skill_sword_swing.description, printing_location_x, printing_location_y, SKILLS_BUTTON_WIDTH / 2);
	if (button_collision(mouse, skill_sword_crit.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) CP_Font_DrawTextBox(skill_sword_crit.description, printing_location_x, printing_location_y, SKILLS_BUTTON_WIDTH / 2);
}
