#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace marshaller {


class MinimumEscapeHandler {
public:
    static const CharacterEscapeHandler theInstance = std::make_shared<MinimumEscapeHandler>();

    private MinimumEscapeHandler() {
   }

    void escape(char[] ch, int start, int length, bool isAttVal, Writer out) {
    int limit = start + length;

      for (int i = start; i < limit; i++) {
    char c = ch[i];
         if (c == '&' || c == '<' || c == '>' || c == '\r' || c == '\n' && isAttVal || c == '"' && isAttVal) {
            if (i != start) {
               out.write(ch, start, i - start);
            }

            start = i + 1;
            switch (ch[i]) {
               case '\n':
               case '\r':
                  out.write("&#");
                  out.write(int.toString(c));
                  out.write(59);
                  break;
               case '"':
                  out.write("&quot;");
                  break;
               case '&':
                  out.write("&amp;");
                  break;
               case '<':
                  out.write("&lt;");
                  break;
               case '>':
                  out.write("&gt;");
                  break;
               default:
                  throw IllegalArgumentException("Cannot escape: '" + c + "'");
            }
         }
      }

      if (start != limit) {
         out.write(ch, start, limit - start);
      }
   }
}
} // namespace marshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
