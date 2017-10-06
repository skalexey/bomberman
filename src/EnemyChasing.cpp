//
//  EnemyChasing.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "EnemyChasing.h"
#include "Player.h"

extern float block_size;

EnemyChasing::EnemyChasing(const Point& start_point)
: Enemy(start_point)
{
    
}

void EnemyChasing::render(SDL_Renderer* renderer) const
{
    SDL_Rect sdl_enemy;
    const Vector2& position = getPosition();
    float size = getSize();
    sdl_enemy.w = size * 2;
    sdl_enemy.h = size * 2;
    sdl_enemy.x = position.x - sdl_enemy.w / 2;
    sdl_enemy.y = position.y - sdl_enemy.h / 2;
    SDL_SetRenderDrawColor(renderer, 0, 0, 180, 255);
    SDL_RenderFillRect(renderer, &sdl_enemy);
}

bool EnemyChasing::update(float delta_t, const LevelMap& level_map)
{
    float dt = fmin(delta_t, 0.2f);
    if(!Enemy::update(dt, level_map))
    {
        return false;
    }
    const Vector2& position = getPosition();
    Point start_point = level_map.getPointAtPosition(position);
    Player& player = Player::getInstance();
    const Vector2& target_position = player.getPosition();
    Point target_point = level_map.getPointAtPosition(target_position);
    if(_path.empty())
    {
        _path_finder.findPath(_path, start_point, target_point, level_map.getField());
        if(_path.size() > 1)
        {
            Vector2 target = level_map.getPositionAtPoint(_path[1]);
            _direction = (target - position).normalized();
        }
        else if(_path.size() == 1)
        {
            Vector2 target = target_position;
            _direction = (target - position).normalized();
        }
    }
    if(_path.size() > 1)
    {
        const Point& penult_point = _path[1];
        Vector2 direction = (level_map.getPositionAtPoint(penult_point) - position);
        Vector2 direction_normalized = direction.normalized();
        Vector2 delta_d = direction_normalized + _direction;
        if(delta_d.x == 0 && delta_d.y == 0)
        {
            setPosition(level_map.getPositionAtPoint(penult_point));
            _path.clear();
            return false;
        }
        else
        {
            setPosition(position + direction_normalized * dt * block_size);
        }
    }
    else if(_path.size() == 1)
    {
        Vector2 direction = player.getPosition() - position;
        setPosition(position + direction.normalized() * block_size * dt);
        if(direction.length() > block_size)
        {
            _path.clear();
        }
    }
    return true;
}
