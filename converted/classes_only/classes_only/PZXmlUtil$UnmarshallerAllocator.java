package zombie.util;

import java.util.HashMap;
import java.util.Map;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;
import zombie.util.PZXmlUtil.UnmarshallerAllocator.1;

final class PZXmlUtil$UnmarshallerAllocator {
   private static final ThreadLocal<PZXmlUtil$UnmarshallerAllocator> instance = ThreadLocal.withInitial(PZXmlUtil$UnmarshallerAllocator::new);
   private final Map<Class, Unmarshaller> m_map = new HashMap<>();

   private PZXmlUtil$UnmarshallerAllocator() {
   }

   public static <T> Unmarshaller get(Class<T> var0) throws JAXBException {
      return instance.get().getOrCreate(var0);
   }

   private <T> Unmarshaller getOrCreate(Class<T> var1) throws JAXBException {
      Unmarshaller var2 = this.m_map.get(var1);
      if (var2 == null) {
         JAXBContext var3 = JAXBContext.newInstance(new Class[]{var1});
         var2 = var3.createUnmarshaller();
         var2.setListener(new 1(this));
         this.m_map.put(var1, var2);
      }

      return var2;
   }
}
