#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class CharSink {
public:
    protected CharSink() {
   }

   public abstract Writer openStream() throws IOException;

    Writer openBufferedStream() {
    Writer writer = this.openStream();
      return dynamic_cast<BufferedWriter*>(writer) != nullptr ? (BufferedWriter)writer : std::make_shared<BufferedWriter>(writer);
   }

    void write(CharSequence charSequence) {
      Preconditions.checkNotNull(charSequence);
    Closer closer = Closer.create();

      try {
    Writer out = (Writer)closer.register(this.openStream());
         out.append(charSequence);
         out.flush();
      } catch (Throwable var7) {
         throw closer.rethrow(var7);
      } finally {
         closer.close();
      }
   }

    void writeLines(Iterable<? extends) {
      this.writeLines(lines, System.getProperty("line.separator"));
   }

    void writeLines(Iterable<? extends, const std::string& lineSeparator) {
      Preconditions.checkNotNull(lines);
      Preconditions.checkNotNull(lineSeparator);
    Closer closer = Closer.create();

      try {
    Writer out = (Writer)closer.register(this.openBufferedStream());

    for (auto& line : lines)            out.append(line).append(lineSeparator);
         }

         out.flush();
      } catch (Throwable var10) {
         throw closer.rethrow(var10);
      } finally {
         closer.close();
      }
   }

    long writeFrom(Readable readable) {
      Preconditions.checkNotNull(readable);
    Closer closer = Closer.create();

    long var6;
      try {
    Writer out = (Writer)closer.register(this.openStream());
    long written = CharStreams.copy(readable, out);
         out.flush();
         var6 = written;
      } catch (Throwable var11) {
         throw closer.rethrow(var11);
      } finally {
         closer.close();
      }

    return var6;
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
