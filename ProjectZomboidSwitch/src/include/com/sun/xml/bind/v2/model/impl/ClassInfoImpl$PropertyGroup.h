#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/impl/ClassInfoImpl/SecondaryAnnotation.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


enum class ClassInfoImpl {
   TRANSIENT(false, false, false, false, false, false),
   ANY_ATTRIBUTE(true, false, false, false, false, false),
   ATTRIBUTE(true, true, true, false, true, true),
   VALUE(true, true, true, false, true, true),
   ELEMENT(true, true, true, true, true, true),
   ELEMENT_REF(true, false, false, true, false, false),
   MAP(false, false, false, true, false, false);

    const int allowedsecondaryAnnotations;

   private ClassInfoImpl$PropertyGroup(boolean... bits) {
    int mask = 0;
      if (!$assertionsDisabled && bits.length != ClassInfoImpl.access$300().length) {
         throw std::make_unique<AssertionError>();
      } else {
         for (int i = 0; i < bits.length; i++) {
            if (bits[i]) {
               mask |= ClassInfoImpl.access$300()[i].bitMask;
            }
         }

         this.allowedsecondaryAnnotations = ~mask;
      }
   }

    bool allows(SecondaryAnnotation a) {
      return (this.allowedsecondaryAnnotations & a.bitMask) == 0;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
