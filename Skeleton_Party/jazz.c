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
#include "cprocessing.h"
#include "game.h"

//These variables are for melee attacks, for function 'melee_attack' and 'activate_melee_by_mouse'
int first_time = 1, * pfirst_time = &first_time; //First time running the function
float melee_start_angle = 135; //Determines where the melee attack is facing. 135 is when it's facing north.
int melee_max_angle = 90; //starting melee angle
int melee_anticlockwise = FALSE; //clockwise or anti clockwise melee
int melee_speed = 10; //speed of melee animation
int melee_angle_upgrade = 40; //angle upgrade for melee

int melee_or_not = 0, * pmelee_or_not = &melee_or_not; //Determine if should melee or not
CP_Vector melee_position; //Position of where the melee animation happens

/*This function melee*/
void melee_attack(float *melee_angle,CP_Vector position) {
	//Set the melee angle for the first time
	if (first_time) {
		*pfirst_time = 0;
		melee_start_angle -= melee_angle_upgrade;
		melee_max_angle += (int)melee_start_angle + 2*melee_angle_upgrade;
		*melee_angle = melee_start_angle;
	}

	//This determines the speed of the rectangle swinging. **Beware, it skips some areas, so might not hit enemies that are too small**
	*melee_angle += melee_speed;

	//This determines if the attack is counter clockwise or clockwise
	if (melee_anticlockwise) *melee_angle *= -1; 
	
	//This sets the starting location of the action.
	//CP_Vector position = CP_Vector_Set(CP_System_GetWindowWidth() / 4.0f, CP_System_GetWindowHeight() / 4.0f);

	// Create transform matrices
	CP_Vector vec2_set = CP_Vector_Set(0.001f, 0.001f); //These value should be very small, afterwards scale the rectangle up. This will create an effect where the rectangle is pure color, no black border. To explain better, make these values 1 to try it out.
	CP_Matrix scale = CP_Matrix_Scale(vec2_set);
	CP_Matrix translate = CP_Matrix_Translate(position);
	CP_Matrix rotate = CP_Matrix_Rotate((float)*melee_angle);

	// Combine transfrom
	// Translate * rotation * scale
	CP_Matrix transform = CP_Matrix_Multiply(translate, CP_Matrix_Multiply(rotate, scale));

	// Set the camera transfrom to the created matrix
	CP_Settings_ApplyMatrix(transform);

	// Draw a blue rectangle that rotates
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	CP_Graphics_DrawRect(0, 0, 10000, 100000);

	// Reset the matrix to the identity matrix
	CP_Settings_ResetMatrix();

	//Resets the animation of the attack
	printf("angle: %f", *melee_angle);
	if (!(-melee_max_angle < *melee_angle && *melee_angle < melee_max_angle)) {
		*melee_angle = melee_start_angle;
		*pmelee_or_not = 0;
	}
	//Resets the melee angle back to positive
	if (*melee_angle < 0) *melee_angle *= -1;
}


void activate_melee_by_mouse(float *melee_angle) {
	melee_position = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
	//Check for mouse input
	if (!(*pmelee_or_not)) {
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
			*pmelee_or_not = 1;
			//Get mouse input position and parse into melee_attack
		}
	}
	if (*pmelee_or_not) {
		melee_attack(melee_angle, melee_position);
	}
}