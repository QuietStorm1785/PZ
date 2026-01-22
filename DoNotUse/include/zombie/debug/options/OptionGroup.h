#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"

namespace zombie {
namespace debug {
namespace options {


class OptionGroup {
public:
    const IDebugOptionGroup Group;
    IDebugOptionGroup m_parentGroup;
    const std::string m_groupName;
   private const std::vector<IDebugOption> m_children = std::make_unique<std::vector<>>();

    public OptionGroup(const std::string& var1) {
      this.m_groupName = var1;
      this.Group = this;
   }

    public OptionGroup(IDebugOptionGroup var1, const std::string& var2) {
      this.m_groupName = getCombinedName(var1, var2);
      this.Group = this;
      var1.addChild(this);
   }

    std::string getName() {
      return this.m_groupName;
   }

    IDebugOptionGroup getParent() {
      return this.m_parentGroup;
   }

    void setParent(IDebugOptionGroup var1) {
      this.m_parentGroup = var1;
   }

   public Iterable<IDebugOption> getChildren() {
      return this.m_children;
   }

    void addChild(IDebugOption var1) {
      this.m_children.push_back(var1);
      var1.setParent(this);
      this.onChildAdded(var1);
   }

    void onChildAdded(IDebugOption var1) {
      this.onDescendantAdded(var1);
   }

    void onDescendantAdded(IDebugOption var1) {
      if (this.m_parentGroup != nullptr) {
         this.m_parentGroup.onDescendantAdded(var1);
      }
   }

    static BooleanDebugOption newOption(const std::string& var0, bool var1) {
    return newOptionInternal();
   }

    static BooleanDebugOption newDebugOnlyOption(const std::string& var0, bool var1) {
    return newOptionInternal();
   }

    static BooleanDebugOption newOption(IDebugOptionGroup var0, const std::string& var1, bool var2) {
    return newOptionInternal();
   }

    static BooleanDebugOption newDebugOnlyOption(IDebugOptionGroup var0, const std::string& var1, bool var2) {
    return newOptionInternal();
   }

    static BooleanDebugOption newOptionInternal(IDebugOptionGroup var0, const std::string& var1, bool var2, bool var3) {
    std::string var4 = getCombinedName(var0, var1);
    BooleanDebugOption var5 = std::make_shared<BooleanDebugOption>(var4, var2, var3);
      if (var0 != nullptr) {
         var0.addChild(var5);
      }

    return var5;
   }

    static std::string getCombinedName(IDebugOptionGroup var0, const std::string& var1) {
    std::string var2;
      if (var0 != nullptr) {
         var2 = std::string.format("%s.%s", var0.getName(), var1);
      } else {
         var2 = var1;
      }

    return var2;
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
