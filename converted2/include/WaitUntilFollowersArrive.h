#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   WaitUntilFollowersArrive.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include "Behavior.h"
#include "SatisfyIdleBehavior.h"
#include "characters.h"
#include "NulledArrayList.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            Order, FollowOrder
class WaitUntilFollowersArrive : public Order {
public:
{
    public WaitUntilFollowersArrive(IsoGameCharacter chr)
    {
        super(chr);
        timeout = 600;
        idle = new SatisfyIdleBehavior();
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        idle.process(nullptr, character);
        timeout--;
        return zombie.behaviors.Behavior.BehaviorResult.Working;
    }
    public bool complete()
    {
        if(timeout <= 0)
            return true;
        for(int n = 0; n < character.getDescriptor().getGroup().Members.size(); n++)
        {
            SurvivorDesc desc = (SurvivorDesc)character.getDescriptor().getGroup().Members.get(n);
            if(desc.getInstance() != nullptr && desc.getInstance() != character && !desc.getInstance().isDead() && (desc.getInstance().getOrder() instanceof FollowOrder) && ((FollowOrder)desc.getInstance().getOrder()).target == character && !desc.getInstance().InBuildingWith(character))
                return false;
        }
        return true;
    }
    public void update()
    {
    }
    SatisfyIdleBehavior idle;
    int timeout;
}
} // namespace
