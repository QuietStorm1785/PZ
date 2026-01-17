#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   StopAndFaceForOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace LittleTasks {
#include "Behavior.h"
#include "Order.h"
#include "IsoGameCharacter.h"
#include "Rand.h"
#include "Vector2.h"
class StopAndFaceForOrder : public Order {
public:
{
    public StopAndFaceForOrder(IsoGameCharacter chr, IsoGameCharacter other, int ticks)
    {
        super(chr);
        delayticks = 0;
        vec = new Vector2();
        this.other = other;
        this.ticks = ticks;
        delayticks = Rand.Next(35) + 10;
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        if(delayticks > 0)
        {
            return processNext();
        } else
        {
            vec.x = other.getX();
            vec.y = other.getY();
            vec.x -= character.getX();
            vec.y -= character.getY();
            vec.normalize();
            character.DirectionFromVector(vec);
            return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
        }
    }
    public bool complete()
    {
        return ticks <= 0;
    }
    public void update()
    {
        if(delayticks <= 0)
        {
            ticks--;
        } else
        {
            delayticks--;
            updatenext();
        }
    }
    public float getPriority(IsoGameCharacter character)
    {
        return delayticks > 0 ? -100000F : 100000F;
    }
    IsoGameCharacter other;
    int ticks;
    int delayticks;
    Vector2 vec;
}
} // namespace
