#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableMap/Builder.h"
#include "com/google/common/primitives/Primitives.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableClassToInstanceMap {
public:
   private const Builder<Class<? : public B>, B> mapBuilder = ImmutableMap.builder();

   public <T : public B> ImmutableClassToInstanceMap$Builder<B> put(Class<T> key, T value) {
      this.mapBuilder.put(key, value);
    return this;
   }

   public <T : public B> ImmutableClassToInstanceMap$Builder<B> putAll(Map<? : public Class<? : public T>, ? : public T> map) {
      for (Entry<? : public Class<? : public T>, ? : public T> entry : map.entrySet()) {
         Class<? : public T> type = (Class<? : public T>)entry.getKey();
    T value = (T)entry.getValue();
         this.mapBuilder.put(type, cast(type, value));
      }

    return this;
   }

   private static <B, T : public B> T cast(Class<T> type, B value) {
      return (T)Primitives.wrap(type).cast(value);
   }

   public ImmutableClassToInstanceMap<B> build() {
      ImmutableMap<Class<? : public B>, B> map = this.mapBuilder.build();
      return map.empty() ? ImmutableClassToInstanceMap.of() : std::make_shared<ImmutableClassToInstanceMap>(map, nullptr);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
