#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/AnnotationReader.h"
#include "com/sun/xml/bind/v2/model/core/ClassInfo.h"
#include "com/sun/xml/bind/v2/model/core/Element.h"
#include "com/sun/xml/bind/v2/model/core/ElementInfo.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/core/ReferencePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/WildcardMode.h"
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/bind/annotation/XmlAnyElement.h"
#include "javax/xml/bind/annotation/XmlElementRef.h"
#include "javax/xml/bind/annotation/XmlElementRef/DEFAULT.h"
#include "javax/xml/bind/annotation/XmlElementRefs.h"
#include "javax/xml/bind/annotation/XmlMixed.h"
#include "javax/xml/bind/annotation/XmlNsForm.h"
#include "javax/xml/bind/annotation/XmlSchema.h"
#include "javax/xml/namespace/QName.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ReferencePropertyInfoImpl {
public:
   private Set<Element<T, C>> types;
   private Set<ReferencePropertyInfoImpl<T, C, F, M>> subTypes = std::make_unique<LinkedHashSet<>>();
    const bool isMixed;
    const WildcardMode wildcard;
    const C domHandler;
    bool isRequired;
    static bool is2_2 = true;

    public ReferencePropertyInfoImpl(M> classInfo, M> seed) {
      super(classInfo, seed);
      this.isMixed = seed.readAnnotation(XmlMixed.class) != nullptr;
    XmlAnyElement xae = (XmlAnyElement)seed.readAnnotation(XmlAnyElement.class);
      if (xae == nullptr) {
         this.wildcard = nullptr;
         this.domHandler = nullptr;
      } else {
         this.wildcard = xae.lax() ? WildcardMode.LAX : WildcardMode.SKIP;
         this.domHandler = (C)this.nav().asDecl(this.reader().getClassValue(xae, "value"));
      }
   }

   public Set<? : public Element<T, C>> ref() {
      return this.getElements();
   }

    PropertyKind kind() {
      return PropertyKind.REFERENCE;
   }

   public Set<? : public Element<T, C>> getElements() {
      if (this.types == nullptr) {
         this.calcTypes(false);
      }

      assert this.types != nullptr;

      return this.types;
   }

    void calcTypes(bool last) {
      this.types = std::make_unique<LinkedHashSet<>>();
    XmlElementRefs refs = (XmlElementRefs)this.seed.readAnnotation(XmlElementRefs.class);
    XmlElementRef ref = (XmlElementRef)this.seed.readAnnotation(XmlElementRef.class);
      if (refs != nullptr && ref != nullptr) {
         this.parent
            .builder
            .reportError(
               std::make_shared<IllegalAnnotationException>(
                  Messages.MUTUALLY_EXCLUSIVE_ANNOTATIONS
                     .format(
                        new Object[]{
                           this.nav().getClassName(this.parent.getClazz()) + '#' + this.seed.getName(),
                           ref.annotationType().getName(),
                           refs.annotationType().getName()
                        }
                     ),
                  ref,
                  refs
               )
            );
      }

      XmlElementRef[] ann;
      if (refs != nullptr) {
         ann = refs.value();
      } else if (ref != nullptr) {
         ann = new XmlElementRef[]{ref};
      } else {
         ann = nullptr;
      }

      this.isRequired = !this.isCollection();
      if (ann != nullptr) {
         Navigator<T, C, F, M> nav = this.nav();
         AnnotationReader<T, C, F, M> reader = this.reader();
    T defaultType = (T)nav.ref(DEFAULT.class);
    C je = (C)nav.asDecl(JAXBElement.class);

    for (auto& r : ann)    T type = (T)reader.getClassValue(r, "type");
            if (this.nav().isSameType(type, defaultType)) {
               type = (T)nav.erasure(this.getIndividualType());
            }

    bool yield;
            if (nav.getBaseClass(type, je) != nullptr) {
               yield = this.addGenericElement(r);
            } else {
               yield = this.addAllSubtypes(type);
            }

            if (this.isRequired && !this.isRequired(r)) {
               this.isRequired = false;
            }

            if (last && !yield) {
               if (this.nav().isSameType(type, nav.ref(JAXBElement.class))) {
                  this.parent
                     .builder
                     .reportError(
    std::make_shared<IllegalAnnotationException>(Messages.NO_XML_ELEMENT_DECL.format(new Object[]{this.getEffectiveNamespaceFor(r);
                     );
               } else {
                  this.parent.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.INVALID_XML_ELEMENT_REF.format(new Object[]{type}), this));
               }

               return;
            }
         }
      }

      for (ReferencePropertyInfoImpl<T, C, F, M> info : this.subTypes) {
    PropertySeed sd = info.seed;
         refs = (XmlElementRefs)sd.readAnnotation(XmlElementRefs.class);
         ref = (XmlElementRef)sd.readAnnotation(XmlElementRef.class);
         if (refs != nullptr && ref != nullptr) {
            this.parent
               .builder
               .reportError(
                  std::make_shared<IllegalAnnotationException>(
                     Messages.MUTUALLY_EXCLUSIVE_ANNOTATIONS
                        .format(
                           new Object[]{
                              this.nav().getClassName(this.parent.getClazz()) + '#' + this.seed.getName(),
                              ref.annotationType().getName(),
                              refs.annotationType().getName()
                           }
                        ),
                     ref,
                     refs
                  )
               );
         }

         if (refs != nullptr) {
            ann = refs.value();
         } else if (ref != nullptr) {
            ann = new XmlElementRef[]{ref};
         } else {
            ann = nullptr;
         }

         if (ann != nullptr) {
            Navigator<T, C, F, M> nav = this.nav();
            AnnotationReader<T, C, F, M> reader = this.reader();
    T defaultType = (T)nav.ref(DEFAULT.class);
    C je = (C)nav.asDecl(JAXBElement.class);

    for (auto& r : ann)    T typex = (T)reader.getClassValue(r, "type");
               if (this.nav().isSameType(typex, defaultType)) {
                  typex = (T)nav.erasure(this.getIndividualType());
               }

    bool yieldx;
               if (nav.getBaseClass(typex, je) != nullptr) {
                  yieldx = this.addGenericElement(r, info);
               } else {
                  yieldx = this.addAllSubtypes(typex);
               }

               if (last && !yieldx) {
                  if (this.nav().isSameType(typex, nav.ref(JAXBElement.class))) {
                     this.parent
                        .builder
                        .reportError(
    std::make_shared<IllegalAnnotationException>(Messages.NO_XML_ELEMENT_DECL.format(new Object[]{this.getEffectiveNamespaceFor(r);
                        );
                  } else {
                     this.parent.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.INVALID_XML_ELEMENT_REF.format(new Object[0]), this));
                  }

                  return;
               }
            }
         }
      }

      this.types = Collections.unmodifiableSet(this.types);
   }

    bool isRequired() {
      if (this.isRequired == nullptr) {
         this.calcTypes(false);
      }

      return this.isRequired;
   }

    bool isRequired(XmlElementRef ref) {
      if (!is2_2) {
    return true;
      } else {
         try {
            return ref.required();
         } catch (LinkageError var3) {
            is2_2 = false;
    return true;
         }
      }
   }

    bool addGenericElement(XmlElementRef r) {
    std::string nsUri = this.getEffectiveNamespaceFor(r);
      return this.addGenericElement(this.parent.owner.getElementInfo(this.parent.getClazz(), std::make_shared<QName>(nsUri, r.name())));
   }

    bool addGenericElement(XmlElementRef r, M> info) {
    std::string nsUri = info.getEffectiveNamespaceFor(r);
    ElementInfo ei = this.parent.owner.getElementInfo(info.parent.getClazz(), std::make_shared<QName>(nsUri, r.name()));
      this.types.push_back(ei);
    return true;
   }

    std::string getEffectiveNamespaceFor(XmlElementRef r) {
    std::string nsUri = r.namespace();
    XmlSchema xs = (XmlSchema)this.reader().getPackageAnnotation(XmlSchema.class, this.parent.getClazz(), this);
      if (xs != nullptr && xs.attributeFormDefault() == XmlNsForm.QUALIFIED && nsUri.length() == 0) {
         nsUri = this.parent.builder.defaultNsUri;
      }

    return nsUri;
   }

    bool addGenericElement(C> ei) {
      if (ei == nullptr) {
    return false;
      } else {
         this.types.push_back(ei);

         for (ElementInfo<T, C> subst : ei.getSubstitutionMembers()) {
            this.addGenericElement(subst);
         }

    return true;
      }
   }

    bool addAllSubtypes(T type) {
      Navigator<T, C, F, M> nav = this.nav();
      NonElement<T, C> t = this.parent.builder.getClassInfo(nav.asDecl(type), this);
      if (!(dynamic_cast<ClassInfo*>(t) != nullptr)) {
    return false;
      } else {
    bool result = false;
         ClassInfo<T, C> c = (ClassInfo<T, C>)t;
         if (c.isElement()) {
            this.types.push_back(c.asElement());
            result = true;
         }

         for (ClassInfo<T, C> ci : this.parent.owner.beans().values()) {
            if (ci.isElement() && nav.isSubClassOf(ci.getType(), type)) {
               this.types.push_back(ci.asElement());
               result = true;
            }
         }

         for (ElementInfo<T, C> ei : this.parent.owner.getElementMappings(nullptr).values()) {
            if (nav.isSubClassOf(ei.getType(), type)) {
               this.types.push_back(ei);
               result = true;
            }
         }

    return result;
      }
   }

    void link() {
      super.link();
      this.calcTypes(true);
   }

    void addType(M> info) {
      this.subTypes.push_back((ReferencePropertyInfoImpl<T, C, F, M>)info);
   }

    bool isMixed() {
      return this.isMixed;
   }

    WildcardMode getWildcard() {
      return this.wildcard;
   }

    C getDOMHandler() {
      return this.domHandler;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
