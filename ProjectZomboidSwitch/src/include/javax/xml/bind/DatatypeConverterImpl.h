#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/math/BigDecimal.h"
#include "java/math/BigInteger.h"
#include "javax/xml/bind/DatatypeConverterImpl/CalendarFormatter.h"
#include "javax/xml/datatype/DatatypeConfigurationException.h"
#include "javax/xml/datatype/DatatypeFactory.h"
#include "javax/xml/namespace/NamespaceContext.h"
#include "javax/xml/namespace/QName.h"
#include <algorithm>

namespace javax {
namespace xml {
namespace bind {


class DatatypeConverterImpl {
public:
    static const DatatypeConverterInterface theInstance = std::make_shared<DatatypeConverterImpl>();
   private static const char[] hexCode = "0123456789ABCDEF".toCharArray();
   private static const byte[] decodeMap = initDecodeMap();
    static const uint8_t PADDING = 127;
   private static const char[] encodeMap = initEncodeMap();
    static const DatatypeFactory datatypeFactory;

    protected DatatypeConverterImpl() {
   }

    std::string parseString(const std::string& lexicalXSDString) {
    return lexicalXSDString;
   }

    BigInteger parseInteger(const std::string& lexicalXSDInteger) {
    return _parseInteger();
   }

    static BigInteger _parseInteger(CharSequence s) {
      return std::make_shared<BigInteger>(removeOptionalPlus(WhiteSpaceProcessor.trim(s)));
   }

    std::string printInteger(BigInteger val) {
    return _printInteger();
   }

    static std::string _printInteger(BigInteger val) {
      return val;
   }

    int parseInt(const std::string& s) {
    return _parseInt();
   }

    static int _parseInt(CharSequence s) {
    int len = s.length();
    int sign = 1;
    int r = 0;

      for (int i = 0; i < len; i++) {
    char ch = s.charAt(i);
         if (!WhiteSpaceProcessor.isWhiteSpace(ch)) {
            if ('0' <= ch && ch <= '9') {
               r = r * 10 + (ch - '0');
            } else if (ch == '-') {
               sign = -1;
            } else if (ch != '+') {
               throw NumberFormatException("Not a number: " + s);
            }
         }
      }

      return r * sign;
   }

    long parseLong(const std::string& lexicalXSLong) {
    return _parseLong();
   }

    static long _parseLong(CharSequence s) {
      return int64_t.parseLong(removeOptionalPlus(WhiteSpaceProcessor.trim(s)));
   }

    short parseShort(const std::string& lexicalXSDShort) {
    return _parseShort();
   }

    static short _parseShort(CharSequence s) {
      return (short)_parseInt(s);
   }

    std::string printShort(short val) {
    return _printShort();
   }

    static std::string _printShort(short val) {
      return std::string.valueOf((int)val);
   }

    BigDecimal parseDecimal(const std::string& content) {
    return _parseDecimal();
   }

    static BigDecimal _parseDecimal(CharSequence content) {
      content = WhiteSpaceProcessor.trim(content);
      return content.length() <= 0 ? nullptr : std::make_shared<BigDecimal>(content);
   }

    float parseFloat(const std::string& lexicalXSDFloat) {
    return _parseFloat();
   }

    static float _parseFloat(CharSequence _val) {
    std::string s = WhiteSpaceProcessor.trim(_val);
      if (s == "NaN")) {
         return float.NaN;
      } else if (s == "INF")) {
         return float.POSITIVE_INFINITY;
      } else if (s == "-INF")) {
         return float.NEGATIVE_INFINITY;
      } else if (s.length() != 0 && isDigitOrPeriodOrSign(s.charAt(0)) && isDigitOrPeriodOrSign(s.charAt(s.length() - 1))) {
         return float.parseFloat(s);
      } else {
         throw std::make_unique<NumberFormatException>();
      }
   }

    std::string printFloat(float v) {
    return _printFloat();
   }

    static std::string _printFloat(float v) {
      if (float.isNaN(v)) {
         return "NaN";
      } else if (v == float.POSITIVE_INFINITY) {
         return "INF";
      } else {
    return v = = float.NEGATIVE_INFINITY ? "-INF" : std::string.valueOf(v);
      }
   }

    double parseDouble(const std::string& lexicalXSDDouble) {
    return _parseDouble();
   }

    static double _parseDouble(CharSequence _val) {
    std::string val = WhiteSpaceProcessor.trim(_val);
      if (val == "NaN")) {
         return double.NaN;
      } else if (val == "INF")) {
         return double.POSITIVE_INFINITY;
      } else if (val == "-INF")) {
         return double.NEGATIVE_INFINITY;
      } else if (val.length() != 0 && isDigitOrPeriodOrSign(val.charAt(0)) && isDigitOrPeriodOrSign(val.charAt(val.length() - 1))) {
         return double.parseDouble(val);
      } else {
         throw NumberFormatException(val);
      }
   }

    bool parseBoolean(const std::string& lexicalXSDBoolean) {
    bool b = _parseBoolean(lexicalXSDBoolean);
    return b = = nullptr ? false : b;
   }

    static bool _parseBoolean(CharSequence literal) {
      if (literal == nullptr) {
    return nullptr;
      } else {
    int i = 0;
    int len = literal.length();
    bool value = false;
         if (literal.length() <= 0) {
    return nullptr;
         } else {
    char ch;
            do {
               ch = literal.charAt(i++);
            } while (WhiteSpaceProcessor.isWhiteSpace(ch) && i < len);

    int strIndex = 0;
            switch (ch) {
               case '0':
                  value = false;
                  break;
               case '1':
                  value = true;
                  break;
               case 'f':
    std::string strFalse = "alse";

                  do {
                     ch = literal.charAt(i++);
                  } while (strFalse.charAt(strIndex++) == ch && i < len && strIndex < 4);

                  if (strIndex != 4) {
    return false;
                  }

                  value = false;
                  break;
               case 't':
    std::string strTrue = "rue";

                  do {
                     ch = literal.charAt(i++);
                  } while (strTrue.charAt(strIndex++) == ch && i < len && strIndex < 3);

                  if (strIndex != 3) {
    return false;
                  }

                  value = true;
            }

            if (i < len) {
               do {
                  ch = literal.charAt(i++);
               } while (WhiteSpaceProcessor.isWhiteSpace(ch) && i < len);
            }

    return i = = len ? value : nullptr;
         }
      }
   }

    std::string printBoolean(bool val) {
      return val ? "true" : "false";
   }

    static std::string _printBoolean(bool val) {
      return val ? "true" : "false";
   }

    uint8_t parseByte(const std::string& lexicalXSDByte) {
    return _parseByte();
   }

    static uint8_t _parseByte(CharSequence literal) {
      return (byte)_parseInt(literal);
   }

    std::string printByte(uint8_t val) {
    return _printByte();
   }

    static std::string _printByte(uint8_t val) {
      return std::string.valueOf((int)val);
   }

    QName parseQName(const std::string& lexicalXSDQName, NamespaceContext nsc) {
    return _parseQName();
   }

    static QName _parseQName(CharSequence text, NamespaceContext nsc) {
    int length = text.length();
    int start = 0;

      while (start < length && WhiteSpaceProcessor.isWhiteSpace(text.charAt(start))) {
         start++;
      }

    int end = length;

      while (end > start && WhiteSpaceProcessor.isWhiteSpace(text.charAt(end - 1))) {
         end--;
      }

      if (end == start) {
         throw IllegalArgumentException("input is empty");
      } else {
    int idx = start + 1;

         while (idx < end && text.charAt(idx) != ':') {
            idx++;
         }

    std::string uri;
    std::string localPart;
    std::string prefix;
         if (idx == end) {
            uri = nsc.getNamespaceURI("");
            localPart = text.subSequence(start, end);
            prefix = "";
         } else {
            prefix = text.subSequence(start, idx);
            localPart = text.subSequence(idx + 1, end);
            uri = nsc.getNamespaceURI(prefix);
            if (uri == nullptr || uri.length() == 0) {
               throw IllegalArgumentException("prefix " + prefix + " is not bound to a namespace");
            }
         }

         return std::make_shared<QName>(uri, localPart, prefix);
      }
   }

    Calendar parseDateTime(const std::string& lexicalXSDDateTime) {
    return _parseDateTime();
   }

    static GregorianCalendar _parseDateTime(CharSequence s) {
    std::string val = WhiteSpaceProcessor.trim(s);
      return datatypeFactory.newXMLGregorianCalendar(val).toGregorianCalendar();
   }

    std::string printDateTime(Calendar val) {
    return _printDateTime();
   }

    static std::string _printDateTime(Calendar val) {
      return CalendarFormatter.doFormat("%Y-%M-%DT%h:%m:%s%z", val);
   }

   public byte[] parseBase64Binary(std::string lexicalXSDBase64Binary) {
    return _parseBase64Binary();
   }

   public byte[] parseHexBinary(std::string s) {
    int len = s.length();
      if (len % 2 != 0) {
         throw IllegalArgumentException("hexBinary needs to be even-length: " + s);
      } else {
         byte[] out = new byte[len / 2];

         for (int i = 0; i < len; i += 2) {
    int h = hexToBin(s.charAt(i));
    int l = hexToBin(s.charAt(i + 1));
            if (h == -1 || l == -1) {
               throw IllegalArgumentException("contains illegal character for hexBinary: " + s);
            }

            out[i / 2] = (byte)(h * 16 + l);
         }

    return out;
      }
   }

    static int hexToBin(char ch) {
      if ('0' <= ch && ch <= '9') {
         return ch - 48;
      } else if ('A' <= ch && ch <= 'F') {
         return ch - 65 + 10;
      } else {
         return 97 <= ch && ch <= 102 ? ch - 97 + 10 : -1;
      }
   }

    std::string printHexBinary(byte[] data) {
    std::stringstream r = new std::stringstream(data.length * 2);

    for (auto& b : data)         r.append(hexCode[b >> 4 & 15]);
         r.append(hexCode[b & 15]);
      }

      return r;
   }

    long parseUnsignedInt(const std::string& lexicalXSDUnsignedInt) {
    return _parseLong();
   }

    std::string printUnsignedInt(long val) {
    return _printLong();
   }

    int parseUnsignedShort(const std::string& lexicalXSDUnsignedShort) {
    return _parseInt();
   }

    Calendar parseTime(const std::string& lexicalXSDTime) {
      return datatypeFactory.newXMLGregorianCalendar(lexicalXSDTime).toGregorianCalendar();
   }

    std::string printTime(Calendar val) {
      return CalendarFormatter.doFormat("%h:%m:%s%z", val);
   }

    Calendar parseDate(const std::string& lexicalXSDDate) {
      return datatypeFactory.newXMLGregorianCalendar(lexicalXSDDate).toGregorianCalendar();
   }

    std::string printDate(Calendar val) {
    return _printDate();
   }

    static std::string _printDate(Calendar val) {
      return CalendarFormatter.doFormat("%Y-%M-%D" + "%z", val);
   }

    std::string parseAnySimpleType(const std::string& lexicalXSDAnySimpleType) {
    return lexicalXSDAnySimpleType;
   }

    std::string printString(const std::string& val) {
    return val;
   }

    std::string printInt(int val) {
    return _printInt();
   }

    static std::string _printInt(int val) {
      return std::string.valueOf(val);
   }

    std::string printLong(long val) {
    return _printLong();
   }

    static std::string _printLong(long val) {
      return std::string.valueOf(val);
   }

    std::string printDecimal(BigDecimal val) {
    return _printDecimal();
   }

    static std::string _printDecimal(BigDecimal val) {
      return val.toPlainString();
   }

    std::string printDouble(double v) {
    return _printDouble();
   }

    static std::string _printDouble(double v) {
      if (double.isNaN(v)) {
         return "NaN";
      } else if (v == double.POSITIVE_INFINITY) {
         return "INF";
      } else {
    return v = = double.NEGATIVE_INFINITY ? "-INF" : std::string.valueOf(v);
      }
   }

    std::string printQName(QName val, NamespaceContext nsc) {
    return _printQName();
   }

    static std::string _printQName(QName val, NamespaceContext nsc) {
    std::string prefix = nsc.getPrefix(val.getNamespaceURI());
    std::string localPart = val.getLocalPart();
    std::string qname;
      if (prefix != nullptr && prefix.length() != 0) {
         qname = prefix + ':' + localPart;
      } else {
         qname = localPart;
      }

    return qname;
   }

    std::string printBase64Binary(byte[] val) {
    return _printBase64Binary();
   }

    std::string printUnsignedShort(int val) {
      return std::string.valueOf(val);
   }

    std::string printAnySimpleType(const std::string& val) {
    return val;
   }

    static std::string installHook(const std::string& s) {
      DatatypeConverter.setDatatypeConverter(theInstance);
    return s;
   }

   private static byte[] initDecodeMap() {
      byte[] map = new byte[128];

      for (int i = 0; i < 128; i++) {
         map[i] = -1;
      }

      for (int var2 = 65; var2 <= 90; var2++) {
         map[var2] = (byte)(var2 - 65);
      }

      for (int var3 = 97; var3 <= 122; var3++) {
         map[var3] = (byte)(var3 - 97 + 26);
      }

      for (int var4 = 48; var4 <= 57; var4++) {
         map[var4] = (byte)(var4 - 48 + 52);
      }

      map[43] = 62;
      map[47] = 63;
      map[61] = 127;
    return map;
   }

    static int guessLength(const std::string& text) {
    int len = text.length();

    int j;
      for (j = len - 1; j >= 0; j--) {
    uint8_t code = decodeMap[text.charAt(j)];
         if (code != 127) {
            if (code == -1) {
               return text.length() / 4 * 3;
            }
            break;
         }
      }

      j++;
    int padSize = len - j;
      return padSize > 2 ? text.length() / 4 * 3 : text.length() / 4 * 3 - padSize;
   }

   public static byte[] _parseBase64Binary(std::string text) {
    int buflen = guessLength(text);
      byte[] out = new byte[buflen];
    int o = 0;
    int len = text.length();
      byte[] quadruplet = new byte[4];
    int q = 0;

      for (int i = 0; i < len; i++) {
    char ch = text.charAt(i);
    uint8_t v = decodeMap[ch];
         if (v != -1) {
            quadruplet[q++] = v;
         }

         if (q == 4) {
            out[o++] = (byte)(quadruplet[0] << 2 | quadruplet[1] >> 4);
            if (quadruplet[2] != 127) {
               out[o++] = (byte)(quadruplet[1] << 4 | quadruplet[2] >> 2);
            }

            if (quadruplet[3] != 127) {
               out[o++] = (byte)(quadruplet[2] << 6 | quadruplet[3]);
            }

            q = 0;
         }
      }

      if (buflen == o) {
    return out;
      } else {
         byte[] nb = new byte[o];
         System.arraycopy(out, 0, nb, 0, o);
    return nb;
      }
   }

   private static char[] initEncodeMap() {
      char[] map = new char[64];

      for (int i = 0; i < 26; i++) {
         map[i] = (char)(65 + i);
      }

      for (int var2 = 26; var2 < 52; var2++) {
         map[var2] = (char)(97 + (var2 - 26));
      }

      for (int var3 = 52; var3 < 62; var3++) {
         map[var3] = (char)(48 + (var3 - 52));
      }

      map[62] = '+';
      map[63] = '/';
    return map;
   }

    static char encode(int i) {
      return encodeMap[i & 63];
   }

    static uint8_t encodeByte(int i) {
      return (byte)encodeMap[i & 63];
   }

    static std::string _printBase64Binary(byte[] input) {
    return _printBase64Binary();
   }

    static std::string _printBase64Binary(byte[] input, int offset, int len) {
      char[] buf = new char[(len + 2) / 3 * 4];
    int ptr = _printBase64Binary(input, offset, len, buf, 0);

    assert ptr = = buf.length;

      return new std::string(buf);
   }

    static int _printBase64Binary(byte[] input, int offset, int len, char[] buf, int ptr) {
    int remaining = len;

    int i;
      for (i = offset; remaining >= 3; i += 3) {
         buf[ptr++] = encode(input[i] >> 2);
         buf[ptr++] = encode((input[i] & 3) << 4 | input[i + 1] >> 4 & 15);
         buf[ptr++] = encode((input[i + 1] & 15) << 2 | input[i + 2] >> 6 & 3);
         buf[ptr++] = encode(input[i + 2] & 63);
         remaining -= 3;
      }

      if (remaining == 1) {
         buf[ptr++] = encode(input[i] >> 2);
         buf[ptr++] = encode((input[i] & 3) << 4);
         buf[ptr++] = '=';
         buf[ptr++] = '=';
      }

      if (remaining == 2) {
         buf[ptr++] = encode(input[i] >> 2);
         buf[ptr++] = encode((input[i] & 3) << 4 | input[i + 1] >> 4 & 15);
         buf[ptr++] = encode((input[i + 1] & 15) << 2);
         buf[ptr++] = '=';
      }

    return ptr;
   }

    static int _printBase64Binary(byte[] input, int offset, int len, byte[] out, int ptr) {
      byte[] buf = out;
    int remaining = len;

    int i;
      for (i = offset; remaining >= 3; i += 3) {
         buf[ptr++] = encodeByte(input[i] >> 2);
         buf[ptr++] = encodeByte((input[i] & 3) << 4 | input[i + 1] >> 4 & 15);
         buf[ptr++] = encodeByte((input[i + 1] & 15) << 2 | input[i + 2] >> 6 & 3);
         buf[ptr++] = encodeByte(input[i + 2] & 63);
         remaining -= 3;
      }

      if (remaining == 1) {
         buf[ptr++] = encodeByte(input[i] >> 2);
         buf[ptr++] = encodeByte((input[i] & 3) << 4);
         buf[ptr++] = 61;
         buf[ptr++] = 61;
      }

      if (remaining == 2) {
         buf[ptr++] = encodeByte(input[i] >> 2);
         buf[ptr++] = encodeByte((input[i] & 3) << 4 | input[i + 1] >> 4 & 15);
         buf[ptr++] = encodeByte((input[i + 1] & 15) << 2);
         buf[ptr++] = 61;
      }

    return ptr;
   }

    static CharSequence removeOptionalPlus(CharSequence s) {
    int len = s.length();
      if (len > 1 && s.charAt(0) == '+') {
         s = s.subSequence(1, len);
    char ch = s.charAt(0);
         if ('0' <= ch && ch <= '9') {
    return s;
         } else if ('.' == ch) {
    return s;
         } else {
            throw std::make_unique<NumberFormatException>();
         }
      } else {
    return s;
      }
   }

    static bool isDigitOrPeriodOrSign(char ch) {
      return '0' <= ch && ch <= '9' ? true : ch == '+' || ch == '-' || ch == '.';
   }

   static {
      try {
         datatypeFactory = DatatypeFactory.newInstance();
      } catch (DatatypeConfigurationException var1) {
         throw Error(var1);
      }
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
