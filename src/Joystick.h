//
//  Joystick.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef Joystick_h
#define Joystick_h

#include "Vector2.h"

class Joystick
{
public:
    void setPosition(float x, float y);
    void setDirection(float x, float y);
    void reset();
    const Vector2& getDirection();
    float getSquaredForce();
private:
    Vector2 _origin;
    Vector2 _pointer;
    Vector2 _direction;
};

#endif /* Joystick_h */
