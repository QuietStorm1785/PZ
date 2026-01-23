#include "zombie/audio/ObjectAmbientEmitters.h"

namespace zombie {
namespace audio {

bool ChunkData::hasObject(const IsoObject* obj) const {
    return m_objects.find(const_cast<IsoObject*>(obj)) != m_objects.end();
}

void ChunkData::addObject(IsoObject* obj, PerObjectLogic* logic) {
    m_objects.emplace(obj, logic);
}

void ChunkData::removeObject(IsoObject* obj) {
    m_objects.erase(obj);
}

void ChunkData::reset() {
    m_objects.clear();
}

} // namespace audio
} // namespace zombie
