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
#include "LevelMap.h"

class LevelMapCollider : public Collider
{
public:
    LevelMapCollider(LevelMap const* level_map, FieldBlock block_type = BLOCK_NONE);
    bool check(const Collider& collider2) const;
    void removeBlockCollider(FieldBlock* block);
private:
    void init(LevelMap const* level_map, FieldBlock block_type);
    LevelMap const* _level_map;
    std::unordered_map<FieldBlock const*, BoxCollider> _blocks_colliders;
};

#endif /* LevelMapCollider_h */
