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

#define COLOR_GRAY CP_Color_Create(127, 127, 127, 255)
#define COLOR_GREEN CP_Color_Create(0, 255, 0, 255)
#define COLOR_BLUE CP_Color_Create(0, 0, 255, 255)
#define COLOR_WHITE CP_Color_Create(255, 255, 255, 255)

//These variables are for melee attacks, for function 'melee_attack' and 'activate_melee_by_mouse'
int first_time = 1, * pfirst_time = &first_time; //First time running the function
int melee_max_angle = 90; //starting melee angle
int melee_anticlockwise = TRUE; //clockwise or anti clockwise melee
int melee_speed = 10; //speed of melee animation

int melee_or_not = 0, * pmelee_or_not = &melee_or_not; //Determine if should melee or not
CP_Vector melee_position; //Position of where the melee animation happens

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

	// Create transform matrices
	CP_Matrix rotate = CP_Matrix_Rotate((float)*melee_angle);


	// Set the camera transfrom to the created matrix
	CP_Settings_ApplyMatrix(transform);

	// Draw a blue rectangle that rotates
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));

	// Reset the matrix to the identity matrix
	CP_Settings_ResetMatrix();

	}


}

	//Check for mouse input
	if (!(*pmelee_or_not)) {
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
			*pmelee_or_not = 1;
			//Get mouse input position and parse into melee_attack
		}
	}
	if (*pmelee_or_not) {
	}
}

void lightbulb(void) {
		CP_Settings_Fill(COLOR_GREEN);
	} else {
		CP_Settings_Fill(COLOR_WHITE);
	}
	CP_Graphics_DrawRect(WIDTH/10, HEIGHT/10, WIDTH / 10, HEIGHT / 10 );
}