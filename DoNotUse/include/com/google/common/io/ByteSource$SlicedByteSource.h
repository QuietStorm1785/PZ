#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Optional.h"
#include "com/google/common/base/Preconditions.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteSource {
public:
    const long offset;
    const long length;

   ByteSource$SlicedByteSource(ByteSource var1, long offset, long length) {
      this.this$0 = var1;
      Preconditions.checkArgument(offset >= 0L, "offset (%s) may not be negative", offset);
      Preconditions.checkArgument(length >= 0L, "length (%s) may not be negative", length);
      this.offset = offset;
      this.length = length;
   }

    InputStream openStream() {
      return this.sliceStream(this.this$0.openStream());
   }

    InputStream openBufferedStream() {
      return this.sliceStream(this.this$0.openBufferedStream());
   }

    InputStream sliceStream(InputStream in) {
      if (this.offset > 0L) {
    long skipped;
         try {
            skipped = ByteStreams.skipUpTo(in, this.offset);
         } catch (Throwable var10) {
    std::exception e = var10;
    Closer closer = Closer.create();
            closer.register(in);

            try {
               throw closer.rethrow(e);
            } finally {
               closer.close();
            }
         }

         if (skipped < this.offset) {
            in.close();
            return std::make_shared<ByteArrayInputStream>(new byte[0]);
         }
      }

      return ByteStreams.limit(in, this.length);
   }

    ByteSource slice(long offset, long length) {
      Preconditions.checkArgument(offset >= 0L, "offset (%s) may not be negative", offset);
      Preconditions.checkArgument(length >= 0L, "length (%s) may not be negative", length);
    long maxLength = this.length - offset;
      return this.this$0.slice(this.offset + offset, Math.min(length, maxLength));
   }

    bool isEmpty() {
      return this.length == 0L || super.empty();
   }

   public Optional<int64_t> sizeIfKnown() {
      Optional<int64_t> optionalUnslicedSize = this.this$0.sizeIfKnown();
      if (optionalUnslicedSize.isPresent()) {
    long unslicedSize = (int64_t)optionalUnslicedSize.get();
    long off = Math.min(this.offset, unslicedSize);
         return Optional.of(Math.min(this.length, unslicedSize - off));
      } else {
         return Optional.absent();
      }
   }

    std::string toString() {
      return this.this$0 + ".slice(" + this.offset + ", " + this.length + ")";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
