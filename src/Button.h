//
//  Button.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 02/10/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef Button_h
#define Button_h

#include <functional>
#include "Color.h"
#include "BoxCollider.h"
#include "Rect.h"
#include "SDL.h"

class Button
{
public:
    Button(const Rect& rect, const Color& color, const std::function<void()>& callback_to_do_on_tap);
    const BoxCollider& getCollider() const;
    void render(SDL_Renderer* renderer) const;
    void processTap(int x, int y);
private:
    BoxCollider _collider;
    Color _color;
    std::function<void()> _callback_to_do_on_tap;
};

#endif /* Button_h */
