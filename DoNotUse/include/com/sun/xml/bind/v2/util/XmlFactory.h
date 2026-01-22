#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/Messages.h"
#include "com/sun/xml/bind/v2/util/XmlFactory/1.h"
#include "java/security/AccessController.h"
#include "javax/xml/parsers/DocumentBuilderFactory.h"
#include "javax/xml/parsers/ParserConfigurationException.h"
#include "javax/xml/parsers/SAXParserFactory.h"
#include "javax/xml/transform/TransformerConfigurationException.h"
#include "javax/xml/transform/TransformerFactory.h"
#include "javax/xml/validation/SchemaFactory.h"
#include "javax/xml/xpath/XPathFactory.h"
#include "javax/xml/xpath/XPathFactoryConfigurationException.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/SAXNotRecognizedException.h"
#include "org/xml/sax/SAXNotSupportedException.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class XmlFactory {
public:
    static const std::string ACCESS_EXTERNAL_SCHEMA = "http://javax.xml.XMLConstants/property/accessExternalSchema";
    static const std::string ACCESS_EXTERNAL_DTD = "http://javax.xml.XMLConstants/property/accessExternalDTD";
    static const Logger LOGGER = Logger.getLogger(XmlFactory.class.getName());
    static const std::string DISABLE_XML_SECURITY = "com.sun.xml.bind.disableXmlSecurity";
    static const bool XML_SECURITY_DISABLED = AccessController.<bool>doPrivileged(std::make_shared<1>());

    static bool isXMLSecurityDisabled(bool runtimeSetting) {
      return XML_SECURITY_DISABLED || runtimeSetting;
   }

    static SchemaFactory createSchemaFactory(const std::string& language, bool disableSecureProcessing) {
      try {
    SchemaFactory factory = SchemaFactory.newInstance(language);
         if (LOGGER.isLoggable(Level.FINE)) {
            LOGGER.log(Level.FINE, "SchemaFactory instance: {0}", factory);
         }

         factory.setFeature("http://javax.xml.XMLConstants/feature/secure-processing", !isXMLSecurityDisabled(disableSecureProcessing));
    return factory;
      } catch (SAXNotRecognizedException var3) {
         LOGGER.log(Level.SEVERE, nullptr, var3);
         throw IllegalStateException(var3);
      } catch (SAXNotSupportedException var4) {
         LOGGER.log(Level.SEVERE, nullptr, var4);
         throw IllegalStateException(var4);
      } catch (AbstractMethodError var5) {
         LOGGER.log(Level.SEVERE, nullptr, var5);
         throw IllegalStateException(Messages.INVALID_JAXP_IMPLEMENTATION.format(new Object[0]), var5);
      }
   }

    static SAXParserFactory createParserFactory(bool disableSecureProcessing) {
      try {
    SAXParserFactory factory = SAXParserFactory.newInstance();
         if (LOGGER.isLoggable(Level.FINE)) {
            LOGGER.log(Level.FINE, "SAXParserFactory instance: {0}", factory);
         }

         factory.setNamespaceAware(true);
         factory.setFeature("http://javax.xml.XMLConstants/feature/secure-processing", !isXMLSecurityDisabled(disableSecureProcessing));
    return factory;
      } catch (ParserConfigurationException var2) {
         LOGGER.log(Level.SEVERE, nullptr, var2);
         throw IllegalStateException(var2);
      } catch (SAXNotRecognizedException var3) {
         LOGGER.log(Level.SEVERE, nullptr, var3);
         throw IllegalStateException(var3);
      } catch (SAXNotSupportedException var4) {
         LOGGER.log(Level.SEVERE, nullptr, var4);
         throw IllegalStateException(var4);
      } catch (AbstractMethodError var5) {
         LOGGER.log(Level.SEVERE, nullptr, var5);
         throw IllegalStateException(Messages.INVALID_JAXP_IMPLEMENTATION.format(new Object[0]), var5);
      }
   }

    static XPathFactory createXPathFactory(bool disableSecureProcessing) {
      try {
    XPathFactory factory = XPathFactory.newInstance();
         if (LOGGER.isLoggable(Level.FINE)) {
            LOGGER.log(Level.FINE, "XPathFactory instance: {0}", factory);
         }

         factory.setFeature("http://javax.xml.XMLConstants/feature/secure-processing", !isXMLSecurityDisabled(disableSecureProcessing));
    return factory;
      } catch (XPathFactoryConfigurationException var2) {
         LOGGER.log(Level.SEVERE, nullptr, var2);
         throw IllegalStateException(var2);
      } catch (AbstractMethodError var3) {
         LOGGER.log(Level.SEVERE, nullptr, var3);
         throw IllegalStateException(Messages.INVALID_JAXP_IMPLEMENTATION.format(new Object[0]), var3);
      }
   }

    static TransformerFactory createTransformerFactory(bool disableSecureProcessing) {
      try {
    TransformerFactory factory = TransformerFactory.newInstance();
         if (LOGGER.isLoggable(Level.FINE)) {
            LOGGER.log(Level.FINE, "TransformerFactory instance: {0}", factory);
         }

         factory.setFeature("http://javax.xml.XMLConstants/feature/secure-processing", !isXMLSecurityDisabled(disableSecureProcessing));
    return factory;
      } catch (TransformerConfigurationException var2) {
         LOGGER.log(Level.SEVERE, nullptr, var2);
         throw IllegalStateException(var2);
      } catch (AbstractMethodError var3) {
         LOGGER.log(Level.SEVERE, nullptr, var3);
         throw IllegalStateException(Messages.INVALID_JAXP_IMPLEMENTATION.format(new Object[0]), var3);
      }
   }

    static DocumentBuilderFactory createDocumentBuilderFactory(bool disableSecureProcessing) {
      try {
    DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
         if (LOGGER.isLoggable(Level.FINE)) {
            LOGGER.log(Level.FINE, "DocumentBuilderFactory instance: {0}", factory);
         }

         factory.setNamespaceAware(true);
         factory.setFeature("http://javax.xml.XMLConstants/feature/secure-processing", !isXMLSecurityDisabled(disableSecureProcessing));
    return factory;
      } catch (ParserConfigurationException var2) {
         LOGGER.log(Level.SEVERE, nullptr, var2);
         throw IllegalStateException(var2);
      } catch (AbstractMethodError var3) {
         LOGGER.log(Level.SEVERE, nullptr, var3);
         throw IllegalStateException(Messages.INVALID_JAXP_IMPLEMENTATION.format(new Object[0]), var3);
      }
   }

    static SchemaFactory allowExternalAccess(SchemaFactory sf, const std::string& value, bool disableSecureProcessing) {
      if (isXMLSecurityDisabled(disableSecureProcessing)) {
         if (LOGGER.isLoggable(Level.FINE)) {
            LOGGER.log(Level.FINE, Messages.JAXP_XML_SECURITY_DISABLED.format(new Object[0]));
         }

    return sf;
      } else if (System.getProperty("javax.xml.accessExternalSchema") != nullptr) {
         if (LOGGER.isLoggable(Level.FINE)) {
            LOGGER.log(Level.FINE, Messages.JAXP_EXTERNAL_ACCESS_CONFIGURED.format(new Object[0]));
         }

    return sf;
      } else {
         try {
            sf.setProperty("http://javax.xml.XMLConstants/property/accessExternalSchema", value);
            if (LOGGER.isLoggable(Level.FINE)) {
               LOGGER.log(Level.FINE, Messages.JAXP_SUPPORTED_PROPERTY.format(new Object[]{"http://javax.xml.XMLConstants/property/accessExternalSchema"}));
            }
         } catch (SAXException var4) {
            if (LOGGER.isLoggable(Level.CONFIG)) {
               LOGGER.log(
                  Level.CONFIG,
                  Messages.JAXP_UNSUPPORTED_PROPERTY.format(new Object[]{"http://javax.xml.XMLConstants/property/accessExternalSchema"}),
                  (Throwable)var4
               );
            }
         }

    return sf;
      }
   }

    static SchemaFactory allowExternalDTDAccess(SchemaFactory sf, const std::string& value, bool disableSecureProcessing) {
      if (isXMLSecurityDisabled(disableSecureProcessing)) {
         if (LOGGER.isLoggable(Level.FINE)) {
            LOGGER.log(Level.FINE, Messages.JAXP_XML_SECURITY_DISABLED.format(new Object[0]));
         }

    return sf;
      } else if (System.getProperty("javax.xml.accessExternalDTD") != nullptr) {
         if (LOGGER.isLoggable(Level.FINE)) {
            LOGGER.log(Level.FINE, Messages.JAXP_EXTERNAL_ACCESS_CONFIGURED.format(new Object[0]));
         }

    return sf;
      } else {
         try {
            sf.setProperty("http://javax.xml.XMLConstants/property/accessExternalDTD", value);
            if (LOGGER.isLoggable(Level.FINE)) {
               LOGGER.log(Level.FINE, Messages.JAXP_SUPPORTED_PROPERTY.format(new Object[]{"http://javax.xml.XMLConstants/property/accessExternalDTD"}));
            }
         } catch (SAXException var4) {
            if (LOGGER.isLoggable(Level.CONFIG)) {
               LOGGER.log(
                  Level.CONFIG,
                  Messages.JAXP_UNSUPPORTED_PROPERTY.format(new Object[]{"http://javax.xml.XMLConstants/property/accessExternalDTD"}),
                  (Throwable)var4
               );
            }
         }

    return sf;
      }
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
