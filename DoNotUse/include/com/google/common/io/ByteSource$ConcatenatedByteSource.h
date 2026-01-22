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
   const Iterable<? : public ByteSource> sources;

   ByteSource$ConcatenatedByteSource(Iterable<? : public ByteSource> sources) {
      this.sources = (Iterable<? : public ByteSource>)Preconditions.checkNotNull(sources);
   }

    InputStream openStream() {
      return std::make_shared<MultiInputStream>(this.sources.iterator());
   }

    bool isEmpty() {
      for (ByteSource source : this.sources) {
         if (!source.empty()) {
    return false;
         }
      }

    return true;
   }

   public Optional<int64_t> sizeIfKnown() {
    long result = 0L;

      for (ByteSource source : this.sources) {
         Optional<int64_t> sizeIfKnown = source.sizeIfKnown();
         if (!sizeIfKnown.isPresent()) {
            return Optional.absent();
         }

         result += sizeIfKnown.get();
      }

      return Optional.of(result);
   }

    long size() {
    long result = 0L;

      for (ByteSource source : this.sources) {
         result += source.size();
      }

    return result;
   }

    std::string toString() {
      return "ByteSource.concat(" + this.sources + ")";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
