#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/ContainerOverlays/ContainerOverlayEntry.h"
#include "zombie/util/LocationRNG.h"

namespace zombie {
namespace iso {


class ContainerOverlays {
public:
    std::string name;
   public const std::vector<ContainerOverlayEntry> entries = std::make_unique<std::vector<>>();

   private ContainerOverlays$ContainerOverlay() {
   }

    void getEntries(const std::string& var1, std::vector<ContainerOverlayEntry> var2) {
      var2.clear();

      for (int var3 = 0; var3 < this.entries.size(); var3++) {
    ContainerOverlayEntry var4 = this.entries.get(var3);
         if (var4.room.equalsIgnoreCase(var1)) {
            var2.push_back(var4);
         }
      }
   }

    ContainerOverlayEntry pickRandom(const std::string& var1, int var2, int var3, int var4) {
      this.getEntries(var1, ContainerOverlays.tempEntries);
      if (ContainerOverlays.tempEntries.empty()) {
    return nullptr;
      } else {
    int var5 = LocationRNG.instance.nextInt(ContainerOverlays.tempEntries.size(), var2, var3, var4);
         return (ContainerOverlayEntry)ContainerOverlays.tempEntries.get(var5);
      }
   }
}
} // namespace iso
} // namespace zombie
