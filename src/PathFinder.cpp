//
//  PathFinder.cpp
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//
#include <limits>
#include <cmath>
#include "PathFinder.h"

PointInfo::PointInfo(const Point& point)
: point(point)
, g_score(std::numeric_limits<float>::max())
, f_score(std::numeric_limits<float>::max())
, h_score(0)
{
    
}

float PointInfo::calculateFScore(const PointInfo& end_point)
{
    h_score = (point - end_point.point).manhattanLength();
    f_score = g_score + h_score;
    return f_score;
}

const Point& PathFinder::getLowestFCostFromOpenSet(const std::set<Point>& open_set)
{
    float min_f_cost = std::numeric_limits<float>::max();
    Point const* min_point = nullptr;
    for(const Point& point : open_set)
    {
        const PointInfo& point_info = _points_infos.at(point);
        if(point_info.f_score < min_f_cost)
        {
            min_f_cost = point_info.f_score;
            min_point = &point_info.point;
        }
    }
    return *min_point;
}

bool PointInfo::operator==(PointInfo& another_point_info)
{
    return point == another_point_info.point;
}

PointInfo& PathFinder::registerPoint(const Point& point)
{
    std::map<Point, PointInfo>::iterator it = _points_infos.insert(std::pair<Point, PointInfo>(point, PointInfo(point))).first;
    return it->second;
}

bool PathFinder::isPointRegistered(const Point& point_info)
{
    return _points_infos.find(point_info) != _points_infos.end();
}

void PathFinder::findPath(std::deque<Point>& out, const Point& start_point, const Point& end_point, const TLevelMapField& field)
{
    _points_infos.clear();
    _came_from.clear();
    std::set<Point> closed_set;
    std::set<Point> open_set;
    open_set.insert(start_point);
    PointInfo& start_point_info = registerPoint(start_point);
    start_point_info.g_score = 0;
    PointInfo& end_point_info = registerPoint(end_point);
    estimatePathCost(start_point_info, end_point_info);
    while(!open_set.empty())
    {
        const Point& current = getLowestFCostFromOpenSet(open_set);
        if(current == end_point)
        {
            open_set.clear();
            reconstructPath(out, current);
            return;
        }
        open_set.erase(current);
        closed_set.insert(current);
        std::vector<Point> neighbors;
        getNeighbors(neighbors, current, field);
        for(Point& neighbor : neighbors)
        {
            if(!isPointRegistered(neighbor))
            {
                registerPoint(neighbor);
            }
            PointInfo& neighbor_point_info = _points_infos.at(neighbor);
            if(closed_set.find(neighbor) == closed_set.end())
            {
                if(open_set.find(neighbor) == open_set.end())
                {
                    open_set.insert(neighbor);
                }
                const PointInfo& current_point_info = _points_infos.at(current);
                float tentative_g_score = current_point_info.g_score + (current - neighbor).manhattanLength();
                if(tentative_g_score < neighbor_point_info.g_score)
                {
                    _came_from[neighbor] = current;
                    neighbor_point_info.g_score = tentative_g_score;
                    estimatePathCost(neighbor_point_info, end_point_info);
                }
            }
        }
    }
}

void PathFinder::getNeighbors(std::vector<Point>& neighbors_out, const Point& point, const TLevelMapField& field)
{
    Point left(point.x - 1, point.y);
    if(isPointPassable(left, field))
    {
        neighbors_out.push_back(left);
    }
    Point right(point.x + 1, point.y);
    if(isPointPassable(right, field))
    {
        neighbors_out.push_back(right);
    }
    Point top(point.x, point.y + 1);
    if(isPointPassable(top, field))
    {
        neighbors_out.push_back(top);
    }
    Point bottom(point.x, point.y - 1);
    if(isPointPassable(bottom, field))
    {
        neighbors_out.push_back(bottom);
    }
}

bool PathFinder::isPointPassable(const Point& point, const TLevelMapField& field)
{
    bool is_coordinate_valid = point.x >= 0 && point.y >= 0 && point.y < field.size() && point.x < field[0].size();
    return is_coordinate_valid && field[point.y][point.x] == BLOCK_NONE;
}

void PathFinder::reconstructPath(std::deque<Point>& path_out, const Point& current)
{
    Point current_point = current;
    while(_came_from.find(current_point) != _came_from.end())
    {
        Point cur = _came_from[current_point];
        current_point = cur;
        path_out.push_front(current_point);
    }
}

void PathFinder::estimatePathCost(PointInfo& point_info, const PointInfo& end_point_info)
{
    point_info.calculateFScore(end_point_info);
}

