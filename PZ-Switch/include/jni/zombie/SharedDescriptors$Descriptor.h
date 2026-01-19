#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {


class SharedDescriptors {
:
    int ID = 0;
    int persistentOutfitID = 0;
    std::string outfitName;
    const HumanVisual humanVisual = new HumanVisual(this);
    const ItemVisuals itemVisuals = new ItemVisuals();
    bool bFemale = false;
    bool bZombie = false;

    int getID() const {
      return this.ID;
   }

    int getPersistentOutfitID() const {
      return this.persistentOutfitID;
   }

    HumanVisual getHumanVisual() const {
      return this.humanVisual;
   }

    void getItemVisuals(ItemVisuals var1) {
      var1.clear();
      var1.addAll(this.itemVisuals);
   }

    bool isFemale() {
      return this.bFemale;
   }

    bool isZombie() {
      return this.bZombie;
   }

    bool isSkeleton() {
    return false;
   }

    void save(ByteBuffer var1) {
    uint8_t var2 = 0;
      if (this.bFemale) {
         var2 = (byte)(var2 | 1);
      }

      if (this.bZombie) {
         var2 = (byte)(var2 | 2);
      }

      var1.put(var2);
      var1.putInt(this.ID);
      var1.putInt(this.persistentOutfitID);
      GameWindow.WriteStringUTF(var1, this.outfitName);
      this.humanVisual.save(var1);
      this.itemVisuals.save(var1);
   }

    void load(ByteBuffer var1, int var2) {
      this.humanVisual.clear();
      this.itemVisuals.clear();
    uint8_t var3 = var1.get();
      this.bFemale = (var3 & 1) != 0;
      this.bZombie = (var3 & 2) != 0;
      this.ID = var1.getInt();
      this.persistentOutfitID = var1.getInt();
      this.outfitName = GameWindow.ReadStringUTF(var1);
      this.humanVisual.load(var1, var2);
    short var4 = var1.getShort();

      for (int var5 = 0; var5 < var4; var5++) {
    ItemVisual var6 = new ItemVisual();
         var6.load(var1, var2);
         this.itemVisuals.add(var6);
      }
   }
}
} // namespace zombie
