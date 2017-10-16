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

Game* Game::_instance;

extern float block_size;

Game::Game()
: _destroyed(false)
, _bomb_power(3)
{
    _instance = this;
    init();
}

void Game::init()
{
    _level_map = spLevelMap(new LevelMap());
    _player = spPlayer(new Player(&_level_map->getCollider()));
    _player->setPosition(1, 1);
    spButton button_ew(new Button(Rect(block_size * 18, block_size * 14.5f, block_size * 5, block_size * 2.5), Color(255, 0, 0, 255), [=]()
                     {
                         Point random_free_position = _level_map->findRandomFreePoint();
                         spEnemyWandering enemy(new EnemyWandering(random_free_position));
                         _level_map->addEnemy(enemy);
                     }));
    _buttons.push_back(button_ew);
    spButton button_ec(new Button(Rect(12 * block_size, block_size * 14.5f, block_size * 5, block_size * 2.5), Color(0, 0, 180, 255), [=]()
                     {
                         Point random_free_position = _level_map->findRandomFreePoint();
                         spEnemyChasing enemy(new EnemyChasing(random_free_position));
                         _level_map->addEnemy(enemy);
                     }));
    _buttons.push_back(button_ec);
    spButton button_bomb(new Button(Rect(6 * block_size, block_size * 14.5f, block_size * 5, block_size * 2.5), Color(0, 0, 0, 255), [=]()
                                   {
                                       spBomb bomb(new Bomb(_bomb_power));
                                       Dispatcher::instance().runAfter([=]()
                                       {
                                           bomb->detonate();
                                       }, 2000);
                                       bomb->setPosition(_player->getPosition());
                                       bomb->setOnDetonated([=]()
                                        {
                                            _level_map->affect(*bomb);
                                            _bombs.erase(bomb);
                                        });
                                       _bombs.insert(bomb);
                                   }));
    _buttons.push_back(button_bomb);
    Point random_free_position = _level_map->findRandomFreePoint();
    spEnemyWandering enemy(new EnemyWandering(random_free_position));
    _level_map->addEnemy(enemy);
    random_free_position = _level_map->findRandomFreePoint();
    spEnemyChasing enemy2(new EnemyChasing(random_free_position));
    _level_map->addEnemy(enemy2);
    _destroyed = false;
}

void Game::over()
{
    _instance->destroy();
    _instance->init();
    Dispatcher::instance().cancelAll();
}

void Game::destroy()
{
    _bombs.clear();
    _buttons.clear();
//    generateOverScreen();
    _destroyed = true;
}

void Game::render(SDL_Renderer *renderer)
{
    if(_level_map)
    {
        _level_map->render(renderer);
    }
    if(_player)
    {
        _player->render(renderer);
    }
    for(const spBomb& bomb : _bombs)
    {
        bomb->render(renderer);
    }
    for(const spButton& button: _buttons)
    {
        button->render(renderer);
    }
    if(_destroyed)
    {
        
    }
}

void Game::onMouseButtonDown()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    _joystick.setPosition(x, y);
    for(const spButton& button : _buttons)
    {
        button->processTap(x, y);
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
        if(_player)
        {
            _player->move(_joystick.getDirection(), dt);
        }
    }
    if(_level_map)
    {
        _level_map->update(dt);
    }
    Dispatcher::instance().update();
}
