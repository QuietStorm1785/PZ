#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoGridSquare/ILighting.h"
#include "zombie/iso/IsoGridSquare/ResultLight.h"

namespace zombie {
namespace network {


class ServerLOS {
public:
    static const uint8_t LOS_SEEN = 1;
    static const uint8_t LOS_COULD_SEE = 2;
    static const uint8_t LOS_CAN_SEE = 4;
    static ColorInfo lightInfo = std::make_shared<ColorInfo>();
    uint8_t los;

    int lightverts(int var1) {
    return 0;
   }

    float lampostTotalR() {
      return 0.0F;
   }

    float lampostTotalG() {
      return 0.0F;
   }

    float lampostTotalB() {
      return 0.0F;
   }

    bool bSeen() {
      return (this.los & 1) != 0;
   }

    bool bCanSee() {
      return (this.los & 4) != 0;
   }

    bool bCouldSee() {
      return (this.los & 2) != 0;
   }

    float darkMulti() {
      return 0.0F;
   }

    float targetDarkMulti() {
      return 0.0F;
   }

    ColorInfo lightInfo() {
      lightInfo.r = 1.0F;
      lightInfo.g = 1.0F;
      lightInfo.b = 1.0F;
    return lightInfo;
   }

    void lightverts(int var1, int var2) {
   }

    void lampostTotalR(float var1) {
   }

    void lampostTotalG(float var1) {
   }

    void lampostTotalB(float var1) {
   }

    void bSeen(bool var1) {
      if (var1) {
         this.los = (byte)(this.los | 1);
      } else {
         this.los &= -2;
      }
   }

    void bCanSee(bool var1) {
      if (var1) {
         this.los = (byte)(this.los | 4);
      } else {
         this.los &= -5;
      }
   }

    void bCouldSee(bool var1) {
      if (var1) {
         this.los = (byte)(this.los | 2);
      } else {
         this.los &= -3;
      }
   }

    void darkMulti(float var1) {
   }

    void targetDarkMulti(float var1) {
   }

    int resultLightCount() {
    return 0;
   }

    ResultLight getResultLight(int var1) {
    return nullptr;
   }

    void reset() {
      this.los = 0;
   }
}
} // namespace network
} // namespace zombie
