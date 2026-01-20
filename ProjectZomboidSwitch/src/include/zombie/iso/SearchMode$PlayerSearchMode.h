#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/SearchMode/SearchModeFloat.h"

namespace zombie {
namespace iso {


class SearchMode {
public:
    const int plrIndex;
    const SearchMode parent;
    bool override = false;
    bool enabled = false;
    const SearchModeFloat radius = std::make_shared<SearchModeFloat>(0.0F, 50.0F, 1.0F);
    const SearchModeFloat gradientWidth = std::make_shared<SearchModeFloat>(0.0F, 20.0F, 1.0F);
    const SearchModeFloat blur = std::make_shared<SearchModeFloat>(0.0F, 1.0F, 0.01F);
    const SearchModeFloat desat = std::make_shared<SearchModeFloat>(0.0F, 1.0F, 0.01F);
    const SearchModeFloat darkness = std::make_shared<SearchModeFloat>(0.0F, 1.0F, 0.01F);
    float timer;
    bool doFadeOut;
    bool doFadeIn;

   public SearchMode$PlayerSearchMode(int var1, SearchMode var2) {
      this.plrIndex = var1;
      this.parent = var2;
   }

    bool isShaderEnabled() {
      return this.enabled || this.doFadeIn || this.doFadeOut;
   }

    bool isPlayerExterior() {
    IsoPlayer var1 = IsoPlayer.players[this.plrIndex];
      return var1 != nullptr && var1.getCurrentSquare() != nullptr && !var1.getCurrentSquare().isInARoom();
   }

    float getShaderBlur() {
      return this.isPlayerExterior() ? this.blur.getExterior() : this.blur.getInterior();
   }

    float getShaderDesat() {
      return this.isPlayerExterior() ? this.desat.getExterior() : this.desat.getInterior();
   }

    float getShaderRadius() {
      return this.isPlayerExterior() ? this.radius.getExterior() : this.radius.getInterior();
   }

    float getShaderGradientWidth() {
      return this.isPlayerExterior() ? this.gradientWidth.getExterior() : this.gradientWidth.getInterior();
   }

    float getShaderDarkness() {
      return this.isPlayerExterior() ? this.darkness.getExterior() : this.darkness.getInterior();
   }

    SearchModeFloat getBlur() {
      return this.blur;
   }

    SearchModeFloat getDesat() {
      return this.desat;
   }

    SearchModeFloat getRadius() {
      return this.radius;
   }

    SearchModeFloat getGradientWidth() {
      return this.gradientWidth;
   }

    SearchModeFloat getDarkness() {
      return this.darkness;
   }

    void update() {
      if (!this.override) {
         if (this.doFadeIn) {
            this.timer = this.timer + GameTime.getInstance().getTimeDelta();
            this.timer = PZMath.clamp(this.timer, 0.0F, this.parent.fadeTime);
    float var2 = PZMath.clamp(this.timer / this.parent.fadeTime, 0.0F, 1.0F);
            this.blur.update(var2);
            this.desat.update(var2);
            this.radius.update(var2);
            this.darkness.update(var2);
            this.gradientWidth.equalise();
            if (this.timer >= this.parent.fadeTime) {
               this.doFadeIn = false;
            }
         } else if (this.doFadeOut) {
            this.timer = this.timer - GameTime.getInstance().getTimeDelta();
            this.timer = PZMath.clamp(this.timer, 0.0F, this.parent.fadeTime);
    float var1 = PZMath.clamp(this.timer / this.parent.fadeTime, 0.0F, 1.0F);
            this.blur.update(var1);
            this.desat.update(var1);
            this.radius.update(var1);
            this.darkness.update(var1);
            this.gradientWidth.equalise();
            if (this.timer <= 0.0F) {
               this.doFadeOut = false;
            }
         } else {
            if (this.enabled) {
               this.blur.equalise();
               this.desat.equalise();
               this.radius.equalise();
               this.darkness.equalise();
               this.gradientWidth.equalise();
            } else {
               this.blur.reset();
               this.desat.reset();
               this.radius.reset();
               this.darkness.reset();
               this.gradientWidth.equalise();
            }
         }
      }
   }
}
} // namespace iso
} // namespace zombie
