#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   CloseDoor.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace LittleTasks {
#include "Behavior.h"
#include "Order.h"
#include "IsoGameCharacter.h"
#include "IsoDoor.h"
class CloseDoor : public Order {
public:
{
    public CloseDoor(IsoGameCharacter chr, IsoDoor door)
    {
        super(chr);
        this.door = nullptr;
        this.door = door;
        this.chr = chr;
    }
    public bool complete()
    {
        if(door == nullptr)
            return true;
        else
            return !door.open;
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        if(door != nullptr && door.open)
            door.ToggleDoor(chr);
        return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
    }
    public void update()
    {
    }
    IsoDoor door;
    IsoGameCharacter chr;
}
} // namespace
