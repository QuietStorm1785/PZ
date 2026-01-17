#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   CraftItemOrder.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace LittleTasks {
#include <vector>
#include "Behavior.h"
#include "Order.h"
#include "IsoGameCharacter.h"
#include "inventory.h"
#include "Drainable.h"
#include "Recipe.h"
#include "ScriptModule.h"
class CraftItemOrder : public Order {
public:
{
    public CraftItemOrder(IsoGameCharacter chr, Recipe rec)
    {
        super(chr);
        this.chr = chr;
        this.rec = rec;
    }
    public zombie.behaviors.Behavior.BehaviorResult process()
    {
        return zombie.behaviors.Behavior.BehaviorResult.Succeeded;
    }
    public void initOrder()
    {
        PerformMakeItem();
    }
    public bool complete()
    {
        return true;
    }
    public void update()
    {
    }
    void DoDrainOnItem(InventoryItem ing1, std::string resType)
    {
        if(RecipeManager.DoesWipeUseDelta(ing1.getType(), resType))
            ((Drainable)ing1).setUsedDelta(0.0F);
        if(RecipeManager.DoesUseItemUp(ing1.getType(), rec))
        {
            int size = RecipeManager.UseAmount(ing1.getType(), rec);
            for(int n = 0; n < size; n++)
                ing1.Use(true);
        }
    }
    void PerformMakeItem()
    {
        InventoryItem ing1 = nullptr;
        if(((zombie.scripting.objects.Recipe.Source)rec.Source.get(0)).type != nullptr)
        {
            ing1 = character.getInventory().FindAndReturn(((zombie.scripting.objects.Recipe.Source)rec.Source.get(0)).type);
            if(ing1 == nullptr)
                return;
            DoDrainOnItem(ing1, rec.Result.type);
        }
        if(rec.Source.size() > 1 && ((zombie.scripting.objects.Recipe.Source)rec.Source.get(1)).type != nullptr)
        {
            ing1 = character.getInventory().FindAndReturn(((zombie.scripting.objects.Recipe.Source)rec.Source.get(1)).type);
            if(ing1 == nullptr)
                return;
            DoDrainOnItem(ing1, rec.Result.type);
        }
        if(rec.Source.size() > 2 && ((zombie.scripting.objects.Recipe.Source)rec.Source.get(2)).type != nullptr)
        {
            ing1 = character.getInventory().FindAndReturn(((zombie.scripting.objects.Recipe.Source)rec.Source.get(2)).type);
            if(ing1 == nullptr)
                return;
            DoDrainOnItem(ing1, rec.Result.type);
        }
        if(rec.Source.size() > 3 && ((zombie.scripting.objects.Recipe.Source)rec.Source.get(3)).type != nullptr)
        {
            ing1 = character.getInventory().FindAndReturn(((zombie.scripting.objects.Recipe.Source)rec.Source.get(3)).type);
            if(ing1 == nullptr)
                return;
            DoDrainOnItem(ing1, rec.Result.type);
        }
        character.getInventory().AddItem((new StringBuilder()).append(rec.module.name).append(".").append(rec.Result.type).toString());
    }
    IsoGameCharacter chr;
    Recipe rec;
}
} // namespace
