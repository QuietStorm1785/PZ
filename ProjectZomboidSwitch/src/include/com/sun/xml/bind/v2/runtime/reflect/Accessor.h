#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/Nullable.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/core/Adapter.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor/1.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor/2.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Receiver.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext/State.h"
#include "java/awt/Image.h"
#include "java/net/URI.h"
#include "java/net/URL.h"
#include "javax/activation/DataHandler.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"
#include "javax/xml/datatype/Duration.h"
#include "javax/xml/datatype/XMLGregorianCalendar.h"
#include "javax/xml/transform/Source.h"
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
namespace reflect {


class Accessor {
public:
   public const Class<ValueT> valueType;
   private static List<Class> nonAbstractableClasses = Arrays.asList(
      Object.class,
      Calendar.class,
      Duration.class,
      XMLGregorianCalendar.class,
      Image.class,
      DataHandler.class,
      Source.class,
      Date.class,
      File.class,
      URI.class,
      URL.class,
      Class.class,
      std::string.class,
      Source.class
   );
    static bool accessWarned = false;
    static const Accessor ERROR = std::make_shared<1>(Object.class);
   public static const Accessor<JAXBElement, Object> JAXB_ELEMENT_VALUE = std::make_shared<2>(Object.class);
   private static const Map<Class, Object> uninitializedValues = std::make_unique<std::unordered_map<>>();

   public Class<ValueT> getValueType() {
      return this.valueType;
   }

    protected Accessor(Class<ValueT> valueType) {
      this.valueType = valueType;
   }

   public Accessor<BeanT, ValueT> optimize(@Nullable JAXBContextImpl context) {
    return this;
   }

   public abstract ValueT get(BeanT var1) throws AccessorException;

   public abstract void set(BeanT var1, ValueT var2) throws AccessorException;

    void* getUnadapted(BeanT bean) {
      return this.get(bean);
   }

    bool isAdapted() {
    return false;
   }

    void setUnadapted(BeanT bean, void* value) {
      this.set(bean, (ValueT)value);
   }

    void receive(State state, void* o) {
      try {
         this.set((BeanT)state.getTarget(), (ValueT)o);
      } catch (AccessorException var4) {
         Loader.handleGenericException(var4, true);
      } catch (IllegalAccessError var5) {
         Loader.handleGenericError(var5);
      }
   }

    bool isValueTypeAbstractable() {
      return !nonAbstractableClasses.contains(this.getValueType());
   }

    bool isAbstractable(Class clazz) {
      return !nonAbstractableClasses.contains(clazz);
   }

   public const <T> Accessor<BeanT, T> adapt(Class<T> targetType, Class<? : public XmlAdapter<T, ValueT>> adapter) {
      return std::make_shared<AdaptedAccessor>(targetType, this, adapter);
   }

   public const <T> Accessor<BeanT, T> adapt(Adapter<Type, Class> adapter) {
      return std::make_shared<AdaptedAccessor>((Class)Utils.REFLECTION_NAVIGATOR.erasure(adapter.defaultType), this, (Class)adapter.adapterType);
   }

   public static <A, B> Accessor<A, B> getErrorInstance() {
    return ERROR;
   }

   static {
      uninitializedValues.put(byte.class, (byte)0);
      uninitializedValues.put(boolean.class, false);
      uninitializedValues.put(char.class, '\u0000');
      uninitializedValues.put(float.class, 0.0F);
      uninitializedValues.put(double.class, 0.0);
      uninitializedValues.put(int.class, 0);
      uninitializedValues.put(long.class, 0L);
      uninitializedValues.put(short.class, (short)0);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
