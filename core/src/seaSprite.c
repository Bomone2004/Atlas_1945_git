#include "seaSprite.h"

seaSprite_t* seaSprite_new(){
    seaSprite_t* seaSprite = calloc(1, sizeof(seaSprite_t)); //Allocation of a sea sprite in memory

    seaSprite->position.x = 0;
    seaSprite->position.y = 0;

    seaSprite->AtlasPosition = (Vector2){269, 204};

    seaSprite->AtlasOffset = (Vector2){30,30};
    
    return seaSprite;
}

//Free the memory occupied by the sea_Sprite at the end of program and set all variables to their default value
void FreeSeaSprite(seaSprite_t* seaSprite)
{
    seaSprite->position = (Vector2){0,0};
    free(seaSprite);
}