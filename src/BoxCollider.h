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

class BoxCollider : public Collider
{
public:
    BoxCollider();
    BoxCollider(float x, float y, float w, float h);
    bool check(const Collider& collider2) const;
private:
    float _x;
    float _y;
    float _w;
    float _h;
};

#endif /* BoxCollider_h */
