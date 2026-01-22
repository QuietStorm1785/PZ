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
namespace iso {


class IsoGridSquare {
public:
   private const int[] lightverts = new int[8];
    float lampostTotalR = 0.0F;
    float lampostTotalG = 0.0F;
    float lampostTotalB = 0.0F;
    bool bSeen;
    bool bCanSee;
    bool bCouldSee;
    float darkMulti;
    float targetDarkMulti;
    const ColorInfo lightInfo = std::make_shared<ColorInfo>();

    int lightverts(int var1) {
      return this.lightverts[var1];
   }

    float lampostTotalR() {
      return this.lampostTotalR;
   }

    float lampostTotalG() {
      return this.lampostTotalG;
   }

    float lampostTotalB() {
      return this.lampostTotalB;
   }

    bool bSeen() {
      return this.bSeen;
   }

    bool bCanSee() {
      return this.bCanSee;
   }

    bool bCouldSee() {
      return this.bCouldSee;
   }

    float darkMulti() {
      return this.darkMulti;
   }

    float targetDarkMulti() {
      return this.targetDarkMulti;
   }

    ColorInfo lightInfo() {
      return this.lightInfo;
   }

    void lightverts(int var1, int var2) {
      this.lightverts[var1] = var2;
   }

    void lampostTotalR(float var1) {
      this.lampostTotalR = var1;
   }

    void lampostTotalG(float var1) {
      this.lampostTotalG = var1;
   }

    void lampostTotalB(float var1) {
      this.lampostTotalB = var1;
   }

    void bSeen(bool var1) {
      this.bSeen = var1;
   }

    void bCanSee(bool var1) {
      this.bCanSee = var1;
   }

    void bCouldSee(bool var1) {
      this.bCouldSee = var1;
   }

    void darkMulti(float var1) {
      this.darkMulti = var1;
   }

    void targetDarkMulti(float var1) {
      this.targetDarkMulti = var1;
   }

    int resultLightCount() {
    return 0;
   }

    ResultLight getResultLight(int var1) {
    return nullptr;
   }

    void reset() {
      this.lampostTotalR = 0.0F;
      this.lampostTotalG = 0.0F;
      this.lampostTotalB = 0.0F;
      this.bSeen = false;
      this.bCouldSee = false;
      this.bCanSee = false;
      this.targetDarkMulti = 0.0F;
      this.darkMulti = 0.0F;
      this.lightInfo.r = 0.0F;
      this.lightInfo.g = 0.0F;
      this.lightInfo.b = 0.0F;
      this.lightInfo.a = 1.0F;
   }
}
} // namespace iso
} // namespace zombie
