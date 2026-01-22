#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {


class ClassFactory {
public:
   public Map<Class, WeakReference<Constructor>> initialValue() {
      return std::make_unique<WeakHashMap<>>();
   }
}
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
