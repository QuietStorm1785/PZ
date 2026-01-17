#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   WalkCommand.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "InvalidParameterException.h"
#include "Behavior.h"
#include "PathFindBehavior.h"
#include "IsoGameCharacter.h"
#include "NulledArrayList.h"
#include "iso.h"
#include "BaseCommand.h"
#include "objects.h"
class WalkCommand : public BaseCommand {
public:
{
    public void updateskip()
    {
        IsoGameCharacter Actual = module.getCharacterActual(owner);
        Actual.setX((float)x + 0.5F);
        Actual.setY((float)y + 0.5F);
        Actual.setZ(z);
        Actual.getCurrentSquare().getMovingObjects().remove(Actual);
        Actual.setCurrent(IsoWorld.instance.CurrentCell.getGridSquare(x, y, z));
        if(Actual.getCurrentSquare() != nullptr)
            Actual.getCurrentSquare().getMovingObjects().add(Actual);
    }
    public WalkCommand()
    {
        res = zombie.behaviors.Behavior.BehaviorResult.Working;
        behavior = new PathFindBehavior(true);
    }
    public void init(std::string object, std::string params[])
    {
        if(params.length == 1)
        {
            Waypoint pt = module.getWaypoint(params[0].trim());
            if(pt != nullptr)
            {
                x = pt.x;
                y = pt.y;
                z = pt.z;
            }
            owner = object;
        }
    }
    public void begin()
    {
        if(module.getCharacter(owner).Actual == nullptr)
        {
            throw new InvalidParameterException();
        } else
        {
            aowner = module.getCharacter(owner).Actual;
            behavior.sx = (int)aowner.getX();
            behavior.sy = (int)aowner.getY();
            behavior.sz = (int)aowner.getZ();
            behavior.tx = x;
            behavior.ty = y;
            behavior.tz = z;
            behavior.pathIndex = 0;
            return;
        }
    }
    public bool AllowCharacterBehaviour(std::string scriptCharacter)
    {
        return false;
    }
    public void Finish()
    {
        aowner = nullptr;
        res = zombie.behaviors.Behavior.BehaviorResult.Working;
        behavior.reset();
    }
    public bool IsFinished()
    {
        return res == zombie.behaviors.Behavior.BehaviorResult.Succeeded;
    }
    public void update()
    {
        if(res == zombie.behaviors.Behavior.BehaviorResult.Failed)
            begin();
        res = behavior.process(nullptr, aowner);
    }
    public bool DoesInstantly()
    {
        return false;
    }
    int x;
    int y;
    int z;
    zombie.behaviors.Behavior.BehaviorResult res;
    PathFindBehavior behavior;
    std::string owner;
    IsoGameCharacter aowner;
}
} // namespace
