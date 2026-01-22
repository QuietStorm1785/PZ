#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/AttachedItems/AttachedModels.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class ModelManager {
public:
    int ID;
    ModelInstance model;
    IsoGameCharacter character;
   public const std::vector<ModelInstance> sub = std::make_unique<std::vector<>>();
    const AttachedModels attachedModels = std::make_shared<AttachedModels>();
    bool active;
    bool bRemove;
    int renderRefCount = 0;
    int framesSinceStart;

   public ModelManager$ModelSlot(int var1, ModelInstance var2, IsoGameCharacter var3) {
      this.ID = var1;
      this.model = var2;
      this.character = var3;
   }

    void Update() {
      if (this.character != nullptr && !this.bRemove) {
         this.framesSinceStart++;
         if (this != this.character.legsSprite.modelSlot) {
    bool var1 = false;
         }

         if (this.model.AnimPlayer != this.character.getAnimationPlayer()) {
            this.model.AnimPlayer = this.character.getAnimationPlayer();
         }

         /* synchronized - TODO: add std::mutex */ (this.model.m_lock) {
            this.model.UpdateDir();
            this.model.Update();

            for (int var2 = 0; var2 < this.sub.size(); var2++) {
               this.sub.get(var2).AnimPlayer = this.model.AnimPlayer;
            }
         }
      }
   }

    bool isRendering() {
      return this.renderRefCount > 0;
   }

    void reset() {
      ModelManager.instance.resetModelInstanceRecurse(this.model, this);
      if (this.character != nullptr) {
         this.character.primaryHandModel = nullptr;
         this.character.secondaryHandModel = nullptr;
         ModelManager.instance.derefModelInstances(this.character.getReadyModelData());
         this.character.getReadyModelData().clear();
      }

      this.active = false;
      this.character = nullptr;
      this.bRemove = false;
      this.renderRefCount = 0;
      this.model = nullptr;
      this.sub.clear();
      this.attachedModels.clear();
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
