#ifndef H_COMPONENT
#define H_COMPONENT

#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    TILE_TOP_LEFT_CORNER,
    TILE_TOP_CENTER,
    TILE_TOP_RIGHT_CORNER,
    TILE_TOP_LEFT_EDGE,
    TILE_TOP_RIGHT_EDGE,
    TILE_SIDE_LEFT,
    TILE_CENTER,
    TILE_SIDE_RIGHT,
    TILE_BOTTOM_LEFT_EDGE,
    TILE_BOTTOM_RIGHT_EDGE,
    TILE_BOTTOM_LEFT_CORNER,
    TILE_BOTTOM_CENTER,
    TILE_BOTTOM_RIGHT_CORNER,
    NULLA,
    NULLB
} TileID;

typedef struct 
{
    Vector2 position;
    float rotation;
    float scale;
} TransformComponent;

typedef struct 
{
    uint32_t maxHealth;
    uint32_t currentHealth;
} HealthComponent;

typedef struct 
{
    Texture2D texture;
    Vector2 sheetSize;
    Color colorTint;
    Vector2 currentFrame;
    uint32_t startFrame;
    uint32_t endFrame;
    bool isFlipped;
    float z;
} DrawComponent;

typedef struct 
{
    Texture2D tileset;
    uint32_t tileSize;
    Vector2 tileIndex[13];
    Rectangle *tileRects;

} TileComponent;

#endif