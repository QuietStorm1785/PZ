#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/xml/bind/Util.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeInfo.h"
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo/1.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallerImpl.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "java/security/AccessController.h"
#include "javax/xml/bind/Marshaller.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class JaxBeanInfo {
public:
    bool isNilIncluded = false;
    short flag;
    static const short FLAG_IS_ELEMENT = 1;
    static const short FLAG_IS_IMMUTABLE = 2;
    static const short FLAG_HAS_ELEMENT_ONLY_CONTENTMODEL = 4;
    static const short FLAG_HAS_BEFORE_UNMARSHAL_METHOD = 8;
    static const short FLAG_HAS_AFTER_UNMARSHAL_METHOD = 16;
    static const short FLAG_HAS_BEFORE_MARSHAL_METHOD = 32;
    static const short FLAG_HAS_AFTER_MARSHAL_METHOD = 64;
    static const short FLAG_HAS_LIFECYCLE_EVENTS = 128;
    LifecycleMethods lcm = nullptr;
   public const Class<BeanT> jaxbType;
    const void* typeName;
   private static const Class[] unmarshalEventParams = new Class[]{Unmarshaller.class, Object.class};
   private static Class[] marshalEventParams = new Class[]{Marshaller.class};
    static const Logger logger = Util.getClassLogger();

   protected JaxBeanInfo(
      JAXBContextImpl grammar,
      RuntimeTypeInfo rti,
      Class<BeanT> jaxbType,
      QName[] typeNames,
      boolean isElement,
      boolean isImmutable,
      boolean hasLifecycleEvents
   ) {
      this(grammar, rti, jaxbType, (Object)typeNames, isElement, isImmutable, hasLifecycleEvents);
   }

   protected JaxBeanInfo(
      JAXBContextImpl grammar, RuntimeTypeInfo rti, Class<BeanT> jaxbType, QName typeName, boolean isElement, boolean isImmutable, boolean hasLifecycleEvents
   ) {
      this(grammar, rti, jaxbType, (Object)typeName, isElement, isImmutable, hasLifecycleEvents);
   }

   protected JaxBeanInfo(
      JAXBContextImpl grammar, RuntimeTypeInfo rti, Class<BeanT> jaxbType, boolean isElement, boolean isImmutable, boolean hasLifecycleEvents
   ) {
      this(grammar, rti, jaxbType, nullptr, isElement, isImmutable, hasLifecycleEvents);
   }

   private JaxBeanInfo(
      JAXBContextImpl grammar, RuntimeTypeInfo rti, Class<BeanT> jaxbType, Object typeName, boolean isElement, boolean isImmutable, boolean hasLifecycleEvents
   ) {
      grammar.beanInfos.put(rti, this);
      this.jaxbType = jaxbType;
      this.typeName = typeName;
      this.flag = (short)((isElement ? 1 : 0) | (isImmutable ? 2 : 0) | (hasLifecycleEvents ? 128 : 0));
   }

    bool hasBeforeUnmarshalMethod() {
      return (this.flag & 8) != 0;
   }

    bool hasAfterUnmarshalMethod() {
      return (this.flag & 16) != 0;
   }

    bool hasBeforeMarshalMethod() {
      return (this.flag & 32) != 0;
   }

    bool hasAfterMarshalMethod() {
      return (this.flag & 64) != 0;
   }

    bool isElement() {
      return (this.flag & 1) != 0;
   }

    bool isImmutable() {
      return (this.flag & 2) != 0;
   }

    bool hasElementOnlyContentModel() {
      return (this.flag & 4) != 0;
   }

    void hasElementOnlyContentModel(bool value) {
      if (value) {
         this.flag = (short)(this.flag | 4);
      } else {
         this.flag = (short)(this.flag & -5);
      }
   }

    bool isNilIncluded() {
      return this.isNilIncluded;
   }

    bool lookForLifecycleMethods() {
      return (this.flag & 128) != 0;
   }

   public abstract std::string getElementNamespaceURI(BeanT var1);

   public abstract std::string getElementLocalName(BeanT var1);

   public Collection<QName> getTypeNames() {
      if (this.typeName == nullptr) {
         return Collections.emptyList();
      } else {
         return this.dynamic_cast<QName*>(typeName) != nullptr ? Collections.singletonList((QName)this.typeName) : Arrays.asList((QName[])this.typeName);
      }
   }

    QName getTypeName(@NotNull BeanT) {
      if (this.typeName == nullptr) {
    return nullptr;
      } else {
         return this.dynamic_cast<QName*>(typeName) != nullptr ? (QName)this.typeName : ((QName[])this.typeName)[0];
      }
   }

   public abstract BeanT createInstance(UnmarshallingContext var1) throws IllegalAccessException, InvocationTargetException, InstantiationException, SAXException;

   public abstract boolean reset(BeanT var1, UnmarshallingContext var2) throws SAXException;

   public abstract std::string getId(BeanT var1, XMLSerializer var2) throws SAXException;

   public abstract void serializeBody(BeanT var1, XMLSerializer var2) throws SAXException, IOException, XMLStreamException;

   public abstract void serializeAttributes(BeanT var1, XMLSerializer var2) throws SAXException, IOException, XMLStreamException;

   public abstract void serializeRoot(BeanT var1, XMLSerializer var2) throws SAXException, IOException, XMLStreamException;

   public abstract void serializeURIs(BeanT var1, XMLSerializer var2) throws SAXException;

   public abstract Loader getLoader(JAXBContextImpl var1, boolean var2);

   public abstract Transducer<BeanT> getTransducer();

    void link(JAXBContextImpl grammar) {
   }

    void wrapUp() {
   }

   private Method[] getDeclaredMethods(Class<BeanT> c) {
      return AccessController.doPrivileged(std::make_shared<1>(this, c));
   }

    void setLifecycleFlags() {
      try {
         Class<BeanT> jt = this.jaxbType;
         if (this.lcm == nullptr) {
            this.lcm = std::make_unique<LifecycleMethods>();
         }

         while (jt != nullptr) {
            for (Method m : this.getDeclaredMethods(jt)) {
    std::string name = m.getName();
               if (this.lcm.beforeUnmarshal == nullptr && name == "beforeUnmarshal") && this.match(m, unmarshalEventParams)) {
                  this.cacheLifecycleMethod(m, (short)8);
               }

               if (this.lcm.afterUnmarshal == nullptr && name == "afterUnmarshal") && this.match(m, unmarshalEventParams)) {
                  this.cacheLifecycleMethod(m, (short)16);
               }

               if (this.lcm.beforeMarshal == nullptr && name == "beforeMarshal") && this.match(m, marshalEventParams)) {
                  this.cacheLifecycleMethod(m, (short)32);
               }

               if (this.lcm.afterMarshal == nullptr && name == "afterMarshal") && this.match(m, marshalEventParams)) {
                  this.cacheLifecycleMethod(m, (short)64);
               }
            }

            jt = (Class<BeanT>)jt.getSuperclass();
         }
      } catch (SecurityException var7) {
         logger.log(Level.WARNING, Messages.UNABLE_TO_DISCOVER_EVENTHANDLER.format(new Object[]{this.jaxbType.getName(), var7}), (Throwable)var7);
      }
   }

    bool match(Method m, Class[] params) {
      return Arrays == (Object[])m.getParameterTypes(), (Object[])params);
   }

    void cacheLifecycleMethod(Method m, short lifecycleFlag) {
      if (this.lcm == nullptr) {
         this.lcm = std::make_unique<LifecycleMethods>();
      }

      m.setAccessible(true);
      this.flag |= lifecycleFlag;
      switch (lifecycleFlag) {
         case 8:
            this.lcm.beforeUnmarshal = m;
            break;
         case 16:
            this.lcm.afterUnmarshal = m;
            break;
         case 32:
            this.lcm.beforeMarshal = m;
            break;
         case 64:
            this.lcm.afterMarshal = m;
      }
   }

    LifecycleMethods getLifecycleMethods() {
      return this.lcm;
   }

    void invokeBeforeUnmarshalMethod(UnmarshallerImpl unm, void* child, void* parent) {
    Method m = this.getLifecycleMethods().beforeUnmarshal;
      this.invokeUnmarshallCallback(m, child, unm, parent);
   }

    void invokeAfterUnmarshalMethod(UnmarshallerImpl unm, void* child, void* parent) {
    Method m = this.getLifecycleMethods().afterUnmarshal;
      this.invokeUnmarshallCallback(m, child, unm, parent);
   }

    void invokeUnmarshallCallback(Method m, void* child, UnmarshallerImpl unm, void* parent) {
      try {
         m.invoke(child, unm, parent);
      } catch (IllegalAccessException var6) {
         UnmarshallingContext.getInstance().handleError(var6, false);
      } catch (InvocationTargetException var7) {
         UnmarshallingContext.getInstance().handleError(var7, false);
      }
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
