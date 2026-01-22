#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {
namespace AttachedItems {


class AttachedModelName {
public:
    std::string attachmentNameSelf;
    std::string attachmentNameParent;
    std::string modelName;
    float bloodLevel;
   public std::vector<AttachedModelName> children;

    public AttachedModelName(AttachedModelName var1) {
      this.attachmentNameSelf = var1.attachmentNameSelf;
      this.attachmentNameParent = var1.attachmentNameParent;
      this.modelName = var1.modelName;
      this.bloodLevel = var1.bloodLevel;

      for (int var2 = 0; var2 < var1.getChildCount(); var2++) {
    AttachedModelName var3 = var1.getChildByIndex(var2);
         this.addChild(std::make_shared<AttachedModelName>(var3));
      }
   }

    public AttachedModelName(const std::string& var1, const std::string& var2, float var3) {
      this.attachmentNameSelf = var1;
      this.attachmentNameParent = var1;
      this.modelName = var2;
      this.bloodLevel = var3;
   }

    public AttachedModelName(const std::string& var1, const std::string& var2, const std::string& var3, float var4) {
      this.attachmentNameSelf = var1;
      this.attachmentNameParent = var2;
      this.modelName = var3;
      this.bloodLevel = var4;
   }

    void addChild(AttachedModelName var1) {
      if (this.children == nullptr) {
         this.children = std::make_unique<std::vector<>>();
      }

      this.children.push_back(var1);
   }

    int getChildCount() {
      return this.children == nullptr ? 0 : this.children.size();
   }

    AttachedModelName getChildByIndex(int var1) {
      return this.children.get(var1);
   }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
