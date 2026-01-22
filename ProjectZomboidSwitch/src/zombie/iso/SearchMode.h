#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/SearchMode/PlayerSearchMode.h"
#include "zombie/iso/SearchMode/SearchModeFloat.h"

namespace zombie {
namespace iso {


class SearchMode {
public:
    static SearchMode instance;
    float fadeTime = 1.0F;
   private PlayerSearchMode[] plrModes = new PlayerSearchMode[4];

    static SearchMode getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<SearchMode>();
      }

    return instance;
   }

    private SearchMode() {
      for (int var1 = 0; var1 < this.plrModes.length; var1++) {
         this.plrModes[var1] = std::make_shared<PlayerSearchMode>(var1, this);
         this.plrModes[var1].blur.setTargets(1.0F, 1.0F);
         this.plrModes[var1].desat.setTargets(0.85F, 0.85F);
         this.plrModes[var1].radius.setTargets(4.0F, 4.0F);
         this.plrModes[var1].darkness.setTargets(0.0F, 0.0F);
         this.plrModes[var1].gradientWidth.setTargets(4.0F, 4.0F);
      }
   }

    PlayerSearchMode getSearchModeForPlayer(int var1) {
      return this.plrModes[var1];
   }

    float getFadeTime() {
      return this.fadeTime;
   }

    void setFadeTime(float var1) {
      this.fadeTime = var1;
   }

    bool isOverride(int var1) {
      return this.plrModes[var1].override;
   }

    void setOverride(int var1, bool var2) {
      this.plrModes[var1].override = var2;
   }

    SearchModeFloat getRadius(int var1) {
      return this.plrModes[var1].radius;
   }

    SearchModeFloat getGradientWidth(int var1) {
      return this.plrModes[var1].gradientWidth;
   }

    SearchModeFloat getBlur(int var1) {
      return this.plrModes[var1].blur;
   }

    SearchModeFloat getDesat(int var1) {
      return this.plrModes[var1].desat;
   }

    SearchModeFloat getDarkness(int var1) {
      return this.plrModes[var1].darkness;
   }

    bool isEnabled(int var1) {
      return this.plrModes[var1].enabled;
   }

    void setEnabled(int var1, bool var2) {
    PlayerSearchMode var3 = this.plrModes[var1];
      if (var2 && !var3.enabled) {
         var3.enabled = true;
         this.FadeIn(var1);
      } else if (!var2 && var3.enabled) {
         var3.enabled = false;
         this.FadeOut(var1);
      }
   }

    void FadeIn(int var1) {
    PlayerSearchMode var2 = this.plrModes[var1];
      var2.timer = Math.max(var2.timer, 0.0F);
      var2.doFadeIn = true;
      var2.doFadeOut = false;
   }

    void FadeOut(int var1) {
    PlayerSearchMode var2 = this.plrModes[var1];
      var2.timer = Math.min(var2.timer, this.fadeTime);
      var2.doFadeIn = false;
      var2.doFadeOut = true;
   }

    void update() {
      for (int var1 = 0; var1 < this.plrModes.length; var1++) {
    PlayerSearchMode var2 = this.plrModes[var1];
         var2.update();
      }
   }

    static void reset() {
      instance = nullptr;
   }
}
} // namespace iso
} // namespace zombie
