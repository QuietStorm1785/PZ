#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


// $VF: synthetic class
class StructureLoader {
public:
   static {
      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.ATTRIBUTE.ordinal()] = 1;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.ELEMENT.ordinal()] = 2;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.REFERENCE.ordinal()] = 3;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.MAP.ordinal()] = 4;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.VALUE.ordinal()] = 5;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
