#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   FriendlyArmed.java
namespace zombie {
namespace characters {
namespace personalities {
#include "behaviors.h"
#include "FollowBehaviour.h"
#include "survivor.h"
#include "IsoSurvivor.h"
#include "SurvivorPersonality.h"
#include "HandWeapon.h"
class FriendlyArmed : public SurvivorPersonality {
public:
{
    public FriendlyArmed()
    {
    }
    public int getZombieFleeAmount()
    {
        return 10;
    }
    public void CreateBehaviours(IsoSurvivor survivor)
    {
        survivor.getMasterBehaviorList().addChild(new ObeyOrders(survivor));
        survivor.behaviours.AddTrigger("IdleBoredom", 0.0F, 0.6F, 1E-006F, new SatisfyIdleBehavior());
        survivor.getMasterBehaviorList().addChild(new FleeBehaviour());
        FollowBehaviour fol = new FollowBehaviour();
        AttackBehavior att = new AttackBehavior();
        survivor.getMasterBehaviorList().addChild(att);
        att.process(nullptr, survivor);
        if(survivor.getPrimaryHandItem() != nullptr)
        {
            zombie.inventory.InventoryItem attackItem = survivor.getPrimaryHandItem();
            if(attackItem instanceof HandWeapon)
                survivor.setUseHandWeapon((HandWeapon)attackItem);
        }
        survivor.getMasterBehaviorList().addChild(survivor.behaviours);
    }
    public int getHuntZombieRange()
    {
        return 10;
    }
}
} // namespace
