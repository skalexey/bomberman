//
//  LevelMap.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 27/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef LevelMap_h
#define LevelMap_h

#include <vector>
#include "SDL.h"
#include "LevelMapCollider.h"

const float block_size = 20.0f;

enum FieldBlock
{
    BLOCK_NONE,
    BLOCK_BRICK,
    BLOCK_CONCRETE,
    BLOCK_KEY,
    BLOCK_DOOR
};

enum CheckCollisionResult
{
    COLLISION_NONE,
    COLLISION_XY,
    COLLISION_X,
    COLLISION_Y
};

class LevelMap
{
public:
    LevelMap();
    void render(SDL_Renderer *renderer);
    FieldBlock getBlockAtPoint(const Vector2& point) const;
    const LevelMapCollider& getCollider() const;
    typedef std::vector<std::vector<FieldBlock> > TLevelMapField;
    const TLevelMapField& getField() const;
private:
    void generate();
    TLevelMapField _field;
    int _level_size_x;
    int _level_size_y;
    LevelMapCollider _collider;
};

#endif /* LevelMap_h */
