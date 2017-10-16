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
    virtual bool containPoint(int x, int y) const;
    void setPosition(const Vector2& new_position);
    const Vector2& getPosition() const;
private:
protected:
    Vector2 _position;
};

#endif /* Collider_h */
