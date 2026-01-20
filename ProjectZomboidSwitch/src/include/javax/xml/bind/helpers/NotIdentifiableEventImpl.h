#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/NotIdentifiableEvent.h"
#include "javax/xml/bind/ValidationEventLocator.h"

namespace javax {
namespace xml {
namespace bind {
namespace helpers {


class NotIdentifiableEventImpl : public ValidationEventImpl {
public:
    public NotIdentifiableEventImpl(int _severity, const std::string& _message, ValidationEventLocator _locator) {
      super(_severity, _message, _locator);
   }

    public NotIdentifiableEventImpl(int _severity, const std::string& _message, ValidationEventLocator _locator, std::exception _linkedException) {
      super(_severity, _message, _locator, _linkedException);
   }
}
} // namespace helpers
} // namespace bind
} // namespace xml
} // namespace javax
