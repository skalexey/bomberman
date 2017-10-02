//
//  PathFinder.h
//  bomberman
//
//  Created by Alexey Skorokhodov on 29/09/2017.
//  Copyright © 2017 Alexey Skorokhodov. All rights reserved.
//

#ifndef PathFinder_h
#define PathFinder_h

#include <vector>
#include <map>
#include <set>
#include <deque>
#include "Vector2.h"
#include "LevelMap.h"

struct PointInfo
{
    PointInfo(const Point& point);
    float calculateFScore(const PointInfo& end_point);
    Point point;
    float g_score;
    float h_score;
    float f_score;
    bool operator==(PointInfo& another_point_info);
};

class PathFinder
{
public:
    void findPath(std::deque<Point>& out, const Point& start_point, const Point& end_point, const TLevelMapField& field);
private:
    void estimatePathCost(PointInfo& point, const PointInfo& end_point);
    const Point& getLowestFCostFromOpenSet(const std::set<Point>& open_set);
    void reconstructPath(std::deque<Point>& path_out, const Point& current);
    void getNeighbors(std::vector<Point>& neighbors_out, const Point& point, const TLevelMapField& field);
    bool isPointPassable(const Point& point, const TLevelMapField& field);
    PointInfo& registerPoint(const Point& point_info);
    bool isPointRegistered(const Point& point_info);
    std::map<Point, Point> _came_from;
    std::map<Point, PointInfo> _points_infos;
};

#endif /* PathFinder_h */
