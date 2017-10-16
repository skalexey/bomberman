//
//  BoxCollider.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "BoxCollider.h"
#include "CircleCollider.h"

BoxCollider::BoxCollider()
: Collider()
, _w(0)
, _h(0)
{
    
}

Vector2 BoxCollider::getSize() const
{
    return Vector2(_w, _h);
}

bool BoxCollider::containPoint(int x, int y) const
{
    float x_distance = fabs(x - _position.x);
    float y_distance = fabs(y - _position.y);
    return x_distance <= _w / 2 && y_distance <= _h / 2;
}

BoxCollider::BoxCollider(float x, float y, float w, float h)
: Collider()
, _w(w)
, _h(h)
{
    _position.x = x;
    _position.y = y;
}

bool BoxCollider::check(const CircleCollider& collider2) const
{
    const Vector2& circle_position = collider2.getPosition();
    const Vector2& box_position = getPosition();
    Vector2 distance = _position - collider2.getPosition();
    float circle_distance_x = fabs(circle_position.x - box_position.x);
    float circle_distance_y = fabs(circle_position.y - box_position.y);
    float w2 = _w / 2;
    float h2 = _h / 2;
    float r = collider2.getSize();
    if (circle_distance_x > (w2 + r))
    {
        return false;
    }
    if (circle_distance_y > (h2 + r))
    {
        return false;
    }
    if (circle_distance_x <= w2)
    {
        return true;
    }
    if (circle_distance_y <= h2)
    {
        return true;
    }
    float corner_distance_sq = (circle_distance_x - w2) * (circle_distance_x - w2) + (circle_distance_y - h2) * (circle_distance_y - h2);
    bool result = corner_distance_sq <= (r * r);
    if(result)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

bool BoxCollider::check(const BoxCollider& collider2) const
{
    float w2_1 = _w / 2;
    float h2_1 = _h / 2;
    Vector2 collider_2_size = collider2.getSize();
    float w2_2 = collider_2_size.x / 2;
    float h2_2 = collider_2_size.y / 2;
    Vector2 distance = getPosition() - collider2.getPosition();
    return fabs(distance.x) < w2_1 + w2_2 && fabs(distance.y) < h2_1 + h2_2;
}
