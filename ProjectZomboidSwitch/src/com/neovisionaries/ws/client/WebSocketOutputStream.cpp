#include <string>
#include "com\neovisionaries\ws\client/WebSocketOutputStream.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

public WebSocketOutputStream::WebSocketOutputStream(OutputStream out) {
    // TODO: Implement WebSocketOutputStream
    return nullptr;
}

void WebSocketOutputStream::write(const std::string& string) {
    // TODO: Implement write
}

void WebSocketOutputStream::write(WebSocketFrame frame) {
    // TODO: Implement write
}

void WebSocketOutputStream::writeFrame0(WebSocketFrame frame) {
    // TODO: Implement writeFrame0
}

void WebSocketOutputStream::writeFrame1(WebSocketFrame frame) {
    // TODO: Implement writeFrame1
}

void WebSocketOutputStream::writeFrameExtendedPayloadLength(WebSocketFrame frame) {
    // TODO: Implement writeFrameExtendedPayloadLength
}

void WebSocketOutputStream::writeFramePayload(WebSocketFrame frame, byte[] maskingKey) {
    // TODO: Implement writeFramePayload
}

} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
