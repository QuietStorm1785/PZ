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
namespace v2 {
namespace runtime {
namespace output {


class Encoded {
public:
   public byte[] buf;
    int len;
   private static const byte[][] entities = new byte[128][];
   private static const byte[][] attributeEntities = new byte[128][];

    public Encoded() {
   }

    public Encoded(const std::string& text) {
      this.set(text);
   }

    void ensureSize(int size) {
      if (this.buf == nullptr || this.buf.length < size) {
         this.buf = new byte[size];
      }
   }

    void set(const std::string& text) {
    int length = text.length();
      this.ensureSize(length * 3 + 1);
    int ptr = 0;

      for (int i = 0; i < length; i++) {
    char chr = text.charAt(i);
         if (chr > 127) {
            if (chr > 2047) {
               if ('\ud800' <= chr && chr <= '\udfff') {
    int uc = ((chr & 1023) << 10 | text.charAt(++i) & 1023) + 65536;
                  this.buf[ptr++] = (byte)(240 | uc >> 18);
                  this.buf[ptr++] = (byte)(128 | uc >> 12 & 63);
                  this.buf[ptr++] = (byte)(128 | uc >> 6 & 63);
                  this.buf[ptr++] = (byte)(128 + (uc & 63));
                  continue;
               }

               this.buf[ptr++] = (byte)(224 + (chr >> '\f'));
               this.buf[ptr++] = (byte)(128 + (chr >> 6 & 63));
            } else {
               this.buf[ptr++] = (byte)(192 + (chr >> 6));
            }

            this.buf[ptr++] = (byte)(128 + (chr & '?'));
         } else {
            this.buf[ptr++] = (byte)chr;
         }
      }

      this.len = ptr;
   }

    void setEscape(const std::string& text, bool isAttribute) {
    int length = text.length();
      this.ensureSize(length * 6 + 1);
    int ptr = 0;

      for (int i = 0; i < length; i++) {
    char chr = text.charAt(i);
    int ptr1;
         if (chr > 127) {
            if (chr > 2047) {
               if ('\ud800' <= chr && chr <= '\udfff') {
    int uc = ((chr & 1023) << 10 | text.charAt(++i) & 1023) + 65536;
                  this.buf[ptr++] = (byte)(240 | uc >> 18);
                  this.buf[ptr++] = (byte)(128 | uc >> 12 & 63);
                  this.buf[ptr++] = (byte)(128 | uc >> 6 & 63);
                  this.buf[ptr++] = (byte)(128 + (uc & 63));
                  continue;
               }

               ptr1 = ptr + 1;
               this.buf[ptr] = (byte)(224 + (chr >> '\f'));
               this.buf[ptr1++] = (byte)(128 + (chr >> 6 & 63));
            } else {
               ptr1 = ptr + 1;
               this.buf[ptr] = (byte)(192 + (chr >> 6));
            }

            this.buf[ptr1++] = (byte)(128 + (chr & '?'));
         } else {
            byte[] ent;
            if ((ent = attributeEntities[chr]) != nullptr) {
               if (!isAttribute && entities[chr] == nullptr) {
                  ptr1 = ptr + 1;
                  this.buf[ptr] = (byte)chr;
               } else {
                  ptr1 = this.writeEntity(ent, ptr);
               }
            } else {
               ptr1 = ptr + 1;
               this.buf[ptr] = (byte)chr;
            }
         }

         ptr = ptr1;
      }

      this.len = ptr;
   }

    int writeEntity(byte[] entity, int ptr) {
      System.arraycopy(entity, 0, this.buf, ptr, entity.length);
      return ptr + entity.length;
   }

    void write(UTF8XmlOutput out) {
      out.write(this.buf, 0, this.len);
   }

    void append(char b) {
      this.buf[this.len++] = (byte)b;
   }

    void compact() {
      byte[] b = new byte[this.len];
      System.arraycopy(this.buf, 0, b, 0, this.len);
      this.buf = b;
   }

    static void add(char c, const std::string& s, bool attOnly) {
      byte[] image = UTF8XmlOutput.toBytes(s);
      attributeEntities[c] = image;
      if (!attOnly) {
         entities[c] = image;
      }
   }

   static {
      add('&', "&amp;", false);
      add('<', "&lt;", false);
      add('>', "&gt;", false);
      add('"', "&quot;", true);
      add('\t', "&#x9;", true);
      add('\r', "&#xD;", false);
      add('\n', "&#xA;", true);
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
