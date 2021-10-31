/*---------------------------------------------------------
 * file:	game.c
 * author:	
 * email:	
*
 * brief:	
*
 * documentation link:
 * https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
*
 * Copyright � 2020 DigiPen, All rights reserved.
* ---------------------------------------------------------*/
/*
Functions to call to modify hp
PlayerSetHealth (int Basehealth)
Playertakedamage(int damageAmt)
PlayerHealed(int healAmt)

// art not included
// contact isaac to instance new hp bar
*/

#include <stdio.h>
#include "cprocessing.h"
#include "game.h"

#define pueple CP_Color_Create(255, 0, 0, 255)

//Heart sprite settings below
static CP_Image spriteSheetImage;
static int imageIndex; // decides what image it uses 
static const float Heart_FRAME_DIMENSIONx = 58.0f;
static const float Heart_FRAME_DIMENSIONy = 45.0f;
int player_maxhp;
static  float Heart_size_windowsx;
static  float Heart_size_windowsy;

static float hplocationX = 100.0f;
static float hplocationY = 100.0f;
//Heart sprite settings above


// do not temper any thing from here to next comment
// HealthSystem Object decleration below
#define NewHealthSystem(VarName)	\
	VarName.set = setter;			\
	VarName.get = getter;			\
	VarName.damage = damager;		\
	VarName.heal = healer;

typedef struct HealthSystem {
	int health;
	void (*set)(struct HealthSystem* inst, int);
	int (*get)(struct HealthSystem*);
	void (*damage)(struct HealthSystem* inst, int);
	void (*heal)(struct HealthSystem* inst, int);
} HealthSystem;

HealthSystem p1;

void setter(HealthSystem* inst, int health)
{
	inst->health = health;
	player_maxhp = health;

}

int getter(HealthSystem* inst)
{
	return inst->health;
}

void damager(HealthSystem* inst, int damageamount)
{
	inst->health -= damageamount;
}

void healer(HealthSystem* inst, int healamount)
{
	if (inst->health < player_maxhp)
	{
		inst->health += healamount;
	}
	//inst->health += healamount;
}
// HealthSystem Object decleration above 

//Heart sprite settings below

//Heart sprite settings above

void init_PlayerHP(void)
{
	spriteSheetImage = CP_Image_Load("./Assets/HeartSprite.png");
	NewHealthSystem(p1)
	p1.set(&p1, 10);

	hplocationX = (CP_System_GetWindowWidth()) / 10.0f;
	hplocationY = (CP_System_GetWindowHeight()) / 8.0f;
	// size of the heart 
	Heart_size_windowsx = (CP_System_GetWindowWidth()) / 5.0f;
	Heart_size_windowsy = (CP_System_GetWindowHeight()) / 5.0f;
}
void exit_PlayerHP(void)
{
	CP_Image_Free(&spriteSheetImage);
}

//call function to set players base health 
void PlayerSetHealth (int Basehealth)
{
    p1.set(&p1,Basehealth);

}
// call function when player takes damage and enter amount of damage taken 
void Playertakedamage(int damageAmt)
{
    p1.damage(&p1, damageAmt);
}
// call function when player is healed and enter amount healed
void PlayerHealed(int healAmt)
{
    p1.heal(&p1, healAmt);
}


void Player_Emptyheartprinter(void)
{
	int playerhp = p1.get(&p1);
	int Eplayerhp = player_maxhp - playerhp;
	imageIndex = 0;
	imageIndex = (imageIndex + 1) % 2; // decides which spritte to take on the sheet, adjust hard coded initialising at the top 

	//spriteSheetImage = CP_Image_Load("./Assets/HeartSptite.png");
	for (int y = 0; y < Eplayerhp; y++)
	{
		CP_Image_DrawSubImage(spriteSheetImage, // image used 
			hplocationX + ((y + playerhp) * (Heart_size_windowsx - 60.0f)) + (Heart_FRAME_DIMENSIONx * (y + playerhp)), hplocationY, // coordinates of where the sprite is drawn
			Heart_size_windowsx, Heart_size_windowsy,   // image size on window 
			imageIndex * Heart_FRAME_DIMENSIONx, 0, // image selection  by parts. first image = 0 + 1 % 4 = 1, second image = 1 + 1 % 4 = 2, third image = 2 + 1 % 4 = 3 , forth image = 3+1 % 4 = 0 
			// image 4 / 4 is the first one on the sprite sheet
			// horizontal movement, vertical movement
			// frame diemnsion is 1 sprite on the sprite sheet
			// left most pixel, top most pixel (top left corner )
			(imageIndex + 1) * Heart_FRAME_DIMENSIONx, Heart_FRAME_DIMENSIONy, // right most pixel, bottom most pixel (bottom right corner )
			255); // alpha value that affects transpaarency
	}

	//CP_Image_Free(&spriteSheetImage);

}

void Player_Redheartprinter(void)
{
	int playerhp = p1.get(&p1);

	imageIndex = 1;
	imageIndex = (imageIndex + 1) % 2; // decides which spritte to take on the sheet, adjust hard coded initialising at the top 

	//spriteSheetImage = CP_Image_Load("./Assets/HeartSptite.png");
	for (int y = 0; y < playerhp; y++)
	{
		CP_Image_DrawSubImage(spriteSheetImage,
			hplocationX + (y * (Heart_size_windowsx - 60.0f)) + (y * Heart_FRAME_DIMENSIONx), hplocationY, // coordinates of where the sprite is drawn
			Heart_size_windowsx, Heart_size_windowsy,   // image size on window 
			imageIndex * Heart_FRAME_DIMENSIONx, 0, // image selection  by parts. first image = 0 + 1 % 4 = 1, second image = 1 + 1 % 4 = 2, third image = 2 + 1 % 4 = 3 , forth image = 3+1 % 4 = 0 
			// image 4 / 4 is the first one on the sprite sheet
			// horizontal movement, vertical movement
			// frame diemnsion is 1 sprite on the sprite sheet
			// left most pixel, top most pixel (top left corner )
			(imageIndex + 1) * Heart_FRAME_DIMENSIONx, Heart_FRAME_DIMENSIONy, // right most pixel, bottom most pixel (bottom right corner )
			255); // alpha value that affects transpaarency
	}
	//CP_Image_Free(&spriteSheetImage);
}
