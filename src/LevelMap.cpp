//
//  LevelMap.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 27/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#include "LevelMap.h"
#include "Game.h"
#include "Utils.h"

LevelMap::LevelMap()
: _level_size_x(0)
, _level_size_y(0)
{
    generate();
    _collider.init(this);
}

const LevelMapCollider& LevelMap::getCollider() const
{
    return _collider;
}

const LevelMap::TLevelMapField& LevelMap::getField() const
{
    return _field;
}

void LevelMap::render(SDL_Renderer *renderer)
{
    for(int y = 0; y < _level_size_y; y++)
    {
        const std::vector<FieldBlock>& field_row = _field[y];
        for(int x = 0; x < _level_size_x; x++)
        {
            const FieldBlock& block = field_row[x];
            SDL_Rect sdl_block;
            sdl_block.x = x * block_size;
            sdl_block.y = y * block_size;
            sdl_block.h = block_size;
            sdl_block.w = block_size;
            Uint8 r = 0, g = 0, b = 0;
            switch(block)
            {
                case BLOCK_CONCRETE:
                    r = 255;
                    g = 255;
                    b = 255;
                    break;
                case BLOCK_BRICK:
                    r = 164;
                    g = 164;
                    b = 164;
                    break;
                case BLOCK_NONE:
                    break;
                default:
                    break;
            }
            if(block != BLOCK_NONE)
            {
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
                SDL_RenderFillRect(renderer, &sdl_block);
            }
        }
    }

}

void LevelMap::generate()
{
    _level_size_x = (int)SCREEN_WIDTH / block_size;
    _level_size_y = (int)SCREEN_HEIGHT / block_size - 3; // field for controls
    for(int y = 0; y < _level_size_y; y++)
    {
        std::vector<FieldBlock> field_row(_level_size_x, BLOCK_NONE);
        for(int x = 0; x < _level_size_x; x++)
        {
            if(x == 0 || x == _level_size_x - 1 || y == 0 || y == _level_size_y - 1 || (y % 2 == 0 && x % 2 == 0))
            {
                field_row[x] = BLOCK_CONCRETE;
            }
            else if(!(x == 1 && y == 1)) // start position should be clean
            {
                field_row[x] = (FieldBlock)Utils::random(0, 2) == 0 ? BLOCK_BRICK : BLOCK_NONE;
            }
            else
            {
                field_row[x] = BLOCK_NONE;
            }
        }
        _field.push_back(field_row);
    }
}

FieldBlock LevelMap::getBlockAtPoint(const Vector2& point) const
{
    int block_index_x = fmin((int)point.x / block_size, _level_size_x);
    int block_index_y = fmin((int)point.y / block_size, _level_size_y);
    return _field[block_index_y][block_index_x];
}
