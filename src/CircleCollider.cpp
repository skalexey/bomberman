//
//  CircleCollider.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "CircleCollider.h"
#include "LevelMapCollider.h"

CircleCollider::CircleCollider(float size)
: Collider()
, _size(size)
, _size_squared(size * size)
{
    
}

float CircleCollider::getSize() const
{
    return _size;
}

bool CircleCollider::check(const Collider& collider2) const
{
    CircleCollider const* collider2_circle = dynamic_cast<CircleCollider const*>(&collider2);
    if(collider2_circle)
    {
        Vector2 distance = collider2.getPosition() - _position;
        float collider2_size = collider2_circle->getSize();
        return distance.sqlength() <= (collider2_size + _size) * (collider2_size + _size);
    }
    LevelMapCollider const* collider2_map = dynamic_cast<LevelMapCollider const*>(&collider2);
    if(collider2_map)
    {
        return collider2_map->check(*this);
    }
    return false;
}
