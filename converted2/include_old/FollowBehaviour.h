#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   FollowBehaviour.java
namespace zombie {
namespace behaviors {
namespace general {
#include "Behavior.h"
#include "DecisionPath.h"
#include "IsoGameCharacter.h"
#include "SurvivorPersonality.h"
#include "Rand.h"
#include "InventoryItem.h"
#include "IsoGridSquare.h"
#include "IsoUtils.h"
// Referenced classes of package zombie.behaviors.general:
//            PathFindBehavior
class FollowBehaviour : public Behavior {
public:
{
    public FollowBehaviour()
    {
        thinkTime = 30;
        thinkTimeMax = 30;
        stayInside = false;
        pathFind = new PathFindBehavior("FollowBehaviour");
        Target = nullptr;
        weapon = nullptr;
        timeout = 180;
    }
    public zombie.behaviors.Behavior.BehaviorResult process(DecisionPath path, IsoGameCharacter character)
    {
        character.setFollowingTarget(Target);
        bool PickedTargetThisFrame = false;
        timeout--;
        if(timeout > 0);
        if(Target != nullptr && Target.getHealth() <= 0.0F)
        {
            Target = nullptr;
            weapon = nullptr;
            timeout = 180;
            return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
        }
        thinkTime--;
        if(Target == nullptr && thinkTime <= 0)
        {
            Target = character.getCurrentSquare().FindFriend(character, character.getPersonality().getHuntZombieRange(), character.getEnemyList());
            if(Target != nullptr && Target.getCurrentSquare() != nullptr)
                PickedTargetThisFrame = true;
            if(Rand.Next(2) != 0)
                character.setPathSpeed(0.08F);
            else
                character.setPathSpeed(0.05F);
            thinkTime = thinkTimeMax;
            pathFind.sx = character.getCurrentSquare().getX();
            pathFind.sy = character.getCurrentSquare().getY();
            pathFind.sz = character.getCurrentSquare().getZ();
        }
        if(Target == nullptr)
        {
            weapon = nullptr;
            timeout = 180;
            return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
        }
        IsoGridSquare mine = character.getCurrentSquare();
        IsoGridSquare theirs = Target.getCurrentSquare();
        if(mine != nullptr && theirs != nullptr)
        {
            float dist = IsoUtils.DistanceManhatten(mine.getX(), mine.getY(), theirs.getX(), theirs.getY());
            if(theirs.getZ() != mine.getZ() || 5F < dist)
            {
                if(PickedTargetThisFrame)
                {
                    pathFind.tx = theirs.getX();
                    pathFind.ty = theirs.getY();
                    pathFind.tz = theirs.getZ();
                    PickedTargetThisFrame = false;
                }
                zombie.behaviors.Behavior.BehaviorResult res = pathFind.process(path, character);
                if(res == zombie.behaviors.Behavior.BehaviorResult.Failed)
                {
                    Target = nullptr;
                    weapon = nullptr;
                    thinkTime = thinkTimeMax;
                    return res;
                }
                if(res == zombie.behaviors.Behavior.BehaviorResult.Succeeded)
                {
                    Target = nullptr;
                    weapon = nullptr;
                    thinkTime = 0;
                    return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
                }
            } else
            {
                timeout = 180;
                return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
            }
        }
        return zombie.behaviors.Behavior.BehaviorResult.Working;
    }
    public void reset()
    {
        Target = nullptr;
        weapon = nullptr;
        timeout = 180;
        pathFind.reset();
    }
    public bool valid()
    {
        return true;
    }
    public int thinkTime;
    public int thinkTimeMax;
    public bool stayInside;
    PathFindBehavior pathFind;
    IsoGameCharacter Target;
    InventoryItem weapon;
    int timeout;
}
} // namespace
