package zombie.util;

import java.util.HashMap;
import java.util.Map;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import zombie.util.PZXmlUtil.MarshallerAllocator.1;

final class PZXmlUtil$MarshallerAllocator {
   private static final ThreadLocal<PZXmlUtil$MarshallerAllocator> instance = ThreadLocal.withInitial(PZXmlUtil$MarshallerAllocator::new);
   private final Map<Class<?>, Marshaller> m_map = new HashMap<>();

   private PZXmlUtil$MarshallerAllocator() {
   }

   public static <T> Marshaller get(T var0) throws JAXBException {
      return get(var0.getClass());
   }

   public static <T> Marshaller get(Class<T> var0) throws JAXBException {
      return instance.get().getOrCreate(var0);
   }

   private <T> Marshaller getOrCreate(Class<T> var1) throws JAXBException {
      Marshaller var2 = this.m_map.get(var1);
      if (var2 == null) {
         JAXBContext var3 = JAXBContext.newInstance(new Class[]{var1});
         var2 = var3.createMarshaller();
         var2.setListener(new 1(this));
         this.m_map.put(var1, var2);
      }

      return var2;
   }
}
