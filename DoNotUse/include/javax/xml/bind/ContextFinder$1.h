#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/ServiceLoaderUtil/ExceptionHandler.h"

namespace javax {
namespace xml {
namespace bind {


class ContextFinder {
public:
    JAXBException createException(std::exception throwable, const std::string& message) {
      return std::make_shared<JAXBException>(message, throwable);
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
