//
//  Game.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 27/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef Game_h
#define Game_h

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

#include <set>
#include "SDL.h"
#include "LevelMap.h"
#include "Player.h"
#include "Joystick.h"
#include "Bomb.h"
#include "Button.h"

class Game
{
public:
    Game();
    void render(SDL_Renderer *renderer);
    void onMouseButtonDown();
    void onMouseButtonUp();
    void onMouseMove();
    void update(float dt);
    static void over();
    void init();
private:
    void destroy();
    int _bomb_power;
    static Game* _instance;
    spLevelMap _level_map;
    spPlayer _player;
    Joystick _joystick;
    std::set<spBomb> _bombs;
    std::vector<spButton> _buttons;
    bool _destroyed;
};

#endif /* Game_h */
