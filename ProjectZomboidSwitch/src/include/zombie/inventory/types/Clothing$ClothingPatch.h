#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Translator.h"
#include "zombie/inventory/types/Clothing/ClothingPatchFabricType.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {


class Clothing {
public:
    int tailorLvl;
    int fabricType;
    int scratchDefense;
    int biteDefense;
    bool hasHole;
    int conditionGain;

    std::string getFabricTypeName() {
      return Translator.getText("IGUI_FabricType_" + this.fabricType);
   }

    int getScratchDefense() {
      return this.scratchDefense;
   }

    int getBiteDefense() {
      return this.biteDefense;
   }

    int getFabricType() {
      return this.fabricType;
   }

   public Clothing$ClothingPatch(Clothing var1) {
      this.this$0 = var1;
      this.tailorLvl = 0;
      this.fabricType = 0;
      this.scratchDefense = 0;
      this.biteDefense = 0;
      this.conditionGain = 0;
   }

   public Clothing$ClothingPatch(Clothing var1, int var2, int var3, boolean var4) {
      this.this$0 = var1;
      this.tailorLvl = 0;
      this.fabricType = 0;
      this.scratchDefense = 0;
      this.biteDefense = 0;
      this.conditionGain = 0;
      this.tailorLvl = var2;
      this.fabricType = var3;
      this.hasHole = var4;
    ClothingPatchFabricType var5 = ClothingPatchFabricType.fromIndex(var3);
      this.scratchDefense = (int)Math.max(1.0F, var5.maxScratchDef * (var2 / 10.0F));
      if (var5.maxBiteDef > 0) {
         this.biteDefense = (int)Math.max(1.0F, var5.maxBiteDef * (var2 / 10.0F));
      }
   }

    void save(ByteBuffer var1, bool var2) {
      var1.put((byte)this.tailorLvl);
      var1.put((byte)this.fabricType);
      var1.put((byte)this.scratchDefense);
      var1.put((byte)this.biteDefense);
      var1.put((byte)(this.hasHole ? 1 : 0));
      var1.putShort((short)this.conditionGain);
   }

    void load(ByteBuffer var1, int var2) {
      this.tailorLvl = var1.get();
      if (var2 < 178) {
         this.fabricType = var1.getShort();
      } else {
         this.fabricType = var1.get();
      }

      this.scratchDefense = var1.get();
      this.biteDefense = var1.get();
      this.hasHole = var1.get() == 1;
      this.conditionGain = var1.getShort();
   }

    void save_old(ByteBuffer var1, bool var2) {
      var1.putInt(this.tailorLvl);
      var1.putInt(this.fabricType);
      var1.putInt(this.scratchDefense);
      var1.putInt(this.biteDefense);
      var1.put((byte)(this.hasHole ? 1 : 0));
      var1.putInt(this.conditionGain);
   }

    void load_old(ByteBuffer var1, int var2, bool var3) {
      this.tailorLvl = var1.getInt();
      this.fabricType = var1.getInt();
      this.scratchDefense = var1.getInt();
      this.biteDefense = var1.getInt();
      this.hasHole = var1.get() == 1;
      this.conditionGain = var1.getInt();
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
