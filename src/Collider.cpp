//
//  Collider.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "Collider.h"
#include "CircleCollider.h"

Collider::Collider()
{
}

bool Collider::setPosition(const Vector2& new_position)
{
    Vector2 tmp_position = _position;
    _position = new_position;
    if(checkCollisions())
    {
        _position = tmp_position;
        return false;
    }
    return true;
}

bool Collider::containPoint(int x, int y) const
{
    return false;
}

const Vector2& Collider::getPosition() const
{
    return _position;
}

void Collider::addCollider(Collider const* collider)
{
    _colliders.push_back(collider);
}

bool Collider::checkCollisions()
{
    for(Collider const* collider : _colliders)
    {
        if(check(*collider))
        {
            return true;
        }
    }
    return false;
}
