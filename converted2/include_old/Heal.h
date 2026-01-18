#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Heal.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace Needs {
#include <algorithm>
#include "EatFoodOrder.h"
#include "ObtainItem.h"
#include "OrderSequence.h"
#include "BodyDamage.h"
#include "IsoGameCharacter.h"
#include "MoodleType.h"
#include "Moodles.h"
#include "ItemContainer.h"
class Heal : public OrderSequence {
public:
{
    public Heal(IsoGameCharacter chr)
    {
        super(chr);
        Items = new Stack();
        obtain = nullptr;
        type = "Heal";
    }
    public void initOrder()
    {
        Items.add("Type:Food");
        if(character.getInventory().getBestFood(character.getDescriptor()) == nullptr)
        {
            obtain = new ObtainItem(character, Items, 1000);
            Orders.add(obtain);
        }
        Orders.add(new EatFoodOrder(character));
    }
    public bool isCritical()
    {
        return character.getMoodles().getMoodleLevel(MoodleType.Hungry) > 1 || character.getBodyDamage().getHealth() <= 60F;
    }
    public bool ActedThisFrame()
    {
        if(obtain != nullptr && Orders.get(ID) == obtain)
            return obtain.ActedThisFrame();
        else
            return false;
    }
    public Stack Items;
    ObtainItem obtain;
}
} // namespace
