

#define TRUE 1
#define FALSE 0
#define BOOL CP_BOOL

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
BOOL CheckCollisionWithBox(float posX, float posY, float boundaryX, float boundaryY, float posBoxX, float posBoxY);