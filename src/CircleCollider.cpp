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

bool CircleCollider::containPoint(int x, int y) const
{
    Vector2 point_position(x, y);
    Vector2 distance = point_position - _position;
    return distance.sqlength() <= _size_squared;
}

bool CircleCollider::check(const CircleCollider& collider2) const
{
    Vector2 distance = collider2.getPosition() - _position;
    float collider2_size = collider2.getSize();
    return distance.sqlength() <= (collider2_size + _size) * (collider2_size + _size);
}

bool CircleCollider::check(const LevelMapCollider& collider2) const
{
    return collider2.check(*this);
}
