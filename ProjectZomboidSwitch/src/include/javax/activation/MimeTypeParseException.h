#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace javax {
namespace activation {

class MimeTypeParseException : public Exception {
public:
    public MimeTypeParseException() {
   }

    public MimeTypeParseException(const std::string& s) {
      super(s);
   }
}
} // namespace activation
} // namespace javax
