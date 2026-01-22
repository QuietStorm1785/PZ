#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoDirections/1.h"

namespace zombie {
namespace iso {


enum class IsoDirections {
   N(0),
   NW(1),
   W(2),
   SW(3),
   S(4),
   SE(5),
   E(6),
   NE(7),
   Max(8);

   private static const IsoDirections[] VALUES = values();
   private static IsoDirections[][] directionLookup;
    static const Vector2 temp = std::make_shared<Vector2>();
    const int index;

    private IsoDirections(int var3) {
      this.index = var3;
   }

    static IsoDirections fromIndex(int var0) {
      while (var0 < 0) {
         var0 += 8;
      }

      var0 %= 8;
      return VALUES[var0];
   }

    IsoDirections RotLeft(int var1) {
    IsoDirections var2 = RotLeft(this);

      for (int var3 = 0; var3 < var1 - 1; var3++) {
         var2 = RotLeft(var2);
      }

    return var2;
   }

    IsoDirections RotRight(int var1) {
    IsoDirections var2 = RotRight(this);

      for (int var3 = 0; var3 < var1 - 1; var3++) {
         var2 = RotRight(var2);
      }

    return var2;
   }

    IsoDirections RotLeft() {
    return RotLeft();
   }

    IsoDirections RotRight() {
    return RotRight();
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static IsoDirections RotLeft(IsoDirections var0) {
      switch (1.$SwitchMap$zombie$iso$IsoDirections[var0.ordinal()]) {
         case 1:
    return N;
         case 2:
    return NW;
         case 3:
    return W;
         case 4:
    return SW;
         case 5:
    return S;
         case 6:
    return SE;
         case 7:
    return E;
         case 8:
    return NE;
         default:
    return Max;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static IsoDirections RotRight(IsoDirections var0) {
      switch (1.$SwitchMap$zombie$iso$IsoDirections[var0.ordinal()]) {
         case 1:
    return E;
         case 2:
    return NE;
         case 3:
    return N;
         case 4:
    return NW;
         case 5:
    return W;
         case 6:
    return SW;
         case 7:
    return S;
         case 8:
    return SE;
         default:
    return Max;
      }
   }

    static void generateTables() {
      directionLookup = new IsoDirections[200][200];

      for (int var0 = 0; var0 < 200; var0++) {
         for (int var1 = 0; var1 < 200; var1++) {
    int var2 = var0 - 100;
    int var3 = var1 - 100;
    float var4 = var2 / 100.0F;
    float var5 = var3 / 100.0F;
    Vector2 var6 = std::make_shared<Vector2>(var4, var5);
            var6.normalize();
            directionLookup[var0][var1] = fromAngleActual(var6);
         }
      }
   }

    static IsoDirections fromAngleActual(Vector2 var0) {
      temp.x = var0.x;
      temp.y = var0.y;
      temp.normalize();
    float var1 = temp.getDirectionNeg();
    float var2 = (float) (Math.PI / 4);
    float var3 = (float) (Math.PI * 2);
      var3 = (float)(var3 + Math.toRadians(112.5));

      for (int var4 = 0; var4 < 8; var4++) {
         var3 += var2;
         if (var1 >= var3 && var1 <= var3 + var2
            || var1 + (float) (Math.PI * 2) >= var3 && var1 + (float) (Math.PI * 2) <= var3 + var2
            || var1 - (float) (Math.PI * 2) >= var3 && var1 - (float) (Math.PI * 2) <= var3 + var2) {
    return fromIndex();
         }

         if (var3 > Math.PI * 2) {
            var3 = (float)(var3 - (Math.PI * 2));
         }
      }

      if (temp.x > 0.5F) {
         if (temp.y < -0.5F) {
    return NE;
         } else {
            return temp.y > 0.5F ? SE : E;
         }
      } else if (temp.x < -0.5F) {
         if (temp.y < -0.5F) {
    return NW;
         } else {
            return temp.y > 0.5F ? SW : W;
         }
      } else if (temp.y < -0.5F) {
    return N;
      } else {
         return temp.y > 0.5F ? S : N;
      }
   }

    static IsoDirections fromAngle(float var0) {
    float var1 = (float)Math.cos(var0);
    float var2 = (float)Math.sin(var0);
    return fromAngle();
   }

    static IsoDirections fromAngle(Vector2 var0) {
    return fromAngle();
   }

    static IsoDirections fromAngle(float var0, float var1) {
      temp.x = var0;
      temp.y = var1;
      if (temp.getLengthSquared() != 1.0F) {
         temp.normalize();
      }

      if (directionLookup == nullptr) {
         generateTables();
      }

    int var2 = (int)((temp.x + 1.0F) * 100.0F);
    int var3 = (int)((temp.y + 1.0F) * 100.0F);
      if (var2 >= 200) {
         var2 = 199;
      }

      if (var3 >= 200) {
         var3 = 199;
      }

      if (var2 < 0) {
         var2 = 0;
      }

      if (var3 < 0) {
         var3 = 0;
      }

      return directionLookup[var2][var3];
   }

    static IsoDirections cardinalFromAngle(Vector2 var0) {
    bool var1 = var0.getX() >= var0.getY();
    bool var2 = var0.getX() > -var0.getY();
      if (var1) {
         return var2 ? E : N;
      } else {
         return var2 ? S : W;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static IsoDirections reverse(IsoDirections var0) {
      switch (1.$SwitchMap$zombie$iso$IsoDirections[var0.ordinal()]) {
         case 1:
    return SW;
         case 2:
    return S;
         case 3:
    return SE;
         case 4:
    return E;
         case 5:
    return NE;
         case 6:
    return N;
         case 7:
    return NW;
         case 8:
    return W;
         default:
    return Max;
      }
   }

    int index() {
      return this.index % 8;
   }

    std::string toCompassString() {
      switch (this.index) {
         case 0:
            return "9";
         case 1:
            return "8";
         case 2:
            return "7";
         case 3:
            return "4";
         case 4:
            return "1";
         case 5:
            return "2";
         case 6:
            return "3";
         case 7:
            return "6";
         default:
            return "";
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    Vector2 ToVector() {
      switch (1.$SwitchMap$zombie$iso$IsoDirections[this.ordinal()]) {
         case 1:
            temp.x = 1.0F;
            temp.y = -1.0F;
            break;
         case 2:
            temp.x = 0.0F;
            temp.y = -1.0F;
            break;
         case 3:
            temp.x = -1.0F;
            temp.y = -1.0F;
            break;
         case 4:
            temp.x = -1.0F;
            temp.y = 0.0F;
            break;
         case 5:
            temp.x = -1.0F;
            temp.y = 1.0F;
            break;
         case 6:
            temp.x = 0.0F;
            temp.y = 1.0F;
            break;
         case 7:
            temp.x = 1.0F;
            temp.y = 1.0F;
            break;
         case 8:
            temp.x = 1.0F;
            temp.y = 0.0F;
      }

      temp.normalize();
    return temp;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    float toAngle() {
    float var1 = (float) (Math.PI / 4);
      switch (1.$SwitchMap$zombie$iso$IsoDirections[this.ordinal()]) {
         case 1:
            return var1 * 7.0F;
         case 2:
            return var1 * 0.0F;
         case 3:
            return var1 * 1.0F;
         case 4:
            return var1 * 2.0F;
         case 5:
            return var1 * 3.0F;
         case 6:
            return var1 * 4.0F;
         case 7:
            return var1 * 5.0F;
         case 8:
            return var1 * 6.0F;
         default:
            return 0.0F;
      }
   }

    static IsoDirections getRandom() {
    return fromIndex();
   }
}
} // namespace iso
} // namespace zombie
