#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlNsForm.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


// $VF: synthetic class
class PropertyInfoImpl {
public:
   static {
      try {
         $SwitchMap$javax$xml$bind$annotation$XmlNsForm[XmlNsForm.QUALIFIED.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$javax$xml$bind$annotation$XmlNsForm[XmlNsForm.UNQUALIFIED.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$javax$xml$bind$annotation$XmlNsForm[XmlNsForm.UNSET.ordinal()] = 3;
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
