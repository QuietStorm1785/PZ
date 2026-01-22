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
#include "com/google/common/collect/Lists.h"
#include "com/google/common/io/CharSource/AsByteSource.h"
#include "com/google/common/io/CharSource/CharSequenceCharSource.h"
#include "com/google/common/io/CharSource/ConcatenatedCharSource.h"
#include "com/google/common/io/CharSource/EmptyCharSource.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace io {


class CharSource {
public:
    protected CharSource() {
   }

    ByteSource asByteSource(Charset charset) {
      return std::make_shared<AsByteSource>(this, charset);
   }

   public abstract Reader openStream() throws IOException;

    BufferedReader openBufferedStream() {
    Reader reader = this.openStream();
      return dynamic_cast<BufferedReader*>(reader) != nullptr ? (BufferedReader)reader : std::make_shared<BufferedReader>(reader);
   }

   public Optional<int64_t> lengthIfKnown() {
      return Optional.absent();
   }

    long length() {
      Optional<int64_t> lengthIfKnown = this.lengthIfKnown();
      if (lengthIfKnown.isPresent()) {
         return (int64_t)lengthIfKnown.get();
      } else {
    Closer closer = Closer.create();

    long var4;
         try {
    Reader reader = (Reader)closer.register(this.openStream());
            var4 = this.countBySkipping(reader);
         } catch (Throwable var9) {
            throw closer.rethrow(var9);
         } finally {
            closer.close();
         }

    return var4;
      }
   }

    long countBySkipping(Reader reader) {
    long count = 0L;

    long read;
      while ((read = reader.skip(int64_t.MAX_VALUE)) != 0L) {
         count += read;
      }

    return count;
   }

    long copyTo(Appendable appendable) {
      Preconditions.checkNotNull(appendable);
    Closer closer = Closer.create();

    long var4;
      try {
    Reader reader = (Reader)closer.register(this.openStream());
         var4 = CharStreams.copy(reader, appendable);
      } catch (Throwable var9) {
         throw closer.rethrow(var9);
      } finally {
         closer.close();
      }

    return var4;
   }

    long copyTo(CharSink sink) {
      Preconditions.checkNotNull(sink);
    Closer closer = Closer.create();

    long var5;
      try {
    Reader reader = (Reader)closer.register(this.openStream());
    Writer writer = (Writer)closer.register(sink.openStream());
         var5 = CharStreams.copy(reader, writer);
      } catch (Throwable var10) {
         throw closer.rethrow(var10);
      } finally {
         closer.close();
      }

    return var5;
   }

    std::string read() {
    Closer closer = Closer.create();

    std::string var3;
      try {
    Reader reader = (Reader)closer.register(this.openStream());
         var3 = CharStreams.toString(reader);
      } catch (Throwable var7) {
         throw closer.rethrow(var7);
      } finally {
         closer.close();
      }

    return var3;
   }

    std::string readFirstLine() {
    Closer closer = Closer.create();

    std::string var3;
      try {
    BufferedReader reader = (BufferedReader)closer.register(this.openBufferedStream());
         var3 = reader.readLine();
      } catch (Throwable var7) {
         throw closer.rethrow(var7);
      } finally {
         closer.close();
      }

    return var3;
   }

   public ImmutableList<std::string> readLines() throws IOException {
    Closer closer = Closer.create();

    ImmutableList var5;
      try {
    BufferedReader reader = (BufferedReader)closer.register(this.openBufferedStream());
         List<std::string> result = Lists.newArrayList();

    std::string line;
         while ((line = reader.readLine()) != nullptr) {
            result.push_back(line);
         }

         var5 = ImmutableList.copyOf(result);
      } catch (Throwable var9) {
         throw closer.rethrow(var9);
      } finally {
         closer.close();
      }

    return var5;
   }

   public <T> T readLines(LineProcessor<T> processor) throws IOException {
      Preconditions.checkNotNull(processor);
    Closer closer = Closer.create();

    void* var4;
      try {
    Reader reader = (Reader)closer.register(this.openStream());
         var4 = CharStreams.readLines(reader, processor);
      } catch (Throwable var8) {
         throw closer.rethrow(var8);
      } finally {
         closer.close();
      }

      return (T)var4;
   }

    bool isEmpty() {
      Optional<int64_t> lengthIfKnown = this.lengthIfKnown();
      if (lengthIfKnown.isPresent() && (int64_t)lengthIfKnown.get() == 0L) {
    return true;
      } else {
    Closer closer = Closer.create();

    bool var4;
         try {
    Reader reader = (Reader)closer.register(this.openStream());
            var4 = reader.read() == -1;
         } catch (Throwable var8) {
            throw closer.rethrow(var8);
         } finally {
            closer.close();
         }

    return var4;
      }
   }

    static CharSource concat(Iterable<? extends) {
      return std::make_shared<ConcatenatedCharSource>(sources);
   }

    static CharSource concat(Iterator<? extends) {
    return concat();
   }

    static CharSource concat(CharSource... sources) {
    return concat();
   }

    static CharSource wrap(CharSequence charSequence) {
      return std::make_shared<CharSequenceCharSource>(charSequence);
   }

    static CharSource empty() {
      return EmptyCharSource.access$000();
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
