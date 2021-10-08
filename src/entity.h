#ifndef H_ENTITY
#define H_ENTITY

#include "component.h"
#include <stdint.h>
#define MAX_ENTITIES 100
#define MAX_COMPONENTS_PER_ENTITY 10
#define TOTAL_COMPONENTS 4

typedef enum ComponentType
{
    COMPONENT_TRANSFORM,
    COMPONENT_HEALTH,
    COMPONENT_DRAW,
    COMPONENT_TILE
} ComponentType;

typedef union ComponentData
{
    TransformComponent transform;
    HealthComponent health;
    DrawComponent draw;
    TileComponent tile;
} ComponentData;

typedef struct Component
{
    ComponentType type;
    ComponentData data;
} Component;

typedef struct EntityData
{
    //Component components[MAX_ENTITIES][MAX_COMPONENTS_PER_ENTITY];
    Component **components;
    uint32_t totalComponents[TOTAL_COMPONENTS];
}   EntityData;

void InitData(EntityData *data, uint32_t initEntities, uint32_t totalComponents);
void AttachComponent(EntityData *data, uint32_t ID, Component component);

void PlayAnimation(EntityData *data, uint32_t ID, uint32_t startFrame, uint32_t endFrame);
void DrawEntity(EntityData *data, uint32_t ID);

void FreeData(EntityData *data, uint32_t initEntities);
#endif