//
//  EnemyChasing.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "EnemyChasing.h"
#include "Player.h"

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
    SDL_SetRenderDrawColor(renderer, 119, 0, 255, 255);
    SDL_RenderFillRect(renderer, &sdl_enemy);
}

void EnemyChasing::update(float dt, const LevelMap& level_map)
{
    _path.clear();
    const Vector2& position = getPosition();
    Point start_point = level_map.getPointAtPosition(position);
    Player& player = Player::getInstance();
    Point target_point = level_map.getPointAtPosition(player.getPosition());
    _path_finder.findPath(_path, start_point, target_point, level_map.getField());
    if(_path.size() > 1)
    {
        const Point& penult_point = _path[1];
        Vector2 direction = Vector2((penult_point.x + 0.5f) * block_size, (penult_point.y + 0.5f) * block_size) - position;
        setPosition(position + direction * dt);
    }
    else if(_path.size() == 1)
    {
        Vector2 direction = player.getPosition() - position;
        setPosition(position + direction * dt);
    }
}
