//
//  BombFragment.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef BombFragment_h
#define BombFragment_h

#include "Vector2.h"
#include "BoxCollider.h"

class BombFragment
{
public:
    BombFragment(int field_position_x, int field_position_y);
    const Point& getFieldPosition();
    const BoxCollider& getCollider() const;
private:
    Point _field_position;
    BoxCollider _collider;
};

#endif /* BombFragment_h */
