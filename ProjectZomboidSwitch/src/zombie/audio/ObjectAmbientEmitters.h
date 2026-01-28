#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <array>
#include <cstdint>
#include <algorithm>
#include <limits>
#include <type_traits>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/audio/OpenALSoundEmitter.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/core/Core.h"
#include "zombie/audio/parameters/ParameterCurrentZone.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/objects/IsoWindow.h"

// Forward declarations for types used in class members
class IsoObject;
class PerObjectLogic;
class ObjectWithDistance;
class Slot;
// Power policy for ambient emitters. Replacement for ObjectAmbientEmitters$PowerPolicy.h
enum class PowerPolicy : int {
    NotRequired = 0,
    InteriorHydro = 1,
    ExteriorOK = 2,
};
class BaseSoundEmitter;
class GameSound;
class GameSounds;

// Holds a mapping of IsoObject* to PerObjectLogic* for a chunk. Replacement for ObjectAmbientEmitters$ChunkData.h
class ChunkData {
public:
    std::unordered_map<IsoObject*, PerObjectLogic*> m_objects;

    bool hasObject(const IsoObject* obj) const {
        return m_objects.find(const_cast<IsoObject*>(obj)) != m_objects.end();
    }

    void addObject(IsoObject* obj, PerObjectLogic* logic) {
        m_objects.emplace(obj, logic);
    }

    void removeObject(IsoObject* obj) {
        m_objects.erase(obj);
    }

    void reset() {
        m_objects.clear();
    }
};
// Base per-object logic for ambient emitters. Replacement for ObjectAmbientEmitters$PerObjectLogic.h
class PerObjectLogic {
public:
    IsoObject* object = nullptr;
    float parameterValue1 = std::numeric_limits<float>::quiet_NaN();

    PerObjectLogic() = default;
    virtual ~PerObjectLogic() = default;

    virtual void init(IsoObject* obj) { object = obj; }

    void setParameterValue1(BaseSoundEmitter* emitter, int64_t time, const std::string& name, float value) {
        if (value != parameterValue1) {
            parameterValue1 = value;
                // TODO: Replace FMOD parameter logic with OpenAL equivalent or stub
            emitter->setParameterValue(time, desc, value);
        }
    }

    void setParameterValue1(BaseSoundEmitter* emitter, int64_t time, const std::string& param, float value) {
        if (value != parameterValue1) {
            parameterValue1 = value;
            emitter->setParameterValue(time, param, value);
        }
    }

    virtual bool shouldPlaySound() = 0;
    virtual std::string getSoundName() const = 0;
    virtual void startPlaying(BaseSoundEmitter* emitter, int64_t time) = 0;
    virtual void stopPlaying(BaseSoundEmitter* emitter, int64_t time) = 0;
    virtual void checkParameters(BaseSoundEmitter* emitter, int64_t time) = 0;
};
// Logic for ambient sound emitters, enforcing power policy and generator parameter. Replacement for ObjectAmbientEmitters$AmbientSoundLogic.h
class AmbientSoundLogic final : public PerObjectLogic {
public:
    PowerPolicy powerPolicy_ = PowerPolicy::NotRequired;
    bool hasGeneratorParameter_ = false;

    AmbientSoundLogic() = default;
    ~AmbientSoundLogic() override = default;

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

    std::string getSoundName() const override {
        if (!object) return {};
        if (auto* props = object->getProperties()) {
            return props->Val("AmbientSound");
        }
        return {};
    }

    void startPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}

    void stopPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {
        parameterValue1 = std::numeric_limits<float>::quiet_NaN();
    }

    void checkParameters(BaseSoundEmitter* emitter, int64_t time) override {
        if (powerPolicy_ != PowerPolicy::NotRequired) {
            setParameterValue1(emitter, time, "Generator", IsoWorld::instance->isHydroPowerOn() ? 0.0f : 1.0f);
        }
    }
};

// Simple logic for doors: always eligible and exposes a "DoorWindowOpen" parameter. Replacement for ObjectAmbientEmitters$DoorLogic.h
class DoorLogic final : public PerObjectLogic {
public:
    DoorLogic() = default;
    ~DoorLogic() override = default;

    void init(IsoObject* obj) override {
        PerObjectLogic::init(obj);
    }

    bool shouldPlaySound() override {
        return object != nullptr;
    }

    std::string getSoundName() const override {
        return "DoorAmbiance";
    }

    void startPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}

    void stopPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {
        parameterValue1 = std::numeric_limits<float>::quiet_NaN();
    }

    void checkParameters(BaseSoundEmitter* emitter, int64_t time) override {
        if (!object) return;
        auto* door = dynamic_cast<IsoDoor*>(object);
        if (!door) return;
        float value = door->IsOpen() ? 1.0f : 0.0f;
        setParameterValue1(emitter, time, "DoorWindowOpen", value);
    }
};


// Specific logic for fridge/freezer hum ambient sound. Replacement for ObjectAmbientEmitters$FridgeHumLogic.h
class FridgeHumLogic final : public PerObjectLogic {
public:
    FridgeHumLogic() = default;
    ~FridgeHumLogic() override = default;

    void init(IsoObject* obj) override {
        PerObjectLogic::init(obj);
    }

    bool shouldPlaySound() override {
        if (!object) return false;
        ItemContainer* c = object->getContainerByEitherType("fridge", "freezer");
        return c != nullptr && c->isPowered();
    }

    std::string getSoundName() const override {
        return "FridgeHum";
    }

    void startPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}

    void stopPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {
        parameterValue1 = std::numeric_limits<float>::quiet_NaN();
    }

    void checkParameters(BaseSoundEmitter* emitter, int64_t time) override {
        setParameterValue1(emitter, time, "Generator", IsoWorld::instance->isHydroPowerOn() ? 0.0f : 1.0f);
    }
};

// Tent ambiance logic. Replacement for ObjectAmbientEmitters$TentAmbianceLogic.h
class TentAmbianceLogic final : public PerObjectLogic {
public:
    TentAmbianceLogic() = default;
    ~TentAmbianceLogic() override = default;

    void init(IsoObject* obj) override { PerObjectLogic::init(obj); }

    bool shouldPlaySound() override {
        if (!object) return false;
        // Many converted Java classes expose a `sprite` pointer with name and tileSheetIndex.
        // Guard defensively if those members are not present at runtime.
        if (!object->sprite) return false;
        const char* name = object->sprite->getName();
        if (!name) return false;
        std::string sname(name);
        if (sname.rfind("camping_01", 0) != 0) return false; // startsWith
        int idx = object->sprite->tileSheetIndex;
        return (idx == 0 || idx == 3);
    }

    std::string getSoundName() const override {
        return "TentAmbiance";
    }

    void startPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}
    void stopPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}
    void checkParameters(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}
};

// Water drip logic. Replacement for ObjectAmbientEmitters$WaterDripLogic.h
class WaterDripLogic final : public PerObjectLogic {
public:
    WaterDripLogic() = default;
    ~WaterDripLogic() override = default;

    void init(IsoObject* obj) override { PerObjectLogic::init(obj); }

    bool shouldPlaySound() override {
        if (!object) return false;
        if (!object->sprite) return false;
        if (!object->sprite->getProperties().Is(IsoFlagType::waterPiped)) return false;
        return object->getWaterAmount() > 0.0f;
    }

    std::string getSoundName() const override {
        return "WaterDrip";
    }

    void startPlaying(BaseSoundEmitter* emitter, int64_t time) override {
        if (!object || !object->sprite) return;
        if (object->sprite->getProperties().Is("SinkType")) {
            std::string type = object->sprite->getProperties().Val("SinkType");
            float v = 0.0f;
            if (type == "Ceramic") v = 1.0f;
            else if (type == "Metal") v = 2.0f;
            setParameterValue1(emitter, time, "SinkType", v);
        }
    }

    void stopPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {
        parameterValue1 = std::numeric_limits<float>::quiet_NaN();
    }

    void checkParameters(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}
};

// Tree ambiance logic. Replacement for ObjectAmbientEmitters$TreeAmbianceLogic.h
class TreeAmbianceLogic final : public PerObjectLogic {
public:
    TreeAmbianceLogic() = default;
    ~TreeAmbianceLogic() override = default;

    void init(IsoObject* obj) override { PerObjectLogic::init(obj); }

    bool shouldPlaySound() override {
        if (!object) return false;
        return true;
    }

    std::string getSoundName() const override {
        return "TreeAmbiance";
    }

    void startPlaying(BaseSoundEmitter* emitter, int64_t /*time*/) override {
        if (!emitter) return;
          if (auto* openalEmitter = dynamic_cast<OpenALSoundEmitter*>(emitter)) {
              // OpenAL emitter logic can be added here if needed
          }
        emitter->playAmbientLoopedImpl("BirdInTree");
    }

    void stopPlaying(BaseSoundEmitter* emitter, int64_t /*time*/) override {
        if (!emitter) return;
        emitter->stopOrTriggerSoundByName("BirdInTree");
    }

    void checkParameters(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}
};

// Window logic. Replacement for ObjectAmbientEmitters$WindowLogic.h
class WindowLogic final : public PerObjectLogic {
public:
    WindowLogic() = default;
    ~WindowLogic() override = default;

    void init(IsoObject* obj) override { PerObjectLogic::init(obj); }

    bool shouldPlaySound() override { return true; }

    std::string getSoundName() const override { return "WindowAmbiance"; }

    void startPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {}

    void stopPlaying(BaseSoundEmitter* /*emitter*/, int64_t /*time*/) override {
        parameterValue1 = std::numeric_limits<float>::quiet_NaN();
    }

    void checkParameters(BaseSoundEmitter* emitter, int64_t time) override {
        if (!object || !emitter) return;
        auto* win = dynamic_cast<IsoWindow*>(object);
        if (!win) return;
        float v = (!win->IsOpen() && !win->isDestroyed()) ? 0.0f : 1.0f;
        setParameterValue1(emitter, time, "DoorWindowOpen", v);
    }
};


// Comparator for sorting ObjectWithDistance by squared distance. Replacement for ObjectAmbientEmitters$ObjectWithDistanceComparator.h
struct ObjectWithDistanceComparator {
    // Compare by value (ascending)
    bool operator()(const ObjectWithDistance& a, const ObjectWithDistance& b) const noexcept {
        return a.distSq < b.distSq;
    }

    // Compare by pointer with null-safety (null is treated as greater)
    bool operator()(const ObjectWithDistance* a, const ObjectWithDistance* b) const noexcept {
        if (a == b) return false;
        if (!a) return false; // nullptr is greater than any valid pointer
        if (!b) return true;
        return a->distSq < b->distSq;
    }
};

// Represents an object with a cached squared distance and its logic. Replacement for ObjectAmbientEmitters$ObjectWithDistance.h
class ObjectWithDistance {
public:
    IsoObject* object = nullptr;
    PerObjectLogic* logic = nullptr;
    float distSq = std::numeric_limits<float>::infinity();

    ObjectWithDistance() = default;
    ObjectWithDistance(IsoObject* obj, PerObjectLogic* lg, float ds) : object(obj), logic(lg), distSq(ds) {}
};

// Slot holds emitter state for a single ambient sound slot. Replacement for ObjectAmbientEmitters$Slot.h
class Slot {
public:
    IsoObject* object = nullptr;
    PerObjectLogic* logic = nullptr;
    std::unique_ptr<BaseSoundEmitter> emitter;
    int64_t instance = 0;
    bool playing = false;

    void playSound(IsoObject* obj, PerObjectLogic* lg) {
        if (!emitter) {
            if (Core::SoundDisabled) {
                class DummySoundEmitter; // forward declare to avoid header dependency
                emitter = std::unique_ptr<BaseSoundEmitter>(static_cast<BaseSoundEmitter*>(new DummySoundEmitter()));
            } else {
#if defined(__SWITCH__) || defined(NINTENDO_SWITCH)
                emitter = std::unique_ptr<BaseSoundEmitter>(static_cast<BaseSoundEmitter*>(new audio::SDL2SoundEmitter()));
#else
                #if defined(__SWITCH__) || defined(NINTENDO_SWITCH)
                emitter = std::unique_ptr<BaseSoundEmitter>(static_cast<BaseSoundEmitter*>(new audio::SDL2SoundEmitter()));
                #else
                emitter = std::make_unique<OpenALSoundEmitter>();
                #endif
#endif
            }
        }

        obj->getFacingPosition(ObjectAmbientEmitters::tempVector2_);
        emitter->setPos(ObjectAmbientEmitters::tempVector2_.getX(), ObjectAmbientEmitters::tempVector2_.getY(), obj->square->z);
        object = obj;
        logic = lg;

        const std::string soundName = logic->getSoundName();
        if (!emitter->isPlaying(soundName)) {
            emitter->stopAll();
              if (auto* openalEmitter = dynamic_cast<OpenALSoundEmitter*>(emitter.get())) {
                  // OpenAL emitter parameter clearing logic can be added here if needed
              }

            instance = emitter->playSoundImpl(soundName, nullptr);
            logic->startPlaying(emitter.get(), instance);
        }

        logic->checkParameters(emitter.get(), instance);
        playing = true;
        emitter->tick();
    }

    void stopPlaying() {
        if (emitter && instance != 0) {
            if (logic) logic->stopPlaying(emitter.get(), instance);
            if (emitter->hasSustainPoints(instance)) {
                emitter->triggerCue(instance);
                instance = 0;
            } else {
                emitter->stopAll();
                instance = 0;
            }
        }
    }
};

class ObjectAmbientEmitters {
public:
    static constexpr size_t SLOT_COUNT = 16;
    std::unordered_map<std::string, PowerPolicy> powerPolicyMap_;
    static std::unique_ptr<ObjectAmbientEmitters> instance_;
    static Vector2 tempVector2_;
    std::unordered_map<IsoObject*, ObjectWithDistance*> m_added_;
    ObjectPool<ObjectWithDistance> m_objectPool_;
    std::vector<ObjectWithDistance*> m_objects_;
    std::array<Slot, SLOT_COUNT> m_slots_;

    static ObjectAmbientEmitters& getInstance() {
        if (!instance_) {
            instance_ = std::make_unique<ObjectAmbientEmitters>();
        }
        return *instance_;
    }

    ObjectAmbientEmitters();
    ~ObjectAmbientEmitters() = default;

    void addObject(IsoObject* obj, PerObjectLogic* logic);
    void removeObject(IsoObject* obj);
    void update();
    void addObjectsFromChunks();
    float getClosestListener(float x, float y, float z);
    bool shouldPlay(IsoObject* obj, PerObjectLogic* logic);
    int getExistingSlot(IsoObject* obj);
    int getFreeSlot();
    void stopNotPlaying();
    void render();
    static void Reset();
};
