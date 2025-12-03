#ifndef COLLISION_MANAGER_C
#define COLLISION_MANAGER_C
#include "EnemyManager.h"
#include "Player.h"
#include "BulletManager.h"

typedef struct Collision_Manager_t
{
    playerSprite_t* playerReference;
    EnemyContainer_t* enemiesReferences;
    BulletManager_t* bulletsReferences;
    
    

}Collision_Manager_t;

Collision_Manager_t* Collision_manager_new(playerSprite_t* player,EnemyContainer_t* enemiesReferences,BulletManager_t* bullets);

void CheckCollisions(Collision_Manager_t* collisionManager);

void FreeCollisionManager(Collision_Manager_t* collisionManager);

#endif