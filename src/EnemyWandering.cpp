//
//  EnemyWondering.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "EnemyWandering.h"
#include "LevelMap.h"

EnemyWandering::EnemyWandering(const Point& start_point)
: Enemy(start_point)
{
    
}

void EnemyWandering::render(SDL_Renderer* renderer) const
{
    SDL_Rect sdl_enemy;
    const Vector2& position = getPosition();
    float size = getSize();
    sdl_enemy.w = size * 2;
    sdl_enemy.h = size * 2;
    sdl_enemy.x = position.x - sdl_enemy.w / 2;
    sdl_enemy.y = position.y - sdl_enemy.h / 2;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &sdl_enemy);
}

bool EnemyWandering::update(float dt, const LevelMap& level_map)
{
//    float dt = fmin(delta_t, 0.2f);
    if(!Enemy::update(dt, level_map))
    {
        return false;
    }
    const Vector2& current_position = getPosition();
    if(_direction.sqlength() == 0)
    {
        _direction = level_map.chooseFreeDirection(current_position);
    }
    if(_direction.sqlength() == 0)
    {
        return true;
    }
    if(_target.sqlength() == 0)
    {
        _target = level_map.findNearestCrossway(current_position, _direction);
    }
    Vector2 last_position = current_position;
    Vector2 position_after_dt = current_position + _direction * dt;
    Vector2 direction_normalized = _direction.normalized();
    Vector2 direction_to_target = (_target - position_after_dt).normalized();
    if((direction_normalized + direction_to_target).sqlength() == 0)
    {
        setPosition(_target);
        _direction = level_map.chooseFreeDirection(_target);
        _target = level_map.findNearestCrossway(current_position, _direction);
    }
    else
    {
        setPosition(position_after_dt);
    }
    if(level_map.getCollider().check(_collider))
    {
        Point point_at_position = level_map.getPointAtPosition(last_position);
        Vector2 position = {(point_at_position.x + 0.5f) * block_size, (point_at_position.y + 0.5f) * block_size};
        setPosition(position);
        _direction = level_map.chooseFreeDirection(current_position);
        _target = level_map.findNearestCrossway(current_position, _direction);
    }
    return true;
}
