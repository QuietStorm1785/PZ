#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"

namespace zombie {
namespace ai {


class MapKnowledge {
public:
   private const std::vector<KnownBlockedEdges> knownBlockedEdges = std::make_unique<std::vector<>>();

   public std::vector<KnownBlockedEdges> getKnownBlockedEdges() {
      return this.knownBlockedEdges;
   }

    KnownBlockedEdges getKnownBlockedEdges(int var1, int var2, int var3) {
      for (int var4 = 0; var4 < this.knownBlockedEdges.size(); var4++) {
    KnownBlockedEdges var5 = this.knownBlockedEdges.get(var4);
         if (var5.x == var1 && var5.y == var2 && var5.z == var3) {
    return var5;
         }
      }

    return nullptr;
   }

    KnownBlockedEdges createKnownBlockedEdges(int var1, int var2, int var3) {
      assert this.getKnownBlockedEdges(var1, var2, var3) == nullptr;

    KnownBlockedEdges var4 = KnownBlockedEdges.alloc();
      var4.init(var1, var2, var3);
      this.knownBlockedEdges.push_back(var4);
    return var4;
   }

    KnownBlockedEdges getOrCreateKnownBlockedEdges(int var1, int var2, int var3) {
    KnownBlockedEdges var4 = this.getKnownBlockedEdges(var1, var2, var3);
      if (var4 == nullptr) {
         var4 = this.createKnownBlockedEdges(var1, var2, var3);
      }

    return var4;
   }

    void releaseIfEmpty(KnownBlockedEdges var1) {
      if (!var1.n && !var1.w) {
         this.knownBlockedEdges.remove(var1);
         var1.release();
      }
   }

    void setKnownBlockedEdgeW(int var1, int var2, int var3, bool var4) {
    KnownBlockedEdges var5 = this.getOrCreateKnownBlockedEdges(var1, var2, var3);
      var5.w = var4;
      this.releaseIfEmpty(var5);
   }

    void setKnownBlockedEdgeN(int var1, int var2, int var3, bool var4) {
    KnownBlockedEdges var5 = this.getOrCreateKnownBlockedEdges(var1, var2, var3);
      var5.n = var4;
      this.releaseIfEmpty(var5);
   }

    void setKnownBlockedDoor(IsoDoor var1, bool var2) {
    IsoGridSquare var3 = var1.getSquare();
      if (var1.getNorth()) {
         this.setKnownBlockedEdgeN(var3.x, var3.y, var3.z, var2);
      } else {
         this.setKnownBlockedEdgeW(var3.x, var3.y, var3.z, var2);
      }
   }

    void setKnownBlockedDoor(IsoThumpable var1, bool var2) {
      if (var1.isDoor()) {
    IsoGridSquare var3 = var1.getSquare();
         if (var1.getNorth()) {
            this.setKnownBlockedEdgeN(var3.x, var3.y, var3.z, var2);
         } else {
            this.setKnownBlockedEdgeW(var3.x, var3.y, var3.z, var2);
         }
      }
   }

    void setKnownBlockedWindow(IsoWindow var1, bool var2) {
    IsoGridSquare var3 = var1.getSquare();
      if (var1.getNorth()) {
         this.setKnownBlockedEdgeN(var3.x, var3.y, var3.z, var2);
      } else {
         this.setKnownBlockedEdgeW(var3.x, var3.y, var3.z, var2);
      }
   }

    void setKnownBlockedWindowFrame(IsoObject var1, bool var2) {
    IsoGridSquare var3 = var1.getSquare();
      if (IsoWindowFrame.isWindowFrame(var1, true)) {
         this.setKnownBlockedEdgeN(var3.x, var3.y, var3.z, var2);
      } else if (IsoWindowFrame.isWindowFrame(var1, false)) {
         this.setKnownBlockedEdgeW(var3.x, var3.y, var3.z, var2);
      }
   }

    void forget() {
      KnownBlockedEdges.releaseAll(this.knownBlockedEdges);
      this.knownBlockedEdges.clear();
   }
}
} // namespace ai
} // namespace zombie
