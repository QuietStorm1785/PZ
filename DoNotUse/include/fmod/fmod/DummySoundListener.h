#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
namespace fmod {

class DummySoundListener : public BaseSoundListener {
public:
    public DummySoundListener(int var1) {
      super(var1);
   }

    void tick() {
   }
}
} // namespace fmod
} // namespace fmod
