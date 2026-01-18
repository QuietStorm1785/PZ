#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Kate.java
namespace zombie {
namespace characters {
namespace personalities {
#include "IsoSurvivor.h"
#include "SurvivorPersonality.h"
class Kate : public SurvivorPersonality {
public:
{
    public Kate()
    {
    }
    public void CreateBehaviours(IsoSurvivor isosurvivor)
    {
    }
    public int getHuntZombieRange()
    {
        return 20;
    }
}
} // namespace
