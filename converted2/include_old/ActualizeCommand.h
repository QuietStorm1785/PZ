#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ActualizeCommand.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "BaseCommand.h"
#include "objects.h"
class ActualizeCommand : public BaseCommand {
public:
{
    public ActualizeCommand()
    {
    }
    public void init(std::string object, std::string params[])
    {
        if(params.length == 1)
        {
            Waypoint pt = module.getWaypoint(params[0]);
            x = pt.x;
            y = pt.y;
            z = pt.z;
            owner = object;
        }
    }
    public void begin()
    {
        module.getCharacter(owner).Actualise(x, y, z);
    }
    public bool IsFinished()
    {
        return true;
    }
    public void update()
    {
    }
    public bool DoesInstantly()
    {
        return true;
    }
    public std::string command;
    public std::string chr;
    public std::string params[];
    std::string owner;
    int x;
    int y;
    int z;
}
} // namespace
