#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/ObjectAmbientEmitters/PerObjectLogic.h"
#include "zombie/iso/IsoObject.h"

namespace zombie {
namespace audio {


class ObjectAmbientEmitters {
:
   HashMap<IsoObject, PerObjectLogic> m_objects = std::make_unique<HashMap<>>();

    bool hasObject(IsoObject var1) {
      return this.m_objects.containsKey(var1);
   }

    void addObject(IsoObject var1, PerObjectLogic var2) {
      if (!this.m_objects.containsKey(var1)) {
         this.m_objects.put(var1, var2);
      }
   }

    void removeObject(IsoObject var1) {
      this.m_objects.remove(var1);
   }

    void reset() {
      this.m_objects.clear();
   }
}
} // namespace audio
} // namespace zombie
