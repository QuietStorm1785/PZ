#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Sidebar.java
namespace zombie {
namespace ui {
#include "Keyboard.h"
#include "LuaEventManager.h"
#include "LuaHookManager.h"
#include "BodyDamage.h"
#include "IsoGameCharacter.h"
#include "IsoPlayer.h"
#include "NulledArrayList.h"
#include "Core.h"
#include "Texture.h"
#include "Mouse.h"
#include "InventoryItem.h"
#include "ItemContainer.h"
#include "Food.h"
#include "Literature.h"
#include "Item.h"
// Referenced classes of package zombie.ui:
//            UIElement, VirtualItemSlot, InventoryFlowControl, HUDButton, 
//            MovementBlender, ClothingPanel, NewHealthPanel, NewCraftingPanel, 
//            UIManager, SpeedControls, PZConsole
class Sidebar : public UIElement {
public:
{
    public Sidebar(int x, int y)
    {
        HeartOscilationLevel = 0.0F;
        HeartOscilator = 0.0F;
        HeartOscilatorDecelerator = 0.93F;
        HeartOscilatorRate = 0.8F;
        HeartOscilatorScalar = 15.6F;
        HeartOscilatorStartLevel = 1.0F;
        HeartOscilatorStep = 0.0F;
        HeartDefaultXOffset = 0.0F;
        bottom = nullptr;
        MainHand = new VirtualItemSlot("Main", 60, 10, "media/ui/HandMain_Off.png", IsoPlayer.getInstance());
        middle = nullptr;
        SecondHand = new VirtualItemSlot("Secondary", 60, 10, "media/ui/HandSecondary_Off.png", IsoPlayer.getInstance());
        top = nullptr;
        topRight = nullptr;
        wheel = 0;
        lastwheel = 0;
        instance = this;
        this.x = x;
        this.y = y;
        InventoryFlow = new InventoryFlowControl(10, 60, 1, 8, IsoPlayer.getInstance().getInventory());
        UpInv = new HUDButton("upInv", 18, 49, "media/ui/Inventory_UpArrow_Up.png", "media/ui/Inventory_UpArrow_Down.png", this);
        DownInv = new HUDButton("downInv", 18, 321, "media/ui/Inventory_DownArrow_Up.png", "media/ui/Inventory_DownArrow_Down.png", this);
        InventoryIcon = new HUDButton("Inventory", 0, 0, "media/ui/Inventory_Off.png", "media/ui/Inventory_On.png", this);
        Heart = new HUDButton("Heart", 0, 0, "media/ui/Heart_Off.png", "media/ui/Heart_On.png", this);
        Clothing = new HUDButton("Clothing", 0, 0, "media/ui/Stats_Off.png", "media/ui/Stats_On.png", this);
        Crafting = new HUDButton("Crafting", 0, 0, "media/ui/CraftButton_Up.png", "media/ui/CraftButton_Down.png", this);
        bottom = Texture.getSharedTexture("media/ui/SidePanel_Bottom.png");
        middle = Texture.getSharedTexture("media/ui/SidePanel_Middle.png");
        top = Texture.getSharedTexture("media/ui/SidePanel_Top.png");
        topRight = Texture.getSharedTexture("media/ui/SidePanel_TopRight.png");
        width = width;
        height = Core.getInstance().getOffscreenHeight();
        int mainX = 59;
        int mainY = 10;
        mainX += MainHand.width / 2;
        mainY += MainHand.height / 2;
        mainY += 42;
        SecondHand.x = mainX - SecondHand.width / 2;
        SecondHand.y = mainY - SecondHand.height / 2;
        mainY += 19;
        InventoryIcon.x = mainX - InventoryIcon.width / 2;
        InventoryIcon.y = mainY;
        mainY += 36;
        Heart.x = mainX - Heart.width / 2;
        Heart.y = mainY;
        mainY += 29;
        Clothing.x = mainX - Clothing.width / 2;
        Clothing.y = mainY;
        HeartDefaultXOffset = Heart.x;
        mainX--;
        mainY += 29;
        mainY += 38;
        AddChild(MainHand);
        AddChild(SecondHand);
        AddChild(InventoryIcon);
        AddChild(Heart);
        AddChild(Clothing);
        AddChild(InventoryFlow);
        Crafting.x = 8F;
        Crafting.y = DownInv.y + (float)DownInv.height + 10F;
        AddChild(Crafting);
        AddChild(UpInv);
        AddChild(DownInv);
        width = 115;
    }
    public void ButtonClicked(std::string name)
    {
        super.ButtonClicked(name);
        if("Clothing" == name))
        {
            ClothingPanel.instance.setVisible(!ClothingPanel.instance.isVisible());
            ClothingPanel.instance.setX(Clothing.getX() + 40F);
            ClothingPanel.instance.setY(Clothing.getY() - 70F);
        }
        if("Heart" == name))
            if(UIManager.getDragInventory() != nullptr)
            {
                LuaEventManager.TriggerEvent("OnUseItem", IsoPlayer.getInstance(), UIManager.getDragInventory());
                if(!LuaHookManager.TriggerHook("HookUseItem", IsoPlayer.getInstance(), UIManager.DragInventory))
                    if("PillsBeta" == UIManager.getDragInventory().getType()))
                    {
                        UIManager.getDragInventory().Use();
                        IsoPlayer.getInstance().BetaBlockers(0.3F);
                    } else
                    if("PillsAntiDep" == UIManager.getDragInventory().getType()))
                    {
                        UIManager.getDragInventory().Use();
                        IsoPlayer.getInstance().BetaAntiDepress(0.3F);
                    } else
                    if("PillsSleepingTablets" == UIManager.getDragInventory().getType()))
                    {
                        UIManager.getDragInventory().Use();
                        IsoPlayer.getInstance().SleepingTablet(0.5F);
                    } else
                    if("Pills" == UIManager.getDragInventory().getType()))
                    {
                        UIManager.getDragInventory().Use();
                        IsoPlayer.getInstance().PainMeds(0.3F);
                    } else
                    if(UIManager.getDragInventory() instanceof Food)
                    {
                        if(((Food)UIManager.getDragInventory()).isAlcoholic())
                        {
                            IsoPlayer.getInstance().Eat(UIManager.getDragInventory());
                            UIManager.getDragInventory().Use();
                            IsoPlayer.getInstance().SleepingTablet(0.02F);
                            IsoPlayer.getInstance().BetaAntiDepress(0.4F);
                            IsoPlayer.getInstance().BetaBlockers(0.2F);
                            IsoPlayer.getInstance().PainMeds(0.2F);
                            IsoPlayer.getInstance().getBodyDamage().JustDrankBooze();
                        } else
                        if(!"TinnedSoup" == UIManager.DragInventory.getType()))
                        {
                            Food TheFood = (Food)UIManager.getDragInventory();
                            NewHealthPanel.instance.ParentChar.Eat(UIManager.getDragInventory());
                            NewHealthPanel.instance.ParentChar.getBodyDamage().JustAteFood(TheFood);
                            UIManager.getDragInventory().Use();
                        }
                    } else
                    if(UIManager.getDragInventory() instanceof Literature)
                    {
                        NewHealthPanel.instance.ParentChar.getBodyDamage().JustReadSomething((Literature)UIManager.getDragInventory());
                        IsoPlayer.instance.getStats().stress -= UIManager.getDragInventory().getStressChange() / 100F;
                        UIManager.getDragInventory().Use();
                    }
            } else
            {
                NewHealthPanel.instance.setVisible(!NewHealthPanel.instance.isVisible());
                NewHealthPanel.instance.setX(Heart.getX() + 40F);
                NewHealthPanel.instance.setY(Heart.getY() - 70F);
            }
        if(name == "upInv"))
            InventoryFlow.startRow--;
        if(name == "downInv"))
            InventoryFlow.startRow++;
        if("Crafting" == name))
        {
            NewCraftingPanel.instance.setVisible(!NewCraftingPanel.instance.isVisible());
            NewCraftingPanel.instance.setX(Crafting.getX() + 60F);
            NewCraftingPanel.instance.setY(Crafting.getY() - 70F);
        }
        if("Inventory" == name))
            if(((MovementBlender)getParent()).getX() < -30F)
            {
                if(UIManager.getDragInventory() == nullptr)
                {
                    ((MovementBlender)getParent()).MoveTo(0.0F, 0.0F, 0.4F);
                } else
                {
                    if(IsoPlayer.getInstance().getCraftIngredient1() == UIManager.getDragInventory())
                        IsoPlayer.getInstance().setCraftIngredient1(nullptr);
                    if(IsoPlayer.getInstance().getCraftIngredient2() == UIManager.getDragInventory())
                        IsoPlayer.getInstance().setCraftIngredient2(nullptr);
                    if(IsoPlayer.getInstance().getCraftIngredient3() == UIManager.getDragInventory())
                        IsoPlayer.getInstance().setCraftIngredient3(nullptr);
                    if(IsoPlayer.getInstance().getCraftIngredient4() == UIManager.getDragInventory())
                        IsoPlayer.getInstance().setCraftIngredient4(nullptr);
                    if(IsoPlayer.getInstance().getClothingItem_Head() == UIManager.getDragInventory() && UIManager.getDragInventory() != nullptr)
                        IsoPlayer.getInstance().setClothingItem_Head(nullptr);
                    if(IsoPlayer.getInstance().getClothingItem_Torso() == UIManager.getDragInventory() && UIManager.getDragInventory() != nullptr)
                    {
                        IsoPlayer.getInstance().setClothingItem_Torso(nullptr);
                        IsoPlayer.getInstance().SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Top, nullptr, nullptr);
                    }
                    if(IsoPlayer.getInstance().getClothingItem_Hands() == UIManager.getDragInventory() && UIManager.getDragInventory() != nullptr)
                        IsoPlayer.getInstance().setClothingItem_Hands(nullptr);
                    if(IsoPlayer.getInstance().getClothingItem_Legs() == UIManager.getDragInventory() && UIManager.getDragInventory() != nullptr)
                    {
                        IsoPlayer.getInstance().setClothingItem_Legs(nullptr);
                        IsoPlayer.getInstance().SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Bottoms, nullptr, nullptr);
                    }
                    if(IsoPlayer.getInstance().getClothingItem_Feet() == UIManager.getDragInventory() && UIManager.getDragInventory() != nullptr)
                    {
                        IsoPlayer.getInstance().setClothingItem_Feet(nullptr);
                        IsoPlayer.getInstance().SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Shoes, nullptr, nullptr);
                    }
                    if(UIManager.getDragInventory() == MainHand.item)
                        IsoPlayer.getInstance().setPrimaryHandItem(nullptr);
                    if(UIManager.getDragInventory() == SecondHand.item)
                        IsoPlayer.getInstance().setSecondaryHandItem(nullptr);
                    if(UIManager.getDragInventory() == ClothingPanel.instance.HeadItem.item && UIManager.getDragInventory() != nullptr)
                        IsoPlayer.getInstance().setClothingItem_Head(nullptr);
                    if(UIManager.getDragInventory() == ClothingPanel.instance.TorsoItem.item && UIManager.getDragInventory() != nullptr)
                    {
                        IsoPlayer.getInstance().setClothingItem_Torso(nullptr);
                        IsoPlayer.getInstance().SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Top, nullptr, nullptr);
                    }
                    if(UIManager.getDragInventory() == ClothingPanel.instance.HandsItem.item)
                        IsoPlayer.getInstance().setClothingItem_Hands(nullptr);
                    if(UIManager.getDragInventory() == ClothingPanel.instance.LegsItem.item && UIManager.getDragInventory() != nullptr)
                    {
                        IsoPlayer.getInstance().setClothingItem_Legs(nullptr);
                        IsoPlayer.getInstance().SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Bottoms, nullptr, nullptr);
                    }
                    if(UIManager.getDragInventory() == ClothingPanel.instance.FeetItem.item && UIManager.getDragInventory() != nullptr)
                    {
                        IsoPlayer.getInstance().setClothingItem_Feet(nullptr);
                        IsoPlayer.getInstance().SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Shoes, nullptr, nullptr);
                    }
                    if(IsoPlayer.getInstance().getInventory() == UIManager.getDragInventory().getContainer())
                    {
                        UIManager.setDragInventory(nullptr);
                    } else
                    {
                        if(UIManager.getDragInventory().getContainer() != nullptr)
                        {
                            UIManager.getDragInventory().getContainer().Items.remove(UIManager.getDragInventory());
                            UIManager.getDragInventory().getContainer().dirty = true;
                        }
                        UIManager.getDragInventory().setContainer(IsoPlayer.getInstance().getInventory());
                        IsoPlayer.getInstance().getInventory().AddItem(UIManager.getDragInventory());
                        UIManager.setDragInventory(nullptr);
                    }
                }
            } else
            {
                if(UIManager.getDragInventory() != nullptr)
                {
                    if(UIManager.getDragInventory() == MainHand.item)
                        IsoPlayer.getInstance().setPrimaryHandItem(nullptr);
                    if(UIManager.getDragInventory() == SecondHand.item)
                        IsoPlayer.getInstance().setSecondaryHandItem(nullptr);
                    if(UIManager.getDragInventory() == ClothingPanel.instance.HeadItem.item)
                        IsoPlayer.getInstance().setClothingItem_Head(nullptr);
                    if(UIManager.getDragInventory() == ClothingPanel.instance.TorsoItem.item)
                    {
                        IsoPlayer.getInstance().setClothingItem_Torso(nullptr);
                        IsoPlayer.getInstance().SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Top, nullptr, nullptr);
                    }
                    if(UIManager.getDragInventory() == ClothingPanel.instance.HandsItem.item)
                        IsoPlayer.getInstance().setClothingItem_Hands(nullptr);
                    if(UIManager.getDragInventory() == ClothingPanel.instance.LegsItem.item)
                    {
                        IsoPlayer.getInstance().setClothingItem_Legs(nullptr);
                        IsoPlayer.getInstance().SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Bottoms, nullptr, nullptr);
                    }
                    if(UIManager.getDragInventory() == ClothingPanel.instance.FeetItem.item)
                    {
                        IsoPlayer.getInstance().setClothingItem_Feet(nullptr);
                        IsoPlayer.getInstance().SetClothing(zombie.scripting.objects.Item.ClothingBodyLocation.Shoes, nullptr, nullptr);
                    }
                }
                if(UIManager.getDragInventory() != nullptr && IsoPlayer.getInstance().getInventory() == UIManager.getDragInventory().getContainer())
                    UIManager.setDragInventory(nullptr);
                else
                if(UIManager.getDragInventory() != nullptr)
                {
                    if(UIManager.getDragInventory().getContainer() != nullptr)
                    {
                        UIManager.getDragInventory().getContainer().Items.remove(UIManager.getDragInventory());
                        UIManager.getDragInventory().getContainer().dirty = true;
                    }
                    UIManager.getDragInventory().setContainer(IsoPlayer.getInstance().getInventory());
                    IsoPlayer.getInstance().getInventory().AddItem(UIManager.getDragInventory());
                    UIManager.setDragInventory(nullptr);
                } else
                if(!Keyboard.isKeyDown(57))
                    ((MovementBlender)getParent()).MoveTo(-53F, 0.0F, 0.3F);
                setClickedValue(nullptr);
                UIManager.setDragInventory(nullptr);
            }
    }
    public bool onMouseDown(int x, int y)
    {
        super.onMouseDown(x, y);
        return x <= 53 || y <= 200;
    }
    public bool onMouseUp(int x, int y)
    {
        super.onMouseUp(x, y);
        return x <= 53 || y <= 200;
    }
    public void TriggerHeartWiggle()
    {
    }
    public void update()
    {
        if(SpeedControls.instance != nullptr && SpeedControls.instance.getCurrentGameSpeed() == 0)
            Crafting.setVisible(false);
        else
            Crafting.setVisible(true);
        if(IsoPlayer.getInstance() == nullptr || IsoPlayer.getInstance().isAsleep())
            return;
        super.update();
        HeartOscilatorStep += HeartOscilatorRate;
        HeartOscilator = (float)Math.sin(HeartOscilatorStep);
        float WiggleOffset = HeartOscilator * HeartOscilatorScalar * HeartOscilationLevel;
        HeartOscilationLevel *= HeartOscilatorDecelerator;
        Heart.setX(HeartDefaultXOffset + WiggleOffset);
        InventoryFlow.hTiles = (int)((float)Core.getInstance().getOffscreenHeight() - InventoryFlow.getY() - 100F) / 32;
        InventoryFlow.height = InventoryFlow.hTiles * 32;
        DownInv.setY(InventoryFlow.getY() + (float)InventoryFlow.getHeight() + 10F);
        Crafting.setY(DownInv.getY() + (float)DownInv.getHeight() + 10F);
        lastwheel = 0;
        wheel = Mouse.getWheelState();
        if(wheel != lastwheel)
        {
            InventoryFlow.startRow += wheel - lastwheel >= 0 ? -1 : 1;
            InventoryFlow.update();
        }
        if(InventoryFlow.Container.Items.size() - InventoryFlow.startRow <= InventoryFlow.hTiles)
            DownInv.setVisible(false);
        else
            DownInv.setVisible(true);
        if(InventoryFlow.startRow > 0)
            UpInv.setVisible(true);
        else
            UpInv.setVisible(false);
        if(!PZConsole.instance.isVisible() && Keyboard.isKeyDown(57) && ((MovementBlender)getParent()).getX() < -30F)
            ((MovementBlender)getParent()).MoveTo(0.0F, 0.0F, 0.4F);
    }
    public void render()
    {
        if(IsoPlayer.getInstance().isAsleep())
        {
            return;
        } else
        {
            int x = 0;
            int y = 0;
            DrawTexture(top, x, y, 0.8F);
            DrawTexture(topRight, x + top.getWidth(), y, 0.8F);
            y += top.getHeight();
            DrawTexture(middle, x, y, 0.8F);
            y += middle.getHeight();
            DrawTextureScaled(bottom, x, y, bottom.getWidth(), getHeight() - y, 0.8F);
            Integer weight = Integer.valueOf(IsoPlayer.getInstance().getInventory().getWeight());
            Integer maxWeight = Integer.valueOf(IsoPlayer.getInstance().getMaxWeight().intValue());
            DrawTextCentre("Weight", 26, 20, 1.0F, 1.0F, 1.0F, 1.0F);
            DrawTextCentre((new StringBuilder()).append(weight.toString()).append("/").append(maxWeight.toString()).toString(), 26, 30, (float)weight.intValue() / (float)maxWeight.intValue(), 1.0F - (float)weight.intValue() / (float)maxWeight.intValue(), 0.0F, 1.0F);
            super.render();
            return;
        }
    }
    private float HeartOscilationLevel;
    private float HeartOscilator;
    private float HeartOscilatorDecelerator;
    private float HeartOscilatorRate;
    private float HeartOscilatorScalar;
    private float HeartOscilatorStartLevel;
    private float HeartOscilatorStep;
    private float HeartDefaultXOffset;
    public static Sidebar instance = nullptr;
    public static HUDButton InventoryIcon;
    public static HUDButton Heart;
    public static HUDButton Clothing;
    public static HUDButton Crafting;
    public static HUDButton UpInv;
    public static HUDButton DownInv;
    Texture bottom;
    public InventoryFlowControl InventoryFlow;
    public VirtualItemSlot MainHand;
    Texture middle;
    public VirtualItemSlot SecondHand;
    Texture top;
    Texture topRight;
    int wheel;
    int lastwheel;
}
} // namespace
