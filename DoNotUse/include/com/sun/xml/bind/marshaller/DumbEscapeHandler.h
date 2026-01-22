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


class DumbEscapeHandler {
public:
    static const CharacterEscapeHandler theInstance = std::make_shared<DumbEscapeHandler>();

    private DumbEscapeHandler() {
   }

    void escape(char[] ch, int start, int length, bool isAttVal, Writer out) {
    int limit = start + length;

      for (int i = start; i < limit; i++) {
         switch (ch[i]) {
            case '"':
               if (isAttVal) {
                  out.write("&quot;");
               } else {
                  out.write(34);
               }
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
               if (ch[i] > 127) {
                  out.write("&#");
                  out.write(int.toString(ch[i]));
                  out.write(59);
               } else {
                  out.write(ch[i]);
               }
         }
      }
   }
}
} // namespace marshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
