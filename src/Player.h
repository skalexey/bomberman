//
//  Player.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 27/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef Player_h
#define Player_h


#include "SDL.h"
#include "Vector2.h"
#include "LevelMap.h"
#include "CircleCollider.h"
#include "Bomb.h"

class Player
{
public:
    Player();
    void render(SDL_Renderer* renderer);
    void setPosition(float field_x, float field_y);
    bool setPosition(const Vector2& new_position);
    const Vector2& getPosition();
    void move(const Vector2& direction, float dt);
    Collider& getCollider();
    Bomb* putBomb();
private:
    const Vector2 size = {0.8f, 0.8f};
    const float default_speed = 50.0f;
    CircleCollider _collider;
    int _bomb_power;
};

#endif /* Player_h */
