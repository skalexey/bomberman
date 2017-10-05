//
//  EnemyWondering.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef EnemyWondering_h
#define EnemyWondering_h

#include "Enemy.h"

class LevelMap;

class EnemyWandering : public Enemy
{
public:
    EnemyWandering(const Point& start_point);
    void render(SDL_Renderer* renderer) const;
    bool update(float dt, const LevelMap& level_map);
private:
    Vector2 _direction;
    Vector2 _target;
};
typedef std::shared_ptr<EnemyWandering> spEnemyWandering;
#endif /* EnemyWondering_h */
