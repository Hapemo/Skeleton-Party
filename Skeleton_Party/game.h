

#define TRUE 1
#define FALSE 0
#define BOOL CP_BOOL
#define WIDTH (float)CP_System_GetWindowWidth()
#define HEIGHT (float)CP_System_GetWindowHeight()

struct character
{
    CP_Vector position;
    CP_Image sprite;
	float width;
	float height;
};

struct character knight;

struct enemy
{
	CP_Vector enemyPosition;
	CP_Image enemyDesign;
	CP_Image enemyDead;
	float width;
	float height;
} bug;


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
void melee_attack(float* melee_angle, CP_Vector position);

/*!
@brief		This function detects mouse click, and activate the melee attack function for wherever the mouse is at. (the position can be changed in future)
@param		*melee_angle - This is should take in 1 from game.c, the function will change it later on according to the angle of attack at specific frames (it's to be parsed into function melee_attack
@return		NIL
*//*______________________________________________________________*/
void activate_melee_by_mouse(float *melee_angle);


void lightbulb(void);

void init_enemy();

void enemy_movement();

void enemy_damage();

BOOL check_enemy_collide(float posX, float posY, float boundaryX, float boundaryY, float posBoxX, float posBoxY);