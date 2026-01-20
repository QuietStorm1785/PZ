#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace mashape {
namespace unirest {
namespace http {
namespace exceptions {

class UnirestException : public Exception {
public:
    static const long serialVersionUID = -3714840499934575734L;

    public UnirestException(std::exception e) {
      super(e);
   }

    public UnirestException(const std::string& msg) {
      super(msg);
   }
}
} // namespace exceptions
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
