#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexElement.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexType.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class VertexBufferObject {
public:
   const VertexElement[] m_elements;
    int m_stride;

   public VertexBufferObject$VertexFormat(int var1) {
      this.m_elements = (VertexElement[])PZArrayUtil.newInstance(VertexElement.class, var1, VertexElement::new);
   }

    void setElement(int var1, VertexType var2, int var3) {
      this.m_elements[var1].m_type = var2;
      this.m_elements[var1].m_byteSize = var3;
   }

    void calculate() {
      this.m_stride = 0;

      for (int var1 = 0; var1 < this.m_elements.length; var1++) {
         this.m_elements[var1].m_byteOffset = this.m_stride;
         this.m_stride = this.m_stride + this.m_elements[var1].m_byteSize;
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
