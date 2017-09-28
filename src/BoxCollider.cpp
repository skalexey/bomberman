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

BoxCollider::BoxCollider(float x, float y, float w, float h)
: Collider()
, _w(w)
, _h(h)
{
    _position.x = x;
    _position.y = y;
}

bool BoxCollider::check(const Collider& collider2) const
{
    CircleCollider const* collider2_circle = dynamic_cast<CircleCollider const*>(&collider2);
    if(collider2_circle)
    {
        const Vector2& circle_position = collider2.getPosition();
        const Vector2& box_position = getPosition();
        Vector2 distance = _position - collider2.getPosition();
        float circle_distance_x = fabs(circle_position.x - box_position.x);
        float circle_distance_y = fabs(circle_position.y - box_position.y);
        float w2 = _w / 2;
        float h2 = _h / 2;
        float r = collider2_circle->getSize();
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
    return false;
}
