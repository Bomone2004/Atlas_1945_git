#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
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



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

#define MAX_SEA_SPRITES 2500

int main(void)
{   
    InitAudioDevice();
    static int screenWidth = 1920;
    static int screenHeight = 1080;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    //Inizialization
    UIScreen_t* UI_Screen = UIScreen_new(screenWidth,screenHeight);

    seaSpriteManager_t* seaSpriteManager = seaSprite_Manager_new(screenWidth,screenHeight);
    
    BulletManager_t* bulletManager = BulletManager_new();

    playerSprite_t* playerSprite = playerSprite_new(bulletManager,UI_Screen);

    EnemyContainer_t* enemyContainer = EnemyContainer_new(bulletManager,UI_Screen);

    Collision_Manager_t* collisionManager = Collision_manager_new(playerSprite,enemyContainer,bulletManager);

    const char* app_dir = GetApplicationDirectory();
    TraceLog(LOG_INFO, "Bin directory: %s", app_dir);
    ChangeDirectory(app_dir);


    Music music = LoadMusicStream("resources/assets/audio/background.mp3");
    music.looping = true;
    PlayMusicStream(music);

    Texture2D spritesheet = LoadTexture("resources/assets/1945_atlas.png");
    if (spritesheet.id == 0) {
        TraceLog(LOG_ERROR, "Error loading atlas!");
        exit(-1);
    }


    char title[100];
    while (!WindowShouldClose()) 
    {   
        float delta_time = GetFrameTime();
        int fps = GetFPS();
        sprintf(title, "Delta: %.4f - FPS: %d", delta_time, fps);
        SetWindowTitle(title);

        static float time = 0;
        time += delta_time;
        unsigned char r = (unsigned char) ((sin(time) * 0.5f + 0.5f) * 255);

        //Update
        UpdateSeaSpriteManager(seaSpriteManager, delta_time);

        UpdatePlayer(playerSprite);

        UpdateEnemiesManager(enemyContainer);

        UpdateBullets(bulletManager);
       
        CheckCollisions(collisionManager);

        UpdateMusicStream(music);

        BeginDrawing();

            ClearBackground(BLACK);

            //Draw
            DrawSeaSpriteManager(seaSpriteManager, spritesheet);

            DrawPlayer(playerSprite,spritesheet);

            DrawsEnemiesManager(enemyContainer, spritesheet);

            DrawBulletManager(bulletManager, spritesheet);

            DrawUI(UI_Screen,spritesheet);
        
        EndDrawing();
    }

    //Clear
    UnloadMusicStream(music);
    UnloadTexture(spritesheet);
    FreeSeaSpriteManager(seaSpriteManager);
    FreeEnemyManager(enemyContainer);
    FreePlayer(playerSprite);
    FreeBullets(bulletManager);
    FreeCollisionManager(collisionManager);
    FreeUI(UI_Screen);
    CloseWindow();

    return 0;
}