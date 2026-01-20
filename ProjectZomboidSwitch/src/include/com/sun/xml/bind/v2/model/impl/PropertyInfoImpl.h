#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/TODO.h"
#include "com/sun/xml/bind/v2/model/annotation/AnnotationReader.h"
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/core/Adapter.h"
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/model/core/PropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/TypeInfo.h"
#include "com/sun/xml/bind/v2/model/impl/PropertyInfoImpl/1.h"
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"
#include "com/sun/xml/bind/v2/runtime/SwaRefAdapter.h"
#include "javax/activation/MimeType.h"
#include "javax/xml/bind/annotation/XmlAttachmentRef.h"
#include "javax/xml/bind/annotation/XmlElement.h"
#include "javax/xml/bind/annotation/XmlElementWrapper.h"
#include "javax/xml/bind/annotation/XmlID.h"
#include "javax/xml/bind/annotation/XmlIDREF.h"
#include "javax/xml/bind/annotation/XmlInlineBinaryData.h"
#include "javax/xml/bind/annotation/XmlMimeType.h"
#include "javax/xml/bind/annotation/XmlSchema.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"
#include "javax/xml/bind/annotation/adapters/XmlJavaTypeAdapter.h"
#include "javax/xml/bind/annotation/adapters/XmlJavaTypeAdapters.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class PropertyInfoImpl {
public:
   protected const PropertySeed<T, C, F, M> seed;
    const bool isCollection;
    const ID id;
    const MimeType expectedMimeType;
    const bool inlineBinary;
    const QName schemaType;
   protected const ClassInfoImpl<T, C, F, M> parent;
   private const Adapter<T, C> adapter;

    protected PropertyInfoImpl(M> parent, M> spi) {
      this.seed = spi;
      this.parent = parent;
      if (parent == nullptr) {
         throw std::make_unique<AssertionError>();
      } else {
    MimeType mt = Util.calcExpectedMediaType(this.seed, parent.builder);
         if (mt != nullptr && !this.kind().canHaveXmlMimeType) {
            parent.builder
               .reportError(
                  std::make_shared<IllegalAnnotationException>(
                     Messages.ILLEGAL_ANNOTATION.format(new Object[]{XmlMimeType.class.getName()}), this.seed.readAnnotation(XmlMimeType.class)
                  )
               );
            mt = nullptr;
         }

         this.expectedMimeType = mt;
         this.inlineBinary = this.seed.hasAnnotation(XmlInlineBinaryData.class);
    T t = (T)this.seed.getRawType();
    XmlJavaTypeAdapter xjta = this.getApplicableAdapter(t);
         if (xjta != nullptr) {
            this.isCollection = false;
            this.adapter = std::make_shared<Adapter>(xjta, this.reader(), this.nav());
         } else {
            this.isCollection = this.nav().isSubClassOf(t, this.nav().ref(Collection.class)) || this.nav().isArrayButNotByteArray(t);
            xjta = this.getApplicableAdapter(this.getIndividualType());
            if (xjta == nullptr) {
    XmlAttachmentRef xsa = (XmlAttachmentRef)this.seed.readAnnotation(XmlAttachmentRef.class);
               if (xsa != nullptr) {
                  parent.builder.hasSwaRef = true;
                  this.adapter = std::make_shared<Adapter>(this.nav().asDecl(SwaRefAdapter.class), this.nav());
               } else {
                  this.adapter = nullptr;
                  xjta = (XmlJavaTypeAdapter)this.seed.readAnnotation(XmlJavaTypeAdapter.class);
                  if (xjta != nullptr) {
    T ad = (T)this.reader().getClassValue(xjta, "value");
                     parent.builder
                        .reportError(
                           std::make_shared<IllegalAnnotationException>(
                              Messages.UNMATCHABLE_ADAPTER.format(new Object[]{this.nav().getTypeName(ad), this.nav().getTypeName(t)}), xjta
                           )
                        );
                  }
               }
            } else {
               this.adapter = std::make_shared<Adapter>(xjta, this.reader(), this.nav());
            }
         }

         this.id = this.calcId();
         this.schemaType = Util.calcSchemaType(this.reader(), this.seed, parent.clazz, this.getIndividualType(), this);
      }
   }

   public ClassInfoImpl<T, C, F, M> parent() {
      return this.parent;
   }

   protected const Navigator<T, C, F, M> nav() {
      return this.parent.nav();
   }

   protected const AnnotationReader<T, C, F, M> reader() {
      return this.parent.reader();
   }

    T getRawType() {
      return (T)this.seed.getRawType();
   }

    T getIndividualType() {
      if (this.adapter != nullptr) {
         return (T)this.adapter.defaultType;
      } else {
    T raw = this.getRawType();
         if (!this.isCollection()) {
    return raw;
         } else if (this.nav().isArrayButNotByteArray(raw)) {
            return (T)this.nav().getComponentType(raw);
         } else {
    T bt = (T)this.nav().getBaseClass(raw, this.nav().asDecl(Collection.class));
            return (T)(this.nav().isParameterizedType(bt) ? this.nav().getTypeArgument(bt, 0) : this.nav().ref(Object.class));
         }
      }
   }

    std::string getName() {
      return this.seed.getName();
   }

    bool isApplicable(XmlJavaTypeAdapter jta, T declaredType) {
      if (jta == nullptr) {
    return false;
      } else {
    T type = (T)this.reader().getClassValue(jta, "type");
         if (this.nav().isSameType(declaredType, type)) {
    return true;
         } else {
    T ad = (T)this.reader().getClassValue(jta, "value");
    T ba = (T)this.nav().getBaseClass(ad, this.nav().asDecl(XmlAdapter.class));
            if (!this.nav().isParameterizedType(ba)) {
    return true;
            } else {
    T inMemType = (T)this.nav().getTypeArgument(ba, 1);
               return this.nav().isSubClassOf(declaredType, inMemType);
            }
         }
      }
   }

    XmlJavaTypeAdapter getApplicableAdapter(T type) {
    XmlJavaTypeAdapter jta = (XmlJavaTypeAdapter)this.seed.readAnnotation(XmlJavaTypeAdapter.class);
      if (jta != nullptr && this.isApplicable(jta, type)) {
    return jta;
      } else {
    XmlJavaTypeAdapters jtas = (XmlJavaTypeAdapters)this.reader().getPackageAnnotation(XmlJavaTypeAdapters.class, this.parent.clazz, this.seed);
         if (jtas != nullptr) {
            for (XmlJavaTypeAdapter xjta : jtas.value()) {
               if (this.isApplicable(xjta, type)) {
    return xjta;
               }
            }
         }

         jta = (XmlJavaTypeAdapter)this.reader().getPackageAnnotation(XmlJavaTypeAdapter.class, this.parent.clazz, this.seed);
         if (this.isApplicable(jta, type)) {
    return jta;
         } else {
    C refType = (C)this.nav().asDecl(type);
            if (refType != nullptr) {
               jta = (XmlJavaTypeAdapter)this.reader().getClassAnnotation(XmlJavaTypeAdapter.class, refType, this.seed);
               if (jta != nullptr && this.isApplicable(jta, type)) {
    return jta;
               }
            }

    return nullptr;
         }
      }
   }

   public Adapter<T, C> getAdapter() {
      return this.adapter;
   }

    std::string displayName() {
      return this.nav().getClassName(this.parent.getClazz()) + '#' + this.getName();
   }

    ID id() {
      return this.id;
   }

    ID calcId() {
      if (this.seed.hasAnnotation(XmlID.class)) {
         if (!this.nav().isSameType(this.getIndividualType(), this.nav().ref(std::string.class))) {
            this.parent.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.ID_MUST_BE_STRING.format(new Object[]{this.getName()}), this.seed));
         }

         return ID.ID;
      } else {
         return this.seed.hasAnnotation(XmlIDREF.class) ? ID.IDREF : ID.NONE;
      }
   }

    MimeType getExpectedMimeType() {
      return this.expectedMimeType;
   }

    bool inlineBinaryData() {
      return this.inlineBinary;
   }

    QName getSchemaType() {
      return this.schemaType;
   }

    bool isCollection() {
      return this.isCollection;
   }

    void link() {
      if (this.id == ID.IDREF) {
         for (TypeInfo<T, C> ti : this.ref()) {
            if (!ti.canBeReferencedByIDREF()) {
               this.parent
                  .builder
                  .reportError(
    std::make_shared<IllegalAnnotationException>(Messages.INVALID_IDREF.format(new Object[]{this.parent.builder.nav.getTypeName(ti.getType();
                  );
            }
         }
      }
   }

    Locatable getUpstream() {
      return this.parent;
   }

    Location getLocation() {
      return this.seed.getLocation();
   }

    QName calcXmlName(XmlElement e) {
      return e != nullptr ? this.calcXmlName(e.namespace(), e.name()) : this.calcXmlName("##default", "##default");
   }

    QName calcXmlName(XmlElementWrapper e) {
      return e != nullptr ? this.calcXmlName(e.namespace(), e.name()) : this.calcXmlName("##default", "##default");
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    QName calcXmlName(const std::string& uri, const std::string& local) {
      TODO.checkSpec();
      if (local.length() == 0 || local == "##default")) {
         local = this.seed.getName();
      }

      if (uri == "##default")) {
    XmlSchema xs = (XmlSchema)this.reader().getPackageAnnotation(XmlSchema.class, this.parent.getClazz(), this);
         if (xs != nullptr) {
            switch (1.$SwitchMap$javax$xml$bind$annotation$XmlNsForm[xs.elementFormDefault().ordinal()]) {
               case 1:
    QName typeName = this.parent.getTypeName();
                  if (typeName != nullptr) {
                     uri = typeName.getNamespaceURI();
                  } else {
                     uri = xs.namespace();
                  }

                  if (uri.length() == 0) {
                     uri = this.parent.builder.defaultNsUri;
                  }
                  break;
               case 2:
               case 3:
                  uri = "";
            }
         } else {
            uri = "";
         }
      }

      return std::make_shared<QName>(uri.intern(), local.intern());
   }

    int compareTo(PropertyInfoImpl that) {
      return this.getName().compareTo(that.getName());
   }

   public const <A : public Annotation> A readAnnotation(Class<A> annotationType) {
      return (A)this.seed.readAnnotation(annotationType);
   }

    bool hasAnnotation(Class<? extends) {
      return this.seed.hasAnnotation(annotationType);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
