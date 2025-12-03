#ifndef UI_MANAGER_C
#define UI_MANAGER_C
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct UIScreen_t
{
    int score;
    int height;
    int width;

    int playerHP;

}UIScreen_t;

UIScreen_t* UIScreen_new(int screenWidth, int screenHeight);

void UpdateScore(UIScreen_t* Ui_Screen,float score);

void DrawUI(UIScreen_t* Ui_Screen, Texture2D spritesheet);

void DrawPlayerLives(UIScreen_t* Ui_Screen, Texture2D spritesheet);

void DrawScoreBoard(UIScreen_t* Ui_Screen, Texture2D spritesheet);

void FreeUI(UIScreen_t* Ui_Screen);


#endif