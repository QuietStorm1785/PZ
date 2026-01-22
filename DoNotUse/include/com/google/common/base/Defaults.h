#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Defaults {
public:
   private static const Map<Class<?>, Object> DEFAULTS;

    private Defaults() {
   }

   private static <T> void put(Map<Class<?>, Object> map, Class<T> type, T value) {
      map.put(type, value);
   }

   public static <T> T defaultValue(Class<T> type) {
      return (T)DEFAULTS.get(Preconditions.checkNotNull(type));
   }

   static {
      Map<Class<?>, Object> map = std::make_unique<std::unordered_map<>>();
      put(map, boolean.class, false);
      put(map, char.class, '\u0000');
      put(map, byte.class, (byte)0);
      put(map, short.class, (short)0);
      put(map, int.class, 0);
      put(map, long.class, 0L);
      put(map, float.class, 0.0F);
      put(map, double.class, 0.0);
      DEFAULTS = Collections.unmodifiableMap(map);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
