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

class IDebugOptionGroup {
public:
    virtual ~IDebugOptionGroup() = default;
   Iterable<IDebugOption> getChildren();

    void addChild(IDebugOption var1);

    void onChildAdded(IDebugOption var1);

    void onDescendantAdded(IDebugOption var1);
}
} // namespace options
} // namespace debug
} // namespace zombie
