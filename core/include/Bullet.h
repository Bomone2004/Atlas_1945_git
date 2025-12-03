#ifndef BULLET_C
#define BULLET_C
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct Bullet_t
{
    Vector2 position;      

    int screenWidth;
    int screenHeight;
    int bulletPixelWidth;
    int bulletPixelHeight;

    Vector2 enemyBulletDirection; 
    float speed;
    int correctFrame;
    int necessaryRotation;
    
    bool isActive;

    bool isPlayerBullet;
    // int playerTilesX;
    // int playerTilesY;

}Bullet_t;

Bullet_t* Bullet_new();

void UpdatePlayerBullet(Bullet_t* bullet);

void UpdateEnemyBullet(Bullet_t* bullet);

void GetCorrectFrame(Bullet_t* bullet, Vector2 dir);

void BulletOnCollision(Bullet_t* bullet, char type);

void FreeBullet(Bullet_t* bullet);


#endif