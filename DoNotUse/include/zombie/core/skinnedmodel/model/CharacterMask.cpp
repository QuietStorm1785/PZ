#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/core/skinnedmodel/model/CharacterMask/Part.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/util/Pool.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class CharacterMask {
public:
   private const boolean[] m_visibleFlags = createFlags(Part.values().length, true);

    bool isBloodBodyPartVisible(BloodBodyPartType var1) {
      for (Part var5 : var1.getCharacterMaskParts()) {
         if (this.isPartVisible(var5)) {
    return true;
         }
      }

    return false;
   }

   private static boolean[] createFlags(int var0, boolean var1) {
      boolean[] var2 = new boolean[var0];

      for (int var3 = 0; var3 < var0; var3++) {
         var2[var3] = var1;
      }

    return var2;
   }

    void setAllVisible(bool var1) {
      Arrays.fill(this.m_visibleFlags, var1);
   }

    void copyFrom(CharacterMask var1) {
      System.arraycopy(var1.m_visibleFlags, 0, this.m_visibleFlags, 0, this.m_visibleFlags.length);
   }

    void setPartVisible(Part var1, bool var2) {
      if (var1.hasSubdivisions()) {
         for (Part var6 : var1.subDivisions()) {
            this.setPartVisible(var6, var2);
         }
      } else {
         this.m_visibleFlags[var1.getValue()] = var2;
      }
   }

    void setPartsVisible(std::vector<int> var1, bool var2) {
      for (int var3 = 0; var3 < var1.size(); var3++) {
    int var4 = (int)var1.get(var3);
    Part var5 = Part.fromInt(var4);
         if (var5 == nullptr) {
            if (DebugLog.isEnabled(DebugType.Clothing)) {
               DebugLog.Clothing.warn("MaskValue out of bounds: " + var4);
            }
         } else {
            this.setPartVisible(var5, var2);
         }
      }
   }

    bool isPartVisible(Part var1) {
      if (var1 == nullptr) {
    return false;
      } else if (!var1.hasSubdivisions()) {
         return this.m_visibleFlags[var1.getValue()];
      } else {
    bool var2 = true;

         for (int var3 = 0; var2 && var3 < var1.subDivisions().length; var3++) {
    Part var4 = var1.subDivisions()[var3];
            var2 = this.m_visibleFlags[var4.getValue()];
         }

    return var2;
      }
   }

    bool isTorsoVisible() {
      return this.isPartVisible(Part.Torso);
   }

    std::string toString() {
      return this.getClass().getSimpleName() + "{VisibleFlags:(" + this.contentsToString() + ")}";
   }

    std::string contentsToString() {
      if (this.isAllVisible()) {
         return "All Visible";
      } else if (this.isNothingVisible()) {
         return "Nothing Visible";
      } else {
    std::stringstream var1 = new std::stringstream();
    int var2 = 0;

         for (int var3 = 0; var2 < Part.leaves().length; var2++) {
    Part var4 = Part.leaves()[var2];
            if (this.isPartVisible(var4)) {
               if (var3 > 0) {
                  var1.append(',');
               }

               var1.append(var4);
               var3++;
            }
         }

         return var1;
      }
   }

    bool isAll(bool var1) {
    bool var2 = true;
    int var3 = 0;

      for (int var4 = Part.leaves().length; var2 && var3 < var4; var3++) {
    Part var5 = Part.leaves()[var3];
         var2 = this.isPartVisible(var5) == var1;
      }

    return var2;
   }

    bool isNothingVisible() {
      return this.isAll(false);
   }

    bool isAllVisible() {
      return this.isAll(true);
   }

    void forEachVisible(Consumer<Part> var1) {
      try {
         for (int var2 = 0; var2 < Part.leaves().length; var2++) {
    Part var3 = Part.leaves()[var2];
            if (this.isPartVisible(var3)) {
               var1.accept(var3);
            }
         }
      } finally {
         Pool.tryRelease(var1);
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
