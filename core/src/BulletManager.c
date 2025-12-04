#include "BulletManager.h"
#include "raylib.h"

BulletManager_t* BulletManager_new(){
    //Allocation in memory 
    BulletManager_t* bulletManager = calloc(1, sizeof(BulletManager_t)); 

    bulletManager->bulletCount = 25;

    //Allocation in memory of enemy bullets
    bulletManager->enemyBullets = calloc(bulletManager->bulletCount, sizeof(BulletManager_t));

    //Allocation in memory of player bullets
    bulletManager->playerBUllets = calloc(bulletManager->bulletCount, sizeof(BulletManager_t));

    PopulateArray(bulletManager);

    return bulletManager;
}

//Function to populate the array with bullets
void PopulateArray(BulletManager_t* bulletManager) {
    for (int i = 0; i < bulletManager->bulletCount; i++) {
        bulletManager->enemyBullets[i] = Bullet_new();
        bulletManager->enemyBullets[i]->isActive = false;
        //Position out of Windows
        bulletManager->enemyBullets[i]->position.x = -200;
        bulletManager->enemyBullets[i]->position.y = -200;

        bulletManager->playerBUllets[i] = Bullet_new();
        bulletManager->playerBUllets[i]->isActive = false;
        //Position out of Windows
        bulletManager->playerBUllets[i]->position.x = -200;
        bulletManager->playerBUllets[i]->position.y = -200;
    }
}

void ActivatePlayerBullet(BulletManager_t* bulletManager, Vector2 PlayerBulletPosition){
    for (int i = 0; i < bulletManager->bulletCount; i++) {
        if (!bulletManager->playerBUllets[i]->isActive) {
            PlayerBulletPosition = (Vector2){PlayerBulletPosition.x + bulletManager->playerBUllets[i]->bulletPixelWidth * 0.5,PlayerBulletPosition.y};
            bulletManager->playerBUllets[i]->isActive = true;
            bulletManager->playerBUllets[i]->isPlayerBullet = true;
            bulletManager->playerBUllets[i]->position = PlayerBulletPosition;
            break;
        }
    }
}

void ActivateEnemyBullet(BulletManager_t* bulletManager, Vector2 EnemyBulletPosition,Vector2 dir)
{
    for (int i = 0; i < bulletManager->bulletCount; i++) {
        if (!bulletManager->enemyBullets[i]->isActive) 
        {
            EnemyBulletPosition = (Vector2){EnemyBulletPosition.x + bulletManager->enemyBullets[i]->bulletPixelWidth * 0.5,EnemyBulletPosition.y};
            bulletManager->enemyBullets[i]->isActive = true;
            bulletManager->enemyBullets[i]->isPlayerBullet = false;
            bulletManager->enemyBullets[i]->position = EnemyBulletPosition;
            bulletManager->enemyBullets[i]->enemyBulletDirection = dir;
            GetCorrectFrame(bulletManager->enemyBullets[i],bulletManager->enemyBullets[i]->enemyBulletDirection);
            break;
        }   
    }
}


void UpdateBullets(BulletManager_t* bulletManager){
    for (int i = 0; i < bulletManager->bulletCount; i++) 
    {
        UpdatePlayerBullet(bulletManager->playerBUllets[i]);
        
    }
    for (int i = 0; i < bulletManager->bulletCount; i++) {

        UpdateEnemyBullet(bulletManager->enemyBullets[i]);
    }
}

void DrawBulletManager(BulletManager_t* bulletManager, Texture2D spritesheet){
    for (int i = 0; i < bulletManager->bulletCount; i++) {
       if (bulletManager->playerBUllets[i]->isActive) {
            Rectangle source_bullet = (Rectangle){36, 169, bulletManager->playerBUllets[i]->bulletPixelWidth , bulletManager->playerBUllets[i]->bulletPixelHeight };
            Rectangle dest_bullet = (Rectangle){bulletManager->playerBUllets[i]->position.x,bulletManager->playerBUllets[0]->position.y, bulletManager->playerBUllets[i]->bulletPixelWidth*0.5f,bulletManager->playerBUllets[i]->bulletPixelHeight*0.5f};  //(float)GetScreenWidth(), (float)GetScreenHeight()
            Vector2 orig_bullet = (Vector2){0};

            DrawTexturePro(spritesheet, source_bullet, dest_bullet, orig_bullet, 0, WHITE);
       }
       if (bulletManager->enemyBullets[i]->isActive) {
            Rectangle source_bullet = (Rectangle){((bulletManager->enemyBullets[i]->bulletPixelWidth  ) * bulletManager->enemyBullets[i]->correctFrame), 235, bulletManager->enemyBullets[i]->bulletPixelWidth, bulletManager->enemyBullets[i]->bulletPixelHeight};
            Rectangle dest_bullet = (Rectangle){bulletManager->enemyBullets[i]->position.x,bulletManager->enemyBullets[i]->position.y, bulletManager->enemyBullets[i]->bulletPixelWidth*0.5f,bulletManager->enemyBullets[i]->bulletPixelHeight*0.5f};  //(float)GetScreenWidth(), (float)GetScreenHeight()
            Vector2 orig_bullet = (Vector2){0};
            DrawTexturePro(spritesheet, source_bullet, dest_bullet, orig_bullet, bulletManager->enemyBullets[i]->necessaryRotation, WHITE);
       }
    }      
}


//Free bullet manager memory and relative bullets after pressing esc to close the program
void FreeBullets(BulletManager_t* bulletManager)
{
    for (int i = 0; i < bulletManager->bulletCount; i++) 
    {
        FreeBullet(bulletManager->playerBUllets[i]);
        FreeBullet(bulletManager->enemyBullets[i]);
    }
    free(bulletManager);
}

