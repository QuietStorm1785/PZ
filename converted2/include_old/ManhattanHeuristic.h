#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:46
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   ManhattanHeuristic.java
namespace zombie {
namespace ai {
namespace astar {
namespace heuristics {
#include "astar.h"
class ManhattanHeuristic {
public:
    implements AStarHeuristic
{
    public ManhattanHeuristic(int minimumCost)
    {
        this.minimumCost = minimumCost;
    }
    public float getCost(TileBasedMap map, Mover mover, int x, int y, int z, int tx, int ty, 
            int tz)
    {
        return (float)(minimumCost * (Math.abs(x - tx) + Math.abs(y - ty) + Math.abs(z - tz)));
    }
    private int minimumCost;
}} // namespace
