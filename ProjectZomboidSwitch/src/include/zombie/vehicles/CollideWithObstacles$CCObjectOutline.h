#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/CollideWithObstacles/CCNode.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class CollideWithObstacles {
public:
    int x;
    int y;
    int z;
    bool nw;
    bool nw_w;
    bool nw_n;
    bool nw_e;
    bool nw_s;
    bool w_w;
    bool w_e;
    bool w_cutoff;
    bool n_n;
    bool n_s;
    bool n_cutoff;
   std::vector<CCNode> nodes;
   static ArrayDeque<CollideWithObstacles$CCObjectOutline> pool = std::make_unique<ArrayDeque<>>();

   private CollideWithObstacles$CCObjectOutline() {
   }

   CollideWithObstacles$CCObjectOutline init(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.nw = this.nw_w = this.nw_n = this.nw_e = false;
      this.w_w = this.w_e = this.w_cutoff = false;
      this.n_n = this.n_s = this.n_cutoff = false;
    return this;
   }

    static void setSolid(int var0, int var1, int var2, CollideWithObstacles$CCObjectOutline[][] var3) {
      setWest(var0, var1, var2, var3);
      setNorth(var0, var1, var2, var3);
      setWest(var0 + 1, var1, var2, var3);
      setNorth(var0, var1 + 1, var2, var3);
   }

    static void setWest(int var0, int var1, int var2, CollideWithObstacles$CCObjectOutline[][] var3) {
      CollideWithObstacles$CCObjectOutline var4 = get(var0, var1, var2, var3);
      if (var4 != nullptr) {
         if (var4.nw) {
            var4.nw_s = false;
         } else {
            var4.nw = true;
            var4.nw_w = true;
            var4.nw_n = true;
            var4.nw_e = true;
            var4.nw_s = false;
         }

         var4.w_w = true;
         var4.w_e = true;
      }

      var4 = get(var0, var1 + 1, var2, var3);
      if (var4 == nullptr) {
         if (var4 != nullptr) {
            var4.w_cutoff = true;
         }
      } else if (var4.nw) {
         var4.nw_n = false;
      } else {
         var4.nw = true;
         var4.nw_n = false;
         var4.nw_w = true;
         var4.nw_e = true;
         var4.nw_s = true;
      }
   }

    static void setNorth(int var0, int var1, int var2, CollideWithObstacles$CCObjectOutline[][] var3) {
      CollideWithObstacles$CCObjectOutline var4 = get(var0, var1, var2, var3);
      if (var4 != nullptr) {
         if (var4.nw) {
            var4.nw_e = false;
         } else {
            var4.nw = true;
            var4.nw_w = true;
            var4.nw_n = true;
            var4.nw_e = false;
            var4.nw_s = true;
         }

         var4.n_n = true;
         var4.n_s = true;
      }

      var4 = get(var0 + 1, var1, var2, var3);
      if (var4 == nullptr) {
         if (var4 != nullptr) {
            var4.n_cutoff = true;
         }
      } else if (var4.nw) {
         var4.nw_w = false;
      } else {
         var4.nw = true;
         var4.nw_n = true;
         var4.nw_w = false;
         var4.nw_e = true;
         var4.nw_s = true;
      }
   }

   static CollideWithObstacles$CCObjectOutline get(int var0, int var1, int var2, CollideWithObstacles$CCObjectOutline[][] var3) {
      if (var0 < 0 || var0 >= var3.length) {
    return nullptr;
      } else if (var1 >= 0 && var1 < var3[0].length) {
         if (var3[var0][var1] == nullptr) {
            var3[var0][var1] = alloc().init(var0, var1, var2);
         }

         return var3[var0][var1];
      } else {
    return nullptr;
      }
   }

    void trace_NW_N(CollideWithObstacles$CCObjectOutline[][] var1, CCNode var2) {
      if (var2 != nullptr) {
         var2.setXY(this.x + 0.3F, this.y - 0.3F);
      } else {
    CCNode var3 = CCNode.alloc().init(this.x + 0.3F, this.y - 0.3F, this.z);
         this.nodes.push_back(var3);
      }

      this.nw_n = false;
      if (this.nw_e) {
         this.trace_NW_E(var1, nullptr);
      } else if (this.n_n) {
         this.trace_N_N(var1, this.nodes.get(this.nodes.size() - 1));
      }
   }

    void trace_NW_S(CollideWithObstacles$CCObjectOutline[][] var1, CCNode var2) {
      if (var2 != nullptr) {
         var2.setXY(this.x - 0.3F, this.y + 0.3F);
      } else {
    CCNode var3 = CCNode.alloc().init(this.x - 0.3F, this.y + 0.3F, this.z);
         this.nodes.push_back(var3);
      }

      this.nw_s = false;
      if (this.nw_w) {
         this.trace_NW_W(var1, nullptr);
      } else {
         CollideWithObstacles$CCObjectOutline var4 = get(this.x - 1, this.y, this.z, var1);
         if (var4 == nullptr) {
            return;
         }

         if (var4.n_s) {
            var4.nodes = this.nodes;
            var4.trace_N_S(var1, this.nodes.get(this.nodes.size() - 1));
         }
      }
   }

    void trace_NW_W(CollideWithObstacles$CCObjectOutline[][] var1, CCNode var2) {
      if (var2 != nullptr) {
         var2.setXY(this.x - 0.3F, this.y - 0.3F);
      } else {
    CCNode var3 = CCNode.alloc().init(this.x - 0.3F, this.y - 0.3F, this.z);
         this.nodes.push_back(var3);
      }

      this.nw_w = false;
      if (this.nw_n) {
         this.trace_NW_N(var1, nullptr);
      } else {
         CollideWithObstacles$CCObjectOutline var4 = get(this.x, this.y - 1, this.z, var1);
         if (var4 == nullptr) {
            return;
         }

         if (var4.w_w) {
            var4.nodes = this.nodes;
            var4.trace_W_W(var1, this.nodes.get(this.nodes.size() - 1));
         }
      }
   }

    void trace_NW_E(CollideWithObstacles$CCObjectOutline[][] var1, CCNode var2) {
      if (var2 != nullptr) {
         var2.setXY(this.x + 0.3F, this.y + 0.3F);
      } else {
    CCNode var3 = CCNode.alloc().init(this.x + 0.3F, this.y + 0.3F, this.z);
         this.nodes.push_back(var3);
      }

      this.nw_e = false;
      if (this.nw_s) {
         this.trace_NW_S(var1, nullptr);
      } else if (this.w_e) {
         this.trace_W_E(var1, this.nodes.get(this.nodes.size() - 1));
      }
   }

    void trace_W_E(CollideWithObstacles$CCObjectOutline[][] var1, CCNode var2) {
      if (var2 != nullptr) {
         var2.setXY(this.x + 0.3F, this.y + 1 - 0.3F);
      } else {
    CCNode var3 = CCNode.alloc().init(this.x + 0.3F, this.y + 1 - 0.3F, this.z);
         this.nodes.push_back(var3);
      }

      this.w_e = false;
      if (this.w_cutoff) {
    CCNode var5 = this.nodes.get(this.nodes.size() - 1);
         var5.setXY(this.x + 0.3F, this.y + 1 + 0.3F);
         var5 = CCNode.alloc().init(this.x - 0.3F, this.y + 1 + 0.3F, this.z);
         this.nodes.push_back(var5);
         var5 = CCNode.alloc().init(this.x - 0.3F, this.y + 1 - 0.3F, this.z);
         this.nodes.push_back(var5);
         this.trace_W_W(var1, var5);
      } else {
         CollideWithObstacles$CCObjectOutline var4 = get(this.x, this.y + 1, this.z, var1);
         if (var4 != nullptr) {
            if (var4.nw && var4.nw_e) {
               var4.nodes = this.nodes;
               var4.trace_NW_E(var1, this.nodes.get(this.nodes.size() - 1));
            } else if (var4.n_n) {
               var4.nodes = this.nodes;
               var4.trace_N_N(var1, nullptr);
            }
         }
      }
   }

    void trace_W_W(CollideWithObstacles$CCObjectOutline[][] var1, CCNode var2) {
      if (var2 != nullptr) {
         var2.setXY(this.x - 0.3F, this.y + 0.3F);
      } else {
    CCNode var3 = CCNode.alloc().init(this.x - 0.3F, this.y + 0.3F, this.z);
         this.nodes.push_back(var3);
      }

      this.w_w = false;
      if (this.nw_w) {
         this.trace_NW_W(var1, this.nodes.get(this.nodes.size() - 1));
      } else {
         CollideWithObstacles$CCObjectOutline var4 = get(this.x - 1, this.y, this.z, var1);
         if (var4 == nullptr) {
            return;
         }

         if (var4.n_s) {
            var4.nodes = this.nodes;
            var4.trace_N_S(var1, nullptr);
         }
      }
   }

    void trace_N_N(CollideWithObstacles$CCObjectOutline[][] var1, CCNode var2) {
      if (var2 != nullptr) {
         var2.setXY(this.x + 1 - 0.3F, this.y - 0.3F);
      } else {
    CCNode var3 = CCNode.alloc().init(this.x + 1 - 0.3F, this.y - 0.3F, this.z);
         this.nodes.push_back(var3);
      }

      this.n_n = false;
      if (this.n_cutoff) {
    CCNode var6 = this.nodes.get(this.nodes.size() - 1);
         var6.setXY(this.x + 1 + 0.3F, this.y - 0.3F);
         var6 = CCNode.alloc().init(this.x + 1 + 0.3F, this.y + 0.3F, this.z);
         this.nodes.push_back(var6);
         var6 = CCNode.alloc().init(this.x + 1 - 0.3F, this.y + 0.3F, this.z);
         this.nodes.push_back(var6);
         this.trace_N_S(var1, var6);
      } else {
         CollideWithObstacles$CCObjectOutline var4 = get(this.x + 1, this.y, this.z, var1);
         if (var4 != nullptr) {
            if (var4.nw_n) {
               var4.nodes = this.nodes;
               var4.trace_NW_N(var1, this.nodes.get(this.nodes.size() - 1));
            } else {
               var4 = get(this.x + 1, this.y - 1, this.z, var1);
               if (var4 == nullptr) {
                  return;
               }

               if (var4.w_w) {
                  var4.nodes = this.nodes;
                  var4.trace_W_W(var1, nullptr);
               }
            }
         }
      }
   }

    void trace_N_S(CollideWithObstacles$CCObjectOutline[][] var1, CCNode var2) {
      if (var2 != nullptr) {
         var2.setXY(this.x + 0.3F, this.y + 0.3F);
      } else {
    CCNode var3 = CCNode.alloc().init(this.x + 0.3F, this.y + 0.3F, this.z);
         this.nodes.push_back(var3);
      }

      this.n_s = false;
      if (this.nw_s) {
         this.trace_NW_S(var1, this.nodes.get(this.nodes.size() - 1));
      } else if (this.w_e) {
         this.trace_W_E(var1, nullptr);
      }
   }

    void trace(CollideWithObstacles$CCObjectOutline[][] var1, std::vector<CCNode> var2) {
      var2.clear();
      this.nodes = var2;
    CCNode var3 = CCNode.alloc().init(this.x - 0.3F, this.y - 0.3F, this.z);
      var2.push_back(var3);
      this.trace_NW_N(var1, nullptr);
      if (var2.size() != 2 && var3.x == ((CCNode)var2.get(var2.size() - 1)).x && var3.y == ((CCNode)var2.get(var2.size() - 1)).y) {
         ((CCNode)var2.get(var2.size() - 1)).release();
         var2.set(var2.size() - 1, var3);
      } else {
         var2.clear();
      }
   }

   static CollideWithObstacles$CCObjectOutline alloc() {
      return pool.empty() ? new CollideWithObstacles$CCObjectOutline() : pool.pop();
   }

    void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw std::make_unique<AssertionError>();
      } else {
         pool.push(this);
      }
   }
}
} // namespace vehicles
} // namespace zombie
