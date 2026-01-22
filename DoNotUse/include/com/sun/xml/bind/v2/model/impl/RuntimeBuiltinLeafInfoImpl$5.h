#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/DatatypeConverterImpl.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/StringImpl.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "javax/xml/namespace/QName.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
   RuntimeBuiltinLeafInfoImpl$5(Class type, QName... typeNames) {
      super(type, typeNames);
   }

    Date parse(CharSequence text) {
      return DatatypeConverterImpl._parseDateTime(text).getTime();
   }

    std::string print(Date v) {
    XMLSerializer xs = XMLSerializer.getInstance();
    QName type = xs.getSchemaType();
    GregorianCalendar cal = std::make_shared<GregorianCalendar>(0, 0, 0);
      cal.setTime(v);
      return type != nullptr && "http://www.w3.org/2001/XMLSchema" == type.getNamespaceURI()) && "date" == type.getLocalPart())
         ? DatatypeConverterImpl._printDate(cal)
         : DatatypeConverterImpl._printDateTime(cal);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
