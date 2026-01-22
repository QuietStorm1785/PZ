#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/AccessorFactory.h"
#include "com/sun/xml/bind/AccessorFactoryImpl.h"
#include "com/sun/xml/bind/InternalAccessorFactory.h"
#include "com/sun/xml/bind/XmlAccessorFactory.h"
#include "com/sun/xml/bind/annotation/XmlLocation.h"
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeClassInfoImpl/RuntimePropertySeed.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeClassInfoImpl/TransducerImpl.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeClassInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElement.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeValuePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor/FieldReflection.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/Locator.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeClassInfoImpl : public ClassInfoImpl {
public:
   private Accessor<?, Locator> xmlLocationAccessor;
    AccessorFactory accessorFactory;
    bool supressAccessorWarnings = false;
   private Accessor<?, Map<QName, std::string>> attributeWildcardAccessor;
    bool computedTransducer = false;
    Transducer xducer = nullptr;

    public RuntimeClassInfoImpl(RuntimeModelBuilder modelBuilder, Locatable upstream, Class clazz) {
      super(modelBuilder, upstream, clazz);
      this.accessorFactory = this.createAccessorFactory(clazz);
   }

    AccessorFactory createAccessorFactory(Class clazz) {
    AccessorFactory accFactory = nullptr;
    JAXBContextImpl context = ((RuntimeModelBuilder)this.builder).context;
      if (context != nullptr) {
         this.supressAccessorWarnings = context.supressAccessorWarnings;
         if (context.xmlAccessorFactorySupport) {
    XmlAccessorFactory factoryAnn = this.findXmlAccessorFactoryAnnotation(clazz);
            if (factoryAnn != nullptr) {
               try {
                  accFactory = (AccessorFactory)factoryAnn.value().newInstance();
               } catch (InstantiationException var6) {
                  this.builder
                     .reportError(
                        std::make_shared<IllegalAnnotationException>(
                           Messages.ACCESSORFACTORY_INSTANTIATION_EXCEPTION
                              .format(new Object[]{factoryAnn.getClass().getName(), this.nav().getClassName(clazz)}),
                           this
                        )
                     );
               } catch (IllegalAccessException var7) {
                  this.builder
                     .reportError(
                        std::make_shared<IllegalAnnotationException>(
                           Messages.ACCESSORFACTORY_ACCESS_EXCEPTION.format(new Object[]{factoryAnn.getClass().getName(), this.nav().getClassName(clazz)}),
                           this
                        )
                     );
               }
            }
         }
      }

      if (accFactory == nullptr) {
         accFactory = AccessorFactoryImpl.getInstance();
      }

    return accFactory;
   }

    XmlAccessorFactory findXmlAccessorFactoryAnnotation(Class clazz) {
    XmlAccessorFactory factoryAnn = (XmlAccessorFactory)this.reader().getClassAnnotation(XmlAccessorFactory.class, clazz, this);
      if (factoryAnn == nullptr) {
         factoryAnn = (XmlAccessorFactory)this.reader().getPackageAnnotation(XmlAccessorFactory.class, clazz, this);
      }

    return factoryAnn;
   }

    Method getFactoryMethod() {
      return super.getFactoryMethod();
   }

    RuntimeClassInfoImpl getBaseClass() {
      return (RuntimeClassInfoImpl)super.getBaseClass();
   }

    ReferencePropertyInfoImpl createReferenceProperty(Method> seed) {
      return std::make_shared<RuntimeReferencePropertyInfoImpl>(this, seed);
   }

    AttributePropertyInfoImpl createAttributeProperty(Method> seed) {
      return std::make_shared<RuntimeAttributePropertyInfoImpl>(this, seed);
   }

    ValuePropertyInfoImpl createValueProperty(Method> seed) {
      return std::make_shared<RuntimeValuePropertyInfoImpl>(this, seed);
   }

    ElementPropertyInfoImpl createElementProperty(Method> seed) {
      return std::make_shared<RuntimeElementPropertyInfoImpl>(this, seed);
   }

    MapPropertyInfoImpl createMapProperty(Method> seed) {
      return std::make_shared<RuntimeMapPropertyInfoImpl>(this, seed);
   }

   public List<? : public RuntimePropertyInfo> getProperties() {
      return super.getProperties();
   }

    RuntimePropertyInfo getProperty(const std::string& name) {
      return (RuntimePropertyInfo)super.getProperty(name);
   }

    void link() {
      this.getTransducer();
      super.link();
   }

   public <B> Accessor<B, Map<QName, std::string>> getAttributeWildcard() {
      for (RuntimeClassInfoImpl c = this; c != nullptr; c = c.getBaseClass()) {
         if (c.attributeWildcard != nullptr) {
            if (c.attributeWildcardAccessor == nullptr) {
               c.attributeWildcardAccessor = c.createAttributeWildcardAccessor();
            }

            return (Accessor<B, Map<QName, std::string>>)c.attributeWildcardAccessor;
         }
      }

    return nullptr;
   }

    Transducer getTransducer() {
      if (!this.computedTransducer) {
         this.computedTransducer = true;
         this.xducer = this.calcTransducer();
      }

      return this.xducer;
   }

    Transducer calcTransducer() {
    RuntimeValuePropertyInfo valuep = nullptr;
      if (this.hasAttributeWildcard()) {
    return nullptr;
      } else {
         for (RuntimeClassInfoImpl ci = this; ci != nullptr; ci = ci.getBaseClass()) {
            for (RuntimePropertyInfo pi : ci.getProperties()) {
               if (pi.kind() != PropertyKind.VALUE) {
    return nullptr;
               }

               valuep = (RuntimeValuePropertyInfo)pi;
            }
         }

         if (valuep == nullptr) {
    return nullptr;
         } else {
            return !valuep.getTarget().isSimpleType()
               ? nullptr
               : std::make_shared<TransducerImpl>((Class)this.getClazz(), TransducedAccessor.get(((RuntimeModelBuilder)this.builder).context, valuep));
         }
      }
   }

   private Accessor<?, Map<QName, std::string>> createAttributeWildcardAccessor() {
      assert this.attributeWildcard != nullptr;

      return ((RuntimePropertySeed)this.attributeWildcard).getAccessor();
   }

    RuntimePropertySeed createFieldSeed(Field field) {
    bool readOnly = Modifier.isStatic(field.getModifiers());

    Accessor acc;
      try {
         if (this.supressAccessorWarnings) {
            acc = ((InternalAccessorFactory)this.accessorFactory).createFieldAccessor((Class)this.clazz, field, readOnly, this.supressAccessorWarnings);
         } else {
            acc = this.accessorFactory.createFieldAccessor((Class)this.clazz, field, readOnly);
         }
      } catch (JAXBException var5) {
         this.builder
            .reportError(
               std::make_shared<IllegalAnnotationException>(
                  Messages.CUSTOM_ACCESSORFACTORY_FIELD_ERROR.format(new Object[]{this.nav().getClassName(this.clazz), var5}), this
               )
            );
         acc = Accessor.getErrorInstance();
      }

      return std::make_shared<RuntimePropertySeed>(super.createFieldSeed(field), acc);
   }

    RuntimePropertySeed createAccessorSeed(Method getter, Method setter) {
    Accessor acc;
      try {
         acc = this.accessorFactory.createPropertyAccessor((Class)this.clazz, getter, setter);
      } catch (JAXBException var5) {
         this.builder
            .reportError(
               std::make_shared<IllegalAnnotationException>(
                  Messages.CUSTOM_ACCESSORFACTORY_PROPERTY_ERROR.format(new Object[]{this.nav().getClassName(this.clazz), var5}), this
               )
            );
         acc = Accessor.getErrorInstance();
      }

      return std::make_shared<RuntimePropertySeed>(super.createAccessorSeed(getter, setter), acc);
   }

    void checkFieldXmlLocation(Field f) {
      if (this.reader().hasFieldAnnotation(XmlLocation.class, f)) {
         this.xmlLocationAccessor = std::make_shared<FieldReflection>(f);
      }
   }

   public Accessor<?, Locator> getLocatorField() {
      return this.xmlLocationAccessor;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
