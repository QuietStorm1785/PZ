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

class WebSocketOpcode {
public:
    static const int CONTINUATION = 0;
    static const int TEXT = 1;
    static const int BINARY = 2;
    static const int CLOSE = 8;
    static const int PING = 9;
    static const int PONG = 10;

    private WebSocketOpcode() {
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
