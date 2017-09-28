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

#include "SDL.h"
#include "LevelMap.h"
#include "Player.h"
#include "Joystick.h"

class Game
{
public:
    Game();
    void render(SDL_Renderer *renderer);
    void onMouseButtonDown();
    void onMouseButtonUp();
    void onMouseMove();
    void update(float dt);
private:
    LevelMap _level_map;
    Player _player;
    Joystick _joystick;
};

#endif /* Game_h */