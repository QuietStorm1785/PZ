#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:46
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   ClosestHeuristic.java
namespace zombie {
namespace ai {
namespace astar {
namespace heuristics {
#include "astar.h"
class ClosestHeuristic {
public:
    implements AStarHeuristic
{
    public ClosestHeuristic()
    {
    }
    public float getCost(TileBasedMap map, Mover mover, int x, int y, int z, int tx, int ty, 
            int tz)
    {
        float dx = tx - x;
        float dy = ty - y;
        float dz = tz - z;
        float result = (float)Math.sqrt(dx * dx + dy * dy + dz * dz);
        return result;
    }
}} // namespace
