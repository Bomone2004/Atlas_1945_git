#ifndef PLAYER_C
#define PLAYER_C
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "BulletManager.h"
#include "UIManager.h"


typedef struct playerSprite_t
{
    Vector2 position;      
    BulletManager_t* bulletManagerRef;
    UIScreen_t* UI_ScreenRef;

    int hp;

    int screenWidth;
    int screenHeight;
    int playerPixelWidth;
    int playerPixelHeight;
    float nextFrameTimer;
    int currentFrame;
    int invisibilyFrames;
    bool isHit;

    float shootCooldown;
    float speed;


    // int playerTilesX;
    // int playerTilesY;

}playerSprite_t;

playerSprite_t* playerSprite_new(BulletManager_t* bulletManager,UIScreen_t* UI_Screen);

void UpdatePlayer(playerSprite_t* playerSprite);

void DrawPlayer(playerSprite_t* playerSprite, Texture2D spritesheet);

void PlayerOnCollision(playerSprite_t* playerSprite);   

void FreePlayer(playerSprite_t* playerSprite);

#endif