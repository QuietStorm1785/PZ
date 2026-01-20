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


class CharSource {
public:
   private const Iterable<? : public CharSource> sources;

   CharSource$ConcatenatedCharSource(Iterable<? : public CharSource> sources) {
      this.sources = (Iterable<? : public CharSource>)Preconditions.checkNotNull(sources);
   }

    Reader openStream() {
      return std::make_shared<MultiReader>(this.sources.iterator());
   }

    bool isEmpty() {
      for (CharSource source : this.sources) {
         if (!source.empty()) {
    return false;
         }
      }

    return true;
   }

   public Optional<int64_t> lengthIfKnown() {
    long result = 0L;

      for (CharSource source : this.sources) {
         Optional<int64_t> lengthIfKnown = source.lengthIfKnown();
         if (!lengthIfKnown.isPresent()) {
            return Optional.absent();
         }

         result += lengthIfKnown.get();
      }

      return Optional.of(result);
   }

    long length() {
    long result = 0L;

      for (CharSource source : this.sources) {
         result += source.length();
      }

    return result;
   }

    std::string toString() {
      return "CharSource.concat(" + this.sources + ")";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
