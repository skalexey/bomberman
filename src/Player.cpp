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

extern float block_size;

Player* Player::_instance;

Player::Player(const LevelMapCollider* level_map_collider)
: _collider(size.x * block_size / 2)
, _key_found(false)
, _level_map_collider(level_map_collider)
{
    _instance = this;
}

void Player::setKeyFound()
{
    _key_found = true;
}

Player& Player::getInstance()
{
    return *_instance;
}

bool Player::haveKey()
{
    return _key_found;
}

void Player::render(SDL_Renderer* renderer) const
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

const Vector2& Player::getPosition() const
{
    return _collider.getPosition();
}

void Player::setPosition(float field_x, float field_y)
{
    setPosition({(field_x + 0.5f) * block_size, (field_y + 0.5f) * block_size});
}

void Player::setPosition(const Vector2& new_position)
{
    return _collider.setPosition(new_position);
}

CircleCollider& Player::getCollider()
{
    return _collider;
}

void Player::move(const Vector2& direction, float dt)
{
    Vector2 rounded_direction = direction;
    rounded_direction.normalize();
    rounded_direction *= block_size * 2.5f;
    rounded_direction *= dt;
    Vector2 current_position = getPosition();
    Vector2 new_position = current_position + rounded_direction;
    Vector2 new_position_x = {new_position.x, current_position.y};
    Vector2 new_position_y = {current_position.x, new_position.y};
    setPosition(new_position_x);
    if(_collider.check(*_level_map_collider))
    {
        setPosition(new_position_y);
        if(_collider.check(*_level_map_collider))
        {
            setPosition(current_position);
        }
    }
    else
    {
        setPosition(new_position);
        if(_collider.check(*_level_map_collider))
        {
            setPosition(new_position_x);
        }
    }
}

