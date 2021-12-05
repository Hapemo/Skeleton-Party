/*---------------------------------------------------------
 * file:	issac.c
 * author:	issac
 * email:	i.yeo@digipen.edu
*
 * brief:	
*
 * documentation link:
 * https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
*
 * Copyright © 2020 DigiPen, All rights reserved.
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

/***********************************************************************************************Number defines Start  ************************************************************************************************/
/*the numbers printed in the number system are defined here.*/

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
#define Twenty1 "21"
#define Twenty2 "22"
#define Twenty3 "23"
#define Twenty4 "24"
#define Twenty5 "25"
#define Twenty6 "26"
#define Twenty7 "27"
#define Twenty8 "28"
#define Twenty9 "29"

#define Thirty "30"
#define Thirty1 "31"
#define Thirty2 "32"
#define Thirty3 "33"
#define Thirty4 "34"
#define Thirty5 "35"
#define Thirty6 "36"
#define Thirty7 "37"
#define Thirty8 "38"
#define Thirty9 "39"

#define Fourty "40"
#define Fourty1 "41"
#define Fourty2 "42"
#define Fourty3 "43"
#define Fourty4 "44"
#define Fourty5 "45"
#define Fourty6 "46"
#define Fourty7 "47"
#define Fourty8 "48"
#define Fourty9 "49"

#define Fifty "50"
#define Fifty1 "51"
#define Fifty2 "52"
#define Fifty3 "53"
#define Fifty4 "54"
#define Fifty5 "55"
#define Fifty6 "56"
#define Fifty7 "57"
#define Fifty8 "58"
#define Fifty9 "59"

#define Sixty "60"
#define Sixty1 "61"
#define Sixty2 "62"
#define Sixty3 "63"
#define Sixty4 "64"
#define Sixty5 "65"
#define Sixty6 "66"
#define Sixty7 "67"
#define Sixty8 "68"
#define Sixty9 "69"

#define Seventy "70"
#define Seventy1 "71"
#define Seventy2 "72"
#define Seventy3 "73"
#define Seventy4 "74"
#define Seventy5 "75"
#define Seventy6 "76"
#define Seventy7 "77"
#define Seventy8 "78"
#define Seventy9 "79"

#define Eighty "80"
#define Eighty1 "81"
#define Eighty2 "82"
#define Eighty3 "83"
#define Eighty4 "84"
#define Eighty5 "85"
#define Eighty6 "86"
#define Eighty7 "87"
#define Eighty8 "88"
#define Eighty9 "89"

#define Ninety "90"
#define Ninety1 "91"
#define Ninety2 "92"
#define Ninety3 "93"
#define Ninety4 "94"
#define Ninety5 "95"
#define Ninety6 "96"
#define Ninety7 "97"
#define Ninety8 "98"
#define Ninety9 "99"

/***********************************************************************************************Number defines End ************************************************************************************************/

CP_Font SkullFont;
CP_Font BonesFont;

/***********************************************************************************************Image Declerations  Start ************************************************************************************************/

CP_Image Image_GoldSprite = NULL;
CP_Image Image_ExpSprite = NULL;
CP_Image Image_ReztokenSprite = NULL;

CP_Image Image_PrepRoom_Empty = NULL;
CP_Image Image_Upgrade_Empty = NULL;
CP_Image Image_Skill_Tree = NULL;
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

CP_Image Image_num_1;
CP_Image Image_num_2;
CP_Image Image_num_3;
CP_Image Image_num_4;
CP_Image Image_num_5;
CP_Image Image_num_6;
CP_Image Image_num_7;
CP_Image Image_num_8;
CP_Image Image_num_9;
CP_Image Image_num_10;

button skill_arrow_charge = {0};
button skill_arrow_size = { 0 };
button skill_attack_speed = { 0 };
button skill_blast_range = { 0 };
button skill_health = { 0 };
button skill_movement = { 0 };
button skill_shrapnels = { 0 };
button skill_sword_range = { 0 };
button skill_sword_swing = { 0 };
button skill_sword_crit = { 0 };

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

CP_Image Image_Thanks_Background = NULL;

/***********************************************************************************************Image Declerations END ************************************************************************************************/


/***********************************************************************************************Local Variable Declerations Start ************************************************************************************************/

float button_spacing = 30.0f + SKILLS_BUTTON_HEIGHT;


//Heart sprite settings below
static CP_Image spriteSheetImage;
static int imageIndex; // decides what image it uses 
static const float Heart_FRAME_DIMENSIONx = 58.0f;
static const float Heart_FRAME_DIMENSIONy = 45.0f;
int player_maxhp;
int additionalhp, maxadditionalhp;
int additionalspeed, maxadditionalspeed;
int max_skill_upgrade;
static  float Heart_size_windowsx;
static  float Heart_size_windowsy;

static float hplocationX = 100.0f;
static float hplocationY = 100.0f;
//Heart sprite settings above

float isaac_width;
float isaac_height;
float isaac_textboxwidth;
float isaac_addmousepos;

const char Skill_Hearts_Desc[] = { "Cost : 1 EXP per level\n Max 5 levels\n + 1 Heart per level" };
const char Skill_Agility_Desc[] = { "Cost : 1 EXP per level\n Max 4 levels\n + 20 agility / level" };
const char Skill_Crit_Desc[] = { "Cost : 1 EXP per level\n Max 9 Levels\n + 10% crit / level" };

const char Shop_Heal_Desc[] = { "Cost : 10 Gold Coins \n Doubles  the amount of healing from potions \n 1 heart -> 2 heart" };
const char Shop_Drop_Desc[] = { "Cost : 10 Gold Coins \n Increases amount of EXP gained from winning \n 3 EXP-> 6 EXP" };
const char Shop_Rez_Desc[] = { "Cost : 5 Gold Coins \n Allows you to coninue from where you died " };
const char Shop_Shrapnel_Desc[] = { "Cost : 20 Gold Coins \n Enables Mage AOE to Fire additional bullets upon impact" };
const char Shop_Shockwave_Desc[] = { "Cost : 20 Gold Coins \n Adds An AOE to the knights Melee attack" };

const char Pause_mainmenu_Desc[] = { "Click To Return To Main Menu" };
//const char Pause_mainmenu_Desc[] = { "Click To Return To Main Menu" };




/***********************************************************************************************Local Variable Declerations END ************************************************************************************************/



/***********************************************************************************************Player Health "object" Declerations and Definitions Start ************************************************************************************************/



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
}
// HealthSystem Object decleration above 

/***********************************************************************************************Player Health "object" Declerations and Definitions END ************************************************************************************************/


/***********************************************************************************************Structs for Shop And Skills System UI Start ************************************************************************************************/

struct Thanks_Background {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
}Thanks_Background;

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
	BOOL hover;

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
	BOOL hover;

}Skill_HeartsButton;

struct Skill_AgilityButton {
	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
	BOOL hover;

}Skill_AgilityButton;

struct Skill_CritButton {
	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
	BOOL hover;

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
	BOOL hover;

}Shop_HealButton;

struct Shop_DropsButton {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
	BOOL hover;

}Shop_DropsButton;

struct Shop_RezButton {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
	BOOL hover;

}Shop_RezButton;

struct Shop_ShrapnelButton {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
	BOOL hover;

}Shop_ShrapnelButton;

struct Shop_Shockwave {

	BOOL enabled;
	float posX;
	float posY;
	float width;
	float height;
	BOOL hover;

}Shop_Shockwave;


/*********************************************************************************************** Structs for Shop And Skills System UI END ************************************************************************************************/

/*!
@brief  -this function contains variables to be be set in game_init relating to player's Health Syetem
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void init_PlayerHP(void)
{
	spriteSheetImage = CP_Image_Load("./Assets/HeartSprite.png");
	NewHealthSystem(p1)
	p1.set(&p1, 3);

	maxadditionalhp = 5;
	additionalhp = 0;

	maxadditionalspeed = 320;
	additionalspeed = 0;

	hplocationX = (CP_System_GetWindowWidth()) / 10.0f;
	hplocationY = (CP_System_GetWindowHeight()) / 8.0f;
	// size of the heart 
	Heart_size_windowsx = (CP_System_GetWindowWidth()) / 5.0f;
	Heart_size_windowsy = (CP_System_GetWindowHeight()) / 5.0f;
}

/*!
@brief  -this function contains variables to be be freed in game_exit relating to player's Health Syetem
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void exit_PlayerHP(void)
{
	CP_Image_Free(&spriteSheetImage);
}

/*!
@brief  -this function contains variables to be be set in game_init relating to the Shop/Skill UI and with Pause, Win Revive, Youlose Screens
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void InitializeSkillShopUI(void)         
{
	SkullFont = CP_Font_Load("./Assets/Font/Skull-Story.ttf");
	BonesFont = CP_Font_Load("./Assets/Font/BikerBones.ttf");
	//SWORD_CRIT_CHANCE = 10;
	revivetoken = 0;
	Exp = 3;
	Gold = 2;
	additionalExp = 3;
	additionalGold = 1;

	additionalcrit = 0;
	max_skill_upgrade = 9;
	ptr_additionalcrit = &additionalcrit;
	ptr_Gold = &Gold;

	firstclear = FALSE;
	DoubleExp = FALSE;
	DoubleGold = FALSE;
	DoubleDrop = FALSE;
	DoubleHeal = FALSE;
	MainMenuState = TRUE;
	
	isaac_width = WIDTH;
	isaac_height = HEIGHT;
	isaac_textboxwidth = 190.0f;
	isaac_addmousepos = 30.0f;

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

	//Initialisation of skills buttons
	skill_health.position = CP_Vector_Set(250, HEIGHT / 2 + 10.0f);
	skill_health.num_position = CP_Vector_Set(250.0f + NUM_POSITION_RATIO * SKILLS_BUTTON_WIDTH, HEIGHT / 2 + 10.0f);
	skill_health.image = CP_Image_Load("./Assets/skilltree/health.png");
	skill_health.description = "Additional heart container";

	skill_sword_range.position = CP_Vector_Set(250, HEIGHT / 2 + 10.0f + button_spacing);
	skill_sword_range.num_position = CP_Vector_Set(250.0f + NUM_POSITION_RATIO * SKILLS_BUTTON_WIDTH, HEIGHT / 2 + 10.0f);
	skill_sword_range.image = CP_Image_Load("./Assets/skilltree/sword_range.png");
	skill_sword_range.description = "Increase sword reach";

	skill_shrapnels.position = CP_Vector_Set(250, HEIGHT / 2 + 10.0f + button_spacing*2);
	skill_shrapnels.num_position = CP_Vector_Set(250.0f + NUM_POSITION_RATIO * SKILLS_BUTTON_WIDTH, HEIGHT / 2 + 10.0f);
	skill_shrapnels.image = CP_Image_Load("./Assets/skilltree/shrapnels.png");
	skill_shrapnels.description = "Increase sharpnels (MUST own sharpnel from shop)";

	skill_arrow_size.position = CP_Vector_Set(250, HEIGHT / 2 + 10.0f + button_spacing * 3);
	skill_arrow_size.num_position = CP_Vector_Set(250.0f + NUM_POSITION_RATIO * SKILLS_BUTTON_WIDTH, HEIGHT / 2 + 10.0f);
	skill_arrow_size.image = CP_Image_Load("./Assets/skilltree/arrow_size.png");
	skill_arrow_size.description = "Increase arrow size";

	skill_attack_speed.position = CP_Vector_Set(250, HEIGHT / 2 + 10.0f + button_spacing* 4);
	skill_attack_speed.num_position = CP_Vector_Set(250.0f + NUM_POSITION_RATIO * SKILLS_BUTTON_WIDTH, HEIGHT / 2 + 10.0f);
	skill_attack_speed.image = CP_Image_Load("./Assets/skilltree/attack_speed.png");
	skill_attack_speed.description = "Increase fireball and sword attack speed";


	skill_movement.position = CP_Vector_Set(WIDTH - 250, HEIGHT / 2 + 10.0f);
	skill_movement.num_position = CP_Vector_Set(250.0f + NUM_POSITION_RATIO * SKILLS_BUTTON_WIDTH, HEIGHT / 2 + 10.0f);
	skill_movement.image = CP_Image_Load("./Assets/skilltree/movement.png");
	skill_movement.description = "Increase movement speed";

	skill_sword_swing.position = CP_Vector_Set(WIDTH - 250, HEIGHT / 2 + 10.0f + button_spacing);
	skill_sword_swing.num_position = CP_Vector_Set(250.0f + NUM_POSITION_RATIO * SKILLS_BUTTON_WIDTH, HEIGHT / 2 + 10.0f);
	skill_sword_swing.image = CP_Image_Load("./Assets/skilltree/sword_swing.png");
	skill_sword_swing.description = "Increase sword swinging angle";

	skill_blast_range.position = CP_Vector_Set(WIDTH - 250, HEIGHT / 2 + 10.0f + button_spacing * 2);
	skill_blast_range.num_position = CP_Vector_Set(250.0f + NUM_POSITION_RATIO * SKILLS_BUTTON_WIDTH, HEIGHT / 2 + 10.0f);
	skill_blast_range.image = CP_Image_Load("./Assets/skilltree/blast_range.png");
	skill_blast_range.description = "Increase fireball explosion";

	skill_arrow_charge.position = CP_Vector_Set(WIDTH - 250, HEIGHT / 2 + 10.0f + button_spacing * 3);
	skill_arrow_charge.num_position = CP_Vector_Set(250.0f + NUM_POSITION_RATIO * SKILLS_BUTTON_WIDTH, HEIGHT / 2 + 10.0f);
	skill_arrow_charge.image = CP_Image_Load("./Assets/skilltree/arrow_charge.png");
	skill_arrow_charge.description = "Increase arrow charge speed";

	skill_sword_crit.position = CP_Vector_Set(WIDTH - 250, HEIGHT / 2 + 10.0f + button_spacing * 4);
	skill_sword_crit.num_position = CP_Vector_Set(250.0f + NUM_POSITION_RATIO * SKILLS_BUTTON_WIDTH, HEIGHT / 2 + 10.0f);
	skill_sword_crit.image = CP_Image_Load("./Assets/skilltree/sword_crit.png");
	skill_sword_crit.description = "Increase sword critical strike chance (MUST own shockwave from shop)";






	Thanks_Background.enabled = TRUE;
	Thanks_Background.width = isaac_width;
	Thanks_Background.height = isaac_height;
	Thanks_Background.posX = (float)(isaac_width / 2.0);
	Thanks_Background.posY = (float)(isaac_height / 2.0);
	
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
	Shop_Shockwave.enabled = TRUE;

	Skill_HeartsButton.hover = TRUE;
	Skill_AgilityButton.hover = TRUE;
	Skill_CritButton.hover = TRUE;

	Shop_HealButton.hover = TRUE;
	Shop_DropsButton.hover = TRUE;
	Shop_RezButton.hover = TRUE;
	Shop_ShrapnelButton.hover = TRUE;
	Shop_Shockwave.hover = TRUE;

	Pause_Background.hover = TRUE;

	Image_GoldSprite = CP_Image_Load("./Assets/goldsprite.png");
	Image_ExpSprite = CP_Image_Load("./Assets/Exporb.png");
	Image_ReztokenSprite = CP_Image_Load("./Assets/ReviveToken.png");

	Image_PrepRoom_Empty = CP_Image_Load("./Assets/preproom.png");
	Image_Upgrade_Empty = CP_Image_Load("./Assets/upgrades.png");
	Image_Skill_Tree = CP_Image_Load("./Assets/New_skills_background.png");
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

	Image_Skill_CritOn = CP_Image_Load("./Assets/skilltree/Crit/Skill_critOn.png");
	Image_num_1 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit1.png");
	Image_num_2 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit2.png");
	Image_num_3 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit3.png");
	Image_num_4 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit4.png");
	Image_num_5 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit5.png");
	Image_num_6 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit6.png");
	Image_num_7 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit7.png");
	Image_num_8 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit8.png");
	Image_num_9 = CP_Image_Load("./Assets/skilltree/Crit/Skill_crit9.png");
	Image_num_10 = CP_Image_Load("./Assets/skilltree/Crit/Skil_crit10.png");

	Image_Shop_HealOn = CP_Image_Load("./Assets/Shop_2xhealOn.png");
	Image_Shop_DropsOn = CP_Image_Load("./Assets/Shop_2xdropsOn.png");
	Image_Shop_RezOn = CP_Image_Load("./Assets/Shop_rezOn.png");
	Image_Shop_ShrapnelOn = CP_Image_Load("./Assets/Shop_shrapnelOn.png");
	Image_Shop_Shockwave = CP_Image_Load("./Assets/Shop_ShockWave.png");

	Image_Shop_HealOff = CP_Image_Load("./Assets/Shop_2xhealOff.png");
	Image_Shop_DropsOff = CP_Image_Load("./Assets/Shop_2xdropsOff.png");
	Image_Shop_RezOff = CP_Image_Load("./Assets/Shop_rezOff.png");
	Image_Shop_ShrapnelOff = CP_Image_Load("./Assets/Shop_shrapnelOff.png");
	
	Image_Pause_Mistake = CP_Image_Load("./Assets/pause_mistake2.png");

	Image_Win_Background = CP_Image_Load("./Assets/winscreen.png");

	Image_Gameover_Background = CP_Image_Load("./Assets/GameOver.png");

	Image_YouDied_Background = CP_Image_Load("./Assets/youdiedRevive.png");
	Image_Revive_Background = CP_Image_Load("./Assets/Revive.png");


	Image_Thanks_Background = CP_Image_Load("./Assets/tksForPlaying.png");
	maxadditionalhp = 5;
	additionalhp = 0;

	maxadditionalspeed = 320;
	additionalspeed = 0;

	hplocationX = (CP_System_GetWindowWidth()) / 10.0f;
	hplocationY = (CP_System_GetWindowHeight()) / 8.0f;
	// size of the heart 
	Heart_size_windowsx = (CP_System_GetWindowWidth()) / 5.0f;
	Heart_size_windowsy = (CP_System_GetWindowHeight()) / 5.0f;
}


/***********************************************************************************************Start of Premade Functions for interacting with Player's Health system in Game.c ************************************************************************************************/

/*!
@brief  -this function sets the Player's base health to the integer passed into the function
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void PlayerSetHealth (int Basehealth)
{
    p1.set(&p1,Basehealth);
}
/*!
@brief  -this function is called when the player  takes damage, Player's health will decrease by the integer amount passed into this function
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Playertakedamage(int damageAmt)
{
    p1.damage(&p1, damageAmt);
}


/*!
@brief  -this function is called when player is healed, Player's health will increase by the integer amount passed into this function
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void PlayerHealed(int healAmt)
{
    p1.heal(&p1, healAmt);
}


/*!
@brief  -this function is called to check players current health.
@return - this function returns players current health as integer
*//*_________________________________________________________________________________________________________________________________________________________________*/
int PlayerGethealth(void)
{
	return p1.get(&p1);
}


/*!
@brief  -this function is called when player needs to be fully healed
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Player_FullHeal(void)
{
	int playerhp = p1.get(&p1);
	int Eplayerhp = player_maxhp - playerhp;
	while (Eplayerhp > 0)
	{
		PlayerHealed(1);
		Eplayerhp -= 1;
	}
}

/*!
@brief  -this function is called when player is healed, to prevent over healing past max hp
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Checkoverheal(int healamt)
{
	if (player_maxhp - (PlayerGethealth()) >= healamt)
	{
		PlayerHealed(healamt);
	}
}

/*!
@brief  -this function is called to print the number of empty hearts the player has relative to the current and max health of the player
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
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
}


/*!
@brief  -this function is called to print the number of RED hearts the player has relative to the current  health of the player
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Player_Redheartprinter(void)
{
	int playerhp = p1.get(&p1);
	imageIndex = 1;
	imageIndex = (imageIndex + 1) % 2; // decides which spritte to take on the sheet, adjust hard coded initialising at the top 
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
}


/*********************************************************************************************** End of Premade Functions for interacting with Player's Health system in Game.c ************************************************************************************************/


/*********************************************************************************************** Start of  Shop,Skills,Upgrade,PrepRoom,Pause,Win,Lose,Revive,YouDied Ui Printers  ************************************************************************************************/

/*!
@brief  -this function is called to print the sprites of the EXP, Gold and ReviveToken on the Main screen during the play state
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_Currency_Print(void)
{
	CP_Image_Draw(Image_GoldSprite, Currency_Sprite.posX, Currency_Sprite.posY, isaac_width, isaac_height, 255);
	CP_Image_Draw(Image_ExpSprite, Currency_Sprite.posX, Currency_Sprite.posY, isaac_width, isaac_height, 255);
	CP_Image_Draw(Image_ReztokenSprite, Currency_Sprite.posX, Currency_Sprite.posY, isaac_width, isaac_height, 255);
}

/*!
@brief  -this function is called to print the the Gameover Screen when Gamestate ="LOSE"
		-Player Enters "LOSE" when player dies while  reviveToken == 0
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_GAMEOVER_Print(void)										
{
	CP_Image_Draw(Image_Gameover_Background, GameOver_Background.posX, GameOver_Background.posY, isaac_width, isaac_height, 255);
}

/*!
@brief  -this function is called to print the amount of EXP, Gold, and revive tokens the player is in posession of
		-Pass in the variable to print into score , and x and y coordinates to print it at
		-Maximum number printer pritable is 0-99
		NOTE: Font , FontSize, and Font Color needs to be specified before calling the functions
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void ScorePrinter(int score, float x, float y)
{
	CP_Font_Set(BonesFont);
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
	case 21:
		CP_Font_DrawText(Twenty1, x, y);
		break;
	case 22:
		CP_Font_DrawText(Twenty2, x, y);
		break;
	case 23:
		CP_Font_DrawText(Twenty3, x, y);
		break;
	case 24:
		CP_Font_DrawText(Twenty4, x, y);
		break;
	case 25:
		CP_Font_DrawText(Twenty5, x, y);
		break;
	case 26:
		CP_Font_DrawText(Twenty6, x, y);
		break;
	case 27:
		CP_Font_DrawText(Twenty7, x, y);
		break;
	case 28:
		CP_Font_DrawText(Twenty8, x, y);
		break;
	case 29:
		CP_Font_DrawText(Twenty9, x, y);
		break;
	case 30:
		CP_Font_DrawText(Thirty, x, y);
		break;
	case 31:
		CP_Font_DrawText(Thirty1, x, y);
		break;
	case 32:
		CP_Font_DrawText(Thirty2, x, y);
		break;
	case 33:
		CP_Font_DrawText(Thirty3, x, y);
		break;
	case 34:
		CP_Font_DrawText(Thirty4, x, y);
		break;
	case 35:
		CP_Font_DrawText(Thirty5, x, y);
		break;
	case 36:
		CP_Font_DrawText(Thirty6, x, y);
		break;
	case 37:
		CP_Font_DrawText(Twenty7, x, y);
		break;
	case 38:
		CP_Font_DrawText(Twenty8, x, y);
		break;
	case 39:
		CP_Font_DrawText(Twenty9, x, y);
		break;
	case 40:
		CP_Font_DrawText(Fourty, x, y);
		break;
	case 41:
		CP_Font_DrawText(Fourty1, x, y);
		break;
	case 42:
		CP_Font_DrawText(Fourty2, x, y);
		break;
	case 43:
		CP_Font_DrawText(Fourty3, x, y);
		break;
	case 44:
		CP_Font_DrawText(Fourty4, x, y);
		break;
	case 45:
		CP_Font_DrawText(Fourty4, x, y);
		break;
	case 46:
		CP_Font_DrawText(Fourty4, x, y);
		break;
	case 47:
		CP_Font_DrawText(Fourty4, x, y);
		break;
	case 48:
		CP_Font_DrawText(Fourty4, x, y);
		break;
	case 49:
		CP_Font_DrawText(Fourty4, x, y);
		break;
	case 50:
		CP_Font_DrawText(Fifty, x, y);
		break;
	case 51:
		CP_Font_DrawText(Fifty1, x, y);
		break;
	case 52:
		CP_Font_DrawText(Fifty2, x, y);
		break;
	case 53:
		CP_Font_DrawText(Fifty3, x, y);
		break;
	case 54:
		CP_Font_DrawText(Fifty4, x, y);
		break;
	case 55:
		CP_Font_DrawText(Fifty5, x, y);
		break;
	case 56:
		CP_Font_DrawText(Fifty6, x, y);
		break;
	case 57:
		CP_Font_DrawText(Fifty7, x, y);
		break;
	case 58:
		CP_Font_DrawText(Fifty8, x, y);
		break;
	case 59:
		CP_Font_DrawText(Fifty9, x, y);
		break;
	case 60:
		CP_Font_DrawText(Sixty, x, y);
		break;
	case 61:
		CP_Font_DrawText(Sixty1, x, y);
		break;
	case 62:
		CP_Font_DrawText(Sixty2, x, y);
		break;
	case 63:
		CP_Font_DrawText(Sixty3, x, y);
		break;
	case 64:
		CP_Font_DrawText(Sixty4, x, y);
		break;
	case 65:
		CP_Font_DrawText(Sixty5, x, y);
		break;
	case 66:
		CP_Font_DrawText(Sixty6, x, y);
		break;
	case 67:
		CP_Font_DrawText(Sixty7, x, y);
		break;
	case 68:
		CP_Font_DrawText(Sixty8, x, y);
		break;
	case 69:
		CP_Font_DrawText(Sixty9, x, y);
		break;
	case 70:
		CP_Font_DrawText(Seventy, x, y);
		break;
	case 71:
		CP_Font_DrawText(Seventy1, x, y);
		break;
	case 72:
		CP_Font_DrawText(Seventy2, x, y);
		break;
	case 73:
		CP_Font_DrawText(Seventy3, x, y);
		break;
	case 74:
		CP_Font_DrawText(Seventy4, x, y);
		break;
	case 75:
		CP_Font_DrawText(Seventy5, x, y);
		break;
	case 76:
		CP_Font_DrawText(Seventy6, x, y);
		break;
	case 77:
		CP_Font_DrawText(Seventy7, x, y);
		break;
	case 78:
		CP_Font_DrawText(Seventy8, x, y);
		break;
	case 79:
		CP_Font_DrawText(Seventy9, x, y);
		break;
	case 80:
		CP_Font_DrawText(Eighty, x, y);
		break;
	case 81:
		CP_Font_DrawText(Eighty1, x, y);
		break;
	case 82:
		CP_Font_DrawText(Eighty2, x, y);
		break;
	case 83:
		CP_Font_DrawText(Eighty3, x, y);
		break;
	case 84:
		CP_Font_DrawText(Eighty4, x, y);
		break;
	case 85:
		CP_Font_DrawText(Eighty5, x, y);
		break;
	case 86:
		CP_Font_DrawText(Eighty6, x, y);
		break;
	case 87:
		CP_Font_DrawText(Eighty7, x, y);
		break;
	case 88:
		CP_Font_DrawText(Eighty8, x, y);
		break;
	case 89:
		CP_Font_DrawText(Eighty9, x, y);
		break;
	case 90:
		CP_Font_DrawText(Ninety, x, y);
		break;
	case 91:
		CP_Font_DrawText(Ninety1, x, y);
		break;
	case 92:
		CP_Font_DrawText(Ninety2, x, y);
		break;
	case 93:
		CP_Font_DrawText(Ninety3, x, y);
		break;
	case 94:
		CP_Font_DrawText(Ninety4, x, y);
		break;
	case 95:
		CP_Font_DrawText(Ninety5, x, y);
		break;
	case 96:
		CP_Font_DrawText(Ninety6, x, y);
		break;
	case 97:
		CP_Font_DrawText(Ninety7, x, y);
		break;
	case 98:
		CP_Font_DrawText(Ninety8, x, y);
		break;
	case 99:
		CP_Font_DrawText(Ninety9, x, y);
		break;

	default:
		score = 99;
		CP_Font_DrawText(Ninety9, x, y);
		break;
	}
}

/*!
@brief  -this function is called to print the the YouDied Screen when the gamestate = "YOUDIED"
		-Player Enters "YOUDIED" when player dies while in reviveToken != 0
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_YOUDIED_Print(void)											
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_YouDied_Background, Revive_Background.posX, Revive_Background.posY, isaac_width, isaac_height, 255);
}


/*!
@brief  -this function is called to print the the REVIVE Screen when the gamestate = "REVIVE"
		-Player Enters "REVIVE" when player clicks anyone the screen after entering the "YOUDIED" screen
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_REVIVE_Print(void)											
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_Revive_Background, Revive_Background.posX, Revive_Background.posY, isaac_width, isaac_height, 255);
	CP_Settings_Fill(darkviolet);
	ScorePrinter(revivetoken, 432, 347);
}

/*!
@brief  -this function is called to print the the WIN Screen when the gamestate = "WIN"
		-Player Enters "WIN" when player Survives all the waves intended to spawn in the level
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_WIN_Print(void)											
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_Win_Background, Win_Background.posX, Win_Background.posY, isaac_width, isaac_height, 255);
}

/*!
@brief  -this function is called to print the the THANKS Screen when the gamestate = "THANKS"
		-Player Enters "THANKS" when player first clears level 5
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_THANKS_Print(void)
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_Thanks_Background, Thanks_Background.posX, Thanks_Background.posY, isaac_width, isaac_height, 255);
}

/*!
@brief  -this function is called to print the the PAUSE Screen when the gamestate = "PAUSE"
		-Player Enters "PAUSE" when the player presses the key tied to trigger the pause state
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_PAUSE_Print(void)										
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_Pause_Mistake, Pause_Background.posX, Pause_Background.posY, isaac_width, isaac_height, 255);

	/*float mousehoverPosX = CP_Input_GetMouseX();
	float mousehoverPosY = CP_Input_GetMouseY();*/

	/*CP_Settings_TextSize(20);
	CP_Settings_Fill(COLOR_GOLD);
	CP_Font_Set(CP_Font_GetDefault());

	if (Pause_Background.hover == FALSE)
	{
		CP_Font_DrawTextBox(Pause_mainmenu_Desc, mousehoverPosX + isaac_addmousepos, mousehoverPosY, isaac_textboxwidth);
	}*/
}


/*!
@brief  -this function is called to print the the PREPROOM Screen when the gamestate = "PREPROOM"
		-Player Enters "PREPROOM" when the player Clicks continue from the "WIN" screen
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_PREPROOM_Print(void)											
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_PrepRoom_Empty, PrepRoom_Background.posX, PrepRoom_Background.posY, isaac_width, isaac_height, 255);
}
	

/*!
@brief  -this function is called to print the the UPGRADE Screen when the gamestate = "UPGRADE"
		-Player Enters "UPGRADE" when the player Clicks the upgrade button.
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_UPGRADES_Print(void)											
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("x is %f, y is %f \n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	CP_Image_Draw(Image_Upgrade_Empty, Upgrade_Background.posX, Upgrade_Background.posY, isaac_width, isaac_height, 255);
}

/*!
@brief  -this function is called to print the the SHOP Screen when the gamestate = "SHOP"
		-Player Enters "SHOP" when the player Clicks The SHOP button
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_SHOP_Print(void)								
{
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
		CP_Image_Draw(Image_Shop_DropsOn, Shop_Background.posX, Shop_Background.posY, isaac_width, isaac_height, 100);
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

	float mousehoverPosX = CP_Input_GetMouseX();
	float mousehoverPosY = CP_Input_GetMouseY();

	CP_Settings_TextSize(20);
	CP_Settings_Fill(COLOR_GOLD);
	CP_Font_Set(CP_Font_GetDefault());

	if (Shop_HealButton.hover == FALSE)
	{
		CP_Font_DrawTextBox(Shop_Heal_Desc, mousehoverPosX + isaac_addmousepos, mousehoverPosY, isaac_textboxwidth);
	}
	if (Shop_DropsButton.hover == FALSE)
	{
		CP_Font_DrawTextBox(Shop_Drop_Desc, mousehoverPosX + isaac_addmousepos, mousehoverPosY, isaac_textboxwidth);

	}
	if (Shop_RezButton.hover == FALSE)
	{
		CP_Font_DrawTextBox(Shop_Rez_Desc, mousehoverPosX + isaac_addmousepos, mousehoverPosY, isaac_textboxwidth);
	}
	if (Shop_ShrapnelButton.hover == FALSE)
	{
		CP_Font_DrawTextBox(Shop_Shrapnel_Desc, mousehoverPosX - (6*isaac_addmousepos), mousehoverPosY, isaac_textboxwidth);
	}
	if (Shop_Shockwave.hover == FALSE)
	{
		CP_Font_DrawTextBox(Shop_Shockwave_Desc, mousehoverPosX - (6*isaac_addmousepos), mousehoverPosY, isaac_textboxwidth);
	}

	CP_Settings_TextSize(100);
	CP_Settings_Fill(COLOR_WHITE);
	ScorePrinter(Gold,335, 429);
}

/*!
@brief  This is the brain of printing all skills tree buttons and number
@param  NIL
@return NIL
*//*______________________________________________________________*/
void Screen_SKILL_Print(void)											
{
	CP_Image_Draw(Image_Skill_Tree, Skill_Background.posX, Skill_Background.posY, isaac_width, isaac_height, 255); //prints the base background

	//prints the base button image for all skills
	CP_Image_Draw(skill_arrow_size.image, skill_arrow_size.position.x, skill_arrow_size.position.y, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT, 255);
	CP_Image_Draw(skill_attack_speed.image, skill_attack_speed.position.x, skill_attack_speed.position.y, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT, 255);
	CP_Image_Draw(skill_blast_range.image, skill_blast_range.position.x, skill_blast_range.position.y, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT, 255);
	CP_Image_Draw(skill_health.image, skill_health.position.x, skill_health.position.y, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT, 255);
	CP_Image_Draw(skill_movement.image, skill_movement.position.x, skill_movement.position.y, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT, 255);
	CP_Image_Draw(skill_shrapnels.image, skill_shrapnels.position.x, skill_shrapnels.position.y, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT, 255);
	CP_Image_Draw(skill_sword_range.image, skill_sword_range.position.x, skill_sword_range.position.y, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT, 255);
	CP_Image_Draw(skill_sword_swing.image, skill_sword_swing.position.x, skill_sword_swing.position.y, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT, 255);
	CP_Image_Draw(skill_arrow_charge.image, skill_arrow_charge.position.x, skill_arrow_charge.position.y, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT, 255);
	CP_Image_Draw(skill_sword_crit.image, skill_sword_crit.position.x, skill_sword_crit.position.y, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT, 255);

	CP_Graphics_ClearBackground(COLOR_BLACK);

	//prints the number of upgrade for each skills button
	skills_num_printer(skill_sword_crit);
	skills_num_printer(skill_arrow_size);
	skills_num_printer(skill_attack_speed);
	skills_num_printer(skill_blast_range);
	skills_num_printer(skill_health);
	skills_num_printer(skill_movement);
	skills_num_printer(skill_shrapnels);
	skills_num_printer(skill_sword_range);
	skills_num_printer(skill_sword_swing);
	skills_num_printer(skill_arrow_charge);

	//Prints skills description when mouse hovering above button
	skill_description_printer();

	CP_Settings_TextSize(100);
	CP_Settings_Fill(COLOR_WHITE);
	ScorePrinter(Exp, 325, 429);

	CP_Settings_TextSize(20);
	CP_Font_DrawTextBox("Right-click to sell skills", WIDTH/3*2 + 100, 1010, WIDTH);
}


/*********************************************************************************************** End of Shop,Skills,Upgrade,PrepRoom,Pause,Win,Lose,Revive,YouDied Ui Printers  ************************************************************************************************/


/*********************************************************************************************** START of Collision Detection Functions ************************************************************************************************/

/*!
@brief  -this function is called to check for collision when a key is triggered
		-this function takes Current position	(posx, posy)
		-top left corner of the box				(startx and starty)
		-bottom right of the box				(endx, endy)
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
BOOL IsaacCheckCollisionWithButtonImage(float posX, float posY, float startX, float starty, float endx, float endy)											
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

/*!
@brief  -this function is called to check for collision when no key is triggered
		-this function takes Current position	(posx, posy)
		-top left corner of the box				(startx and starty)
		-bottom right of the box				(endx, endy)
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
BOOL IsaacHover(float posX, float posY, float startX, float starty, float endx, float endy)
{
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
}


/**************************************************************************************** END of Collision Detection Functions ************************************************************************************************/


/**************************************************************************************** START  of Shop,Skills,Upgrade,PrepRoom,Pause,Win,Lose,Revive,YouDied Ui Collision Checkers ************************************************************************************************/


/*!
@brief  -this function is called to check for collisions on the "LOSE" SCreen and call the intended instruction when a button is pressed
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_GAMEOVER_ButtonClicked(void)											
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("button pressed  \n");

		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 44.0, 820.0, 403.0, 939.0))
		{
			play_click();
			printf("button pressed mm \n");
			gameState = MAIN_MENU;
			currentLevel = MAIN_MENU;
		}

		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 557.0, 822.0, 906.0, 936.0))
		{
			play_click();
			printf("button pressed retry \n");
			gamePause = 1;
			*tick = 0;
			reset_enemy_and_weapon();
			preload_spawn_map(currentLevel);
			ResetState();
			gameState = currentLevel;
		}
	}
}

/*!
@brief  -this function is called Check if the player has fufilled the conditions to Lose the round, and changes the Gamestate to LOSE, and Do the necessary Resets
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void DeathCondition(void)
{
	if (PlayerGethealth() == 0)
	{
		gamePause = !gamePause;
		reset_enemy_and_weapon();
		ResetState();
		gameState = LOSE;
	}
}

/*!
@brief  -this function is called to check for collisions on the "WIN" SCreen and call the intended instruction when a button is pressed
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_WIN_ButtonClicked(void)											
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("button pressed  \n");
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 206.0, 628.0, 727.0, 829.0))
		{
			printf("button pressed continue \n");
			//gameState = PREPROOM;
			if (firstclear == 0 && currentLevel==LEVEL_5) {
				firstclear = 1;
				gameState=THANKS;
			}
			else{
			   gameState = PREPROOM;
			}
		}
		
	}
}

/*!
@brief  -this function is called to check for collisions on the "THANKS" SCreen and call the intended instruction when a button is pressed
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_Thanks_ButtonClicked(void)
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		printf("button pressed  \n");
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();

		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 206.0, 628.0, 727.0, 829.0))
		{
			printf("button pressed continue \n");
			gameState = MAIN_MENU;
		
		}

	}
}

/*!
@brief  -this function is called to check for collisions on the "PAUSE" SCreen and call the intended instruction when a button is pressed
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_PAUSE_ButtonClicked(void)											
{
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		printf("button pressed back esc \n");
		printf("button pressed continue \n");
		gamePause = !gamePause;
		gameState = currentLevel;
	}

	/*float mousehoverPosX = CP_Input_GetMouseX();
	float mousehoverPosY = CP_Input_GetMouseY();

	if (IsaacHover(mousehoverPosX, mousehoverPosY, 299.0, 661.0, 595.0, 781.0))
	{
		Pause_Background.hover = FALSE;
	}
	else
	{
		Pause_Background.hover = TRUE;
	}*/


	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();

		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 199.0, 350.0, 699.0, 507.0))
		{
			printf("button pressed continue \n");
			gamePause = !gamePause;
			gameState = currentLevel;
		}

		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 297.0, 510.0, 580.0, 622.0))
		{
			printf("button pressed retry\n");
			reset_enemy_and_weapon();
			preload_spawn_map(currentLevel);
			ResetState();
			gameState = currentLevel;
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 150.0, 614.0, 742.0, 744.0))
		{
			printf("button pressed menu\n");
			gameState = MAIN_MENU;
			currentLevel = MAIN_MENU;
		}
	}
}


/*!
@brief  -this function is called to check for collisions on the "PREPROOM" SCreen and call the intended instruction when a button is pressed
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_PREPROOM_ButtonClicked(void)											
{ 
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
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 270.0, 550.0, 684.0, 676.0))
		{
			printf("button pressed continye \n");
			gamePause = !gamePause;
			reset_enemy_and_weapon();
			preload_spawn_map(currentLevel);
			ResetState();
			gameState = currentLevel;
		}
	
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 143.0, 827.0, 511.0, 916.0))
		{
			printf("button pressed quit\n");
			gameState = MAIN_MENU;
			currentLevel = MAIN_MENU;
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 597.0, 827.0, 913.0, 915.0))
		{
			printf("button pressed upgrade\n");
			gameState = UPGRADES;
		}
	}
}


/*!
@brief  -this function is called to check for collisions on the "UPGRADE" SCreen and call the intended instruction when a button is pressed
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_UPGRADE_ButtonClicked(void)											
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
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 792.0, 24.0, 952.0, 160.0))
		{
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
			printf("button pressed skill\n");
			gameState = SKILL;
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 552.0, 353.0, 936.0, 730.0))
		{
			printf("button pressed shop\n");
			gameState = SHOP;
		}

	}
}

/*!
@brief  -this function is called to check for collisions on the "SHOP" SCreen and call the intended instruction when a button is pressed
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_SHOP_ButtonClicked(void)											
{
	float mousehoverPosX = CP_Input_GetMouseX();
	float mousehoverPosY = CP_Input_GetMouseY();
	
	if (IsaacHover(mousehoverPosX, mousehoverPosY, 26.0, 546.0, 459.0, 671.0))
	{
		printf("button hovering heal \n");
		Shop_HealButton.hover = FALSE;
	}
	else
	{
		Shop_HealButton.hover = TRUE;
	}

	if (IsaacHover(mousehoverPosX, mousehoverPosY, 25.0, 690.0, 460.0, 843.0))
	{
		printf("button pressed drop\n");
		Shop_DropsButton.hover = FALSE;
	}
	else
	{
		Shop_DropsButton.hover = TRUE;
	}

	if (IsaacHover(mousehoverPosX, mousehoverPosY, 25.0, 833.0, 460.0, 955.0))
	{
		printf("button pressed rez\n");
		Shop_RezButton.hover = FALSE;
	}
	else
	{
		Shop_RezButton.hover = TRUE;
	}
	if (IsaacHover(mousehoverPosX, mousehoverPosY, 511.0, 543.0, 943.0, 661.0))
	{
		printf("button pressed shrapnel\n");
		Shop_ShrapnelButton.hover = FALSE;
	}
	else
	{
		Shop_ShrapnelButton.hover = TRUE;
	}
	
	if (IsaacHover(mousehoverPosX, mousehoverPosY, 511.0, 686.0, 943.0, 811.0))
	{
		printf("button pressed shockwave\n");
		Shop_Shockwave.hover = FALSE;
	}
	else
	{
		Shop_Shockwave.hover = TRUE;
	}



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
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 787.0, 27.0, 936.0, 154.0))
		{
			CP_Graphics_ClearBackground(COLOR_BLACK);
			printf("button pressed back \n");
			gameState = UPGRADES;
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 26.0, 546.0, 459.0, 671.0))
		{
			CP_Graphics_ClearBackground(COLOR_BLACK);
			printf("button pressed heal\n");
			if ((Gold > 10) && (DoubleHeal == FALSE))
			{
				play_coins();

				Gold -= 10;
				DoubleHeal = TRUE;
				Shop_HealButton.enabled = FALSE;
			}
			else
			{
				play_denied();
				printf("not enough gold ");
			}
			
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 25.0, 690.0, 460.0, 843.0))
		{
			CP_Graphics_ClearBackground(COLOR_BLACK);
			printf("button pressed drop\n");
			if ((Gold > 10) && (DoubleDrop == FALSE))
			{
				play_coins();

				Gold -= 10;
				DoubleDrop = TRUE;
				Shop_DropsButton.enabled = FALSE;
			}
			else
			{
				play_denied();
				printf("not enough gold ");
			}
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 25.0, 833.0, 460.0, 955.0))
		{
			CP_Graphics_ClearBackground(COLOR_BLACK);
			//play_coins();
			printf("button pressed rez\n");
			if (Gold > 5)
			{
				play_coins();
				revivetoken++;
				Gold -= 5;
			}
			else
			{
				play_denied();
				printf("not enough gold ");
			}
			
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 511.0, 543.0, 943.0, 661.0))
		{
			CP_Graphics_ClearBackground(COLOR_BLACK);
			printf("button pressed shrapnel\n");
			if ((Gold > 20) && (shrapnelstate == FALSE))
			{
				play_coins();
				Gold -= 20;
				shrapnelstate = TRUE;
			}
			else
			{
				play_denied();
				printf("not enough gold ");
			}
		}
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 511.0, 686.0, 943.0, 811.0))
		{
			CP_Graphics_ClearBackground(COLOR_BLACK);
			printf("button pressed shockwave\n");
			if ((Gold > 20) && (shockwavestate == FALSE))
			{
				play_coins();
				Gold -= 20;
				shockwavestate = TRUE;
			}
			else
			{
				play_denied();
				printf("not enough gold ");
			}
		}
	}
}

/*!
@brief  -this function is called to check for collisions on the "SKILL" SCreen and call the intended instruction when a button is pressed
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_SKILL_ButtonClicked(void)											
{
	float mousehoverPosX = CP_Input_GetMouseX();
	float mousehoverPosY = CP_Input_GetMouseY();

	if (IsaacHover(mousehoverPosX, mousehoverPosY, 44.0, 540.0, 483.0, 668.0))
	{
		Skill_HeartsButton.hover = FALSE;
	}
	else
	{
		Skill_HeartsButton.hover = TRUE;
	}

	if (IsaacHover(mousehoverPosX, mousehoverPosY, 44.0, 683.0, 480.0, 811.0))
	{
		Skill_AgilityButton.hover = FALSE;
	}
	else
	{
		Skill_AgilityButton.hover = TRUE;
	}

	if (IsaacHover(mousehoverPosX, mousehoverPosY, 44.0, 832.0, 480.0, 958.0))
	{
		Skill_CritButton.hover = FALSE;
	}
	else
	{
		Skill_CritButton.hover = TRUE;
	}

	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		gameState = UPGRADES;
	}

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		CP_Vector mouse = CP_Vector_Set(mousePosX, mousePosY);
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 767.0, 28.0, 924.0, 153.0)) gameState = UPGRADES;

		//Skills upgrade for only health and movement
		if (button_collision(mouse, skill_movement.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) {
			if (Exp > 0 && originalPlayerSpeed < maxadditionalspeed) {

				Exp -= 1;
				play_click();
				skill_movement.state++;
				additionalspeed = 30;
				//knight.speed += additionalspeed;
				originalPlayerSpeed += additionalspeed;
				//printf("knight speed: %f\n", knight.speed);
			}
			else
			{
				play_denied();
			}
		}
		if (button_collision(mouse, skill_health.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) {
			if (Exp > 0 && skill_health.state < maxadditionalhp) {

				Exp -= 1;
				play_click();

				additionalhp = ++skill_health.state;
				p1.set(&p1, 3 + additionalhp);
			}
			else
			{
				play_denied();
			}
		}

		//Skills upgrade for newer skill 
		buy_skill(&skill_arrow_charge, mouse, max_skill_upgrade);
		buy_skill(&skill_arrow_size, mouse, max_skill_upgrade);
		buy_skill(&skill_attack_speed, mouse, max_skill_upgrade);
		buy_skill(&skill_blast_range, mouse, max_skill_upgrade);
		buy_skill(&skill_shrapnels, mouse, max_skill_upgrade);
		buy_skill(&skill_sword_range, mouse, max_skill_upgrade);
		buy_skill(&skill_sword_swing, mouse, max_skill_upgrade);
		buy_skill(&skill_sword_crit, mouse, max_skill_upgrade);

	}

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_2)) {
		// sell skills and refund exp to player 
		float mousePosX = CP_Input_GetMouseX();
		float mousePosY = CP_Input_GetMouseY();
		CP_Vector mouse = CP_Vector_Set(mousePosX, mousePosY);
		
		//skills refund for only health and movement
		if (skill_health.state) {
			if (button_collision(mouse, skill_health.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) {
				skill_health.state--;
				play_click();

				Exp++;
				additionalhp--;
				p1.set(&p1, 3 + additionalhp);
			}
		}
		if (skill_movement.state) {
			if (button_collision(mouse, skill_movement.position, SKILLS_BUTTON_WIDTH, SKILLS_BUTTON_HEIGHT)) {
				skill_movement.state--;
				play_click();

				Exp++;
				additionalspeed = 30;
				originalPlayerSpeed -= additionalspeed;
			}
		}
		
		//Skills refund for newer skill 
		refund_skill(&skill_arrow_charge, mouse);
		refund_skill(&skill_arrow_size, mouse);
		refund_skill(&skill_attack_speed, mouse);
		refund_skill(&skill_blast_range, mouse);
		refund_skill(&skill_shrapnels, mouse);
		refund_skill(&skill_sword_range, mouse);
		refund_skill(&skill_sword_swing, mouse);
		refund_skill(&skill_sword_crit, mouse);
	}
}

/*!
@brief  -this function is called to check for collisions on the "YOUDIED" SCreen and call the intended instruction when a button is pressed
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_YOUDIED_ButtonClicked(void)											
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
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 4.0, 5.0, 952.0, 1009.0))
		{
			printf("button pressed back \n");
			gameState = REVIVE;
		}
	}
}

/*!
@brief  -this function is called to check for collisions on the "REVIVE" SCreen and call the intended instruction when a button is pressed
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void Screen_REVIVE_ButtonClicked(void)											
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
		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 99.0, 524.0, 394.0, 711.0))
		{
			printf("button pressed yes \n");
			revivetoken -= 1;
			*tick = 0;
			//ResetState();
			ResetState_revive();
			gameState = currentLevel;
		}

		if (IsaacCheckCollisionWithButtonImage(mousePosX, mousePosY, 511.0, 539.0, 728.0, 736.0))
		{
			printf("button pressed no \n");
			gameState = LOSE;
		}
	}
}

/**************************************************************************************** END of Shop,Skills,Upgrade,PrepRoom,Pause,Win,Lose,Revive,YouDied Ui Collision Checkers ************************************************************************************************/


/*!
@brief  -this function is called to Free all the images loaded for the Shop,Skills,Upgrade,PrepRoom,Pause,Win,Lose,Revive,YouDied Ui
@return - this function does not return a value, just a function call to execute a set number of instructions
*//*_________________________________________________________________________________________________________________________________________________________________*/
void exit_skilltreepictures(void) 
{
	CP_Image_Free(&Image_GoldSprite);
	CP_Image_Free(&Image_ExpSprite);
	CP_Image_Free(&Image_ReztokenSprite);

	CP_Image_Free(&Image_PrepRoom_Empty);
	CP_Image_Free(&Image_Upgrade_Empty);
	CP_Image_Free(&Image_Skill_Tree);
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
	
	CP_Image_Free(&Image_Thanks_Background);



	CP_Image_Free(&Image_num_1) ;
	CP_Image_Free(&Image_num_2) ;
	CP_Image_Free(&Image_num_3) ;
	CP_Image_Free(&Image_num_4) ;
	CP_Image_Free(&Image_num_5) ;
	CP_Image_Free(&Image_num_6) ;
	CP_Image_Free(&Image_num_7) ;
	CP_Image_Free(&Image_num_8) ;
	CP_Image_Free(&Image_num_9) ;
	CP_Image_Free(&Image_num_10) ;
	CP_Image_Free(&skill_health.image);
	CP_Image_Free(&skill_movement.image);
	CP_Image_Free(&skill_arrow_charge.image);
	CP_Image_Free(&skill_arrow_size.image);
	CP_Image_Free(&skill_attack_speed.image);
	CP_Image_Free(&skill_blast_range.image);
	CP_Image_Free(&skill_shrapnels.image);
	CP_Image_Free(&skill_sword_range.image);
	CP_Image_Free(&skill_sword_swing.image);
	CP_Image_Free(&skill_sword_crit.image);
}