//
//  Collider.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "Collider.h"

Collider::Collider()
{
}

void Collider::setPosition(const Vector2& new_position)
{
    _position = new_position;
}

bool Collider::containPoint(int x, int y) const
{
    return false;
}

const Vector2& Collider::getPosition() const
{
    return _position;
}

