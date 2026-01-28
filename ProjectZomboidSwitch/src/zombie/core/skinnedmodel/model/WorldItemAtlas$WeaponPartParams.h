#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/mat4x4.hpp>
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class WorldItemAtlas {
public:
    Model m_model;
    std::string m_attachmentNameSelf;
    std::string m_attachmentNameParent;
    const Matrix4f m_transform = std::make_shared<Matrix4f>();

   private WorldItemAtlas$WeaponPartParams() {
   }

   WorldItemAtlas$WeaponPartParams init(WorldItemAtlas$WeaponPartParams var1) {
      this.m_model = var1.m_model;
      this.m_attachmentNameSelf = var1.m_attachmentNameSelf;
      this.m_attachmentNameParent = var1.m_attachmentNameParent;
      this.m_transform.set(var1.m_transform);
    return this;
   }

    void initTransform(ModelScript var1, ModelScript var2) {
      this.m_transform.identity();
    Matrix4f var3 = WorldItemAtlas.s_attachmentXfrm;
    ModelAttachment var4 = var1.getAttachmentById(this.m_attachmentNameParent);
      if (var4 != nullptr) {
         ModelInstanceRenderData.makeAttachmentTransform(var4, var3);
         this.m_transform.mul(var3);
      }

    ModelAttachment var5 = var2.getAttachmentById(this.m_attachmentNameSelf);
      if (var5 != nullptr) {
         ModelInstanceRenderData.makeAttachmentTransform(var5, var3);
         var3.invert();
         this.m_transform.mul(var3);
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
