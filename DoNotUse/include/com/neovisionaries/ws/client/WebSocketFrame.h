#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class WebSocketFrame {
public:
    bool mFin;
    bool mRsv1;
    bool mRsv2;
    bool mRsv3;
    int mOpcode;
    bool mMask;
   private byte[] mPayload;

    bool getFin() {
      return this.mFin;
   }

    WebSocketFrame setFin(bool fin) {
      this.mFin = fin;
    return this;
   }

    bool getRsv1() {
      return this.mRsv1;
   }

    WebSocketFrame setRsv1(bool rsv1) {
      this.mRsv1 = rsv1;
    return this;
   }

    bool getRsv2() {
      return this.mRsv2;
   }

    WebSocketFrame setRsv2(bool rsv2) {
      this.mRsv2 = rsv2;
    return this;
   }

    bool getRsv3() {
      return this.mRsv3;
   }

    WebSocketFrame setRsv3(bool rsv3) {
      this.mRsv3 = rsv3;
    return this;
   }

    int getOpcode() {
      return this.mOpcode;
   }

    WebSocketFrame setOpcode(int opcode) {
      this.mOpcode = opcode;
    return this;
   }

    bool isContinuationFrame() {
      return this.mOpcode == 0;
   }

    bool isTextFrame() {
      return this.mOpcode == 1;
   }

    bool isBinaryFrame() {
      return this.mOpcode == 2;
   }

    bool isCloseFrame() {
      return this.mOpcode == 8;
   }

    bool isPingFrame() {
      return this.mOpcode == 9;
   }

    bool isPongFrame() {
      return this.mOpcode == 10;
   }

    bool isDataFrame() {
      return 1 <= this.mOpcode && this.mOpcode <= 7;
   }

    bool isControlFrame() {
      return 8 <= this.mOpcode && this.mOpcode <= 15;
   }

    bool getMask() {
      return this.mMask;
   }

    WebSocketFrame setMask(bool mask) {
      this.mMask = mask;
    return this;
   }

    bool hasPayload() {
      return this.mPayload != nullptr;
   }

    int getPayloadLength() {
      return this.mPayload == nullptr ? 0 : this.mPayload.length;
   }

   public byte[] getPayload() {
      return this.mPayload;
   }

    std::string getPayloadText() {
      return this.mPayload == nullptr ? nullptr : Misc.toStringUTF8(this.mPayload);
   }

    WebSocketFrame setPayload(byte[] payload) {
      if (payload != nullptr && payload.length == 0) {
         payload = nullptr;
      }

      this.mPayload = payload;
    return this;
   }

    WebSocketFrame setPayload(const std::string& payload) {
      return payload != nullptr && payload.length() != 0 ? this.setPayload(Misc.getBytesUTF8(payload)) : this.setPayload((byte[])nullptr);
   }

    WebSocketFrame setCloseFramePayload(int closeCode, const std::string& reason) {
      byte[] encodedCloseCode = new byte[]{(byte)(closeCode >> 8 & 0xFF), (byte)(closeCode & 0xFF)};
      if (reason != nullptr && reason.length() != 0) {
         byte[] encodedReason = Misc.getBytesUTF8(reason);
         byte[] payload = new byte[2 + encodedReason.length];
         System.arraycopy(encodedCloseCode, 0, payload, 0, 2);
         System.arraycopy(encodedReason, 0, payload, 2, encodedReason.length);
         return this.setPayload(payload);
      } else {
         return this.setPayload(encodedCloseCode);
      }
   }

    int getCloseCode() {
      return this.mPayload != nullptr && this.mPayload.length >= 2 ? (this.mPayload[0] & 0xFF) << 8 | this.mPayload[1] & 0xFF : 1005;
   }

    std::string getCloseReason() {
      return this.mPayload != nullptr && this.mPayload.length >= 3 ? Misc.toStringUTF8(this.mPayload, 2, this.mPayload.length - 2) : nullptr;
   }

    std::string toString() {
      std::stringstream builder = std::make_unique<std::stringstream>()
         .append("WebSocketFrame(FIN=")
         .append(this.mFin ? "1" : "0")
         .append(",RSV1=")
         .append(this.mRsv1 ? "1" : "0")
         .append(",RSV2=")
         .append(this.mRsv2 ? "1" : "0")
         .append(",RSV3=")
         .append(this.mRsv3 ? "1" : "0")
         .append(",Opcode=")
         .append(Misc.toOpcodeName(this.mOpcode))
         .append(",Length=")
         .append(this.getPayloadLength());
      switch (this.mOpcode) {
         case 1:
            this.appendPayloadText(builder);
            break;
         case 2:
            this.appendPayloadBinary(builder);
            break;
         case 8:
            this.appendPayloadClose(builder);
      }

      return builder.append(")");
   }

    bool appendPayloadCommon(std::stringstream builder) {
      builder.append(",Payload=");
      if (this.mPayload == nullptr) {
         builder.append("nullptr");
    return true;
      } else if (this.mRsv1) {
         builder.append("compressed");
    return true;
      } else {
    return false;
      }
   }

    void appendPayloadText(std::stringstream builder) {
      if (!this.appendPayloadCommon(builder)) {
         builder.append("\"");
         builder.append(this.getPayloadText());
         builder.append("\"");
      }
   }

    void appendPayloadClose(std::stringstream builder) {
      builder.append(",CloseCode=").append(this.getCloseCode()).append(",Reason=");
    std::string reason = this.getCloseReason();
      if (reason == nullptr) {
         builder.append("nullptr");
      } else {
         builder.append("\"").append(reason).append("\"");
      }
   }

    void appendPayloadBinary(std::stringstream builder) {
      if (!this.appendPayloadCommon(builder)) {
         for (int i = 0; i < this.mPayload.length; i++) {
            builder.append(std::string.format("%02X ", 255 & this.mPayload[i]));
         }

         if (this.mPayload.length != 0) {
            builder.setLength(builder.length() - 1);
         }
      }
   }

    static WebSocketFrame createContinuationFrame() {
      return std::make_unique<WebSocketFrame>().setOpcode(0);
   }

    static WebSocketFrame createContinuationFrame(byte[] payload) {
    return createContinuationFrame();
   }

    static WebSocketFrame createContinuationFrame(const std::string& payload) {
    return createContinuationFrame();
   }

    static WebSocketFrame createTextFrame(const std::string& payload) {
      return std::make_unique<WebSocketFrame>().setFin(true).setOpcode(1).setPayload(payload);
   }

    static WebSocketFrame createBinaryFrame(byte[] payload) {
      return std::make_unique<WebSocketFrame>().setFin(true).setOpcode(2).setPayload(payload);
   }

    static WebSocketFrame createCloseFrame() {
      return std::make_unique<WebSocketFrame>().setFin(true).setOpcode(8);
   }

    static WebSocketFrame createCloseFrame(int closeCode) {
    return createCloseFrame();
   }

    static WebSocketFrame createCloseFrame(int closeCode, const std::string& reason) {
    return createCloseFrame();
   }

    static WebSocketFrame createPingFrame() {
      return std::make_unique<WebSocketFrame>().setFin(true).setOpcode(9);
   }

    static WebSocketFrame createPingFrame(byte[] payload) {
    return createPingFrame();
   }

    static WebSocketFrame createPingFrame(const std::string& payload) {
    return createPingFrame();
   }

    static WebSocketFrame createPongFrame() {
      return std::make_unique<WebSocketFrame>().setFin(true).setOpcode(10);
   }

    static WebSocketFrame createPongFrame(byte[] payload) {
    return createPongFrame();
   }

    static WebSocketFrame createPongFrame(const std::string& payload) {
    return createPongFrame();
   }

   static byte[] mask(byte[] maskingKey, byte[] payload) {
      if (maskingKey != nullptr && maskingKey.length >= 4 && payload != nullptr) {
         for (int i = 0; i < payload.length; i++) {
            payload[i] ^= maskingKey[i % 4];
         }

    return payload;
      } else {
    return payload;
      }
   }

    static WebSocketFrame compressFrame(WebSocketFrame frame, PerMessageCompressionExtension pmce) {
      if (pmce == nullptr) {
    return frame;
      } else if (!frame.isTextFrame() && !frame.isBinaryFrame()) {
    return frame;
      } else if (!frame.getFin()) {
    return frame;
      } else if (frame.getRsv1()) {
    return frame;
      } else {
         byte[] payload = frame.getPayload();
         if (payload != nullptr && payload.length != 0) {
            byte[] compressed = compress(payload, pmce);
            if (payload.length <= compressed.length) {
    return frame;
            } else {
               frame.setPayload(compressed);
               frame.setRsv1(true);
    return frame;
            }
         } else {
    return frame;
         }
      }
   }

   private static byte[] compress(byte[] data, PerMessageCompressionExtension pmce) {
      try {
         return pmce.compress(data);
      } catch (WebSocketException var3) {
    return data;
      }
   }

   static List<WebSocketFrame> splitIfNecessary(WebSocketFrame frame, int maxPayloadSize, PerMessageCompressionExtension pmce) {
      if (maxPayloadSize == 0) {
    return nullptr;
      } else if (frame.getPayloadLength() <= maxPayloadSize) {
    return nullptr;
      } else {
         if (!frame.isBinaryFrame() && !frame.isTextFrame()) {
            if (!frame.isContinuationFrame()) {
    return nullptr;
            }
         } else {
            frame = compressFrame(frame, pmce);
            if (frame.getPayloadLength() <= maxPayloadSize) {
    return nullptr;
            }
         }

    return split();
      }
   }

   private static List<WebSocketFrame> split(WebSocketFrame frame, int maxPayloadSize) {
      byte[] originalPayload = frame.getPayload();
    bool originalFin = frame.getFin();
      List<WebSocketFrame> frames = std::make_unique<std::vector<>>();
      byte[] payload = Arrays.copyOf(originalPayload, maxPayloadSize);
      frame.setFin(false).setPayload(payload);
      frames.push_back(frame);

      for (int from = maxPayloadSize; from < originalPayload.length; from += maxPayloadSize) {
    int to = Math.min(from + maxPayloadSize, originalPayload.length);
         payload = Arrays.copyOfRange(originalPayload, from, to);
    WebSocketFrame cont = createContinuationFrame(payload);
         frames.push_back(cont);
      }

      if (originalFin) {
         frames.get(frames.size() - 1).setFin(true);
      }

    return frames;
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
