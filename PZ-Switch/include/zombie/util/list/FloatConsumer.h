#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace list {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FloatConsumer {
public:
 virtual ~FloatConsumer() = default;
 void accept(float var1);

 default FloatConsumer andThen(FloatConsumer floatConsumer0) {
 Objects.requireNonNull(floatConsumer0);
 return float0->{
 this->accept(float0);
 floatConsumer0.accept(float0);
 };
 }
}
} // namespace list
} // namespace util
} // namespace zombie
