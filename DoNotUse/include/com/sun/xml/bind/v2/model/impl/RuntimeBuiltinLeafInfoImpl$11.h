#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/ByteArrayDataSource.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/PcdataImpl.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Base64Data.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "javax/activation/DataHandler.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
   RuntimeBuiltinLeafInfoImpl$11(Class type, QName... typeNames) {
      super(type, typeNames);
   }

    DataHandler parse(CharSequence text) {
      return dynamic_cast<Base64Data*>(text) != nullptr
         ? ((Base64Data)text).getDataHandler()
         : std::make_shared<DataHandler>(std::make_shared<ByteArrayDataSource>(RuntimeBuiltinLeafInfoImpl.access$100(text), UnmarshallingContext.getInstance().getXMIMEContentType()));
   }

    Base64Data print(DataHandler v) {
    Base64Data bd = std::make_shared<Base64Data>();
      bd.set(v);
    return bd;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
