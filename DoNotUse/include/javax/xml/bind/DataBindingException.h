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

class DataBindingException : public RuntimeException {
public:
    public DataBindingException(const std::string& message, std::exception cause) {
      super(message, cause);
   }

    public DataBindingException(std::exception cause) {
      super(cause);
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
