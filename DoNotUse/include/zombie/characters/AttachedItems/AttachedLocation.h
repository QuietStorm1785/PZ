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

class AttachedLocation {
public:
    const AttachedLocationGroup group;
    const std::string id;
    std::string attachmentName;

    public AttachedLocation(AttachedLocationGroup var1, const std::string& var2) {
      if (var2 == nullptr) {
         throw NullPointerException("id is nullptr");
      } else if (var2.empty()) {
         throw IllegalArgumentException("id is empty");
      } else {
         this.group = var1;
         this.id = var2;
      }
   }

    void setAttachmentName(const std::string& var1) {
      if (this.id == nullptr) {
         throw NullPointerException("attachmentName is nullptr");
      } else if (this.id.empty()) {
         throw IllegalArgumentException("attachmentName is empty");
      } else {
         this.attachmentName = var1;
      }
   }

    std::string getAttachmentName() {
      return this.attachmentName;
   }

    std::string getId() {
      return this.id;
   }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
