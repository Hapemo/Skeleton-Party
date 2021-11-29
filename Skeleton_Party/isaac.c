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

#define Zero "0"
#define One "1"
#define Two "2"
#define Three "3"
#define Four "4"
#define Five "5"
#define Six "6"
#define Seven "7"
#define Eight "8"
#define Nine "9"
#define Ten "10"
#define Eleven "11"
#define Twelve "12"
#define Thirteen "13"
#define Fourteen "14"
#define Fifhteen "15"
#define Sixteen "16"
#define Seventeen "17"
#define Eighteen "18"
#define Nineteen "19"
#define Twenty "20"



CP_Font SkullFont;

//SkullFont = CP_Font_Load( "./Assets/Font/Skull-Story.ttf");

CP_Image Image_GoldSprite = NULL;
CP_Image Image_ExpSprite = NULL;
CP_Image Image_ReztokenSprite = NULL;




CP_Image Image_PrepRoom_Empty = NULL;
CP_Image Image_Upgrade_Empty = NULL;
CP_Image Image_Skill_Empty = NULL;
CP_Image Image_Shop_Empty = NULL;

CP_Image Image_Skill_HeartsOn = NULL;
CP_Image Image_Skill_HeartsOn1 = NULL;
CP_Image Image_Skill_HeartsOn2 = NULL;
CP_Image Image_Skill_HeartsOn3 = NULL;
CP_Image Image_Skill_HeartsOn4 = NULL;
CP_Image Image_Skill_HeartsOn5 = NULL;

CP_Image Image_Skill_AgilitOn = NULL;
CP_Image Image_Skill_AgilitOn1 = NULL;
CP_Image Image_Skill_AgilitOn2 = NULL;
CP_Image Image_Skill_AgilitOn3 = NULL;
CP_Image Image_Skill_AgilitOn4 = NULL;
CP_Image Image_Skill_AgilitOn5 = NULL;

//CP_Image Image_Skill_CritOn = NULL;
//CP_Image Image_Skill_CritOn = NULL;

CP_Image Image_Skill_CritOn = NULL;
CP_Image Image_Skill_Crit1 = NULL;
CP_Image Image_Skill_Crit2 = NULL;
CP_Image Image_Skill_Crit3 = NULL;
CP_Image Image_Skill_Crit4 = NULL;
CP_Image Image_Skill_Crit5 = NULL;
CP_Image Image_Skill_Crit6 = NULL;
CP_Image Image_Skill_Crit7 = NULL;
CP_Image Image_Skill_Crit8 = NULL;
CP_Image Image_Skill_Crit9 = NULL;
CP_Image Image_Skill_Crit10 = NULL;


//CP_Image Image_Skill_HeartsOff = NULL;
//CP_Image Image_Skill_AgilitOff = NULL;
//CP_Image Image_Skill_AtkspeedOff = NULL;


CP_Image Image_Shop_HealOn = NULL;
CP_Image Image_Shop_DropsOn = NULL;
CP_Image Image_Shop_RezOn = NULL;
CP_Image Image_Shop_ShrapnelOn = NULL;
CP_Image Image_Shop_Shockwave = NULL;

CP_Image Image_Shop_HealOff = NULL;
CP_Image Image_Shop_DropsOff = NULL;
CP_Image Image_Shop_RezOff = NULL;
CP_Image Image_Shop_ShrapnelOff = NULL;

CP_Image Image_Pause_Mistake = NULL;
CP_Image Image_Win_Background = NULL;
CP_Image Image_Gameover_Background = NULL;

CP_Image Image_YouDied_Background = NULL;
CP_Image Image_Revive_Background = NULL;

CP_Image Number_Skill_Zero = NULL;
CP_Image Number_Skill_One = NULL;
CP_Image Number_Skill_Two = NULL;
CP_Image Number_Skill_Three = NULL;
CP_Image Number_Skill_Four = NULL;
CP_Image Number_Skill_Five = NULL;
CP_Image Number_Skill_Six = NULL;
CP_Image Number_Skill_Seven = NULL;



//Heart sprite settings below
static CP_Image spriteSheetImage;
static int imageIndex; // decides what image it uses 
static const float Heart_FRAME_DIMENSIONx = 58.0f;
static const float Heart_FRAME_DIMENSIONy = 45.0f;
int player_maxhp;
int additionalhp, maxadditionalhp;
int additionalspeed, maxadditionalspeed;
int maxadditionalcrit;
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


struct Revive_Background {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Revive_Background;


struct Currency_Sprite {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Currency_Sprite;

struct GameOver_Background {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}GameOver_Background;

struct Win_Background {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Win_Background;

struct Pause_Background {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Pause_Background;

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

struct Skill_CritButton {
	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Skill_CritButton;

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

struct Shop_Shockwave {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Shop_Shockwave;





//Heart sprite settings below

//Heart sprite settings above

void init_PlayerHP(void)
{
	spriteSheetImage = CP_Image_Load("./Assets/HeartSprite.png");
	NewHealthSystem(p1)
	p1.set(&p1, 3);

	maxadditionalhp = 5;
	additionalhp = 0;

	maxadditionalspeed = 80;
	additionalspeed = 0;

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
	
	//SkullFont = CP_Font_GetDefault();

	SkullFont = CP_Font_Load("./Assets/Font/Skull-Story.ttf");

	//SWORD_CRIT_CHANCE = 10;
	revivetoken = 0;
	Exp = 18;
	Gold = 19;
	additionalExp = 2;
	additionalGold = 1;

	additionalcrit = 0;
	maxadditionalcrit = 90;

	DoubleExp = FALSE;
	DoubleGold = FALSE;
	DoubleDrop = FALSE;
	DoubleHeal = FALSE;
	MainMenuState = TRUE;
	

	isaac_width = WIDTH;
	isaac_height = HEIGHT;

	shrapnelstate = FALSE;
	shockwavestate = FALSE;
	RewardGiven = FALSE;


	Revive_Background.enabled = TRUE;
	Revive_Background.width = isaac_width;
	Revive_Background.height = isaac_height;
	Revive_Background.posX = (float)(isaac_width / 2.0);
	Revive_Background.posY = (float)(isaac_height / 2.0);
	
	Currency_Sprite.enabled = TRUE;
	Currency_Sprite.width = isaac_width;
	Currency_Sprite.height = isaac_height;
	Currency_Sprite.posX = (float)(isaac_width / 2.0);
	Currency_Sprite.posY = (float)(isaac_height / 2.0);



	GameOver_Background.enabled = TRUE;
	GameOver_Background.width = isaac_width;
	GameOver_Background.height = isaac_height;
	GameOver_Background.posX = (float)(isaac_width / 2.0);
	GameOver_Background.posY = (float)(isaac_height / 2.0);
	
	GameOver_Background.enabled = TRUE;
	GameOver_Background.width = isaac_width;
	GameOver_Background.height = isaac_height;
	GameOver_Background.posX = (float)(isaac_width / 2.0);
	GameOver_Background.posY = (float)(isaac_height / 2.0);

	Win_Background.enabled = TRUE;
	Win_Background.width = isaac_width;
	Win_Background.height = isaac_height;
	Win_Background.posX = (float)(isaac_width / 2.0);
	Win_Background.posY = (float)(isaac_height / 2.0);

	Pause_Background.enabled = TRUE;
	Pause_Background.width = isaac_width;
	Pause_Background.height = isaac_height;
	Pause_Background.posX = (float)(isaac_width / 2.0);
	Pause_Background.posY = (float)(isaac_height / 2.0);


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
	Skill_CritButton.enabled = TRUE;

	Shop_HealButton.enabled = TRUE;
	Shop_DropsButton.enabled = TRUE;
	Shop_RezButton.enabled = TRUE;
	Shop_ShrapnelButton.enabled = TRUE;

	Image_GoldSprite = CP_Image_Load("./Assets/goldsprite.png");
	Image_ExpSprite = CP_Image_Load("./Assets/Exporb.png");
	Image_ReztokenSprite = CP_Image_Load("./Assets/ReviveToken.png");

	Image_PrepRoom_Empty = CP_Image_Load("./Assets/preproom.png");
	Image_Upgrade_Empty = CP_Image_Load("./Assets/upgrades.png");
	Image_Skill_Empty = CP_Image_Load("./Assets/Skill_empty.png");
	Image_Shop_Empty = CP_Image_Load("./Assets/Shop_empty.png");

	Image_Skill_HeartsOn = CP_Image_Load("./Assets/skilltree/Skill_heartsOn.png");
	Image_Skill_HeartsOn1 = CP_Image_Load("./Assets/skilltree/Skill_heartsOn1.png");
	Image_Skill_HeartsOn2 = CP_Image_Load("./Assets/skilltree/Skill_heartsOn2.png");
	Image_Skill_HeartsOn3 = CP_Image_Load("./Assets/skilltree/Skill_heartsOn3.png");
	Image_Skill_HeartsOn4 = CP_Image_Load("./Assets/skilltree/Skill_heartsOn4.png");
	Image_Skill_HeartsOn5 = CP_Image_Load("./Assets/skilltree/Skill_heartsOn5.png");

	Image_Skill_AgilitOn = CP_Image_Load("./Assets/skilltree/Skill_agilityOn.png");
	Image_Skill_AgilitOn1 = CP_Image_Load("./Assets/skilltree/Skill_agilityOn1.png");
	Image_Skill_AgilitOn2 = CP_Image_Load("./Assets/skilltree/Skill_agilityOn2.png");
	Image_Skill_AgilitOn3 = CP_Image_Load("./Assets/skilltree/Skill_agilityOn3.png");
	Image_Skill_AgilitOn4 = CP_Image_Load("./Assets/skilltree/Skill_agilityOn4.png");
	Image_Skill_AgilitOn5 = CP_Image_Load("./Assets/skilltree/Skill_agilityOn5.png");

	Image_Skill_CritOn = CP_Image_Load("./Assets/skilltree/Crit/Skill_critOn.png");
	Image_Skill_Crit1 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit1.png");
	Image_Skill_Crit2 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit2.png");
	Image_Skill_Crit3 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit3.png");
	Image_Skill_Crit4 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit4.png");
	Image_Skill_Crit5 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit5.png");
	Image_Skill_Crit6 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit6.png");
	Image_Skill_Crit7 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit7.png");
	Image_Skill_Crit8 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit8.png");
	Image_Skill_Crit9 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit9.png");
	Image_Skill_Crit10 = CP_Image_Load("./Assets/skilltree/Crit/Skil_crit10.png");



	Image_Shop_HealOn = CP_Image_Load("./Assets/Shop_2xhealOn.png");
	Image_Shop_DropsOn = CP_Image_Load("./Assets/Shop_2xdropsOn.png");
	Image_Shop_RezOn = CP_Image_Load("./Assets/Shop_rezOn.png");
	Image_Shop_ShrapnelOn = CP_Image_Load("./Assets/Shop_shrapnelOn.png");
	Image_Shop_Shockwave = CP_Image_Load("./Assets/Shop_ShockWave.png");


	Image_Shop_HealOff = CP_Image_Load("./Assets/Shop_2xhealOff.png");
	Image_Shop_DropsOff = CP_Image_Load("./Assets/Shop_2xdropsOff.png");
	Image_Shop_RezOff = CP_Image_Load("./Assets/Shop_rezOff.png");
	Image_Shop_ShrapnelOff = CP_Image_Load("./Assets/Shop_shrapnelOff.png");
	

	Image_Pause_Mistake = CP_Image_Load("./Assets/pause_mistake1.png");

	Image_Win_Background = CP_Image_Load("./Assets/winscreen.png");

	Image_Gameover_Background = CP_Image_Load("./Assets/GameOver.png");

	Image_YouDied_Background = CP_Image_Load("./Assets/youdiedRevive.png");
	Image_Revive_Background = CP_Image_Load("./Assets/Revive.png");

	maxadditionalhp = 5;
	additionalhp = 0;

	maxadditionalspeed = 80;
	additionalspeed = 0;

	hplocationX = (CP_System_GetWindowWidth()) / 10.0f;
	hplocationY = (CP_System_GetWindowHeight()) / 8.0f;
	// size of the heart 
	Heart_size_windowsx = (CP_System_GetWindowWidth()) / 5.0f;
	Heart_size_windowsy = (CP_System_GetWindowHeight()) / 5.0f;


}

void InitializeRetry(void)
        // new function 
	{

		//SkullFont = CP_Font_GetDefault();

		SkullFont = CP_Font_Load("./Assets/Font/Skull-Story.ttf");


		Exp = 18;
		Gold = 19;
		additionalExp = 2;
		additionalGold = 1;
		//DoubleExp = FALSE;
		//DoubleGold = FALSE;
		//DoubleDrop = FALSE;
		//DoubleHeal = FALSE;

		isaac_width = WIDTH;
		isaac_height = HEIGHT;

		//shrapnelstate = FALSE;
		//shockwavestate = FALSE;
		//RewardGiven = FALSE;




		Currency_Sprite.enabled = TRUE;
		Currency_Sprite.width = isaac_width;
		Currency_Sprite.height = isaac_height;
		Currency_Sprite.posX = (float)(isaac_width / 2.0);
		Currency_Sprite.posY = (float)(isaac_height / 2.0);



		GameOver_Background.enabled = TRUE;
		GameOver_Background.width = isaac_width;
		GameOver_Background.height = isaac_height;
		GameOver_Background.posX = (float)(isaac_width / 2.0);
		GameOver_Background.posY = (float)(isaac_height / 2.0);

		GameOver_Background.enabled = TRUE;
		GameOver_Background.width = isaac_width;
		GameOver_Background.height = isaac_height;
		GameOver_Background.posX = (float)(isaac_width / 2.0);
		GameOver_Background.posY = (float)(isaac_height / 2.0);

		Win_Background.enabled = TRUE;
		Win_Background.width = isaac_width;
		Win_Background.height = isaac_height;
		Win_Background.posX = (float)(isaac_width / 2.0);
		Win_Background.posY = (float)(isaac_height / 2.0);

		Pause_Background.enabled = TRUE;
		Pause_Background.width = isaac_width;
		Pause_Background.height = isaac_height;
		Pause_Background.posX = (float)(isaac_width / 2.0);
		Pause_Background.posY = (float)(isaac_height / 2.0);


		PrepRoom_Background.enabled = TRUE;
		PrepRoom_Background.width = isaac_width;
		PrepRoom_Background.height = isaac_height;
		PrepRoom_Background.posX = (float)(isaac_width / 2.0);
		PrepRoom_Background.posY = (float)(isaac_height / 2.0);


		Upgrade_Background.enabled = TRUE;
		Upgrade_Background.width = isaac_width;
		Upgrade_Background.height = isaac_height;
		Upgrade_Background.posX = (float)(isaac_width / 2.0);
		Upgrade_Background.posY = (float)(isaac_height / 2.0);

		Skill_Background.enabled = TRUE;
		Skill_Background.width = isaac_width;
		Skill_Background.height = isaac_height;
		Skill_Background.posX = (float)(isaac_width / 2.0);
		Skill_Background.posY = (float)(isaac_height / 2.0);

		Shop_Background.enabled = TRUE;
		Shop_Background.width = isaac_width;
		Shop_Background.height = isaac_height;
		Shop_Background.posX = (float)(isaac_width / 2.0);
		Shop_Background.posY = (float)(isaac_height / 2.0);

		Skill_HeartsButton.enabled = TRUE;
		Skill_AgilityButton.enabled = TRUE;
		Skill_CritButton.enabled = TRUE;

		Shop_HealButton.enabled = TRUE;
		Shop_DropsButton.enabled = TRUE;
		Shop_RezButton.enabled = TRUE;
		Shop_ShrapnelButton.enabled = TRUE;

		//Image_GoldSprite = CP_Image_Load("./Assets/goldsprite.png");
		//Image_ExpSprite = CP_Image_Load("./Assets/Exporb.png");

		//Image_PrepRoom_Empty = CP_Image_Load("./Assets/preproom.png");
		//Image_Upgrade_Empty = CP_Image_Load("./Assets/upgrades.png");
		//Image_Skill_Empty = CP_Image_Load("./Assets/Skill_empty.png");
		//Image_Shop_Empty = CP_Image_Load("./Assets/Shop_empty.png");

		//Image_Skill_HeartsOn = CP_Image_Load("./Assets/skilltree/Skill_heartsOn.png");
		//Image_Skill_HeartsOn1 = CP_Image_Load("./Assets/skilltree/Skill_heartsOn1.png");
		//Image_Skill_HeartsOn2 = CP_Image_Load("./Assets/skilltree/Skill_heartsOn2.png");
		//Image_Skill_HeartsOn3 = CP_Image_Load("./Assets/skilltree/Skill_heartsOn3.png");
		//Image_Skill_HeartsOn4 = CP_Image_Load("./Assets/skilltree/Skill_heartsOn4.png");
		//Image_Skill_HeartsOn5 = CP_Image_Load("./Assets/skilltree/Skill_heartsOn5.png");

		//Image_Skill_AgilitOn = CP_Image_Load("./Assets/skilltree/Skill_agilityOn.png");
		//Image_Skill_AgilitOn1 = CP_Image_Load("./Assets/skilltree/Skill_agilityOn1.png");
		//Image_Skill_AgilitOn2 = CP_Image_Load("./Assets/skilltree/Skill_agilityOn2.png");
		//Image_Skill_AgilitOn3 = CP_Image_Load("./Assets/skilltree/Skill_agilityOn3.png");
		//Image_Skill_AgilitOn4 = CP_Image_Load("./Assets/skilltree/Skill_agilityOn4.png");
		//Image_Skill_AgilitOn5 = CP_Image_Load("./Assets/skilltree/Skill_agilityOn5.png");

		//Image_Skill_AtkspeedOn = CP_Image_Load("./Assets/skilltree/Skill_attackspeedOn.png");


		//Image_Skill_HeartsOff = CP_Image_Load("./Assets/Skill_heartsOff.png");
		//Image_Skill_AgilitOff = CP_Image_Load("./Assets/Skill_agilityOff.png");
		//Image_Skill_AtkspeedOff = CP_Image_Load("./Assets/Skill_attackspeedOff.png");

		//Image_Shop_HealOn = CP_Image_Load("./Assets/Shop_2xhealOn.png");
		//Image_Shop_DropsOn = CP_Image_Load("./Assets/Shop_2xdropsOn.png");
		//Image_Shop_RezOn = CP_Image_Load("./Assets/Shop_rezOn.png");
		//Image_Shop_ShrapnelOn = CP_Image_Load("./Assets/Shop_shrapnelOn.png");
		//Image_Shop_Shockwave = CP_Image_Load("./Assets/Shop_ShockWave.png");


		//Image_Shop_HealOff = CP_Image_Load("./Assets/Shop_2xhealOff.png");
		//Image_Shop_DropsOff = CP_Image_Load("./Assets/Shop_2xdropsOff.png");
		//Image_Shop_RezOff = CP_Image_Load("./Assets/Shop_rezOff.png");
		//Image_Shop_ShrapnelOff = CP_Image_Load("./Assets/Shop_shrapnelOff.png");


		//Image_Pause_Mistake = CP_Image_Load("./Assets/pause_mistake1.png");

		//Image_Win_Background = CP_Image_Load("./Assets/winscreen.png");

		//Image_Gameover_Background = CP_Image_Load("./Assets/GameOver.png");


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



void Player_FullHeal(void)
{
	int playerhp = p1.get(&p1);
	int Eplayerhp = player_maxhp - playerhp;
	while (Eplayerhp > 0)
	{
		PlayerHealed(1);
		printf("playerfull healed \n");
		Eplayerhp -= 1;
	}
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





void Screen_Currency_Print(void)
{
	CP_Image_Draw(Image_GoldSprite, Currency_Sprite.posX, Currency_Sprite.posY, isaac_width, isaac_height, 255);
	CP_Image_Draw(Image_ExpSprite, Currency_Sprite.posX, Currency_Sprite.posY, isaac_width, isaac_height, 255);
	CP_Image_Draw(Image_ReztokenSprite, Currency_Sprite.posX, Currency_Sprite.posY, isaac_width, isaac_height, 255);

}

void Screen_GAMEOVER_Print(void)											//new functuon
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_Gameover_Background, GameOver_Background.posX, GameOver_Background.posY, isaac_width, isaac_height, 255);
}


void ScorePrinter(int score, float x, float y)
{
	CP_Font_Set(SkullFont);
	switch (score)
	{
	case 0:
		CP_Font_DrawText(Zero, x, y);

		break;
	case 1:
		CP_Font_DrawText(One, x, y);
		break;
	case 2:
		CP_Font_DrawText(Two, x, y);
		break;
	case 3:
		CP_Font_DrawText(Three, x, y);
		break;
	case 4:
		CP_Font_DrawText(Four, x, y);
		break;
	case 5:
		CP_Font_DrawText(Five, x, y);
		break;
	case 6:
		CP_Font_DrawText(Six, x, y);
		break;
	case 7:
		CP_Font_DrawText(Seven, x, y);
		break;
	case 8:
		CP_Font_DrawText(Eight, x, y);
		break;
	case 9:
		CP_Font_DrawText(Nine, x, y);
		break;
	case 10:
		CP_Font_DrawText(Ten, x, y);
		break;
	case 11:
		CP_Font_DrawText(Eleven, x, y);
		break;
	case 12:
		CP_Font_DrawText(Twelve, x, y);
		break;
	case 13:
		CP_Font_DrawText(Thirteen, x, y);
		break;
	case 14:
		CP_Font_DrawText(Fourteen, x, y);
		break;
	case 15:
		CP_Font_DrawText(Fifhteen, x, y);
		break;
	case 16:
		CP_Font_DrawText(Sixteen, x, y);
		break;
	case 17:
		CP_Font_DrawText(Seventeen, x, y);
		break;
	case 18:
		CP_Font_DrawText(Eighteen, x, y);
		break;
	case 19:
		CP_Font_DrawText(Nineteen, x, y);
		break;
	case 20:
		CP_Font_DrawText(Twenty, x, y);
		break;

	}
}

void Screen_YOUDIED_Print(void)											//new functuon
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_YouDied_Background, Revive_Background.posX, Revive_Background.posY, isaac_width, isaac_height, 255);

	
}



void Screen_REVIVE_Print(void)											//new functuon
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_Revive_Background, Revive_Background.posX, Revive_Background.posY, isaac_width, isaac_height, 255);
	
	CP_Settings_Fill(darkviolet);
	ScorePrinter(revivetoken, 432, 347);
}


void Screen_WIN_Print(void)											//new functuon
{


	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}

	CP_Image_Draw(Image_Win_Background, Win_Background.posX, Win_Background.posY, isaac_width, isaac_height, 255);
}

void Screen_PAUSE_Print(void)											//new functuon
{

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}

	CP_Image_Draw(Image_Pause_Mistake, Pause_Background.posX, Pause_Background.posY, isaac_width, isaac_height, 255);
}

void Screen_PREPROOM_Print(void)											//new functuon
{
/*
	PrepRoom_QuitButton.posX = menu.height * (3.0f / 7.0f);
	PrepRoom_QuitButton.posY = menu.height * (3.0f / 7.0f);

	PrepRoom_UpgrradesButton.posX = menu.height * (3.0f / 7.0f);
	PrepRoom_UpgrradesButton.posY = menu.height * (3.0f / 7.0f);
*/	
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}

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
	/*
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	*/
	CP_Graphics_ClearBackground(COLOR_BLACK);

	CP_Image_Draw(Image_Shop_Empty, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255);


	if (Shop_HealButton.enabled == TRUE)
	{
		CP_Image_Draw(Image_Shop_HealOn, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255);
	}
	else
	{
		CP_Image_Draw(Image_Shop_HealOn, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 100) ;
	}
		

	if (Shop_DropsButton.enabled == TRUE)
	{
		(CP_Image_Draw(Image_Shop_DropsOn, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255));
	}
	else
	{
		//printf("False");
		CP_Image_Draw(Image_Shop_DropsOff, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 100);
	}

	if (Shop_RezButton.enabled == TRUE)
	{
		CP_Image_Draw(Image_Shop_RezOn, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255);
	}
	else
	{
		CP_Image_Draw(Image_Shop_RezOff, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 100);
	}

	
	if (shrapnelstate == FALSE)
	{
		CP_Image_Draw(Image_Shop_ShrapnelOff, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255);
	}
	else
	{
		CP_Image_Draw(Image_Shop_ShrapnelOff, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 100);
	}


	if (shockwavestate == FALSE)
	{
		CP_Image_Draw(Image_Shop_Shockwave, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 255);
	}
	else
	{
		CP_Image_Draw(Image_Shop_Shockwave, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 100);
	}



	CP_Settings_TextSize(100);
	CP_Settings_Fill(COLOR_WHITE);
	ScorePrinter(Gold,335, 429);
}

void Screen_SKILL_Print(void)											//new functuon
{

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_Skill_Empty, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);

	CP_Graphics_ClearBackground(COLOR_BLACK);

	switch (additionalhp) {
		case 0:
			CP_Image_Draw(Image_Skill_HeartsOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
			break;
		case 1:
			CP_Image_Draw(Image_Skill_HeartsOn1, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
			break;
		case 2:
			CP_Image_Draw(Image_Skill_HeartsOn2, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);

			break;
		case 3:
			CP_Image_Draw(Image_Skill_HeartsOn3, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);

			break;
		case 4:
			CP_Image_Draw(Image_Skill_HeartsOn4, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
			break;
		default:
			CP_Image_Draw(Image_Skill_HeartsOn5, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 100);
			break;
	}

	switch (additionalspeed) {
	case 0:
		CP_Image_Draw(Image_Skill_AgilitOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		break;

	case 20:
		CP_Image_Draw(Image_Skill_AgilitOn1, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		break;

	case 40:
		CP_Image_Draw(Image_Skill_AgilitOn2, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		break;

	case 60:
		CP_Image_Draw(Image_Skill_AgilitOn3, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		break;

	//case 80:
		//CP_Image_Draw(Image_Skill_AgilitOn4, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		//break; 

	default:
		CP_Image_Draw(Image_Skill_AgilitOn4, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 100);

		//CP_Image_Draw(Image_Skill_AgilitOn5, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 100);
			break;
	}

	switch (additionalcrit) {
	case 0:
		CP_Image_Draw(Image_Skill_CritOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		break;
	case 10:
		CP_Image_Draw(Image_Skill_CritOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);

		CP_Image_Draw(Image_Skill_Crit1, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		break;
	case 20:
		CP_Image_Draw(Image_Skill_CritOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);

		CP_Image_Draw(Image_Skill_Crit2, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);

		break;
	case 30:
		CP_Image_Draw(Image_Skill_CritOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);

		CP_Image_Draw(Image_Skill_Crit3, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);

		break;
	case 40:
		CP_Image_Draw(Image_Skill_CritOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);

		CP_Image_Draw(Image_Skill_Crit4, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		break;

	case 50:
		CP_Image_Draw(Image_Skill_CritOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);

		CP_Image_Draw(Image_Skill_Crit5, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		break;

	case 60:
		CP_Image_Draw(Image_Skill_CritOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		CP_Image_Draw(Image_Skill_Crit6, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		break;
	case 70:
		CP_Image_Draw(Image_Skill_CritOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		CP_Image_Draw(Image_Skill_Crit7, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		break;
	case 80:
		CP_Image_Draw(Image_Skill_CritOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		CP_Image_Draw(Image_Skill_Crit8, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255);
		break;

	default:
		CP_Image_Draw(Image_Skill_CritOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 100);
		CP_Image_Draw(Image_Skill_Crit9, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 100);
		break;

	//default:
		//CP_Image_Draw(Image_Skill_CritOn, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 100);

		//CP_Image_Draw(Image_Skill_Crit10, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 100);
		//break;
	}

	CP_Settings_TextSize(100);
	CP_Settings_Fill(COLOR_WHITE);
	ScorePrinter(Exp, 325, 429);
}


BOOL IsaacCheckCollisionWithButtonImage(float posX, float posY, float startX, float starty, float endx, float endy)											//new functuon
{

	if ((posX < endx && posX > startX)
		&& (posY < endy && posY > starty))
	{
		play_click();
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}



void Screen_GAMEOVER_ButtonClicked(void)											//new functuon
{
	/*
		if (CP_Input_KeyTriggered(KEY_ESCAPE))
		{
			printf("button pressed back esc \n");
			gameState = UPGRADES;
		}
	*/

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("button pressed  \n");

		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		//printf("%f", mousePosX);
		//if (CheckCollisionWithBox(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		//{
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 44.0, 820.0, 403.0, 939.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			// pressany button to coninure 

			printf("button pressed mm \n");
			gameState = MAIN_MENU;
			currentLevel = MAIN_MENU;
		}

		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 557.0, 822.0, 906.0, 936.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			// pressany button to coninure 

			printf("button pressed retry \n");
			gamePause = 1;
			//gameState = RETRY;
			*tick = 0;
			reset_enemy_and_weapon();
			
			preload_spawn_map(currentLevel);
			ResetState();
			gameState = currentLevel;
			
			

			//gameState = MAIN_MENU;
		}

	}
}

void DeathCondition(void)
{
	if (PlayerGethealth() == 0)
	{
		gamePause = !gamePause;
		//Player_FullHeal();
		reset_enemy_and_weapon();
		ResetState();
		gameState = LOSE;
	}
}

void Screen_WIN_ButtonClicked(void)											//new functuon
{
/*
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		printf("button pressed back esc \n");
		gameState = UPGRADES;
	} 
*/

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("button pressed  \n");

		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		//printf("%f", mousePosX);
		//if (CheckCollisionWithBox(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		//{
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 206.0, 628.0, 727.0, 829.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;

			printf("button pressed continue \n");
			gameState = PREPROOM;
		}
	}
}

void Screen_PAUSE_ButtonClicked(void)											//new functuon
{
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		printf("button pressed back esc \n");
		printf("button pressed continue \n");
		gamePause = !gamePause;
		gameState = currentLevel;
	}

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		//printf("%f", mousePosX);
		//if (CheckCollisionWithBox(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		//{
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 199.0, 350.0, 699.0, 507.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed continue \n");
			gamePause = !gamePause;
			gameState = currentLevel;
		}

		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 297.0, 510.0, 580.0, 622.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			
			printf("button pressed retry\n");
			reset_enemy_and_weapon();

			preload_spawn_map(currentLevel);
			ResetState();
			gameState = currentLevel;
			
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 299.0, 661.0, 595.0, 781.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed menu\n");

			//gamePause = !gamePause;
			gameState = MAIN_MENU;
			currentLevel = MAIN_MENU;
			//gameState = UPGRADES;
		}

	}
}

void Screen_PREPROOM_ButtonClicked(void)											//new functuon
{
/*

	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		printf("button pressed back esc \n");
		gameState = UPGRADES;
	}
*/
	// temporary access to shop 
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		printf("button pressed back esc \n");
		printf("button pressed continue \n");
		gamePause = !gamePause;
		gameState = PAUSED;
	}

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
			gamePause = !gamePause;
			
			reset_enemy_and_weapon();
			preload_spawn_map(currentLevel);
			ResetState();
			gameState = currentLevel;

		}
	
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 309.0, 827.0, 511.0, 916.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed quit\n");

			gameState = MAIN_MENU;
			currentLevel = MAIN_MENU;
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 597.0, 827.0, 913.0, 915.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed upgrade\n");
			gameState = UPGRADES;
		}

	}
}

void Screen_UPGRADE_ButtonClicked(void)											//new functuon
{

	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		printf("button pressed back esc \n");
		if (MainMenuState == TRUE)
		{
			gameState = MAIN_MENU;

		}
		else if (MainMenuState == FALSE)
		{
			gameState = PREPROOM;
		}
		
	}

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
			if (currentLevel == MAIN_MENU)
			{
				gameState = MAIN_MENU;
			}
			else
			{
				gameState = PREPROOM;
			}
		}

		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 31.0, 349.0, 414.0, 730.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed skill\n");
			gameState = SKILL;
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 552.0, 353.0, 936.0, 730.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			
			printf("button pressed shop\n");
			gameState = SHOP;
		}

	}
}

void Screen_SHOP_ButtonClicked(void)											//new functuon
{

	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		printf("button pressed back esc \n");
		gameState = UPGRADES;
	}

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		printf("\n x is %f, Y is %f ", mousePosX,mousePosY);
		//if (CheckCollisionWithBox(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		//{
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 787.0, 27.0, 936.0, 154.0))
		{
			//menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_BLACK);
			//gameState = PLAYING;
			printf("button pressed back \n");
			gameState = UPGRADES;
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 26.0, 546.0, 459.0, 671.0))
		{
			//menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_BLACK);
			//gameState = PLAYING;
			printf("button pressed heal\n");
			//minus gold 
			if ((Gold > 2) && (DoubleHeal == FALSE))
			{
				Gold -= 2;
				DoubleHeal = TRUE;
				Shop_HealButton.enabled = FALSE;
			}
			else
			{
				printf("not enough gold ");
			}
			
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 25.0, 690.0, 460.0, 843.0))
		{
			//menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_BLACK);
			//gameState = PLAYING;
			printf("button pressed drop\n");
			// minus gold 
			if ((Gold > 2) && (DoubleDrop == FALSE))
			{
				Gold -= 2;
				DoubleDrop = TRUE;
				Shop_DropsButton.enabled = FALSE;
			}
			else
			{
				printf("not enough gold ");
			}
			
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 25.0, 833.0, 460.0, 955.0))
		{
			//menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_BLACK);
			//gameState = PLAYING;
			
			printf("button pressed rez\n");
			if (Gold > 2)
			{
				revivetoken++;
				Gold -= 2;
				//Shop_RezButton.enabled = FALSE;
			}
			else
			{
				printf("not enough gold ");
			}
			
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 511.0, 543.0, 943.0, 661.0))
		{
			//menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_BLACK);
			//gameState = PLAYING;
			printf("button pressed shrapnel\n");
			if ((Gold > 2) && (shrapnelstate == FALSE))
			{
				Gold -= 2;
				shrapnelstate = TRUE;
				//Shop_ShrapnelButton.enabled = FALSE;
			}
			else
			{
				printf("not enough gold ");
			}
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 511.0, 686.0, 943.0, 811.0))
		{
			//menu.enabled = FALSE;
			CP_Graphics_ClearBackground(COLOR_BLACK);
			//gameState = PLAYING;
			printf("button pressed shockwave\n");

			if ((Gold > 2) && (shockwavestate == FALSE))
			{
				Gold -= 2;
				shockwavestate = TRUE;

			}
			else
			{
				printf("not enough gold ");
			}


		}

	}
}

void Screen_SKILL_ButtonClicked(void)											//new functuon
{
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		printf("button pressed back esc \n");
		gameState = UPGRADES;
	}

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
			gameState = UPGRADES;
		}

		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 44.0, 540.0, 483.0, 668.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed hearts\n");
			if (Exp > 0)
			{
				if (additionalhp < maxadditionalhp)
				{
					Exp -= 1;
					additionalhp++;
					//printf("hpadded %d" ,additionalhp);
					p1.set(&p1, 3 + additionalhp);
					// minus exp
				}
				else
				{
					//printf("max rhp eached ");

					Skill_HeartsButton.enabled = FALSE;
				}
			}

		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 44.0, 683.0, 480.0, 811.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed agility\n");
			if (Exp > 0)
			{
				if (additionalspeed < maxadditionalspeed)
				{
					Exp -= 1;
					additionalspeed += 20; // or 20 increment ? 
					knight.speed += additionalspeed;
					//mage.speed += additionalspeed;
					//archer.speed += additionalspeed;
				}
				else
				{
					Skill_AgilityButton.enabled = FALSE;
				}
			}
			


		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 44.0, 832.0, 480.0, 958.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed atkspeed\n");
			if (Exp > 0)
			{
				if (additionalcrit < maxadditionalcrit)
				{
					Exp -= 1;
					additionalcrit += 10; // or 20 increment ? 
					//knight.speed += additionalspeed;
					//mage.speed += additionalspeed;
					//archer.speed += additionalspeed;
				}
				else
				{
					Skill_CritButton.enabled = FALSE;
				}
			}
		}

	}

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_2))
	{
		// sell skills and refund exp to player 
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 44.0, 540.0, 483.0, 668.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed sell hearts\n");
			//if (Exp > 0)
			//{
			if (additionalhp != 0)
			{
				Skill_HeartsButton.enabled = TRUE;
				Exp += 1;
				additionalhp--;
				//printf("hpadded %d" ,additionalhp);
				p1.set(&p1, 3 + additionalhp);
				// minus exp
			}
			//else
			//{
				//printf("max rhp eached ");
			//
				//Skill_HeartsButton.enabled = FALSE;
		//	}
		//}

		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 44.0, 683.0, 480.0, 811.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed sell agility\n");
			//if (Exp > 0)
			//{


			if (additionalspeed != 0)
			{
				Skill_AgilityButton.enabled = TRUE;
				Exp += 1;
				additionalspeed -= 20; // or 20 increment ? 
				knight.speed -= additionalspeed;
				//mage.speed += additionalspeed;
				//archer.speed += additionalspeed;
			}
			//else
			//{
				//Skill_AgilityButton.enabled = FALSE;
			//}
		//}
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 44.0, 832.0, 480.0, 958.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed crit\n");
			//if (Exp > 0)
			//{
				if (additionalcrit != 0)
				{
					Skill_CritButton.enabled = TRUE;

					Exp += 1;
					additionalcrit -= 10; 
					
				}
				else
				{
					Skill_CritButton.enabled = FALSE;
				}
			//}
		}
	}
}

void Screen_YOUDIED_ButtonClicked(void)											//new functuon
{
	/*
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		printf("button pressed back esc \n");
		gameState = UPGRADES;
	}
	*/

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		//printf("%f", mousePosX);
		//if (CheckCollisionWithBox(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		//{
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 4.0, 5.0, 952.0, 1009.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed back \n");
			gameState = REVIVE;
		}
	}
}

void Screen_REVIVE_ButtonClicked(void)											//new functuon
{
	/*
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		printf("button pressed back esc \n");
		gameState = UPGRADES;
	}
	*/

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		//printf("%f", mousePosX);
		//if (CheckCollisionWithBox(mousePosX, mousePosY, playButton.width, playButton.height, playButton.posX, playButton.posY))
		//{
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 99.0, 524.0, 394.0, 711.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed yes \n");

			revivetoken -= 1;
			*tick = 0;
			ResetState();
			gameState = currentLevel;


			//gameState = REVIVE;
		}

		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 511.0, 539.0, 728.0, 736.0))
		{
			//menu.enabled = FALSE;
			//CP_Graphics_ClearBackground(COLOR_GRAY);
			//gameState = PLAYING;
			printf("button pressed no \n");
			gameState = LOSE;


		}
	}
}

void exit_skilltreepictures(void) 
{


	
	CP_Image_Free(&Image_GoldSprite);
	CP_Image_Free(&Image_ExpSprite);
	CP_Image_Free(&Image_ReztokenSprite);




	CP_Image_Free(&Image_PrepRoom_Empty);
	CP_Image_Free(&Image_Upgrade_Empty);
	CP_Image_Free(&Image_Skill_Empty);
	CP_Image_Free(&Image_Shop_Empty);

	CP_Image_Free(&Image_Skill_HeartsOn);
	CP_Image_Free(&Image_Skill_HeartsOn1);
	CP_Image_Free(&Image_Skill_HeartsOn2);
	CP_Image_Free(&Image_Skill_HeartsOn3);
	CP_Image_Free(&Image_Skill_HeartsOn4);
	CP_Image_Free(&Image_Skill_HeartsOn5);

	CP_Image_Free(&Image_Skill_AgilitOn);
	CP_Image_Free(&Image_Skill_AgilitOn1);
	CP_Image_Free(&Image_Skill_AgilitOn2);
	CP_Image_Free(&Image_Skill_AgilitOn3);
	CP_Image_Free(&Image_Skill_AgilitOn4);
	CP_Image_Free(&Image_Skill_AgilitOn5);

	CP_Image_Free(&Image_Skill_CritOn);
	CP_Image_Free(&Image_Skill_Crit1);
	CP_Image_Free(&Image_Skill_Crit2);
	CP_Image_Free(&Image_Skill_Crit3);
	CP_Image_Free(&Image_Skill_Crit4);
	CP_Image_Free(&Image_Skill_Crit5);
	CP_Image_Free(&Image_Skill_Crit6);
	CP_Image_Free(&Image_Skill_Crit7);
	CP_Image_Free(&Image_Skill_Crit8);
	CP_Image_Free(&Image_Skill_Crit9);
	CP_Image_Free(&Image_Skill_Crit10);

	//CP_Image_Free(&Image_Skill_HeartsOff);
	//CP_Image_Free(&Image_Skill_AgilitOff);
	//CP_Image_Free(&Image_Skill_AtkspeedOff);

	CP_Image_Free(&Image_Shop_HealOn);
	CP_Image_Free(&Image_Shop_DropsOn);
	CP_Image_Free(&Image_Shop_RezOn);
	CP_Image_Free(&Image_Shop_ShrapnelOn);
	CP_Image_Free(&Image_Shop_Shockwave);

	CP_Image_Free(&Image_Shop_HealOff);
	CP_Image_Free(&Image_Shop_DropsOff);
	CP_Image_Free(&Image_Shop_RezOff);
	CP_Image_Free(&Image_Shop_ShrapnelOff);


	CP_Image_Free(&Image_Pause_Mistake);
	CP_Image_Free(&Image_Win_Background);
	CP_Image_Free(&Image_Gameover_Background);

	CP_Image_Free(&Image_YouDied_Background);
	CP_Image_Free(&Image_Revive_Background);



}