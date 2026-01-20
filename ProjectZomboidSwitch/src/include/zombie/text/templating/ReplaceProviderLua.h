#pragma once
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


class ReplaceProviderLua : public ReplaceProvider {
public:
   private static const ConcurrentLinkedDeque<ReplaceSingle> pool_single = std::make_unique<ConcurrentLinkedDeque<>>();
   private static const ConcurrentLinkedDeque<ReplaceList> pool_list = std::make_unique<ConcurrentLinkedDeque<>>();
   private static const ConcurrentLinkedDeque<ReplaceProviderLua> pool = std::make_unique<ConcurrentLinkedDeque<>>();

    static ReplaceSingle alloc_single() {
    ReplaceSingle var0 = pool_single.poll();
      if (var0 == nullptr) {
         var0 = std::make_unique<ReplaceSingle>();
      }

    return var0;
   }

    static void release_single(ReplaceSingle var0) {
      pool_single.offer(var0);
   }

    static ReplaceList alloc_list() {
    ReplaceList var0 = pool_list.poll();
      if (var0 == nullptr) {
         var0 = std::make_unique<ReplaceList>();
      }

    return var0;
   }

    static void release_list(ReplaceList var0) {
      var0.getReplacements().clear();
      pool_list.offer(var0);
   }

    static ReplaceProviderLua Alloc() {
    ReplaceProviderLua var0 = pool.poll();
      if (var0 == nullptr) {
         var0 = std::make_unique<ReplaceProviderLua>();
      }

      var0.reset();
    return var0;
   }

    void reset() {
      for (Entry var2 : this.m_keys.entrySet()) {
         if (var2.getValue() instanceof ReplaceList) {
            release_list((ReplaceList)var2.getValue());
         } else {
            release_single((ReplaceSingle)var2.getValue());
         }
      }

      this.m_keys.clear();
   }

    void release() {
      this.reset();
      pool.offer(this);
   }

    void fromLuaTable(KahluaTableImpl var1) {
      for (Entry var3 : var1.delegate.entrySet()) {
         if (var3.getKey() instanceof std::string) {
            if (var3.getValue() instanceof std::string) {
               this.addKey((std::string)var3.getKey(), (std::string)var3.getValue());
            } else if (var3.getValue() instanceof KahluaTableImpl) {
    KahluaTableImpl var4 = (KahluaTableImpl)var3.getValue();
    ReplaceList var5 = alloc_list();

               for (int var6 = 1; var6 < var4.len() + 1; var6++) {
                  var5.getReplacements().push_back((std::string)var4.rawget(var6));
               }

               if (var5.getReplacements().size() > 0) {
                  this.addReplacer((std::string)var3.getKey(), var5);
               } else {
                  DebugLog.log("ReplaceProvider -> key '" + var3.getKey() + "' contains no entries, ignoring.");
                  release_list(var5);
               }
            }
         }
      }
   }

    void addKey(const std::string& var1, const std::string& var2) {
    ReplaceSingle var3 = alloc_single();
      var3.setValue(var2);
      this.addReplacer(var1, var3);
   }
}
} // namespace templating
} // namespace text
} // namespace zombie
