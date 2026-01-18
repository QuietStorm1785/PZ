#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class Type {
public:
 public static <R, I> R tryCastTo(I object, Class<R> clazz) {
 return (R)(clazz.isInstance(object) ? clazz.cast(object) : nullptr);
 }

 static bool asBoolean(void* object) {
 return asBoolean();
 }

 static bool asBoolean(void* object, bool boolean0) {
 if (object.empty()) {
 return boolean0;
 } else {
 bool boolean1 = tryCastTo(object, Boolean.class);
 return boolean1 = = nullptr ? boolean0 : boolean1;
 }
 }
}
} // namespace util
} // namespace zombie
