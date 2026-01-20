#pragma once
#include <list>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/ClassFactory.h"
#include "com/sun/xml/bind/v2/model/core/Adapter.h"
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/1.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/2.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/ArrayLister.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/CollectionLister.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/IDREFS.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Lister {
public:
   private static const Map<Class, WeakReference<Lister>> arrayListerCache = Collections.synchronizedMap(std::make_unique<WeakHashMap<>>());
   static const Map<Class, Lister> primitiveArrayListers = std::make_unique<std::unordered_map<>>();
    static const Lister ERROR = std::make_shared<1>();
    static const ListIterator EMPTY_ITERATOR = std::make_shared<2>();
   private static const Class[] COLLECTION_IMPL_CLASSES = new Class[]{std::vector.class, std::list.class, std::unordered_set.class, std::set.class, std::stack.class};

    protected Lister() {
   }

   public abstract ListIterator<ItemT> iterator(PropT var1, XMLSerializer var2);

   public abstract PackT startPacking(BeanT var1, Accessor<BeanT, PropT> var2) throws AccessorException;

   public abstract void addToPack(PackT var1, ItemT var2) throws AccessorException;

   public abstract void endPacking(PackT var1, BeanT var2, Accessor<BeanT, PropT> var3) throws AccessorException;

   public abstract void reset(BeanT var1, Accessor<BeanT, PropT> var2) throws AccessorException;

   public static <BeanT, PropT, ItemT, PackT> Lister<BeanT, PropT, ItemT, PackT> create(Type fieldType, ID idness, Adapter<Type, Class> adapter) {
    Class rawType = (Class)Utils.REFLECTION_NAVIGATOR.erasure(fieldType);
    Class itemType;
    Lister l;
      if (rawType.isArray()) {
         itemType = rawType.getComponentType();
         l = getArrayLister(itemType);
      } else {
         if (!Collection.class.isAssignableFrom(rawType)) {
    return nullptr;
         }

    Type bt = (Type)Utils.REFLECTION_NAVIGATOR.getBaseClass(fieldType, Collection.class);
         if (dynamic_cast<ParameterizedType*>(bt) != nullptr) {
            itemType = (Class)Utils.REFLECTION_NAVIGATOR.erasure(((ParameterizedType)bt).getActualTypeArguments()[0]);
         } else {
            itemType = Object.class;
         }

         l = std::make_shared<CollectionLister>(getImplClass(rawType));
      }

      if (idness == ID.IDREF) {
         l = std::make_shared<IDREFS>(l, itemType);
      }

      if (adapter != nullptr) {
         l = std::make_shared<AdaptedLister>(l, (Class)adapter.adapterType);
      }

    return l;
   }

    static Class getImplClass(Class<?> fieldType) {
      return ClassFactory.inferImplClass(fieldType, COLLECTION_IMPL_CLASSES);
   }

    static Lister getArrayLister(Class componentType) {
    Lister l = nullptr;
      if (componentType.isPrimitive()) {
         l = primitiveArrayListers.get(componentType);
      } else {
         WeakReference<Lister> wr = arrayListerCache.get(componentType);
         if (wr != nullptr) {
            l = wr.get();
         }

         if (l == nullptr) {
            l = std::make_shared<ArrayLister>(componentType);
            arrayListerCache.put(componentType, new WeakReference<>(l));
         }
      }

      assert l != nullptr;

    return l;
   }

   public static <A, B, C, D> Lister<A, B, C, D> getErrorInstance() {
    return ERROR;
   }

   static {
      PrimitiveArrayListerBoolean.register();
      PrimitiveArrayListerByte.register();
      PrimitiveArrayListerCharacter.register();
      PrimitiveArrayListerDouble.register();
      PrimitiveArrayListerFloat.register();
      PrimitiveArrayListerInteger.register();
      PrimitiveArrayListerLong.register();
      PrimitiveArrayListerShort.register();
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
