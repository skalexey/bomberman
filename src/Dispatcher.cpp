//
//  Dispatcher.cpp
//  Slots_ios
//
//  Created by Alexey Skorokhodov on 18/09/2017.
//  Copyright © 2017 Mac. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include "Dispatcher.h"
#include "SDL.h"

Dispatcher& Dispatcher::instance()
{
    static Dispatcher _instance;
    return _instance;
}

void Dispatcher::cancelAll()
{
    _timeouts.clear();
    _intervals.clear();
}

int Dispatcher::runAfter(std::function<bool()> callback_to_do, int timeout_ms)
{
    Timeout timeout(callback_to_do, timeout_ms);
    int id = generateId();
    _timeouts[id] = timeout;
    return id;
}

int Dispatcher::runAndRepeatAfter(std::function<bool()> callback_to_do, int timeout_ms)
{
    callback_to_do();
    Interval interval(callback_to_do, timeout_ms);
    int id = generateId();
    _intervals[id] = interval;
    return id;
}

void Dispatcher::cancelInterval(int id)
{
    _intervals.erase(id);
}

int Dispatcher::generateId() const
{
    int id = 0;
    do
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 0xFFFFFFFF);
        id = dis(gen);
    }
    while(_timeouts.find(id) != _timeouts.end() && id == 0);
    return id;
}

bool Dispatcher::update()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    for(auto it = _timeouts.begin(); it != _timeouts.end();)
    {
        Timeout& timeout = it->second;
        long time_since_start = std::chrono::duration_cast<std::chrono::milliseconds>(now - timeout.creation_time).count();
        if(time_since_start >= timeout.timeout_ms)
        {
            if(timeout.callback_to_do())
            {
                if(_timeouts.size() > 0)
                {
                    it = _timeouts.erase(it);
                }
                else
                {
                    break;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            ++it;
        }
    }
    for(auto it = _intervals.begin(); it != _intervals.end(); ++it)
    {
        Interval& interval = it->second;
        long time_since_last_cycle = std::chrono::duration_cast<std::chrono::milliseconds>(now - interval.last_cycle_time).count();
        if(time_since_last_cycle >= interval.timeout_ms)
        {
            interval.callback_to_do();
            interval.last_cycle_time = now;
        }
    }
    return true;
}

Timeout::Timeout(std::function<bool()> callback_to_do, int timeout_ms)
: callback_to_do(callback_to_do)
, timeout_ms(timeout_ms)
{
    creation_time = std::chrono::steady_clock::now();
}

Interval::Interval(std::function<bool()> callback_to_do, int timeout_ms)
: callback_to_do(callback_to_do)
, timeout_ms(timeout_ms)
{
    last_cycle_time = std::chrono::steady_clock::now();
}
