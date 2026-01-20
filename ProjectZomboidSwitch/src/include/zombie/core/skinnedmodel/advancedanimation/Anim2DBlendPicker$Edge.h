#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {

class Anim2DBlendPicker {
public:
    Anim2DBlend a;
    Anim2DBlend b;

   public Anim2DBlendPicker$Edge(Anim2DBlend var1, Anim2DBlend var2) {
    bool var3;
      if (var1.m_XPos != var2.m_XPos) {
         var3 = var1.m_XPos > var2.m_XPos;
      } else {
         var3 = var1.m_YPos > var2.m_YPos;
      }

      if (var3) {
         this.a = var2;
         this.b = var1;
      } else {
         this.a = var1;
         this.b = var2;
      }
   }

    int hashCode() {
    int var1 = this.a.hashCode();
    int var2 = this.b.hashCode();
      return (var1 << 5) + var1 ^ var2;
   }

    bool equals(void* var1) {
      return !(dynamic_cast<Anim2DBlendPicker*>(var1) != nullptr$Edge) ? false : this.a == ((Anim2DBlendPicker$Edge)var1).a && this.b == ((Anim2DBlendPicker$Edge)var1).b;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
