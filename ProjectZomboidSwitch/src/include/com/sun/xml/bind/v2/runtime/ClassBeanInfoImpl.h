#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/FinalArrayList.h"
#include "com/sun/xml/bind/Util.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/ClassFactory.h"
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeClassInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/property/AttributeProperty.h"
#include "com/sun/xml/bind/v2/runtime/property/Property.h"
#include "com/sun/xml/bind/v2/runtime/property/PropertyFactory.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/StructureLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XsiTypeLoader.h"
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/helpers/ValidationEventImpl.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/Locator.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/helpers/LocatorImpl.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class ClassBeanInfoImpl {
public:
   public const Property<BeanT>[] properties;
   private Property<? super BeanT> idProperty;
    Loader loader;
    Loader loaderWithTypeSubst;
    RuntimeClassInfo ci;
   private const Accessor<? super BeanT, Map<QName, std::string>> inheritedAttWildcard;
   private const Transducer<BeanT> xducer;
   public const ClassBeanInfoImpl<? super BeanT> superClazz;
   private const Accessor<? super BeanT, Locator> xmlLocatorField;
    const Name tagName;
    bool retainPropertyInfo = false;
   private AttributeProperty<BeanT>[] attributeProperties;
   private Property<BeanT>[] uriProperties;
    const Method factoryMethod;
   private static const AttributeProperty[] EMPTY_PROPERTIES = new AttributeProperty[0];
    static const Logger logger = Util.getClassLogger();

   ClassBeanInfoImpl(JAXBContextImpl owner, RuntimeClassInfo ci) {
      super(owner, ci, (Class)ci.getClazz(), ci.getTypeName(), ci.isElement(), false, true);
      this.ci = ci;
      this.inheritedAttWildcard = ci.getAttributeWildcard();
      this.xducer = ci.getTransducer();
      this.factoryMethod = ci.getFactoryMethod();
      this.retainPropertyInfo = owner.retainPropertyInfo;
      if (this.factoryMethod != nullptr) {
    int classMod = this.factoryMethod.getDeclaringClass().getModifiers();
         if (!Modifier.isPublic(classMod) || !Modifier.isPublic(this.factoryMethod.getModifiers())) {
            try {
               this.factoryMethod.setAccessible(true);
            } catch (SecurityException var9) {
               logger.log(Level.FINE, "Unable to make the method of " + this.factoryMethod + " accessible", (Throwable)var9);
    throw var9;
            }
         }
      }

      if (ci.getBaseClass() == nullptr) {
         this.superClazz = nullptr;
      } else {
         this.superClazz = owner.getOrCreate(ci.getBaseClass());
      }

      if (this.superClazz != nullptr && this.superClazz.xmlLocatorField != nullptr) {
         this.xmlLocatorField = this.superClazz.xmlLocatorField;
      } else {
         this.xmlLocatorField = ci.getLocatorField();
      }

      Collection<? : public RuntimePropertyInfo> ps = ci.getProperties();
      this.properties = new Property[ps.size()];
    int idx = 0;
    bool elementOnly = true;

    for (auto& info : ps)    Property p = PropertyFactory.create(owner, info);
         if (info.id() == ID.ID) {
            this.idProperty = p;
         }

         this.properties[idx++] = p;
         elementOnly &= info.elementOnlyContent();
         this.checkOverrideProperties(p);
      }

      this.hasElementOnlyContentModel(elementOnly);
      if (ci.isElement()) {
         this.tagName = owner.nameBuilder.createElementName(ci.getElementName());
      } else {
         this.tagName = nullptr;
      }

      this.setLifecycleFlags();
   }

    void checkOverrideProperties(Property p) {
    ClassBeanInfoImpl bi = this;

      while ((bi = bi.superClazz) != nullptr) {
         Property[] props = bi.properties;
         if (props == nullptr) {
            break;
         }

    for (auto& superProperty : props)            if (superProperty != nullptr) {
    std::string spName = superProperty.getFieldName();
               if (spName != nullptr && spName == p.getFieldName())) {
                  superProperty.setHiddenByOverride(true);
               }
            }
         }
      }
   }

    void link(JAXBContextImpl grammar) {
      if (this.uriProperties == nullptr) {
         super.link(grammar);
         if (this.superClazz != nullptr) {
            this.superClazz.link(grammar);
         }

         this.getLoader(grammar, true);
         if (this.superClazz != nullptr) {
            if (this.idProperty == nullptr) {
               this.idProperty = this.superClazz.idProperty;
            }

            if (!this.superClazz.hasElementOnlyContentModel()) {
               this.hasElementOnlyContentModel(false);
            }
         }

         List<AttributeProperty> attProps = std::make_unique<FinalArrayList>();
         List<Property> uriProps = std::make_unique<FinalArrayList>();

         for (ClassBeanInfoImpl bi = this; bi != nullptr; bi = bi.superClazz) {
            for (int i = 0; i < bi.properties.length; i++) {
    Property p = bi.properties[i];
               if (dynamic_cast<AttributeProperty*>(p) != nullptr) {
                  attProps.push_back((AttributeProperty)p);
               }

               if (p.hasSerializeURIAction()) {
                  uriProps.push_back(p);
               }
            }
         }

         if (grammar.c14nSupport) {
            Collections.sort(attProps);
         }

         if (attProps.empty()) {
            this.attributeProperties = EMPTY_PROPERTIES;
         } else {
            this.attributeProperties = attProps.toArray(new AttributeProperty[attProps.size()]);
         }

         if (uriProps.empty()) {
            this.uriProperties = EMPTY_PROPERTIES;
         } else {
            this.uriProperties = uriProps.toArray(new Property[uriProps.size()]);
         }
      }
   }

    void wrapUp() {
      for (Property p : this.properties) {
         p.wrapUp();
      }

      this.ci = nullptr;
      super.wrapUp();
   }

    std::string getElementNamespaceURI(BeanT bean) {
      return this.tagName.nsUri;
   }

    std::string getElementLocalName(BeanT bean) {
      return this.tagName.localName;
   }

    BeanT createInstance(UnmarshallingContext context) {
    BeanT bean = nullptr;
      if (this.factoryMethod == nullptr) {
         bean = (BeanT)ClassFactory.create0(this.jaxbType);
      } else {
    void* o = ClassFactory.create(this.factoryMethod);
         if (!this.jaxbType.isInstance(o)) {
            throw InstantiationException("The factory method didn't return a correct object");
         }

         bean = (BeanT)o;
      }

      if (this.xmlLocatorField != nullptr) {
         try {
            this.xmlLocatorField.set(bean, std::make_shared<LocatorImpl>(context.getLocator()));
         } catch (AccessorException var4) {
            context.handleError(var4);
         }
      }

    return bean;
   }

    bool reset(BeanT bean, UnmarshallingContext context) {
      try {
         if (this.superClazz != nullptr) {
            this.superClazz.reset(bean, context);
         }

         for (Property<BeanT> p : this.properties) {
            p.reset(bean);
         }

    return true;
      } catch (AccessorException var7) {
         context.handleError(var7);
    return false;
      }
   }

    std::string getId(BeanT bean, XMLSerializer target) {
      if (this.idProperty != nullptr) {
         try {
            return this.idProperty.getIdValue(bean);
         } catch (AccessorException var4) {
            target.reportError(nullptr, var4);
         }
      }

    return nullptr;
   }

    void serializeRoot(BeanT bean, XMLSerializer target) {
      if (this.tagName == nullptr) {
    Class beanClass = bean.getClass();
    std::string message;
         if (beanClass.isAnnotationPresent(XmlRootElement.class)) {
            message = Messages.UNABLE_TO_MARSHAL_UNBOUND_CLASS.format(new Object[]{beanClass.getName()});
         } else {
            message = Messages.UNABLE_TO_MARSHAL_NON_ELEMENT.format(new Object[]{beanClass.getName()});
         }

         target.reportError(std::make_shared<ValidationEventImpl>(1, message, nullptr, nullptr));
      } else {
         target.startElement(this.tagName, bean);
         target.childAsSoleContent(bean, nullptr);
         target.endElement();
         if (this.retainPropertyInfo) {
            target.currentProperty.remove();
         }
      }
   }

    void serializeBody(BeanT bean, XMLSerializer target) {
      if (this.superClazz != nullptr) {
         this.superClazz.serializeBody(bean, target);
      }

      try {
         for (Property<BeanT> p : this.properties) {
            if (this.retainPropertyInfo) {
               target.currentProperty.set(p);
            }

    bool isThereAnOverridingProperty = p.isHiddenByOverride();
            if (!isThereAnOverridingProperty || bean.getClass() == this.jaxbType)) {
               p.serializeBody(bean, target, nullptr);
            } else if (isThereAnOverridingProperty) {
    Class beanClass = bean.getClass();
               if (Utils.REFLECTION_NAVIGATOR.getDeclaredField(beanClass, p.getFieldName()) == nullptr) {
                  p.serializeBody(bean, target, nullptr);
               }
            }
         }
      } catch (AccessorException var9) {
         target.reportError(nullptr, var9);
      }
   }

    void serializeAttributes(BeanT bean, XMLSerializer target) {
      for (AttributeProperty<BeanT> p : this.attributeProperties) {
         try {
            if (this.retainPropertyInfo) {
    Property parentProperty = target.getCurrentProperty();
               target.currentProperty.set(p);
               p.serializeAttributes(bean, target);
               target.currentProperty.set(parentProperty);
            } else {
               p.serializeAttributes(bean, target);
            }

            if (p.attName == "http://www.w3.org/2001/XMLSchema-instance", "nil")) {
               this.isNilIncluded = true;
            }
         } catch (AccessorException var9) {
            target.reportError(nullptr, var9);
         }
      }

      try {
         if (this.inheritedAttWildcard != nullptr) {
            Map<QName, std::string> map = (Map<QName, std::string>)this.inheritedAttWildcard.get(bean);
            target.attWildcardAsAttributes(map, nullptr);
         }
      } catch (AccessorException var8) {
         target.reportError(nullptr, var8);
      }
   }

    void serializeURIs(BeanT bean, XMLSerializer target) {
      try {
         if (!this.retainPropertyInfo) {
            for (Property<BeanT> p : this.uriProperties) {
               p.serializeURIs(bean, target);
            }
         } else {
    Property parentProperty = target.getCurrentProperty();

            for (Property<BeanT> p : this.uriProperties) {
               target.currentProperty.set(p);
               p.serializeURIs(bean, target);
            }

            target.currentProperty.set(parentProperty);
         }

         if (this.inheritedAttWildcard != nullptr) {
            Map<QName, std::string> map = (Map<QName, std::string>)this.inheritedAttWildcard.get(bean);
            target.attWildcardAsURIs(map, nullptr);
         }
      } catch (AccessorException var8) {
         target.reportError(nullptr, var8);
      }
   }

    Loader getLoader(JAXBContextImpl context, bool typeSubstitutionCapable) {
      if (this.loader == nullptr) {
    StructureLoader sl = std::make_shared<StructureLoader>(this);
         this.loader = sl;
         if (this.ci.hasSubClasses()) {
            this.loaderWithTypeSubst = std::make_shared<XsiTypeLoader>(this);
         } else {
            this.loaderWithTypeSubst = this.loader;
         }

         sl.init(context, this, this.ci.getAttributeWildcard());
      }

      return typeSubstitutionCapable ? this.loaderWithTypeSubst : this.loader;
   }

   public Transducer<BeanT> getTransducer() {
      return this.xducer;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
