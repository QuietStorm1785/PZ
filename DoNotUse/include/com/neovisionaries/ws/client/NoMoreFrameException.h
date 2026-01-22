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

class NoMoreFrameException : public WebSocketException {
public:
    static const long serialVersionUID = 1L;

    public NoMoreFrameException() {
      super(WebSocketError.NO_MORE_FRAME, "No more WebSocket frame from the server.");
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
