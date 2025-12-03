#include "Player.h"
#include "BulletManager.h"

playerSprite_t* playerSprite_new(BulletManager_t* bulletManager,UIScreen_t* UI_Screen){
    playerSprite_t* player = calloc(1, sizeof(playerSprite_t)); //Allocation of a player in memory
    player->hp = 3;
    player->UI_ScreenRef = UI_Screen;

    player->screenWidth = GetScreenWidth();
    player->screenHeight = GetScreenHeight();

    //Spawn location
    player->position.x = 400;
    player->position.y = player->screenHeight-100; 

    player->bulletManagerRef = bulletManager;

    player->nextFrameTimer = 1.0f; //animation for the player
    player->playerPixelWidth = 60;
    player->playerPixelHeight = 60;
    player->currentFrame = 0;
    player->speed = 15.0f;
    //invincibility after getting hit
    player->invisibilyFrames = 120.0f;
    player->isHit = false;

    player->shootCooldown = 0.0f;
    return player;
}

void UpdatePlayer(playerSprite_t* playerSprite)
{
    //If he is hit, the player is unable to move for a short moment but is also invincible
    if(playerSprite->isHit)
    {
        playerSprite->invisibilyFrames -= GetFrameTime();
        if(playerSprite->invisibilyFrames > 0)
        {
            return;
        }
        playerSprite->invisibilyFrames = 120.0f;
        playerSprite->isHit = false;
    }
    //else the update checks for his animation, movement, out of bounds, and shoot cooldown
    else
    {
        //Animation
        playerSprite->nextFrameTimer -= GetFrameTime();
        if(playerSprite->nextFrameTimer <= 0)
        {
            playerSprite->nextFrameTimer = 1.0f;
            playerSprite->currentFrame++;
            if(playerSprite->currentFrame == 3)
            {
                playerSprite->currentFrame = 0;
            }
        }
        //Movement
        if (IsKeyDown(KEY_RIGHT)) playerSprite->position.x += playerSprite->speed;
        if (IsKeyDown(KEY_LEFT)) playerSprite->position.x -= playerSprite->speed;
        if (IsKeyDown(KEY_UP)) playerSprite->position.y -= playerSprite->speed;
        if (IsKeyDown(KEY_DOWN)) playerSprite->position.y += playerSprite->speed;
        //Out of bounds
        if (playerSprite->position.x < 0) playerSprite->position.x = 0;
        if (playerSprite->position.x > GetScreenWidth() - 50) playerSprite->position.x = GetScreenWidth() - 50;
        if (playerSprite->position.y < 0) playerSprite->position.y = 0;
        if (playerSprite->position.y + playerSprite->playerPixelHeight > GetScreenHeight() - playerSprite->UI_ScreenRef->height) playerSprite->position.y = GetScreenHeight() - playerSprite->UI_ScreenRef->height - 50;
        //Shoot
        playerSprite->shootCooldown -= GetFrameTime();
        if (IsKeyDown(KEY_SPACE) && playerSprite->shootCooldown<=0)
        {
            playerSprite->shootCooldown = 2.0f;
            ActivatePlayerBullet(playerSprite->bulletManagerRef, playerSprite->position);
        }
    }
}

void DrawPlayer(playerSprite_t* playerSprite,Texture2D spritesheet)
{
    Rectangle source_player = (Rectangle){301, 103 + (playerSprite[0].playerPixelHeight*playerSprite->currentFrame+10), playerSprite[0].playerPixelWidth, playerSprite[0].playerPixelHeight};
    Rectangle dest_player = (Rectangle){playerSprite[0].position.x,playerSprite[0].position.y, playerSprite[0].playerPixelWidth*0.5f,playerSprite[0].playerPixelHeight*0.5f};  //(float)GetScreenWidth(), (float)GetScreenHeight()
    Vector2 orig_player = (Vector2){0};

    DrawTexturePro(spritesheet, source_player, dest_player, orig_player ,0, WHITE);
}

//removes a life from the player and the ui as well
void PlayerOnCollision(playerSprite_t* playerSprite)
{
    playerSprite->hp--;
    playerSprite->UI_ScreenRef->playerHP--;
    playerSprite->isHit = true;
    if(playerSprite->hp == 0){
        CloseWindow();
    }
}

//Free the memory occupied by the player at the end of program and set all variables to their default value
void FreePlayer(playerSprite_t* playerSprite)
{
    playerSprite->bulletManagerRef = NULL;
    playerSprite->playerPixelHeight = 0;
    playerSprite->playerPixelWidth = 0;
    playerSprite->position = (Vector2){0,0};
    playerSprite->screenHeight = 0;
    playerSprite->screenWidth = 0;
    playerSprite->shootCooldown = 0;
    playerSprite->speed = 0;
    free(playerSprite);
}

