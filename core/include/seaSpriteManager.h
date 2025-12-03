#ifndef seaSpriteManager_C
#define seaSpriteManager_C

#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "seaSprite.h"


typedef struct seaSpriteManager_t
{
    seaSprite_t** seaSprites;

    float next_Island_Timer;

    int seaPixelWidth ;
    int seaPixelHeight ;

    int screenWidth;
    int screenHeight;

    int seaTilesX ;
    int seaTilesY ; 

    int count;

    float timer;

    int index;
    bool isFirst;
    
}seaSpriteManager_t;

seaSpriteManager_t* seaSprite_Manager_new(int screenWidth,int screenHeight);

void SpawnSeaSprite(seaSpriteManager_t* seaSpriteManager);

void PopulateSeaSpriteManagerArray(seaSpriteManager_t* seaSpriteManager);

void DrawSeaSpriteManager(seaSpriteManager_t* seaSpriteManager, Texture2D spritesheet);

void UpdateSeaSpriteManager(seaSpriteManager_t* seaSpriteManager, float delta_time);

void FreeSeaSpriteManager(seaSpriteManager_t* seaSpriteManager);

void SpawnIsland(seaSpriteManager_t* seaSpriteManager, int index);

#endif