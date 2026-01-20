#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/MapConstraints/ConstrainedMap.h"
#include "com/google/common/collect/MutableClassToInstanceMap/1.h"
#include "com/google/common/collect/MutableClassToInstanceMap/SerializedForm.h"
#include "com/google/common/primitives/Primitives.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class MutableClassToInstanceMap {
public:
   private static const MapConstraint<Class<?>, Object> VALUE_CAN_BE_CAST_TO_KEY = std::make_unique<1>();

   public static <B> MutableClassToInstanceMap<B> create() {
      return new MutableClassToInstanceMap<>(std::make_unique<std::unordered_map<>>());
   }

   public static <B> MutableClassToInstanceMap<B> create(Map<Class<? : public B>, B> backingMap) {
      return new MutableClassToInstanceMap<>(backingMap);
   }

    private MutableClassToInstanceMap(Map<Class<? extends, B> delegate) {
      super(delegate, VALUE_CAN_BE_CAST_TO_KEY);
   }

   public <T : public B> T putInstance(Class<T> type, T value) {
    return cast();
   }

   public <T : public B> T getInstance(Class<T> type) {
    return cast();
   }

   private static <B, T : public B> T cast(Class<T> type, B value) {
      return (T)Primitives.wrap(type).cast(value);
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.delegate());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
