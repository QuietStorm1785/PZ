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

class WebSocketCloseCode {
public:
    static const int NORMAL = 1000;
    static const int AWAY = 1001;
    static const int UNCONFORMED = 1002;
    static const int UNACCEPTABLE = 1003;
    static const int NONE = 1005;
    static const int ABNORMAL = 1006;
    static const int INCONSISTENT = 1007;
    static const int VIOLATED = 1008;
    static const int OVERSIZE = 1009;
    static const int UNEXTENDED = 1010;
    static const int UNEXPECTED = 1011;
    static const int INSECURE = 1015;

    private WebSocketCloseCode() {
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
