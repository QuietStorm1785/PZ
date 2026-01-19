#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include <filesystem>

namespace zombie {


class GameWindow {
:
   private char[] chars;
    ByteBuffer byteBuffer;
    CharBuffer charBuffer;
    CharsetEncoder ce;
    CharsetDecoder cd;

   private GameWindow$StringUTF() {
   }

    int encode(std::string_view var1) {
      if (this.chars == nullptr || this.chars.length < var1.length()) {
    int var2 = (var1.length() + 128 - 1) / 128 * 128;
         this.chars = new char[var2];
         this.charBuffer = CharBuffer.wrap(this.chars);
      }

      var1.getChars(0, var1.length(), this.chars, 0);
      this.charBuffer.limit(var1.length());
      this.charBuffer.position(0);
      if (this.ce == nullptr) {
         this.ce = StandardCharsets.UTF_8.newEncoder().onMalformedInput(CodingErrorAction.REPLACE).onUnmappableCharacter(CodingErrorAction.REPLACE);
      }

      this.ce.reset();
    int var4 = (int)((double)var1.length() * this.ce.maxBytesPerChar());
      var4 = (var4 + 128 - 1) / 128 * 128;
      if (this.byteBuffer == nullptr || this.byteBuffer.capacity() < var4) {
         this.byteBuffer = ByteBuffer.allocate(var4);
      }

      this.byteBuffer.clear();
    CoderResult var3 = this.ce.encode(this.charBuffer, this.byteBuffer, true);
      return this.byteBuffer.position();
   }

    std::string decode(int var1) {
      if (this.cd == nullptr) {
         this.cd = StandardCharsets.UTF_8.newDecoder().onMalformedInput(CodingErrorAction.REPLACE).onUnmappableCharacter(CodingErrorAction.REPLACE);
      }

      this.cd.reset();
    int var2 = (int)((double)var1 * this.cd.maxCharsPerByte());
      if (this.chars == nullptr || this.chars.length < var2) {
    int var3 = (var2 + 128 - 1) / 128 * 128;
         this.chars = new char[var3];
         this.charBuffer = CharBuffer.wrap(this.chars);
      }

      this.charBuffer.clear();
    CoderResult var4 = this.cd.decode(this.byteBuffer, this.charBuffer, true);
      return new String(this.chars, 0, this.charBuffer.position());
   }

    void save(ByteBuffer var1, std::string_view var2) {
      if (var2 != nullptr && !var2.isEmpty()) {
    int var3 = this.encode(var2);
         var1.putShort((short)var3);
         this.byteBuffer.flip();
         var1.put(this.byteBuffer);
      } else {
         var1.putShort((short)0);
      }
   }

    std::string load(ByteBuffer var1) {
    short var2 = var1.getShort();
      if (var2 <= 0) {
         return "";
      } else {
    int var3 = (var2 + 128 - 1) / 128 * 128;
         if (this.byteBuffer == nullptr || this.byteBuffer.capacity() < var3) {
            this.byteBuffer = ByteBuffer.allocate(var3);
         }

         this.byteBuffer.clear();
         if (var1.remaining() < var2) {
            DebugLog.General.error("GameWindow.StringUTF.load> numBytes:" + var2 + " is higher than the remaining bytes in the buffer:" + var1.remaining());
         }

    int var4 = var1.limit();
         var1.limit(var1.position() + var2);
         this.byteBuffer.put(var1);
         var1.limit(var4);
         this.byteBuffer.flip();
         return this.decode(var2);
      }
   }
}
} // namespace zombie
