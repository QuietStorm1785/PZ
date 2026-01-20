#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/WhiteSpaceProcessor.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/FilterTransducer.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeModelBuilder {
public:
   public RuntimeModelBuilder$IDTransducerImpl(Transducer<ValueT> core) {
      super(core);
   }

    ValueT parse(CharSequence lexical) {
    std::string value = WhiteSpaceProcessor.trim(lexical);
      UnmarshallingContext.getInstance().addToIdTable(value);
      return (ValueT)this.core.parse(value);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
