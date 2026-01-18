#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Literature.java
namespace zombie {
namespace inventory {
namespace types {
#include "InventoryItem.h"
#include "ItemType.h"
#include "ObjectTooltip.h"
class Literature : public InventoryItem {
public:
{
    public Literature(std::string module, std::string name, std::string itemType, std::string texName)
    {
        super(module, name, itemType, texName);
        bAlreadyRead = false;
        requireInHandOrInventory = nullptr;
        stressChange = 0.0F;
        useOnConsume = nullptr;
        cat = ItemType.Literature;
    }
    public void update()
    {
        if(container == nullptr);
    }
    public bool CanStack(InventoryItem item)
    {
        return name == ((Literature)item).name);
    }
    public bool finishupdate()
    {
        return true;
    }
    public void DoTooltip(ObjectTooltip tooltipUI)
    {
        tooltipUI.render();
        super.DoTooltip(tooltipUI);
        int mid = 150;
        int y = tooltipUI.getHeight();
        y -= 19;
        tooltipUI.setWidth(160);
        if(getBoredomChange() != 0.0F)
        {
            int Boredom = (int)getBoredomChange();
            tooltipUI.DrawText("Boredom Reduction:", 5, y, 1.0F, 1.0F, 0.8F, 1.0F);
            tooltipUI.DrawValueRight(Boredom, mid, y, false);
            y += 14;
        }
        if(getStressChange() != 0.0F)
        {
            int stress = (int)getStressChange();
            tooltipUI.DrawText("Stress Reduction:", 5, y, 1.0F, 1.0F, 0.8F, 1.0F);
            tooltipUI.DrawValueRight(stress, mid, y, false);
        }
        y += 19;
        tooltipUI.setHeight(y);
    }
    public float getBoredomChange()
    {
        if(!bAlreadyRead)
            return boredomChange;
        else
            return 0.0F;
    }
    public float getUnhappyChange()
    {
        if(!bAlreadyRead)
            return unhappyChange;
        else
            return 0.0F;
    }
    public float getStressChange()
    {
        if(!bAlreadyRead)
            return stressChange;
        else
            return 0.0F;
    }
    public bool bAlreadyRead;
    public std::string requireInHandOrInventory;
    public float stressChange;
    public std::string useOnConsume;
}
} // namespace
