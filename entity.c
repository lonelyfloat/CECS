#include "entity.h"
#include <stdint.h>
#include <malloc.h>
#include <raymath.h>

void InitData(EntityData *data, uint32_t initEntities, uint32_t totalComponents)
{
    data->components = malloc(initEntities * sizeof(Component*));
    for (int i = 0; i < initEntities; ++i)
    {
        data->components[i] = malloc(totalComponents * sizeof(Component));
    }
    
}
void AttachComponent(EntityData *data, uint32_t ID, Component component)
{
    data->components[ID][component.type] = component;
    data->totalComponents[component.type]++;
}

void PlayAnimation(EntityData *data, uint32_t ID, uint32_t startFrame, uint32_t endFrame)
{
    data->components[ID][COMPONENT_DRAW].data.draw.startFrame = startFrame;
    data->components[ID][COMPONENT_DRAW].data.draw.endFrame = endFrame;
}

void DrawEntity(EntityData *data, uint32_t ID)
{
    data->components[ID][COMPONENT_DRAW].data.draw.currentFrame.x = Clamp(data->components[ID][COMPONENT_DRAW].data.draw.currentFrame.x, data->components[ID][COMPONENT_DRAW].data.draw.startFrame, data->components[ID][COMPONENT_DRAW].data.draw.endFrame);
    data->components[ID][COMPONENT_DRAW].data.draw.currentFrame.x += 0.1;

    if(data->components[ID][COMPONENT_DRAW].data.draw.currentFrame.x >= data->components[ID][COMPONENT_DRAW].data.draw.endFrame)
    {
        data->components[ID][COMPONENT_DRAW].data.draw.currentFrame.x = data->components[ID][COMPONENT_DRAW].data.draw.startFrame;
        ++data->components[ID][COMPONENT_DRAW].data.draw.currentFrame.y;
        if(data->components[ID][COMPONENT_DRAW].data.draw.currentFrame.y >= data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.y) data->components[ID][COMPONENT_DRAW].data.draw.currentFrame.y = 0;
    }

    if(data->components[ID][COMPONENT_DRAW].data.draw.isFlipped == true)
    {
        DrawTexturePro(
        data->components[ID][COMPONENT_DRAW].data.draw.texture,
        (Rectangle){
        floor(data->components[ID][COMPONENT_DRAW].data.draw.currentFrame.x) * (data->components[ID][COMPONENT_DRAW].data.draw.texture.width / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.x),
        floor(data->components[ID][COMPONENT_DRAW].data.draw.currentFrame.y) * (data->components[ID][COMPONENT_DRAW].data.draw.texture.height / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.y), 
        floor(-(data->components[ID][COMPONENT_DRAW].data.draw.texture.width) / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.x),
        floor(data->components[ID][COMPONENT_DRAW].data.draw.texture.height) / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.y},         
        (Rectangle){
        floor(data->components[ID][COMPONENT_TRANSFORM].data.transform.position.x), 
        floor(data->components[ID][COMPONENT_TRANSFORM].data.transform.position.y),
        floor((data->components[ID][COMPONENT_DRAW].data.draw.texture.width) / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.x * data->components[ID][COMPONENT_TRANSFORM].data.transform.scale), 
        floor(data->components[ID][COMPONENT_DRAW].data.draw.texture.height) / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.y * data->components[ID][COMPONENT_TRANSFORM].data.transform.scale}, 
        (Vector2){((data->components[ID][COMPONENT_DRAW].data.draw.texture.width) / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.x) / 2,
        ((data->components[ID][COMPONENT_DRAW].data.draw.texture.height) / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.y) / 2},
        data->components[ID][COMPONENT_TRANSFORM].data.transform.rotation, 
        WHITE);
    }
    else
    {
        DrawTexturePro(
        data->components[ID][COMPONENT_DRAW].data.draw.texture,
        (Rectangle){
        floor(data->components[ID][COMPONENT_DRAW].data.draw.currentFrame.x) * (data->components[ID][COMPONENT_DRAW].data.draw.texture.width / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.x),
        floor(data->components[ID][COMPONENT_DRAW].data.draw.currentFrame.y) * (data->components[ID][COMPONENT_DRAW].data.draw.texture.height / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.y), 
        floor((data->components[ID][COMPONENT_DRAW].data.draw.texture.width) / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.x),
        floor(data->components[ID][COMPONENT_DRAW].data.draw.texture.height) / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.y},         
        (Rectangle){
        floor(data->components[ID][COMPONENT_TRANSFORM].data.transform.position.x), 
        floor(data->components[ID][COMPONENT_TRANSFORM].data.transform.position.y),
        floor((data->components[ID][COMPONENT_DRAW].data.draw.texture.width) / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.x * data->components[ID][COMPONENT_TRANSFORM].data.transform.scale), 
        floor(data->components[ID][COMPONENT_DRAW].data.draw.texture.height) / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.y * data->components[ID][COMPONENT_TRANSFORM].data.transform.scale}, 
        (Vector2){((data->components[ID][COMPONENT_DRAW].data.draw.texture.width) / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.x * data->components[ID][COMPONENT_TRANSFORM].data.transform.scale) / 2,
        ((data->components[ID][COMPONENT_DRAW].data.draw.texture.height) / data->components[ID][COMPONENT_DRAW].data.draw.sheetSize.y * data->components[ID][COMPONENT_TRANSFORM].data.transform.scale) / 2},
        data->components[ID][COMPONENT_TRANSFORM].data.transform.rotation, 
        WHITE);
    }
}

void FreeData(EntityData *data, uint32_t initEntities)
{
    for(int i = 0; i < initEntities; ++i)
    {
        free(data->components[i]);
    }
    free(data->components);

}