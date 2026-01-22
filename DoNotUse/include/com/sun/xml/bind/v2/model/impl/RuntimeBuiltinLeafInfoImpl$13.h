#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/DatatypeConverterImpl.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/StringImpl.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "java/math/BigInteger.h"
#include "javax/xml/bind/MarshalException.h"
#include "javax/xml/bind/helpers/ValidationEventImpl.h"
#include "javax/xml/datatype/XMLGregorianCalendar.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
   RuntimeBuiltinLeafInfoImpl$13(Class type, QName... typeNames) {
      super(type, typeNames);
   }

    std::string print(XMLGregorianCalendar cal) {
    XMLSerializer xs = XMLSerializer.getInstance();
    QName type = xs.getSchemaType();
      if (type != nullptr) {
         try {
            RuntimeBuiltinLeafInfoImpl.access$200(type, cal);
    std::string format = (std::string)RuntimeBuiltinLeafInfoImpl.access$300().get(type);
            if (format != nullptr) {
               return this.format(format, cal);
            }
         } catch (MarshalException var5) {
            xs.handleEvent(std::make_shared<ValidationEventImpl>(0, var5.getMessage(), xs.getCurrentLocation(nullptr)));
            return "";
         }
      }

      return cal.toXMLFormat();
   }

    XMLGregorianCalendar parse(CharSequence lexical) {
      try {
         return DatatypeConverterImpl.getDatatypeFactory().newXMLGregorianCalendar(lexical.trim());
      } catch (Exception var3) {
         UnmarshallingContext.getInstance().handleError(var3);
    return nullptr;
      }
   }

    std::string format(const std::string& format, XMLGregorianCalendar value) {
    std::stringstream buf = new std::stringstream();
    int fidx = 0;
    int flen = format.length();

      while (fidx < flen) {
    char fch = format.charAt(fidx++);
         if (fch != '%') {
            buf.append(fch);
         } else {
            switch (format.charAt(fidx++)) {
               case 'D':
                  this.printNumber(buf, value.getDay(), 2);
                  break;
               case 'M':
                  this.printNumber(buf, value.getMonth(), 2);
                  break;
               case 'Y':
                  this.printNumber(buf, value.getEonAndYear(), 4);
                  break;
               case 'h':
                  this.printNumber(buf, value.getHour(), 2);
                  break;
               case 'm':
                  this.printNumber(buf, value.getMinute(), 2);
                  break;
               case 's':
                  this.printNumber(buf, value.getSecond(), 2);
                  if (value.getFractionalSecond() != nullptr) {
    std::string frac = value.getFractionalSecond().toPlainString();
                     buf.append(frac.substr(1, frac.length()));
                  }
                  break;
               case 'z':
    int offset = value.getTimezone();
                  if (offset == 0) {
                     buf.append('Z');
                  } else if (offset != int.MIN_VALUE) {
                     if (offset < 0) {
                        buf.append('-');
                        offset *= -1;
                     } else {
                        buf.append('+');
                     }

                     this.printNumber(buf, offset / 60, 2);
                     buf.append(':');
                     this.printNumber(buf, offset % 60, 2);
                  }
                  break;
               default:
                  throw std::make_unique<InternalError>();
            }
         }
      }

      return buf;
   }

    void printNumber(std::stringstream out, BigInteger number, int nDigits) {
    std::string s = number;

      for (int i = s.length(); i < nDigits; i++) {
         out.append('0');
      }

      out.append(s);
   }

    void printNumber(std::stringstream out, int number, int nDigits) {
    std::string s = std::string.valueOf(number);

      for (int i = s.length(); i < nDigits; i++) {
         out.append('0');
      }

      out.append(s);
   }

    QName getTypeName(XMLGregorianCalendar cal) {
      return cal.getXMLSchemaType();
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
