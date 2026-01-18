#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Barricade.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace LittleTasks {
#include <algorithm>
#include "Behavior.h"
#include "Order.h"
#include "BarricadeAction.h"
#include "IsoGameCharacter.h"
#include "IsoDoor.h"
class Barricade : public Order {
public:
{
    public Barricade(IsoGameCharacter chr, IsoDoor door)
    {
        super(chr);
        this.door = nullptr;
        level = 2;
        this.door = door;
        this.chr = chr;
    }
    public bool complete()
    {
        return door.Barricaded >= level;
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        if(chr.getCharacterActions().isEmpty() && door.Barricaded < level)
            chr.StartAction(new BarricadeAction(chr, door));
        if(door.Barricaded >= level)
            return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
        else
            return zombie.behaviors.Behavior.BehaviorResult.Working;
    }
    public void update()
    {
    }
    IsoDoor door;
    IsoGameCharacter chr;
    int level;
}
} // namespace
