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
PlayerGethealth(void)   returns int current health amount 

// art not included
// contact isaac to instance new hp bar
*/

#include <stdio.h>
#include "cprocessing.h"
#include "game.h"

#define pueple CP_Color_Create(255, 0, 0, 255)


CP_Image Image_PrepRoom_Empty = NULL;
CP_Image Image_Upgrade_Empty = NULL;
CP_Image Image_Skill_Empty = NULL;
CP_Image Image_Shop_Empty = NULL;

CP_Image Image_Skill_HeartsOn = NULL;
CP_Image Image_Skill_AgilitOn = NULL;
CP_Image Image_Skill_AtkspeedOn = NULL;

CP_Image Image_Skill_HeartsOff = NULL;
CP_Image Image_Skill_AgilitOff = NULL;
CP_Image Image_Skill_AtkspeedOff = NULL;


CP_Image Image_Shop_HealOn = NULL;
CP_Image Image_Shop_DropsOn = NULL;
CP_Image Image_Shop_RezOn = NULL;
CP_Image Image_Shop_ShrapnelOn = NULL;

CP_Image Image_Shop_HealOff = NULL;
CP_Image Image_Shop_DropsOff = NULL;
CP_Image Image_Shop_RezOff = NULL;
CP_Image Image_Shop_ShrapnelOff = NULL;

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

float isaac_width;
float isaac_height;


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


struct PrepRoom_Background {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}PrepRoom_Background;

struct PrepRoom_ContinueButton {

	float posX;
	float posY;
	float width;
	float height;
}PrepRoom_ContinueButton;

struct PrepRoom_QuitButton {

	float posX;
	float posY;
	float width;
	float height;
}PrepRoom_QuitButton;

struct PrepRoom_UpgrradesButton {

	float posX;
	float posY;
	float width;
	float height;
}PrepRoom_UpgradesButton;



struct Upgrade_Background {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Upgrade_Background;

struct Upgrade_SkillButton {

	float posX;
	float posY;
	float width;
	float height;
}Upgrade_SkillButton;

struct Upgrade_ShopButton {

	float posX;
	float posY;
	float width;
	float height;
}Upgrade_ShopButton;

struct Upgrade_BackButton {

	float posX;
	float posY;
	float width;
	float height;
}Upgrade_BackButton;




struct Skill_Background {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Skill_Background;

struct Skill_HeartsButton {
	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Skill_HeartsButton;

struct Skill_AgilityButton {
	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Skill_AgilityButton;

struct Skill_AtkspeedButton {
	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Skill_AtkspeedButton;

struct Skill_BackButton {

	float posX;
	float posY;
	float width;
	float height;
}Skill_BackButton;



struct Shop_Background {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Shop_Background;

struct Shop_BackButton {

	float posX;
	float posY;
	float width;
	float height;
}Shop_BackButton;

struct Shop_HealButton {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Shop_HealButton;

struct Shop_DropsButton {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Shop_DropsButton;

struct Shop_RezButton {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Shop_RezButton;

struct Shop_ShrapnelButton {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Shop_ShrapnelButton;




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


void InitializeSkillShopUI(void)         // new function 
{
	
	//isaac_width = (float)CP_System_GetWindowWidth();
	//isaac_height = (float)CP_System_GetWindowHeight();

	isaac_width = WIDTH;
	isaac_height = HEIGHT;

	PrepRoom_Background.enabled = TRUE;
	PrepRoom_Background.width = isaac_width;
	PrepRoom_Background.height = isaac_height;
	PrepRoom_Background.posX = (float)(isaac_width /2.0);
	PrepRoom_Background.posY = (float)(isaac_height /2.0);


	Upgrade_Background.enabled = TRUE;
	Upgrade_Background.width = isaac_width;
	Upgrade_Background.height = isaac_height;
	Upgrade_Background.posX = (float)(isaac_width /2.0);
	Upgrade_Background.posY = (float)(isaac_height /2.0);

	Skill_Background.enabled = TRUE;
	Skill_Background.width = isaac_width;
	Skill_Background.height = isaac_height;
	Skill_Background.posX = (float)(isaac_width /2.0);
	Skill_Background.posY = (float)(isaac_height /2.0);

	Shop_Background.enabled = TRUE;
	Shop_Background.width = isaac_width;
	Shop_Background.height = isaac_height;
	Shop_Background.posX = (float)(isaac_width /2.0);
	Shop_Background.posY = (float)(isaac_height /2.0);


	Skill_HeartsButton.enabled = TRUE;
	Skill_AgilityButton.enabled = TRUE;
	Skill_AtkspeedButton.enabled = TRUE;

	Shop_HealButton.enabled = TRUE;
	Shop_DropsButton.enabled = TRUE;
	Shop_RezButton.enabled = TRUE;
	Shop_ShrapnelButton.enabled = TRUE;

	Image_PrepRoom_Empty = CP_Image_Load("./Assets/preproom.png");
	Image_Upgrade_Empty = CP_Image_Load("./Assets/upgrades.png");
	Image_Skill_Empty = CP_Image_Load("./Assets/Skill_empty.png");
	Image_Shop_Empty = CP_Image_Load("./Assets/Shop_empty.png");

	Image_Skill_HeartsOn = CP_Image_Load("./Assets/Skill_heartsOn.png");
	Image_Skill_AgilitOn = CP_Image_Load("./Assets/Skill_agilityOn.png");
	Image_Skill_AtkspeedOn = CP_Image_Load("./Assets/Skill_attackspeedOn.png");

	Image_Skill_HeartsOff = CP_Image_Load("./Assets/Skill_heartsOff.png");
	Image_Skill_AgilitOff = CP_Image_Load("./Assets/Skill_agilityOff.png");
	Image_Skill_AtkspeedOff = CP_Image_Load("./Assets/Skill_attackspeedOff.png");

	Image_Shop_HealOn = CP_Image_Load("./Assets/Shop_2xhealOn.png");
	Image_Shop_DropsOn = CP_Image_Load("./Assets/Shop_2xdropsOn.png");
	Image_Shop_RezOn = CP_Image_Load("./Assets/Shop_rezOn.png");
	Image_Shop_ShrapnelOn = CP_Image_Load("./Assets/Shop_shrapnelOn.png");

	Image_Shop_HealOff = CP_Image_Load("./Assets/Shop_2xhealOff.png");
	Image_Shop_DropsOff = CP_Image_Load("./Assets/Shop_2xdropsOff.png");
	Image_Shop_RezOff = CP_Image_Load("./Assets/Shop_rezOff.png");
	Image_Shop_ShrapnelOff = CP_Image_Load("./Assets/Shop_shrapnelOff.png");
	
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

int PlayerGethealth(void)
{
	return p1.get(&p1);
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


void Screen_PREPROOM_Print(void)											//new functuon
{
	

	PrepRoom_ContinueButton.posX = 270.0f;
	PrepRoom_ContinueButton.posY = 550.0f;
/*
	PrepRoom_QuitButton.posX = menu.height * (3.0f / 7.0f);
	PrepRoom_QuitButton.posY = menu.height * (3.0f / 7.0f);

	PrepRoom_UpgrradesButton.posX = menu.height * (3.0f / 7.0f);
	PrepRoom_UpgrradesButton.posY = menu.height * (3.0f / 7.0f);
	
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
*/
	//CP_Graphics_ClearBackground(COLOR_BLACK);
	CP_Image_Draw(Image_PrepRoom_Empty, PrepRoom_Background.posX, PrepRoom_Background.posY, isaac_width, isaac_height, 255);
}
	

void Screen_UPGRADES_Print(void)											//new functuon
{
/*
	Upgrade_SkillButton.posX = menu.width / 2.0f;
	Upgrade_SkillButton.posY = menu.height * (3.0f / 7.0f);

	Upgrade_ShopButton.posX = menu.width / 2.0f;
	Upgrade_ShopButton.posY = menu.height * (3.0f / 7.0f);

	Upgrade_BackButton.posX = menu.width / 2.0f;
	Upgrade_BackButton.posY = menu.height * (3.0f / 7.0f);
*/

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_Upgrade_Empty, Upgrade_Background.posX, Upgrade_Background.posY, isaac_width, isaac_height, 255);


}

void Screen_SHOP_Print(void)
											//new functuon
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Graphics_ClearBackground(COLOR_BLACK);

	CP_Image_Draw(Image_Shop_Empty, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255);

	if (Shop_HealButton.enabled == TRUE)
	{
		CP_Image_Draw(Image_Shop_HealOn, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255);
	}
	else
	{
		CP_Image_Draw(Image_Shop_HealOff, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255) ;
	}
		

	if (Shop_DropsButton.enabled == TRUE)
	{
		(CP_Image_Draw(Image_Shop_DropsOn, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255));
	}
	else
	{
		//printf("False");
		CP_Image_Draw(Image_Shop_DropsOff, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255);
	}

	if (Shop_RezButton.enabled == TRUE)
	{
		CP_Image_Draw(Image_Shop_RezOn, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255);
	}
	else
	{
		CP_Image_Draw(Image_Shop_RezOff, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255);
	}

	
	if (Shop_ShrapnelButton.enabled == TRUE)
	{
		CP_Image_Draw(Image_Shop_ShrapnelOn, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255);
	}
	else
	{
		CP_Image_Draw(Image_Shop_ShrapnelOff, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255);
	}
	
}

void Screen_SKILL_Print(void)											//new functuon
{

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_Skill_Empty, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);

	if (Skill_HeartsButton.enabled == TRUE)
	{
		CP_Image_Draw(Image_Skill_HeartsOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
	}
	else
	{
		CP_Image_Draw(Image_Skill_HeartsOff, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
	}

	if (Skill_AgilityButton.enabled == TRUE)
	{
		CP_Image_Draw(Image_Skill_AgilitOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
	}
	else
	{
		P_Image_Draw(Image_Skill_AgilitOff, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
	}

	if (Skill_AtkspeedButton.enabled == TRUE)
	{
		CP_Image_Draw(Image_Skill_AtkspeedOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
	}
	else
	{
		CP_Image_Draw(Image_Skill_AtkspeedOff, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
	}

}


BOOL IsaacCheckCollisionWithButtonImage(float posX, float posY, float startX, float starty, float endx, float endy)											//new functuon
{

	if ((posX < endx && posX > startX)
		&& (posY < endy && posY > starty))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

void Screen_PREPROOM_ButtonClicked(void)											//new functuon
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		//printf("%f", mousePosX);
		//if (CheckCollisionWithBox(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		//{
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 270.0, 550.0, 684.0, 676.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed continye \n");
		}
	
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 309.0, 827.0, 511.0, 916.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed quit\n");
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 597.0, 827.0, 913.0, 915.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed upgrade\n");
		}

	}
}

void Screen_UPGRADE_ButtonClicked(void)											//new functuon
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		//printf("%f", mousePosX);
		//if (CheckCollisionWithBox(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		//{
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 792.0, 24.0, 952.0, 160.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed back \n");
		}

		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 31.0, 349.0, 414.0, 730.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed skill\n");
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 552.0, 353.0, 936.0, 730.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed shop\n");
		}

	}
}

void Screen_SHOP_ButtonClicked(void)											//new functuon
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		//printf("%f", mousePosX);
		//if (CheckCollisionWithBox(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		//{
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 787.0, 27.0, 936.0, 154.0))
		{
			//menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_BLACK);
			//gameState = PLAYING;
			printf("button pressed back \n");
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 26.0, 546.0, 459.0, 671.0))
		{
			//menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_BLACK);
			//gameState = PLAYING;
			printf("button pressed heal\n");
			Shop_HealButton.enabled = FALSE;
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 25.0, 690.0, 460.0, 843.0))
		{
			//menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_BLACK);
			//gameState = PLAYING;
			printf("button pressed drop\n");
			Shop_DropsButton.enabled = FALSE;
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 25.0, 833.0, 460.0, 955.0))
		{
			//menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_BLACK);
			//gameState = PLAYING;
			
			printf("button pressed rez\n");
			Shop_RezButton.enabled = FALSE;
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 511.0, 543.0, 943.0, 661.0))
		{
			//menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_BLACK);
			//gameState = PLAYING;
			printf("button pressed shrapnel\n");
			Shop_ShrapnelButton.enabled = FALSE;

		}

	}
}

void Screen_SKILL_ButtonClicked(void)											//new functuon
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		//printf("%f", mousePosX);
		//if (CheckCollisionWithBox(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		//{
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 767.0, 28.0, 924.0, 153.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed back \n");
		}

		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 44.0, 540.0, 483.0, 668.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed hearts\n");
			Skill_HeartsButton.enabled = FALSE;

		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 44.0, 683.0, 480.0, 811.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed agility\n");
			Skill_AgilityButton.enabled = FALSE;
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 44.0, 832.0, 480.0, 958.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed atkspeed\n");
			Skill_AtkspeedButton.enabled = FALSE;
		}

	}
}

void exit_skilltreepictures(void) 
{
	CP_Image_Free(&Image_PrepRoom_Empty);
	CP_Image_Free(&Image_Upgrade_Empty);
	CP_Image_Free(&Image_Skill_Empty);
	CP_Image_Free(&Image_Shop_Empty);

	CP_Image_Free(&Image_Skill_HeartsOn);
	CP_Image_Free(&Image_Skill_AgilitOn);
	CP_Image_Free(&Image_Skill_AtkspeedOn);

	CP_Image_Free(&Image_Skill_HeartsOff);
	CP_Image_Free(&Image_Skill_AgilitOff);
	CP_Image_Free(&Image_Skill_AtkspeedOff);

	CP_Image_Free(&Image_Shop_HealOn);
	CP_Image_Free(&Image_Shop_DropsOn);
	CP_Image_Free(&Image_Shop_RezOn);
	CP_Image_Free(&Image_Shop_ShrapnelOn);


	CP_Image_Free(&Image_Shop_HealOff);
	CP_Image_Free(&Image_Shop_DropsOff);
	CP_Image_Free(&Image_Shop_RezOff);
	CP_Image_Free(&Image_Shop_ShrapnelOff);


}