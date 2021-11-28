
#pragma once
extern float tick_p, * tick ; //This is for the tick timer. *tick will give back the tick 


#define MAX_DROP 100
#define TRUE 1
#define FALSE 0
#define BOOL CP_BOOL
#define WIDTH 960.0f
#define HEIGHT 1035.0f
#define PI 3.1415926535
#define MAX_ENEMY 1500
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

#define COLOR_GRAY CP_Color_Create(127, 127, 127, 255)
#define COLOR_BLACK CP_Color_Create(0, 0, 0, 255)
#define COLOR_GREEN CP_Color_Create(0, 255, 0, 255)
#define COLOR_BLUE CP_Color_Create(0, 0, 255, 255)
#define COLOR_WHITE CP_Color_Create(255, 255, 255, 255)
#define COLOR_RED CP_Color_Create(255, 0, 0, 255)
#define COLOR_PURPLE CP_Color_Create(128,0,128, 255)
#define pueple CP_Color_Create(255, 0, 0, 255)
#define darkviolet CP_Color_Create(148, 0, 211, 255)


enum GameStates {LOGO, MAIN_MENU, INSTRUCTIONS, EXIT, LEVEL_SELECTION, LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5, PAUSED, PREPROOM, UPGRADES, SHOP, SKILL,WIN, LOSE, RETRY};
enum GameStates gameState;


float originalPlayerPositionX;
float originalPlayerPositionY;
int Exp, Gold ;
int additionalExp, additionalGold;

BOOL DoubleExp, DoubleGold, DoubleHeal, DoubleDrop ;

int gamePause;
enum { knightint, mageint, archerint };
BOOL shrapnelstate, shockwavestate;
BOOL RewardGiven;


typedef struct EnemySprite
{
	float x, y, dx; // where dx is the velocity 
}EnemySprite;
EnemySprite* enemy[MAX_ENEMY]; // when used, if first one is null, all othjers will be set to 0 
EnemySprite* enemycircle[MAX_ENEMY][ShapeSizecircle];
EnemySprite* enemyline[MAX_ENEMY][ShapeSizeline];



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


struct Item
{
	CP_Vector position;
	CP_Image sprite;
	int enabled;
	int id;
	float width;
	float height;
};

struct Enemy {
	CP_Vector position;
	int alive; //boolean 1 or 0
	float size; //radius of enemy
	int type;
};

struct spawn {
	CP_Vector position;
	float time;
	int type;
};

struct mother_enemy {
	CP_Vector position;
	float time;
	int alive;
	int type;
	struct Enemy children[MAX_CHILDREN];
	float spare;
};

struct Enemy enemy_pool[MAX_ENEMY];
struct spawn spawn_pool[MAX_ENEMY];
struct mother_enemy mother_enemy_pool[MAX_MOTHER_ENEMY];

struct Item item;
struct Item item_pool[MAX_DROP];


void EnableMenu();
void Damage(float damage);
void DrawPlayerHealth();
void DrawHP(float currentHealth, float maxHealth );


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

//--------------------------------------------------------------------------------------------------------------------------------
//isaac's EnemySprite Functions 
//--------------------------------------------------------------------------------------------------------------------------------

//void addEnemy(float x, float y, float dx);
//void removeEnemy(int i);
//void cycleEnemyRemove(void);
//void Enemy_printer(void);
//void movement_1(float x, float y, float C_radius);
//CP_Vector Enemy_rotate_vector(float scalar, float angle, CP_Vector unit_vector);
//void enemy_pattern_circle(CP_Vector mid_position, float big_radius, int speed, int enemynum);
//void addenemy_pattern_circle(CP_Vector mid_position, float big_radius, int speed);
//void init_EnemySprite(void);
//void SpawnEnemyCircle(float Positionx, float Positiony);
//void SpawnEnemySingle(float Positionx, float Positiony);
//void UpdateEnemyMovement(void);
//void exit_EnemySprite(void);
//----------------------------------------------------------------------------------------------------------------------------------
void DrawBuffIndicator();
void ButtonLevelSelectionClicked();
void DrawLevelSelectionCanvas();
void ResetItemPool();
void WinCondition();
int currentState;
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
void FullscreenKeyPressed();
void FullscreenMode();
void ButtonClicked();
void DrawGameCanvas();
void DrawMenuButton();
void DrawMenuCanvas();
void EnableMenu();
void game_control(struct character* spritename);
void init_char(struct character* spritename, float spawnx, float spawny, char* pathname);

BOOL CheckIfBoxesOverlap(float posX1, float posY1, float width1, float height1, float posX2, float posY2, float width2, float height2);

BOOL CheckCollisionWithBoxImage(float posX, float posY, float widthBox, float heightBox, float posBoxX, float posBoxY);
BOOL CheckCollisionWithBox(float posX, float posY, float boundaryX, float boundaryY, float posBoxX, float posBoxY);

/*!
@brief		Activates the melee attack for wherever the position of sprite is.
@param		position - This is the position of the sprite, where the melee attack will happen from
@return		NIL
*//*______________________________________________________________*/
void melee_attack(CP_Vector position);
void print_cooldown(CP_Vector position, int weapon); //int weapon, 0 for sword, 1 for fireball

/*!
@brief		This function detects mouse click, and activate the melee attack function for wherever the mouse is at. (the position can be changed in future)
@param		*melee_angle - This is should take in 1 from game.c, the function will change it later on according to the angle of attack at specific frames (it's to be parsed into function melee_attack
@return		NIL
*//*______________________________________________________________*/
void melee_update(CP_Vector position);
void initiate_melee(void);

/*!
@brief		Calculate the vector direction due to change in rotation. Used in function melee_attack to calculate the angle 6
@param		*melee_angle - This is should take in 1 from game.c, the function will change it later on according to the angle of attack at specific frames (it's to be parsed into function melee_attack
@return		NIL
*//*______________________________________________________________*/
CP_Vector rotate_vector(float scalar, float angle, CP_Vector unit_vector);

/*!
@brief		Prints a rectangle as a weapon
@param		*melee_angle - angle of rectangle
			position - coordinate of rectangle
@return		NIL
*//*______________________________________________________________*/
void print_melee_weapon(CP_Vector position, float angle);

/*!
@brief		Checks collision of rect with a circle. This function is to be used inside function melee_attack
@param		enemy - position of enemy point
			position - position of sword
			vec1 - width of sword
			vec2 - length of sword
			enemy_radius - radius of enemy
@return		1 if collide, 0 if none
*//*______________________________________________________________*/
int rect_collision(CP_Vector enemy, CP_Vector position, CP_Vector vec1, CP_Vector vec2, float enemy_radius);

/*!
@brief		A prototype stage function. To check if collision with target happened. Determines if collision happen via int collide.
@param		NIL
@return		NIL
*//*______________________________________________________________*/
void lightbulb(void);

enum Direction { UP = 1, DOWN, LEFT, RIGHT };
CP_Vector enemy_moving_up_down_left_right(CP_Vector enemy_current, float velocity_scale, int direction);

//void enemy_pattern_circle(CP_Vector mid_position, float enemy_number, float big_radius, int speed);

//void movement_1(void);

//void print_enemy(CP_Vector sprite_position);

void timer(void);

void timer_reset(void);

int out_of_screen(CP_Vector sprite_position);

void shooting_check(CP_Vector position);

void shoot_bullet(CP_Vector position);

void update_bullet_travel(void);

void print_bullet(void);

//void bullet_collision(void);

void explosion_update(void);

void explosion_print(void);

void explode(CP_Vector position);

//void explosion_collision(void);

void sword_explosion(CP_Vector position);

void sword_explosion_update(void);

void sword_explosion_print(void);

//void sword_explosion_collision(void);

void sword_explosion_update(void);

void shrapnel(CP_Vector position);

void shrapnel_update(void);

void print_shrapnel(void);

void shrapnel_collision(void);

//void piercing_bullet_collision(void);
void weapon_to_enemy_collision(void);

void print_piercing_bullet(void);

void update_piercing_bullet_travel(void);

void shoot_piercing_bullet(CP_Vector position, float charge);

void piercing_shooting_check(CP_Vector position);

double sine(double speed, int randomiser);

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

//Start of enemy array functions
//-------------------------------
void preload_spawn_map(int level);

/*!
@brief		Assigns enemies to empty spawn_pool slots
@param		position - position of first enemy spawned
			spawn_speed_delay - delay between each enemy spawned (higher number = slower spawn rate)
			start_spawn_tick - tick time at which the enemy starts spawning
			spawn_amount - amount of enemy spawn
			type - movement pattern
@return		NIL
*//*______________________________________________________________*/
void spawn_pool_assigner(CP_Vector position, float spawn_speed_delay, float start_spawn_tick, int spawn_amount, int type);

void enemy_out_of_screen(int enemy_not_mother, int enemy_i);

void print_enemy(CP_Vector position, float size);

void print_charge(CP_Vector position, float charge);

//These are the function that updates the positions every frame
	void movement_pattern_vertical_and_diagonal(void);
	void initialise_circle_shape(CP_Vector mid_position, int enemy_count, float radius);
	void initialise_horizontal_line(CP_Vector start_position, int enemy_count, float distance_apart, int type);

//-------------------------------
//End of enemy array functions
//void init_enemy();
void reset_enemy_and_weapon(void);

void player_touch_enemy();

//void enemy_movement();

//void enemy_damage();

void DrawPauseCanvas();
void PauseButtonClicked();

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
void free_audio();


//BOOL check_enemy_collide(float posX, float posY, float boundaryX, float boundaryY, float posBoxX, float posBoxY

void InitializeSkillShopUI(void);
BOOL IsaacCheckCollisionWithButtonImage(float posX, float posY, float startX, float starty, float endx, float endy);

void InitializeRetry(void);
void Screen_Currency_Print(void);
void ScorePrinter(int score, float x, float y);
void Screen_GAMEOVER_Print(void);
void Screen_WIN_Print(void);
void Screen_PAUSE_Print(void);
void Screen_PREPROOM_Print(void);	
void Screen_UPGRADES_Print(void);
void Screen_SHOP_Print(void);
void Screen_SKILL_Print(void);

void Screen_GAMEOVER_ButtonClicked(void);
void Screen_WIN_ButtonClicked(void);
void Screen_PAUSE_ButtonClicked(void);
void Screen_PREPROOM_ButtonClicked(void);
void Screen_UPGRADE_ButtonClicked(void);
void Screen_SHOP_ButtonClicked(void);
void Screen_SKILL_ButtonClicked(void);

void exit_skilltreepictures(void);
void resetPool(void);


