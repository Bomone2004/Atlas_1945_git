#include "CollisionManager.h"

Collision_Manager_t* Collision_manager_new(playerSprite_t* player,EnemyContainer_t* enemies,BulletManager_t* bullets) 
{
    Collision_Manager_t* collisionManager= calloc(1, sizeof(Collision_Manager_t));
    collisionManager->playerReference = player;
    collisionManager->enemiesReferences = enemies;
    collisionManager->bulletsReferences = bullets;

    return collisionManager;

}

void CheckCollisions(Collision_Manager_t* collisionManager)
{
    //Get player and check his collision box
    playerSprite_t* player = collisionManager->playerReference;
    Rectangle playerColl = (Rectangle){player->position.x,player->position.y,player->playerPixelWidth,player->playerPixelHeight};

    //Check if is Invisible Times
    if(!player->isHit)
    {
        for(int i = 0; i < collisionManager->enemiesReferences->enemyCount; i++)
        {
            //Get relative enemy and his collision box
            enemySprite_t* enemy = collisionManager->enemiesReferences->enemies[i];
            if(enemy->isActive == true)
            {
                Rectangle enemyColl = (Rectangle){enemy->position.x,enemy->position.y,enemy->enemyPixelWidth,enemy->enemyPixelHeight};
                //If they are colliding both collision function are called
                if(CheckCollisionRecs(playerColl,enemyColl))
                {
                    EnemyOnCollision(enemy,'P');
                    PlayerOnCollision(player);
                }
            }
        }
    }
    for(int i = 0; i < collisionManager->enemiesReferences->enemyCount; i++)
    {
        enemySprite_t* enemy = collisionManager->enemiesReferences->enemies[i];
        Rectangle enemyColl = (Rectangle){enemy->position.x,enemy->position.y,enemy->enemyPixelWidth,enemy->enemyPixelHeight};
        for(int j = 0; j < collisionManager->bulletsReferences->bulletCount; j++)
        {
            //get player bullet and his collision box
            Bullet_t* playerbullet = collisionManager->bulletsReferences->playerBUllets[j];
            Rectangle playerbulletColl = (Rectangle){playerbullet->position.x,playerbullet->position.y,playerbullet->bulletPixelWidth,playerbullet->bulletPixelHeight};
            if(playerbullet->isPlayerBullet == true && playerbullet->isActive == true)
            {
                //If enemy and player bullet collide both collision funcion are called
                if(CheckCollisionRecs(playerbulletColl,enemyColl))
                {
                    EnemyOnCollision(enemy,'B');
                    BulletOnCollision(playerbullet,'E');
                }
            }

            //Check EnemyBullet Collision to player
            if(!player->isHit)
            {
                //Same for the player, expect if the is in his invisibility frames after getting hit
                Bullet_t* enemybullet = collisionManager->bulletsReferences->enemyBullets[i];
                Rectangle enemybulletColl = (Rectangle){enemybullet->position.x,enemybullet->position.y,enemybullet->bulletPixelWidth,enemybullet->bulletPixelHeight};

                if (enemybullet->isPlayerBullet == false && enemybullet->isActive == true)
                {
                    if(CheckCollisionRecs(enemybulletColl,playerColl))
                    {
                        PlayerOnCollision(player);
                        BulletOnCollision(enemybullet,'E');
                    }
                }
            }
            
        }
    }

    //Collision of bullet 
    for(int i = 0; i < collisionManager->bulletsReferences->bulletCount; i++)
    {
        Bullet_t* playerbullet = collisionManager->bulletsReferences->playerBUllets[i];
        Rectangle playerbulletColl = (Rectangle){playerbullet->position.x,playerbullet->position.y,playerbullet->bulletPixelWidth,playerbullet->bulletPixelHeight};
        for(int i = 0; i < collisionManager->bulletsReferences->bulletCount; i++)
        {
            Bullet_t* enemybullet = collisionManager->bulletsReferences->enemyBullets[i];
            Rectangle enemybulletColl = (Rectangle){enemybullet->position.x,enemybullet->position.y,enemybullet->bulletPixelWidth,enemybullet->bulletPixelHeight};
            if(CheckCollisionRecs(enemybulletColl,playerColl))
            {
                BulletOnCollision(playerbullet,'E');
                BulletOnCollision(enemybullet,'E');
            }
        }
    }
}

//Free memory used by collision manager and set all variables to their default value
void FreeCollisionManager(Collision_Manager_t* collision_manager)
{
    collision_manager->playerReference = NULL;
    collision_manager->enemiesReferences = NULL;
    collision_manager->bulletsReferences = NULL;
    free(collision_manager);
}