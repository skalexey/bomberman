//
//  Bomb.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef Bomb_h
#define Bomb_h

#include <functional>
#include "SDL.h"
#include "Vector2.h"

class Bomb
{
public:
    Bomb(int power);
    void render(SDL_Renderer* renderer) const;
    void setPosition(const Vector2& position);
    const Vector2& getPosition() const;
    void detonate();
    void setOnDetonated(const std::function<void()>& callback_to_do_on_detonated);
    int getPower() const;
private:
    Vector2 _position;
    int _power;
private:
    std::function<void()> _callback_to_do_on_detonated;
};

#endif /* Bomb_h */
