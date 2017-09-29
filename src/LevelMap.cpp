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
#include "Dispatcher.h"

LevelMap::LevelMap()
: _level_size_x(0)
, _level_size_y(0)
{
    generate();
    _collider = new LevelMapCollider(this);
    _concrete_collider = new LevelMapCollider(this, BLOCK_CONCRETE);
    _brick_collider = new LevelMapCollider(this, BLOCK_BRICK);
}

LevelMap::~LevelMap()
{
    delete _collider;
    delete _concrete_collider;
    delete _brick_collider;
}

void LevelMap::generateBombFragments(const Bomb& bomb, std::vector<BombFragment*>& out)
{
    int bomb_power = bomb.getPower();
    const Vector2& bomb_position = bomb.getPosition();
    int block_index_x = fmin((int)bomb_position.x / block_size, _level_size_x);
    int block_index_y = fmin((int)bomb_position.y / block_size, _level_size_y);
    BombFragment* bomb_fragment = new BombFragment(block_index_x, block_index_y);
    _bomb_fragments.insert(bomb_fragment);
    out.push_back(bomb_fragment);
    
    for(int i = 0; i < bomb_power; i++)
    {
        BombFragment* bomb_fragment = new BombFragment(block_index_x + i + 1, block_index_y);
        if(_concrete_collider->check(bomb_fragment->getCollider()))
        {
            delete bomb_fragment;
            break;
        }
        else
        {
            _bomb_fragments.insert(bomb_fragment);
            out.push_back(bomb_fragment);
        }
    }
    
    for(int i = 0; i < bomb_power; i++)
    {
        BombFragment* bomb_fragment = new BombFragment(block_index_x - i - 1, block_index_y);
        if(_concrete_collider->check(bomb_fragment->getCollider()))
        {
            delete bomb_fragment;
            break;
        }
        else
        {
            _bomb_fragments.insert(bomb_fragment);
            out.push_back(bomb_fragment);
        }
    }
    
    for(int i = 0; i < bomb_power; i++)
    {
        BombFragment* bomb_fragment = new BombFragment(block_index_x, block_index_y + i + 1);
        if(_concrete_collider->check(bomb_fragment->getCollider()))
        {
            delete bomb_fragment;
            break;
        }
        else
        {
            _bomb_fragments.insert(bomb_fragment);
            out.push_back(bomb_fragment);
        }
    }
    
    for(int i = 0; i < bomb_power; i++)
    {
        BombFragment* bomb_fragment = new BombFragment(block_index_x, block_index_y - i - 1);
        if(_concrete_collider->check(bomb_fragment->getCollider()))
        {
            delete bomb_fragment;
            break;
        }
        else
        {
            _bomb_fragments.insert(bomb_fragment);
            out.push_back(bomb_fragment);
        }
    }
}

void LevelMap::removeFragment(BombFragment* fragment)
{
    _bomb_fragments.erase(fragment);
    delete fragment;
}

void LevelMap::destroyBlock(const Point& block_field_position)
{
    FieldBlock& field_block = _field[block_field_position.y][block_field_position.x];
    FieldBlock* field_block_ptr = &field_block;
    field_block = BLOCK_NONE;
    _collider->removeBlockCollider(field_block_ptr);
    _brick_collider->removeBlockCollider(field_block_ptr);
}

void LevelMap::affect(const Bomb& bomb)
{
    Vector2 bomb_position = bomb.getPosition();
    std::vector<BombFragment*> bomb_fragments;
    generateBombFragments(bomb, bomb_fragments);
    for(BombFragment* fragment : bomb_fragments)
    {
        if(_brick_collider->check(fragment->getCollider()))
        {
            destroyBlock(fragment->getFieldPosition());
            destroyFragmentAfterDelay(fragment);
        }
        else
        {
            processCollisionsWithEnemies();
            destroyFragmentAfterDelay(fragment);
        }
    }
}

void LevelMap::destroyFragmentAfterDelay(BombFragment* fragment)
{
    Dispatcher::instance().runAfter([=]()
    {
        removeFragment(fragment);
    }, 1200);
}

const LevelMapCollider& LevelMap::getCollider() const
{
    return *_collider;
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
    for(BombFragment* bomb_fragment : _bomb_fragments)
    {
        const Point& field_position = bomb_fragment->getFieldPosition();
        SDL_Rect sdl_block;
        sdl_block.x = field_position.x * block_size;
        sdl_block.y = field_position.y * block_size;
        sdl_block.h = block_size;
        sdl_block.w = block_size;
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &sdl_block);
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
