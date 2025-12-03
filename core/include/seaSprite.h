#ifndef SEASPRITE_C
#define SEASPRITE_C
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


typedef struct seaSprite_t
{
    Vector2 position;     
    
    Vector2 AtlasPosition;
    Vector2 AtlasOffset;

}seaSprite_t;

seaSprite_t* seaSprite_new();
void FreeSeaSprite(seaSprite_t* seaSprite);


#endif