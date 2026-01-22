#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ai/states/PlayerActionsState.h"
#include "zombie/characters/CharacterActionAnims.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/packets/EventPacket/EventType.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace CharacterTimedActions {


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
   public const std::vector<std::string> animVariables = std::make_unique<std::vector<>>();
    bool loopAction = false;
    bool bStarted = false;
    bool forceStop = false;
    bool forceComplete = false;
   private static const std::vector<std::string> specificNetworkAnim = new std::vector<>(
      Arrays.asList("Reload", "Bandage", "Loot", "AttachItem", "Drink", "Eat", "Pour", "Read", "fill_container_tap", "drink_tap", "WearClothing")
   );
    InventoryItem primaryHandItem = nullptr;
    InventoryItem secondaryHandItem = nullptr;
    std::string primaryHandMdl;
    std::string secondaryHandMdl;
    bool overrideHandModels = false;

    public BaseAction(IsoGameCharacter var1) {
      this.chr = var1;
   }

    void forceStop() {
      this.forceStop = true;
   }

    void forceComplete() {
      this.forceComplete = true;
   }

    void PlayLoopedSoundTillComplete(const std::string& var1, int var2, float var3) {
      this.SoundEffect = this.chr.getEmitter().playSound(var1);
   }

    bool hasStalled() {
      return !this.bStarted
         ? false
         : this.LastTime == this.CurrentTime && this.LastTime == this.PrevLastTime && this.LastTime < 0.0F || this.CurrentTime < 0.0F;
   }

    float getJobDelta() {
      return this.delta;
   }

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

      boolean var1 = (Core.getInstance().isOptionProgressBar() || this.ForceProgressBar)
         && this.UseProgressBar
         && this.dynamic_cast<IsoPlayer*>(chr) != nullptr
         && ((IsoPlayer)this.chr).isLocalPlayer();
      if (this.MaxTime == -1) {
         if (var1) {
            UIManager.getProgressBar(((IsoPlayer)this.chr).getPlayerNum()).setValue(float.POSITIVE_INFINITY);
         }
      } else {
         if (this.MaxTime == 0) {
            this.delta = 0.0F;
         } else {
            this.delta = Math.min(this.CurrentTime / this.MaxTime, 1.0F);
         }

         if (var1) {
            UIManager.getProgressBar(((IsoPlayer)this.chr).getPlayerNum()).setValue(this.delta);
         }
      }
   }

    void start() {
      this.forceComplete = false;
      this.forceStop = false;
      if (this.chr.isCurrentState(PlayerActionsState.instance())) {
    InventoryItem var1 = this.chr.getPrimaryHandItem();
    InventoryItem var2 = this.chr.getSecondaryHandItem();
         this.chr.setHideWeaponModel(!(dynamic_cast<HandWeapon*>(var1) != nullptr) && !(dynamic_cast<HandWeapon*>(var2) != nullptr));
      }
   }

    void reset() {
      this.CurrentTime = 0.0F;
      this.forceComplete = false;
      this.forceStop = false;
   }

    float getCurrentTime() {
      return this.CurrentTime;
   }

    void stop() {
      UIManager.getProgressBar(((IsoPlayer)this.chr).getPlayerNum()).setValue(0.0F);
      if (this.SoundEffect > -1L) {
         this.chr.getEmitter().stopSound(this.SoundEffect);
         this.SoundEffect = -1L;
      }

      this.stopTimedActionAnim();
   }

    bool valid() {
    return true;
   }

    bool finished() {
      return this.CurrentTime >= this.MaxTime && this.MaxTime != -1;
   }

    void perform() {
      UIManager.getProgressBar(((IsoPlayer)this.chr).getPlayerNum()).setValue(1.0F);
      if (!this.loopAction) {
         this.stopTimedActionAnim();
      }
   }

    void setUseProgressBar(bool var1) {
      this.UseProgressBar = var1;
   }

    void setBlockMovementEtc(bool var1) {
      this.blockMovementEtc = var1;
   }

    void setOverrideAnimation(bool var1) {
      this.overrideAnimation = var1;
   }

    void stopTimedActionAnim() {
      for (int var1 = 0; var1 < this.animVariables.size(); var1++) {
    std::string var2 = this.animVariables.get(var1);
         this.chr.clearVariable(var2);
      }

      this.chr.setVariable("IsPerformingAnAction", false);
      if (this.overrideHandModels) {
         this.overrideHandModels = false;
         this.chr.resetEquippedHandsModels();
      }
   }

    void setAnimVariable(const std::string& var1, const std::string& var2) {
      if (!this.animVariables.contains(var1)) {
         this.animVariables.push_back(var1);
      }

      this.chr.setVariable(var1, var2);
   }

    void setAnimVariable(const std::string& var1, bool var2) {
      if (!this.animVariables.contains(var1)) {
         this.animVariables.push_back(var1);
      }

      this.chr.setVariable(var1, std::string.valueOf(var2));
   }

    std::string getPrimaryHandMdl() {
      return this.primaryHandMdl;
   }

    std::string getSecondaryHandMdl() {
      return this.secondaryHandMdl;
   }

    InventoryItem getPrimaryHandItem() {
      return this.primaryHandItem;
   }

    InventoryItem getSecondaryHandItem() {
      return this.secondaryHandItem;
   }

    void setActionAnim(CharacterActionAnims var1) {
      this.setActionAnim(var1);
   }

    void setActionAnim(const std::string& var1) {
      this.setAnimVariable("PerformingAction", var1);
      this.chr.setVariable("IsPerformingAnAction", true);
      if (Core.bDebug) {
         this.chr.advancedAnimator.printDebugCharacterActions(var1);
      }
   }

    void setOverrideHandModels(InventoryItem var1, InventoryItem var2) {
      this.setOverrideHandModels(var1, var2, true);
   }

    void setOverrideHandModels(InventoryItem var1, InventoryItem var2, bool var3) {
      this.setOverrideHandModelsObject(var1, var2, var3);
   }

    void setOverrideHandModelsString(const std::string& var1, const std::string& var2) {
      this.setOverrideHandModelsString(var1, var2, true);
   }

    void setOverrideHandModelsString(const std::string& var1, const std::string& var2, bool var3) {
      this.setOverrideHandModelsObject(var1, var2, var3);
   }

    void setOverrideHandModelsObject(void* var1, void* var2, bool var3) {
      this.overrideHandModels = true;
      this.primaryHandItem = (InventoryItem)Type.tryCastTo(var1, InventoryItem.class);
      this.secondaryHandItem = (InventoryItem)Type.tryCastTo(var2, InventoryItem.class);
      this.primaryHandMdl = StringUtils.discardNullOrWhitespace((std::string)Type.tryCastTo(var1, std::string.class));
      this.secondaryHandMdl = StringUtils.discardNullOrWhitespace((std::string)Type.tryCastTo(var2, std::string.class));
      if (var3) {
         this.chr.resetEquippedHandsModels();
      }

      if (this.primaryHandItem != nullptr || this.secondaryHandItem != nullptr) {
         this.chr.reportEvent(EventType.EventOverrideItem.name());
      }
   }

    void OnAnimEvent(AnimEvent var1) {
   }

    void setLoopedAction(bool var1) {
      this.loopAction = var1;
   }
}
} // namespace CharacterTimedActions
} // namespace characters
} // namespace zombie
