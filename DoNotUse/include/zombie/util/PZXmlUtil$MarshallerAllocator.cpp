#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Marshaller.h"
#include "zombie/util/PZXmlUtil/MarshallerAllocator/1.h"

namespace zombie {
namespace util {


class PZXmlUtil {
public:
   private static const ThreadLocal<PZXmlUtil$MarshallerAllocator> instance = ThreadLocal.withInitial(PZXmlUtil$MarshallerAllocator::new);
   private const Map<Class<?>, Marshaller> m_map = std::make_unique<std::unordered_map<>>();

   private PZXmlUtil$MarshallerAllocator() {
   }

   public static <T> Marshaller get(T var0) throws JAXBException {
    return get();
   }

   public static <T> Marshaller get(Class<T> var0) throws JAXBException {
      return instance.get().getOrCreate(var0);
   }

   private <T> Marshaller getOrCreate(Class<T> var1) throws JAXBException {
    Marshaller var2 = this.m_map.get(var1);
      if (var2 == nullptr) {
    JAXBContext var3 = JAXBContext.newInstance(new Class[]{var1});
         var2 = var3.createMarshaller();
         var2.setListener(std::make_shared<1>(this));
         this.m_map.put(var1, var2);
      }

    return var2;
   }
}
} // namespace util
} // namespace zombie
