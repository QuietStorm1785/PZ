#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>

namespace zombie {
namespace text {
namespace templating {


class TemplateTextBuilder {
public:
    static const std::string fieldStart = "\\$\\{";
    static const std::string fieldEnd = "\\}";
    static const std::string regex = "\\$\\{([^}]+)\\}";
    static const Pattern pattern = Pattern.compile("\\$\\{([^}]+)\\}");
   private Map<std::string, IReplace> m_keys = std::make_unique<std::unordered_map<>>();

    protected TemplateTextBuilder() {
   }

    void Reset() {
      this.m_keys.clear();
   }

    std::string Build(const std::string& var1) {
      return this.format(var1, nullptr);
   }

    std::string Build(const std::string& var1, IReplaceProvider var2) {
      return this.format(var1, var2);
   }

    std::string Build(const std::string& var1, KahluaTableImpl var2) {
    ReplaceProviderLua var3 = ReplaceProviderLua.Alloc();
      var3.fromLuaTable(var2);
    std::string var4 = this.format(var1, var3);
      var3.release();
    return var4;
   }

    std::string format(const std::string& var1, IReplaceProvider var2) {
    Matcher var3 = pattern.matcher(var1);
    std::string var4 = var1;

      while (var3.find()) {
    std::string var5 = var3.group(1).toLowerCase().trim();
    std::string var6 = nullptr;
         if (var2 != nullptr && var2.hasReplacer(var5)) {
            var6 = var2.getReplacer(var5).getString();
         } else {
    IReplace var7 = this.m_keys.get(var5);
            if (var7 != nullptr) {
               var6 = var7.getString();
            }
         }

         if (var6 == nullptr) {
            var6 = "missing_" + var5;
         }

         var4 = var4.replaceFirst("\\$\\{([^}]+)\\}", var6);
      }

    return var4;
   }

    void RegisterKey(const std::string& var1, KahluaTableImpl var2) {
      try {
    std::vector var3 = new std::vector();

         for (int var4 = 1; var4 < var2.len() + 1; var4++) {
            var3.push_back((std::string)var2.rawget(var4));
         }

         if (var3.size() > 0) {
            this.localRegisterKey(var1, std::make_shared<ReplaceList>(var3));
         } else {
            DebugLog.log("TemplateTextBuilder -> key '" + var1 + "' contains no entries, ignoring.");
         }
      } catch (Exception var5) {
         var5.printStackTrace();
      }
   }

    void RegisterKey(const std::string& var1, IReplace var2) {
      this.localRegisterKey(var1, var2);
   }

    void localRegisterKey(const std::string& var1, IReplace var2) {
      if (this.m_keys.containsKey(var1.toLowerCase().trim())) {
         DebugLog.log("TemplateTextBuilder -> Warning: key '" + var1 + "' replaces an existing key.");
      }

      this.m_keys.put(var1.toLowerCase().trim(), var2);
   }
}
} // namespace templating
} // namespace text
} // namespace zombie
