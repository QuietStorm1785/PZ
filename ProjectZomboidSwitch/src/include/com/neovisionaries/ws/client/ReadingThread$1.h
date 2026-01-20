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

// $VF: synthetic class
class ReadingThread {
public:
   static {
      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.INSUFFICENT_DATA.ordinal()] = 1;
      } catch (NoSuchFieldError var15) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.INVALID_PAYLOAD_LENGTH.ordinal()] = 2;
      } catch (NoSuchFieldError var14) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.NO_MORE_FRAME.ordinal()] = 3;
      } catch (NoSuchFieldError var13) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.TOO_LONG_PAYLOAD.ordinal()] = 4;
      } catch (NoSuchFieldError var12) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.INSUFFICIENT_MEMORY_FOR_PAYLOAD.ordinal()] = 5;
      } catch (NoSuchFieldError var11) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.NON_ZERO_RESERVED_BITS.ordinal()] = 6;
      } catch (NoSuchFieldError var10) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.UNEXPECTED_RESERVED_BIT.ordinal()] = 7;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.UNKNOWN_OPCODE.ordinal()] = 8;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.FRAME_MASKED.ordinal()] = 9;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.FRAGMENTED_CONTROL_FRAME.ordinal()] = 10;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.UNEXPECTED_CONTINUATION_FRAME.ordinal()] = 11;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.CONTINUATION_NOT_CLOSED.ordinal()] = 12;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.TOO_LONG_CONTROL_FRAME_PAYLOAD.ordinal()] = 13;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.INTERRUPTED_IN_READING.ordinal()] = 14;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$com$neovisionaries$ws$client$WebSocketError[WebSocketError.IO_ERROR_IN_READING.ordinal()] = 15;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
