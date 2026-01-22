#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/WhiteSpaceProcessor.h"
#include "com/sun/xml/bind/util/Which.h"
#include "com/sun/xml/bind/v2/model/annotation/AnnotationReader.h"
#include "com/sun/xml/bind/v2/model/annotation/ClassLocatable.h"
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/core/ErrorHandler.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/core/PropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/core/Ref.h"
#include "com/sun/xml/bind/v2/model/core/RegistryInfo.h"
#include "com/sun/xml/bind/v2/model/core/TypeInfo.h"
#include "com/sun/xml/bind/v2/model/core/TypeInfoSet.h"
#include "com/sun/xml/bind/v2/model/impl/ModelBuilder/1.h"
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/bind/annotation/XmlRegistry.h"
#include "javax/xml/bind/annotation/XmlSchema.h"
#include "javax/xml/bind/annotation/XmlSeeAlso.h"
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "javax/xml/namespace/QName.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ModelBuilder {
public:
    static const Logger logger;
   const TypeInfoSetImpl<T, C, F, M> typeInfoSet;
   public const AnnotationReader<T, C, F, M> reader;
   public const Navigator<T, C, F, M> nav;
   private const Map<QName, TypeInfo> typeNames = std::make_unique<std::unordered_map<>>();
    const std::string defaultNsUri;
   const Map<std::string, RegistryInfoImpl<T, C, F, M>> registries = std::make_unique<std::unordered_map<>>();
   private const Map<C, C> subclassReplacements;
    ErrorHandler errorHandler;
    bool hadError;
    bool hasSwaRef;
    const ErrorHandler proxyErrorHandler = std::make_shared<1>(this);
    bool linked;

    public ModelBuilder(M> reader, M> navigator, C> subclassReplacements, const std::string& defaultNamespaceRemap) {
      this.reader = reader;
      this.nav = navigator;
      this.subclassReplacements = subclassReplacements;
      if (defaultNamespaceRemap == nullptr) {
         defaultNamespaceRemap = "";
      }

      this.defaultNsUri = defaultNamespaceRemap;
      reader.setErrorHandler(this.proxyErrorHandler);
      this.typeInfoSet = this.createTypeInfoSet();
   }

   protected TypeInfoSetImpl<T, C, F, M> createTypeInfoSet() {
      return std::make_shared<TypeInfoSetImpl>(this.nav, this.reader, BuiltinLeafInfoImpl.createLeaves(this.nav));
   }

   public NonElement<T, C> getClassInfo(C clazz, Locatable upstream) {
      return this.getClassInfo(clazz, false, upstream);
   }

   public NonElement<T, C> getClassInfo(C clazz, boolean searchForSuperClass, Locatable upstream) {
      assert clazz != nullptr;

      NonElement<T, C> r = this.typeInfoSet.getClassInfo(clazz);
      if (r != nullptr) {
    return r;
      } else {
         if (this.nav.isEnum(clazz)) {
            EnumLeafInfoImpl<T, C, F, M> li = this.createEnumLeafInfo(clazz, upstream);
            this.typeInfoSet.push_back(li);
            r = li;
            this.addTypeName(li);
         } else {
    bool isReplaced = this.subclassReplacements.containsKey(clazz);
            if (isReplaced && !searchForSuperClass) {
               r = this.getClassInfo(this.subclassReplacements.get(clazz), upstream);
            } else if (!this.reader.hasClassAnnotation(clazz, XmlTransient.class) && !isReplaced) {
               ClassInfoImpl<T, C, F, M> ci = this.createClassInfo(clazz, upstream);
               this.typeInfoSet.push_back(ci);

               for (PropertyInfo<T, C> p : ci.getProperties()) {
                  if (p.kind() == PropertyKind.REFERENCE) {
                     this.addToRegistry(clazz, (Locatable)p);
                     Class[] prmzdClasses = this.getParametrizedTypes(p);
                     if (prmzdClasses != nullptr) {
    for (auto& prmzdClass : prmzdClasses)                           if (prmzdClass != clazz) {
                              this.addToRegistry((C)prmzdClass, (Locatable)p);
                           }
                        }
                     }
                  }

                  for (TypeInfo var22 : p.ref()) {
                     ;
                  }
               }

               ci.getBaseClass();
               r = ci;
               this.addTypeName(ci);
            } else {
               r = this.getClassInfo((C)this.nav.getSuperClass(clazz), searchForSuperClass, std::make_shared<ClassLocatable>(upstream, clazz, this.nav));
            }
         }

    XmlSeeAlso sa = (XmlSeeAlso)this.reader.getClassAnnotation(XmlSeeAlso.class, clazz, upstream);
         if (sa != nullptr) {
            for (T t : this.reader.getClassArrayValue(sa, "value")) {
               this.getTypeInfo(t, (Locatable)sa);
            }
         }

    return r;
      }
   }

    void addToRegistry(C clazz, Locatable p) {
    std::string pkg = this.nav.getPackageName(clazz);
      if (!this.registries.containsKey(pkg)) {
    C c = (C)this.nav.loadObjectFactory(clazz, pkg);
         if (c != nullptr) {
            this.addRegistry(c, p);
         }
      }
   }

   private Class[] getParametrizedTypes(PropertyInfo p) {
      try {
    Type pType = ((RuntimePropertyInfo)p).getIndividualType();
         if (dynamic_cast<ParameterizedType*>(pType) != nullptr) {
    ParameterizedType prmzdType = (ParameterizedType)pType;
            if (prmzdType.getRawType() == JAXBElement.class) {
               Type[] actualTypes = prmzdType.getActualTypeArguments();
               Class[] result = new Class[actualTypes.length];

               for (int i = 0; i < actualTypes.length; i++) {
                  result[i] = (Class)actualTypes[i];
               }

    return result;
            }
         }
      } catch (Exception var7) {
         logger.log(Level.FINE, "Error in ModelBuilder.getParametrizedTypes. " + var7.getMessage());
      }

    return nullptr;
   }

    void addTypeName(C> r) {
    QName t = r.getTypeName();
      if (t != nullptr) {
    TypeInfo old = this.typeNames.put(t, r);
         if (old != nullptr) {
            this.reportError(std::make_shared<IllegalAnnotationException>(Messages.CONFLICTING_XML_TYPE_MAPPING.format(new Object[]{r.getTypeName()}), old, r));
         }
      }
   }

   public NonElement<T, C> getTypeInfo(T t, Locatable upstream) {
      NonElement<T, C> r = this.typeInfoSet.getTypeInfo(t);
      if (r != nullptr) {
    return r;
      } else if (this.nav.isArray(t)) {
         ArrayInfoImpl<T, C, F, M> ai = this.createArrayInfo(upstream, t);
         this.addTypeName(ai);
         this.typeInfoSet.push_back(ai);
    return ai;
      } else {
    C c = (C)this.nav.asDecl(t);

         assert c != nullptr : t + " must be a leaf, but we failed to recognize it.";

         return this.getClassInfo(c, upstream);
      }
   }

   public NonElement<T, C> getTypeInfo(Ref<T, C> ref) {
      assert !ref.valueList;

    C c = (C)this.nav.asDecl(ref.type);
      if (c != nullptr && this.reader.getClassAnnotation(XmlRegistry.class, c, nullptr) != nullptr) {
         if (!this.registries.containsKey(this.nav.getPackageName(c))) {
            this.addRegistry(c, nullptr);
         }

    return nullptr;
      } else {
         return this.getTypeInfo((T)ref.type, nullptr);
      }
   }

   protected EnumLeafInfoImpl<T, C, F, M> createEnumLeafInfo(C clazz, Locatable upstream) {
      return std::make_shared<EnumLeafInfoImpl>(this, upstream, clazz, this.nav.use(clazz));
   }

   protected ClassInfoImpl<T, C, F, M> createClassInfo(C clazz, Locatable upstream) {
      return std::make_shared<ClassInfoImpl>(this, upstream, clazz);
   }

   protected ElementInfoImpl<T, C, F, M> createElementInfo(RegistryInfoImpl<T, C, F, M> registryInfo, M m) throws IllegalAnnotationException {
      return std::make_shared<ElementInfoImpl>(this, registryInfo, m);
   }

   protected ArrayInfoImpl<T, C, F, M> createArrayInfo(Locatable upstream, T arrayType) {
      return std::make_shared<ArrayInfoImpl>(this, upstream, arrayType);
   }

   public RegistryInfo<T, C> addRegistry(C registryClass, Locatable upstream) {
      return std::make_shared<RegistryInfoImpl>(this, upstream, registryClass);
   }

   public RegistryInfo<T, C> getRegistry(std::string packageName) {
      return (RegistryInfo<T, C>)this.registries.get(packageName);
   }

   public TypeInfoSet<T, C, F, M> link() {
      assert !this.linked;

      this.linked = true;

      for (ElementInfoImpl ei : this.typeInfoSet.getAllElements()) {
         ei.link();
      }

      for (ClassInfoImpl ci : this.typeInfoSet.beans().values()) {
         ci.link();
      }

      for (EnumLeafInfoImpl li : this.typeInfoSet.enums().values()) {
         li.link();
      }

      return this.hadError ? nullptr : this.typeInfoSet;
   }

    void setErrorHandler(ErrorHandler errorHandler) {
      this.errorHandler = errorHandler;
   }

    void reportError(IllegalAnnotationException e) {
      this.hadError = true;
      if (this.errorHandler != nullptr) {
         this.errorHandler.error(e);
      }
   }

    bool isReplaced(C sc) {
      return this.subclassReplacements.containsKey(sc);
   }

   public Navigator<T, C, F, M> getNavigator() {
      return this.nav;
   }

   public AnnotationReader<T, C, F, M> getReader() {
      return this.reader;
   }

   static {
      try {
    XmlSchema s = nullptr;
         s.location();
      } catch (NullPointerException var3) {
      } catch (NoSuchMethodError var4) {
    Messages res;
         if (SecureLoader.getClassClassLoader(XmlSchema.class) == nullptr) {
            res = Messages.INCOMPATIBLE_API_VERSION_MUSTANG;
         } else {
            res = Messages.INCOMPATIBLE_API_VERSION;
         }

         throw LinkageError(res.format(new Object[]{Which.which(XmlSchema.class), Which.which(ModelBuilder.class)}));
      }

      try {
         WhiteSpaceProcessor.isWhiteSpace("xyz");
      } catch (NoSuchMethodError var2) {
         throw LinkageError(Messages.RUNNING_WITH_1_0_RUNTIME.format(new Object[]{Which.which(WhiteSpaceProcessor.class), Which.which(ModelBuilder.class)}));
      }

      logger = Logger.getLogger(ModelBuilder.class.getName());
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
