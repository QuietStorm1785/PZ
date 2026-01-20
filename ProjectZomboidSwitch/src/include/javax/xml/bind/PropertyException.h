#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace javax {
namespace xml {
namespace bind {

class PropertyException : public JAXBException {
public:
    public PropertyException(const std::string& message) {
      super(message);
   }

    public PropertyException(const std::string& message, const std::string& errorCode) {
      super(message, errorCode);
   }

    public PropertyException(std::exception exception) {
      super(exception);
   }

    public PropertyException(const std::string& message, std::exception exception) {
      super(message, exception);
   }

    public PropertyException(const std::string& message, const std::string& errorCode, std::exception exception) {
      super(message, errorCode, exception);
   }

    public PropertyException(const std::string& name, void* value) {
      super(Messages.format("PropertyException.NameValue", name, value));
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
