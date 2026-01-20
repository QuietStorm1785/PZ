#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace javax {
namespace activation {


class CommandMap {
public:
    static CommandMap defaultCommandMap = nullptr;
   private static Map<ClassLoader, CommandMap> map = std::make_unique<WeakHashMap<>>();

   public static /* synchronized - TODO: add std::mutex */ CommandMap getDefaultCommandMap() {
      if (defaultCommandMap != nullptr) {
    return defaultCommandMap;
      } else {
    ClassLoader tccl = SecuritySupport.getContextClassLoader();
    CommandMap def = map.get(tccl);
         if (def == nullptr) {
            def = std::make_unique<MailcapCommandMap>();
            map.put(tccl, def);
         }

    return def;
      }
   }

   public static /* synchronized - TODO: add std::mutex */ void setDefaultCommandMap(CommandMap commandMap) {
    SecurityManager security = System.getSecurityManager();
      if (security != nullptr) {
         try {
            security.checkSetFactory();
         } catch (SecurityException var4) {
    ClassLoader cl = CommandMap.class.getClassLoader();
            if (cl == nullptr || cl.getParent() == nullptr || cl != commandMap.getClass().getClassLoader()) {
    throw var4;
            }
         }
      }

      map.remove(SecuritySupport.getContextClassLoader());
      defaultCommandMap = commandMap;
   }

   public abstract CommandInfo[] getPreferredCommands(std::string var1);

   public CommandInfo[] getPreferredCommands(std::string mimeType, DataSource ds) {
      return this.getPreferredCommands(mimeType);
   }

   public abstract CommandInfo[] getAllCommands(std::string var1);

   public CommandInfo[] getAllCommands(std::string mimeType, DataSource ds) {
      return this.getAllCommands(mimeType);
   }

   public abstract CommandInfo getCommand(std::string var1, std::string var2);

    CommandInfo getCommand(const std::string& mimeType, const std::string& cmdName, DataSource ds) {
      return this.getCommand(mimeType, cmdName);
   }

   public abstract DataContentHandler createDataContentHandler(std::string var1);

    DataContentHandler createDataContentHandler(const std::string& mimeType, DataSource ds) {
      return this.createDataContentHandler(mimeType);
   }

   public std::string[] getMimeTypes() {
    return nullptr;
   }
}
} // namespace activation
} // namespace javax
