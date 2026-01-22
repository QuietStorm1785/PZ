// Logic for tree ambiance sound emitters
class TreeAmbianceLogic final : public PerObjectLogic {
public:
   TreeAmbianceLogic() = default;
   ~TreeAmbianceLogic() override = default;

   bool shouldPlaySound() override {
      return true;
   }

   std::string getSoundName() const override {
      return "TreeAmbiance";
   }

   void startPlaying(BaseSoundEmitter* emitter, int64_t /*time*/) override {
      if (auto* fmodEmitter = dynamic_cast<FMODSoundEmitter*>(emitter)) {
         fmodEmitter->addParameter(std::make_shared<ParameterCurrentZone>(object));
      }
      emitter->playAmbientLoopedImpl("BirdInTree");
   }

   void stopPlaying(BaseSoundEmitter* emitter, int64_t /*time*/) override {
      emitter->stopOrTriggerSoundByName("BirdInTree");
   }

   void checkParameters(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}
};


#pragma once

// Enum for power policy used by ambient emitters
enum class PowerPolicy {
   NotRequired,
   InteriorHydro,
   ExteriorOK
};


// Abstract base class for per-object ambient sound logic.
class PerObjectLogic {
public:
   IsoObject* object = nullptr;
   float parameterValue1 = std::numeric_limits<float>::quiet_NaN();

   PerObjectLogic() = default;
   virtual ~PerObjectLogic() = default;

   // Initialize logic for a given IsoObject.
   virtual void init(IsoObject* obj) {
      object = obj;
   }

   // Set a parameter value by name, updating only if changed.
   void setParameterValue1(BaseSoundEmitter* emitter, int64_t time, const std::string& param, float value) {
      if (value != parameterValue1) {
         parameterValue1 = value;
         FMOD_STUDIO_PARAMETER_DESCRIPTION desc = FMODManager::instance->getParameterDescription(param);
         emitter->setParameterValue(time, desc, value);
      }
   }

   // Set a parameter value by FMOD parameter description, updating only if changed.
   void setParameterValue1(BaseSoundEmitter* emitter, int64_t time, const FMOD_STUDIO_PARAMETER_DESCRIPTION& desc, float value) {
      if (value != parameterValue1) {
         parameterValue1 = value;
         emitter->setParameterValue(time, desc, value);
      }
   }

   // Abstract interface for subclasses.
   virtual bool shouldPlaySound() = 0;
   virtual std::string getSoundName() const = 0;
   virtual void startPlaying(BaseSoundEmitter* emitter, int64_t time) = 0;
   virtual void stopPlaying(BaseSoundEmitter* emitter, int64_t time) = 0;
   virtual void checkParameters(BaseSoundEmitter* emitter, int64_t time) = 0;
};

// Comparator for sorting or storing ObjectWithDistance pointers by distance.
// Usage example:
//   std::sort(vec.begin(), vec.end(), ObjectWithDistanceComparator{});
struct ObjectWithDistanceComparator {
   bool operator()(const ObjectWithDistance* lhs, const ObjectWithDistance* rhs) const {
      return lhs->distSq < rhs->distSq;
   }
};

// Associates an IsoObject and its logic with a distance value.
struct ObjectWithDistance {
   IsoObject* object = nullptr;
   PerObjectLogic* logic = nullptr;
   float distSq = 0.0f;

   ObjectWithDistance() = default;
   ObjectWithDistance(IsoObject* obj, PerObjectLogic* log, float dist = 0.0f)
      : object(obj), logic(log), distSq(dist) {}
};

// Holds a mapping of IsoObject* to PerObjectLogic* for a chunk.
class ChunkData {
public:
   // Map of objects to their ambient logic for this chunk.
   std::unordered_map<IsoObject*, PerObjectLogic*> m_objects;

   // Returns true if the object is present in the chunk.
   bool hasObject(const IsoObject* obj) const {
      return m_objects.find(const_cast<IsoObject*>(obj)) != m_objects.end();
   }

   // Adds an object and its logic to the chunk if not already present.
   void addObject(IsoObject* obj, PerObjectLogic* logic) {
      m_objects.emplace(obj, logic);
   }

   // Removes an object from the chunk.
   void removeObject(IsoObject* obj) {
      m_objects.erase(obj);
   }

   // Clears all objects from the chunk.
   void reset() {
      m_objects.clear();
   }
};

// Slot for managing a single ambient sound emitter instance
struct Slot {
   IsoObject* object = nullptr;
   PerObjectLogic* logic = nullptr;
   std::unique_ptr<BaseSoundEmitter> emitter;
   int64_t instance = 0;
   bool playing = false;

   Slot() = default;

   void playSound(IsoObject* obj, PerObjectLogic* log);
   void stopPlaying();
};
public:
   // Map of objects to their ambient logic for this chunk.
   std::unordered_map<IsoObject*, PerObjectLogic*> m_objects;

   // Returns true if the object is present in the chunk.
   bool hasObject(const IsoObject* obj) const {
      return m_objects.find(const_cast<IsoObject*>(obj)) != m_objects.end();
   }

   // Adds an object and its logic to the chunk if not already present.
   void addObject(IsoObject* obj, PerObjectLogic* logic) {
      m_objects.emplace(obj, logic);
   }

   // Removes an object from the chunk.
   void removeObject(IsoObject* obj) {
      m_objects.erase(obj);
   }

   // Clears all objects from the chunk.
   void reset() {
      m_objects.clear();
   }
};

// Logic for door ambient sound emitters.
class DoorLogic final : public PerObjectLogic {
public:
   DoorLogic() = default;
   ~DoorLogic() override = default;

   // Always play sound for doors.
   bool shouldPlaySound() override { return true; }

   // The sound name for doors.
   std::string getSoundName() const override { return "DoorAmbiance"; }

   // Called when sound starts playing (no-op).
   void startPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}

   // Called when sound stops playing; reset parameter value.
   void stopPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {
      parameterValue1 = std::numeric_limits<float>::quiet_NaN();
   }

   // Update sound parameters based on door state.
   void checkParameters(BaseSoundEmitter* emitter, int64_t time) override {
      if (!object) return;
      auto* door = dynamic_cast<IsoDoor*>(object);
      float value = (door && door->IsOpen()) ? 1.0f : 0.0f;
      setParameterValue1(emitter, time, "DoorWindowOpen", value);
   }
};

// Logic for fridge hum ambient sound emitters.
class FridgeHumLogic final : public PerObjectLogic {
public:
   FridgeHumLogic() = default;
   ~FridgeHumLogic() override = default;

   // Only play sound if the fridge or freezer is powered.
   bool shouldPlaySound() override {
      if (!object) return false;
      auto* container = object->getContainerByEitherType("fridge", "freezer");
      return container && container->isPowered();
   }

   // The sound name for fridges.
   std::string getSoundName() const override { return "FridgeHum"; }

   // Called when sound starts playing (no-op).
   void startPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}

   // Called when sound stops playing; reset parameter value.
   void stopPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {
      parameterValue1 = std::numeric_limits<float>::quiet_NaN();
   }

   // Update sound parameters based on generator state.
   void checkParameters(BaseSoundEmitter* emitter, int64_t time) override {
      setParameterValue1(emitter, time, "Generator", IsoWorld::instance->isHydroPowerOn() ? 0.0f : 1.0f);
   }
};

// Logic for ambient sound emitters, enforcing power policy and generator parameter.
class AmbientSoundLogic final : public PerObjectLogic {
public:
   PowerPolicy powerPolicy_ = PowerPolicy::NotRequired;
   bool hasGeneratorParameter_ = false;

   AmbientSoundLogic() = default;
   ~AmbientSoundLogic() override = default;

   // Initialize logic for a given IsoObject.
   void init(IsoObject* obj) override {
      PerObjectLogic::init(obj);
      const std::string soundName = getSoundName();
      const auto& policyMap = ObjectAmbientEmitters::getInstance().powerPolicyMap_;
      auto it = policyMap.find(soundName);
      powerPolicy_ = (it != policyMap.end()) ? it->second : PowerPolicy::NotRequired;
      if (powerPolicy_ != PowerPolicy::NotRequired) {
         if (GameSound* sound = GameSounds::getSound(soundName)) {
            hasGeneratorParameter_ = sound->numClipsUsingParameter("Generator") > 0;
         } else {
            hasGeneratorParameter_ = false;
         }
      } else {
         hasGeneratorParameter_ = false;
      }
   }

   // Determine if the sound should play based on power policy and generator.
   bool shouldPlaySound() override {
      if (!object) return false;
      if (powerPolicy_ == PowerPolicy::InteriorHydro) {
         bool hasPower = object->square->haveElectricity() ||
            (IsoWorld::instance->isHydroPowerOn() && object->square->getRoom() != nullptr);
         if (!hasPower) return false;
      }
      if (powerPolicy_ == PowerPolicy::ExteriorOK) {
         bool hasPower = object->square->haveElectricity() || IsoWorld::instance->isHydroPowerOn();
         if (!hasPower) return false;
      }
      if (powerPolicy_ != PowerPolicy::NotRequired &&
         !IsoWorld::instance->isHydroPowerOn() && !hasGeneratorParameter_) {
         return false;
      }
      if (auto* props = object->getProperties()) {
         return props->Is("AmbientSound");
      }
      return false;
   }

   // Get the ambient sound name from the object's properties.
   std::string getSoundName() const override {
      if (!object) return {};
      if (auto* props = object->getProperties()) {
         return props->Val("AmbientSound");
      }
      return {};
   }

   // Called when sound starts playing (no-op for now).
   void startPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}

   // Called when sound stops playing; reset parameter value.
   void stopPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {
      parameterValue1 = std::numeric_limits<float>::quiet_NaN();
   }

   // Update sound parameters based on power policy.
   void checkParameters(BaseSoundEmitter* emitter, int64_t time) override {
      if (powerPolicy_ != PowerPolicy::NotRequired) {
         setParameterValue1(emitter, time, "Generator", IsoWorld::instance->isHydroPowerOn() ? 0.0f : 1.0f);
      }
   }
};

// Logic for tent ambiance sound emitters
class TentAmbianceLogic final : public PerObjectLogic {
public:
    TentAmbianceLogic() = default;
    ~TentAmbianceLogic() override = default;

    bool shouldPlaySound() override {
        if (!object || !object->sprite) return false;
        const std::string& name = object->sprite->getName();
        if (name.empty()) return false;
        if (name.rfind("camping_01", 0) != 0) return false; // startsWith
        int idx = object->sprite->tileSheetIndex;
        return idx == 0 || idx == 3;
    }

    std::string getSoundName() const override {
        return "TentAmbiance";
    }

    void startPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}
    void stopPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}
    void checkParameters(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}
};
public:
   PowerPolicy powerPolicy_ = PowerPolicy::NotRequired;
   bool hasGeneratorParameter_ = false;

   AmbientSoundLogic() = default;
   ~AmbientSoundLogic() override = default;

   // Initialize logic for a given IsoObject.
   void init(IsoObject* obj) override {
      PerObjectLogic::init(obj);
      const std::string soundName = getSoundName();
      const auto& policyMap = ObjectAmbientEmitters::getInstance().powerPolicyMap_;
      auto it = policyMap.find(soundName);
      powerPolicy_ = (it != policyMap.end()) ? it->second : PowerPolicy::NotRequired;
      if (powerPolicy_ != PowerPolicy::NotRequired) {
         if (GameSound* sound = GameSounds::getSound(soundName)) {
            hasGeneratorParameter_ = sound->numClipsUsingParameter("Generator") > 0;
         } else {
            hasGeneratorParameter_ = false;
         }
      } else {
         hasGeneratorParameter_ = false;
      }
   }

   // Determine if the sound should play based on power policy and generator.
   bool shouldPlaySound() override {
      if (!object) return false;
      if (powerPolicy_ == PowerPolicy::InteriorHydro) {
         bool hasPower = object->square->haveElectricity() ||
            (IsoWorld::instance->isHydroPowerOn() && object->square->getRoom() != nullptr);
         if (!hasPower) return false;
      }
      if (powerPolicy_ == PowerPolicy::ExteriorOK) {
         bool hasPower = object->square->haveElectricity() || IsoWorld::instance->isHydroPowerOn();
         if (!hasPower) return false;
      }
      if (powerPolicy_ != PowerPolicy::NotRequired &&
         !IsoWorld::instance->isHydroPowerOn() && !hasGeneratorParameter_) {
         return false;
      }
      if (auto* props = object->getProperties()) {
         return props->Is("AmbientSound");
      }
      return false;
   }

   // Get the ambient sound name from the object's properties.
   std::string getSoundName() const override {
      if (!object) return {};
      if (auto* props = object->getProperties()) {
         return props->Val("AmbientSound");
      }
      return {};
   }

   // Called when sound starts playing (no-op for now).
   void startPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}

   // Called when sound stops playing; reset parameter value.
   void stopPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {
      parameterValue1 = std::numeric_limits<float>::quiet_NaN();
   }

   // Update sound parameters based on power policy.
   void checkParameters(BaseSoundEmitter* emitter, int64_t time) override {
      if (powerPolicy_ != PowerPolicy::NotRequired) {
         setParameterValue1(emitter, time, "Generator", IsoWorld::instance->isHydroPowerOn() ? 0.0f : 1.0f);
      }
   }
};
      powerPolicyMap_["StreetLightAmbiance"] = PowerPolicy::ExteriorOK;
      powerPolicyMap_["NeonLightAmbiance"] = PowerPolicy::ExteriorOK;
      powerPolicyMap_["NeonSignAmbiance"] = PowerPolicy::ExteriorOK;
      powerPolicyMap_["JukeboxAmbiance"] = PowerPolicy::InteriorHydro;
      powerPolicyMap_["ControlStationAmbiance"] = PowerPolicy::InteriorHydro;
      powerPolicyMap_["ClockAmbiance"] = PowerPolicy::InteriorHydro;
      powerPolicyMap_["GasPumpAmbiance"] = PowerPolicy::ExteriorOK;
      powerPolicyMap_["LightBulbAmbiance"] = PowerPolicy::InteriorHydro;
      powerPolicyMap_["ArcadeMachineAmbiance"] = PowerPolicy::InteriorHydro;
   }

   ~ObjectAmbientEmitters() = default;

   void addObject(IsoObject* obj, PerObjectLogic* logic) {
      if (!GameServer::bServer) {
         if (m_added_.find(obj) == m_added_.end()) {
            bool shouldAdd = false;
            for (int i = 0; i < IsoPlayer::numPlayers; ++i) {
               auto* player = IsoPlayer::players[i];
               if (player != nullptr && obj->getObjectIndex() != -1) {
                  uint8_t distLimit = 15;
                  if (dynamic_cast<DoorLogic*>(logic) != nullptr || dynamic_cast<WindowLogic*>(logic) != nullptr) {
                     distLimit = 10;
                  }
                  if ((obj->square->z == PZMath::fastfloor(player->getZ()) || !(dynamic_cast<DoorLogic*>(logic) != nullptr) && !(dynamic_cast<WindowLogic*>(logic) != nullptr))
                     && !(player->DistToSquared(obj->square->x + 0.5F, obj->square->y + 0.5F) > distLimit * distLimit)) {
                     shouldAdd = true;
                     break;
                  }
               }
            }
            if (shouldAdd) {
               ObjectWithDistance* owd = m_objectPool_.alloc();
               owd->object = obj;
               owd->logic = logic;
               m_objects_.push_back(owd);
               m_added_[obj] = owd;
            }
         }
      }
   }

   void removeObject(IsoObject* obj) {
      if (!GameServer::bServer) {
         auto* owd = m_added_[obj];
         m_added_.erase(obj);
         if (owd != nullptr) {
            auto it = std::find(m_objects_.begin(), m_objects_.end(), owd);
            if (it != m_objects_.end()) m_objects_.erase(it);
            m_objectPool_.release(owd);
         }
      }
   }

   void update() {
      if (!GameServer::bServer) {
         addObjectsFromChunks();
         for (auto& slot : m_slots_) slot.playing = false;

         if (m_objects_.empty()) {
            stopNotPlaying();
         } else {
            for (size_t i = 0; i < m_objects_.size(); ) {
               auto* owd = m_objects_[i];
               auto* obj = owd->object;
               auto* logic = owd->logic;
               if (!shouldPlay(obj, logic)) {
                  m_added_.erase(obj);
                  m_objects_.erase(m_objects_.begin() + i);
                  m_objectPool_.release(owd);
               } else {
                  obj->getFacingPosition(tempVector2_);
                  owd->distSq = getClosestListener(tempVector2_.x, tempVector2_.y, obj->square->z);
                  ++i;
               }
            }
            std::sort(m_objects_.begin(), m_objects_.end(), [](ObjectWithDistance* a, ObjectWithDistance* b) { return a->distSq < b->distSq; });
            size_t topN = std::min(m_objects_.size(), SLOT_COUNT);
            for (size_t i = 0; i < topN; ++i) {
               auto* obj = m_objects_[i]->object;
               auto* logic = m_objects_[i]->logic;
               if (shouldPlay(obj, logic)) {
                  int slotIdx = getExistingSlot(obj);
                  if (slotIdx != -1) {
                     m_slots_[slotIdx].playSound(obj, logic);
                  }
               }
            }
            for (size_t i = 0; i < topN; ++i) {
               auto* obj = m_objects_[i]->object;
               auto* logic = m_objects_[i]->logic;
               if (shouldPlay(obj, logic)) {
                  int slotIdx = getExistingSlot(obj);
                  if (slotIdx == -1) {
                     slotIdx = getFreeSlot();
                     if (m_slots_[slotIdx].object != nullptr) {
                        m_slots_[slotIdx].stopPlaying();
                        m_slots_[slotIdx].object = nullptr;
                     }
                     m_slots_[slotIdx].playSound(obj, logic);
                  }
               }
            }
            stopNotPlaying();
            m_added_.clear();
            for (auto& obj : m_objects_) m_objectPool_.release(obj);
            m_objects_.clear();
         }
      }
   }

    void addObjectsFromChunks() {
            for (int var1 = 0; var1 < IsoPlayer::numPlayers; var1++) {
                  auto* var2 = IsoWorld::instance->CurrentCell->ChunkMap[var1];
                  if (!var2->ignore) {
    int var3 = IsoChunkMap::ChunkGridWidth / 2;
    int var4 = IsoChunkMap::ChunkGridWidth / 2;

            for (int var5 = -1; var5 <= 1; var5++) {
               for (int var6 = -1; var6 <= 1; var6++) {
    IsoChunk* var7 = var2->getChunk(var3 + var6, var4 + var5);
                  if (var7 != nullptr) {
                     for (auto& pair : var7->m_objectEmitterData.m_objects) {
                        IsoObject* var10 = pair.first;
                        PerObjectLogic* var11 = pair.second;
                        addObject(var10, var11);
                     }
                  }
               }
            }
         }
      }
   }

    float getClosestListener(float var1, float var2, float var3) {
    float var4 = std::numeric_limits<float>::max();

            for (int var5 = 0; var5 < IsoPlayer::numPlayers; var5++) {
                  auto* var6 = IsoPlayer::players[var5];
                  if (var6 != nullptr && var6->getCurrentSquare() != nullptr) {
    float var7 = var6->getX();
    float var8 = var6->getY();
    float var9 = var6->getZ();
    float var10 = IsoUtils::DistanceToSquared(var7, var8, var9 * 3.0F, var1, var2, var3 * 3.0F);
            if (var6->Traits->HardOfHearing->isSet()) {
               var10 *= 4.5F;
            }

            if (var10 < var4) {
               var4 = var10;
            }
         }
      }

    return var4;
   }

    bool shouldPlay(IsoObject* var1, PerObjectLogic* var2) {
      if (var1 == nullptr) {
    return false;
      } else {
         return var1->getObjectIndex() == -1 ? false : var2->shouldPlaySound();
      }
   }

    int getExistingSlot(IsoObject* var1) {
      for (size_t var2 = 0; var2 < SLOT_COUNT; var2++) {
         if (m_slots[var2].object == var1) {
    return var2;
         }
      }

      return -1;
   }

    int getFreeSlot() {
      for (size_t var1 = 0; var1 < SLOT_COUNT; var1++) {
         if (!m_slots[var1].playing) {
    return var1;
         }
      }

      return -1;
   }

    void stopNotPlaying() {
      for (size_t var1 = 0; var1 < SLOT_COUNT; var1++) {
    Slot& var2 = m_slots[var1];
         if (!var2.playing) {
            var2.stopPlaying();
            var2.object = nullptr;
         }
      }
   }

    void render() {
      if (DebugOptions::instance->ObjectAmbientEmitterRender->getValue()) {
      auto* var1 = IsoWorld::instance->CurrentCell->ChunkMap[IsoCamera::frameState->playerIndex];
      if (!var1->ignore) {
    int var2 = IsoChunkMap::ChunkGridWidth / 2;
    int var3 = IsoChunkMap::ChunkGridWidth / 2;

            for (int var4 = -1; var4 <= 1; var4++) {
               for (int var5 = -1; var5 <= 1; var5++) {
    IsoChunk* var6 = var1->getChunk(var2 + var5, var3 + var4);
                  if (var6 != nullptr) {
                     for (auto& pair : var6->m_objectEmitterData.m_objects) {
                        IsoObject* var9 = pair.first;
                        if (var9->square->z == static_cast<int>(IsoCamera::frameState->CamCharacterZ)) {
                           var9->getFacingPosition(tempVector2);
    float var10 = tempVector2.x;
    float var11 = tempVector2.y;
    float var12 = var9->square->z;
                           LineDrawer::addLine(var10 - 0.45F, var11 - 0.45F, var12, var10 + 0.45F, var11 + 0.45F, var12, 0.5F, 0.5F, 0.5F, nullptr, false);
                        }
                     }
                  }
               }
            }
         }

             for (size_t var13 = 0; var13 < SLOT_COUNT; var13++) {
          Slot& var14 = m_slots[var13];
            if (var14.playing) {
    IsoObject* var15 = var14.object;
               var15->getFacingPosition(tempVector2);
    float var16 = tempVector2.x;
    float var17 = tempVector2.y;
    float var18 = var15->square->z;
               LineDrawer::addLine(var16 - 0.45F, var17 - 0.45F, var18, var16 + 0.45F, var17 + 0.45F, var18, 0.0F, 0.0F, 1.0F, nullptr, false);
            }
         }
      }
   }

    static void Reset() {
      if (instance) {
         for (size_t var0 = 0; var0 < SLOT_COUNT; var0++) {
            instance->m_slots[var0].stopPlaying();
            instance->m_slots[var0].object = nullptr;
            instance->m_slots[var0].playing = false;
         }
      }
   }
}
} // namespace audio
} // namespace zombie

// Static member definitions
std::unique_ptr<ObjectAmbientEmitters> zombie::audio::ObjectAmbientEmitters::instance_;
zombie::Vector2 zombie::audio::ObjectAmbientEmitters::tempVector2_;
