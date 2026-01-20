#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace globalObjects {

class CGlobalObject : public GlobalObject {
public:
   CGlobalObject(CGlobalObjectSystem var1, int var2, int var3, int var4) {
      super(var1, var2, var3, var4);
   }
}
} // namespace globalObjects
} // namespace zombie
