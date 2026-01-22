#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/objects/IsoRadio.h"
#include "zombie/iso/objects/IsoStove.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/TutorialManager/Stage.h"

namespace zombie {
namespace ui {


class TutorialManager {
public:
    static bool Debug = false;
    bool Active = false;
    bool ActiveControlZombies = false;
    float TargetZombies = 0.0F;
    Stage stage = Stage.getBelt;
    IsoSurvivor wife = nullptr;
    IsoZombie zombie;
    IsoStove tutorialStove;
    IsoBuilding tutBuilding;
    bool DoorsLocked = true;
    int BarricadeCount = 0;
    std::string PrefMusic = nullptr;
    IsoSurvivor gunnut;
    bool StealControl = false;
    int AlarmTime = 0;
    bool ProfanityFilter = false;
    int Timer = 0;
    int AlarmTickTime = 160;
    bool DoneFirstSleep = false;
    bool wifeKilledByEarl = false;
    bool warnedHammer = false;
    bool TriggerFire = false;
    bool CanDragWife = false;
    bool AllowSleep = false;
    bool skipped = false;
    bool bDoneDeath = false;
    bool bDoGunnutDeadTalk = true;
    std::string millingTune = "tune1.ogg";
    IsoRadio radio = nullptr;
    static TutorialManager instance = std::make_shared<TutorialManager>();

    bool AllowUse(IsoObject var1) {
    return true;
   }

    void CheckWake() {
   }

    void CreateQuests() {
      try {
         for (int var1 = 0; var1 < IsoWorld.instance.CurrentCell.getStaticUpdaterObjectList().size(); var1++) {
    IsoObject var2 = (IsoObject)IsoWorld.instance.CurrentCell.getStaticUpdaterObjectList().get(var1);
            if (dynamic_cast<IsoRadio*>(var2) != nullptr) {
               this.radio = (IsoRadio)var2;
            }
         }
      } catch (Exception var3) {
         var3.printStackTrace();
         this.radio = nullptr;
      }
   }

    void init() {
      if (!GameServer.bServer) {
         if (this.Active) {
            ;
         }
      }
   }

    void update() {
   }

    void ForceKillZombies() {
      IsoWorld.instance.ForceKillAllZombies();
   }
}
} // namespace ui
} // namespace zombie
