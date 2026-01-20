#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/core/WildcardMode.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


// $VF: synthetic class
class XmlSchemaGenerator {
public:
   static {
      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$WildcardMode[WildcardMode.LAX.ordinal()] = 1;
      } catch (NoSuchFieldError var11) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$WildcardMode[WildcardMode.SKIP.ordinal()] = 2;
      } catch (NoSuchFieldError var10) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$WildcardMode[WildcardMode.STRICT.ordinal()] = 3;
      } catch (NoSuchFieldError var9) {
      }

      $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind = new int[PropertyKind.values().length];

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.ATTRIBUTE.ordinal()] = 1;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.VALUE.ordinal()] = 2;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.ELEMENT.ordinal()] = 3;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.REFERENCE.ordinal()] = 4;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.MAP.ordinal()] = 5;
      } catch (NoSuchFieldError var4) {
      }

      $SwitchMap$com$sun$xml$bind$v2$model$core$ID = new int[ID.values().length];

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$ID[ID.ID.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$ID[ID.IDREF.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$ID[ID.NONE.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
