#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SkinningBone {
public:
  SkinningBone Parent;
  std::string Name;
  int Index;
public
  SkinningBone[] Children;

  void forEachDescendant(Consumer<SkinningBone> consumer) {
    forEachDescendant(this, consumer);
  }

  static void forEachDescendant(SkinningBone skinningBone0,
                                Consumer<SkinningBone> consumer) {
    if (skinningBone0.Children != nullptr &&
        skinningBone0.Children.length != 0) {
      for (SkinningBone skinningBone1 : skinningBone0.Children) {
        consumer.accept(skinningBone1);
      }

      for (SkinningBone skinningBone2 : skinningBone0.Children) {
        forEachDescendant(skinningBone2, consumer);
      }
    }
  }

  std::string toString() {
    std::string string = System.lineSeparator();
    return this.getClass().getName() + string + "{" + string + "\tName:\"" +
           this.Name + "\"" + string + "\tIndex:" + this.Index + string + "}";
  }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
