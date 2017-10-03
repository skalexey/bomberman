//
//  Bomb.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 28/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "Bomb.h"
#include "LevelMap.h"

Bomb::Bomb(int power)
: _power(power)
{
    
}

void Bomb::setPosition(const Vector2& position)
{
    _position = position;
}

const Vector2& Bomb::getPosition() const
{
    return _position;
}

int Bomb::getPower() const
{
    return _power;
}

void Bomb::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect sdl_bomb;
    float w2 = block_size / 2;
    sdl_bomb.x = _position.x - w2;
    sdl_bomb.y = _position.y - w2;
    sdl_bomb.w = block_size;
    sdl_bomb.h = block_size;
    SDL_RenderFillRect(renderer, &sdl_bomb);
}

bool Bomb::detonate()
{
    if(_callback_to_do_on_detonated)
    {
        bool result = _callback_to_do_on_detonated();
        return result;
    }
    return true;
}

void Bomb::setOnDetonated(const std::function<bool()>& callback_to_do_on_detonated)
{
    _callback_to_do_on_detonated = callback_to_do_on_detonated;
}
