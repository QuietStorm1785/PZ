#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/set/hash/THashSet.h"
#include "zombie/iso/IsoGridOcclusionData/OcclusionFilter.h"
#include "zombie/iso/areas/IsoBuilding.h"

namespace zombie {
namespace iso {


class IsoGridOcclusionData {
public:
    static const int MAXBUILDINGOCCLUDERS = 3;
   private static const THashSet<IsoBuilding> _leftBuildings = std::make_shared<THashSet>(3);
   private static const THashSet<IsoBuilding> _rightBuildings = std::make_shared<THashSet>(3);
   private static const THashSet<IsoBuilding> _allBuildings = std::make_shared<THashSet>(3);
    static int _ObjectEpoch = 0;
   private const std::vector<IsoBuilding> _leftBuildingsArray = new std::vector<>(3);
   private const std::vector<IsoBuilding> _rightBuildingsArray = new std::vector<>(3);
   private const std::vector<IsoBuilding> _allBuildingsArray = new std::vector<>(3);
    IsoGridSquare _ownerSquare = nullptr;
    bool _bSoftInitialized = false;
    bool _bLeftOccludedByOrphanStructures = false;
    bool _bRightOccludedByOrphanStructures = false;
    int _objectEpoch = -1;

    public IsoGridOcclusionData(IsoGridSquare var1) {
      this._ownerSquare = var1;
   }

    static void SquareChanged() {
      _ObjectEpoch++;
      if (_ObjectEpoch < 0) {
         _ObjectEpoch = 0;
      }
   }

    void Reset() {
      this._bSoftInitialized = false;
      this._bLeftOccludedByOrphanStructures = false;
      this._bRightOccludedByOrphanStructures = false;
      this._allBuildingsArray.clear();
      this._leftBuildingsArray.clear();
      this._rightBuildingsArray.clear();
      this._objectEpoch = -1;
   }

    bool getCouldBeOccludedByOrphanStructures(OcclusionFilter var1) {
      if (this._objectEpoch != _ObjectEpoch) {
         if (this._bSoftInitialized) {
            this.Reset();
         }

         this._objectEpoch = _ObjectEpoch;
      }

      if (!this._bSoftInitialized) {
         this.LazyInitializeSoftOccluders();
      }

      if (var1 == OcclusionFilter.Left) {
         return this._bLeftOccludedByOrphanStructures;
      } else {
         return var1 == OcclusionFilter.Right
            ? this._bRightOccludedByOrphanStructures
            : this._bLeftOccludedByOrphanStructures || this._bRightOccludedByOrphanStructures;
      }
   }

   public std::vector<IsoBuilding> getBuildingsCouldBeOccluders(OcclusionFilter var1) {
      if (this._objectEpoch != _ObjectEpoch) {
         if (this._bSoftInitialized) {
            this.Reset();
         }

         this._objectEpoch = _ObjectEpoch;
      }

      if (!this._bSoftInitialized) {
         this.LazyInitializeSoftOccluders();
      }

      if (var1 == OcclusionFilter.Left) {
         return this._leftBuildingsArray;
      } else {
    return var1 = = OcclusionFilter.Right ? this._rightBuildingsArray : this._allBuildingsArray;
      }
   }

    void LazyInitializeSoftOccluders() {
    bool var1 = false;
    int var2 = this._ownerSquare.getX();
    int var3 = this._ownerSquare.getY();
    int var4 = this._ownerSquare.getZ();
      _allBuildings.clear();
      _leftBuildings.clear();
      _rightBuildings.clear();
      var1 |= this.GetBuildingFloorsProjectedOnSquare(_allBuildings, var2, var3, var4);
      var1 |= this.GetBuildingFloorsProjectedOnSquare(_allBuildings, var2 + 1, var3 + 1, var4);
      var1 |= this.GetBuildingFloorsProjectedOnSquare(_allBuildings, var2 + 2, var3 + 2, var4);
      var1 |= this.GetBuildingFloorsProjectedOnSquare(_allBuildings, var2 + 3, var3 + 3, var4);
      this._bLeftOccludedByOrphanStructures = this._bLeftOccludedByOrphanStructures
         | this.GetBuildingFloorsProjectedOnSquare(_leftBuildings, var2, var3 + 1, var4);
      this._bLeftOccludedByOrphanStructures = this._bLeftOccludedByOrphanStructures
         | this.GetBuildingFloorsProjectedOnSquare(_leftBuildings, var2 + 1, var3 + 2, var4);
      this._bLeftOccludedByOrphanStructures = this._bLeftOccludedByOrphanStructures
         | this.GetBuildingFloorsProjectedOnSquare(_leftBuildings, var2 + 2, var3 + 3, var4);
      this._bRightOccludedByOrphanStructures = this._bRightOccludedByOrphanStructures
         | this.GetBuildingFloorsProjectedOnSquare(_rightBuildings, var2 + 1, var3, var4);
      this._bRightOccludedByOrphanStructures = this._bRightOccludedByOrphanStructures
         | this.GetBuildingFloorsProjectedOnSquare(_rightBuildings, var2 + 2, var3 + 1, var4);
      this._bRightOccludedByOrphanStructures = this._bRightOccludedByOrphanStructures
         | this.GetBuildingFloorsProjectedOnSquare(_rightBuildings, var2 + 3, var3 + 2, var4);
      this._bLeftOccludedByOrphanStructures |= var1;
      _leftBuildings.addAll(_allBuildings);
      this._bRightOccludedByOrphanStructures |= var1;
      _rightBuildings.addAll(_allBuildings);
      _allBuildings.clear();
      _allBuildings.addAll(_leftBuildings);
      _allBuildings.addAll(_rightBuildings);
      this._leftBuildingsArray.addAll(_leftBuildings);
      this._rightBuildingsArray.addAll(_rightBuildings);
      this._allBuildingsArray.addAll(_allBuildings);
      this._bSoftInitialized = true;
   }

    bool GetBuildingFloorsProjectedOnSquare(THashSet<IsoBuilding> var1, int var2, int var3, int var4) {
    bool var5 = false;
    int var6 = var2;
    int var7 = var3;

      for (int var8 = var4; var8 < IsoCell.MaxHeight; var7 += 3) {
    IsoGridSquare var9 = IsoWorld.instance.CurrentCell.getGridSquare(var6, var7, var8);
         if (var9 != nullptr) {
    IsoBuilding var10 = var9.getBuilding();
            if (var10 == nullptr) {
               var10 = var9.roofHideBuilding;
            }

            if (var10 != nullptr) {
               var1.push_back(var10);
            }

            for (int var11 = var8 - 1; var11 >= 0 && var10 == nullptr; var11--) {
    IsoGridSquare var12 = IsoWorld.instance.CurrentCell.getGridSquare(var6, var7, var11);
               if (var12 != nullptr) {
                  var10 = var12.getBuilding();
                  if (var10 == nullptr) {
                     var10 = var12.roofHideBuilding;
                  }

                  if (var10 != nullptr) {
                     var1.push_back(var10);
                  }
               }
            }

            if (var10 == nullptr && !var5 && var9.getZ() != 0 && var9.getPlayerBuiltFloor() != nullptr) {
               var5 = true;
            }
         }

         var8++;
         var6 += 3;
      }

    return var5;
   }
}
} // namespace iso
} // namespace zombie
