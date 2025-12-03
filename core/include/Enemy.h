#ifndef ENEMY_C
#define ENEMY_C

#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BulletManager.h"
#include "UIManager.h"

typedef struct enemySprite_t
{
    Vector2 position;     
    BulletManager_t* bulletManagerRef;
    UIScreen_t* UI_ScreenRef;


    int screenWidth;
    int screenHeight;
    int enemyPixelWidth;
    int enemyPixelHeight;

    bool isDead;
    float explosionTimer;

    Sound explosionSound;

    int CorrectSpriteFrame;

    bool isActive;

    float time;
    bool canShoot;

    float speed;
    Vector2 dir;

}enemySprite_t;

enemySprite_t* enemySprite_new(BulletManager_t* bulletManager,UIScreen_t* UI_Screen);

void UpdateEnemy(enemySprite_t* enemySprite);

Vector2 GetRandomDirection(enemySprite_t* enemySprite);

void EnemyOnCollision(enemySprite_t* enemySprite, char type);

void FreeEnemy(enemySprite_t* enemySprite);

#endif