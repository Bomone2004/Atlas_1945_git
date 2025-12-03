#include "Enemy.h"
#include "EnemyManager.h"
#include "raylib.h"
#include "UIManager.h"

EnemyContainer_t* EnemyContainer_new(BulletManager_t* bulletManager,UIScreen_t* UI_Screen) {
    EnemyContainer_t* EnemyAliveContainer= calloc(1, sizeof(EnemyContainer_t)); //Allocation of an enemy manager in memory
    BulletManager_t* bulletManagerRef = bulletManager; //Same reason as the UI_Screen one
    EnemyAliveContainer->UI_ScreenRef = UI_Screen; //Reference needed in order to be able to pass UI_Screen to the enemies
    EnemyAliveContainer->enemyCount = 5;
    EnemyAliveContainer->enemies = calloc(EnemyAliveContainer->enemyCount, sizeof(enemySprite_t)); //Allocation of n-count of enemies in memory

    static float spawnTimer = 0.0f;
    float time = spawnTimer;

    PopulateEnemyArray(EnemyAliveContainer,bulletManagerRef);
    return EnemyAliveContainer;
}

void PopulateEnemyArray(EnemyContainer_t* container,BulletManager_t* bulletManager) {
    for (int i = 0; i < container->enemyCount; i++) {
        container->enemies[i] = enemySprite_new(bulletManager, container->UI_ScreenRef);
        container->enemies[i]->isActive = false;
        container->enemies[i]->isDead = false;
        container->enemies[i]->position.x = -2000;
        container->enemies[i]->position.y = -2000;
    }
}

void SpawnEnemy(EnemyContainer_t* container, float x, float y) {
    for (int i = 0; i < container->enemyCount; i++) {
        if (!container->enemies[i]->isActive) {
            container->enemies[i]->isActive = true;
            container->enemies[i]->position.x = GetRandomValue(0, GetScreenWidth() - container->enemies[i]->enemyPixelWidth );
            container->enemies[i]->position.y = GetRandomValue(0, 200);
            break;
        }
    }
}

void UpdateEnemiesManager(EnemyContainer_t* container) {
    
    //If enough time passes another enemy is activated else all enemies are updated if they are active or on their way to die
    container->time -= GetFrameTime();
    if (container->time <= 0.0f) {
        container->time = 5.0f; // Reset spawn timer
        ActivateEnemy(container);
    }
    for (int i = 0; i < container->enemyCount; i++) {
        if (container->enemies[i]->isActive || container->enemies[i]->isDead) {
            UpdateEnemy(container->enemies[i]);
        }
    }
}

void ActivateEnemy(EnemyContainer_t* container) {
    for (int i = 0; i < container->enemyCount; i++) {
        if (!container->enemies[i]->isActive && container->enemies[i]->isDead == false) {
            container->enemies[i]->isActive = true;
            container->enemies[i]->position.x = GetRandomValue(0, GetScreenWidth() - container->enemies[i]->enemyPixelWidth);
            container->enemies[i]->position.y = GetRandomValue(0, 100);
            break;
        }
    }
}


//If the enemy is active he uses the sprite for the enemy, else if he is dead he uses the sprite for the explosion "montage"
void DrawsEnemiesManager(EnemyContainer_t* enemyContainer, Texture2D spritesheet) {
    for (int i = 0; i < enemyContainer->enemyCount; i++) {
       if (enemyContainer->enemies[i]->isActive) {
            Rectangle source_enemy = (Rectangle){((enemyContainer->enemies[i]->enemyPixelWidth  +1) * enemyContainer->enemies[i]->CorrectSpriteFrame), 33, enemyContainer->enemies[i]->enemyPixelWidth, enemyContainer->enemies[i]->enemyPixelHeight};
            Rectangle dest_enemy = (Rectangle){enemyContainer->enemies[i]->position.x,enemyContainer->enemies[i]->position.y, enemyContainer->enemies[i]->enemyPixelWidth,enemyContainer->enemies[i]->enemyPixelHeight};  //(float)GetScreenWidth(), (float)GetScreenHeight()
            Vector2 orig_enemy = (Vector2){0};

            DrawTexturePro(spritesheet, source_enemy, dest_enemy, orig_enemy ,0, WHITE);
       }
       else if(enemyContainer->enemies[i]->isDead)
       {
            Rectangle source_enemy = (Rectangle){(70+( 32 * enemyContainer->enemies[i]->CorrectSpriteFrame)), 170, enemyContainer->enemies[i]->enemyPixelWidth, enemyContainer->enemies[i]->enemyPixelHeight};
            Rectangle dest_enemy = (Rectangle){enemyContainer->enemies[i]->position.x,enemyContainer->enemies[i]->position.y, enemyContainer->enemies[i]->enemyPixelWidth,enemyContainer->enemies[i]->enemyPixelHeight};  //(float)GetScreenWidth(), (float)GetScreenHeight()
            Vector2 orig_enemy = (Vector2){0};

            DrawTexturePro(spritesheet, source_enemy, dest_enemy, orig_enemy ,0, WHITE);
       }
    }         
}

//Free the memory occupied by the manager and respective enemies at the end of program and set all variables to their default value
void FreeEnemyManager(EnemyContainer_t* enemyContainer)
{
    for (int i = 0; i < enemyContainer->enemyCount; i++) 
    {
        FreeEnemy(enemyContainer->enemies[i]);
    }
    enemyContainer->bulletManagerRef = NULL;
    enemyContainer->enemyCount = 0;
    enemyContainer->time = 0;
    free(enemyContainer);
}


