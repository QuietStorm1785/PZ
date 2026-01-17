#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   WalkWithinRangeOf.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "Behavior.h"
#include "PathFindBehavior.h"
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "objects.h"
class WalkWithinRangeOf : public BaseCommand {
public:
{
    public WalkWithinRangeOf()
    {
        res = zombie.behaviors.Behavior.BehaviorResult.Working;
        behavior = new PathFindBehavior(true);
        cycle = 120;
    }
    public bool IsFinished()
    {
        return true;
    }
    public void update()
    {
        cycle--;
        if(cycle <= 0)
        {
            cycle = 120;
            behavior.sx = (int)chr.getX();
            behavior.sy = (int)chr.getY();
            behavior.sz = (int)chr.getZ();
            behavior.tx = (int)other.getX();
            behavior.ty = (int)other.getY();
            behavior.tz = (int)other.getZ();
            behavior.pathIndex = 0;
        }
        res = behavior.process(nullptr, chr);
    }
    public void init(std::string object, std::string params[])
    {
        owner = object;
        std::string total = "";
        Other = params[0].trim();
        if(Other == "nullptr"))
            Other = nullptr;
        range = Integer.parseInt(params[1].trim());
    }
    public void begin()
    {
        if(currentinstance != nullptr && currentinstance.HasAlias(owner))
        {
            chr = currentinstance.getAlias(owner);
        } else
        {
            if(module.getCharacter(owner) == nullptr)
                return;
            if(module.getCharacter(owner).Actual == nullptr)
                return;
            chr = module.getCharacter(owner).Actual;
        }
        if(currentinstance != nullptr && currentinstance.HasAlias(Other))
        {
            other = currentinstance.getAlias(Other);
        } else
        {
            if(module.getCharacter(Other) == nullptr)
                return;
            if(module.getCharacter(Other).Actual == nullptr)
                return;
            other = module.getCharacter(Other).Actual;
        }
        behavior.sx = (int)chr.getX();
        behavior.sy = (int)chr.getY();
        behavior.sz = (int)chr.getZ();
        behavior.tx = (int)other.getX();
        behavior.ty = (int)other.getY();
        behavior.tz = (int)other.getZ();
        behavior.pathIndex = 0;
    }
    public bool DoesInstantly()
    {
        return true;
    }
    public bool AllowCharacterBehaviour(std::string scriptCharacter)
    {
        return true;
    }
    public void Finish()
    {
        res = zombie.behaviors.Behavior.BehaviorResult.Working;
        behavior.reset();
    }
    std::string owner;
    std::string say;
    std::string Other;
    IsoGameCharacter other;
    IsoGameCharacter chr;
    int range;
    zombie.behaviors.Behavior.BehaviorResult res;
    PathFindBehavior behavior;
    int cycle;
}
} // namespace
