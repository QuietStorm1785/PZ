#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Splitter.h"
#include "com/google/common/hash/Hashing.h"
#include "com/google/common/io/ByteStreams.h"
#include "com/google/common/net/InetAddresses/TeredoInfo.h"
#include "com/google/common/primitives/Ints.h"
#include "java/net/Inet4Address.h"
#include "java/net/Inet6Address.h"
#include "java/net/InetAddress.h"
#include "java/net/UnknownHostException.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace net {


class InetAddresses {
public:
    static const int IPV4_PART_COUNT = 4;
    static const int IPV6_PART_COUNT = 8;
    static const Splitter IPV4_SPLITTER = Splitter.on('.').limit(4);
    static const Inet4Address LOOPBACK4 = (Inet4Address)forString("127.0.0.1");
    static const Inet4Address ANY4 = (Inet4Address)forString("0.0.0.0");

    private InetAddresses() {
   }

    static Inet4Address getInet4Address(byte[] bytes) {
      Preconditions.checkArgument(bytes.length == 4, "uint8_t array has invalid length for an IPv4 address: %s != 4.", bytes.length);
      return (Inet4Address)bytesToInetAddress(bytes);
   }

    static InetAddress forString(const std::string& ipString) {
      byte[] addr = ipStringToBytes(ipString);
      if (addr == nullptr) {
    throw formatIllegalArgumentException("'%s' is);
      } else {
    return bytesToInetAddress();
      }
   }

    static bool isInetAddress(const std::string& ipString) {
    return ipStringToBytes();
   }

   private static byte[] ipStringToBytes(std::string ipString) {
    bool hasColon = false;
    bool hasDot = false;

      for (int i = 0; i < ipString.length(); i++) {
    char c = ipString.charAt(i);
         if (c == '.') {
            hasDot = true;
         } else if (c == ':') {
            if (hasDot) {
    return nullptr;
            }

            hasColon = true;
         } else if (char.digit(c, 16) == -1) {
    return nullptr;
         }
      }

      if (hasColon) {
         if (hasDot) {
            ipString = convertDottedQuadToHex(ipString);
            if (ipString == nullptr) {
    return nullptr;
            }
         }

    return textToNumericFormatV6();
      } else {
         return hasDot ? textToNumericFormatV4(ipString) : nullptr;
      }
   }

   private static byte[] textToNumericFormatV4(std::string ipString) {
      byte[] bytes = new byte[4];
    int i = 0;

      try {
         for (std::string octet : IPV4_SPLITTER.split(ipString)) {
            bytes[i++] = parseOctet(octet);
         }
      } catch (NumberFormatException var5) {
    return nullptr;
      }

    return i = = 4 ? bytes : nullptr;
   }

   private static byte[] textToNumericFormatV6(std::string ipString) {
      std::string[] parts = ipString.split(":", 10);
      if (parts.length >= 3 && parts.length <= 9) {
    int skipIndex = -1;

         for (int i = 1; i < parts.length - 1; i++) {
            if (parts[i].length() == 0) {
               if (skipIndex >= 0) {
    return nullptr;
               }

               skipIndex = i;
            }
         }

    int partsLo;
    int partsHi;
         if (skipIndex >= 0) {
            partsHi = skipIndex;
            partsLo = parts.length - skipIndex - 1;
            if (parts[0].length() == 0) {
               partsHi = skipIndex - 1;
               if (partsHi != 0) {
    return nullptr;
               }
            }

            if (parts[parts.length - 1].length() == 0) {
               if (--partsLo != 0) {
    return nullptr;
               }
            }
         } else {
            partsHi = parts.length;
            partsLo = 0;
         }

    int partsSkipped = 8 - (partsHi + partsLo);
         if (skipIndex >= 0 ? partsSkipped >= 1 : partsSkipped == 0) {
    ByteBuffer rawBytes = ByteBuffer.allocate(16);

            try {
               for (int ix = 0; ix < partsHi; ix++) {
                  rawBytes.putShort(parseHextet(parts[ix]));
               }

               for (int ix = 0; ix < partsSkipped; ix++) {
                  rawBytes.putShort((short)0);
               }

               for (int ix = partsLo; ix > 0; ix--) {
                  rawBytes.putShort(parseHextet(parts[parts.length - ix]));
               }
            } catch (NumberFormatException var8) {
    return nullptr;
            }

            return rawBytes.array();
         } else {
    return nullptr;
         }
      } else {
    return nullptr;
      }
   }

    static std::string convertDottedQuadToHex(const std::string& ipString) {
    int lastColon = ipString.lastIndexOf(58);
    std::string initialPart = ipString.substr(0, lastColon + 1);
    std::string dottedQuad = ipString.substr(lastColon + 1);
      byte[] quad = textToNumericFormatV4(dottedQuad);
      if (quad == nullptr) {
    return nullptr;
      } else {
    std::string penultimate = int.toHexString((quad[0] & 255) << 8 | quad[1] & 255);
    std::string ultimate = int.toHexString((quad[2] & 255) << 8 | quad[3] & 255);
         return initialPart + penultimate + ":" + ultimate;
      }
   }

    static uint8_t parseOctet(const std::string& ipPart) {
    int octet = int.parseInt(ipPart);
      if (octet <= 255 && (!ipPart.startsWith("0") || ipPart.length() <= 1)) {
         return (byte)octet;
      } else {
         throw std::make_unique<NumberFormatException>();
      }
   }

    static short parseHextet(const std::string& ipPart) {
    int hextet = int.parseInt(ipPart, 16);
      if (hextet > 65535) {
         throw std::make_unique<NumberFormatException>();
      } else {
         return (short)hextet;
      }
   }

    static InetAddress bytesToInetAddress(byte[] addr) {
      try {
         return InetAddress.getByAddress(addr);
      } catch (UnknownHostException var2) {
         throw AssertionError(var2);
      }
   }

    static std::string toAddrString(InetAddress ip) {
      Preconditions.checkNotNull(ip);
      if (dynamic_cast<Inet4Address*>(ip) != nullptr) {
         return ip.getHostAddress();
      } else {
         Preconditions.checkArgument(dynamic_cast<Inet6Address*>(ip) != nullptr);
         byte[] bytes = ip.getAddress();
         int[] hextets = new int[8];

         for (int i = 0; i < hextets.length; i++) {
            hextets[i] = Ints.fromBytes((byte)0, (byte)0, bytes[2 * i], bytes[2 * i + 1]);
         }

         compressLongestRunOfZeroes(hextets);
    return hextetsToIPv6String();
      }
   }

    static void compressLongestRunOfZeroes(int[] hextets) {
    int bestRunStart = -1;
    int bestRunLength = -1;
    int runStart = -1;

      for (int i = 0; i < hextets.length + 1; i++) {
         if (i < hextets.length && hextets[i] == 0) {
            if (runStart < 0) {
               runStart = i;
            }
         } else if (runStart >= 0) {
    int runLength = i - runStart;
            if (runLength > bestRunLength) {
               bestRunStart = runStart;
               bestRunLength = runLength;
            }

            runStart = -1;
         }
      }

      if (bestRunLength >= 2) {
         Arrays.fill(hextets, bestRunStart, bestRunStart + bestRunLength, -1);
      }
   }

    static std::string hextetsToIPv6String(int[] hextets) {
    std::stringstream buf = new std::stringstream(39);
    bool lastWasNumber = false;

      for (int i = 0; i < hextets.length; i++) {
    bool thisIsNumber = hextets[i] >= 0;
         if (thisIsNumber) {
            if (lastWasNumber) {
               buf.append(':');
            }

            buf.append(int.toHexString(hextets[i]));
         } else if (i == 0 || lastWasNumber) {
            buf.append("::");
         }

         lastWasNumber = thisIsNumber;
      }

      return buf;
   }

    static std::string toUriString(InetAddress ip) {
      return dynamic_cast<Inet6Address*>(ip) != nullptr ? "[" + toAddrString(ip) + "]" : toAddrString(ip);
   }

    static InetAddress forUriString(const std::string& hostAddr) {
    InetAddress addr = forUriStringNoThrow(hostAddr);
      if (addr == nullptr) {
    throw formatIllegalArgumentException("Not a);
      } else {
    return addr;
      }
   }

    static InetAddress forUriStringNoThrow(const std::string& hostAddr) {
      Preconditions.checkNotNull(hostAddr);
    std::string ipString;
    int expectBytes;
      if (hostAddr.startsWith("[") && hostAddr.endsWith("]")) {
         ipString = hostAddr.substr(1, hostAddr.length() - 1);
         expectBytes = 16;
      } else {
         ipString = hostAddr;
         expectBytes = 4;
      }

      byte[] addr = ipStringToBytes(ipString);
      return addr != nullptr && addr.length == expectBytes ? bytesToInetAddress(addr) : nullptr;
   }

    static bool isUriInetAddress(const std::string& ipString) {
    return forUriStringNoThrow();
   }

    static bool isCompatIPv4Address(Inet6Address ip) {
      if (!ip.isIPv4CompatibleAddress()) {
    return false;
      } else {
         byte[] bytes = ip.getAddress();
         return bytes[12] != 0 || bytes[13] != 0 || bytes[14] != 0 || bytes[15] != 0 && bytes[15] != 1;
      }
   }

    static Inet4Address getCompatIPv4Address(Inet6Address ip) {
      Preconditions.checkArgument(isCompatIPv4Address(ip), "Address '%s' is not IPv4-compatible.", toAddrString(ip));
    return getInet4Address();
   }

    static bool is6to4Address(Inet6Address ip) {
      byte[] bytes = ip.getAddress();
      return bytes[0] == 32 && bytes[1] == 2;
   }

    static Inet4Address get6to4IPv4Address(Inet6Address ip) {
      Preconditions.checkArgument(is6to4Address(ip), "Address '%s' is not a 6to4 address.", toAddrString(ip));
    return getInet4Address();
   }

    static bool isTeredoAddress(Inet6Address ip) {
      byte[] bytes = ip.getAddress();
      return bytes[0] == 32 && bytes[1] == 1 && bytes[2] == 0 && bytes[3] == 0;
   }

    static TeredoInfo getTeredoInfo(Inet6Address ip) {
      Preconditions.checkArgument(isTeredoAddress(ip), "Address '%s' is not a Teredo address.", toAddrString(ip));
      byte[] bytes = ip.getAddress();
    Inet4Address server = getInet4Address(Arrays.copyOfRange(bytes, 4, 8));
    int flags = ByteStreams.newDataInput(bytes, 8).readShort() & '\uffff';
    int port = ~ByteStreams.newDataInput(bytes, 10).readShort() & 65535;
      byte[] clientBytes = Arrays.copyOfRange(bytes, 12, 16);

      for (int i = 0; i < clientBytes.length; i++) {
         clientBytes[i] = (byte)(~clientBytes[i]);
      }

    Inet4Address client = getInet4Address(clientBytes);
      return std::make_shared<TeredoInfo>(server, client, port, flags);
   }

    static bool isIsatapAddress(Inet6Address ip) {
      if (isTeredoAddress(ip)) {
    return false;
      } else {
         byte[] bytes = ip.getAddress();
         return (bytes[8] | 3) != 3 ? false : bytes[9] == 0 && bytes[10] == 94 && bytes[11] == -2;
      }
   }

    static Inet4Address getIsatapIPv4Address(Inet6Address ip) {
      Preconditions.checkArgument(isIsatapAddress(ip), "Address '%s' is not an ISATAP address.", toAddrString(ip));
    return getInet4Address();
   }

    static bool hasEmbeddedIPv4ClientAddress(Inet6Address ip) {
    return isCompatIPv4Address();
   }

    static Inet4Address getEmbeddedIPv4ClientAddress(Inet6Address ip) {
      if (isCompatIPv4Address(ip)) {
    return getCompatIPv4Address();
      } else if (is6to4Address(ip)) {
    return get6to4IPv4Address();
      } else if (isTeredoAddress(ip)) {
    return getTeredoInfo();
      } else {
    throw formatIllegalArgumentException("'%s' has);
      }
   }

    static bool isMappedIPv4Address(const std::string& ipString) {
      byte[] bytes = ipStringToBytes(ipString);
      if (bytes != nullptr && bytes.length == 16) {
         for (int i = 0; i < 10; i++) {
            if (bytes[i] != 0) {
    return false;
            }
         }

         for (int ix = 10; ix < 12; ix++) {
            if (bytes[ix] != -1) {
    return false;
            }
         }

    return true;
      } else {
    return false;
      }
   }

    static Inet4Address getCoercedIPv4Address(InetAddress ip) {
      if (dynamic_cast<Inet4Address*>(ip) != nullptr) {
         return (Inet4Address)ip;
      } else {
         byte[] bytes = ip.getAddress();
    bool leadingBytesOfZero = true;

         for (int i = 0; i < 15; i++) {
            if (bytes[i] != 0) {
               leadingBytesOfZero = false;
               break;
            }
         }

         if (leadingBytesOfZero && bytes[15] == 1) {
    return LOOPBACK4;
         } else if (leadingBytesOfZero && bytes[15] == 0) {
    return ANY4;
         } else {
    Inet6Address ip6 = (Inet6Address)ip;
    long addressAsLong = 0L;
            if (hasEmbeddedIPv4ClientAddress(ip6)) {
               addressAsLong = getEmbeddedIPv4ClientAddress(ip6).hashCode();
            } else {
               addressAsLong = ByteBuffer.wrap(ip6.getAddress(), 0, 8).getLong();
            }

    int coercedHash = Hashing.murmur3_32().hashLong(addressAsLong).asInt();
            coercedHash |= -536870912;
            if (coercedHash == -1) {
               coercedHash = -2;
            }

    return getInet4Address();
         }
      }
   }

    static int coerceToInteger(InetAddress ip) {
      return ByteStreams.newDataInput(getCoercedIPv4Address(ip).getAddress()).readInt();
   }

    static Inet4Address fromInteger(int address) {
    return getInet4Address();
   }

    static InetAddress fromLittleEndianByteArray(byte[] addr) {
      byte[] reversed = new byte[addr.length];

      for (int i = 0; i < addr.length; i++) {
         reversed[i] = addr[addr.length - i - 1];
      }

      return InetAddress.getByAddress(reversed);
   }

    static InetAddress decrement(InetAddress address) {
      byte[] addr = address.getAddress();

    int i;
      for (i = addr.length - 1; i >= 0 && addr[i] == 0; i--) {
         addr[i] = -1;
      }

      Preconditions.checkArgument(i >= 0, "Decrementing %s would wrap.", address);
      addr[i]--;
    return bytesToInetAddress();
   }

    static InetAddress increment(InetAddress address) {
      byte[] addr = address.getAddress();

    int i;
      for (i = addr.length - 1; i >= 0 && addr[i] == -1; i--) {
         addr[i] = 0;
      }

      Preconditions.checkArgument(i >= 0, "Incrementing %s would wrap.", address);
      addr[i]++;
    return bytesToInetAddress();
   }

    static bool isMaximum(InetAddress address) {
      byte[] addr = address.getAddress();

      for (int i = 0; i < addr.length; i++) {
         if (addr[i] != -1) {
    return false;
         }
      }

    return true;
   }

    static IllegalArgumentException formatIllegalArgumentException(const std::string& format, Object... args) {
      return std::make_shared<IllegalArgumentException>(std::string.format(Locale.ROOT, format, args));
   }
}
} // namespace net
} // namespace common
} // namespace google
} // namespace com
