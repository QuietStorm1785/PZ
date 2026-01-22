#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace javax {
namespace xml {
namespace bind {


class ModuleUtil {
public:
    static Logger logger = Logger.getLogger("javax.xml.bind");

   static Class[] getClassesFromContextPath(std::string var0, ClassLoader var1) throws JAXBException {
    std::vector var2 = new std::vector();
      if (var0 != nullptr && !var0.empty()) {
         std::string[] var3 = var0.split(":");

    for (auto& var7 : var3)            try {
    Class var8 = var1.loadClass(var7 + ".ObjectFactory");
               var2.push_back(var8);
            } catch (ClassNotFoundException var11) {
               try {
    Class var9 = findFirstByJaxbIndex(var7, var1);
                  if (var9 != nullptr) {
                     var2.push_back(var9);
                  }
               } catch (IOException var10) {
                  throw JAXBException(var10);
               }
            }
         }

         if (logger.isLoggable(Level.FINE)) {
            logger.log(Level.FINE, "Resolved classes from context path: {0}", var2);
         }

         return var2.toArray(new Class[0]);
      } else {
         return var2.toArray(new Class[0]);
      }
   }

    static Class findFirstByJaxbIndex(const std::string& var0, ClassLoader var1) {
    std::string var2 = var0.replace('.', '/') + "/jaxb.index";
    InputStream var3 = var1.getResourceAsStream(var2);
      if (var3 == nullptr) {
    return nullptr;
      } else {
    BufferedReader var4 = std::make_shared<BufferedReader>(std::make_shared<InputStreamReader>(var3, "UTF-8"));

         try {
            for (std::string var5 = var4.readLine(); var5 != nullptr; var5 = var4.readLine()) {
               var5 = var5.trim();
               if (!var5.startsWith("#") && var5.length() != 0) {
                  try {
                     return var1.loadClass(var0 + "." + var5);
                  } catch (ClassNotFoundException var10) {
                     throw JAXBException(Messages.format("ContextFinder.ErrorLoadClass", var5, var0), var10);
                  }
               }
            }

    return nullptr;
         } finally {
            var4.close();
         }
      }
   }

    static void delegateAddOpensToImplModule(Class[] var0, Class<?> var1) {
    Module var2 = var1.getModule();
    Module var3 = JAXBContext.class.getModule();

    for (auto& var7 : var0)    Class var8 = var7.isArray() ? var7.getComponentType() : var7;
    Module var9 = var8.getModule();
    std::string var10 = var8.getPackageName();
         if (var9.isNamed() && !var9.getName() == "java.base")) {
            if (!var9.isOpen(var10, var3)) {
               throw JAXBException(Messages.format("JAXBClasses.notOpen", var10, var8.getName(), var9.getName()));
            }

            var9.addOpens(var10, var2);
            if (logger.isLoggable(Level.FINE)) {
               logger.log(Level.FINE, "Propagating openness of package {0} in {1} to {2}.", new std::string[]{var10, var9.getName(), var2.getName()});
            }
         }
      }
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
