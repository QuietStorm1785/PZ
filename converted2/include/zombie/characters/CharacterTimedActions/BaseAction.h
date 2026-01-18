#pragma once
#include "zombie/GameTime.h"
#include "zombie/ai/states/PlayerActionsState.h"
#include "zombie/characters/CharacterActionAnims.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/packets/EventPacket.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace CharacterTimedActions {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BaseAction {
public:
  long SoundEffect = -1L;
  float CurrentTime = -2.0F;
  float LastTime = -1.0F;
  int MaxTime = 60;
  float PrevLastTime = 0.0F;
  bool UseProgressBar = true;
  bool ForceProgressBar = false;
  IsoGameCharacter chr;
  bool StopOnWalk = true;
  bool StopOnRun = true;
  bool StopOnAim = false;
  float caloriesModifier = 1.0F;
  float delta = 0.0F;
  bool blockMovementEtc;
  bool overrideAnimation;
public
  final ArrayList<String> animVariables = std::make_unique<ArrayList<>>();
  bool loopAction = false;
  bool bStarted = false;
  bool forceStop = false;
  bool forceComplete = false;
private
  static final ArrayList<String> specificNetworkAnim =
      new ArrayList<>(Arrays.asList(
          "Reload", "Bandage", "Loot", "AttachItem", "Drink", "Eat", "Pour",
          "Read", "fill_container_tap", "drink_tap", "WearClothing"));
  InventoryItem primaryHandItem = null;
  InventoryItem secondaryHandItem = null;
  std::string primaryHandMdl;
  std::string secondaryHandMdl;
  bool overrideHandModels = false;

public
  BaseAction(IsoGameCharacter _chr) { this.chr = _chr; }

  void forceStop() { this.forceStop = true; }

  void forceComplete() { this.forceComplete = true; }

  void PlayLoopedSoundTillComplete(const std::string &name, int radius,
                                   float maxGain) {
    this.SoundEffect = this.chr.getEmitter().playSound(name);
  }

  bool hasStalled() {
    return !this.bStarted ? false
                          : this.LastTime == this.CurrentTime &&
                                    this.LastTime == this.PrevLastTime &&
                                    this.LastTime < 0.0F ||
                                this.CurrentTime < 0.0F;
  }

  float getJobDelta() { return this.delta; }

  void resetJobDelta() {
    this.delta = 0.0F;
    this.CurrentTime = 0.0F;
  }

  void waitToStart() {
    if (!this.chr.shouldWaitToStartTimedAction()) {
      this.bStarted = true;
      this.start();
    }
  }

  void update() {
    this.PrevLastTime = this.LastTime;
    this.LastTime = this.CurrentTime;
    this.CurrentTime = this.CurrentTime + GameTime.instance.getMultiplier();
    if (this.CurrentTime < 0.0F) {
      this.CurrentTime = 0.0F;
    }

    boolean boolean0 =
        (Core.getInstance().isOptionProgressBar() || this.ForceProgressBar) &&
        this.UseProgressBar && this.chr instanceof
        IsoPlayer && ((IsoPlayer)this.chr).isLocalPlayer();
    if (this.MaxTime == -1) {
      if (boolean0) {
        UIManager.getProgressBar(((IsoPlayer)this.chr).getPlayerNum())
            .setValue(Float.POSITIVE_INFINITY);
      }
    } else {
      if (this.MaxTime == 0) {
        this.delta = 0.0F;
      } else {
        this.delta = Math.min(this.CurrentTime / this.MaxTime, 1.0F);
      }

      if (boolean0) {
        UIManager.getProgressBar(((IsoPlayer)this.chr).getPlayerNum())
            .setValue(this.delta);
      }
    }
  }

  void start() {
    this.forceComplete = false;
    this.forceStop = false;
    if (this.chr.isCurrentState(PlayerActionsState.instance())) {
      InventoryItem item0 = this.chr.getPrimaryHandItem();
      InventoryItem item1 = this.chr.getSecondaryHandItem();
      this.chr.setHideWeaponModel(!(item0 instanceof HandWeapon) &&
                                  !(item1 instanceof HandWeapon));
    }
  }

  void reset() {
    this.CurrentTime = 0.0F;
    this.forceComplete = false;
    this.forceStop = false;
  }

  float getCurrentTime() { return this.CurrentTime; }

  void stop() {
    UIManager.getProgressBar(((IsoPlayer)this.chr).getPlayerNum())
        .setValue(0.0F);
    if (this.SoundEffect > -1L) {
      this.chr.getEmitter().stopSound(this.SoundEffect);
      this.SoundEffect = -1L;
    }

    this.stopTimedActionAnim();
  }

  bool valid() { return true; }

  bool finished() {
    return this.CurrentTime >= this.MaxTime && this.MaxTime != -1;
  }

  void perform() {
    UIManager.getProgressBar(((IsoPlayer)this.chr).getPlayerNum())
        .setValue(1.0F);
    if (!this.loopAction) {
      this.stopTimedActionAnim();
    }
  }

  void setUseProgressBar(bool use) { this.UseProgressBar = use; }

  void setBlockMovementEtc(bool block) { this.blockMovementEtc = block; }

  void setOverrideAnimation(bool override) {
    this.overrideAnimation = override;
  }

  void stopTimedActionAnim() {
    for (int int0 = 0; int0 < this.animVariables.size(); int0++) {
      std::string string = this.animVariables.get(int0);
      this.chr.clearVariable(string);
    }

    this.chr.setVariable("IsPerformingAnAction", false);
    if (this.overrideHandModels) {
      this.overrideHandModels = false;
      this.chr.resetEquippedHandsModels();
    }
  }

  void setAnimVariable(const std::string &key, const std::string &val) {
    if (!this.animVariables.contains(key)) {
      this.animVariables.add(key);
    }

    this.chr.setVariable(key, val);
  }

  void setAnimVariable(const std::string &key, bool val) {
    if (!this.animVariables.contains(key)) {
      this.animVariables.add(key);
    }

    this.chr.setVariable(key, String.valueOf(val));
  }

  std::string getPrimaryHandMdl() { return this.primaryHandMdl; }

  std::string getSecondaryHandMdl() { return this.secondaryHandMdl; }

  InventoryItem getPrimaryHandItem() { return this.primaryHandItem; }

  InventoryItem getSecondaryHandItem() { return this.secondaryHandItem; }

  void setActionAnim(CharacterActionAnims act) {
    this.setActionAnim(act.toString());
  }

  void setActionAnim(const std::string &animNode) {
    this.setAnimVariable("PerformingAction", animNode);
    this.chr.setVariable("IsPerformingAnAction", true);
    if (Core.bDebug) {
      this.chr.advancedAnimator.printDebugCharacterActions(animNode);
    }
  }

  void setOverrideHandModels(InventoryItem primaryHand,
                             InventoryItem secondaryHand) {
    this.setOverrideHandModels(primaryHand, secondaryHand, true);
  }

  void setOverrideHandModels(InventoryItem primaryHand,
                             InventoryItem secondaryHand, bool resetModel) {
    this.setOverrideHandModelsObject(primaryHand, secondaryHand, resetModel);
  }

  void setOverrideHandModelsString(const std::string &primaryHand,
                                   const std::string &secondaryHand) {
    this.setOverrideHandModelsString(primaryHand, secondaryHand, true);
  }

  void setOverrideHandModelsString(const std::string &primaryHand,
                                   const std::string &secondaryHand,
                                   bool resetModel) {
    this.setOverrideHandModelsObject(primaryHand, secondaryHand, resetModel);
  }

  void setOverrideHandModelsObject(void *primaryHand, void *secondaryHand,
                                   bool resetModel) {
    this.overrideHandModels = true;
    this.primaryHandItem = Type.tryCastTo(primaryHand, InventoryItem.class);
    this.secondaryHandItem = Type.tryCastTo(secondaryHand, InventoryItem.class);
    this.primaryHandMdl = StringUtils.discardNullOrWhitespace(
        Type.tryCastTo(primaryHand, String.class));
    this.secondaryHandMdl = StringUtils.discardNullOrWhitespace(
        Type.tryCastTo(secondaryHand, String.class));
    if (resetModel) {
      this.chr.resetEquippedHandsModels();
    }

    if (this.primaryHandItem != nullptr || this.secondaryHandItem != nullptr) {
      this.chr.reportEvent(EventPacket.EventType.EventOverrideItem.name());
    }
  }

  void OnAnimEvent(AnimEvent event) {}

  void setLoopedAction(bool looped) { this.loopAction = looped; }
}
} // namespace CharacterTimedActions
} // namespace characters
} // namespace zombie
