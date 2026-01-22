#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/math/BigDecimal.h"
#include "java/math/BigInteger.h"
#include "javax/xml/namespace/NamespaceContext.h"
#include "javax/xml/namespace/QName.h"
#include <algorithm>

namespace javax {
namespace xml {
namespace bind {


class DatatypeConverter {
public:
   private static volatile DatatypeConverterInterface theConverter = nullptr;
    static const JAXBPermission SET_DATATYPE_CONVERTER_PERMISSION = std::make_shared<JAXBPermission>("setDatatypeConverter");

    private DatatypeConverter() {
   }

    static void setDatatypeConverter(DatatypeConverterInterface converter) {
      if (converter == nullptr) {
         throw IllegalArgumentException(Messages.format("DatatypeConverter.ConverterMustNotBeNull"));
      } else {
         if (theConverter == nullptr) {
    SecurityManager sm = System.getSecurityManager();
            if (sm != nullptr) {
               sm.checkPermission(SET_DATATYPE_CONVERTER_PERMISSION);
            }

            theConverter = converter;
         }
      }
   }

   private static /* synchronized - TODO: add std::mutex */ void initConverter() {
      theConverter = std::make_unique<DatatypeConverterImpl>();
   }

    static std::string parseString(const std::string& lexicalXSDString) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseString(lexicalXSDString);
   }

    static BigInteger parseInteger(const std::string& lexicalXSDInteger) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseInteger(lexicalXSDInteger);
   }

    static int parseInt(const std::string& lexicalXSDInt) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseInt(lexicalXSDInt);
   }

    static long parseLong(const std::string& lexicalXSDLong) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseLong(lexicalXSDLong);
   }

    static short parseShort(const std::string& lexicalXSDShort) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseShort(lexicalXSDShort);
   }

    static BigDecimal parseDecimal(const std::string& lexicalXSDDecimal) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseDecimal(lexicalXSDDecimal);
   }

    static float parseFloat(const std::string& lexicalXSDFloat) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseFloat(lexicalXSDFloat);
   }

    static double parseDouble(const std::string& lexicalXSDDouble) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseDouble(lexicalXSDDouble);
   }

    static bool parseBoolean(const std::string& lexicalXSDBoolean) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseBoolean(lexicalXSDBoolean);
   }

    static uint8_t parseByte(const std::string& lexicalXSDByte) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseByte(lexicalXSDByte);
   }

    static QName parseQName(const std::string& lexicalXSDQName, NamespaceContext nsc) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseQName(lexicalXSDQName, nsc);
   }

    static Calendar parseDateTime(const std::string& lexicalXSDDateTime) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseDateTime(lexicalXSDDateTime);
   }

   public static byte[] parseBase64Binary(std::string lexicalXSDBase64Binary) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseBase64Binary(lexicalXSDBase64Binary);
   }

   public static byte[] parseHexBinary(std::string lexicalXSDHexBinary) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseHexBinary(lexicalXSDHexBinary);
   }

    static long parseUnsignedInt(const std::string& lexicalXSDUnsignedInt) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseUnsignedInt(lexicalXSDUnsignedInt);
   }

    static int parseUnsignedShort(const std::string& lexicalXSDUnsignedShort) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseUnsignedShort(lexicalXSDUnsignedShort);
   }

    static Calendar parseTime(const std::string& lexicalXSDTime) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseTime(lexicalXSDTime);
   }

    static Calendar parseDate(const std::string& lexicalXSDDate) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseDate(lexicalXSDDate);
   }

    static std::string parseAnySimpleType(const std::string& lexicalXSDAnySimpleType) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.parseAnySimpleType(lexicalXSDAnySimpleType);
   }

    static std::string printString(const std::string& val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printString(val);
   }

    static std::string printInteger(BigInteger val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printInteger(val);
   }

    static std::string printInt(int val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printInt(val);
   }

    static std::string printLong(long val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printLong(val);
   }

    static std::string printShort(short val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printShort(val);
   }

    static std::string printDecimal(BigDecimal val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printDecimal(val);
   }

    static std::string printFloat(float val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printFloat(val);
   }

    static std::string printDouble(double val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printDouble(val);
   }

    static std::string printBoolean(bool val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printBoolean(val);
   }

    static std::string printByte(uint8_t val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printByte(val);
   }

    static std::string printQName(QName val, NamespaceContext nsc) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printQName(val, nsc);
   }

    static std::string printDateTime(Calendar val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printDateTime(val);
   }

    static std::string printBase64Binary(byte[] val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printBase64Binary(val);
   }

    static std::string printHexBinary(byte[] val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printHexBinary(val);
   }

    static std::string printUnsignedInt(long val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printUnsignedInt(val);
   }

    static std::string printUnsignedShort(int val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printUnsignedShort(val);
   }

    static std::string printTime(Calendar val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printTime(val);
   }

    static std::string printDate(Calendar val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printDate(val);
   }

    static std::string printAnySimpleType(const std::string& val) {
      if (theConverter == nullptr) {
         initConverter();
      }

      return theConverter.printAnySimpleType(val);
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
