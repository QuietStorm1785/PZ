#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/ValidationEventHandler.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {


class IDResolver {
public:
    void startDocument(ValidationEventHandler eventHandler) {
   }

    void endDocument() {
   }

   public abstract void bind(std::string var1, Object var2) throws SAXException;

   public abstract Callable<?> resolve(std::string var1, Class var2) throws SAXException;
}
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
