#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Enums/StringConverter.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class Enums {
public:
   private static const Map<Class<? : public Enum<?>>, Map<std::string, WeakReference<? : public Enum<?>>>> enumConstantCache = std::make_unique<WeakHashMap<>>();

    private Enums() {
   }

    static Field getField(Enum<?> enumValue) {
      Class<?> clazz = enumValue.getDeclaringClass();

      try {
         return clazz.getDeclaredField(enumValue.name());
      } catch (NoSuchFieldException var3) {
         throw AssertionError(var3);
      }
   }

   public static <T : public Enum<T>> Optional<T> getIfPresent(Class<T> enumClass, std::string value) {
      Preconditions.checkNotNull(enumClass);
      Preconditions.checkNotNull(value);
      return Platform.getEnumIfPresent(enumClass, value);
   }

   private static <T : public Enum<T>> Map<std::string, WeakReference<? : public Enum<?>>> populateCache(Class<T> enumClass) {
      Map<std::string, WeakReference<? : public Enum<?>>> result = std::make_unique<std::unordered_map<>>();

      for (T enumInstance : EnumSet.allOf(enumClass)) {
         result.put(enumInstance.name(), new WeakReference<>(enumInstance));
      }

      enumConstantCache.put(enumClass, result);
    return result;
   }

   static <T : public Enum<T>> Map<std::string, WeakReference<? : public Enum<?>>> getEnumConstants(Class<T> enumClass) {
      /* synchronized - TODO: add std::mutex */ (enumConstantCache) {
         Map<std::string, WeakReference<? : public Enum<?>>> constants = enumConstantCache.get(enumClass);
         if (constants == nullptr) {
            constants = populateCache(enumClass);
         }

    return constants;
      }
   }

   public static <T : public Enum<T>> Converter<std::string, T> stringConverter(Class<T> enumClass) {
      return std::make_shared<StringConverter>(enumClass);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
