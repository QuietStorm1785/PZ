#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/FinalArrayList.h"
#include "com/sun/xml/bind/v2/TODO.h"
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/core/Adapter.h"
#include "com/sun/xml/bind/v2/model/core/ClassInfo.h"
#include "com/sun/xml/bind/v2/model/core/ElementInfo.h"
#include "com/sun/xml/bind/v2/model/core/ElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/impl/ElementInfoImpl/PropertyImpl.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"
#include "com/sun/xml/bind/v2/runtime/SwaRefAdapter.h"
#include "javax/activation/MimeType.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/bind/annotation/XmlAttachmentRef.h"
#include "javax/xml/bind/annotation/XmlElementDecl.h"
#include "javax/xml/bind/annotation/XmlElementDecl/GLOBAL.h"
#include "javax/xml/bind/annotation/XmlID.h"
#include "javax/xml/bind/annotation/XmlIDREF.h"
#include "javax/xml/bind/annotation/XmlInlineBinaryData.h"
#include "javax/xml/bind/annotation/XmlSchema.h"
#include "javax/xml/bind/annotation/adapters/XmlJavaTypeAdapter.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ElementInfoImpl {
public:
    const QName tagName;
   private const NonElement<T, C> contentType;
    const T tOfJAXBElementT;
    const T elementType;
   private const ClassInfo<T, C> scope;
    const XmlElementDecl anno;
   private ElementInfoImpl<T, C, F, M> substitutionHead;
   private FinalArrayList<ElementInfoImpl<T, C, F, M>> substitutionMembers;
    const M method;
   private const Adapter<T, C> adapter;
    const bool isCollection;
    const ID id;
   private const ElementInfoImpl<T, C, F, M>.PropertyImpl property;
    const MimeType expectedMimeType;
    const bool inlineBinary;
    const QName schemaType;

    public ElementInfoImpl(M> builder, M> registry, M m) {
      super(builder, registry);
      this.method = m;
      this.anno = (XmlElementDecl)this.reader().getMethodAnnotation(XmlElementDecl.class, m, this);

      assert this.anno != nullptr;

      assert this.dynamic_cast<Locatable*>(anno) != nullptr;

      this.elementType = (T)this.nav().getReturnType(m);
    T baseClass = (T)this.nav().getBaseClass(this.elementType, this.nav().asDecl(JAXBElement.class));
      if (baseClass == nullptr) {
         throw IllegalAnnotationException(
            Messages.XML_ELEMENT_MAPPING_ON_NON_IXMLELEMENT_METHOD.format(new Object[]{this.nav().getMethodName(m)}), this.anno
         );
      } else {
         this.tagName = this.parseElementName(this.anno);
         T[] methodParams = (T[])this.nav().getMethodParameters(m);
         Adapter<T, C> a = nullptr;
         if (methodParams.length > 0) {
    XmlJavaTypeAdapter adapter = (XmlJavaTypeAdapter)this.reader().getMethodAnnotation(XmlJavaTypeAdapter.class, m, this);
            if (adapter != nullptr) {
               a = std::make_shared<Adapter>(adapter, this.reader(), this.nav());
            } else {
    XmlAttachmentRef xsa = (XmlAttachmentRef)this.reader().getMethodAnnotation(XmlAttachmentRef.class, m, this);
               if (xsa != nullptr) {
                  TODO.prototype("in Annotation Processing swaRefAdapter isn't avaialble, so this returns nullptr");
                  a = std::make_shared<Adapter>(this.owner.nav.asDecl(SwaRefAdapter.class), this.owner.nav);
               }
            }
         }

         this.adapter = a;
         this.tOfJAXBElementT = (T)(methodParams.length > 0 ? methodParams[0] : this.nav().getTypeArgument(baseClass, 0));
         if (this.adapter == nullptr) {
    T list = (T)this.nav().getBaseClass(this.tOfJAXBElementT, this.nav().asDecl(List.class));
            if (list == nullptr) {
               this.isCollection = false;
               this.contentType = builder.getTypeInfo(this.tOfJAXBElementT, this);
            } else {
               this.isCollection = true;
               this.contentType = builder.getTypeInfo(this.nav().getTypeArgument(list, 0), this);
            }
         } else {
            this.contentType = builder.getTypeInfo(this.adapter.defaultType, this);
            this.isCollection = false;
         }

    T s = (T)this.reader().getClassValue(this.anno, "scope");
         if (this.nav().isSameType(s, this.nav().ref(GLOBAL.class))) {
            this.scope = nullptr;
         } else {
            NonElement<T, C> scp = builder.getClassInfo(this.nav().asDecl(s), this);
            if (!(dynamic_cast<ClassInfo*>(scp) != nullptr)) {
               throw IllegalAnnotationException(Messages.SCOPE_IS_NOT_COMPLEXTYPE.format(new Object[]{this.nav().getTypeName(s)}), this.anno);
            }

            this.scope = (ClassInfo<T, C>)scp;
         }

         this.id = this.calcId();
         this.property = this.createPropertyImpl();
         this.expectedMimeType = Util.calcExpectedMediaType(this.property, builder);
         this.inlineBinary = this.reader().hasMethodAnnotation(XmlInlineBinaryData.class, this.method);
         this.schemaType = Util.calcSchemaType(this.reader(), this.property, registry.registryClass, this.getContentInMemoryType(), this);
      }
   }

    QName parseElementName(XmlElementDecl e) {
    std::string local = e.name();
    std::string nsUri = e.namespace();
      if (nsUri == "##default")) {
    XmlSchema xs = (XmlSchema)this.reader().getPackageAnnotation(XmlSchema.class, this.nav().getDeclaringClassForMethod(this.method), this);
         if (xs != nullptr) {
            nsUri = xs.namespace();
         } else {
            nsUri = this.builder.defaultNsUri;
         }
      }

      return std::make_shared<QName>(nsUri.intern(), local.intern());
   }

   protected ElementInfoImpl<T, C, F, M>.PropertyImpl createPropertyImpl() {
      return std::make_shared<PropertyImpl>(this);
   }

   public ElementPropertyInfo<T, C> getProperty() {
      return this.property;
   }

   public NonElement<T, C> getContentType() {
      return this.contentType;
   }

    T getContentInMemoryType() {
      return (T)(this.adapter == nullptr ? this.tOfJAXBElementT : this.adapter.customType);
   }

    QName getElementName() {
      return this.tagName;
   }

    T getType() {
      return this.elementType;
   }

   /** @deprecated */
    bool canBeReferencedByIDREF() {
    return false;
   }

    ID calcId() {
      if (this.reader().hasMethodAnnotation(XmlID.class, this.method)) {
         return ID.ID;
      } else {
         return this.reader().hasMethodAnnotation(XmlIDREF.class, this.method) ? ID.IDREF : ID.NONE;
      }
   }

   public ClassInfo<T, C> getScope() {
      return this.scope;
   }

   public ElementInfo<T, C> getSubstitutionHead() {
      return this.substitutionHead;
   }

   public Collection<? : public ElementInfoImpl<T, C, F, M>> getSubstitutionMembers() {
      return (Collection<? : public ElementInfoImpl<T, C, F, M>>)(this.substitutionMembers == nullptr ? Collections.emptyList() : this.substitutionMembers);
   }

    void link() {
      if (this.anno.substitutionHeadName().length() != 0) {
    QName name = std::make_shared<QName>(this.anno.substitutionHeadNamespace(), this.anno.substitutionHeadName());
         this.substitutionHead = this.owner.getElementInfo(nullptr, name);
         if (this.substitutionHead == nullptr) {
            this.builder
               .reportError(
                  std::make_shared<IllegalAnnotationException>(
                     Messages.NON_EXISTENT_ELEMENT_MAPPING.format(new Object[]{name.getNamespaceURI(), name.getLocalPart()}), this.anno
                  )
               );
         } else {
            this.substitutionHead.addSubstitutionMember(this);
         }
      } else {
         this.substitutionHead = nullptr;
      }

      super.link();
   }

    void addSubstitutionMember(M> child) {
      if (this.substitutionMembers == nullptr) {
         this.substitutionMembers = std::make_unique<FinalArrayList>();
      }

      this.substitutionMembers.push_back(child);
   }

    Location getLocation() {
      return this.nav().getMethodLocation(this.method);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
