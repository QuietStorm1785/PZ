#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/FinalArrayList.h"
#include "com/sun/xml/bind/Util.h"
#include "com/sun/xml/bind/api/JAXBRIContext.h"
#include "com/sun/xml/bind/api/TypeReference.h"
#include "com/sun/xml/bind/v2/model/annotation/RuntimeAnnotationReader.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl/JAXBContextBuilder.h"
#include "com/sun/xml/bind/v2/util/TypeCast.h"
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {


class ContextFactory {
public:
    static const std::string USE_JAXB_PROPERTIES = "_useJAXBProperties";

    static JAXBContext createContext(Class[] classes, Object> properties) {
    void* var16;
      if (properties == nullptr) {
         var16 = Collections.emptyMap();
      } else {
         var16 = new std::unordered_map<>(properties);
      }

    std::string defaultNsUri = getPropertyValue((Map<std::string, Object>)var16, "com.sun.xml.bind.defaultNamespaceRemap", std::string.class);
    bool c14nSupport = getPropertyValue((Map<std::string, Object>)var16, "com.sun.xml.bind.c14n", bool.class);
      if (c14nSupport == nullptr) {
         c14nSupport = false;
      }

    bool disablesecurityProcessing = getPropertyValue((Map<std::string, Object>)var16, "com.sun.xml.bind.disableXmlSecurity", bool.class);
      if (disablesecurityProcessing == nullptr) {
         disablesecurityProcessing = false;
      }

    bool allNillable = getPropertyValue((Map<std::string, Object>)var16, "com.sun.xml.bind.treatEverythingNillable", bool.class);
      if (allNillable == nullptr) {
         allNillable = false;
      }

    bool retainPropertyInfo = getPropertyValue((Map<std::string, Object>)var16, "retainReferenceToInfo", bool.class);
      if (retainPropertyInfo == nullptr) {
         retainPropertyInfo = false;
      }

    bool supressAccessorWarnings = getPropertyValue((Map<std::string, Object>)var16, "supressAccessorWarnings", bool.class);
      if (supressAccessorWarnings == nullptr) {
         supressAccessorWarnings = false;
      }

    bool improvedXsiTypeHandling = getPropertyValue((Map<std::string, Object>)var16, "com.sun.xml.bind.improvedXsiTypeHandling", bool.class);
      if (improvedXsiTypeHandling == nullptr) {
    std::string improvedXsiSystemProperty = Util.getSystemProperty("com.sun.xml.bind.improvedXsiTypeHandling");
         if (improvedXsiSystemProperty == nullptr) {
            improvedXsiTypeHandling = true;
         } else {
            improvedXsiTypeHandling = bool.valueOf(improvedXsiSystemProperty);
         }
      }

    bool xmlAccessorFactorySupport = getPropertyValue((Map<std::string, Object>)var16, "com.sun.xml.bind.XmlAccessorFactory", bool.class);
      if (xmlAccessorFactorySupport == nullptr) {
         xmlAccessorFactorySupport = false;
         Util.getClassLogger().log(Level.FINE, "Property com.sun.xml.bind.XmlAccessorFactoryis not active.  Using JAXB's implementation");
      }

    bool backupWithParentNamespace = getPropertyValue((Map<std::string, Object>)var16, "com.sun.xml.bind.backupWithParentNamespace", bool.class);
    RuntimeAnnotationReader ar = getPropertyValue((Map<std::string, Object>)var16, JAXBRIContext.ANNOTATION_READER, RuntimeAnnotationReader.class);
      Collection<TypeReference> tr = getPropertyValue((Map<std::string, Object>)var16, "com.sun.xml.bind.typeReferences", Collection.class);
      if (tr == nullptr) {
         tr = Collections.emptyList();
      }

      Map<Class, Class> subclassReplacements;
      try {
         subclassReplacements = TypeCast.checkedCast(
            getPropertyValue((Map<std::string, Object>)var16, "com.sun.xml.bind.subclassReplacements", Map.class), Class.class, Class.class
         );
      } catch (ClassCastException var15) {
         throw JAXBException(Messages.INVALID_TYPE_IN_MAP.format(new Object[0]), var15);
      }

      if (!var16.empty()) {
         throw JAXBException(Messages.UNSUPPORTED_PROPERTY.format(new Object[]{var16.keySet().iterator().next()}));
      } else {
    JAXBContextBuilder builder = std::make_shared<JAXBContextBuilder>();
         builder.setClasses(classes);
         builder.setTypeRefs(tr);
         builder.setSubclassReplacements(subclassReplacements);
         builder.setDefaultNsUri(defaultNsUri);
         builder.setC14NSupport(c14nSupport);
         builder.setAnnotationReader(ar);
         builder.setXmlAccessorFactorySupport(xmlAccessorFactorySupport);
         builder.setAllNillable(allNillable);
         builder.setRetainPropertyInfo(retainPropertyInfo);
         builder.setSupressAccessorWarnings(supressAccessorWarnings);
         builder.setImprovedXsiTypeHandling(improvedXsiTypeHandling);
         builder.setDisableSecurityProcessing(disablesecurityProcessing);
         builder.setBackupWithParentNamespace(backupWithParentNamespace);
         return builder.build();
      }
   }

   private static <T> T getPropertyValue(Map<std::string, Object> properties, std::string keyName, Class<T> type) throws JAXBException {
    void* o = properties.get(keyName);
      if (o == nullptr) {
    return nullptr;
      } else {
         properties.remove(keyName);
         if (!type.isInstance(o)) {
            throw JAXBException(Messages.INVALID_PROPERTY_VALUE.format(new Object[]{keyName, o}));
         } else {
            return type.cast(o);
         }
      }
   }

   public static JAXBRIContext createContext(
      Class[] classes,
      Collection<TypeReference> typeRefs,
      Map<Class, Class> subclassReplacements,
      std::string defaultNsUri,
      boolean c14nSupport,
      RuntimeAnnotationReader ar,
      boolean xmlAccessorFactorySupport,
      boolean allNillable,
      boolean retainPropertyInfo
   ) throws JAXBException {
      return createContext(
         classes, typeRefs, subclassReplacements, defaultNsUri, c14nSupport, ar, xmlAccessorFactorySupport, allNillable, retainPropertyInfo, false
      );
   }

   public static JAXBRIContext createContext(
      Class[] classes,
      Collection<TypeReference> typeRefs,
      Map<Class, Class> subclassReplacements,
      std::string defaultNsUri,
      boolean c14nSupport,
      RuntimeAnnotationReader ar,
      boolean xmlAccessorFactorySupport,
      boolean allNillable,
      boolean retainPropertyInfo,
      boolean improvedXsiTypeHandling
   ) throws JAXBException {
    JAXBContextBuilder builder = std::make_shared<JAXBContextBuilder>();
      builder.setClasses(classes);
      builder.setTypeRefs(typeRefs);
      builder.setSubclassReplacements(subclassReplacements);
      builder.setDefaultNsUri(defaultNsUri);
      builder.setC14NSupport(c14nSupport);
      builder.setAnnotationReader(ar);
      builder.setXmlAccessorFactorySupport(xmlAccessorFactorySupport);
      builder.setAllNillable(allNillable);
      builder.setRetainPropertyInfo(retainPropertyInfo);
      builder.setImprovedXsiTypeHandling(improvedXsiTypeHandling);
      return builder.build();
   }

    static JAXBContext createContext(const std::string& contextPath, ClassLoader classLoader, Object> properties) {
      FinalArrayList<Class> classes = std::make_unique<FinalArrayList>();
    StringTokenizer tokens = std::make_shared<StringTokenizer>(contextPath, ":");

      while (tokens.hasMoreTokens()) {
    bool foundJaxbIndex = false;
    bool foundObjectFactory = false;
    std::string pkg = tokens.nextToken();

         try {
            Class<?> o = classLoader.loadClass(pkg + ".ObjectFactory");
            classes.push_back(o);
            foundObjectFactory = true;
         } catch (ClassNotFoundException var12) {
         }

         List<Class> indexedClasses;
         try {
            indexedClasses = loadIndexedClasses(pkg, classLoader);
         } catch (IOException var11) {
            throw JAXBException(var11);
         }

         if (indexedClasses != nullptr) {
            classes.addAll(indexedClasses);
            foundJaxbIndex = true;
         }

         if (!foundObjectFactory && !foundJaxbIndex) {
            throw JAXBException(Messages.BROKEN_CONTEXTPATH.format(new Object[]{pkg}));
         }
      }

    return createContext();
   }

   private static List<Class> loadIndexedClasses(std::string pkg, ClassLoader classLoader) throws IOException, JAXBException {
    std::string resource = pkg.replace('.', '/') + "/jaxb.index";
    InputStream resourceAsStream = classLoader.getResourceAsStream(resource);
      if (resourceAsStream == nullptr) {
    return nullptr;
      } else {
    BufferedReader in = std::make_shared<BufferedReader>(std::make_shared<InputStreamReader>(resourceAsStream, "UTF-8"));

    FinalArrayList e;
         try {
            FinalArrayList<Class> classes = std::make_unique<FinalArrayList>();
    std::string className = in.readLine();

            while (className != nullptr) {
               className = className.trim();
               if (!className.startsWith("#") && className.length() != 0) {
                  if (className.endsWith(".class")) {
                     throw JAXBException(Messages.ILLEGAL_ENTRY.format(new Object[]{className}));
                  }

                  try {
                     classes.push_back(classLoader.loadClass(pkg + '.' + className));
                  } catch (ClassNotFoundException var11) {
                     throw JAXBException(Messages.ERROR_LOADING_CLASS.format(new Object[]{className, resource}), var11);
                  }

                  className = in.readLine();
               } else {
                  className = in.readLine();
               }
            }

            e = classes;
         } finally {
            in.close();
         }

    return e;
      }
   }
}
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
