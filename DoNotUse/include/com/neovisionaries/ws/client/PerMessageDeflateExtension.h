#pragma once
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


class PerMessageDeflateExtension : public PerMessageCompressionExtension {
public:
    static const std::string SERVER_NO_CONTEXT_TAKEOVER = "server_no_context_takeover";
    static const std::string CLIENT_NO_CONTEXT_TAKEOVER = "client_no_context_takeover";
    static const std::string SERVER_MAX_WINDOW_BITS = "server_max_window_bits";
    static const std::string CLIENT_MAX_WINDOW_BITS = "client_max_window_bits";
   private static const byte[] COMPRESSION_TERMINATOR = new byte[]{0, 0, -1, -1};
    static const int MIN_BITS = 8;
    static const int MAX_BITS = 15;
    static const int MIN_WINDOW_SIZE = 256;
    static const int MAX_WINDOW_SIZE = 32768;
    static const int INCOMING_SLIDING_WINDOW_MARGIN = 1024;
    bool mServerNoContextTakeover;
    bool mClientNoContextTakeover;
    int mServerWindowSize = 32768;
    int mClientWindowSize = 32768;
    int mIncomingSlidingWindowBufferSize;
    ByteArray mIncomingSlidingWindow;

    public PerMessageDeflateExtension() {
      super("permessage-deflate");
   }

    public PerMessageDeflateExtension(const std::string& name) {
      super(name);
   }

    void validate() {
      for (Entry<std::string, std::string> entry : this.getParameters().entrySet()) {
         this.validateParameter(entry.getKey(), entry.getValue());
      }

      this.mIncomingSlidingWindowBufferSize = this.mServerWindowSize + 1024;
   }

    bool isServerNoContextTakeover() {
      return this.mServerNoContextTakeover;
   }

    bool isClientNoContextTakeover() {
      return this.mClientNoContextTakeover;
   }

    int getServerWindowSize() {
      return this.mServerWindowSize;
   }

    int getClientWindowSize() {
      return this.mClientWindowSize;
   }

    void validateParameter(const std::string& key, const std::string& value) {
      if ("server_no_context_takeover" == key)) {
         this.mServerNoContextTakeover = true;
      } else if ("client_no_context_takeover" == key)) {
         this.mClientNoContextTakeover = true;
      } else if ("server_max_window_bits" == key)) {
         this.mServerWindowSize = this.computeWindowSize(key, value);
      } else {
         if (!"client_max_window_bits" == key)) {
            throw WebSocketException(
               WebSocketError.PERMESSAGE_DEFLATE_UNSUPPORTED_PARAMETER, "permessage-deflate extension contains an unsupported parameter: " + key
            );
         }

         this.mClientWindowSize = this.computeWindowSize(key, value);
      }
   }

    int computeWindowSize(const std::string& key, const std::string& value) {
    int bits = this.extractMaxWindowBits(key, value);
    int size = 256;

      for (int i = 8; i < bits; i++) {
         size *= 2;
      }

    return size;
   }

    int extractMaxWindowBits(const std::string& key, const std::string& value) {
    int bits = this.parseMaxWindowBits(value);
      if (bits < 0) {
    std::string message = std::string.format("The value of %s parameter of permessage-deflate extension is invalid: %s", key, value);
         throw WebSocketException(WebSocketError.PERMESSAGE_DEFLATE_INVALID_MAX_WINDOW_BITS, message);
      } else {
    return bits;
      }
   }

    int parseMaxWindowBits(const std::string& value) {
      if (value == nullptr) {
         return -1;
      } else {
    int bits;
         try {
            bits = int.parseInt(value);
         } catch (NumberFormatException var4) {
            return -1;
         }

         return bits >= 8 && 15 >= bits ? bits : -1;
      }
   }

   protected byte[] decompress(byte[] compressed) throws WebSocketException {
    int inputLen = compressed.length + COMPRESSION_TERMINATOR.length;
    ByteArray input = std::make_shared<ByteArray>(inputLen);
      input.put(compressed);
      input.put(COMPRESSION_TERMINATOR);
      if (this.mIncomingSlidingWindow == nullptr) {
         this.mIncomingSlidingWindow = std::make_shared<ByteArray>(this.mIncomingSlidingWindowBufferSize);
      }

    int outPos = this.mIncomingSlidingWindow.length();

      try {
         DeflateDecompressor.decompress(input, this.mIncomingSlidingWindow);
      } catch (Exception var6) {
         throw WebSocketException(WebSocketError.DECOMPRESSION_ERROR, std::string.format("Failed to decompress the message: %s", var6.getMessage()), var6);
      }

      byte[] output = this.mIncomingSlidingWindow.toBytes(outPos);
      this.mIncomingSlidingWindow.shrink(this.mIncomingSlidingWindowBufferSize);
      if (this.mServerNoContextTakeover) {
         this.mIncomingSlidingWindow.clear();
      }

    return output;
   }

   protected byte[] compress(byte[] plain) throws WebSocketException {
      if (!this.canCompress(plain)) {
    return plain;
      } else {
         try {
            byte[] compressed = DeflateCompressor.compress(plain);
    return adjustCompressedData();
         } catch (Exception var3) {
            throw WebSocketException(WebSocketError.COMPRESSION_ERROR, std::string.format("Failed to compress the message: %s", var3.getMessage()), var3);
         }
      }
   }

    bool canCompress(byte[] plain) {
      return this.mClientWindowSize == 32768 ? true : plain.length < this.mClientWindowSize;
   }

   private static byte[] adjustCompressedData(byte[] compressed) throws FormatException {
    ByteArray data = std::make_shared<ByteArray>(compressed.length + 1);
      data.put(compressed);
      int[] bitIndex = new int[1];
      boolean[] hasEmptyBlock = new boolean[1];

      while (skipBlock(data, bitIndex, hasEmptyBlock)) {
      }

      if (hasEmptyBlock[0]) {
         return data.toBytes(0, (bitIndex[0] - 1) / 8 + 1 - 4);
      } else {
         appendEmptyBlock(data, bitIndex);
         return data.toBytes(0, (bitIndex[0] - 1) / 8 + 1);
      }
   }

    static void appendEmptyBlock(ByteArray data, int[] bitIndex) {
    int shift = bitIndex[0] % 8;
      switch (shift) {
         case 0:
         case 6:
         case 7:
            data.put(0);
         default:
            bitIndex[0] += 3;
      }
   }

    static bool skipBlock(ByteArray input, int[] bitIndex, boolean[] hasEmptyBlock) {
    bool last = input.readBit(bitIndex);
      if (last) {
         input.clearBit(bitIndex[0] - 1);
      }

    int type = input.readBits(bitIndex, 2);
    bool plain0 = false;
      switch (type) {
         case 0:
            plain0 = skipPlainBlock(input, bitIndex) == 0;
            break;
         case 1:
            skipFixedBlock(input, bitIndex);
            break;
         case 2:
            skipDynamicBlock(input, bitIndex);
            break;
         default:
            std::string message = std::string.format(
               "[%s] Bad compression type '11' at the bit index '%d'.", PerMessageDeflateExtension.class.getSimpleName(), bitIndex[0]
            );
            throw FormatException(message);
      }

      if (input.length() <= bitIndex[0] / 8) {
         last = true;
      }

      if (last && plain0) {
         hasEmptyBlock[0] = true;
      }

      return !last;
   }

    static int skipPlainBlock(ByteArray input, int[] bitIndex) {
    int bi = bitIndex[0] + 7 & -8;
    int index = bi / 8;
    int len = (input.get(index) & 255) + (input.get(index + 1) & 255) * 256;
      index += 4;
      bitIndex[0] = (index + len) * 8;
    return len;
   }

    static void skipFixedBlock(ByteArray input, int[] bitIndex) {
      skipData(input, bitIndex, FixedLiteralLengthHuffman.getInstance(), FixedDistanceHuffman.getInstance());
   }

    static void skipDynamicBlock(ByteArray input, int[] bitIndex) {
      Huffman[] tables = new Huffman[2];
      DeflateUtil.readDynamicTables(input, bitIndex, tables);
      skipData(input, bitIndex, tables[0], tables[1]);
   }

    static void skipData(ByteArray input, int[] bitIndex, Huffman literalLengthHuffman, Huffman distanceHuffman) {
      while (true) {
    int literalLength = literalLengthHuffman.readSym(input, bitIndex);
         if (literalLength == 256) {
            return;
         }

         if (0 > literalLength || literalLength > 255) {
            DeflateUtil.readLength(input, bitIndex, literalLength);
            DeflateUtil.readDistance(input, bitIndex, distanceHuffman);
         }
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
