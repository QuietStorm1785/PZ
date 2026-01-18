#pragma once
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

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TutorialManager {
public:
 static bool Debug = false;
 bool Active = false;
 bool ActiveControlZombies = false;
 float TargetZombies = 0.0F;
 public TutorialManager.Stage stage = TutorialManager.Stage.getBelt;
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
 static TutorialManager instance = new TutorialManager();

 bool AllowUse(IsoObject var1) {
 return true;
 }

 void CheckWake() {
 }

 void CreateQuests() {
 try {
 for (int int0 = 0; int0 < IsoWorld.instance.CurrentCell.getStaticUpdaterObjectList().size(); int0++) {
 IsoObject object = IsoWorld.instance.CurrentCell.getStaticUpdaterObjectList().get(int0);
 if (object instanceof IsoRadio) {
 this->radio = (IsoRadio)object;
 }
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 this->radio = nullptr;
 }
 }

 void init() {
 if (!GameServer.bServer) {
 if (this->Active) {
 ;
 }
 }
 }

 void update() {
 }

 void ForceKillZombies() {
 IsoWorld.instance.ForceKillAllZombies();
 }

 public static enum Stage {
 getBelt,
 RipSheet,
 Apply,
 FindShed,
 getShedItems,
 EquipHammer,
 BoardUpHouse,
 FindFood,
 InHouseFood,
 KillZombie,
 StockUp,
 ExploreHouse,
 BreakBarricade,
 getSoupIngredients,
 MakeSoupPot,
 LightStove,
 Distraction,
 InvestigateSound,
 Alarm,
 Mouseover,
 Escape,
 ShouldBeOk;
 }
}
} // namespace ui
} // namespace zombie
