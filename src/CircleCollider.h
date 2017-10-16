//
//  CircleCollider.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef CircleCollider_h
#define CircleCollider_h

#include "Collider.h"

class LevelMapCollider;

class CircleCollider : public Collider
{
public:
    CircleCollider(float size);
    bool check(const CircleCollider& collider2) const;
    bool check(const LevelMapCollider& collider2) const;
    float getSize() const;
    bool containPoint(int x, int y) const;
private:
    float _size;
    float _size_squared;
};

#endif /* CircleCollider_h */
