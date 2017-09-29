//
//  BombFragment.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "BombFragment.h"
#include "LevelMap.h"

BombFragment::BombFragment(int field_position_x, int field_position_y)
: _field_position(field_position_x, field_position_y)
, _collider((field_position_x + 0.5f) * block_size, (field_position_y + 0.5f) * block_size, block_size, block_size)
{
    
}

const Point& BombFragment::getFieldPosition()
{
    return _field_position;
}

const BoxCollider& BombFragment::getCollider() const
{
    return _collider;
}
