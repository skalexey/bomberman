//
//  Button.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 02/10/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "Button.h"

Button::Button(const Rect& rect, const Color& color, const std::function<void()>& callback_to_do_on_tap)
: _collider(BoxCollider(rect.x, rect.y, rect.w, rect.h))
, _color(color)
, _callback_to_do_on_tap(callback_to_do_on_tap)
{
    
}

const BoxCollider& Button::getCollider() const
{
    return _collider;
}

void Button::render(SDL_Renderer* renderer) const
{
    SDL_Rect sdl_button;
    Vector2 position = _collider.getPosition();
    Vector2 size = _collider.getSize();
    sdl_button.w = size.x;
    sdl_button.h = size.y;
    sdl_button.x = position.x - sdl_button.w / 2;
    sdl_button.y = position.y - sdl_button.h / 2;
    SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
    SDL_RenderFillRect(renderer, &sdl_button);

}

void Button::processTap(int x, int y)
{
    if(_collider.containPoint(x, y))
    {
        _callback_to_do_on_tap();
    }
}
