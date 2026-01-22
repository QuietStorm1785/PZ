#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableClassToInstanceMap/Builder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableClassToInstanceMap {
public:
   private static const ImmutableClassToInstanceMap<Object> EMPTY = new ImmutableClassToInstanceMap<>(ImmutableMap.of());
   private const ImmutableMap<Class<? : public B>, B> delegate;

   public static <B> ImmutableClassToInstanceMap<B> of() {
      return (ImmutableClassToInstanceMap<B>)EMPTY;
   }

   public static <B, T : public B> ImmutableClassToInstanceMap<B> of(Class<T> type, T value) {
      ImmutableMap<Class<? : public B>, B> map = ImmutableMap.of(type, value);
      return new ImmutableClassToInstanceMap<>(map);
   }

   public static <B> Builder<B> builder() {
      return std::make_unique<Builder>();
   }

   public static <B, S : public B> ImmutableClassToInstanceMap<B> copyOf(Map<? : public Class<? : public S>, ? : public S> map) {
      return dynamic_cast<ImmutableClassToInstanceMap*>(map) != nullptr ? (ImmutableClassToInstanceMap)map : std::make_unique<Builder>().putAll(map).build();
   }

    private ImmutableClassToInstanceMap(ImmutableMap<Class<? extends, B> delegate) {
      this.delegate = delegate;
   }

   protected Map<Class<? : public B>, B> delegate() {
      return this.delegate;
   }

   public <T : public B> T getInstance(Class<T> type) {
      return (T)this.delegate.get(Preconditions.checkNotNull(type));
   }

   public <T : public B> T putInstance(Class<T> type, T value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void* readResolve() {
      return this.empty() ? of() : this;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
