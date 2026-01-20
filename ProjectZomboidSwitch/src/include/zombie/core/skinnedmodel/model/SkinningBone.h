#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class SkinningBone {
public:
    SkinningBone Parent;
    std::string Name;
    int Index;
   public SkinningBone[] Children;

    void forEachDescendant(Consumer<SkinningBone> var1) {
      forEachDescendant(this, var1);
   }

    static void forEachDescendant(SkinningBone var0, Consumer<SkinningBone> var1) {
      if (var0.Children != nullptr && var0.Children.length != 0) {
         for (SkinningBone var5 : var0.Children) {
            var1.accept(var5);
         }

         for (SkinningBone var9 : var0.Children) {
            forEachDescendant(var9, var1);
         }
      }
   }

    std::string toString() {
    std::string var1 = System.lineSeparator();
      return this.getClass().getName() + var1 + "{" + var1 + "\tName:\"" + this.Name + "\"" + var1 + "\tIndex:" + this.Index + var1 + "}";
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
