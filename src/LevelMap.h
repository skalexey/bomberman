//
//  LevelMap.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 27/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef LevelMap_h
#define LevelMap_h

#include <set>
#include <vector>
#include "SDL.h"
#include "Bomb.h"
#include "BombFragment.h"

const float block_size = 20.0f;

class LevelMap;

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

#include "LevelMapCollider.h"

class LevelMapCollider;

class LevelMap
{
public:
    LevelMap();
    ~LevelMap();
    void render(SDL_Renderer *renderer);
    FieldBlock getBlockAtPoint(const Vector2& point) const;
    const LevelMapCollider& getCollider() const;
    typedef std::vector<std::vector<FieldBlock> > TLevelMapField;
    const TLevelMapField& getField() const;
    void affect(const Bomb& bomb);
    void generateBombFragments(const Bomb& bomb, std::vector<BombFragment*>& out);
    void removeFragment(BombFragment* fragment);
    void destroyBlock(const Point& block_field_position);
private:
    bool processCollisionsWithEnemies();
    void destroyFragmentAfterDelay(BombFragment* fragment);
    void generate();
    TLevelMapField _field;
    int _level_size_x;
    int _level_size_y;
    LevelMapCollider* _collider;
    LevelMapCollider* _concrete_collider;
    LevelMapCollider* _brick_collider;
    std::set<BombFragment*> _bomb_fragments;

};

#endif /* LevelMap_h */
