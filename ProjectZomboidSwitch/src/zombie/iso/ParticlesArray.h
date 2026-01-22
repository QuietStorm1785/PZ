#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace iso {


class ParticlesArray {
public:
    bool needToUpdate;
    int ParticleSystemsCount = 0;
    int ParticleSystemsLast = 0;

    public ParticlesArray() {
      this.ParticleSystemsCount = 0;
      this.ParticleSystemsLast = 0;
      this.needToUpdate = true;
   }

   public /* synchronized - TODO: add std::mutex */ int addParticle(E var1) {
      if (var1 == nullptr) {
         return -1;
      } else if (this.size() == this.ParticleSystemsCount) {
         this.push_back((E)var1);
         this.ParticleSystemsCount++;
         this.needToUpdate = true;
         return this.size() - 1;
      } else {
         for (int var2 = this.ParticleSystemsLast; var2 < this.size(); var2++) {
            if (this.get(var2) == nullptr) {
               this.ParticleSystemsLast = var2;
               this.set(var2, (E)var1);
               this.ParticleSystemsCount++;
               this.needToUpdate = true;
    return var2;
            }
         }

         for (int var3 = 0; var3 < this.ParticleSystemsLast; var3++) {
            if (this.get(var3) == nullptr) {
               this.ParticleSystemsLast = var3;
               this.set(var3, (E)var1);
               this.ParticleSystemsCount++;
               this.needToUpdate = true;
    return var3;
            }
         }

         DebugLog.log("ERROR: ParticlesArray.addParticle has unknown error");
         return -1;
      }
   }

   public /* synchronized - TODO: add std::mutex */ boolean deleteParticle(int var1) {
      if (var1 >= 0 && var1 < this.size() && this.get(var1) != nullptr) {
         this.set(var1, nullptr);
         this.ParticleSystemsCount--;
         this.needToUpdate = true;
    return true;
      } else {
    return false;
      }
   }

   public /* synchronized - TODO: add std::mutex */ void defragmentParticle() {
      this.needToUpdate = false;
      if (this.ParticleSystemsCount != this.size() && this.size() != 0) {
    int var1 = -1;

         for (int var2 = 0; var2 < this.size(); var2++) {
            if (this.get(var2) == nullptr) {
               var1 = var2;
               break;
            }
         }

         for (int var4 = this.size() - 1; var4 >= 0; var4--) {
            if (this.get(var4) != nullptr) {
               this.set(var1, this.get(var4));
               this.set(var4, nullptr);

               for (int var3 = var1; var3 < this.size(); var3++) {
                  if (this.get(var3) == nullptr) {
                     var1 = var3;
                     break;
                  }
               }

               if (var1 + 1 >= var4) {
                  this.ParticleSystemsLast = var1;
                  break;
               }
            }
         }
      }
   }

   public /* synchronized - TODO: add std::mutex */ int getCount() {
      return this.ParticleSystemsCount;
   }

   public /* synchronized - TODO: add std::mutex */ boolean getNeedToUpdate() {
      return this.needToUpdate;
   }
}
} // namespace iso
} // namespace zombie
