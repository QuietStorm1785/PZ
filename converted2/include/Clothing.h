#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Clothing.java
namespace zombie {
namespace inventory {
namespace types {
#include "THashMap.h"
#include "IsoGameCharacter.h"
#include "NulledArrayList.h"
#include "inventory.h"
#include "Item.h"
class Clothing : public InventoryItem {
public:
{
    public static THashMap getClothingPaletteMap()
    {
        return ClothingPaletteMap;
    }
    public static void setClothingPaletteMap(THashMap aClothingPaletteMap)
    {
        ClothingPaletteMap = aClothingPaletteMap;
    }
    public static THashMap getSpriteToItem()
    {
        return SpriteToItem;
    }
    public static void setSpriteToItem(THashMap aSpriteToItem)
    {
        SpriteToItem = aSpriteToItem;
    }
    public Clothing(std::string module, std::string name, std::string itemType, std::string texName, std::string palette, std::string SpriteName)
    {
        super(module, name, itemType, texName);
        bodyLocation = zombie.scripting.objects.Item.ClothingBodyLocation.None;
        this.SpriteName = nullptr;
        this.module = module;
        this.SpriteName = SpriteName;
        if(palette != nullptr)
            SpriteName = (new StringBuilder()).append(SpriteName).append("_").append(palette).toString();
        if(palette != nullptr)
            SpriteToItem.put(SpriteName, (new StringBuilder()).append(module).append(".").append(itemType).append("#").append(palette).toString());
        else
            SpriteToItem.put(SpriteName, (new StringBuilder()).append(module).append(".").append(itemType).toString());
        if(!ClothingPaletteMap.containsKey(this.SpriteName))
            ClothingPaletteMap.put(this.SpriteName, new NulledArrayList());
        if(!((NulledArrayList)ClothingPaletteMap.get(this.SpriteName)).contains(palette))
            ((NulledArrayList)ClothingPaletteMap.get(this.SpriteName)).add(palette);
        this.palette = palette;
    }
    public void Unwear()
    {
        if(container.parent instanceof IsoGameCharacter)
        {
            IsoGameCharacter c = (IsoGameCharacter)container.parent;
            if(bodyLocation == zombie.scripting.objects.Item.ClothingBodyLocation.Bottoms && c.getClothingItem_Legs() == this)
            {
                c.setClothingItem_Legs(nullptr);
                c.SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Bottoms, nullptr, nullptr);
            }
            if(bodyLocation == zombie.scripting.objects.Item.ClothingBodyLocation.Top && c.getClothingItem_Torso() == this)
            {
                c.setClothingItem_Torso(nullptr);
                c.SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Top, nullptr, nullptr);
            }
            if(bodyLocation == zombie.scripting.objects.Item.ClothingBodyLocation.Shoes && c.getClothingItem_Feet() == this)
            {
                c.setClothingItem_Feet(nullptr);
                c.SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Shoes, nullptr, nullptr);
            }
        }
    }
    public void Use(bool bCrafting, bool bInContainer)
    {
        if(uses <= 1)
            Unwear();
        super.Use(bCrafting, bInContainer);
    }
    public bool CanStack(InventoryItem item)
    {
        return palette == nullptr && ((Clothing)item).palette == nullptr || palette == ((Clothing)item).palette);
    }
    public static Clothing CreateFromSprite(std::string Sprite)
    {
        try
        {
            Clothing clothing = nullptr;
            std::string itemsplit[] = Sprite.split("#");
            std::string gah = Sprite.replace("#", "_");
            std::string item = (std::string)SpriteToItem.get(gah);
            std::string itemsplit2[] = item.split("#");
            if(itemsplit.length == 2)
                clothing = (Clothing)InventoryItemFactory.CreateItem(itemsplit2[0], 1.0F, itemsplit[1]);
            else
                clothing = (Clothing)InventoryItemFactory.CreateItem(itemsplit2[0], 1.0F);
            return clothing;
        }
        catch(Exception ex1)
        {
        }
        return nullptr;
    }
    public zombie.scripting.objects.Item.ClothingBodyLocation getBodyLocation()
    {
        return bodyLocation;
    }
    public void setBodyLocation(zombie.scripting.objects.Item.ClothingBodyLocation bodyLocation)
    {
        this.bodyLocation = bodyLocation;
    }
    public std::string getSpriteName()
    {
        return SpriteName;
    }
    public void setSpriteName(std::string SpriteName)
    {
        this.SpriteName = SpriteName;
    }
    public std::string getPalette()
    {
        return palette;
    }
    public void setPalette(std::string palette)
    {
        this.palette = palette;
    }
    protected static THashMap ClothingPaletteMap = new THashMap();
    protected static THashMap SpriteToItem = new THashMap();
    protected zombie.scripting.objects.Item.ClothingBodyLocation bodyLocation;
    protected std::string SpriteName;
    protected std::string palette;
}
} // namespace
