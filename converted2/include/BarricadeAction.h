#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   BarricadeAction.java
namespace zombie {
namespace characters {
namespace CharacterTimedActions {
#include "SoundManager.h"
#include "WorldSoundManager.h"
#include "IsoGameCharacter.h"
#include "PerkFactory.h"
#include "InventoryItem.h"
#include "ItemContainer.h"
#include "IsoGridSquare.h"
#include "IsoDoor.h"
#include "IsoWindow.h"
#include "TutorialManager.h"
// Referenced classes of package zombie.characters.CharacterTimedActions:
//            BaseAction
class BarricadeAction : public BaseAction {
public:
{
    public BarricadeAction(IsoGameCharacter chr, IsoDoor door)
    {
        super(chr);
        this.door = nullptr;
        window = nullptr;
        this.door = door;
        MaxTime = 70;
        if(chr.HasTrait("Handy"))
            MaxTime = 35;
        MaxTime *= chr.getBarricadeTimeMod();
    }
    public BarricadeAction(IsoGameCharacter chr, IsoWindow window)
    {
        super(chr);
        door = nullptr;
        this.window = nullptr;
        this.window = window;
        MaxTime = 70;
        if(chr.HasTrait("Handy"))
            MaxTime = 35;
        MaxTime *= chr.getBarricadeTimeMod();
    }
    public bool valid()
    {
        InventoryItem item = chr.getInventory().getBestCondition("Plank");
        return chr.getInventory().contains("Nails") && item != nullptr && chr.hasEquipped("Hammer") && (window != nullptr && window.Barricaded <= 3 || door != nullptr && door.Barricaded <= 3);
    }
    public void start()
    {
        SoundEffect = SoundManager.instance.PlayWorldSound("hammernail", true, chr.getCurrentSquare(), 0.2F, 10F, 0.4F * chr.getHammerSoundMod(), true);
        int rad = 40;
        rad = (int)((float)rad * chr.getHammerSoundMod());
        if(door != nullptr)
            WorldSoundManager.instance.addSound(door, door.square.getX(), door.square.getY(), door.square.getZ(), rad, rad);
        else
            WorldSoundManager.instance.addSound(window, window.square.getX(), window.square.getY(), window.square.getZ(), rad, rad);
        if(door != nullptr && door.open)
            door.ToggleDoor(chr);
    }
    public void perform()
    {
        if(door != nullptr)
        {
            InventoryItem item = chr.getInventory().getBestCondition("Plank");
            if(item != nullptr)
            {
                door.Barricade(chr, item);
                TutorialManager.instance.BarricadeCount++;
                if(item.getUses() > 1)
                    item.setUses(item.getUses() - 1);
                else
                    chr.getInventory().Remove(item);
                chr.getInventory().RemoveOneOf("Nails");
                chr.getXp().AddXP(zombie.characters.skills.PerkFactory.Perks.Woodwork, 5);
            }
        }
        if(window != nullptr)
        {
            InventoryItem item = chr.getInventory().getBestCondition("Plank");
            if(item != nullptr)
            {
                window.Barricade(item);
                TutorialManager.instance.BarricadeCount++;
                if(item.getUses() > 1)
                    item.setUses(item.getUses() - 1);
                else
                    chr.getInventory().Remove(item);
                chr.getInventory().RemoveOneOf("Nails");
                chr.getXp().AddXP(zombie.characters.skills.PerkFactory.Perks.Woodwork, 5);
            }
        }
    }
    IsoDoor door;
    IsoWindow window;
}
} // namespace
