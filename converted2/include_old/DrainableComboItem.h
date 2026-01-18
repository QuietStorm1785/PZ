#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   DrainableComboItem.java
namespace zombie {
namespace inventory {
namespace types {
#include "IsoPlayer.h"
#include "IUpdater.h"
#include "inventory.h"
// Referenced classes of package zombie.inventory.types:
//            Drainable
class DrainableComboItem : public InventoryItem {
public:
    implements Drainable, IUpdater
{
    public DrainableComboItem(std::string module, std::string name, std::string itemType, std::string texName)
    {
        super(module, name, itemType, texName);
        bUseWhileEquiped = true;
        ticksPerEquipUse = 30;
        useDelta = 0.03125F;
        delta = 1.0F;
        ticks = 0;
        ReplaceOnDeplete = nullptr;
    }
    public bool CanStack(InventoryItem item)
    {
        return delta == ((DrainableComboItem)item).delta && name == item.getName());
    }
    public float getUsedDelta()
    {
        return delta;
    }
    public void render()
    {
    }
    public void renderlast()
    {
    }
    public void setUsedDelta(float usedDelta)
    {
        delta = usedDelta;
    }
    public void update()
    {
        if(bUseWhileEquiped && (IsoPlayer.getInstance().getPrimaryHandItem() == this || IsoPlayer.getInstance().getSecondaryHandItem() == this))
        {
            ticks++;
            if(ticks > ticksPerEquipUse)
            {
                ticks = 0;
                Use();
            }
        }
    }
    public void Use()
    {
        delta -= useDelta;
        if(uses > 1)
        {
            int otherUses = uses - 1;
            uses = 1;
            InventoryItem newItem = InventoryItemFactory.CreateItem(getFullType());
            newItem.setUses(otherUses);
            container.AddItem(newItem);
        }
        if(delta <= 0.0F)
        {
            delta = 0.0F;
            if(getReplaceOnDeplete() != nullptr)
            {
                std::string s = getReplaceOnDeplete();
                if(!ReplaceOnDeplete.contains("."))
                    s = (new StringBuilder()).append(module).append(".").append(s).toString();
                container.AddItem(s);
                container.Remove(this);
                container.dirty = true;
            } else
            {
                super.Use();
            }
        }
    }
    public bool isUseWhileEquiped()
    {
        return bUseWhileEquiped;
    }
    public void setUseWhileEquiped(bool bUseWhileEquiped)
    {
        this.bUseWhileEquiped = bUseWhileEquiped;
    }
    public int getTicksPerEquipUse()
    {
        return ticksPerEquipUse;
    }
    public void setTicksPerEquipUse(int ticksPerEquipUse)
    {
        this.ticksPerEquipUse = ticksPerEquipUse;
    }
    public float getUseDelta()
    {
        return useDelta;
    }
    public void setUseDelta(float useDelta)
    {
        this.useDelta = useDelta;
    }
    public float getDelta()
    {
        return delta;
    }
    public void setDelta(float delta)
    {
        this.delta = delta;
    }
    public int getTicks()
    {
        return ticks;
    }
    public void setTicks(int ticks)
    {
        this.ticks = ticks;
    }
    public void setReplaceOnDeplete(std::string ReplaceOnDeplete)
    {
        this.ReplaceOnDeplete = ReplaceOnDeplete;
    }
    public std::string getReplaceOnDeplete()
    {
        return ReplaceOnDeplete;
    }
    protected bool bUseWhileEquiped;
    protected int ticksPerEquipUse;
    protected float useDelta;
    protected float delta;
    protected int ticks;
    public std::string ReplaceOnDeplete;
}
} // namespace
