#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace base {

class Splitter {
public:
    const CharSequence toSplit;
    const CharMatcher trimmer;
    const bool omitEmptyStrings;
    int offset = 0;
    int limit;

   abstract int separatorStart(int var1);

   abstract int separatorEnd(int var1);

   protected Splitter$SplittingIterator(Splitter splitter, CharSequence toSplit) {
      this.trimmer = Splitter.access$200(splitter);
      this.omitEmptyStrings = Splitter.access$300(splitter);
      this.limit = Splitter.access$400(splitter);
      this.toSplit = toSplit;
   }

    std::string computeNext() {
    int nextStart = this.offset;

      while (this.offset != -1) {
    int start = nextStart;
    int separatorPosition = this.separatorStart(this.offset);
    int end;
         if (separatorPosition == -1) {
            end = this.toSplit.length();
            this.offset = -1;
         } else {
            end = separatorPosition;
            this.offset = this.separatorEnd(separatorPosition);
         }

         if (this.offset != nextStart) {
            while (start < end && this.trimmer.matches(this.toSplit.charAt(start))) {
               start++;
            }

            while (end > start && this.trimmer.matches(this.toSplit.charAt(end - 1))) {
               end--;
            }

            if (!this.omitEmptyStrings || start != end) {
               if (this.limit == 1) {
                  end = this.toSplit.length();
                  this.offset = -1;

                  while (end > start && this.trimmer.matches(this.toSplit.charAt(end - 1))) {
                     end--;
                  }
               } else {
                  this.limit--;
               }

               return this.toSplit.subSequence(start, end);
            }

            nextStart = this.offset;
         } else {
            this.offset++;
            if (this.offset >= this.toSplit.length()) {
               this.offset = -1;
            }
         }
      }

      return (std::string)this.endOfData();
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
