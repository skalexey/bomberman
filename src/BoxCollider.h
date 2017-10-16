//
//  BoxCollider.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef BoxCollider_h
#define BoxCollider_h

#include "Collider.h"

class CircleCollider;
class BoxCollider;

class BoxCollider : public Collider
{
public:
    BoxCollider();
    BoxCollider(float x, float y, float w, float h);
    bool check(const CircleCollider& collider2) const;
    bool check(const BoxCollider& collider2) const;
    Vector2 getSize() const;
    bool containPoint(int x, int y) const;
private:
    float _w;
    float _h;
};

#endif /* BoxCollider_h */
