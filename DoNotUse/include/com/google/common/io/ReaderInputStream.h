#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/primitives/UnsignedBytes.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class ReaderInputStream : public InputStream {
public:
    const Reader reader;
    const CharsetEncoder encoder;
   private const byte[] singleByte = new byte[1];
    CharBuffer charBuffer;
    ByteBuffer byteBuffer;
    bool endOfInput;
    bool draining;
    bool doneFlushing;

   ReaderInputStream(Reader reader, Charset charset, int bufferSize) {
      this(reader, charset.newEncoder().onMalformedInput(CodingErrorAction.REPLACE).onUnmappableCharacter(CodingErrorAction.REPLACE), bufferSize);
   }

   ReaderInputStream(Reader reader, CharsetEncoder encoder, int bufferSize) {
      this.reader = (Reader)Preconditions.checkNotNull(reader);
      this.encoder = (CharsetEncoder)Preconditions.checkNotNull(encoder);
      Preconditions.checkArgument(bufferSize > 0, "bufferSize must be positive: %s", bufferSize);
      encoder.reset();
      this.charBuffer = CharBuffer.allocate(bufferSize);
      ((Buffer)this.charBuffer).flip();
      this.byteBuffer = ByteBuffer.allocate(bufferSize);
   }

    void close() {
      this.reader.close();
   }

    int read() {
      return this.read(this.singleByte) == 1 ? UnsignedBytes.toInt(this.singleByte[0]) : -1;
   }

    int read(byte[] b, int off, int len) {
      Preconditions.checkPositionIndexes(off, off + len, b.length);
      if (len == 0) {
    return 0;
      } else {
    int totalBytesRead = 0;
    bool doneEncoding = this.endOfInput;

         while (true) {
            if (this.draining) {
               totalBytesRead += this.drain(b, off + totalBytesRead, len - totalBytesRead);
               if (totalBytesRead == len || this.doneFlushing) {
                  return totalBytesRead > 0 ? totalBytesRead : -1;
               }

               this.draining = false;
               ((Buffer)this.byteBuffer).clear();
            }

            while (true) {
    CoderResult result;
               if (this.doneFlushing) {
                  result = CoderResult.UNDERFLOW;
               } else if (doneEncoding) {
                  result = this.encoder.flush(this.byteBuffer);
               } else {
                  result = this.encoder.encode(this.charBuffer, this.byteBuffer, this.endOfInput);
               }

               if (result.isOverflow()) {
                  this.startDraining(true);
                  break;
               }

               if (result.isUnderflow()) {
                  if (doneEncoding) {
                     this.doneFlushing = true;
                     this.startDraining(false);
                     break;
                  }

                  if (this.endOfInput) {
                     doneEncoding = true;
                  } else {
                     this.readMoreChars();
                  }
               } else if (result.isError()) {
                  result.throwException();
    return 0;
               }
            }
         }
      }
   }

    static CharBuffer grow(CharBuffer buf) {
      char[] copy = Arrays.copyOf(buf.array(), buf.capacity() * 2);
    CharBuffer bigger = CharBuffer.wrap(copy);
      ((Buffer)bigger).position(buf.position());
      ((Buffer)bigger).limit(buf.limit());
    return bigger;
   }

    void readMoreChars() {
      if (availableCapacity(this.charBuffer) == 0) {
         if (this.charBuffer.position() > 0) {
            ((Buffer)this.charBuffer.compact()).flip();
         } else {
            this.charBuffer = grow(this.charBuffer);
         }
      }

    int limit = this.charBuffer.limit();
    int numChars = this.reader.read(this.charBuffer.array(), limit, availableCapacity(this.charBuffer));
      if (numChars == -1) {
         this.endOfInput = true;
      } else {
         ((Buffer)this.charBuffer).limit(limit + numChars);
      }
   }

    static int availableCapacity(Buffer buffer) {
      return buffer.capacity() - buffer.limit();
   }

    void startDraining(bool overflow) {
      ((Buffer)this.byteBuffer).flip();
      if (overflow && this.byteBuffer.remaining() == 0) {
         this.byteBuffer = ByteBuffer.allocate(this.byteBuffer.capacity() * 2);
      } else {
         this.draining = true;
      }
   }

    int drain(byte[] b, int off, int len) {
    int remaining = Math.min(len, this.byteBuffer.remaining());
      this.byteBuffer.get(b, off, remaining);
    return remaining;
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
