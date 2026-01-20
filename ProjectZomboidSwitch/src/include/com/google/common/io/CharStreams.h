#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/io/CharStreams/NullWriter.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class CharStreams {
public:
    static CharBuffer createBuffer() {
      return CharBuffer.allocate(2048);
   }

    private CharStreams() {
   }

    static long copy(Readable from, Appendable to) {
      Preconditions.checkNotNull(from);
      Preconditions.checkNotNull(to);
    CharBuffer buf = createBuffer();
    long total = 0L;

      while (from.read(buf) != -1) {
         ((Buffer)buf).flip();
         to.append(buf);
         total += buf.remaining();
         ((Buffer)buf).clear();
      }

    return total;
   }

    static std::string toString(Readable r) {
    return toStringBuilder();
   }

    static std::stringstream toStringBuilder(Readable r) {
    std::stringstream sb = new std::stringstream();
      copy(r, sb);
    return sb;
   }

   public static List<std::string> readLines(Readable r) throws IOException {
      List<std::string> result = std::make_unique<std::vector<>>();
    LineReader lineReader = std::make_shared<LineReader>(r);

    std::string line;
      while ((line = lineReader.readLine()) != nullptr) {
         result.push_back(line);
      }

    return result;
   }

   public static <T> T readLines(Readable readable, LineProcessor<T> processor) throws IOException {
      Preconditions.checkNotNull(readable);
      Preconditions.checkNotNull(processor);
    LineReader lineReader = std::make_shared<LineReader>(readable);

    std::string line;
      while ((line = lineReader.readLine()) != nullptr && processor.processLine(line)) {
      }

      return (T)processor.getResult();
   }

    static long exhaust(Readable readable) {
    long total = 0L;
    CharBuffer buf = createBuffer();

    long read;
      while ((read = readable.read(buf)) != -1L) {
         total += read;
         ((Buffer)buf).clear();
      }

    return total;
   }

    static void skipFully(Reader reader, long n) {
      Preconditions.checkNotNull(reader);

      while (n > 0L) {
    long amt = reader.skip(n);
         if (amt == 0L) {
            throw std::make_unique<EOFException>();
         }

         n -= amt;
      }
   }

    static Writer nullWriter() {
      return NullWriter.access$000();
   }

    static Writer asWriter(Appendable target) {
      return (Writer)(dynamic_cast<Writer*>(target) != nullptr ? (Writer)target : std::make_shared<AppendableWriter>(target));
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
