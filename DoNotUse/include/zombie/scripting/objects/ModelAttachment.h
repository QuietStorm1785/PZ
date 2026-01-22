#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace scripting {
namespace objects {


class ModelAttachment {
public:
    std::string id;
    const Vector3f offset = std::make_shared<Vector3f>();
    const Vector3f rotate = std::make_shared<Vector3f>();
    std::string bone;
   private std::vector<std::string> canAttach;
    float zoffset;
    bool updateConstraint = true;

    public ModelAttachment(const std::string& var1) {
      this.setId(var1);
   }

    std::string getId() {
      return this.id;
   }

    void setId(const std::string& var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
         throw IllegalArgumentException("ModelAttachment id is nullptr or empty");
      } else {
         this.id = var1;
      }
   }

    Vector3f getOffset() {
      return this.offset;
   }

    Vector3f getRotate() {
      return this.rotate;
   }

    std::string getBone() {
      return this.bone;
   }

    void setBone(const std::string& var1) {
      var1 = var1.trim();
      this.bone = var1.empty() ? nullptr : var1;
   }

   public std::vector<std::string> getCanAttach() {
      return this.canAttach;
   }

    void setCanAttach(std::vector<std::string> var1) {
      this.canAttach = var1;
   }

    float getZOffset() {
      return this.zoffset;
   }

    void setZOffset(float var1) {
      this.zoffset = var1;
   }

    bool isUpdateConstraint() {
      return this.updateConstraint;
   }

    void setUpdateConstraint(bool var1) {
      this.updateConstraint = var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
