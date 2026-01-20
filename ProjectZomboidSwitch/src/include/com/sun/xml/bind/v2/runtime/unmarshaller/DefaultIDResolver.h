#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/IDResolver.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/DefaultIDResolver/1.h"
#include "javax/xml/bind/ValidationEventHandler.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class DefaultIDResolver : public IDResolver {
public:
   private std::unordered_map<std::string, Object> idmap = nullptr;

    void startDocument(ValidationEventHandler eventHandler) {
      if (this.idmap != nullptr) {
         this.idmap.clear();
      }
   }

    void bind(const std::string& id, void* obj) {
      if (this.idmap == nullptr) {
         this.idmap = std::make_unique<std::unordered_map<>>();
      }

      this.idmap.put(id, obj);
   }

    Callable resolve(const std::string& id, Class targetType) {
      return std::make_shared<1>(this, id);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
