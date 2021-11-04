#include <stdio.h>
#include <stdlib.h>
#include "cprocessing.h"

// my defines 
#define pueple CP_Color_Create(255, 0, 0, 255)

//hp bar defines
static CP_Image spriteSheetImage;
static int imageIndex; // decides what image it uses 
static const float Heart_FRAME_DIMENSIONx = 58.0f; 
static const float Heart_FRAME_DIMENSIONy = 45.0f;
int player_maxhp;
static  float Heart_size_windowsx;
static  float Heart_size_windowsy;

static float hplocationX = 100.0f;
static float hplocationY = 100.0f;



//Enemy define
static CP_Image EnemyspriteSheetImage;
#define MAX_ENEMY 500
static const float Enemy_FRAME_DIMENSIONx = 59.0f;
static const float Enemy_FRAME_DIMENSIONy = 59.0f;

static  float Enemy_size_windowsx;
static  float Enemy_size_windowsy;

static float EnemylocationX;
static float EnemylocationY;




//#define COLOR_RED CP_Color_Create(255, 0, 0, 255)
#define TRUE 1
#define FALSE 0
int gIsPaused;
CP_Image hpbar = NULL;

//my Functions 
void envsettings(void)
{
	CP_System_SetFrameRate(20);
	CP_System_SetWindowSize(1000, 900);
	//CP_System_Fullscreen void;
	CP_System_SetWindowTitle("The Game");
}


void Player_Emptyheartprinter(int playerhp)
{
	int Eplayerhp = player_maxhp - playerhp ;
	imageIndex = 0;
	imageIndex = (imageIndex + 1) % 2; // decides which spritte to take on the sheet, adjust hard coded initialising at the top 

	//spriteSheetImage = CP_Image_Load("./Assets/HeartSptite.png");
	for (int y=0;y<Eplayerhp;y++)
	{
		CP_Image_DrawSubImage(spriteSheetImage, // image used 
			hplocationX + ((y+playerhp) * (Heart_size_windowsx- 60.0f)) +(Heart_FRAME_DIMENSIONx*(y+playerhp)), hplocationY, // coordinates of where the sprite is drawn
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

void Player_Redheartprinter(int playerhp)
{	
	imageIndex = 1;
	imageIndex = (imageIndex + 1) % 2; // decides which spritte to take on the sheet, adjust hard coded initialising at the top 

	//spriteSheetImage = CP_Image_Load("./Assets/HeartSptite.png");
	for (int y=0; y < playerhp;y++)
	{
		CP_Image_DrawSubImage(spriteSheetImage,
			hplocationX + (y* (Heart_size_windowsx - 60.0f)) + (y*Heart_FRAME_DIMENSIONx), hplocationY, // coordinates of where the sprite is drawn
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

	
	//int width = CP_System_GetWindowWidth();
	//int height = CP_System_GetWindowHeight();
	//CP_Image_Draw(hpbar, width / 2, height / 2, width / 2, width / 2, 255);
	//CP_Image_Draw(hpbar, 500, 450, 250 / 2, 450 / 4, 255);
}
//#define button_width 100f
//#define button_height 150f


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

// Enemy decleration --------------------------------------------------------------------------

typedef struct Enemy
{
	float x, y, dx; // where dx is the velocity 
}Enemy;

// enemy data and pos will be stored in array of pointers
Enemy* enemy[MAX_ENEMY] = { NULL }; // when used, if first one is null, all othjers will be set to 0 

void addEnemy(float x, float y, float dx)
{
	//("enemyadded\n");
	// go through array to look for first avai enemy stored 
	int found = -1;
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (enemy[i] == NULL)
		{
			found = i;
			break;
		}
	}
	// if found, use the enemy storage
	if (found >= 0)
	{
		//printf("enemyfound\n");

		enemy[found] = malloc(sizeof(enemy));
		enemy[found]->x = x;
		enemy[found]->y = y;
		enemy[found]->dx = dx;

	}
}
// index  i will be the index in the array 
void removeEnemy(int i)
{

	if (enemy[i]== NULL)
	{
		free(enemy[i]);
		enemy[i] = NULL;
	}
}

void cycleEnemyRemove(void)
{
	for (int a = 0; a < MAX_ENEMY; a++)
	{
		removeEnemy(a);
	}
}

void Enemy_printer(void)
{

	imageIndex = 0;
	imageIndex = (imageIndex + 1) % 1; // decides which spritte to take on the sheet, adjust hard coded initialising at the top 

	//spriteSheetImage = CP_Image_Load("./Assets/HeartSptite.png");
	for (int y = 0; y < MAX_ENEMY; y++)
	{
		if (enemy[y] != NULL) {
			CP_Image_DrawSubImage(EnemyspriteSheetImage, // image used 
				enemy[y]->x, enemy[y]->y, // coordinates of where the sprite is drawn
				Enemy_size_windowsx, Enemy_size_windowsy,   // image size on window 
				imageIndex * Enemy_FRAME_DIMENSIONx, 0, // image selection  by parts. first image = 0 + 1 % 4 = 1, second image = 1 + 1 % 4 = 2, third image = 2 + 1 % 4 = 3 , forth image = 3+1 % 4 = 0 
				// image 4 / 4 is the first one on the sprite sheet
				// horizontal movement, vertical movement
				// frame diemnsion is 1 sprite on the sprite sheet
				// left most pixel, top most pixel (top left corner )
				Enemy_FRAME_DIMENSIONx, Enemy_FRAME_DIMENSIONy, // right most pixel, bottom most pixel (bottom right corner )
				255); // alpha value that affects transpaarency
		}
	}

	//CP_Image_Free(&spriteSheetImage);
}





#define COLOR_GRAY CP_Color_Create(150, 150, 150, 255)
#define COLOR_BLACK CP_Color_Create(0, 0, 0, 255)
void boxgenerate(void)
{
	CP_Settings_Fill(COLOR_GRAY);

	// heal box
	CP_Graphics_DrawRect(450 , 450, 100.00, 100.00);
	// damage box
	CP_Graphics_DrawRect(700, 700, 100.00, 100.00);
}


void Generatetitle(void)
{
	CP_Settings_Fill(COLOR_BLACK);
	CP_Font_DrawText("Heal", 450, 450);
	CP_Font_DrawText("damage", 700, 700);

}

int Colcheck(float xp, float yp, float x1, float y1, float x2, float y2)
{
	if ((xp > x1) && (xp < x2) && (yp > y1) && (yp < y2))
	{
		return 1;
	}
	return 0;
}
	// in function check

//Main Game Functions 
void game_init(void)
{
	CP_System_SetFrameRate(10);
	CP_System_ShowConsole();
	envsettings();
	//hp init
	spriteSheetImage = CP_Image_Load("./Assets/HeartSprite.png");
	NewHealthSystem(p1)
	p1.set(&p1,10);
	hplocationX = (CP_System_GetWindowWidth()) / 20.0f;
	hplocationY = (CP_System_GetWindowHeight()) / 20.0f;

	Heart_size_windowsx = (CP_System_GetWindowWidth()) / 20.0f;
	Heart_size_windowsy = (CP_System_GetWindowHeight()) / 20.0f;

	// enemy init

	EnemyspriteSheetImage = CP_Image_Load("./Assets/Enemydot.png");

	Enemy_size_windowsx = (CP_System_GetWindowWidth()) / 20.0f;
	Enemy_size_windowsy = (CP_System_GetWindowHeight()) / 20.0f;
	EnemylocationX = 0.f;
	EnemylocationY = 0.f;


}

void game_update(void)
{
	EnemylocationX = CP_Input_GetMouseX();
	EnemylocationY = CP_Input_GetMouseY();
	CP_Graphics_ClearBackground(COLOR_GRAY);

	//static NewHealthSystem(p1)

	 // will disappear after 1 cycle of update
		
	// col heal
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		if (Colcheck(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 450, 450, 450 + 100, 450 + 100) == 1)
		{
			// heal
			printf("%d\n", player_maxhp);

			p1.heal(&p1, 1);
			printf("%d\n", p1.get(&p1));
		}
		// col damage 
		if (Colcheck(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 700, 700, 700 + 100, 700 + 100) == 1)
		{
			// damage 
			printf("%d\n", player_maxhp);

			p1.damage(&p1, 1);
			printf("%d\n", p1.get(&p1));
		}
	}


	// add random spawn here 
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_2)) {
		/*
		if (Colcheck(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 450, 450, 450 + 100, 450 + 100) == 1)
		{
			// heal
			printf("%d\n", player_maxhp);

			p1.heal(&p1, 1);
			printf("%d\n", p1.get(&p1));
		}
		// col damage 
		if (Colcheck(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 700, 700, 700 + 100, 700 + 100) == 1)
		{
			// damage 
			printf("%d\n", player_maxhp);

			p1.damage(&p1, 1);
			printf("%d\n", p1.get(&p1));
		}*/
		addEnemy(CP_Input_GetMouseX()+(float)40.0, CP_Input_GetMouseY()+(float)15.0,(float)3.0);
	}



	for (int i = 0; i < MAX_ENEMY; i++) {


		if (enemy[i] != NULL)// if (enemy[i])
		{
			// add player homing here 
			//printf("updated enemy locatrion\n");

			enemy[i]->x += enemy[i]->dx;
			//printf("enenmy %d x location is %f",i, enemy[i]->x);


			if (enemy[i]->x < -1000 || enemy[i]->x >1000)
			{
				//printf("enemylocation Exceeded\n");
				enemy[i] = NULL;
				removeEnemy(i);
			}
	}
		}
		

	//printer Functions 
	Player_Redheartprinter(p1.get(&p1));
	Player_Emptyheartprinter(p1.get(&p1));
	Enemy_printer();


	boxgenerate();
	Generatetitle();

	cycleEnemyRemove();

}

void game_exit(void)
{
	CP_Image_Free(&spriteSheetImage);
	CP_Image_Free(&EnemyspriteSheetImage);
}