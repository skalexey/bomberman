//
//  LevelMap.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 27/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef LevelMap_h
#define LevelMap_h

#include <memory>
#include <set>
#include <vector>
#include "SDL.h"
#include "Bomb.h"
#include "BombFragment.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "FieldBlock.h"

const float block_size = 20.0f;

class LevelMap;

enum CheckCollisionResult
{
    COLLISION_NONE,
    COLLISION_XY,
    COLLISION_X,
    COLLISION_Y
};

#include "LevelMapCollider.h"

class LevelMapCollider;

typedef std::vector<std::vector<FieldBlock> > TLevelMapField;

class LevelMap
{
public:
    LevelMap();
    ~LevelMap();
    void render(SDL_Renderer *renderer);
    FieldBlock getBlockAtPosition(const Vector2& point) const;
    const LevelMapCollider& getCollider() const;
    const TLevelMapField& getField() const;
    bool affect(const Bomb& bomb);
    void generateBombFragments(const Bomb& bomb, std::vector<spBombFragment>& out);
    void removeFragment(const spBombFragment& fragment);
    void destroyBlock(const Point& block_field_position);
    void update(float dt);
    Vector2 chooseFreeDirection(const Vector2& start_position) const;
    Point getPointAtPosition(const Vector2& position) const;
    Vector2 getPositionAtPoint(const Point& point) const;
    FieldBlock getBlockAtPoint(const Point& point) const;
    void addEnemy(const spEnemy& enemy);
    Point findRandomFreePoint();
    Point findRandomPoint(FieldBlock block);
    bool isPointPassable(const Point& point) const;
    Vector2 findNearestCrossway(const Vector2& position, const Vector2& direction) const;
private:
    bool isCrosswayOrDeadend(const Vector2& position) const;
    void processCollisionsWithEnemies(const spBombFragment& fragment);
    void destroyFragmentAfterDelay(const spBombFragment& fragment);
    void generate();
    TLevelMapField _field;
    int _level_size_x;
    int _level_size_y;
    spLevelMapCollider _collider;
    spLevelMapCollider _concrete_collider;
    spLevelMapCollider _brick_collider;
    std::set<spBombFragment> _bomb_fragments;
    std::set<spEnemy> _enemies;
    spKey _key;
    spDoor _door;
};
typedef std::shared_ptr<LevelMap> spLevelMap;
#endif /* LevelMap_h */
