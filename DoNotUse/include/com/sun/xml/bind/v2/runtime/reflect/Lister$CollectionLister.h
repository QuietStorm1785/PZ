#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/ClassFactory.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/CollectionLister/1.h"
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Lister {
public:
   private const Class<? : public T> implClass;

   public Lister$CollectionLister(Class<? : public T> implClass) {
      this.implClass = implClass;
   }

    ListIterator iterator(T collection, XMLSerializer context) {
    Iterator itr = collection.iterator();
      return std::make_shared<1>(this, itr);
   }

    T startPacking(BeanT bean, T> acc) {
    T collection = (T)acc.get(bean);
      if (collection == nullptr) {
         collection = (T)ClassFactory.create(this.implClass);
         if (!acc.isAdapted()) {
            acc.set(bean, collection);
         }
      }

      collection.clear();
    return collection;
   }

    void addToPack(T collection, void* o) {
      collection.push_back(o);
   }

    void endPacking(T collection, BeanT bean, T> acc) {
      try {
         if (acc.isAdapted()) {
            acc.set(bean, collection);
         }
      } catch (AccessorException var5) {
         if (acc.isAdapted()) {
    throw var5;
         }
      }
   }

    void reset(BeanT bean, T> acc) {
    T collection = (T)acc.get(bean);
      if (collection != nullptr) {
         collection.clear();
      }
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
