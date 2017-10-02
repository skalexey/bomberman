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

void LevelMap::addEnemy(Enemy* enemy)
{
    _enemies.insert(enemy);
}

Point LevelMap::findRandomFreePosition()
{
    std::vector<Point> free_positions;
    for(int y = 0; y < _level_size_y; y++)
    {
        std::vector<FieldBlock> row = _field[y];
        for(int x = 0; x < _level_size_x; x++)
        {
            if(row[x] == BLOCK_NONE)
            {
                free_positions.push_back({x, y});
            }
        }
    }
    int random_index = Utils::random(0, (int)free_positions.size());
    return free_positions[random_index];
}

void LevelMap::update(float dt)
{
    for(Enemy* enemy : _enemies)
    {
        enemy->update(dt, *this);
    }
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

void LevelMap::processCollisionsWithEnemies(BombFragment* fragment)
{
    
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
            processCollisionsWithEnemies(fragment);
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

const TLevelMapField& LevelMap::getField() const
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
        bomb_fragment->render(renderer);
    }
    for(Enemy* enemy : _enemies)
    {
        enemy->render(renderer);
    }
}

FieldBlock LevelMap::getBlockAtPoint(const Point& point) const
{
    return _field[point.y][point.x];
}

Vector2 LevelMap::chooseFreeDirection(const Vector2& start_position) const
{
    std::vector<Point> available_points;
    Point point = getPointAtPosition(start_position);
    Point left = {point.x - 1, point.y};
    if(left.x >= 0 && getBlockAtPoint(left) == BLOCK_NONE)
    {
        available_points.push_back(left);
    }
    Point top = {point.x, point.y - 1};
    if(top.y >= 0 && getBlockAtPoint(top) == BLOCK_NONE)
    {
        available_points.push_back(top);
    }
    Point right = {point.x + 1, point.y};
    if(top.x < _level_size_x && getBlockAtPoint(right) == BLOCK_NONE)
    {
        available_points.push_back(right);
    }
    Point bottom = {point.x, point.y + 1};
    if(bottom.y < _level_size_y && getBlockAtPoint(bottom) == BLOCK_NONE)
    {
        available_points.push_back(bottom);
    }
    if(available_points.size() > 0)
    {
        int random_index = Utils::random(0, (int)available_points.size() - 1);
        Point random_point = available_points[random_index];
        Vector2 position = {(random_point.x + 0.5f) * block_size, (random_point.y + 0.5f) * block_size};
        Vector2 direction = position - start_position;
        return direction;
    }
    return Vector2();
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

Point LevelMap::getPointAtPosition(const Vector2& position) const
{
    int block_index_x = fmin((int)position.x / block_size, _level_size_x);
    int block_index_y = fmin((int)position.y / block_size, _level_size_y);
    return {block_index_x, block_index_y};
}

FieldBlock LevelMap::getBlockAtPosition(const Vector2& position) const
{
    Point point = getPointAtPosition(position);
    return _field[point.y][point.x];
}
