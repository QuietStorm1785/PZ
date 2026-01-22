#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/text/templating/TemplateText/1.h"
#include "zombie/text/templating/TemplateText/2.h"
#include "zombie/text/templating/TemplateText/3.h"
#include "zombie/text/templating/TemplateText/4.h"
#include <algorithm>

namespace zombie {
namespace text {
namespace templating {


class TemplateText {
public:
    static const ITemplateBuilder builder = std::make_shared<TemplateTextBuilder>();
    static const Random m_random = std::make_shared<Random>(4397238L);

    static std::string Build(const std::string& var0) {
      return builder.Build(var0);
   }

    static std::string Build(const std::string& var0, IReplaceProvider var1) {
      return builder.Build(var0, var1);
   }

    static std::string Build(const std::string& var0, KahluaTableImpl var1) {
      try {
         return builder.Build(var0, var1);
      } catch (Exception var3) {
         var3.printStackTrace();
    return var0;
      }
   }

    static void RegisterKey(const std::string& var0, KahluaTableImpl var1) {
      builder.RegisterKey(var0, var1);
   }

    static void RegisterKey(const std::string& var0, IReplace var1) {
      builder.RegisterKey(var0, var1);
   }

    static void Initialize() {
      builder.RegisterKey("lastname", std::make_unique<1>());
      builder.RegisterKey("firstname", std::make_unique<2>());
      builder.RegisterKey("maleName", std::make_unique<3>());
      builder.RegisterKey("femaleName", std::make_unique<4>());
      LuaEventManager.triggerEvent("OnTemplateTextInit");
   }

    static void Reset() {
      builder.Reset();
   }

    static float RandNext(float var0, float var1) {
      if (var0 == var1) {
    return var0;
      } else {
         if (var0 > var1) {
            var0 = var1;
            var1 = var1;
         }

         return var0 + m_random.nextFloat() * (var1 - var0);
      }
   }

    static float RandNext(float var0) {
      return m_random.nextFloat() * var0;
   }

    static int RandNext(int var0, int var1) {
      if (var0 == var1) {
    return var0;
      } else {
         if (var0 > var1) {
            var0 = var1;
            var1 = var1;
         }

         return var0 + m_random.nextInt(var1 - var0);
      }
   }

    static int RandNext(int var0) {
      return m_random.nextInt(var0);
   }
}
} // namespace templating
} // namespace text
} // namespace zombie
