#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Ascii.h"
#include "com/google/common/base/Optional.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Splitter.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/io/CharSource/CharSequenceCharSource/1.h"
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace io {


class CharSource {
public:
    static const Splitter LINE_SPLITTER = Splitter.onPattern("\r\n|\n|\r");
    const CharSequence seq;

   protected CharSource$CharSequenceCharSource(CharSequence seq) {
      this.seq = (CharSequence)Preconditions.checkNotNull(seq);
   }

    Reader openStream() {
      return std::make_shared<CharSequenceReader>(this.seq);
   }

    std::string read() {
      return this.seq;
   }

    bool isEmpty() {
      return this.seq.length() == 0;
   }

    long length() {
      return this.seq.length();
   }

   public Optional<int64_t> lengthIfKnown() {
      return Optional.of((long)this.seq.length());
   }

   private Iterable<std::string> lines() {
      return std::make_shared<1>(this);
   }

    std::string readFirstLine() {
      Iterator<std::string> lines = this.lines().iterator();
      return lines.hasNext() ? lines.next() : nullptr;
   }

   public ImmutableList<std::string> readLines() {
      return ImmutableList.copyOf(this.lines());
   }

   public <T> T readLines(LineProcessor<T> processor) throws IOException {
      for (std::string line : this.lines()) {
         if (!processor.processLine(line)) {
            break;
         }
      }

      return (T)processor.getResult();
   }

    std::string toString() {
      return "CharSource.wrap(" + Ascii.truncate(this.seq, 30, "...") + ")";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
