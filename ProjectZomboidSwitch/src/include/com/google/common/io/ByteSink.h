#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/io/ByteSink/AsCharSink.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteSink {
public:
    protected ByteSink() {
   }

    CharSink asCharSink(Charset charset) {
      return std::make_shared<AsCharSink>(this, charset, nullptr);
   }

   public abstract OutputStream openStream() throws IOException;

    OutputStream openBufferedStream() {
    OutputStream out = this.openStream();
      return dynamic_cast<BufferedOutputStream*>(out) != nullptr ? (BufferedOutputStream)out : std::make_shared<BufferedOutputStream>(out);
   }

    void write(byte[] bytes) {
      Preconditions.checkNotNull(bytes);
    Closer closer = Closer.create();

      try {
    OutputStream out = (OutputStream)closer.register(this.openStream());
         out.write(bytes);
         out.flush();
      } catch (Throwable var7) {
         throw closer.rethrow(var7);
      } finally {
         closer.close();
      }
   }

    long writeFrom(InputStream input) {
      Preconditions.checkNotNull(input);
    Closer closer = Closer.create();

    long var6;
      try {
    OutputStream out = (OutputStream)closer.register(this.openStream());
    long written = ByteStreams.copy(input, out);
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
