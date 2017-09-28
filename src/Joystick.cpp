//
//  Joystick.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include <stdio.h>
#include "Joystick.h"

void Joystick::setPosition(float x, float y)
{
//    printf("Joystick::setPosition(%f, %f)\n", x, y);
    _origin = {x, y};
}

void Joystick::setDirection(float x, float y)
{
//    printf("Joystick::setDirection(%f, %f)\n", x, y);
    if(_origin.sqlength() == 0)
    {
        return;
    }
    _pointer = {x, y};
    _direction = _pointer - _origin;
}

void Joystick::reset()
{
//    printf("Joystick::reset\n");
    _direction = {0, 0};
    _origin = {0, 0};
}

const Vector2& Joystick::getDirection()
{
    return _direction;
}
float Joystick::getSquaredForce()
{
    return _direction.sqlength();
}
