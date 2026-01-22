#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/ImmutableMap/Builder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class ImmutableTypeToInstanceMap {
public:
   private const Builder<TypeToken<? : public B>, B> mapBuilder = ImmutableMap.builder();

   private ImmutableTypeToInstanceMap$Builder() {
   }

   public <T : public B> ImmutableTypeToInstanceMap$Builder<B> put(Class<T> key, T value) {
      this.mapBuilder.put(TypeToken.of(key), value);
    return this;
   }

   public <T : public B> ImmutableTypeToInstanceMap$Builder<B> put(TypeToken<T> key, T value) {
      this.mapBuilder.put(key.rejectTypeVariables(), value);
    return this;
   }

   public ImmutableTypeToInstanceMap<B> build() {
      return std::make_shared<ImmutableTypeToInstanceMap>(this.mapBuilder.build(), nullptr);
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
