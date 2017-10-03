//
//  BombFragment.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef BombFragment_h
#define BombFragment_h

#include <memory>
#include "Vector2.h"
#include "BoxCollider.h"
#include "SDL.h"

class BombFragment
{
public:
    BombFragment(int field_position_x, int field_position_y);
    const Point& getFieldPosition();
    const BoxCollider& getCollider() const;
    void render(SDL_Renderer* renderer);
private:
    Point _field_position;
    BoxCollider _collider;
};
typedef std::shared_ptr<BombFragment> spBombFragment;

#endif /* BombFragment_h */
