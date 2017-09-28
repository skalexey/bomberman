//
//  LevelMapCollider.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef LevelMapCollider_h
#define LevelMapCollider_h

#include <unordered_map>
#include "Collider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"

class LevelMap;

class LevelMapCollider : public Collider
{
public:
    LevelMapCollider();
    void init(LevelMap const* level_map);
    bool check(const Collider& collider2) const;
private:
    LevelMap const* _level_map;
    std::unordered_map<long, BoxCollider> _blocks_colliders;
};

#endif /* LevelMapCollider_h */
