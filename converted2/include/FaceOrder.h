#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   FaceOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace LittleTasks {
#include "Behavior.h"
#include "Order.h"
#include "IsoGameCharacter.h"
#include "IsoDirections.h"
#include "Vector2.h"
class FaceOrder : public Order {
public:
{
    public FaceOrder(IsoGameCharacter chr, IsoDirections dir)
    {
        super(chr);
        vec = new Vector2();
        instantComplete = false;
        this.chr = chr;
        this.dir = dir;
        instantComplete = true;
    }
    public FaceOrder(IsoGameCharacter chr, IsoGameCharacter chr2)
    {
        super(chr);
        vec = new Vector2();
        instantComplete = false;
        this.chr = chr;
        this.chr2 = chr2;
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        if(chr2 == nullptr)
        {
            chr.dir = dir;
        } else
        {
            vec.x = chr2.getX();
            vec.y = chr2.getY();
            vec.x -= character.getX();
            vec.y -= character.getY();
            vec.normalize();
            character.DirectionFromVector(vec);
        }
        return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
    }
    public bool complete()
    {
        return instantComplete;
    }
    public void update()
    {
    }
    IsoGameCharacter chr;
    IsoGameCharacter chr2;
    IsoDirections dir;
    Vector2 vec;
    bool instantComplete;
}
} // namespace
