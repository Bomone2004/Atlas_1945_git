#include "Bullet.h"


Bullet_t* Bullet_new()
{
    Bullet_t* bullet = calloc(1, sizeof(Bullet_t)); //Allocation in memory;
    bullet->position.x = 0.0f;
    bullet->position.y = 0.0f;
    bullet->screenWidth = GetScreenWidth();
    bullet->screenHeight = GetScreenHeight();

    //Size of Pixel in the atlas
    bullet->bulletPixelWidth = 33;  
    bullet->bulletPixelHeight = 33; 

    //Give Direction
    bullet->enemyBulletDirection = (Vector2){0, 0};

    bullet->speed = 7.0f;

    //Give Correct Bullet Frame
    bullet->correctFrame = 0;
    bullet->necessaryRotation = 0;
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

void UpdatePlayerBullet(Bullet_t* bullet)
{
    bullet->position.y -= bullet->speed;
    if(bullet->position.y <= 0)
    bullet->isActive = false;
}

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
                    bullet->correctFrame = 4; //left
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