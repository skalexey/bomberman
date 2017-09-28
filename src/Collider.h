//
//  Collider.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef Collider_h
#define Collider_h

#include <vector>
#include "Vector2.h"

class Collider
{
public:
    Collider();
    virtual bool check(const Collider& collider2) const = 0;
    bool setPosition(const Vector2& new_position);
    const Vector2& getPosition() const;
    bool checkCollisions();
    void addCollider(Collider const* collider);
private:
    std::vector<Collider const*> _colliders;
protected:
    Vector2 _position;
};

#endif /* Collider_h */
