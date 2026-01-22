#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {

class FastInfosetConnector {
public:
   char[] ch;
    int start;
    int length;

   FastInfosetConnector$CharSequenceImpl(FastInfosetConnector var1) {
      this.this$0 = var1;
   }

   FastInfosetConnector$CharSequenceImpl(FastInfosetConnector var1, char[] ch, int start, int length) {
      this.this$0 = var1;
      this.ch = ch;
      this.start = start;
      this.length = length;
   }

    void set() {
      this.ch = FastInfosetConnector.access$000(this.this$0).getTextCharacters();
      this.start = FastInfosetConnector.access$000(this.this$0).getTextStart();
      this.length = FastInfosetConnector.access$000(this.this$0).getTextLength();
   }

    int length() {
      return this.length;
   }

    char charAt(int index) {
      return this.ch[this.start + index];
   }

    CharSequence subSequence(int start, int end) {
      return new FastInfosetConnector$CharSequenceImpl(this.this$0, this.ch, this.start + start, end - start);
   }

    std::string toString() {
      return new std::string(this.ch, this.start, this.length);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
