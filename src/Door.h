//
//  Door.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 03/10/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef Door_h
#define Door_h

#include <memory>
#include "SDL.h"
#include "CircleCollider.h"
class Door
{
public:
    Door();
    const Collider& getCollider() const;
    void render(SDL_Renderer* renderer) const;
    const Vector2& getPosition() const;
    void setPosition(const Point& point);
private:
    CircleCollider _collider;
};
typedef std::shared_ptr<Door> spDoor;
#endif /* Door_h */
