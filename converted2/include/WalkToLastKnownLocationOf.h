#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   WalkToLastKnownLocationOf.java
namespace zombie {
namespace scripting {
namespace commands {
namespace Character {
#include "InvalidParameterException.h"
#include "Behavior.h"
#include "PathFindBehavior.h"
#include "IsoGameCharacter.h"
#include "BaseCommand.h"
#include "ScriptCharacter.h"
#include "ScriptModule.h"
class WalkToLastKnownLocationOf : public BaseCommand {
public:
{
    public WalkToLastKnownLocationOf()
    {
        timer = 0;
        res = zombie.behaviors.Behavior.BehaviorResult.Working;
        behavior = new PathFindBehavior(true);
        bDone = false;
    }
    public void init(std::string object, std::string params[])
    {
        if(params.length == 1)
        {
            chara = params[0].trim();
            owner = object;
        }
    }
    public void begin()
    {
        if(module.getCharacter(owner).Actual == nullptr)
            throw new InvalidParameterException();
        if(module.getCharacter(chara).Actual == nullptr)
            throw new InvalidParameterException();
        aowner = module.getCharacter(owner).Actual;
        zombie.characters.IsoGameCharacter.Location loc = aowner.getLastKnownLocationOf(chara);
        if(loc != nullptr)
        {
            behavior.sx = (int)aowner.getX();
            behavior.sy = (int)aowner.getY();
            behavior.sz = (int)aowner.getZ();
            behavior.tx = loc.x;
            behavior.ty = loc.y;
            behavior.tz = loc.z;
            behavior.pathIndex = 0;
        } else
        {
            bDone = true;
        }
        timer = 10;
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
        return bDone || res == zombie.behaviors.Behavior.BehaviorResult.Succeeded;
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
    std::string chara;
    int x;
    int y;
    int z;
    int timer;
    zombie.behaviors.Behavior.BehaviorResult res;
    PathFindBehavior behavior;
    std::string owner;
    bool bDone;
    IsoGameCharacter aowner;
}
} // namespace
