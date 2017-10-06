//
//  Enemy.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "Enemy.h"
#include "LevelMap.h"

extern float block_size;

Enemy::Enemy(const Point& start_position)
: _collider(0.9f * block_size / 2)
, _is_dead(false)
{
    setPosition(start_position);
}

void Enemy::die()
{
    _is_dead = true;    
}

float Enemy::getSize() const
{
    return _collider.getSize();
}

CircleCollider& Enemy::getCollider()
{
    return _collider;
}

const Vector2& Enemy::getPosition() const
{
    return _collider.getPosition();
}

void Enemy::setPosition(const Point& field_position)
{
    _collider.setPosition({(field_position.x + 0.5f) * block_size, (field_position.y + 0.5f) * block_size});
}

void Enemy::setPosition(const Vector2& position)
{
    _collider.setPosition(position);
}

bool Enemy::update(float dt, const LevelMap& level_map)
{
    return !_is_dead;
}
