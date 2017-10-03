//
//  Enemy.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef Enemy_h
#define Enemy_h

#include <memory>
#include "Vector2.h"
#include "SDL.h"
#include "CircleCollider.h"

class LevelMap;

class Enemy
{
public:
    Enemy(const Point& start_position);
    virtual void render(SDL_Renderer* renderer) const = 0;
    CircleCollider& getCollider();
    const Vector2& getPosition() const;
    void setPosition(const Point& field_position);
    void setPosition(const Vector2& position);
    void die();
    virtual bool update(float dt, const LevelMap& level_map);
protected:
    bool _is_dead;
    float getSize() const;
    CircleCollider _collider;
private:
};
typedef std::shared_ptr<Enemy> spEnemy;

#endif /* Enemy_h */
