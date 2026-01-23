#include <memory>
#include <string>
#include <algorithm>
#include <limits>
#include "zombie/audio/ObjectAmbientEmitters.h"

namespace zombie {
namespace audio {

// Static member definitions
std::unique_ptr<ObjectAmbientEmitters> ObjectAmbientEmitters::instance_ = nullptr;
Vector2 ObjectAmbientEmitters::tempVector2_;

ObjectAmbientEmitters::ObjectAmbientEmitters() {
    // reserve collections to avoid frequent reallocations
    m_objects_.reserve(64);
}

ObjectAmbientEmitters& ObjectAmbientEmitters::getInstance() {
    if (!instance_) instance_ = std::make_unique<ObjectAmbientEmitters>();
    return *instance_;
}

void ObjectAmbientEmitters::addObject(IsoObject* obj, PerObjectLogic* logic) {
    if (!obj || !logic) return;
    if (m_added_.find(obj) != m_added_.end()) return;

    auto* owd = new ObjectWithDistance(obj, logic, std::numeric_limits<float>::infinity());
    m_added_.emplace(obj, owd);
    m_objects_.push_back(owd);
}

void ObjectAmbientEmitters::removeObject(IsoObject* obj) {
    if (!obj) return;
    auto it = m_added_.find(obj);
    if (it == m_added_.end()) return;
    ObjectWithDistance* owd = it->second;

    // remove from m_objects_
    auto vit = std::find(m_objects_.begin(), m_objects_.end(), owd);
    if (vit != m_objects_.end()) m_objects_.erase(vit);

    m_added_.erase(it);
    delete owd;
}

void ObjectAmbientEmitters::addObjectsFromChunks() {
    // Placeholder: chunk scanning is complex; keep existing added objects
}

float ObjectAmbientEmitters::getClosestListener(float /*x*/, float /*y*/, float /*z*/) {
    // Precise listener calculation requires game state; return 0 for now.
    return 0.0f;
}

bool ObjectAmbientEmitters::shouldPlay(IsoObject* obj, PerObjectLogic* logic) {
    if (!obj || !logic) return false;
    // Ensure logic is initialized for this object
    logic->init(obj);
    return logic->shouldPlaySound();
}

int ObjectAmbientEmitters::getExistingSlot(IsoObject* obj) {
    if (!obj) return -1;
    for (size_t i = 0; i < m_slots_.size(); ++i) {
        if (m_slots_[i].object == obj) return static_cast<int>(i);
    }
    return -1;
}

int ObjectAmbientEmitters::getFreeSlot() {
    for (size_t i = 0; i < m_slots_.size(); ++i) {
        if (!m_slots_[i].playing) return static_cast<int>(i);
    }
    return -1;
}

void ObjectAmbientEmitters::stopNotPlaying() {
    for (auto& slot : m_slots_) {
        if (slot.playing) {
            if (!slot.object || !shouldPlay(slot.object, slot.logic)) {
                slot.stopPlaying();
                slot.playing = false;
                slot.object = nullptr;
                slot.logic = nullptr;
            }
        }
    }
}

void ObjectAmbientEmitters::update() {
    // Update object distances and manage slots
    for (auto* owd : m_objects_) {
        if (!owd) continue;
        if (!owd->object || !owd->logic) continue;

        // simple policy: if shouldPlay and no existing slot, allocate one
        bool want = shouldPlay(owd->object, owd->logic);
        int existing = getExistingSlot(owd->object);
        if (want) {
            if (existing == -1) {
                int freeSlot = getFreeSlot();
                if (freeSlot != -1) {
                    m_slots_[freeSlot].playSound(owd->object, owd->logic);
                }
            } else {
                // refresh parameters on existing slot
                m_slots_[existing].logic->checkParameters(m_slots_[existing].emitter.get(), m_slots_[existing].instance);
            }
        } else {
            if (existing != -1) {
                m_slots_[existing].stopPlaying();
                m_slots_[existing].playing = false;
                m_slots_[existing].object = nullptr;
                m_slots_[existing].logic = nullptr;
            }
        }
    }

    stopNotPlaying();

    // tick emitters
    for (auto& slot : m_slots_) {
        if (slot.playing && slot.emitter) slot.emitter->tick();
    }
}

void ObjectAmbientEmitters::render() {
    // No-op for now; render debug visuals could be added here
}

void ObjectAmbientEmitters::Reset() {
    // stop and clear all slots
    for (auto& slot : m_slots_) {
        slot.stopPlaying();
        slot.playing = false;
        slot.object = nullptr;
        slot.logic = nullptr;
        slot.emitter.reset();
        slot.instance = 0;
    }
    // clear tracked objects
    for (auto& p : m_added_) delete p.second;
    m_added_.clear();
    m_objects_.clear();
    instance_.reset();
}
} // namespace audio
} // namespace zombie   
