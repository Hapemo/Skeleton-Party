

#define TRUE 1
#define FALSE 0
#define BOOL CP_BOOL
#define WIDTH (float)CP_System_GetWindowWidth()
#define HEIGHT (float)CP_System_GetWindowHeight()
#define PI 3.1415926535
#define MAX_ENEMY 500

enum GameStates { MAIN_MENU, EXIT, PLAYING, PAUSED };
enum GameStates gameState;


struct character
{
    CP_Vector position;
    CP_Image sprite;
	float width;
	float height;
	float speed;
};

struct character knight;

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

struct Item item;


void Damage(float damage);
void DrawPlayerHealth();
void DrawHP(float currentHealth, float maxHealth );


void PlayerSetHealth (int Basehealth);
void Playertakedamage(int damageAmt);
void PlayerHealed(int healAmt);
int PlayerGethealth(void);


void init_PlayerHP(void);

void Player_Emptyheartprinter(void);
void Player_Redheartprinter(void);


void exit_PlayerHP(void);


void DropStuff(float posX, float posY);
void DrawItem();
void TerminateFullscreen();
void LoadFont();
void LoadBackgroundImage();
void InitializeVariables();
void FullscreenKeyPressed();
void FullscreenMode();
void ButtonClicked();
void DrawGameCanvas();
void DrawMenuButton();
void DrawMenuCanvas();
void game_control();
void init_char();

BOOL CheckIfBoxesOverlap(float posX1, float posY1, float width1, float height1, float posX2, float posY2, float width2, float height2);


BOOL CheckCollisionWithBox(float posX, float posY, float boundaryX, float boundaryY, float posBoxX, float posBoxY);

/*!
@brief		Activates the melee attack for wherever the position of sprite is.
@param		*melee_angle - This is should take in 1 for starter, the function will change it according to the angle of attack at specific frames
			position - This is the position of the sprite, where the melee attack will happen from
@return		NIL
*//*______________________________________________________________*/
void melee_attack(CP_Vector position, CP_Vector *enemy);

/*!
@brief		This function detects mouse click, and activate the melee attack function for wherever the mouse is at. (the position can be changed in future)
@param		*melee_angle - This is should take in 1 from game.c, the function will change it later on according to the angle of attack at specific frames (it's to be parsed into function melee_attack
@return		NIL
*//*______________________________________________________________*/
void activate_melee_by_mouse(CP_Vector position);

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
@brief		Checks collision of sword with a point. This function is to be used inside function melee_attack
@param		enemy - position of enemy point
			position - position of sword
			vec1 - 
@return		NIL
*//*______________________________________________________________*/
void sword_collision(CP_Vector enemy, CP_Vector position, CP_Vector vec1, CP_Vector vec2);

/*!
@brief		A prototype stage function. To check if collision with target happened. Determines if collision happen via int collide.
@param		NIL
@return		NIL
*//*______________________________________________________________*/
void lightbulb(void);

CP_Vector enemy_moving_up_down_left_right(CP_Vector enemy_current, CP_Vector* vector, float velocity_scale, int direction);

void enemy_pattern_circle(CP_Vector mid_position, float enemy_number, float big_radius, int speed);

void movement_1(void);

void print_enemy(CP_Vector sprite_position);

int tick(void);

void init_enemy();

void enemy_movement();

void enemy_damage();

void DrawPauseCanvas();

BOOL check_enemy_collide(float posX, float posY, float boundaryX, float boundaryY, float posBoxX, float posBoxY);