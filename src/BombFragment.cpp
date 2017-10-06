//
//  BombFragment.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "BombFragment.h"

extern float block_size;

BombFragment::BombFragment(int field_position_x, int field_position_y)
: _field_position(field_position_x, field_position_y)
, _collider((field_position_x + 0.5f) * block_size, (field_position_y + 0.5f) * block_size, block_size, block_size)
{
    
}

const Point& BombFragment::getFieldPosition()
{
    return _field_position;
}

const BoxCollider& BombFragment::getCollider() const
{
    return _collider;
}

void BombFragment::render(SDL_Renderer* renderer)
{
    const Point& field_position = getFieldPosition();
    SDL_Rect sdl_block;
    sdl_block.x = field_position.x * block_size;
    sdl_block.y = field_position.y * block_size;
    sdl_block.h = block_size;
    sdl_block.w = block_size;
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &sdl_block);
}
