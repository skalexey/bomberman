//
//  Game.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 27/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "Game.h"
#include "Dispatcher.h"

Game::Game()
{
    _player.setPosition(1, 1);
    _player.getCollider().addCollider(&_level_map.getCollider());
}

void Game::render(SDL_Renderer *renderer)
{
    _level_map.render(renderer);
    _player.render(renderer);
    for(Bomb* bomb : _bombs)
    {
        bomb->render(renderer);
    }
}

void Game::onMouseButtonDown()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    _joystick.setPosition(x, y);
    if(_player.getCollider().containPoint(x, y))
    {
        Bomb* bomb = _player.putBomb();
        bomb->setOnDetonated([=]()
                             {
                                 _bombs.erase(bomb);
                                 _level_map.affect(*bomb);
                                 delete bomb;
                             });
        _bombs.insert(bomb);
    }
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
        _player.move(_joystick.getDirection(), dt);
    }
    Dispatcher::instance().update();
}
