#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/Bridge.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class InternalBridge {
public:
    protected InternalBridge(JAXBContextImpl context) {
      super(context);
   }

    JAXBContextImpl getContext() {
      return this.context;
   }

   abstract void marshal(T var1, XMLSerializer var2) throws IOException, SAXException, XMLStreamException;
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
