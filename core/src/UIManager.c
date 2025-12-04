#include "UIManager.h"


UIScreen_t* UIScreen_new(int screenWidth, int screenHeight)
{
    UIScreen_t* Ui_screen = calloc(1,sizeof(UIScreen_t)); //Allocation of ui_screen in memory
    Ui_screen->score = 0;
    Ui_screen->width = screenWidth;
    Ui_screen->height = 100;
    Ui_screen->playerHP = 3;
    return Ui_screen;
}

void UpdateScore(UIScreen_t* Ui_Screen,float score)
{
    Ui_Screen->score += score;
}

void DrawUI(UIScreen_t* Ui_Screen, Texture2D spritesheet)
{
    DrawRectangle(0,GetScreenHeight()-Ui_Screen->height,GetScreenWidth(),Ui_Screen->height,BLACK);

    Rectangle sourceLogo = (Rectangle){704, 404, 100, 50};
    Rectangle destLogo = (Rectangle){(float)GetScreenWidth()-100, (float)GetScreenHeight()-Ui_Screen->height,100,50};
    Vector2 origLogo = (Vector2){0};

    DrawTexturePro(spritesheet, sourceLogo, destLogo, origLogo ,0, WHITE);
    DrawPlayerLives(Ui_Screen, spritesheet);
    DrawScoreBoard(Ui_Screen, spritesheet);
}

void DrawPlayerLives(UIScreen_t* Ui_Screen, Texture2D spritesheet){
    for(int i = 0; i < Ui_Screen->playerHP; i++){
        Rectangle sourceLogo = (Rectangle){202, 268, 32, 32}; 
        Rectangle destLogo = (Rectangle){100 + 50 * i, (float)GetScreenHeight()-80,50,50};
        Vector2 origLogo = (Vector2){0};

        DrawTexturePro(spritesheet, sourceLogo, destLogo, origLogo ,0, WHITE);
    }
}

void DrawScoreBoard(UIScreen_t* Ui_Screen, Texture2D spritesheet)
{
    char scorechar[20];
    sprintf(scorechar, "%d" , Ui_Screen->score);
    for(int i=0;i<4;i++)
    {
        int currentChar = scorechar[i]-'0';
        if(currentChar < 9 && currentChar >= 0)
        {
            Rectangle sourceLogo = (Rectangle){580 + (10 * currentChar), 105, 10, 20};
            Rectangle destLogo = (Rectangle){500 + (32*i), (float)GetScreenHeight()-70,30,60};
            Vector2 origLogo = (Vector2){0};
            DrawTexturePro(spritesheet, sourceLogo, destLogo, origLogo ,0, WHITE);
        }
    }


}

//Free the memory occupied by the manager and set all variables to their default value
void FreeUI(UIScreen_t* Ui_Screen)
{
    Ui_Screen->score = 0;
    Ui_Screen->width = 0;
    Ui_Screen->height = 0;
    free(Ui_Screen);
}



