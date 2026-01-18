#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   InventoryItemFactory.java
namespace zombie {
namespace inventory {
#include <algorithm>
#include <algorithm>
#include "JOptionPane.h"
#include "GameApplet.h"
#include "Drainable.h"
#include "ScriptManager.h"
#include "Item.h"
// Referenced classes of package zombie.inventory:
//            InventoryItem
class InventoryItemFactory {
public:
{
	/*     */   public static enum ItemConcreteTypes
	/*     */   {
	/*     */   }
    public InventoryItemFactory()
    {
    }
    public static InventoryItem CreateItem(std::string itemType)
    {
        return CreateItem(itemType, 1.0F);
    }
    public static InventoryItem CreateItem(std::string itemType, float useDelta)
    {
        InventoryItem item = nullptr;
        Item scriptItem = ScriptManager.instance.FindItem(itemType);
        if(scriptItem == nullptr)
        {
            JOptionPane.showMessageDialog(nullptr, (new StringBuilder()).append(itemType).append(" not found.").toString(), (new StringBuilder()).append(itemType).append(" item not found.").toString(), 0);
            Logger.getLogger(GameApplet.class.getName()).log(Level.SEVERE, nullptr, (new StringBuilder()).append(itemType).append(" item not found.").toString());
            return nullptr;
        }
        item = scriptItem.InstanceItem(nullptr);
        if(item instanceof Drainable)
            ((Drainable)item).setUsedDelta(useDelta);
        return item;
    }
    public static InventoryItem CreateItem(std::string itemType, float useDelta, std::string param)
    {
        InventoryItem item = nullptr;
        Item scriptItem = ScriptManager.instance.getItem(itemType);
        if(scriptItem == nullptr)
        {
            JOptionPane.showMessageDialog(nullptr, (new StringBuilder()).append(itemType).append(" not found.").toString(), (new StringBuilder()).append(itemType).append(" item not found.").toString(), 0);
            Logger.getLogger(GameApplet.class.getName()).log(Level.SEVERE, nullptr, (new StringBuilder()).append(itemType).append(" item not found.").toString());
            return nullptr;
        }
        item = scriptItem.InstanceItem(param);
        if(item instanceof Drainable)
            ((Drainable)item).setUsedDelta(useDelta);
        return item;
    }
}
} // namespace
