#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   TutorialManager.java
namespace zombie {
namespace ui {
#include "FrameLoader.h"
#include "GameTime.h"
#include "Quests.h"
#include "characters.h"
#include "NulledArrayList.h"
#include "iso.h"
#include "IsoBuilding.h"
#include "IsoRadio.h"
#include "IsoStove.h"
#include "IsoAnim.h"
#include "IsoSprite.h"
#include "ScriptManager.h"
// Referenced classes of package zombie.ui:
//            UIManager, TutorialPanel
class TutorialManager {
public:
{
	/*     */   public static enum Stage
	/*     */   {
	/*  82 */     getBelt, 
	/*  83 */     RipSheet, 
	/*  84 */     Apply, 
	/*  85 */     FindShed, 
	/*  86 */     getShedItems, 
	/*  87 */     EquipHammer, 
	/*  88 */     BoardUpHouse, 
	/*  89 */     FindFood, 
	/*  90 */     InHouseFood, 
	/*  91 */     KillZombie, 
	/*  92 */     StockUp, 
	/*  93 */     ExploreHouse, 
	/*  94 */     BreakBarricade, 
	/*  95 */     getSoupIngredients, 
	/*  96 */     MakeSoupPot, 
	/*  97 */     LightStove, 
	/*  98 */     Distraction, 
	/*  99 */     InvestigateSound, 
	/* 100 */     Alarm, 
	/* 101 */     Mouseover, 
	/* 102 */     Escape, 
	/* 103 */     ShouldBeOk;
	/*     */   }
    public TutorialManager()
    {
        Active = true;
        ActiveControlZombies = false;
        TargetZombies = 0.0F;
        stage = Stage.getBelt;
        wife = nullptr;
        DoorsLocked = true;
        BarricadeCount = 0;
        PrefMusic = nullptr;
        StealControl = false;
        AlarmTime = 0;
        ProfanityFilter = false;
        Timer = 0;
        AlarmTickTime = 160;
        DoneFirstSleep = false;
        wifeKilledByEarl = false;
        warnedHammer = false;
        TriggerFire = false;
        CanDragWife = false;
        AllowSleep = false;
        skipped = false;
        bDoneDeath = false;
        bDoGunnutDeadTalk = true;
        millingTune = "tune1.ogg";
        radio = nullptr;
        SpottedGunNut = false;
        bDoneWifeDeath = false;
        bDoneWifeDeathMourn = false;
    }
    public bool AllowUse(IsoObject Object)
    {
        return true;
    }
    public void CheckWake()
    {
    }
    public void CreateQuests()
    {
        for(int n = 0; n < IsoWorld.instance.CurrentCell.getStaticUpdaterObjectList().size(); n++)
        {
            IsoObject obj = (IsoObject)IsoWorld.instance.CurrentCell.getStaticUpdaterObjectList().get(n);
            if(obj instanceof IsoRadio)
                radio = (IsoRadio)obj;
        }
    }
    public void init()
    {
        if(FrameLoader.bServer)
            return;
        if(!Active)
            return;
        else
            return;
    }
    public void TutorialMessage(std::string a, std::string b)
    {
        if(a == nullptr && b == nullptr)
            UIManager.getTutorial().hide();
        else
            UIManager.getTutorial().ShowMessage(a, b);
    }
    public void update()
    {
        if(wife == nullptr)
            wife = (IsoSurvivor)ScriptManager.instance.getCharacterActual("KateBaldspotCharacters.Kate");
        if(gunnut == nullptr)
            gunnut = (IsoSurvivor)ScriptManager.instance.getCharacterActual("KateBaldspotCharacters.Raider");
        if(IsoPlayer.getInstance().getCurrentSquare() == nullptr);
        if(IsoPlayer.getInstance().getCurrentSquare() == nullptr)
            return;
        if(wife != nullptr)
        {
            std::string val = ScriptManager.instance.getFlagValue("FireTutorial.CanDragKate");
            wife.Draggable = val == "yes");
        }
        if(Math.abs(IsoPlayer.getInstance().getX() - 43F) < 1.0F && Math.abs(IsoPlayer.getInstance().getY() - 22F) < 2.0F && IsoPlayer.getInstance().getZ() == 1.0F)
            UIManager.AddTutorial(43F, 22F, 1.0F, "Opening Containers", "You can search inside the wardrobe by clicking it when stood next to it.<br><br>Click items to pick them up.<br><br>You can then click on your inventory icon to the left to place it in your bag.", false, 0.0F);
        Quest quest = QuestManager.instance.FindQuest("TendWifeQuest");
        if(wife != nullptr && quest != nullptr && quest.FindTask("BandageLeg").Complete && wife.sprite.CurrentAnim.name == "asleep_bleeding"))
            wife.sprite.PlayAnim("asleep_bandaged");
        std::string wifeTune = "tune2.ogg";
        if(wife != nullptr && wife.getHealth() <= 0.0F)
            wifeTune = "tune8.ogg";
        std::string zombieTune = "tune4.ogg";
        millingTune = GameTime.instance.millingtune;
        zombieTune = GameTime.instance.zombieTune;
        if(!Active)
        {
            return;
        } else
        {
            Timer++;
            return;
        }
    }
    private void ForceKillZombies()
    {
        IsoWorld.instance.ForceKillAllZombies();
    }
    public static bool Debug = false;
    public bool Active;
    public bool ActiveControlZombies;
    public float TargetZombies;
    public Stage stage;
    public IsoSurvivor wife;
    private IsoZombie zombie;
    public IsoStove tutorialStove;
    public IsoBuilding tutBuilding;
    public bool DoorsLocked;
    public int BarricadeCount;
    public std::string PrefMusic;
    public IsoSurvivor gunnut;
    public bool StealControl;
    public int AlarmTime;
    public bool ProfanityFilter;
    public int Timer;
    public int AlarmTickTime;
    public bool DoneFirstSleep;
    public bool wifeKilledByEarl;
    public bool warnedHammer;
    public bool TriggerFire;
    public bool CanDragWife;
    public bool AllowSleep;
    public bool skipped;
    private bool bDoneDeath;
    bool bDoGunnutDeadTalk;
    public std::string millingTune;
    IsoRadio radio;
    public bool SpottedGunNut;
    bool bDoneWifeDeath;
    bool bDoneWifeDeathMourn;
    public static TutorialManager instance = new TutorialManager();
}
} // namespace
