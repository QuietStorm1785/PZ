#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/collect/ForwardingMap.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/reflect/MutableTypeToInstanceMap/UnmodifiableEntry.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace reflect {


class MutableTypeToInstanceMap {
public:
   private const Map<TypeToken<? : public B>, B> backingMap = Maps.newHashMap();

   public <T : public B> T getInstance(Class<T> type) {
      return this.trustedGet(TypeToken.of(type));
   }

   public <T : public B> T putInstance(Class<T> type, @Nullable T value) {
      return this.trustedPut(TypeToken.of(type), value);
   }

   public <T : public B> T getInstance(TypeToken<T> type) {
      return this.trustedGet(type.rejectTypeVariables());
   }

   public <T : public B> T putInstance(TypeToken<T> type, @Nullable T value) {
      return this.trustedPut(type.rejectTypeVariables(), value);
   }

    B put(TypeToken<? extends, B value) {
      throw UnsupportedOperationException("Please use putInstance() instead.");
   }

    void putAll(Map<? extends, ? extends) {
      throw UnsupportedOperationException("Please use putInstance() instead.");
   }

   public Set<Entry<TypeToken<? : public B>, B>> entrySet() {
      return UnmodifiableEntry.transformEntries(super.entrySet());
   }

   protected Map<TypeToken<? : public B>, B> delegate() {
      return this.backingMap;
   }

   private <T : public B> T trustedPut(TypeToken<T> type, @Nullable T value) {
      return (T)this.backingMap.put(type, (B)value);
   }

   private <T : public B> T trustedGet(TypeToken<T> type) {
      return (T)this.backingMap.get(type);
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
