#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/collect/ForwardingMap.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/reflect/ImmutableTypeToInstanceMap/Builder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class ImmutableTypeToInstanceMap {
public:
   private const ImmutableMap<TypeToken<? : public B>, B> delegate;

   public static <B> ImmutableTypeToInstanceMap<B> of() {
      return new ImmutableTypeToInstanceMap<>(ImmutableMap.of());
   }

   public static <B> Builder<B> builder() {
      return std::make_shared<Builder>(nullptr);
   }

    private ImmutableTypeToInstanceMap(ImmutableMap<TypeToken<? extends, B> delegate) {
      this.delegate = delegate;
   }

   public <T : public B> T getInstance(TypeToken<T> type) {
      return this.trustedGet(type.rejectTypeVariables());
   }

   public <T : public B> T putInstance(TypeToken<T> type, T value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public <T : public B> T getInstance(Class<T> type) {
      return this.trustedGet(TypeToken.of(type));
   }

   public <T : public B> T putInstance(Class<T> type, T value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    B put(TypeToken<? extends, B value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   protected Map<TypeToken<? : public B>, B> delegate() {
      return this.delegate;
   }

   private <T : public B> T trustedGet(TypeToken<T> type) {
      return (T)this.delegate.get(type);
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
