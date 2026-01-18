#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   RandomBehavior.java
namespace zombie {
namespace behaviors {
#include "IsoGameCharacter.h"
#include "NulledArrayList.h"
#include "Rand.h"
// Referenced classes of package zombie.behaviors:
//            Behavior, DecisionPath
class RandomBehavior : public Behavior {
public:
{
    public RandomBehavior()
    {
    }
    public Behavior.BehaviorResult process(DecisionPath path, IsoGameCharacter character)
    {
        return processChild(path, character, Rand.Next(childNodes.size()));
    }
    public void reset()
    {
    }
    public bool valid()
    {
        return true;
    }
}
} // namespace
