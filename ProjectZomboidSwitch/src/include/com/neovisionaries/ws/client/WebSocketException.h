#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

class WebSocketException : public Exception {
public:
    static const long serialVersionUID = 1L;
    const WebSocketError mError;

    public WebSocketException(WebSocketError error) {
      this.mError = error;
   }

    public WebSocketException(WebSocketError error, const std::string& message) {
      super(message);
      this.mError = error;
   }

    public WebSocketException(WebSocketError error, std::exception cause) {
      super(cause);
      this.mError = error;
   }

    public WebSocketException(WebSocketError error, const std::string& message, std::exception cause) {
      super(message, cause);
      this.mError = error;
   }

    WebSocketError getError() {
      return this.mError;
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
