//
//  LevelMapCollider.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "LevelMapCollider.h"
#include "LevelMap.h"

LevelMapCollider::LevelMapCollider()
: Collider()
, _level_map(nullptr)
{
    
}

void LevelMapCollider::init(LevelMap const* level_map)
{
    const LevelMap::TLevelMapField& field = level_map->getField();
    for(int y = 0; y < field.size(); y++)
    {
        const std::vector<FieldBlock>& row_in_map = field[y];
        for(int x = 0; x < row_in_map.size(); x++)
        {
            const FieldBlock& block = row_in_map[x];
            if(block == BLOCK_BRICK || block == BLOCK_CONCRETE)
            {
                _blocks_colliders[(long)&block] = BoxCollider((x + 0.5f) * block_size, (y + 0.5f) * block_size, block_size, block_size);
            }
        }
    }
}

bool LevelMapCollider::check(const Collider& collider2) const
{
    for(const auto& it : _blocks_colliders)
    {
        const BoxCollider& box_collider = it.second;
        if(box_collider.check(collider2))
        {
            return true;
        }
    }
    return false;
}

