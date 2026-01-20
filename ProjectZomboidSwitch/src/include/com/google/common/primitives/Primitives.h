#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace primitives {


class Primitives {
public:
   private static const Map<Class<?>, Class<?>> PRIMITIVE_TO_WRAPPER_TYPE;
   private static const Map<Class<?>, Class<?>> WRAPPER_TO_PRIMITIVE_TYPE;

    private Primitives() {
   }

    static void add(Class<?>> forward, Class<?>> backward, Class<?> key, Class<?> value) {
      forward.put(key, value);
      backward.put(value, key);
   }

   public static Set<Class<?>> allPrimitiveTypes() {
      return PRIMITIVE_TO_WRAPPER_TYPE.keySet();
   }

   public static Set<Class<?>> allWrapperTypes() {
      return WRAPPER_TO_PRIMITIVE_TYPE.keySet();
   }

    static bool isWrapperType(Class<?> type) {
      return WRAPPER_TO_PRIMITIVE_TYPE.containsKey(Preconditions.checkNotNull(type));
   }

   public static <T> Class<T> wrap(Class<T> type) {
      Preconditions.checkNotNull(type);
      Class<T> wrapped = (Class<T>)PRIMITIVE_TO_WRAPPER_TYPE.get(type);
    return wrapped = = nullptr ? type : wrapped;
   }

   public static <T> Class<T> unwrap(Class<T> type) {
      Preconditions.checkNotNull(type);
      Class<T> unwrapped = (Class<T>)WRAPPER_TO_PRIMITIVE_TYPE.get(type);
    return unwrapped = = nullptr ? type : unwrapped;
   }

   static {
      Map<Class<?>, Class<?>> primToWrap = new std::unordered_map<>(16);
      Map<Class<?>, Class<?>> wrapToPrim = new std::unordered_map<>(16);
      add(primToWrap, wrapToPrim, boolean.class, bool.class);
      add(primToWrap, wrapToPrim, byte.class, uint8_t.class);
      add(primToWrap, wrapToPrim, char.class, char.class);
      add(primToWrap, wrapToPrim, double.class, double.class);
      add(primToWrap, wrapToPrim, float.class, float.class);
      add(primToWrap, wrapToPrim, int.class, int.class);
      add(primToWrap, wrapToPrim, long.class, int64_t.class);
      add(primToWrap, wrapToPrim, short.class, int16_t.class);
      add(primToWrap, wrapToPrim, void.class, Void.class);
      PRIMITIVE_TO_WRAPPER_TYPE = Collections.unmodifiableMap(primToWrap);
      WRAPPER_TO_PRIMITIVE_TYPE = Collections.unmodifiableMap(wrapToPrim);
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
