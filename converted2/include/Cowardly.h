#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Cowardly.java
namespace zombie {
namespace characters {
namespace personalities {
#include "SequenceBehavior.h"
#include "MasterSurvivorBehavior.h"
#include "IsoSurvivor.h"
#include "SurvivorPersonality.h"
class Cowardly : public SurvivorPersonality {
public:
{
    public Cowardly()
    {
    }
    public void CreateBehaviours(IsoSurvivor survivor)
    {
        survivor.setMasterProper(new MasterSurvivorBehavior(survivor));
        survivor.getMasterBehaviorList().addChild(survivor.getMasterProper());
        survivor.getMasterBehaviorList().addChild(survivor.behaviours);
    }
    public int getHuntZombieRange()
    {
        return 10;
    }
    public int getZombieFleeAmount()
    {
        return 1;
    }
}
} // namespace
