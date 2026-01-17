#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IdleOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
#include "Behavior.h"
#include "SatisfyIdleBehavior.h"
#include "IsoGameCharacter.h"
// Referenced classes of package zombie.behaviors.survivor.orders:
//            Order
class IdleOrder : public Order {
public:
{
    public IdleOrder(IsoGameCharacter chr)
    {
        super(chr);
        idle = new SatisfyIdleBehavior();
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        idle.process(nullptr, character);
        return zombie.behaviors.Behavior.BehaviorResult.Working;
    }
    public bool complete()
    {
        return false;
    }
    public void update()
    {
    }
    public float getPriority(IsoGameCharacter character)
    {
        return 200F;
    }
    SatisfyIdleBehavior idle;
}
} // namespace
