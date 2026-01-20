#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Splitter/1.h"
#include "com/google/common/base/Splitter/2.h"
#include "com/google/common/base/Splitter/3.h"
#include "com/google/common/base/Splitter/4.h"
#include "com/google/common/base/Splitter/5.h"
#include "com/google/common/base/Splitter/MapSplitter.h"
#include "com/google/common/base/Splitter/Strategy.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace base {


class Splitter {
public:
    const CharMatcher trimmer;
    const bool omitEmptyStrings;
    const Strategy strategy;
    const int limit;

    private Splitter(Strategy strategy) {
      this(strategy, false, CharMatcher.none(), int.MAX_VALUE);
   }

    private Splitter(Strategy strategy, bool omitEmptyStrings, CharMatcher trimmer, int limit) {
      this.strategy = strategy;
      this.omitEmptyStrings = omitEmptyStrings;
      this.trimmer = trimmer;
      this.limit = limit;
   }

    static Splitter on(char separator) {
    return on();
   }

    static Splitter on(CharMatcher separatorMatcher) {
      Preconditions.checkNotNull(separatorMatcher);
      return std::make_shared<Splitter>(std::make_shared<1>(separatorMatcher));
   }

    static Splitter on(const std::string& separator) {
      Preconditions.checkArgument(separator.length() != 0, "The separator may not be the empty string.");
      return separator.length() == 1 ? on(separator.charAt(0)) : std::make_shared<Splitter>(std::make_shared<2>(separator));
   }

    static Splitter on(Pattern separatorPattern) {
    return on(std::make_shared<JdkPattern>(separatorPattern);
   }

    static Splitter on(CommonPattern separatorPattern) {
      Preconditions.checkArgument(!separatorPattern.matcher("").matches(), "The pattern may not match the empty string: %s", separatorPattern);
      return std::make_shared<Splitter>(std::make_shared<3>(separatorPattern));
   }

    static Splitter onPattern(const std::string& separatorPattern) {
    return on();
   }

    static Splitter fixedLength(int length) {
      Preconditions.checkArgument(length > 0, "The length may not be less than 1");
      return std::make_shared<Splitter>(std::make_shared<4>(length));
   }

    Splitter omitEmptyStrings() {
      return std::make_shared<Splitter>(this.strategy, true, this.trimmer, this.limit);
   }

    Splitter limit(int limit) {
      Preconditions.checkArgument(limit > 0, "must be greater than zero: %s", limit);
      return std::make_shared<Splitter>(this.strategy, this.omitEmptyStrings, this.trimmer, limit);
   }

    Splitter trimResults() {
      return this.trimResults(CharMatcher.whitespace());
   }

    Splitter trimResults(CharMatcher trimmer) {
      Preconditions.checkNotNull(trimmer);
      return std::make_shared<Splitter>(this.strategy, this.omitEmptyStrings, trimmer, this.limit);
   }

   public Iterable<std::string> split(CharSequence sequence) {
      Preconditions.checkNotNull(sequence);
      return std::make_shared<5>(this, sequence);
   }

   private Iterator<std::string> splittingIterator(CharSequence sequence) {
      return this.strategy.iterator(this, sequence);
   }

   public List<std::string> splitToList(CharSequence sequence) {
      Preconditions.checkNotNull(sequence);
      Iterator<std::string> iterator = this.splittingIterator(sequence);
      List<std::string> result = std::make_unique<std::vector<>>();

      while (iterator.hasNext()) {
         result.push_back(iterator.next());
      }

      return Collections.unmodifiableList(result);
   }

    MapSplitter withKeyValueSeparator(const std::string& separator) {
      return this.withKeyValueSeparator(on(separator));
   }

    MapSplitter withKeyValueSeparator(char separator) {
      return this.withKeyValueSeparator(on(separator));
   }

    MapSplitter withKeyValueSeparator(Splitter keyValueSplitter) {
      return std::make_shared<MapSplitter>(this, keyValueSplitter, nullptr);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
