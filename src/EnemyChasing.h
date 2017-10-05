//
//  EnemyChasing.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef EnemyChasing_h
#define EnemyChasing_h

#include <vector>
#include "Enemy.h"
#include "PathFinder.h"
#include "Vector2.h"

class LevelMap;

class EnemyChasing : public Enemy
{
public:
    EnemyChasing(const Point& start_point);
    void render(SDL_Renderer* renderer) const;
    bool update(float dt, const LevelMap& level_map);
private:
    std::deque<Point> _path;
    PathFinder _path_finder;
    Vector2 _direction;
};
typedef std::shared_ptr<EnemyChasing> spEnemyChasing;

#endif /* EnemyChasing_h */
