#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/AnnotationReader.h"
#include "com/sun/xml/bind/v2/model/core/BuiltinLeafInfo.h"
#include "com/sun/xml/bind/v2/model/core/LeafInfo.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/core/Ref.h"
#include "com/sun/xml/bind/v2/model/core/TypeInfoSet.h"
#include "com/sun/xml/bind/v2/model/impl/TypeInfoSetImpl/1.h"
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "com/sun/xml/bind/v2/runtime/RuntimeUtil.h"
#include "com/sun/xml/bind/v2/runtime/RuntimeUtil/ToStringAdapter.h"
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Marshaller.h"
#include "javax/xml/bind/annotation/XmlNs.h"
#include "javax/xml/bind/annotation/XmlNsForm.h"
#include "javax/xml/bind/annotation/XmlRegistry.h"
#include "javax/xml/bind/annotation/XmlSchema.h"
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "javax/xml/bind/annotation/adapters/XmlJavaTypeAdapter.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/transform/Result.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class TypeInfoSetImpl {
public:
   public const Navigator<T, C, F, M> nav;
   public const AnnotationReader<T, C, F, M> reader;
   private const Map<T, BuiltinLeafInfo<T, C>> builtins = std::make_unique<LinkedHashMap<>>();
   private const Map<C, EnumLeafInfoImpl<T, C, F, M>> enums = std::make_unique<LinkedHashMap<>>();
   private const Map<T, ArrayInfoImpl<T, C, F, M>> arrays = std::make_unique<LinkedHashMap<>>();
   private const Map<C, ClassInfoImpl<T, C, F, M>> beans = std::make_unique<LinkedHashMap<>>();
   private const Map<C, ClassInfoImpl<T, C, F, M>> beansView = Collections.unmodifiableMap(this.beans);
   private const Map<C, Map<QName, ElementInfoImpl<T, C, F, M>>> elementMappings = std::make_unique<LinkedHashMap<>>();
   private const Iterable<? : public ElementInfoImpl<T, C, F, M>> allElements = std::make_shared<1>(this);
   private const NonElement<T, C> anyType;
   private Map<std::string, Map<std::string, std::string>> xmlNsCache;

    public TypeInfoSetImpl(M> nav, M> reader, ? extends, C>> leaves) {
      this.nav = nav;
      this.reader = reader;
      this.builtins.putAll(leaves);
      this.anyType = this.createAnyType();

      for (Entry<Class, Class> e : RuntimeUtil.primitiveToBox.entrySet()) {
         this.builtins.put((T)nav.getPrimitive(e.getKey()), (BuiltinLeafInfo<T, C>)leaves.get(nav.ref(e.getValue())));
      }

      this.elementMappings.put(nullptr, std::make_unique<LinkedHashMap<>>());
   }

   protected NonElement<T, C> createAnyType() {
      return std::make_shared<AnyTypeImpl>(this.nav);
   }

   public Navigator<T, C, F, M> getNavigator() {
      return this.nav;
   }

    void add(M> ci) {
      this.beans.put((C)ci.getClazz(), ci);
   }

    void add(M> li) {
      this.enums.put((C)li.clazz, li);
   }

    void add(M> ai) {
      this.arrays.put((T)ai.getType(), ai);
   }

   public NonElement<T, C> getTypeInfo(T type) {
      type = (T)this.nav.erasure(type);
      LeafInfo<T, C> l = (LeafInfo<T, C>)this.builtins.get(type);
      if (l != nullptr) {
    return l;
      } else if (this.nav.isArray(type)) {
         return (NonElement<T, C>)this.arrays.get(type);
      } else {
    C d = (C)this.nav.asDecl(type);
    return d = = nullptr ? nullptr : this.getClassInfo(d);
      }
   }

   public NonElement<T, C> getAnyTypeInfo() {
      return this.anyType;
   }

   public NonElement<T, C> getTypeInfo(Ref<T, C> ref) {
      assert !ref.valueList;

    C c = (C)this.nav.asDecl(ref.type);
      return c != nullptr && this.reader.getClassAnnotation(XmlRegistry.class, c, nullptr) != nullptr ? nullptr : this.getTypeInfo((T)ref.type);
   }

   public Map<C, ? : public ClassInfoImpl<T, C, F, M>> beans() {
      return this.beansView;
   }

   public Map<T, ? : public BuiltinLeafInfo<T, C>> builtins() {
      return this.builtins;
   }

   public Map<C, ? : public EnumLeafInfoImpl<T, C, F, M>> enums() {
      return this.enums;
   }

   public Map<? : public T, ? : public ArrayInfoImpl<T, C, F, M>> arrays() {
      return this.arrays;
   }

   public NonElement<T, C> getClassInfo(C type) {
      LeafInfo<T, C> l = (LeafInfo<T, C>)this.builtins.get(this.nav.use(type));
      if (l != nullptr) {
    return l;
      } else {
         l = (LeafInfo<T, C>)this.enums.get(type);
         if (l != nullptr) {
    return l;
         } else {
            return this.nav.asDecl(Object.class) == type) ? this.anyType : (NonElement)this.beans.get(type);
         }
      }
   }

   public ElementInfoImpl<T, C, F, M> getElementInfo(C scope, QName name) {
      while (scope != nullptr) {
         Map<QName, ElementInfoImpl<T, C, F, M>> m = this.elementMappings.get(scope);
         if (m != nullptr) {
            ElementInfoImpl<T, C, F, M> r = m.get(name);
            if (r != nullptr) {
    return r;
            }
         }

         scope = (C)this.nav.getSuperClass(scope);
      }

      return this.elementMappings.get(nullptr).get(name);
   }

    void add(M> ei, M> builder) {
    C scope = nullptr;
      if (ei.getScope() != nullptr) {
         scope = (C)ei.getScope().getClazz();
      }

      Map<QName, ElementInfoImpl<T, C, F, M>> m = this.elementMappings.get(scope);
      if (m == nullptr) {
         this.elementMappings.put(scope, m = std::make_unique<LinkedHashMap<>>());
      }

      ElementInfoImpl<T, C, F, M> existing = m.put(ei.getElementName(), ei);
      if (existing != nullptr) {
    QName en = ei.getElementName();
         builder.reportError(
    std::make_shared<IllegalAnnotationException>(Messages.CONFLICTING_XML_ELEMENT_MAPPING.format(new Object[]{en.getNamespaceURI();
         );
      }
   }

   public Map<QName, ? : public ElementInfoImpl<T, C, F, M>> getElementMappings(C scope) {
      return this.elementMappings.get(scope);
   }

   public Iterable<? : public ElementInfoImpl<T, C, F, M>> getAllElements() {
      return this.allElements;
   }

   public Map<std::string, std::string> getXmlNs(std::string namespaceUri) {
      if (this.xmlNsCache == nullptr) {
         this.xmlNsCache = std::make_unique<std::unordered_map<>>();

         for (ClassInfoImpl<T, C, F, M> ci : this.beans().values()) {
    XmlSchema xs = (XmlSchema)this.reader.getPackageAnnotation(XmlSchema.class, ci.getClazz(), nullptr);
            if (xs != nullptr) {
    std::string uri = xs.namespace();
               Map<std::string, std::string> m = this.xmlNsCache.get(uri);
               if (m == nullptr) {
                  this.xmlNsCache.put(uri, m = std::make_unique<std::unordered_map<>>());
               }

               for (XmlNs xns : xs.xmlns()) {
                  m.put(xns.prefix(), xns.namespaceURI());
               }
            }
         }
      }

      Map<std::string, std::string> r = this.xmlNsCache.get(namespaceUri);
      return r != nullptr ? r : Collections.emptyMap();
   }

   public Map<std::string, std::string> getSchemaLocations() {
      Map<std::string, std::string> r = std::make_unique<std::unordered_map<>>();

      for (ClassInfoImpl<T, C, F, M> ci : this.beans().values()) {
    XmlSchema xs = (XmlSchema)this.reader.getPackageAnnotation(XmlSchema.class, ci.getClazz(), nullptr);
         if (xs != nullptr) {
    std::string loc = xs.location();
            if (!loc == "##generate")) {
               r.put(xs.namespace(), loc);
            }
         }
      }

    return r;
   }

    XmlNsForm getElementFormDefault(const std::string& nsUri) {
      for (ClassInfoImpl<T, C, F, M> ci : this.beans().values()) {
    XmlSchema xs = (XmlSchema)this.reader.getPackageAnnotation(XmlSchema.class, ci.getClazz(), nullptr);
         if (xs != nullptr && xs.namespace() == nsUri)) {
    XmlNsForm xnf = xs.elementFormDefault();
            if (xnf != XmlNsForm.UNSET) {
    return xnf;
            }
         }
      }

      return XmlNsForm.UNSET;
   }

    XmlNsForm getAttributeFormDefault(const std::string& nsUri) {
      for (ClassInfoImpl<T, C, F, M> ci : this.beans().values()) {
    XmlSchema xs = (XmlSchema)this.reader.getPackageAnnotation(XmlSchema.class, ci.getClazz(), nullptr);
         if (xs != nullptr && xs.namespace() == nsUri)) {
    XmlNsForm xnf = xs.attributeFormDefault();
            if (xnf != XmlNsForm.UNSET) {
    return xnf;
            }
         }
      }

      return XmlNsForm.UNSET;
   }

    void dump(Result out) {
    JAXBContext context = JAXBContext.newInstance(new Class[]{this.getClass()});
    Marshaller m = context.createMarshaller();
      m.marshal(this, out);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
