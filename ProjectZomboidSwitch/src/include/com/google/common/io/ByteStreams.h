#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/io/ByteStreams/1.h"
#include "com/google/common/io/ByteStreams/ByteArrayDataInputStream.h"
#include "com/google/common/io/ByteStreams/ByteArrayDataOutputStream.h"
#include "com/google/common/io/ByteStreams/FastByteArrayOutputStream.h"
#include "com/google/common/io/ByteStreams/LimitedInputStream.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteStreams {
public:
    static const int ZERO_COPY_CHUNK_SIZE = 524288;
    static const OutputStream NULL_OUTPUT_STREAM = std::make_shared<1>();

   static byte[] createBuffer() {
      return new byte[8192];
   }

    private ByteStreams() {
   }

    static long copy(InputStream from, OutputStream to) {
      Preconditions.checkNotNull(from);
      Preconditions.checkNotNull(to);
      byte[] buf = createBuffer();
    long total = 0L;

      while (true) {
    int r = from.read(buf);
         if (r == -1) {
    return total;
         }

         to.write(buf, 0, r);
         total += r;
      }
   }

    static long copy(ReadableByteChannel from, WritableByteChannel to) {
      Preconditions.checkNotNull(from);
      Preconditions.checkNotNull(to);
      if (dynamic_cast<FileChannel*>(from) != nullptr) {
    FileChannel sourceChannel = (FileChannel)from;
    long oldPosition = sourceChannel.position();
    long position = oldPosition;

    long copied;
         do {
            copied = sourceChannel.transferTo(position, 524288L, to);
            position += copied;
            sourceChannel.position(position);
         } while (copied > 0L || position < sourceChannel.size());

         return position - oldPosition;
      } else {
    ByteBuffer buf = ByteBuffer.wrap(createBuffer());
    long total = 0L;

         while (from.read(buf) != -1) {
            ((Buffer)buf).flip();

            while (buf.hasRemaining()) {
               total += to.write(buf);
            }

            ((Buffer)buf).clear();
         }

    return total;
      }
   }

   public static byte[] toByteArray(InputStream in) throws IOException {
    ByteArrayOutputStream out = std::make_shared<ByteArrayOutputStream>(Math.max(32, in.available()));
      copy(in, out);
      return out.toByteArray();
   }

   static byte[] toByteArray(InputStream in, int expectedSize) throws IOException {
      byte[] bytes = new byte[expectedSize];
    int remaining = expectedSize;

      while (remaining > 0) {
    int off = expectedSize - remaining;
    int read = in.read(bytes, off, remaining);
         if (read == -1) {
            return Arrays.copyOf(bytes, off);
         }

         remaining -= read;
      }

    int b = in.read();
      if (b == -1) {
    return bytes;
      } else {
    FastByteArrayOutputStream out = std::make_shared<FastByteArrayOutputStream>(nullptr);
         out.write(b);
         copy(in, out);
         byte[] result = new byte[bytes.length + out.size()];
         System.arraycopy(bytes, 0, result, 0, bytes.length);
         out.writeTo(result, bytes.length);
    return result;
      }
   }

    static long exhaust(InputStream in) {
    long total = 0L;
      byte[] buf = createBuffer();

    long read;
      while ((read = in.read(buf)) != -1L) {
         total += read;
      }

    return total;
   }

    static ByteArrayDataInput newDataInput(byte[] bytes) {
    return newDataInput(std::make_shared<ByteArrayInputStream>(bytes);
   }

    static ByteArrayDataInput newDataInput(byte[] bytes, int start) {
      Preconditions.checkPositionIndex(start, bytes.length);
    return newDataInput(std::make_shared<ByteArrayInputStream>(bytes, bytes.length -);
   }

    static ByteArrayDataInput newDataInput(ByteArrayInputStream byteArrayInputStream) {
      return std::make_shared<ByteArrayDataInputStream>((ByteArrayInputStream)Preconditions.checkNotNull(byteArrayInputStream));
   }

    static ByteArrayDataOutput newDataOutput() {
    return newDataOutput(std::make_shared<ByteArrayOutputStream>();
   }

    static ByteArrayDataOutput newDataOutput(int size) {
      if (size < 0) {
         throw IllegalArgumentException(std::string.format("Invalid size: %s", size));
      } else {
    return newDataOutput(std::make_shared<ByteArrayOutputStream>(size);
      }
   }

    static ByteArrayDataOutput newDataOutput(ByteArrayOutputStream byteArrayOutputSteam) {
      return std::make_shared<ByteArrayDataOutputStream>((ByteArrayOutputStream)Preconditions.checkNotNull(byteArrayOutputSteam));
   }

    static OutputStream nullOutputStream() {
    return NULL_OUTPUT_STREAM;
   }

    static InputStream limit(InputStream in, long limit) {
      return std::make_shared<LimitedInputStream>(in, limit);
   }

    static void readFully(InputStream in, byte[] b) {
      readFully(in, b, 0, b.length);
   }

    static void readFully(InputStream in, byte[] b, int off, int len) {
    int read = read(in, b, off, len);
      if (read != len) {
         throw EOFException("reached end of stream after reading " + read + " bytes; " + len + " bytes expected");
      }
   }

    static void skipFully(InputStream in, long n) {
    long skipped = skipUpTo(in, n);
      if (skipped < n) {
         throw EOFException("reached end of stream after skipping " + skipped + " bytes; " + n + " bytes expected");
      }
   }

    static long skipUpTo(InputStream in, long n) {
    long totalSkipped = 0L;
      byte[] buf = createBuffer();

      while (totalSkipped < n) {
    long remaining = n - totalSkipped;
    long skipped = skipSafely(in, remaining);
         if (skipped == 0L) {
    int skip = (int)Math.min(remaining, (long)buf.length);
            if ((skipped = in.read(buf, 0, skip)) == -1L) {
               break;
            }
         }

         totalSkipped += skipped;
      }

    return totalSkipped;
   }

    static long skipSafely(InputStream in, long n) {
    int available = in.available();
    return available = = 0 ? 0L : in.skip(Math.min((long)available, n));
   }

   public static <T> T readBytes(InputStream input, ByteProcessor<T> processor) throws IOException {
      Preconditions.checkNotNull(input);
      Preconditions.checkNotNull(processor);
      byte[] buf = createBuffer();

    int read;
      do {
         read = input.read(buf);
      } while (read != -1 && processor.processBytes(buf, 0, read));

      return (T)processor.getResult();
   }

    static int read(InputStream in, byte[] b, int off, int len) {
      Preconditions.checkNotNull(in);
      Preconditions.checkNotNull(b);
      if (len < 0) {
         throw IndexOutOfBoundsException("len is negative");
      } else {
    int total = 0;

         while (total < len) {
    int result = in.read(b, off + total, len - total);
            if (result == -1) {
               break;
            }

            total += result;
         }

    return total;
      }
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
