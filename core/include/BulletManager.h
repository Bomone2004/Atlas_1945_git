#ifndef BULLET_MANAGER_C
#define BULLET_MANAGER_C
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Bullet.h"

typedef struct BulletManager_t
{
    Bullet_t** enemyBullets;
    Bullet_t** playerBUllets;
    
    int bulletCount;

}BulletManager_t;

BulletManager_t* BulletManager_new();

void PopulateArray(BulletManager_t* bulletManager);

void ActivatePlayerBullet(BulletManager_t* bulletManager, Vector2 position);

void ActivateEnemyBullet(BulletManager_t* bulletManager, Vector2 EnemyBulletPosition,Vector2 dir);

void UpdateBullets(BulletManager_t* bulletManager);

void DrawBulletManager(BulletManager_t* bulletManager, Texture2D spritesheet);

void FreeBullets(BulletManager_t* bulletManager);


#endif
