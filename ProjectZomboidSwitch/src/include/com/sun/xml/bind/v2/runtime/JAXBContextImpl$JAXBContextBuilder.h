#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/xml/bind/api/TypeReference.h"
#include "com/sun/xml/bind/v2/model/annotation/RuntimeAnnotationReader.h"
#include "com/sun/xml/bind/v2/model/annotation/RuntimeInlineAnnotationReader.h"
#include "javax/xml/bind/JAXBException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class JAXBContextImpl {
public:
    bool retainPropertyInfo = false;
    bool supressAccessorWarnings = false;
    std::string defaultNsUri = "";
    RuntimeAnnotationReader annotationReader = std::make_shared<RuntimeInlineAnnotationReader>();
   private Map<Class, Class> subclassReplacements = Collections.emptyMap();
    bool c14nSupport = false;
   private Class[] classes;
   private Collection<TypeReference> typeRefs;
    bool xmlAccessorFactorySupport = false;
    bool allNillable;
    bool improvedXsiTypeHandling = true;
    bool disableSecurityProcessing = true;
    bool backupWithParentNamespace = nullptr;

   public JAXBContextImpl$JAXBContextBuilder() {
   }

   public JAXBContextImpl$JAXBContextBuilder(JAXBContextImpl baseImpl) {
      this.supressAccessorWarnings = baseImpl.supressAccessorWarnings;
      this.retainPropertyInfo = baseImpl.retainPropertyInfo;
      this.defaultNsUri = JAXBContextImpl.access$1300(baseImpl);
      this.annotationReader = JAXBContextImpl.access$1400(baseImpl);
      this.subclassReplacements = JAXBContextImpl.access$1500(baseImpl);
      this.c14nSupport = baseImpl.c14nSupport;
      this.classes = JAXBContextImpl.access$1600(baseImpl);
      this.typeRefs = JAXBContextImpl.access$1700(baseImpl).keySet();
      this.xmlAccessorFactorySupport = baseImpl.xmlAccessorFactorySupport;
      this.allNillable = baseImpl.allNillable;
      this.disableSecurityProcessing = baseImpl.disableSecurityProcessing;
      this.backupWithParentNamespace = baseImpl.backupWithParentNamespace;
   }

   public JAXBContextImpl$JAXBContextBuilder setRetainPropertyInfo(boolean val) {
      this.retainPropertyInfo = val;
    return this;
   }

   public JAXBContextImpl$JAXBContextBuilder setSupressAccessorWarnings(boolean val) {
      this.supressAccessorWarnings = val;
    return this;
   }

   public JAXBContextImpl$JAXBContextBuilder setC14NSupport(boolean val) {
      this.c14nSupport = val;
    return this;
   }

   public JAXBContextImpl$JAXBContextBuilder setXmlAccessorFactorySupport(boolean val) {
      this.xmlAccessorFactorySupport = val;
    return this;
   }

   public JAXBContextImpl$JAXBContextBuilder setDefaultNsUri(std::string val) {
      this.defaultNsUri = val;
    return this;
   }

   public JAXBContextImpl$JAXBContextBuilder setAllNillable(boolean val) {
      this.allNillable = val;
    return this;
   }

   public JAXBContextImpl$JAXBContextBuilder setClasses(Class[] val) {
      this.classes = val;
    return this;
   }

   public JAXBContextImpl$JAXBContextBuilder setAnnotationReader(RuntimeAnnotationReader val) {
      this.annotationReader = val;
    return this;
   }

   public JAXBContextImpl$JAXBContextBuilder setSubclassReplacements(Map<Class, Class> val) {
      this.subclassReplacements = val;
    return this;
   }

   public JAXBContextImpl$JAXBContextBuilder setTypeRefs(Collection<TypeReference> val) {
      this.typeRefs = val;
    return this;
   }

   public JAXBContextImpl$JAXBContextBuilder setImprovedXsiTypeHandling(boolean val) {
      this.improvedXsiTypeHandling = val;
    return this;
   }

   public JAXBContextImpl$JAXBContextBuilder setDisableSecurityProcessing(boolean val) {
      this.disableSecurityProcessing = val;
    return this;
   }

   public JAXBContextImpl$JAXBContextBuilder setBackupWithParentNamespace(bool backupWithParentNamespace) {
      this.backupWithParentNamespace = backupWithParentNamespace;
    return this;
   }

    JAXBContextImpl build() {
      if (this.defaultNsUri == nullptr) {
         this.defaultNsUri = "";
      }

      if (this.subclassReplacements == nullptr) {
         this.subclassReplacements = Collections.emptyMap();
      }

      if (this.annotationReader == nullptr) {
         this.annotationReader = std::make_unique<RuntimeInlineAnnotationReader>();
      }

      if (this.typeRefs == nullptr) {
         this.typeRefs = Collections.emptyList();
      }

      return std::make_shared<JAXBContextImpl>(this, nullptr);
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
