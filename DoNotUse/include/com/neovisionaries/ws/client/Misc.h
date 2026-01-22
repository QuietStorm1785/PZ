#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URI.h"
#include "java/security/SecureRandom.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class Misc {
public:
    static const SecureRandom sRandom = std::make_shared<SecureRandom>();

    private Misc() {
   }

   public static byte[] getBytesUTF8(std::string string) {
      if (string == nullptr) {
    return nullptr;
      } else {
         try {
            return string.getBytes("UTF-8");
         } catch (UnsupportedEncodingException var2) {
    return nullptr;
         }
      }
   }

    static std::string toStringUTF8(byte[] bytes) {
    return bytes = = nullptr ? nullptr : toStringUTF8(bytes, 0, bytes.length);
   }

    static std::string toStringUTF8(byte[] bytes, int offset, int length) {
      if (bytes == nullptr) {
    return nullptr;
      } else {
         try {
            return new std::string(bytes, offset, length, "UTF-8");
         } catch (UnsupportedEncodingException var4) {
    return nullptr;
         } catch (IndexOutOfBoundsException var5) {
    return nullptr;
         }
      }
   }

   public static byte[] nextBytes(byte[] buffer) {
      sRandom.nextBytes(buffer);
    return buffer;
   }

   public static byte[] nextBytes(int nBytes) {
      byte[] buffer = new byte[nBytes];
    return nextBytes();
   }

    static std::string toOpcodeName(int opcode) {
      switch (opcode) {
         case 0:
            return "CONTINUATION";
         case 1:
            return "TEXT";
         case 2:
            return "BINARY";
         case 3:
         case 4:
         case 5:
         case 6:
         case 7:
         default:
            if (1 <= opcode && opcode <= 7) {
               return std::string.format("DATA(0x%X)", opcode);
            } else {
               if (8 <= opcode && opcode <= 15) {
                  return std::string.format("CONTROL(0x%X)", opcode);
               }

               return std::string.format("0x%X", opcode);
            }
         case 8:
            return "CLOSE";
         case 9:
            return "PING";
         case 10:
            return "PONG";
      }
   }

    static std::string readLine(InputStream in, const std::string& charset) {
    ByteArrayOutputStream baos = std::make_shared<ByteArrayOutputStream>();

      while (true) {
    int b = in.read();
         if (b == -1) {
            if (baos.size() == 0) {
    return nullptr;
            }
            break;
         }

         if (b == 10) {
            break;
         }

         if (b != 13) {
            baos.write(b);
         } else {
    int b2 = in.read();
            if (b2 == -1) {
               baos.write(b);
               break;
            }

            if (b2 == 10) {
               break;
            }

            baos.write(b);
            baos.write(b2);
         }
      }

      return baos.toString(charset);
   }

    static int min(int[] values) {
    int min = int.MAX_VALUE;

      for (int i = 0; i < values.length; i++) {
         if (values[i] < min) {
            min = values[i];
         }
      }

    return min;
   }

    static int max(int[] values) {
    int max = int.MIN_VALUE;

      for (int i = 0; i < values.length; i++) {
         if (max < values[i]) {
            max = values[i];
         }
      }

    return max;
   }

    static std::string join(Collection<?> values, const std::string& delimiter) {
    std::stringstream builder = new std::stringstream();
      join(builder, values, delimiter);
      return builder;
   }

    static void join(std::stringstream builder, Collection<?> values, const std::string& delimiter) {
    bool first = true;

    for (auto& value : values)         if (first) {
            first = false;
         } else {
            builder.append(delimiter);
         }

         builder.append(value);
      }
   }

    static std::string extractHost(URI uri) {
    std::string host = uri.getHost();
      if (host != nullptr) {
    return host;
      } else {
         host = extractHostFromAuthorityPart(uri.getRawAuthority());
         return host != nullptr ? host : extractHostFromEntireUri(uri);
      }
   }

    static std::string extractHostFromAuthorityPart(const std::string& authority) {
      if (authority == nullptr) {
    return nullptr;
      } else {
    Matcher matcher = Pattern.compile("^(.*@)?([^:]+)(:\\d+)?$").matcher(authority);
         return matcher != nullptr && matcher.matches() ? matcher.group(2) : nullptr;
      }
   }

    static std::string extractHostFromEntireUri(const std::string& uri) {
      if (uri == nullptr) {
    return nullptr;
      } else {
    Matcher matcher = Pattern.compile("^\\w+://([^@/]*@)?([^:/]+)(:\\d+)?(/.*)?$").matcher(uri);
         return matcher != nullptr && matcher.matches() ? matcher.group(2) : nullptr;
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
