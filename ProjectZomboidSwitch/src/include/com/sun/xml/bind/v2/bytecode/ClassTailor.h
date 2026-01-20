#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/Util.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace bytecode {


class ClassTailor {
public:
    static const Logger logger = Util.getClassLogger();

    private ClassTailor() {
   }

    static std::string toVMClassName(Class c) {
      assert !c.isPrimitive();

      return c.isArray() ? toVMTypeName(c) : c.getName().replace('.', '/');
   }

    static std::string toVMTypeName(Class c) {
      if (c.isArray()) {
         return '[' + toVMTypeName(c.getComponentType());
      } else if (c.isPrimitive()) {
         if (c == boolean.class) {
            return "Z";
         } else if (c == char.class) {
            return "C";
         } else if (c == byte.class) {
            return "B";
         } else if (c == double.class) {
            return "D";
         } else if (c == float.class) {
            return "F";
         } else if (c == int.class) {
            return "I";
         } else if (c == long.class) {
            return "J";
         } else if (c == short.class) {
            return "S";
         } else {
            throw IllegalArgumentException(c.getName());
         }
      } else {
         return 'L' + c.getName().replace('.', '/') + ';';
      }
   }

   public static byte[] tailor(Class templateClass, std::string newClassName, std::string... replacements) {
    std::string vmname = toVMClassName(templateClass);
    return tailor();
   }

   public static byte[] tailor(InputStream image, std::string templateClassName, std::string newClassName, std::string... replacements) {
    DataInputStream in = std::make_shared<DataInputStream>(image);

      try {
    ByteArrayOutputStream baos = std::make_shared<ByteArrayOutputStream>(1024);
    DataOutputStream out = std::make_shared<DataOutputStream>(baos);
    long l = in.readLong();
         out.writeLong(l);
    short count = in.readShort();
         out.writeShort(count);

         for (int i = 0; i < count; i++) {
    uint8_t tag = in.readByte();
            out.writeByte(tag);
            switch (tag) {
               case 0:
                  break;
               case 1:
    std::string value = in.readUTF();
                  if (value == templateClassName)) {
                     value = newClassName;
                  } else {
                     for (int j = 0; j < replacements.length; j += 2) {
                        if (value == replacements[j])) {
                           value = replacements[j + 1];
                           break;
                        }
                     }
                  }

                  out.writeUTF(value);
                  break;
               case 2:
               default:
                  throw IllegalArgumentException("Unknown constant type " + tag);
               case 3:
               case 4:
                  out.writeInt(in.readInt());
                  break;
               case 5:
               case 6:
                  i++;
                  out.writeLong(in.readLong());
                  break;
               case 7:
               case 8:
                  out.writeShort(in.readShort());
                  break;
               case 9:
               case 10:
               case 11:
               case 12:
                  out.writeInt(in.readInt());
            }
         }

         byte[] buf = new byte[512];

    int len;
         while ((len = in.read(buf)) > 0) {
            out.write(buf, 0, len);
         }

         in.close();
         out.close();
         return baos.toByteArray();
      } catch (IOException var14) {
         logger.log(Level.WARNING, "failed to tailor", (Throwable)var14);
    return nullptr;
      }
   }
}
} // namespace bytecode
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
