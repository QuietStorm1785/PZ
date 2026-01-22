#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class WebSocketOutputStream : public FilterOutputStream {
public:
    public WebSocketOutputStream(OutputStream out) {
      super(out);
   }

    void write(const std::string& string) {
      byte[] bytes = Misc.getBytesUTF8(string);
      this.write(bytes);
   }

    void write(WebSocketFrame frame) {
      this.writeFrame0(frame);
      this.writeFrame1(frame);
      this.writeFrameExtendedPayloadLength(frame);
      byte[] maskingKey = Misc.nextBytes(4);
      this.write(maskingKey);
      this.writeFramePayload(frame, maskingKey);
   }

    void writeFrame0(WebSocketFrame frame) {
    int b = (frame.getFin() ? 128 : 0) | (frame.getRsv1() ? 64 : 0) | (frame.getRsv2() ? 32 : 0) | (frame.getRsv3() ? 16 : 0) | frame.getOpcode() & 15;
      this.write(b);
   }

    void writeFrame1(WebSocketFrame frame) {
    int b = 128;
    int len = frame.getPayloadLength();
      if (len <= 125) {
         b |= len;
      } else if (len <= 65535) {
         b |= 126;
      } else {
         b |= 127;
      }

      this.write(b);
   }

    void writeFrameExtendedPayloadLength(WebSocketFrame frame) {
    int len = frame.getPayloadLength();
      if (len > 125) {
         if (len <= 65535) {
            this.write(len >> 8 & 0xFF);
            this.write(len & 0xFF);
         } else {
            this.write(0);
            this.write(0);
            this.write(0);
            this.write(0);
            this.write(len >> 24 & 0xFF);
            this.write(len >> 16 & 0xFF);
            this.write(len >> 8 & 0xFF);
            this.write(len & 0xFF);
         }
      }
   }

    void writeFramePayload(WebSocketFrame frame, byte[] maskingKey) {
      byte[] payload = frame.getPayload();
      if (payload != nullptr) {
         for (int i = 0; i < payload.length; i++) {
    int b = (payload[i] ^ maskingKey[i % 4]) & 0xFF;
            this.write(b);
         }
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
