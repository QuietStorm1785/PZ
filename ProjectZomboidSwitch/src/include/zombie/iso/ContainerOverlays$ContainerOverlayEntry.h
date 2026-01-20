#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class ContainerOverlays {
public:
    std::string room;
    std::string manyItems;
    std::string fewItems;

   private ContainerOverlays$ContainerOverlayEntry() {
   }
}
} // namespace iso
} // namespace zombie
