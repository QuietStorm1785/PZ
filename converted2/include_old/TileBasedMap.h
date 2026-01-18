#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:46
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   TileBasedMap.java
namespace zombie {
namespace ai {
namespace astar {
#include "IsoDirections.h"
// Referenced classes of package zombie.ai.astar:
//            AStarPathMap, Mover
class TileBasedMap {
public:
    virtual ~TileBasedMap() = default;
{
    public abstract bool blocked(Mover mover, int i, int j, int k, int l, int i1, int j1);
    public abstract float getCost(Mover mover, int i, int j, int k, int l, int i1, int j1);
    public abstract int getElevInTiles();
    public abstract int getHeightInTiles();
    public abstract int getWidthInTiles();
    public abstract void pathFinderVisited(int i, int j, int k);
    public abstract bool isNull(int i, int j, int k);
    public abstract bool IsStairsNode(AStarPathMap.Node node, AStarPathMap.Node node1, IsoDirections isodirections);
}} // namespace
