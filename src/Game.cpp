//
//  Game.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 27/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "Game.h"

Game::Game()
{
    _player.setPosition(1, 1);
    _player.getCollider().addCollider(&_level_map.getCollider());
}

void Game::render(SDL_Renderer *renderer)
{
    _level_map.render(renderer);
    _player.render(renderer);
}

void Game::onMouseButtonDown()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    _joystick.setPosition(x, y);
}

void Game::onMouseButtonUp()
{
    _joystick.reset();
}

void Game::onMouseMove()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    _joystick.setDirection(x, y);
}

void Game::update(float dt)
{
    if(_joystick.getSquaredForce() > 0)
    {
        _player.move(_joystick.getDirection(), _level_map, dt);
    }
}
