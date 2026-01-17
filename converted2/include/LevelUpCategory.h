#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   LevelUpCategory.java
namespace zombie {
namespace ui {
#include "THashMap.h"
#include <vector>
#include <vector>
#include "IsoPlayer.h"
#include "PerkFactory.h"
#include "NulledArrayList.h"
#include "Color.h"
#include "Texture.h"
// Referenced classes of package zombie.ui:
//            UIElement, PerkButton, UIEventHandler, UIFont, 
//            UIManager, LevelUpScreen
class LevelUpCategory : public UIElement {
public:
    implements UIEventHandler
{
    public void reset()
    {
        if(white == nullptr)
            white = Texture.getSharedTexture("white.png");
        subPerks.clear();
        getControls().clear();
        this.perk = (zombie.characters.skills.PerkFactory.Perk)PerkFactory.PerkMap.get(perkType);
        setWidth(800);
        setHeight(80);
        for(int n = 0; n < PerkFactory.PerkList.size(); n++)
        {
            zombie.characters.skills.PerkFactory.Perk perk = (zombie.characters.skills.PerkFactory.Perk)PerkFactory.PerkList.get(n);
            if(perk.parent == perkType)
                subPerks.add(perk);
        }
        perkbuttons = new PerkButton[subPerks.size()][5];
        for(int n = 0; n < subPerks.size(); n++)
        {
            for(int x = 0; x < 5; x++)
            {
                bool bAvailable = IsoPlayer.getInstance().getCanUpgradePerk().contains(((zombie.characters.skills.PerkFactory.Perk)subPerks.get(n)).type);
                int level = IsoPlayer.getInstance().getPerkLevel(((zombie.characters.skills.PerkFactory.Perk)subPerks.get(n)).type);
                if(x > level)
                    bAvailable = false;
                if(IsoPlayer.getInstance().getNumberOfPerksToPick() <= 0)
                    bAvailable = false;
                bool bHas = level > x;
                perkbuttons[n][x] = new PerkButton(((zombie.characters.skills.PerkFactory.Perk)subPerks.get(n)).name, 0, 0, white, bAvailable, bHas, this);
                perkbuttons[n][x].setWidth(16);
                perkbuttons[n][x].setHeight(16);
                AddChild(perkbuttons[n][x]);
            }
        }
    }
    public LevelUpCategory(zombie.characters.skills.PerkFactory.Perks mainPerk)
    {
        subPerks = new ArrayList();
        perkType = mainPerk;
        reset();
    }
    public void render()
    {
        DrawTextureScaledCol(white, 0, 0, getWidth(), getHeight(), new Color(0.3F, 0.3F, 0.3F, 0.2F));
        DrawTextureScaledCol(white, 0, 0, 172, getHeight(), new Color(0.3F, 0.3F, 0.3F, 0.2F));
        DrawText(UIFont.Large, this.perk.name.toUpperCase(), 64, getHeight() / 2 - 12, 1.0F, 1.0F, 1.0F, 1.0F);
        int x = 288;
        int y = 20;
        for(int n = 0; n < subPerks.size(); n++)
        {
            zombie.characters.skills.PerkFactory.Perk perk = (zombie.characters.skills.PerkFactory.Perk)subPerks.get(n);
            DrawTextRight(UIFont.Small, perk.name.toUpperCase(), x + 3, y, 1.0F, 1.0F, 1.0F, 1.0F);
            int x2 = x + 8;
            for(int q = 0; q < 5; q++)
            {
                perkbuttons[n][q].setX(x2 + 5);
                perkbuttons[n][q].setY(y - 3);
                x2 += 17;
            }
            if((y += 30) > getHeight() - 24)
            {
                y = 20;
                x += 192;
            }
        }
        DrawTextureScaledCol(white, 0, 78, getWidth(), 1, new Color(0.2F, 0.2F, 0.2F, 0.8F));
        DrawTextureScaledCol(white, 0, 79, getWidth(), 1, new Color(0.0F, 0.0F, 0.0F, 1.0F));
        super.render();
    }
    public void DoubleClick(std::string s, int i, int j)
    {
    }
    public void ModalClick(std::string name, std::string chosen)
    {
        if(name == "chooseperk") && chosen == "Yes"))
        {
            IsoPlayer.getInstance().LevelPerk(chosenperk);
            int n = 0;
            do
            {
                if(n >= IsoPlayer.getInstance().getCanUpgradePerk().size())
                    break;
                if(IsoPlayer.getInstance().getCanUpgradePerk().get(n) == chosenperk)
                {
                    IsoPlayer.getInstance().getCanUpgradePerk().remove(n);
                    PerkFactory.CheckForUnlockedPerks(IsoPlayer.getInstance());
                    UIManager.getLevelup().reset();
                    break;
                }
                n++;
            } while(true);
        }
    }
    public void Selected(std::string name, int Selected, int LastSelected)
    {
        zombie.characters.skills.PerkFactory.Perks perkType = PerkFactory.getPerkFromName(name);
        zombie.characters.skills.PerkFactory.Perk perk = (zombie.characters.skills.PerkFactory.Perk)PerkFactory.PerkMap.get(perkType);
        chosenperk = perkType;
        UIManager.DoModal("chooseperk", "Upgrade this skill?", true, this);
    }
    public zombie.characters.skills.PerkFactory.Perk perk;
    public zombie.characters.skills.PerkFactory.Perks perkType;
    public ArrayList subPerks;
    PerkButton perkbuttons[][];
    static Texture white;
    zombie.characters.skills.PerkFactory.Perks chosenperk;
}
} // namespace
