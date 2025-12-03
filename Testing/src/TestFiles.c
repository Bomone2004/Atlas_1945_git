#define CLOVE_SUITE_NAME MainTest
#include "clove-unit.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "seaSprite.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "seaSpriteManager.h"
#include "raylib.h"


CLOVE_TEST(CreateSeaSprite)
{
    seaSprite_t* newSprite = seaSprite_new();
    newSprite->position = (Vector2){2,2};
    newSprite->AtlasPosition = (Vector2){2,2};
    newSprite->AtlasOffset = (Vector2){2,2};

    CLOVE_SIZET_EQ(2, newSprite->position.x);
    CLOVE_SIZET_EQ(2, newSprite->position.y);
    
    CLOVE_SIZET_EQ(0, newSprite->AtlasPosition.x);
    CLOVE_SIZET_EQ(0, newSprite->AtlasPosition.y);

    CLOVE_SIZET_EQ(0, newSprite->AtlasOffset.x);
    CLOVE_SIZET_EQ(0, newSprite->AtlasOffset.y);
}

CLOVE_TEST(UpdateSeaSprite)
{
    seaSprite_t* newSprite = seaSprite_new();
    newSprite->position = (Vector2){2,2};
    newSprite->AtlasPosition = (Vector2){2,2};
    newSprite->AtlasOffset = (Vector2){2,2};

    newSprite->position.y += 2;
    CLOVE_SIZET_EQ(2, newSprite->position.y);
}

CLOVE_TEST(CreateSeaSpriteManager)
{
    seaSpriteManager_t* newSpriteManager = seaSprite_Manager_new(640,420);
    CLOVE_SIZET_EQ(0, newSpriteManager->next_Island_Timer);
    CLOVE_SIZET_EQ(30, newSpriteManager->seaPixelWidth);
    CLOVE_SIZET_EQ(30, newSpriteManager->seaPixelHeight);
    CLOVE_SIZET_EQ(420, newSpriteManager->screenHeight + newSpriteManager->seaPixelHeight * 10);
    CLOVE_SIZET_EQ(640, newSpriteManager->screenWidth);
    CLOVE_SIZET_EQ(newSpriteManager->seaTilesX, newSpriteManager->screenWidth / newSpriteManager->seaPixelWidth);
    CLOVE_SIZET_EQ(newSpriteManager->seaTilesY, newSpriteManager->screenHeight / newSpriteManager->seaPixelHeight);
    CLOVE_SIZET_EQ(newSpriteManager->count, newSpriteManager->seaTilesX * newSpriteManager->seaTilesY);
    CLOVE_SIZET_EQ(newSpriteManager->index, -20);
    CLOVE_IS_TRUE(!newSpriteManager->isFirst);
}

CLOVE_TEST(AddOneItemToSeaSpriteManager)
{
    seaSpriteManager_t* newSpriteManager = seaSprite_Manager_new(640,420);
    seaSprite_t* newSprite = seaSprite_new();
    newSprite->position = (Vector2){2,2};
    newSpriteManager->seaSprites[0] = newSprite;
    CLOVE_SIZET_EQ(2, newSpriteManager->seaSprites[0]->position.x);
    CLOVE_SIZET_EQ(2, newSpriteManager->seaSprites[0]->position.y);
}

CLOVE_TEST(AddTwoItemToSeaSpriteManager)
{
    seaSpriteManager_t* newSpriteManager = seaSprite_Manager_new(640,420);
    seaSprite_t* newSprite = seaSprite_new();
    newSprite->position = (Vector2){2,2};
    newSpriteManager->seaSprites[0] = newSprite;
    seaSprite_t* newSprite2 = seaSprite_new();
    newSprite2->position = (Vector2){4,4};
    newSpriteManager->seaSprites[1] = newSprite2;
    CLOVE_SIZET_EQ(2, newSpriteManager->seaSprites[0]->position.x);
    CLOVE_SIZET_EQ(2, newSpriteManager->seaSprites[0]->position.y);
    CLOVE_SIZET_EQ(4, newSpriteManager->seaSprites[1]->position.x);
    CLOVE_SIZET_EQ(4, newSpriteManager->seaSprites[1]->position.y);
}

CLOVE_TEST(RemoveOneItemToSeaSpriteManager)
{
    seaSpriteManager_t* newSpriteManager = seaSprite_Manager_new(640,420);
    seaSprite_t* newSprite = seaSprite_new();
    newSprite->position = (Vector2){2,2};
    newSpriteManager->seaSprites[0] = newSprite;
    CLOVE_NULL(newSpriteManager->seaSprites);
    newSpriteManager->seaSprites[0] = NULL;
    CLOVE_NULL(newSpriteManager->seaSprites);
}

CLOVE_TEST(CreateEnemy)
{
    enemySprite_t* newEnemy = enemySprite_new(NULL,NULL);
    CLOVE_SIZET_EQ(100, newEnemy->position.x);
    CLOVE_SIZET_EQ(100, newEnemy->position.y);
    CLOVE_SIZET_EQ(GetScreenHeight(), newEnemy->screenHeight);
    CLOVE_SIZET_EQ(GetScreenWidth(), newEnemy->screenWidth);
    CLOVE_IS_TRUE(!newEnemy->isActive);
    CLOVE_SIZET_EQ(1, newEnemy->CorrectSpriteFrame);
    CLOVE_SIZET_EQ(33, newEnemy->enemyPixelWidth);
    CLOVE_SIZET_EQ(33, newEnemy->enemyPixelHeight);
    CLOVE_SIZET_EQ(2.0f, newEnemy->time);
    CLOVE_IS_TRUE(!newEnemy->canShoot);
    CLOVE_IS_TRUE(!newEnemy->isDead);
    CLOVE_SIZET_EQ(3, newEnemy->speed);
    CLOVE_SIZET_EQ(0, newEnemy->dir.x);
    CLOVE_SIZET_EQ(0, newEnemy->dir.y);
}

CLOVE_TEST(UpdateEnemy)
{
    enemySprite_t* newEnemy = enemySprite_new(NULL,NULL);
    newEnemy->position.x += 2;
    newEnemy->position.y += 2;
    CLOVE_SIZET_EQ(102, newEnemy->position.x);
    CLOVE_SIZET_EQ(102, newEnemy->position.y);
    newEnemy->time = 5.0f;
    CLOVE_SIZET_EQ(5.0f, newEnemy->time);
    newEnemy->CorrectSpriteFrame = 2;
    CLOVE_SIZET_EQ(2, newEnemy->CorrectSpriteFrame);
    newEnemy->dir = (Vector2){2,2};
    CLOVE_SIZET_EQ(2, newEnemy->dir.x);
    CLOVE_SIZET_EQ(2, newEnemy->dir.y);
}

CLOVE_TEST(CreateEnemyManager)
{
    EnemyContainer_t* enemyManager = EnemyContainer_new(NULL,NULL);
    CLOVE_SIZET_EQ(5, enemyManager->enemyCount);
    CLOVE_SIZET_EQ(0, enemyManager->time = 0);
    CLOVE_NULL(enemyManager->enemies);
}

CLOVE_TEST(AddOneItemToEnemyManager)
{
    EnemyContainer_t* enemyManager = EnemyContainer_new(NULL,NULL);
    enemySprite_t* newEnemy = enemySprite_new(NULL,NULL);
    newEnemy->position = (Vector2){2,2};
    enemyManager->enemies[0] = newEnemy;
    CLOVE_SIZET_EQ(2, enemyManager->enemies[0]->position.x);
    CLOVE_SIZET_EQ(2, enemyManager->enemies[0]->position.y);
}

CLOVE_TEST(AddTwoItemToEnemyManager)
{
    EnemyContainer_t* enemyManager = EnemyContainer_new(NULL,NULL);
    enemySprite_t* newEnemy = enemySprite_new(NULL,NULL);
    newEnemy->position = (Vector2){2,2};
    enemyManager->enemies[0] = newEnemy;
    enemySprite_t* newEnemy1 = enemySprite_new(NULL,NULL);
    newEnemy1->position = (Vector2){4,4};
    enemyManager->enemies[0] = newEnemy1;
    CLOVE_SIZET_EQ(2, enemyManager->enemies[0]->position.x);
    CLOVE_SIZET_EQ(2, enemyManager->enemies[0]->position.y);
    CLOVE_SIZET_EQ(4, enemyManager->enemies[0]->position.x);
    CLOVE_SIZET_EQ(4, enemyManager->enemies[0]->position.y);
}

CLOVE_TEST(RemoveOneItemToEnemyManager)
{
    EnemyContainer_t* enemyManager = EnemyContainer_new(NULL,NULL);
    enemySprite_t* newEnemy = enemySprite_new(NULL,NULL);
    newEnemy->position = (Vector2){2,2};
    enemyManager->enemies[0] = newEnemy;
    CLOVE_NULL(enemyManager->enemies);
    enemyManager->enemies[0] = NULL;
    CLOVE_NULL(enemyManager->enemies);
}

CLOVE_TEST(CreatePlayer)
{
    playerSprite_t* player = playerSprite_new(NULL,NULL);
    CLOVE_SIZET_EQ(3,player->hp);
    CLOVE_SIZET_EQ(GetScreenHeight(),player->screenHeight);
    CLOVE_SIZET_EQ(GetScreenWidth(),player->screenWidth);
    CLOVE_SIZET_EQ(400,player->position.x);
    CLOVE_SIZET_EQ(GetScreenHeight()-100,player->position.y);
    CLOVE_SIZET_EQ(60,player->playerPixelWidth);
    CLOVE_SIZET_EQ(60,player->playerPixelHeight);
    CLOVE_SIZET_EQ(0,player->currentFrame);
    CLOVE_SIZET_EQ(15.0f,player->speed);
    CLOVE_SIZET_EQ(120.0f,player->invisibilyFrames);
    CLOVE_SIZET_EQ(0.0f,player->shootCooldown);
    CLOVE_IS_TRUE(!player->isHit);

}

CLOVE_TEST(UpdatePlayer)
{
    playerSprite_t* player = playerSprite_new(NULL,NULL);
    player->position.x += 2;
    player->position.y += 2;
    CLOVE_SIZET_EQ(400, player->position.x);
    CLOVE_SIZET_EQ(GetScreenHeight()-98, player->position.y);
    player->shootCooldown = 5.0f;
    CLOVE_SIZET_EQ(5.0f, player->shootCooldown);
}

CLOVE_TEST(CreateBullet)
{
    Bullet_t* bullet = Bullet_new();
    CLOVE_SIZET_EQ(GetScreenHeight(),bullet->screenHeight);
    CLOVE_SIZET_EQ(GetScreenWidth(),bullet->screenWidth);
    CLOVE_SIZET_EQ(0,bullet->position.x);
    CLOVE_SIZET_EQ(0,bullet->position.y);
    CLOVE_SIZET_EQ(33,bullet->bulletPixelHeight);
    CLOVE_SIZET_EQ(33,bullet->bulletPixelWidth);
    CLOVE_SIZET_EQ(0, bullet->enemyBulletDirection.x);
    CLOVE_SIZET_EQ(0, bullet->enemyBulletDirection.y);
    CLOVE_SIZET_EQ(10, bullet->speed);
    CLOVE_SIZET_EQ(0, bullet->correctFrame);
    CLOVE_SIZET_EQ(0, bullet->necessaryRotation);
}

CLOVE_TEST(UpdateBullet)
{
    Bullet_t* bullet = Bullet_new();
    bullet->position.x += 2;
    bullet->position.y += 2;
    CLOVE_SIZET_EQ(2, bullet->position.x);
    CLOVE_SIZET_EQ(2, bullet->position.y);
}


CLOVE_TEST(CreateBulletManager)
{
    BulletManager_t* bulletManager = BulletManager_new();
    CLOVE_SIZET_EQ(25, bulletManager->bulletCount);
    CLOVE_NULL(bulletManager->playerBUllets);
    CLOVE_NULL(bulletManager->enemyBullets);
}

CLOVE_TEST(AddOneItemToBulletManager)
{
    BulletManager_t* bulletManager = BulletManager_new();
    Bullet_t* bullet = Bullet_new();
    bullet->position = (Vector2){2,2};
    bulletManager->playerBUllets[0] = bullet;
    bulletManager->enemyBullets[0] = bullet;
    CLOVE_SIZET_EQ(2,bulletManager->playerBUllets[0]->position.x);
    CLOVE_SIZET_EQ(2,bulletManager->playerBUllets[0]->position.x);
    CLOVE_SIZET_EQ(2,bulletManager->enemyBullets[0]->position.x);
    CLOVE_SIZET_EQ(2,bulletManager->enemyBullets[0]->position.x);

}

CLOVE_TEST(AddTwoItemToBulletManager)
{
    BulletManager_t* bulletManager = BulletManager_new();
    Bullet_t* bullet = Bullet_new();
    bullet->position = (Vector2){2,2};
    bulletManager->playerBUllets[0] = bullet;
    bulletManager->enemyBullets[0] = bullet;
    Bullet_t* bullet1 = Bullet_new();
    bullet1->position = (Vector2){4,4};
    bulletManager->playerBUllets[0] = bullet1;
    bulletManager->enemyBullets[0] = bullet1;
    CLOVE_SIZET_EQ(2,bulletManager->playerBUllets[0]->position.x);
    CLOVE_SIZET_EQ(2,bulletManager->playerBUllets[0]->position.x);
    CLOVE_SIZET_EQ(2,bulletManager->enemyBullets[0]->position.x);
    CLOVE_SIZET_EQ(2,bulletManager->enemyBullets[0]->position.x);
    CLOVE_SIZET_EQ(4,bulletManager->playerBUllets[0]->position.x);
    CLOVE_SIZET_EQ(4,bulletManager->playerBUllets[0]->position.x);
    CLOVE_SIZET_EQ(4,bulletManager->enemyBullets[0]->position.x);
    CLOVE_SIZET_EQ(4,bulletManager->enemyBullets[0]->position.x);
}

CLOVE_TEST(RemoveOneItemToBulletManager)
{
    BulletManager_t* bulletManager = BulletManager_new();
    Bullet_t* bullet = Bullet_new();
    bullet->position = (Vector2){2,2};
    bulletManager->playerBUllets[0] = bullet;
    bulletManager->enemyBullets[0] = bullet;
    CLOVE_NULL(bulletManager->playerBUllets);
    CLOVE_NULL(bulletManager->enemyBullets);
    bulletManager->playerBUllets[0] = NULL;
    bulletManager->enemyBullets[0] = NULL;
    CLOVE_NULL(bulletManager->playerBUllets);
    CLOVE_NULL(bulletManager->enemyBullets);
}

CLOVE_TEST(CreateCollisionManager)
{
    playerSprite_t* player = playerSprite_new(NULL,NULL);
    EnemyContainer_t* enemies = EnemyContainer_new(NULL,NULL);
    BulletManager_t* bulletManager = BulletManager_new();
    Collision_Manager_t* collisionManager = Collision_manager_new(player,enemies,bulletManager);
    CLOVE_NULL(collisionManager->bulletsReferences);
    CLOVE_NULL(collisionManager->playerReference);
    CLOVE_NULL(collisionManager->enemiesReferences->enemies);
}

CLOVE_TEST(CreateUIManager)
{
    UIScreen_t* UIScreen = UIScreen_new(640,480);
    CLOVE_SIZET_EQ(0,UIScreen->score);
    CLOVE_SIZET_EQ(3,UIScreen->playerHP);
    CLOVE_SIZET_EQ(640,UIScreen->width);
    CLOVE_SIZET_EQ(100,UIScreen->height);

}

CLOVE_TEST(UpdateUIManager)
{
    UIScreen_t* UIScreen = UIScreen_new(640,480);
    UIScreen->playerHP--;
    UIScreen->score+=100;
    CLOVE_SIZET_EQ(2,UIScreen->playerHP);
    CLOVE_SIZET_EQ(100,UIScreen->score);

}

