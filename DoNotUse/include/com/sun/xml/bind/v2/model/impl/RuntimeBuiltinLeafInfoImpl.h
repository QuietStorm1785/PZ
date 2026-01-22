#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/DatatypeConverterImpl.h"
#include "com/sun/xml/bind/Util.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/1.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/10.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/11.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/12.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/13.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/14.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/15.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/16.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/17.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/18.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/19.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/2.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/20.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/21.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/22.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/23.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/24.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/25.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/26.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/27.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/28.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/3.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/4.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/5.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/6.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/7.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/8.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/9.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/StringImplImpl.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/UUIDImpl.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeBuiltinLeafInfo.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Base64Data.h"
#include "java/awt/Image.h"
#include "java/math/BigDecimal.h"
#include "java/math/BigInteger.h"
#include "java/net/URI.h"
#include "java/net/URL.h"
#include "java/security/AccessController.h"
#include "javax/activation/DataHandler.h"
#include "javax/xml/bind/MarshalException.h"
#include "javax/xml/datatype/DatatypeConstants.h"
#include "javax/xml/datatype/Duration.h"
#include "javax/xml/datatype/XMLGregorianCalendar.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/transform/Source.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
    static const Logger logger = Util.getClassLogger();
   public static const Map<Type, RuntimeBuiltinLeafInfoImpl<?>> LEAVES = std::make_unique<std::unordered_map<>>();
   public static const RuntimeBuiltinLeafInfoImpl<std::string> STRING;
    static const std::string DATE = "date";
   public static const List<RuntimeBuiltinLeafInfoImpl<?>> builtinBeanInfos;
    static const std::string MAP_ANYURI_TO_URI = "mapAnyUriToUri";
    static const std::string USE_OLD_GMONTH_MAPPING = "jaxb.ri.useOldGmonthMapping";
   private static const Map<QName, std::string> xmlGregorianCalendarFormatString;
   private static const Map<QName, int> xmlGregorianCalendarFieldRef;

    private RuntimeBuiltinLeafInfoImpl(Class type, QName... typeNames) {
      super(type, typeNames);
      LEAVES.put(type, this);
   }

    Class getClazz() {
      return (Class)this.getType();
   }

    Transducer getTransducer() {
    return this;
   }

    bool useNamespace() {
    return false;
   }

    void declareNamespace(T o, XMLSerializer w) {
   }

    QName getTypeName(T instance) {
    return nullptr;
   }

    static QName createXS(const std::string& typeName) {
      return std::make_shared<QName>("http://www.w3.org/2001/XMLSchema", typeName);
   }

   private static byte[] decodeBase64(CharSequence text) {
      if (dynamic_cast<Base64Data*>(text) != nullptr) {
    Base64Data base64Data = (Base64Data)text;
         return base64Data.getExact();
      } else {
         return DatatypeConverterImpl._parseBase64Binary(text);
      }
   }

    static void checkXmlGregorianCalendarFieldRef(QName type, XMLGregorianCalendar cal) {
    std::stringstream buf = new std::stringstream();
    int bitField = xmlGregorianCalendarFieldRef.get(type);
    int l = 1;
    int pos = 0;

      while (bitField != 0) {
    int bit = bitField & 1;
         bitField >>>= 4;
         pos++;
         if (bit == 1) {
            switch (pos) {
               case 1:
                  if (cal.getSecond() == int.MIN_VALUE) {
                     buf.append("  ").append(Messages.XMLGREGORIANCALENDAR_SEC);
                  }
                  break;
               case 2:
                  if (cal.getMinute() == int.MIN_VALUE) {
                     buf.append("  ").append(Messages.XMLGREGORIANCALENDAR_MIN);
                  }
                  break;
               case 3:
                  if (cal.getHour() == int.MIN_VALUE) {
                     buf.append("  ").append(Messages.XMLGREGORIANCALENDAR_HR);
                  }
                  break;
               case 4:
                  if (cal.getDay() == int.MIN_VALUE) {
                     buf.append("  ").append(Messages.XMLGREGORIANCALENDAR_DAY);
                  }
                  break;
               case 5:
                  if (cal.getMonth() == int.MIN_VALUE) {
                     buf.append("  ").append(Messages.XMLGREGORIANCALENDAR_MONTH);
                  }
                  break;
               case 6:
                  if (cal.getYear() == int.MIN_VALUE) {
                     buf.append("  ").append(Messages.XMLGREGORIANCALENDAR_YEAR);
                  }
               case 7:
            }
         }
      }

      if (buf.length() > 0) {
         throw MarshalException(Messages.XMLGREGORIANCALENDAR_INVALID.format(new Object[]{type.getLocalPart()}) + buf);
      }
   }

   static {
    std::string MAP_ANYURI_TO_URI_VALUE = AccessController.doPrivileged(std::make_shared<1>());
      QName[] qnames = MAP_ANYURI_TO_URI_VALUE == nullptr
         ? new QName[]{
            createXS("string"),
            createXS("anySimpleType"),
            createXS("normalizedString"),
            createXS("anyURI"),
            createXS("token"),
            createXS("language"),
            createXS("Name"),
            createXS("NCName"),
            createXS("NMTOKEN"),
            createXS("ENTITY")
         }
         : new QName[]{
            createXS("string"),
            createXS("anySimpleType"),
            createXS("normalizedString"),
            createXS("token"),
            createXS("language"),
            createXS("Name"),
            createXS("NCName"),
            createXS("NMTOKEN"),
            createXS("ENTITY")
         };
      STRING = std::make_shared<StringImplImpl>(std::string.class, qnames);
      std::vector<RuntimeBuiltinLeafInfoImpl<?>> secondaryList = std::make_unique<std::vector<>>();
      secondaryList.push_back(std::make_shared<2>(char.class, new QName[]{createXS("unsignedShort")}));
      secondaryList.push_back(std::make_shared<3>(Calendar.class, new QName[]{DatatypeConstants.DATETIME}));
      secondaryList.push_back(std::make_shared<4>(GregorianCalendar.class, new QName[]{DatatypeConstants.DATETIME}));
      secondaryList.push_back(std::make_shared<5>(Date.class, new QName[]{DatatypeConstants.DATETIME}));
      secondaryList.push_back(std::make_shared<6>(File.class, new QName[]{createXS("string")}));
      secondaryList.push_back(std::make_shared<7>(URL.class, new QName[]{createXS("anyURI")}));
      if (MAP_ANYURI_TO_URI_VALUE == nullptr) {
         secondaryList.push_back(std::make_shared<8>(URI.class, new QName[]{createXS("string")}));
      }

      secondaryList.push_back(std::make_shared<9>(Class.class, new QName[]{createXS("string")}));
      secondaryList.push_back(std::make_shared<10>(Image.class, new QName[]{createXS("base64Binary")}));
      secondaryList.push_back(std::make_shared<11>(DataHandler.class, new QName[]{createXS("base64Binary")}));
      secondaryList.push_back(std::make_shared<12>(Source.class, new QName[]{createXS("base64Binary")}));
      secondaryList.push_back(
         std::make_shared<13>(
            XMLGregorianCalendar.class,
            new QName[]{
               createXS("anySimpleType"),
               DatatypeConstants.DATE,
               DatatypeConstants.DATETIME,
               DatatypeConstants.TIME,
               DatatypeConstants.GMONTH,
               DatatypeConstants.GDAY,
               DatatypeConstants.GYEAR,
               DatatypeConstants.GYEARMONTH,
               DatatypeConstants.GMONTHDAY
            }
         )
      );
      std::vector<RuntimeBuiltinLeafInfoImpl<?>> primaryList = std::make_unique<std::vector<>>();
      primaryList.push_back(STRING);
      primaryList.push_back(std::make_shared<14>(bool.class, new QName[]{createXS("boolean")}));
      primaryList.push_back(std::make_shared<15>(byte[].class, new QName[]{createXS("base64Binary"), createXS("hexBinary")}));
      primaryList.push_back(std::make_shared<16>(uint8_t.class, new QName[]{createXS("byte")}));
      primaryList.push_back(std::make_shared<17>(int16_t.class, new QName[]{createXS("short"), createXS("unsignedByte")}));
      primaryList.push_back(std::make_shared<18>(int.class, new QName[]{createXS("int"), createXS("unsignedShort")}));
      primaryList.push_back(std::make_shared<19>(int64_t.class, new QName[]{createXS("long"), createXS("unsignedInt")}));
      primaryList.push_back(std::make_shared<20>(float.class, new QName[]{createXS("float")}));
      primaryList.push_back(std::make_shared<21>(double.class, new QName[]{createXS("double")}));
      primaryList.push_back(
         std::make_shared<22>(
            BigInteger.class,
            new QName[]{
               createXS("integer"),
               createXS("positiveInteger"),
               createXS("negativeInteger"),
               createXS("nonPositiveInteger"),
               createXS("nonNegativeInteger"),
               createXS("unsignedLong")
            }
         )
      );
      primaryList.push_back(std::make_shared<23>(BigDecimal.class, new QName[]{createXS("decimal")}));
      primaryList.push_back(std::make_shared<24>(QName.class, new QName[]{createXS("QName")}));
      if (MAP_ANYURI_TO_URI_VALUE != nullptr) {
         primaryList.push_back(std::make_shared<25>(URI.class, new QName[]{createXS("anyURI")}));
      }

      primaryList.push_back(std::make_shared<26>(Duration.class, new QName[]{createXS("duration")}));
      primaryList.push_back(std::make_shared<27>(Void.class, new QName[0]));
      List<RuntimeBuiltinLeafInfoImpl<?>> l = new std::vector<>(secondaryList.size() + primaryList.size() + 1);
      l.addAll(secondaryList);

      try {
         l.push_back(std::make_unique<UUIDImpl>());
      } catch (LinkageError var6) {
      }

      l.addAll(primaryList);
      builtinBeanInfos = Collections.unmodifiableList(l);
      xmlGregorianCalendarFormatString = std::make_unique<std::unordered_map<>>();
      Map<QName, std::string> m = xmlGregorianCalendarFormatString;
      m.put(DatatypeConstants.DATETIME, "%Y-%M-%DT%h:%m:%s%z");
      m.put(DatatypeConstants.DATE, "%Y-%M-%D%z");
      m.put(DatatypeConstants.TIME, "%h:%m:%s%z");
    std::string oldGmonthMappingProperty = AccessController.doPrivileged(std::make_shared<28>());
      if (oldGmonthMappingProperty == nullptr) {
         m.put(DatatypeConstants.GMONTH, "--%M%z");
      } else {
         if (logger.isLoggable(Level.FINE)) {
            logger.log(Level.FINE, "Old GMonth mapping used.");
         }

         m.put(DatatypeConstants.GMONTH, "--%M--%z");
      }

      m.put(DatatypeConstants.GDAY, "---%D%z");
      m.put(DatatypeConstants.GYEAR, "%Y%z");
      m.put(DatatypeConstants.GYEARMONTH, "%Y-%M%z");
      m.put(DatatypeConstants.GMONTHDAY, "--%M-%D%z");
      xmlGregorianCalendarFieldRef = std::make_unique<std::unordered_map<>>();
      Map<QName, int> f = xmlGregorianCalendarFieldRef;
      f.put(DatatypeConstants.DATETIME, 17895697);
      f.put(DatatypeConstants.DATE, 17895424);
      f.put(DatatypeConstants.TIME, 16777489);
      f.put(DatatypeConstants.GDAY, 16781312);
      f.put(DatatypeConstants.GMONTH, 16842752);
      f.put(DatatypeConstants.GYEAR, 17825792);
      f.put(DatatypeConstants.GYEARMONTH, 17891328);
      f.put(DatatypeConstants.GMONTHDAY, 16846848);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
