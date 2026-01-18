#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace debug {
namespace options {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class IDebugOptionGroup {
public:
 virtual ~IDebugOptionGroup() = default;
 Iterable<IDebugOption> getChildren();

 void addChild(IDebugOption childOption);

 void onChildAdded(IDebugOption newChild);

 void onDescendantAdded(IDebugOption newDescendant);
}
} // namespace options
} // namespace debug
} // namespace zombie
