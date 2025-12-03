#include "Enemy.h"

enemySprite_t* enemySprite_new(BulletManager_t* bulletManager,UIScreen_t* UI_Screen){
    enemySprite_t* enemy = calloc(1, sizeof(enemySprite_t)); //Allocate one enemy into the memory
    enemy->bulletManagerRef = bulletManager; //Reference needed for shoot function
    enemy->UI_ScreenRef = UI_Screen; //Reference needed to modify score after death

    enemy->position.x = 100.0f;
    enemy->position.y = 100.0f;
    enemy->screenWidth = GetScreenWidth();
    enemy->screenHeight = GetScreenHeight();
    enemy->isActive = false;

    const char* app_dir = GetApplicationDirectory();
    TraceLog(LOG_INFO, "Bin directory: %s", app_dir);
    ChangeDirectory(app_dir);
    enemy->explosionSound = LoadSound("resources/assets/audio/snd_explosion1.wav");

    enemy->CorrectSpriteFrame = 1; //Used to determine the correct frame to use based on the direction of the enemy

    //Offset needed to locate the enemy in the atlas
    enemy->enemyPixelWidth = 33;
    enemy->enemyPixelHeight = 33;

    enemy->time = 2.0f; //time to shoot
    enemy->canShoot = false;
    enemy->isDead = false;
    enemy->explosionTimer = 0.2f; //time before the next explosion frame

    enemy->speed = 3.0f;
    enemy->dir = (Vector2){0, 0};
    return enemy;
}

void UpdateEnemy(enemySprite_t* enemySprite)
{
    float delta_time = GetFrameTime();
    //if the enemy is dead, the explosion takes over and it starts being updated to its correct frame
    if(enemySprite->isDead)
    {
        enemySprite->explosionTimer -= delta_time;
        if(enemySprite->explosionTimer<=0)
        {
            enemySprite->explosionTimer = 0.2f;
            enemySprite->CorrectSpriteFrame++;
            if(enemySprite->CorrectSpriteFrame == 5)
            {
                //When all is over the enemy is no longer used by the program for the time being
                enemySprite->isDead = false;
            }
        }
    }
    //If the enemy is alive he is updated
    else if(enemySprite->isActive)
    {
        enemySprite->time += delta_time;

        //If he can shoots he do so and than resets his ability to shoot
        if (enemySprite->canShoot == true) 
        {
            enemySprite->canShoot = false;
            ActivateEnemyBullet(enemySprite->bulletManagerRef, enemySprite->position,enemySprite->dir);
        }
        //If enough time passes the enemy is able to shoot again and changes direction
        if (enemySprite->time >= 2.0f) 
        {
            enemySprite->canShoot = true;
            enemySprite->time = 0;
            enemySprite->dir = GetRandomDirection(enemySprite);
        }

        //Enemy movement and relative out of bound checks
        enemySprite->position.x += enemySprite->dir.x * enemySprite->speed;
        enemySprite->position.y += enemySprite->dir.y * enemySprite->speed;
        if (enemySprite->position.x < 0)
        {
            enemySprite->position.x = 5;
            enemySprite->dir.x *= -1;
            enemySprite->dir.y = 0;
            enemySprite->CorrectSpriteFrame = 2;
        } 
        if (enemySprite->position.x > GetScreenWidth() - (enemySprite->enemyPixelWidth))
        {
            enemySprite->position.x = (GetScreenWidth() - (enemySprite->enemyPixelWidth*2)) * enemySprite->dir.x;
            enemySprite->dir.x *= -1;
            enemySprite->dir.y = 0;
            enemySprite->CorrectSpriteFrame = 6;

        } 
        if (enemySprite->position.y < 0)
        {

            enemySprite->dir.y *= -1;
            enemySprite->dir.x = 0;
            enemySprite->CorrectSpriteFrame = 0;
            enemySprite->position.y = 5 * enemySprite->dir.y;
        }
        if (enemySprite->position.y + enemySprite->enemyPixelHeight > GetScreenHeight() - enemySprite->UI_ScreenRef->height)
        {
            enemySprite->isActive = false;
        } 
    }
}

void EnemyOnCollision(enemySprite_t* enemySprite, char type)
{
    //Different type of collision do certain thing differently from one another
    PlaySound(enemySprite->explosionSound);
    switch (type)
    {
        case 'P':
            enemySprite->isActive = false;
            enemySprite->isDead = true;
            break;
        case 'B':
            enemySprite->CorrectSpriteFrame = 0;
            enemySprite->isDead = true;
            enemySprite->isActive = false;
            break;
    }
    //Update the score
    enemySprite->UI_ScreenRef->score += 10;
}

Vector2 GetRandomDirection(enemySprite_t* enemySprite) 
{
    //Based on a random direction the enemy gets the correct frame to use and changes his direction to match the correct frame
    enemySprite->CorrectSpriteFrame = GetRandomValue(0, 4);
    
    switch (enemySprite->CorrectSpriteFrame) {
        case 0: return (Vector2){ 0, 1 };
        case 1: return (Vector2){ 1, 1 };
        case 2: return (Vector2){ 1, 0 };
        case 3: 
            enemySprite->CorrectSpriteFrame = 6;
            return (Vector2){ -1, 0 };
        case 4: 
            enemySprite->CorrectSpriteFrame = 7;
            return (Vector2){ -1, 1 };
    }
    return (Vector2){0, 0};

}

//Free the memory occupied by the enemy at the end of program and set all variables to their default value
void FreeEnemy(enemySprite_t* enemySprite)
{
    enemySprite->bulletManagerRef = NULL;
    enemySprite->enemyPixelWidth = 0;
    enemySprite->enemyPixelHeight = 0;
    enemySprite->position = (Vector2){0,0};
    enemySprite->screenHeight = 0;
    enemySprite->screenWidth = 0;
    enemySprite->canShoot = false;
    enemySprite->speed = 0;
    UnloadSound(enemySprite->explosionSound);
    free(enemySprite);
}