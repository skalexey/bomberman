//
//  Player.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 27/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <memory>
#include "SDL.h"
#include "Vector2.h"
#include "LevelMap.h"
#include "CircleCollider.h"
#include "Bomb.h"

class Player
{
public:
    Player();
    void render(SDL_Renderer* renderer) const;
    void setPosition(float field_x, float field_y);
    bool setPosition(const Vector2& new_position);
    const Vector2& getPosition() const;
    void move(const Vector2& direction, float dt);
    Collider& getCollider();
    static Player& getInstance();
    void setKeyFound();
    bool haveKey();
private:
    static Player* _instance;
    const Vector2 size = {0.8f, 0.8f};
    const float default_speed = 50.0f;
    CircleCollider _collider;
    bool _key_found;
};
typedef std::shared_ptr<Player> spPlayer;
#endif /* Player_h */
