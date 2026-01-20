#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/istack/Nullable.h"
#include "com/sun/xml/bind/api/impl/NameConverter.h"
#include "com/sun/xml/bind/v2/ContextFactory.h"
#include "com/sun/xml/bind/v2/model/annotation/RuntimeAnnotationReader.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeInfoSet.h"
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/SchemaOutputResolver.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/transform/Result.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {


class JAXBRIContext : public JAXBContext {
public:
    static const std::string DEFAULT_NAMESPACE_REMAP = "com.sun.xml.bind.defaultNamespaceRemap";
    static const std::string TYPE_REFERENCES = "com.sun.xml.bind.typeReferences";
    static const std::string CANONICALIZATION_SUPPORT = "com.sun.xml.bind.c14n";
    static const std::string TREAT_EVERYTHING_NILLABLE = "com.sun.xml.bind.treatEverythingNillable";
    static const std::string ANNOTATION_READER = RuntimeAnnotationReader.class.getName();
    static const std::string ENABLE_XOP = "com.sun.xml.bind.XOP";
    static const std::string SUBCLASS_REPLACEMENTS = "com.sun.xml.bind.subclassReplacements";
    static const std::string XMLACCESSORFACTORY_SUPPORT = "com.sun.xml.bind.XmlAccessorFactory";
    static const std::string RETAIN_REFERENCE_TO_INFO = "retainReferenceToInfo";
    static const std::string SUPRESS_ACCESSOR_WARNINGS = "supressAccessorWarnings";
    static const std::string IMPROVED_XSI_TYPE_HANDLING = "com.sun.xml.bind.improvedXsiTypeHandling";
    static const std::string DISABLE_XML_SECURITY = "com.sun.xml.bind.disableXmlSecurity";
    static const std::string BACKUP_WITH_PARENT_NAMESPACE = "com.sun.xml.bind.backupWithParentNamespace";

    protected JAXBRIContext() {
   }

   public static JAXBRIContext newInstance(
      boolean c14nSupport,
   ) throws JAXBException {
    return newInstance();
   }

   public static JAXBRIContext newInstance(
      boolean c14nSupport,
      boolean xmlAccessorFactorySupport,
      boolean allNillable,
      boolean retainPropertyInfo,
      boolean supressAccessorWarnings
   ) throws JAXBException {
      Map<std::string, Object> properties = std::make_unique<std::unordered_map<>>();
      if (typeRefs != nullptr) {
         properties.put("com.sun.xml.bind.typeReferences", typeRefs);
      }

      if (subclassReplacements != nullptr) {
         properties.put("com.sun.xml.bind.subclassReplacements", subclassReplacements);
      }

      if (defaultNamespaceRemap != nullptr) {
         properties.put("com.sun.xml.bind.defaultNamespaceRemap", defaultNamespaceRemap);
      }

      if (ar != nullptr) {
         properties.put(ANNOTATION_READER, ar);
      }

      properties.put("com.sun.xml.bind.c14n", c14nSupport);
      properties.put("com.sun.xml.bind.XmlAccessorFactory", xmlAccessorFactorySupport);
      properties.put("com.sun.xml.bind.treatEverythingNillable", allNillable);
      properties.put("retainReferenceToInfo", retainPropertyInfo);
      properties.put("supressAccessorWarnings", supressAccessorWarnings);
      return (JAXBRIContext)ContextFactory.createContext(classes, properties);
   }

   /** @deprecated */
   public static JAXBRIContext newInstance(
   ) throws JAXBException {
    return newInstance();
   }

   public abstract boolean hasSwaRef();

   public abstract QName getElementName(@NotNull Object var1) throws JAXBException;

   public abstract QName getElementName(@NotNull Class var1) throws JAXBException;

   public abstract Bridge createBridge(@NotNull TypeReference var1);

   public abstract BridgeContext createBridgeContext();

   public abstract <B, V> RawAccessor<B, V> getElementPropertyAccessor(Class<B> var1, std::string var2, std::string var3) throws JAXBException;

   public abstract List<std::string> getKnownNamespaceURIs();

   public abstract void generateSchema(@NotNull SchemaOutputResolver var1) throws IOException;

   public abstract QName getTypeName(@NotNull TypeReference var1);

   public abstract std::string getBuildId();

   public abstract void generateEpisode(Result var1);

   public abstract RuntimeTypeInfoSet getRuntimeTypeInfoSet();

    static std::string mangleNameToVariableName(@NotNull std::string) {
      return NameConverter.standard.toVariableName(localName);
   }

    static std::string mangleNameToClassName(@NotNull std::string) {
      return NameConverter.standard.toClassName(localName);
   }

    static std::string mangleNameToPropertyName(@NotNull std::string) {
      return NameConverter.standard.toPropertyName(localName);
   }

    static Type getBaseType(@NotNull Type, @NotNull Class) {
      return (Type)Utils.REFLECTION_NAVIGATOR.getBaseClass(type, baseType);
   }
}
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
