#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   GunNut.java
namespace zombie {
namespace characters {
namespace personalities {
#include "SequenceBehavior.h"
#include "MasterSurvivorBehavior.h"
#include "IsoSurvivor.h"
#include "SurvivorPersonality.h"
#include "HandWeapon.h"
class GunNut : public SurvivorPersonality {
public:
{
    public GunNut()
    {
    }
    public void CreateBehaviours(IsoSurvivor survivor)
    {
        survivor.setMasterProper(new MasterSurvivorBehavior(survivor));
        survivor.getMasterBehaviorList().addChild(survivor.getMasterProper());
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
