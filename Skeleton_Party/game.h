/*---------------------------------------------------------
 * file:	game.h 
 * author:	jazz, isaac, keith, yi thon, qiu hui
 * email:	j.teoh@digipen.edu,i.yeo@digipen.edu, weijiekeith.lua@digipen.edu,yithon.goh@digipen.edu,qiuhui.tan@digipen.edu
*
 * brief:	This file contains delcaration of functions, variables, arrays, constants and structs
 *			Especially for those which would be used across different .c files
*
 * documentation link:
 * https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
*
 * Copyright © 2020 DigiPen, All rights reserved.
* ---------------------------------------------------------*/

#pragma once
extern float tick_p, * tick ; //This is for the tick timer. *tick will give back the tick 


#define MAX_DROP 100
#define TRUE 1
#define FALSE 0
#define BOOL CP_BOOL
#define WIDTH 960.0f
#define HEIGHT 1035.0f
#define PI 3.1415926535
#define MAX_ENEMY 3500
#define MAX_MOTHER_ENEMY 50
#define MAX_CHILDREN 50
#define Formationsingle 0
#define Formationcircle 1
#define Formationline 2
#define ShapeSizecircle 7
#define ShapeSizeline  5
#define ENEMY_SIZE_2 10
#define E1 (CP_Vector_Set(-1, 0))
#define E2 (CP_Vector_Set(0, 1))
#define NUM_POSITION_RATIO 0.22f
enum { SKILLS_BUTTON_WIDTH = 426, SKILLS_BUTTON_HEIGHT = 76 };

#define COLOR_GRAY CP_Color_Create(127, 127, 127, 255)
#define COLOR_BLACK CP_Color_Create(0, 0, 0, 255)
#define COLOR_GREEN CP_Color_Create(0, 255, 0, 255)
#define COLOR_BLUE CP_Color_Create(0, 0, 255, 255)
#define COLOR_WHITE CP_Color_Create(255, 255, 255, 255)
#define COLOR_RED CP_Color_Create(255, 0, 0, 255)
#define COLOR_PURPLE CP_Color_Create(128,0,128, 255)
#define COLOR_GOLD CP_Color_Create(232, 209, 81, 255)
#define pueple CP_Color_Create(255, 0, 0, 255)
#define darkviolet CP_Color_Create(148, 0, 211, 255)



int Exp, Gold ;
int* ptr_Gold; 
int additionalExp, additionalGold;
int additionalcrit;
int* ptr_additionalcrit;

BOOL firstclear;
BOOL DoubleExp, DoubleGold, DoubleHeal, DoubleDrop ;

int gamePause;
enum { knightint, mageint, archerint };
BOOL shrapnelstate, shockwavestate;
BOOL RewardGiven;
BOOL MainMenuState;
int revivetoken;
//int SWORD_CRIT_CHANCE;


typedef struct EnemySprite
{
	float x, y, dx; // where dx is the velocity 
}EnemySprite;
EnemySprite* enemy[MAX_ENEMY]; // when used, if first one is null, all othjers will be set to 0 
EnemySprite* enemycircle[MAX_ENEMY][ShapeSizecircle];
EnemySprite* enemyline[MAX_ENEMY][ShapeSizeline];


//@purpose struct for sprite character properties
struct character
{
    CP_Vector position;
    CP_Image sprite;
	float width;
	float height;
	float speed;
	int transparency;
	BOOL speedbuff;
	BOOL invulnerability;
};

//@purpose initialise character 
struct character knight, mage, archer;

struct enemy
{
	CP_Vector enemyPosition;
	CP_Image enemyDesign;
	CP_Image enemyDead;
	float width;
	float height;
	int alive;
} bug;



//Struct for standard enemy, used in enemy_pool
struct Enemy {
	CP_Vector position; //position of enemy
	int alive; //boolean 1 or 0
	float size; //radius of enemy
	int type; //movement pattern
};

//Struct for spawn setting, used in spawn_pool
struct spawn {
	CP_Vector position; //position of enemy to spawn
	float time; // time in terms of tick to spawn enemy
	int type; //movement pattern
};

//Struct for mother enemy, used in mother_enemy_pool
struct mother_enemy {
	CP_Vector position; //position of mother enemy
	float time; // time in terms of tick to spawn enemy
	int alive; //boolean 1 or 0
	int type; //movement pattern
	struct Enemy children[MAX_CHILDREN]; //child enemy under this mother enemy
	float spare; //Spare parameter for variety of usage. 
	float spare2; //Second spare parameter for variety of usage.
};

//Struct for button, used for skills tree button mostly/only
typedef struct button {
	CP_Vector position; //Position of button center
	CP_Vector num_position; //Position of where number of increment should be printed in skills button
	CP_Image image; //Image of button
	int state; //Number of upgrade triggered in the skill
	const char* description; //Description of the skill that should appear when hovering on button
} button;

//Image of number for skill upgrade
extern CP_Image Image_num_1;
extern CP_Image Image_num_2;
extern CP_Image Image_num_3;
extern CP_Image Image_num_4;
extern CP_Image Image_num_5;
extern CP_Image Image_num_6;
extern CP_Image Image_num_7;
extern CP_Image Image_num_8;
extern CP_Image Image_num_9;
extern CP_Image Image_num_10;

//Buttons for each upgrades
extern button skill_arrow_charge;
extern button skill_arrow_size;
extern button skill_attack_speed;
extern button skill_blast_range;
extern button skill_health;
extern button skill_movement;
extern button skill_shrapnels;
extern button skill_sword_range;
extern button skill_sword_swing;
extern button skill_sword_crit;
extern int max_skill_upgrade;

//Declaration for struct arrays required for Enemy_array.c
struct Enemy enemy_pool[MAX_ENEMY];
struct spawn spawn_pool[MAX_ENEMY];
struct mother_enemy mother_enemy_pool[MAX_MOTHER_ENEMY];










void PlayerSetHealth (int Basehealth);
void Playertakedamage(int damageAmt);
void PlayerHealed(int healAmt);
int PlayerGethealth(void);

void update_char(int CurrentCharacter, struct character* spritename);


void init_PlayerHP(void);
void Player_FullHeal(void);

void Player_Emptyheartprinter(void);
void Player_Redheartprinter(void);
void DeathCondition(void);

void exit_PlayerHP(void);

////////////All functions/variables declarations below can be found/defined in keith.c or is done by Keith/////////////////////////////////////////////////////////

int CurrentCharacterKeith;
float originalPlayerPositionX;
float originalPlayerPositionY;

float originalPlayerSpeed;
float winning_condition;
int currentLevel;

//Struct for item used in item_pool array
struct Item
{
	CP_Vector position;
	CP_Image sprite;
	int enabled;
	int id;
	float width;
	float height;
	float despawnTimer;
	int transparency;
};

//Declarations of item and item_pool array
struct Item item;
struct Item item_pool[MAX_DROP];
enum GameStates {LOGO, MAIN_MENU, INSTRUCTIONS, EXIT, LEVEL_SELECTION, LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5,
	             PAUSED, PREPROOM, UPGRADES, SHOP, SKILL,WIN, LOSE, RETRY, CREDIT1, CREDIT2, CREDIT3, YOUDIED, REVIVE,THANKS};

enum GameStates gameState;

void Damage(float damage); //Unused
void DrawPlayerHealth(); //Unused
void DrawHP(float currentHealth, float maxHealth ); //Unused
void FullscreenKeyPressed(); //Unused
void FullscreenMode(); 

void ResetState_revive(void);
void FreeImage();
void EnableMenu();
void DespawnTimer();
void DrawObjectiveText();
void DrawBuffIndicator();
void ButtonLevelSelectionClicked();
void DrawLevelSelectionCanvas();
void ResetItemPool();
void WinCondition();
void ResetState();
void DrawLogoScreen();
void ReturnMainMenuClicked();
void DrawInstructionsCanvas();
void InvulnerabilityFrame();
void EnemyCollision();
void SpeedBuffEffect();
void DropStuff(float posX, float posY);
void DropStuffs(CP_Vector position);
void DrawItem();
void TerminateFullscreen();
void LoadFont();
void LoadBackgroundImage(int id);
void InitializeVariables();
void ButtonClicked();
void DrawGameCanvas();
void DrawMenuCanvas();

BOOL CheckIfBoxesOverlap(float posX1, float posY1, float width1, float height1, float posX2, float posY2, float width2, float height2);
BOOL CheckCollisionWithBoxImage(float posX, float posY, float widthBox, float heightBox, float posBoxX, float posBoxY);
BOOL CheckCollisionWithBox(float posX, float posY, float boundaryX, float boundaryY, float posBoxX, float posBoxY);

///////////////////End of function/variables declarations that are found/defined in keith.c or is done by Keith/////////////////////////////////////////////////////
void game_control(struct character* spritename);
void init_char(struct character* spritename, float spawnx, float spawny, char* pathname);



void melee_attack(CP_Vector position);
void print_cooldown(CP_Vector position, int weapon); //int weapon, 0 for sword, 1 for fireball

void melee_update(CP_Vector position);
void initiate_melee(void);

CP_Vector rotate_vector(float scalar, float angle, CP_Vector unit_vector);

void print_melee_weapon(CP_Vector position, float angle);

int rect_collision(CP_Vector enemy, CP_Vector position, CP_Vector vec1, CP_Vector vec2, float enemy_radius);

enum Direction { UP = 1, DOWN, LEFT, RIGHT };
CP_Vector enemy_moving_up_down_left_right(CP_Vector enemy_current, float velocity_scale, int direction);

void timer(void);

void timer_reset(void);

int out_of_screen(CP_Vector sprite_position);

void shooting_check(CP_Vector position);

void shoot_bullet(CP_Vector position);

void update_bullet_travel(void);

void print_bullet(void);

void explosion_update(void);

void explosion_print(void);

void explode(CP_Vector position);

void sword_explosion(CP_Vector position);

void sword_explosion_update(void);

void sword_explosion_print(void);

void sword_explosion_update(void);

void shrapnel(CP_Vector position);

void shrapnel_update(void);

void print_shrapnel(void);

void shrapnel_collision(void);

void weapon_to_enemy_collision(void);

void print_piercing_bullet(void);

void update_piercing_bullet_travel(void);

void shoot_piercing_bullet(CP_Vector position, float charge);

void piercing_shooting_check(CP_Vector position);

double sine(double range, int randomiser, double speed);

void print(void); //for debugging only

void run_once_only(void);

struct Enemy enemy_set(CP_Vector position, int alive, float size, int type);

void update_basic_movement(void);

void initialise_basic_movement(int spawn_pool_i);

void movement_pattern_spinning_circle(void);

void spin_enemy(int mother_i, int enemy_count, float spin_speed, float radius, CP_Vector position);

void vertical_enemy(int mother_i, int enemy_count, float distance_apart);

void PlayGame();

void spawn_map(void);
void spawnerthing(CP_Vector position, int spawn_amount, int type);

void preload_spawn_map(int level);

void spawn_pool_assigner(CP_Vector position, float spawn_speed_delay, float start_spawn_tick, int spawn_amount, int type);

void enemy_out_of_screen(int enemy_not_mother, int enemy_i);

void print_enemy(CP_Vector position, float size);

void print_charge(CP_Vector position, float charge);

//These are the function that updates the positions every frame
	void movement_pattern_vertical_and_diagonal(void);
	void initialise_horizontal_line(CP_Vector start_position, int enemy_count, float distance_apart, int type);

//-------------------------------
//End of enemy array functions
//void init_enemy();
void reset_enemy_and_weapon(void);

void skills_num_printer(button current_button);

int button_collision(CP_Vector mouse, CP_Vector button, float x, float y);

void refund_skill(button* current_button, CP_Vector mouse);

void buy_skill(button* current_button, CP_Vector mouse, int max_upgrade);

void skill_description_printer(void);

//void player_touch_enemy();

//void enemy_movement();

//void enemy_damage();

void DrawPauseCanvas();
void PauseButtonClicked();
void load_Credit_Image();
void drawCreditScreenpg1();
void drawCreditScreenpg2();
void drawCreditScreenpg3();
void creditBtnClicked();
void free_IMAGE();
void load_audio();

void play_menubg();
void play_crit();
void play_death();
void play_swordHit();
void play_healthDrop();
void play_speedDrop();
void play_swordSwing();
void play_click();
void play_charswitch();
void play_denied();
void play_coins();
void free_audio();


//BOOL check_enemy_collide(float posX, float posY, float boundaryX, float boundaryY, float posBoxX, float posBoxY

void InitializeSkillShopUI(void);
BOOL IsaacCheckCollisionWithButtonImage(float posX, float posY, float startX, float starty, float endx, float endy);



void Screen_YOUDIED_Print(void);
void Screen_REVIVE_Print(void);
void Screen_Currency_Print(void);
void ScorePrinter(int score, float x, float y);
void Screen_GAMEOVER_Print(void);
void Screen_THANKS_Print(void);
void Screen_WIN_Print(void);
void Screen_PAUSE_Print(void);
void Screen_PREPROOM_Print(void);	
void Screen_UPGRADES_Print(void);
void Screen_SHOP_Print(void);
void Screen_SKILL_Print(void);

BOOL IsaacHover(float posX, float posY, float startX, float starty, float endx, float endy);

void Checkoverheal(int healamt);

void Screen_YOUDIED_ButtonClicked(void);
void Screen_REVIVE_ButtonClicked(void);

void Screen_GAMEOVER_ButtonClicked(void);
void Screen_Thanks_ButtonClicked(void);

void Screen_WIN_ButtonClicked(void);
void Screen_PAUSE_ButtonClicked(void);
void Screen_PREPROOM_ButtonClicked(void);
void Screen_UPGRADE_ButtonClicked(void);
void Screen_SHOP_ButtonClicked(void);
void Screen_SKILL_ButtonClicked(void);

void exit_skilltreepictures(void);


