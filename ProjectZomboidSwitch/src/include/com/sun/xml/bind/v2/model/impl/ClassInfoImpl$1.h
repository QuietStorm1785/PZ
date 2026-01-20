#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/impl/ClassInfoImpl/PropertyGroup.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


// $VF: synthetic class
class ClassInfoImpl {
public:
   static {
      try {
         $SwitchMap$com$sun$xml$bind$v2$model$impl$ClassInfoImpl$PropertyGroup[PropertyGroup.TRANSIENT.ordinal()] = 1;
      } catch (NoSuchFieldError var12) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$impl$ClassInfoImpl$PropertyGroup[PropertyGroup.ANY_ATTRIBUTE.ordinal()] = 2;
      } catch (NoSuchFieldError var11) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$impl$ClassInfoImpl$PropertyGroup[PropertyGroup.ATTRIBUTE.ordinal()] = 3;
      } catch (NoSuchFieldError var10) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$impl$ClassInfoImpl$PropertyGroup[PropertyGroup.VALUE.ordinal()] = 4;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$impl$ClassInfoImpl$PropertyGroup[PropertyGroup.ELEMENT.ordinal()] = 5;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$impl$ClassInfoImpl$PropertyGroup[PropertyGroup.ELEMENT_REF.ordinal()] = 6;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$impl$ClassInfoImpl$PropertyGroup[PropertyGroup.MAP.ordinal()] = 7;
      } catch (NoSuchFieldError var6) {
      }

      $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind = new int[PropertyKind.values().length];

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.ELEMENT.ordinal()] = 1;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.REFERENCE.ordinal()] = 2;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.MAP.ordinal()] = 3;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.VALUE.ordinal()] = 4;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[PropertyKind.ATTRIBUTE.ordinal()] = 5;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
