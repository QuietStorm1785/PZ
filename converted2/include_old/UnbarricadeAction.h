#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   UnbarricadeAction.java
namespace zombie {
namespace characters {
namespace CharacterTimedActions {
#include "SoundManager.h"
#include "IsoGameCharacter.h"
#include "IsoPlayer.h"
#include "PerkFactory.h"
#include "ItemContainer.h"
#include "IsoDoor.h"
#include "IsoWindow.h"
// Referenced classes of package zombie.characters.CharacterTimedActions:
//            BaseAction
class UnbarricadeAction : public BaseAction {
public:
{
    public UnbarricadeAction(IsoGameCharacter chr, IsoDoor door)
    {
        super(chr);
        this.door = nullptr;
        window = nullptr;
        this.door = door;
        MaxTime = 90 * door.Barricaded;
        if(chr.HasTrait("Handy"))
            MaxTime *= 0.5D;
        MaxTime *= chr.getBarricadeTimeMod();
    }
    public UnbarricadeAction(IsoGameCharacter chr, IsoWindow window)
    {
        super(chr);
        door = nullptr;
        this.window = nullptr;
        this.window = window;
        MaxTime = 90 * window.Barricaded;
        if(chr.HasTrait("Handy"))
            MaxTime *= 0.5D;
        MaxTime *= chr.getBarricadeTimeMod();
    }
    public bool valid()
    {
        return chr.getInventory().contains("Hammer") && (window != nullptr && window.Barricaded > 0 || door != nullptr && door.Barricaded > 0);
    }
    public void start()
    {
        SoundEffect = SoundManager.instance.PlayWorldSound("crackwood", true, IsoPlayer.getInstance().getCurrentSquare(), 0.2F, 10F, 0.4F, true);
    }
    public void perform()
    {
        if(door != nullptr)
        {
            door.Unbarricade(chr);
            chr.getXp().AddXP(zombie.characters.skills.PerkFactory.Perks.Woodwork, 2);
            chr.getXp().AddXP(zombie.characters.skills.PerkFactory.Perks.Strength, 2);
        }
        if(window != nullptr)
        {
            window.Unbarricade(chr);
            chr.getXp().AddXP(zombie.characters.skills.PerkFactory.Perks.Woodwork, 5);
            chr.getXp().AddXP(zombie.characters.skills.PerkFactory.Perks.Strength, 2);
        }
    }
    IsoDoor door;
    IsoWindow window;
}
} // namespace
