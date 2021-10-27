

#define COLOR_GRAY CP_Color_Create(127, 127, 127, 255)
#define COLOR_GREEN CP_Color_Create(0, 255, 0, 255)
#define COLOR_BLUE CP_Color_Create(0, 0, 255, 255)
#define COLOR_WHITE CP_Color_Create(255, 255, 255, 255)

#define TRUE 1
#define FALSE 0
#define BOOL CP_BOOL

void ButtonClicked();
void DrawGameCanvas();
void DrawMenuButton();
void DrawMenuCanvas();
BOOL CheckCollisionWithBox(float posX, float posY, float boundaryX, float boundaryY, float posBoxX, float posBoxY);