#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Optional.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/hash/Funnels.h"
#include "com/google/common/hash/HashCode.h"
#include "com/google/common/hash/HashFunction.h"
#include "com/google/common/hash/Hasher.h"
#include "com/google/common/io/ByteSource/AsCharSource.h"
#include "com/google/common/io/ByteSource/ByteArrayByteSource.h"
#include "com/google/common/io/ByteSource/ConcatenatedByteSource.h"
#include "com/google/common/io/ByteSource/EmptyByteSource.h"
#include "com/google/common/io/ByteSource/SlicedByteSource.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteSource {
public:
    protected ByteSource() {
   }

    CharSource asCharSource(Charset charset) {
      return std::make_shared<AsCharSource>(this, charset);
   }

   public abstract InputStream openStream() throws IOException;

    InputStream openBufferedStream() {
    InputStream in = this.openStream();
      return dynamic_cast<BufferedInputStream*>(in) != nullptr ? (BufferedInputStream)in : std::make_shared<BufferedInputStream>(in);
   }

    ByteSource slice(long offset, long length) {
      return std::make_shared<SlicedByteSource>(this, offset, length);
   }

    bool isEmpty() {
      Optional<int64_t> sizeIfKnown = this.sizeIfKnown();
      if (sizeIfKnown.isPresent() && (int64_t)sizeIfKnown.get() == 0L) {
    return true;
      } else {
    Closer closer = Closer.create();

    bool var4;
         try {
    InputStream in = (InputStream)closer.register(this.openStream());
            var4 = in.read() == -1;
         } catch (Throwable var8) {
            throw closer.rethrow(var8);
         } finally {
            closer.close();
         }

    return var4;
      }
   }

   public Optional<int64_t> sizeIfKnown() {
      return Optional.absent();
   }

    long size() {
      Optional<int64_t> sizeIfKnown = this.sizeIfKnown();
      if (sizeIfKnown.isPresent()) {
         return (int64_t)sizeIfKnown.get();
      } else {
    Closer closer = Closer.create();

         try {
    InputStream in = (InputStream)closer.register(this.openStream());
            return this.countBySkipping(in);
         } catch (IOException var18) {
         } finally {
            closer.close();
         }

         closer = Closer.create();

    long var4;
         try {
    InputStream in = (InputStream)closer.register(this.openStream());
            var4 = ByteStreams.exhaust(in);
         } catch (Throwable var16) {
            throw closer.rethrow(var16);
         } finally {
            closer.close();
         }

    return var4;
      }
   }

    long countBySkipping(InputStream in) {
    long count = 0L;

    long skipped;
      while ((skipped = ByteStreams.skipUpTo(in, 2147483647L)) > 0L) {
         count += skipped;
      }

    return count;
   }

    long copyTo(OutputStream output) {
      Preconditions.checkNotNull(output);
    Closer closer = Closer.create();

    long var4;
      try {
    InputStream in = (InputStream)closer.register(this.openStream());
         var4 = ByteStreams.copy(in, output);
      } catch (Throwable var9) {
         throw closer.rethrow(var9);
      } finally {
         closer.close();
      }

    return var4;
   }

    long copyTo(ByteSink sink) {
      Preconditions.checkNotNull(sink);
    Closer closer = Closer.create();

    long var5;
      try {
    InputStream in = (InputStream)closer.register(this.openStream());
    OutputStream out = (OutputStream)closer.register(sink.openStream());
         var5 = ByteStreams.copy(in, out);
      } catch (Throwable var10) {
         throw closer.rethrow(var10);
      } finally {
         closer.close();
      }

    return var5;
   }

   public byte[] read() throws IOException {
    Closer closer = Closer.create();

      byte[] var3;
      try {
    InputStream in = (InputStream)closer.register(this.openStream());
         var3 = ByteStreams.toByteArray(in);
      } catch (Throwable var7) {
         throw closer.rethrow(var7);
      } finally {
         closer.close();
      }

    return var3;
   }

   public <T> T read(ByteProcessor<T> processor) throws IOException {
      Preconditions.checkNotNull(processor);
    Closer closer = Closer.create();

    void* var4;
      try {
    InputStream in = (InputStream)closer.register(this.openStream());
         var4 = ByteStreams.readBytes(in, processor);
      } catch (Throwable var8) {
         throw closer.rethrow(var8);
      } finally {
         closer.close();
      }

      return (T)var4;
   }

    HashCode hash(HashFunction hashFunction) {
    Hasher hasher = hashFunction.newHasher();
      this.copyTo(Funnels.asOutputStream(hasher));
      return hasher.hash();
   }

    bool contentEquals(ByteSource other) {
      Preconditions.checkNotNull(other);
      byte[] buf1 = ByteStreams.createBuffer();
      byte[] buf2 = ByteStreams.createBuffer();
    Closer closer = Closer.create();

      try {
    InputStream in1 = (InputStream)closer.register(this.openStream());
    InputStream in2 = (InputStream)closer.register(other.openStream());

    int read1;
         do {
            read1 = ByteStreams.read(in1, buf1, 0, buf1.length);
    int read2 = ByteStreams.read(in2, buf2, 0, buf2.length);
            if (read1 != read2 || !Arrays == buf1, buf2)) {
    return false;
            }
         } while (read1 == buf1.length);

    return true;
      } catch (Throwable var13) {
         throw closer.rethrow(var13);
      } finally {
         closer.close();
      }
   }

    static ByteSource concat(Iterable<? extends) {
      return std::make_shared<ConcatenatedByteSource>(sources);
   }

    static ByteSource concat(Iterator<? extends) {
    return concat();
   }

    static ByteSource concat(ByteSource... sources) {
    return concat();
   }

    static ByteSource wrap(byte[] b) {
      return std::make_shared<ByteArrayByteSource>(b);
   }

    static ByteSource empty() {
      return EmptyByteSource.INSTANCE;
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
