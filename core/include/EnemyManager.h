#ifndef ENEMY_MANAGER_C
#define ENEMY_MANAGER_C
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <Enemy.h>
#include "UIManager.h"


typedef struct EnemyContainer_t
{
    enemySprite_t **enemies;
    BulletManager_t* bulletManagerRef;
    UIScreen_t* UI_ScreenRef;
    int enemyCount;
    float time; 

}EnemyContainer_t;

EnemyContainer_t* EnemyContainer_new(BulletManager_t* bulletManagerRef,UIScreen_t* UI_ScreenRef);


void PopulateEnemyArray(EnemyContainer_t* container,BulletManager_t* bulletManagerRef);

void SpawnEnemy(EnemyContainer_t* container, float x, float y);

void UpdateEnemiesManager(EnemyContainer_t* container);

void DrawsEnemiesManager(EnemyContainer_t* enemyContainer, Texture2D spritesheet);

void ActivateEnemy(EnemyContainer_t* container);

void FreeEnemyManager(EnemyContainer_t* enemyContainer);

#endif
