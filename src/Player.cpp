//
//  Player.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 27/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include <cmath>
#include <map>
#include "SDL.h"
#include "Player.h"
#include "LevelMap.h"
#include "Dispatcher.h"

Player::Player()
: _collider(size.x * block_size / 2)
, _bomb_power(3)
{
    
}

void Player::render(SDL_Renderer* renderer)
{
    SDL_Rect sdl_player;
    const Vector2& player_position = getPosition();
    sdl_player.w = block_size * size.x;
    sdl_player.h = block_size * size.y;
    sdl_player.x = player_position.x - sdl_player.w / 2;
    sdl_player.y = player_position.y - sdl_player.h / 2;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &sdl_player);
}

const Vector2& Player::getPosition()
{
    return _collider.getPosition();
}

void Player::setPosition(float field_x, float field_y)
{
    setPosition({(field_x + 0.5f) * block_size, (field_y + 0.5f) * block_size});
}

bool Player::setPosition(const Vector2& new_position)
{
    return _collider.setPosition(new_position);
}

Bomb* Player::putBomb()
{
    Bomb* bomb = new Bomb(_bomb_power);
    Dispatcher::instance().runAfter([=]()
    {
        bomb->detonate();
    }, 2000);
    bomb->setPosition(getPosition());
    return bomb;
}

Collider& Player::getCollider()
{
    return _collider;
}

void Player::move(const Vector2& direction, float dt)
{
    Vector2 rounded_direction = direction;
    rounded_direction.normalize();
    rounded_direction *= default_speed;
    rounded_direction *= dt;
    const Vector2& current_position = getPosition();
    Vector2 new_position = current_position + rounded_direction;
    Vector2 new_position_x = {new_position.x, current_position.y};
    Vector2 new_position_y = {current_position.x, new_position.y};
    if(!setPosition(new_position_x))
    {
        setPosition(new_position_y);
    }
    else
    {
        setPosition(new_position);
    }
}

