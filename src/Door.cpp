//
//  Door.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 03/10/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "Door.h"

extern float block_size;

Door::Door()
: _collider(block_size / 2)
{
    
}

const Collider& Door::getCollider() const
{
    return _collider;
}

const Vector2& Door::getPosition() const
{
    return _collider.getPosition();
}

void Door::render(SDL_Renderer* renderer) const
{
    SDL_Rect sdl_key;
    const Vector2& position = getPosition();
    sdl_key.w = block_size;
    sdl_key.h = block_size;
    sdl_key.x = position.x - sdl_key.w / 2;
    sdl_key.y = position.y - sdl_key.h / 2;
    SDL_SetRenderDrawColor(renderer, 255, 183, 61, 255);
    SDL_RenderFillRect(renderer, &sdl_key);
}

void Door::setPosition(const Point& point)
{
    _collider.setPosition({(point.x + 0.5f) * block_size, (point.y + 0.5f) * block_size});
}
