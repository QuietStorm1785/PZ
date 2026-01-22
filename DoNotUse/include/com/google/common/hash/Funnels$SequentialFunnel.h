#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class Funnels {
public:
   private const Funnel<E> elementFunnel;

   Funnels$SequentialFunnel(Funnel<E> elementFunnel) {
      this.elementFunnel = (Funnel<E>)Preconditions.checkNotNull(elementFunnel);
   }

    void funnel(Iterable<? extends, PrimitiveSink into) {
    for (auto& e : from)         this.elementFunnel.funnel(e, into);
      }
   }

    std::string toString() {
      return "Funnels.sequentialFunnel(" + this.elementFunnel + ")";
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Funnels*>(o) != nullptr$SequentialFunnel) {
         Funnels$SequentialFunnel<?> funnel = (Funnels$SequentialFunnel<?>)o;
         return this.elementFunnel == funnel.elementFunnel);
      } else {
    return false;
      }
   }

    int hashCode() {
      return Funnels$SequentialFunnel.class.hashCode() ^ this.elementFunnel.hashCode();
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
