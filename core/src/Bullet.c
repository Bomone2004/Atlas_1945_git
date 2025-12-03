#include "Bullet.h"


Bullet_t* Bullet_new()
{
    Bullet_t* bullet = calloc(1, sizeof(Bullet_t)); //Allocation in memory of a bullet size;
    bullet->position.x = 0.0f;
    bullet->position.y = 0.0f;
    bullet->screenWidth = GetScreenWidth();
    bullet->screenHeight = GetScreenHeight();

    bullet->bulletPixelWidth = 33; //Width of the pixel in the atlas
    bullet->bulletPixelHeight = 33;//Height of the pixel in the atlas

    bullet->enemyBulletDirection = (Vector2){0, 0};

    bullet->speed = 10.0f;
    bullet->correctFrame = 0; //Used to determine the correct frame to use when drawing the bullet based on his direction
    bullet->necessaryRotation = 0;//Since bullet looking up and down where in different places of the atlas i used this variable to simple rotate the bullet looking right either -90 degrees or 90 degrees
    return bullet;
}


void UpdateEnemyBullet(Bullet_t* bullet)
{
    bullet->position.y += (bullet->enemyBulletDirection.y * bullet->speed);
    bullet->position.x += (bullet->enemyBulletDirection.x * bullet->speed);
    //Bullet check if out of bounds
    if(bullet->position.y < 0 || bullet->position.y > GetScreenHeight())
    {
        bullet->isActive = false;
    }
    else if (bullet->position.x < 0 || bullet->position.x > GetScreenWidth())
    {
        bullet->isActive = false;
    }
}

//Player bullet is only able to go up so it has less checks
void UpdatePlayerBullet(Bullet_t* bullet)
{
    bullet->position.y -= bullet->speed;
    if(bullet->position.y <= 0)
    bullet->isActive = false;
}

//Function used to determine the correct frame to use to match the direction of the bullet
void GetCorrectFrame(Bullet_t* bullet, Vector2 dir)
{
    int currentX = dir.x;
    int currentY = dir.y;
    switch(currentX)
    {
        case -1:
            switch (currentY)
            {
                case 0:
                    bullet->correctFrame = 4; //Left
                    break;
                case 1:
                    bullet->correctFrame = 0; //Diagonal left going up
                    break;
                case -1:
                    bullet->correctFrame = 2; //Diagonal left going down
                    break;
            }
            break;
        case 0:
            switch (currentY)
            {
                case 1:
                    bullet->correctFrame = 5; //Right
                    bullet->necessaryRotation = -90; //Right rotated to look up
                    break;
                case -1:
                    bullet->correctFrame = 5;
                    bullet->necessaryRotation = 90; //Right rotated to look down
                    break;
            }
            break;
        case 1:
            switch (currentY)
            {
                case 0:
                    bullet->correctFrame = 5; //Right
                    break;
                case 1:
                    bullet->correctFrame = 1; //Diagonal right going up
                    break;
                case -1:
                    bullet->correctFrame = 3; //Diagonal right going up
                    break;
            }
            break;    
    }
}



void BulletOnCollision(Bullet_t* bullet, char type)
{
    bullet->isActive = false;
}


//Free bullet when pressing esc to quit the game  and set all variables to their default value
void FreeBullet(Bullet_t* bullet)
{
    bullet->bulletPixelHeight = 0;
    bullet->bulletPixelWidth = 0;
    bullet->enemyBulletDirection = (Vector2){0,0};
    bullet->isActive = false;
    bullet->isPlayerBullet = false;
    bullet->position = (Vector2){0,0};
    bullet->screenHeight = 0;
    bullet->screenWidth = 0;
    bullet->speed = 0;
    free(bullet);
}