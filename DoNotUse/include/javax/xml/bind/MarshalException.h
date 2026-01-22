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

class MarshalException : public JAXBException {
public:
    public MarshalException(const std::string& message) {
      this(message, nullptr, nullptr);
   }

    public MarshalException(const std::string& message, const std::string& errorCode) {
      this(message, errorCode, nullptr);
   }

    public MarshalException(std::exception exception) {
      this(nullptr, nullptr, exception);
   }

    public MarshalException(const std::string& message, std::exception exception) {
      this(message, nullptr, exception);
   }

    public MarshalException(const std::string& message, const std::string& errorCode, std::exception exception) {
      super(message, errorCode, exception);
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
