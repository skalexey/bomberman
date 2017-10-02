//
//  Game.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 27/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "Game.h"
#include "Dispatcher.h"
#include "EnemyChasing.h"
#include "EnemyWandering.h"

Game::Game()
{
    _player.setPosition(1, 1);
    _player.getCollider().addCollider(&_level_map.getCollider());
    Button button_ew(Rect(360, 290, 100, 50), Color(255, 0, 0, 255), [=]()
    {
        Point random_free_position = _level_map.findRandomFreePosition();
        EnemyWandering* enemy = new EnemyWandering(random_free_position);
        _level_map.addEnemy(enemy);
    });
    _buttons.push_back(button_ew);
    Button button_ec(Rect(240, 290, 100, 50), Color(119, 0, 255, 255), [=]()
    {
        Point random_free_position = _level_map.findRandomFreePosition();
        EnemyChasing* enemy = new EnemyChasing(random_free_position);
        _level_map.addEnemy(enemy);
    });
    _buttons.push_back(button_ec);
    Point random_free_position = _level_map.findRandomFreePosition();
    EnemyWandering* enemy = new EnemyWandering(random_free_position);
    _level_map.addEnemy(enemy);
    random_free_position = _level_map.findRandomFreePosition();
    EnemyChasing* enemy2 = new EnemyChasing(random_free_position);
    _level_map.addEnemy(enemy2);
}

void Game::render(SDL_Renderer *renderer)
{
    _level_map.render(renderer);
    _player.render(renderer);
    for(Bomb* bomb : _bombs)
    {
        bomb->render(renderer);
    }
    for(const Button& button: _buttons)
    {
        button.render(renderer);
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
    for(Button& button : _buttons)
    {
        button.processTap(x, y);
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
    _level_map.update(dt);
}
