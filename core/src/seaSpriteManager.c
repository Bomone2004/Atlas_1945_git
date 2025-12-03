#include "seaSpriteManager.h"

seaSpriteManager_t* seaSprite_Manager_new(int screenWidth,int screenHeight){

    seaSpriteManager_t* seaSpriteManager = calloc(1, sizeof(seaSpriteManager_t)); //Allocation of a sea sprite manager in memory

    seaSpriteManager->next_Island_Timer = 0.0f; //timer before next island spawn
 
    seaSpriteManager->seaPixelWidth = 30;
    seaSpriteManager->seaPixelHeight = 30;

    seaSpriteManager->screenWidth = screenWidth;
    seaSpriteManager->screenHeight = screenHeight + (seaSpriteManager->seaPixelHeight * 10); //Height is a little bit more since it used to "mask" the island spawn

    seaSpriteManager->seaTilesX = seaSpriteManager->screenWidth / seaSpriteManager->seaPixelWidth;
    seaSpriteManager->seaTilesY = seaSpriteManager->screenHeight / seaSpriteManager->seaPixelHeight;
    
    seaSpriteManager->count = (seaSpriteManager->seaTilesX * seaSpriteManager->seaTilesY); //Count of all the sea pixels needed for the screen to be full of them
    
    seaSpriteManager->seaSprites = calloc(seaSpriteManager->count, sizeof(seaSpriteManager_t));//Allocation of n-count sea sprites in memory

    //Variables needed for island spawn
    seaSpriteManager->isFirst = true;
    seaSpriteManager->index = -20;

    return seaSpriteManager;

}

void SpawnSeaSprite(seaSpriteManager_t* seaSpriteManager){
    int counterY = -10;
    int counterX = 0;
    for(int i = 0; i < seaSpriteManager->count; i++) {
        
            counterX = i % seaSpriteManager->seaTilesX;

            seaSpriteManager->seaSprites[i]->position.x = counterX * seaSpriteManager->seaPixelWidth;
            seaSpriteManager->seaSprites[i]->position.y = counterY * seaSpriteManager->seaPixelHeight;
           

        if(i % seaSpriteManager->seaTilesX == 0){
            counterY++;
        }
    }
}

void SpawnIsland(seaSpriteManager_t* seaSpriteManager, int index){
    //If index is not changed an error occured so the function doesn't do anything
    if (index == -20){
        return;
    }
    //get a random index on the same x as the one selected before
    int RandomSpawnX = GetRandomValue(index, index + seaSpriteManager->seaTilesX-4);
    //random island
    int RandomSpawnSprite = GetRandomValue(0,2);

    //In every case 3 more sea sprites are needed since with only one the island is way too small and this cannot be fixed by using a bigger offset
    switch(RandomSpawnSprite)
    {
        case 0:
            seaSpriteManager->seaSprites[RandomSpawnX]->AtlasPosition = (Vector2){105,500};
            seaSpriteManager->seaSprites[RandomSpawnX]->AtlasOffset = (Vector2){32,32};

            seaSpriteManager->seaSprites[RandomSpawnX + 1]->AtlasPosition = (Vector2){105 + seaSpriteManager->seaPixelWidth,500};
            seaSpriteManager->seaSprites[RandomSpawnX + 1]->AtlasOffset = (Vector2){32,32};

            seaSpriteManager->seaSprites[RandomSpawnX + seaSpriteManager->seaTilesX]->AtlasPosition = (Vector2){105 ,500 + seaSpriteManager->seaPixelHeight};
            seaSpriteManager->seaSprites[RandomSpawnX + seaSpriteManager->seaTilesX]->AtlasOffset = (Vector2){32,32};

            seaSpriteManager->seaSprites[RandomSpawnX + seaSpriteManager->seaTilesX + 1]->AtlasPosition = (Vector2){105 + seaSpriteManager->seaPixelWidth,500  + seaSpriteManager->seaPixelHeight};
            seaSpriteManager->seaSprites[RandomSpawnX + seaSpriteManager->seaTilesX + 1]->AtlasOffset = (Vector2){32,32};
            break;
        case 1:
            seaSpriteManager->seaSprites[RandomSpawnX]->AtlasPosition = (Vector2){170,500};
            seaSpriteManager->seaSprites[RandomSpawnX]->AtlasOffset = (Vector2){32,32};

            seaSpriteManager->seaSprites[RandomSpawnX + 1]->AtlasPosition = (Vector2){170 + seaSpriteManager->seaPixelWidth,500};
            seaSpriteManager->seaSprites[RandomSpawnX + 1]->AtlasOffset = (Vector2){32,32};

            seaSpriteManager->seaSprites[RandomSpawnX + seaSpriteManager->seaTilesX]->AtlasPosition = (Vector2){170 ,500 + seaSpriteManager->seaPixelHeight};
            seaSpriteManager->seaSprites[RandomSpawnX + seaSpriteManager->seaTilesX]->AtlasOffset = (Vector2){32,32};

            seaSpriteManager->seaSprites[RandomSpawnX + seaSpriteManager->seaTilesX + 1]->AtlasPosition = (Vector2){170 + seaSpriteManager->seaPixelWidth,500  + seaSpriteManager->seaPixelHeight};
            seaSpriteManager->seaSprites[RandomSpawnX + seaSpriteManager->seaTilesX + 1]->AtlasOffset = (Vector2){32,32};
            break;
        case 2:
            seaSpriteManager->seaSprites[RandomSpawnX]->AtlasPosition = (Vector2){235,500};
            seaSpriteManager->seaSprites[RandomSpawnX]->AtlasOffset = (Vector2){32,32};

            seaSpriteManager->seaSprites[RandomSpawnX + 1]->AtlasPosition = (Vector2){235 + seaSpriteManager->seaPixelWidth,500};
            seaSpriteManager->seaSprites[RandomSpawnX + 1]->AtlasOffset = (Vector2){32,32};

            seaSpriteManager->seaSprites[RandomSpawnX + seaSpriteManager->seaTilesX]->AtlasPosition = (Vector2){235 ,500 + seaSpriteManager->seaPixelHeight};
            seaSpriteManager->seaSprites[RandomSpawnX + seaSpriteManager->seaTilesX]->AtlasOffset = (Vector2){32,32};

            seaSpriteManager->seaSprites[RandomSpawnX + seaSpriteManager->seaTilesX + 1]->AtlasPosition = (Vector2){235 + seaSpriteManager->seaPixelWidth,500  + seaSpriteManager->seaPixelHeight};
            seaSpriteManager->seaSprites[RandomSpawnX + seaSpriteManager->seaTilesX + 1]->AtlasOffset = (Vector2){32,32};
            break;
    }

    
    
}

void PopulateSeaSpriteManagerArray(seaSpriteManager_t* seaSpriteManager){
    for (int i = 0; i < seaSpriteManager->count; i++) {
        seaSpriteManager->seaSprites[i] = seaSprite_new();
        seaSpriteManager->seaSprites[i]->position.x = -100;
        seaSpriteManager->seaSprites[i]->position.y = -100;
    }
   
}

void DrawSeaSpriteManager(seaSpriteManager_t* seaSpriteManager, Texture2D spritesheet)
{
    for(int i = 0; i < seaSpriteManager->count; i++) 
    {
        Rectangle source = (Rectangle){seaSpriteManager->seaSprites[i]->AtlasPosition.x, seaSpriteManager->seaSprites[i]->AtlasPosition.y, seaSpriteManager->seaSprites[i]->AtlasOffset.x, seaSpriteManager->seaSprites[i]->AtlasOffset.y}; //269, 369
        Rectangle dest = (Rectangle){seaSpriteManager->seaSprites[i]->position.x , seaSpriteManager->seaSprites[i]->position.y ,
                                     seaSpriteManager->seaSprites[i]->AtlasOffset.x, seaSpriteManager->seaSprites[i]->AtlasOffset.y};  //(float)GetScreenWidth(), (float)GetScreenHeight()
                
        Vector2 orig = (Vector2){0};
        DrawTexturePro(spritesheet, source, dest, orig ,0, WHITE);
        
    }
    
}

void UpdateSeaSpriteManager(seaSpriteManager_t* seaSpriteManager, float delta_time)
{
    seaSpriteManager->isFirst = true;
    for (int i = 0 ; i < seaSpriteManager->count; i ++)
    {
        seaSpriteManager->seaSprites[i]->position.y += seaSpriteManager->seaPixelHeight * delta_time;
        //If they reach the bottom of the screen they are sent back to the very top (offscreen)
        if (seaSpriteManager->seaSprites[i]->position.y > GetScreenHeight()) 
        {
            seaSpriteManager->seaSprites[i]->position.y = -seaSpriteManager->seaPixelHeight * 10;

            seaSpriteManager->seaSprites[i]->AtlasPosition = (Vector2){269, 204};

            seaSpriteManager->seaSprites[i]->AtlasOffset = (Vector2){30,30};

            if(seaSpriteManager->isFirst)
            {
                //gets the index of the first sea sprite which is now on the upper end of the screen and is used later to determine island spawn location
                seaSpriteManager->isFirst= false;
                seaSpriteManager->index = i;
            }
        }
    }
    
    seaSpriteManager->next_Island_Timer += delta_time;
    //Next island spawn
    if (seaSpriteManager->next_Island_Timer > 7)
    {
        seaSpriteManager->next_Island_Timer = 0;
        SpawnIsland(seaSpriteManager, seaSpriteManager->index);
    }
}

//Free the memory occupied by the manager and respective sea sprites at the end of program
void FreeSeaSpriteManager(seaSpriteManager_t* seaSpriteManager){
    for(int x = 0; x < seaSpriteManager->seaTilesX; x++) {
        for (int y = -1; y <= seaSpriteManager->seaTilesY; y++) 
        {
            FreeSeaSprite(seaSpriteManager->seaSprites[(y * seaSpriteManager->seaTilesX) + x]);
        }
    }
}