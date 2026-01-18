#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   VirtualItemSlot.java
namespace zombie {
namespace ui {
#include "LuaCaller.h"
#include "KahluaTable.h"
#include "LuaManager.h"
#include "IsoGameCharacter.h"
#include "IsoPlayer.h"
#include "NulledArrayList.h"
#include "Color.h"
#include "Texture.h"
#include "inventory.h"
#include "types.h"
#include "Item.h"
// Referenced classes of package zombie.ui:
//            UIElement, SpeedControls, UIManager, NewCraftingPanel, 
//            Sidebar, ClothingPanel
class VirtualItemSlot : public UIElement {
public:
{
    public VirtualItemSlot(std::string type, int x, int y, std::string backgroundTex, IsoGameCharacter character)
    {
        alpha = 1.0F;
        index = 0;
        chr = character;
        this.type = type;
        tex = Texture.getSharedTexture(backgroundTex);
        this.x = x;
        this.y = y;
        width = tex.getWidth();
        height = tex.getHeight();
    }
    public bool onMouseDown(int x, int y)
    {
        if(!isVisible() || SpeedControls.instance.getCurrentGameSpeed() == 0)
            return true;
        super.onMouseDown(x, y);
        if(item != nullptr && UIManager.getDragInventory() == nullptr && type == "CraftingResult"))
        {
            UIManager.setDragInventory(IsoPlayer.getInstance().getInventory().AddItem(item));
            if(UIManager.getDragInventory() instanceof Drainable)
                ((Drainable)UIManager.getDragInventory()).setUsedDelta(((Drainable)item).getUsedDelta());
            NewCraftingPanel.instance.PerformMakeItem();
            return true;
        }
        if(UIManager.getDragInventory() != nullptr)
        {
            InventoryItem temp = UIManager.getDragInventory();
            if(type == "CraftingResult"))
            {
                if(item != nullptr && UIManager.getDragInventory().getType() == item.getType()) && item.CanStack(temp))
                {
                    std::string s = item.getType();
                    if(!s.contains("."))
                        s = (new StringBuilder()).append(temp.getModule()).append(".").append(item.getType()).toString();
                    InventoryItem tempa = InventoryItemFactory.CreateItem(s);
                    UIManager.getDragInventory().setUses(UIManager.getDragInventory().getUses() + tempa.getUses());
                    NewCraftingPanel.instance.PerformMakeItem();
                }
                return true;
            }
            if(type == "CraftingIngredient"))
            {
                int in = ExistsInOtherSlot(temp, index);
                if(in != -1)
                    chr.setCraftingByIndex(in, nullptr);
                if(temp.getContainer() == chr.getInventory())
                {
                    chr.setCraftingByIndex(index, temp);
                } else
                {
                    if(temp.getContainer() != nullptr)
                    {
                        temp.getContainer().Items.remove(temp);
                        temp.getContainer().dirty = true;
                    }
                    temp = chr.getInventory().AddItem(temp);
                    temp.setContainer(chr.getInventory());
                    chr.setCraftingByIndex(index, temp);
                }
                item = chr.getCraftingByIndex(index);
                UIManager.setDragInventory(nullptr);
            } else
            if(type == "Main"))
            {
                if(chr.getCraftIngredient1() == UIManager.getDragInventory())
                    chr.setCraftIngredient1(nullptr);
                if(chr.getCraftIngredient2() == UIManager.getDragInventory())
                    chr.setCraftIngredient2(nullptr);
                if(chr.getCraftIngredient3() == UIManager.getDragInventory())
                    chr.setCraftIngredient3(nullptr);
                if(chr.getCraftIngredient4() == UIManager.getDragInventory())
                    chr.setCraftIngredient4(nullptr);
                if(chr.getClothingItem_Head() == UIManager.getDragInventory())
                    chr.setClothingItem_Head(nullptr);
                if(chr.getClothingItem_Torso() == UIManager.getDragInventory())
                    chr.setClothingItem_Torso(nullptr);
                if(chr.getClothingItem_Hands() == UIManager.getDragInventory())
                    chr.setClothingItem_Hands(nullptr);
                if(chr.getClothingItem_Legs() == UIManager.getDragInventory())
                    chr.setClothingItem_Legs(nullptr);
                if(chr.getClothingItem_Feet() == UIManager.getDragInventory())
                    chr.setClothingItem_Feet(nullptr);
                if(chr.getSecondaryHandItem() == temp)
                {
                    item = chr.getPrimaryHandItem();
                    chr.setPrimaryHandItem(temp);
                    chr.setSecondaryHandItem(item);
                } else
                if(temp.getContainer() == chr.getInventory())
                {
                    chr.setPrimaryHandItem(temp);
                } else
                {
                    if(temp.getContainer() != nullptr)
                    {
                        temp.getContainer().Items.remove(temp);
                        temp.getContainer().dirty = true;
                    }
                    temp.setContainer(chr.getInventory());
                    chr.getInventory().AddItem(temp);
                    chr.setPrimaryHandItem(temp);
                }
                item = chr.getPrimaryHandItem();
                UIManager.setDragInventory(nullptr);
            } else
            if(type == "Secondary"))
            {
                if(chr.getCraftIngredient1() == UIManager.getDragInventory())
                    chr.setCraftIngredient1(nullptr);
                if(chr.getCraftIngredient2() == UIManager.getDragInventory())
                    chr.setCraftIngredient2(nullptr);
                if(chr.getCraftIngredient3() == UIManager.getDragInventory())
                    chr.setCraftIngredient3(nullptr);
                if(chr.getCraftIngredient4() == UIManager.getDragInventory())
                    chr.setCraftIngredient4(nullptr);
                if(chr.getClothingItem_Head() == UIManager.getDragInventory())
                    chr.setClothingItem_Head(nullptr);
                if(chr.getClothingItem_Torso() == UIManager.getDragInventory())
                    chr.setClothingItem_Torso(nullptr);
                if(chr.getClothingItem_Hands() == UIManager.getDragInventory())
                    chr.setClothingItem_Hands(nullptr);
                if(chr.getClothingItem_Legs() == UIManager.getDragInventory())
                    chr.setClothingItem_Legs(nullptr);
                if(chr.getClothingItem_Feet() == UIManager.getDragInventory())
                    chr.setClothingItem_Feet(nullptr);
                if(chr.getPrimaryHandItem() == temp)
                {
                    item = chr.getSecondaryHandItem();
                    chr.setSecondaryHandItem(temp);
                    chr.setPrimaryHandItem(item);
                } else
                if(temp.getContainer() == chr.getInventory())
                {
                    chr.setSecondaryHandItem(temp);
                } else
                {
                    if(temp.getContainer() != nullptr)
                    {
                        temp.getContainer().Items.remove(temp);
                        temp.getContainer().dirty = true;
                    }
                    temp.setContainer(chr.getInventory());
                    chr.getInventory().AddItem(temp);
                    chr.setSecondaryHandItem(temp);
                }
                item = chr.getSecondaryHandItem();
                UIManager.setDragInventory(nullptr);
            } else
            if(!type == "Head_Clothing"))
                if(type == "Torso_Clothing"))
                {
                    if((temp instanceof Clothing) && ((Clothing)temp).getBodyLocation() == zombie.scripting.objects.Item.ClothingBodyLocation.Top)
                    {
                        if(chr.getCraftIngredient1() == UIManager.getDragInventory())
                            chr.setCraftIngredient1(nullptr);
                        if(chr.getCraftIngredient2() == UIManager.getDragInventory())
                            chr.setCraftIngredient2(nullptr);
                        if(chr.getCraftIngredient3() == UIManager.getDragInventory())
                            chr.setCraftIngredient3(nullptr);
                        if(chr.getCraftIngredient4() == UIManager.getDragInventory())
                            chr.setCraftIngredient4(nullptr);
                        if(chr.getClothingItem_Head() == UIManager.getDragInventory())
                            chr.setClothingItem_Head(nullptr);
                        if(chr.getClothingItem_Hands() == UIManager.getDragInventory())
                            chr.setClothingItem_Hands(nullptr);
                        if(chr.getClothingItem_Legs() == UIManager.getDragInventory())
                            chr.setClothingItem_Legs(nullptr);
                        if(chr.getClothingItem_Feet() == UIManager.getDragInventory())
                            chr.setClothingItem_Feet(nullptr);
                        if(temp.getContainer() == chr.getInventory())
                        {
                            chr.setClothingItem_Torso(temp);
                            if(chr.getPrimaryHandItem() == temp)
                                chr.setPrimaryHandItem(nullptr);
                            if(chr.getSecondaryHandItem() == temp)
                                chr.setSecondaryHandItem(nullptr);
                            if(chr.getClothingItem_Head() == temp)
                                chr.setClothingItem_Head(nullptr);
                            if(chr.getClothingItem_Hands() == temp)
                                chr.setClothingItem_Hands(nullptr);
                            if(chr.getClothingItem_Legs() == temp)
                                chr.setClothingItem_Legs(nullptr);
                            if(chr.getClothingItem_Feet() == temp)
                                chr.setClothingItem_Feet(nullptr);
                            if(Sidebar.instance.MainHand.item == temp)
                                Sidebar.instance.MainHand.item = nullptr;
                            if(Sidebar.instance.SecondHand.item == temp)
                                Sidebar.instance.SecondHand.item = nullptr;
                            if(ClothingPanel.instance.HeadItem.item == temp)
                                ClothingPanel.instance.HeadItem.item = nullptr;
                            if(ClothingPanel.instance.HandsItem.item == temp)
                                ClothingPanel.instance.HandsItem.item = nullptr;
                            if(ClothingPanel.instance.LegsItem.item == temp)
                                ClothingPanel.instance.LegsItem.item = nullptr;
                            if(ClothingPanel.instance.FeetItem.item == temp)
                                ClothingPanel.instance.FeetItem.item = nullptr;
                        } else
                        {
                            if(temp.getContainer() != nullptr)
                            {
                                temp.getContainer().Items.remove(temp);
                                temp.getContainer().dirty = true;
                            }
                            temp.setContainer(chr.getInventory());
                            chr.getInventory().AddItem(temp);
                            chr.setClothingItem_Torso(temp);
                        }
                        item = chr.getClothingItem_Torso();
                        IsoPlayer.getInstance().SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Top, ((Clothing)item).getSpriteName(), ((Clothing)item).getPalette());
                        UIManager.setDragInventory(nullptr);
                    }
                } else
                if(!type == "Hands_Clothing"))
                    if(type == "Legs_Clothing"))
                    {
                        if((temp instanceof Clothing) && ((Clothing)temp).getBodyLocation() == zombie.scripting.objects.Item.ClothingBodyLocation.Bottoms)
                        {
                            if(chr.getCraftIngredient1() == UIManager.getDragInventory())
                                chr.setCraftIngredient1(nullptr);
                            if(chr.getCraftIngredient2() == UIManager.getDragInventory())
                                chr.setCraftIngredient2(nullptr);
                            if(chr.getCraftIngredient3() == UIManager.getDragInventory())
                                chr.setCraftIngredient3(nullptr);
                            if(chr.getCraftIngredient4() == UIManager.getDragInventory())
                                chr.setCraftIngredient4(nullptr);
                            if(chr.getClothingItem_Head() == UIManager.getDragInventory())
                                chr.setClothingItem_Head(nullptr);
                            if(chr.getClothingItem_Torso() == UIManager.getDragInventory())
                                chr.setClothingItem_Torso(nullptr);
                            if(chr.getClothingItem_Hands() == UIManager.getDragInventory())
                                chr.setClothingItem_Hands(nullptr);
                            if(chr.getClothingItem_Feet() == UIManager.getDragInventory())
                                chr.setClothingItem_Feet(nullptr);
                            if(temp.getContainer() == chr.getInventory())
                            {
                                chr.setClothingItem_Legs(temp);
                                if(chr.getPrimaryHandItem() == temp)
                                    chr.setPrimaryHandItem(nullptr);
                                if(chr.getSecondaryHandItem() == temp)
                                    chr.setSecondaryHandItem(nullptr);
                                if(chr.getClothingItem_Head() == temp)
                                    chr.setClothingItem_Head(nullptr);
                                if(chr.getClothingItem_Torso() == temp)
                                    chr.setClothingItem_Torso(nullptr);
                                if(chr.getClothingItem_Hands() == temp)
                                    chr.setClothingItem_Hands(nullptr);
                                if(chr.getClothingItem_Feet() == temp)
                                    chr.setClothingItem_Feet(nullptr);
                                if(Sidebar.instance.MainHand.item == temp)
                                    Sidebar.instance.MainHand.item = nullptr;
                                if(Sidebar.instance.SecondHand.item == temp)
                                    Sidebar.instance.SecondHand.item = nullptr;
                                if(ClothingPanel.instance.HeadItem.item == temp)
                                    ClothingPanel.instance.HeadItem.item = nullptr;
                                if(ClothingPanel.instance.TorsoItem.item == temp)
                                    ClothingPanel.instance.TorsoItem.item = nullptr;
                                if(ClothingPanel.instance.HandsItem.item == temp)
                                    ClothingPanel.instance.HandsItem.item = nullptr;
                                if(ClothingPanel.instance.FeetItem.item == temp)
                                    ClothingPanel.instance.FeetItem.item = nullptr;
                            } else
                            {
                                if(temp.getContainer() != nullptr)
                                {
                                    temp.getContainer().Items.remove(temp);
                                    temp.getContainer().dirty = true;
                                }
                                temp.setContainer(chr.getInventory());
                                chr.getInventory().AddItem(temp);
                                chr.setClothingItem_Legs(temp);
                            }
                            item = chr.getClothingItem_Legs();
                            IsoPlayer.getInstance().SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Bottoms, ((Clothing)item).getSpriteName(), ((Clothing)item).getPalette());
                            UIManager.setDragInventory(nullptr);
                        }
                    } else
                    if(type == "Feet_Clothing"))
                    {
                        if((temp instanceof Clothing) && ((Clothing)temp).getBodyLocation() == zombie.scripting.objects.Item.ClothingBodyLocation.Shoes)
                        {
                            if(chr.getCraftIngredient1() == UIManager.getDragInventory())
                                chr.setCraftIngredient1(nullptr);
                            if(chr.getCraftIngredient2() == UIManager.getDragInventory())
                                chr.setCraftIngredient2(nullptr);
                            if(chr.getCraftIngredient3() == UIManager.getDragInventory())
                                chr.setCraftIngredient3(nullptr);
                            if(chr.getCraftIngredient4() == UIManager.getDragInventory())
                                chr.setCraftIngredient4(nullptr);
                            if(chr.getClothingItem_Head() == UIManager.getDragInventory())
                                chr.setClothingItem_Head(nullptr);
                            if(chr.getClothingItem_Torso() == UIManager.getDragInventory())
                                chr.setClothingItem_Torso(nullptr);
                            if(chr.getClothingItem_Hands() == UIManager.getDragInventory())
                                chr.setClothingItem_Hands(nullptr);
                            if(chr.getClothingItem_Legs() == UIManager.getDragInventory())
                                chr.setClothingItem_Legs(nullptr);
                            if(temp.getContainer() == chr.getInventory())
                            {
                                chr.setClothingItem_Feet(temp);
                                if(chr.getPrimaryHandItem() == temp)
                                    chr.setPrimaryHandItem(nullptr);
                                if(chr.getSecondaryHandItem() == temp)
                                    chr.setSecondaryHandItem(nullptr);
                                if(chr.getClothingItem_Head() == temp)
                                    chr.setClothingItem_Head(nullptr);
                                if(chr.getClothingItem_Torso() == temp)
                                    chr.setClothingItem_Torso(nullptr);
                                if(chr.getClothingItem_Hands() == temp)
                                    chr.setClothingItem_Hands(nullptr);
                                if(chr.getClothingItem_Legs() == temp)
                                    chr.setClothingItem_Legs(nullptr);
                                if(Sidebar.instance.MainHand.item == temp)
                                    Sidebar.instance.MainHand.item = nullptr;
                                if(Sidebar.instance.SecondHand.item == temp)
                                    Sidebar.instance.SecondHand.item = nullptr;
                                if(ClothingPanel.instance.HeadItem.item == temp)
                                    ClothingPanel.instance.HeadItem.item = nullptr;
                                if(ClothingPanel.instance.TorsoItem.item == temp)
                                    ClothingPanel.instance.TorsoItem.item = nullptr;
                                if(ClothingPanel.instance.HandsItem.item == temp)
                                    ClothingPanel.instance.HandsItem.item = nullptr;
                                if(ClothingPanel.instance.LegsItem.item == temp)
                                    ClothingPanel.instance.LegsItem.item = nullptr;
                            } else
                            {
                                if(temp.getContainer() != nullptr)
                                {
                                    temp.getContainer().Items.remove(temp);
                                    temp.getContainer().dirty = true;
                                }
                                temp.setContainer(chr.getInventory());
                                chr.getInventory().AddItem(temp);
                                chr.setClothingItem_Feet(temp);
                            }
                            item = chr.getClothingItem_Feet();
                            IsoPlayer.getInstance().SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Shoes, ((Clothing)item).getSpriteName(), ((Clothing)item).getPalette());
                            UIManager.setDragInventory(nullptr);
                        }
                    } else
                    if(UIManager.getDragInventory() != nullptr)
                    {
                        item = UIManager.getDragInventory();
                        Object o[];
                        if(getTable() != nullptr && getTable().rawget("onPlaceItem") != nullptr)
                            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onPlaceItem"), new Object[] {
                                table, item
                            });
                        UIManager.setDragInventory(nullptr);
                    }
        } else
        {
            if(type == "Main"))
                item = chr.getPrimaryHandItem();
            else
            if(type == "Secondary"))
                item = chr.getSecondaryHandItem();
            else
            if(type == "Head_Clothing"))
                item = chr.getClothingItem_Head();
            else
            if(type == "Torso_Clothing"))
                item = chr.getClothingItem_Torso();
            else
            if(type == "Hands_Clothing"))
                item = chr.getClothingItem_Hands();
            else
            if(type == "Legs_Clothing"))
                item = chr.getClothingItem_Legs();
            else
            if(type == "Feet_Clothing"))
                item = chr.getClothingItem_Feet();
            UIManager.setDragInventory(item);
        }
        return true;
    }
    public void render()
    {
        if(type == "CraftingIngredient"))
            item = chr.getCraftingByIndex(index);
        else
        if(type == "Main"))
        {
            if(chr.getPrimaryHandItem() != nullptr && chr.getInventory() != chr.getPrimaryHandItem().getContainer())
                chr.setPrimaryHandItem(nullptr);
            item = chr.getPrimaryHandItem();
        } else
        if(type == "Secondary"))
        {
            if(chr.getSecondaryHandItem() != nullptr && chr.getInventory() != chr.getSecondaryHandItem().getContainer())
                chr.setSecondaryHandItem(nullptr);
            item = chr.getSecondaryHandItem();
        } else
        if(type == "Head_Clothing"))
        {
            if(chr.getClothingItem_Head() != nullptr && chr.getInventory() != chr.getClothingItem_Head().getContainer())
                chr.setClothingItem_Head(nullptr);
            item = chr.getClothingItem_Head();
        } else
        if(type == "Torso_Clothing"))
        {
            if(chr.getClothingItem_Torso() != nullptr && chr.getInventory() != chr.getClothingItem_Torso().getContainer())
                chr.setClothingItem_Torso(nullptr);
            item = chr.getClothingItem_Torso();
        } else
        if(type == "Hands_Clothing"))
        {
            if(chr.getClothingItem_Hands() != nullptr && chr.getInventory() != chr.getClothingItem_Hands().getContainer())
                chr.setClothingItem_Hands(nullptr);
            item = chr.getClothingItem_Hands();
        } else
        if(type == "Legs_Clothing"))
        {
            if(chr.getClothingItem_Legs() != nullptr && chr.getInventory() != chr.getClothingItem_Legs().getContainer())
                chr.setClothingItem_Legs(nullptr);
            item = chr.getClothingItem_Legs();
        } else
        if(type == "Feet_Clothing"))
        {
            if(chr.getClothingItem_Feet() != nullptr && chr.getInventory() != chr.getClothingItem_Feet().getContainer())
                chr.setClothingItem_Feet(nullptr);
            item = chr.getClothingItem_Feet();
        }
        if(tex != nullptr)
        {
            DrawTexture(tex, 0, 0, alpha);
            if(item != nullptr)
            {
                if(item instanceof Food)
                {
                    float temp = ((Food)item).getHeat();
                    bool red = false;
                    if(temp > 1.0F)
                        temp--;
                    Color C = new Color(70, 153, 211);
                    Color H = new Color(222, 70, 70);
                    Color G = new Color(162, 162, 162);
                }
                if(UIManager.getDragInventory() == item)
                    DrawTextureCol(item.getTex(), tex.getWidth() / 2 - 16, tex.getHeight() / 2 - 16, new Color(255, 255, 255, (byte)(int)(128F * alpha)));
                else
                    DrawTexture(item.getTex(), tex.getWidth() / 2 - 16, tex.getHeight() / 2 - 16, alpha);
                if(item instanceof Drainable)
                {
                    int wid = (int)(24F * ((Drainable)item).getUsedDelta());
                    DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), tex.getWidth() / 2 - 13, tex.getHeight() - 13, 26, 4, new Color(0, 0, 0, 255));
                    DrawTextureScaledCol(Texture.getSharedTexture("media/white.png"), (1 + tex.getWidth() / 2) - 13, (1 + tex.getHeight()) - 13, wid, 2, new Color(64, 150, 32, 255));
                }
                if(item instanceof HandWeapon)
                {
                    Integer n = Integer.valueOf((int)(((float)((HandWeapon)item).getCondition() / (float)((HandWeapon)item).getConditionMax()) * 5F));
                    if(item.getCondition() > 0 && n.intValue() == 0)
                        n = Integer.valueOf(1);
                    std::string str = (new StringBuilder()).append("media/ui/QualityStar_").append(n).append(".png").toString();
                    DrawTextureScaledCol(Texture.getSharedTexture(str), 1 + (tex.getWidth() / 2 - 16), 20 + (tex.getHeight() / 2 - 16), 11, 12, new Color(255, 255, 255, 255));
                }
                if(item.getUses() > 1)
                    DrawTextRight((new StringBuilder()).append("x").append((new Integer(item.getUses())).toString()).toString(), (tex.getWidth() / 2 - 16) + 32, tex.getHeight() / 2 - 16, 1.0F, 1.0F, 1.0F, 1.0F);
            }
        }
        super.render();
    }
    private int ExistsInOtherSlot(InventoryItem temp, int index)
    {
        for(int n = 0; n < 4; n++)
        {
            if(n == index)
                continue;
            InventoryItem test = nullptr;
            if(n == 0)
                test = chr.getCraftIngredient1();
            if(n == 1)
                test = chr.getCraftIngredient2();
            if(n == 2)
                test = chr.getCraftIngredient3();
            if(n == 3)
                test = chr.getCraftIngredient4();
            if(test == temp)
                return n;
        }
        return -1;
    }
    public float alpha;
    public int index;
    public IsoGameCharacter chr;
    InventoryItem item;
    Texture tex;
    std::string type;
}
} // namespace
