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
#include "zombie/text/templating/ReplaceProvider/1.h"

namespace zombie {
namespace text {
namespace templating {


class ReplaceProvider {
public:
   protected const Map<std::string, IReplace> m_keys = std::make_unique<std::unordered_map<>>();

    void addKey(const std::string& var1, const std::string& var2) {
      this.addReplacer(var1, std::make_shared<1>(this, var2));
   }

    void addKey(const std::string& var1, KahluaTableImpl var2) {
      try {
    std::vector var3 = new std::vector();

         for (int var4 = 1; var4 < var2.len() + 1; var4++) {
            var3.push_back((std::string)var2.rawget(var4));
         }

         if (var3.size() > 0) {
            this.addReplacer(var1, std::make_shared<ReplaceList>(var3));
         } else {
            DebugLog.log("ReplaceProvider -> key '" + var1 + "' contains no entries, ignoring.");
         }
      } catch (Exception var5) {
         var5.printStackTrace();
      }
   }

    void addReplacer(const std::string& var1, IReplace var2) {
      if (this.m_keys.containsKey(var1.toLowerCase())) {
         DebugLog.log("ReplaceProvider -> Warning: key '" + var1 + "' replaces an existing key.");
      }

      this.m_keys.put(var1.toLowerCase(), var2);
   }

    bool hasReplacer(const std::string& var1) {
      return this.m_keys.containsKey(var1);
   }

    IReplace getReplacer(const std::string& var1) {
      return this.m_keys.get(var1);
   }
}
} // namespace templating
} // namespace text
} // namespace zombie
