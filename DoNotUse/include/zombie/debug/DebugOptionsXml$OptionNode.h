#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace debug {

class DebugOptionsXml {
public:
    std::string name;
    bool value;

   public DebugOptionsXml$OptionNode() {
   }

   public DebugOptionsXml$OptionNode(std::string var1, boolean var2) {
      this.name = var1;
      this.value = var2;
   }
}
} // namespace debug
} // namespace zombie
