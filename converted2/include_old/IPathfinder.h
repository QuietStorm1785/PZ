#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:45
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   IPathfinder.java
namespace zombie {
namespace ai {
namespace astar {
// Referenced classes of package zombie.ai.astar:
//            Mover, Path
class IPathfinder {
public:
    virtual ~IPathfinder() = default;
{
    public abstract void Failed(Mover mover);
    public abstract void Succeeded(Path path, Mover mover);
    public abstract std::string getName();
}} // namespace
