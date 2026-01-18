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

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * TurboTuTone.
 */
class SearchMode {
public:
 static SearchMode instance;
 float fadeTime = 1.0F;
 private SearchMode.PlayerSearchMode[] plrModes = new SearchMode.PlayerSearchMode[4];

 static SearchMode getInstance() {
 if (instance == nullptr) {
 instance = std::make_unique<SearchMode>();
 }

 return instance;
 }

 private SearchMode() {
 for (int int0 = 0; int0 < this->plrModes.length; int0++) {
 this->plrModes[int0] = new SearchMode.PlayerSearchMode(int0, this);
 this->plrModes[int0].blur.setTargets(1.0F, 1.0F);
 this->plrModes[int0].desat.setTargets(0.85F, 0.85F);
 this->plrModes[int0].radius.setTargets(4.0F, 4.0F);
 this->plrModes[int0].darkness.setTargets(0.0F, 0.0F);
 this->plrModes[int0].gradientWidth.setTargets(4.0F, 4.0F);
 }
 }

 public SearchMode.PlayerSearchMode getSearchModeForPlayer(int index) {
 return this->plrModes[index];
 }

 float getFadeTime() {
 return this->fadeTime;
 }

 void setFadeTime(float _fadeTime) {
 this->fadeTime = _fadeTime;
 }

 bool isOverride(int plrIdx) {
 return this->plrModes[plrIdx].override;
 }

 void setOverride(int plrIdx, bool enabled) {
 this->plrModes[plrIdx].override = enabled;
 }

 public SearchMode.SearchModeFloat getRadius(int plrIdx) {
 return this->plrModes[plrIdx].radius;
 }

 public SearchMode.SearchModeFloat getGradientWidth(int plrIdx) {
 return this->plrModes[plrIdx].gradientWidth;
 }

 public SearchMode.SearchModeFloat getBlur(int plrIdx) {
 return this->plrModes[plrIdx].blur;
 }

 public SearchMode.SearchModeFloat getDesat(int plrIdx) {
 return this->plrModes[plrIdx].desat;
 }

 public SearchMode.SearchModeFloat getDarkness(int plrIdx) {
 return this->plrModes[plrIdx].darkness;
 }

 bool isEnabled(int plrIdx) {
 return this->plrModes[plrIdx].enabled;
 }

 void setEnabled(int plrIdx, bool b) {
 SearchMode.PlayerSearchMode playerSearchMode = this->plrModes[plrIdx];
 if (b && !playerSearchMode.enabled) {
 playerSearchMode.enabled = true;
 this->FadeIn(plrIdx);
 } else if (!b && playerSearchMode.enabled) {
 playerSearchMode.enabled = false;
 this->FadeOut(plrIdx);
 }
 }

 void FadeIn(int int0) {
 SearchMode.PlayerSearchMode playerSearchMode = this->plrModes[int0];
 playerSearchMode.timer = Math.max(playerSearchMode.timer, 0.0F);
 playerSearchMode.doFadeIn = true;
 playerSearchMode.doFadeOut = false;
 }

 void FadeOut(int int0) {
 SearchMode.PlayerSearchMode playerSearchMode = this->plrModes[int0];
 playerSearchMode.timer = Math.min(playerSearchMode.timer, this->fadeTime);
 playerSearchMode.doFadeIn = false;
 playerSearchMode.doFadeOut = true;
 }

 void update() {
 for (int int0 = 0; int0 < this->plrModes.length; int0++) {
 SearchMode.PlayerSearchMode playerSearchMode = this->plrModes[int0];
 playerSearchMode.update();
 }
 }

 static void reset() {
 instance = nullptr;
 }

 public static class PlayerSearchMode {
 const int plrIndex;
 const SearchMode parent;
 bool override = false;
 bool enabled = false;
 private SearchMode.SearchModeFloat radius = new SearchMode.SearchModeFloat(0.0F, 50.0F, 1.0F);
 private SearchMode.SearchModeFloat gradientWidth = new SearchMode.SearchModeFloat(0.0F, 20.0F, 1.0F);
 private SearchMode.SearchModeFloat blur = new SearchMode.SearchModeFloat(0.0F, 1.0F, 0.01F);
 private SearchMode.SearchModeFloat desat = new SearchMode.SearchModeFloat(0.0F, 1.0F, 0.01F);
 private SearchMode.SearchModeFloat darkness = new SearchMode.SearchModeFloat(0.0F, 1.0F, 0.01F);
 float timer;
 bool doFadeOut;
 bool doFadeIn;

 public PlayerSearchMode(int index, SearchMode sm) {
 this->plrIndex = index;
 this->parent = sm;
 }

 bool isShaderEnabled() {
 return this->enabled || this->doFadeIn || this->doFadeOut;
 }

 bool isPlayerExterior() {
 IsoPlayer player = IsoPlayer.players[this->plrIndex];
 return player != nullptr && player.getCurrentSquare() != nullptr && !player.getCurrentSquare().isInARoom();
 }

 float getShaderBlur() {
 return this->isPlayerExterior() ? this->blur.getExterior() : this->blur.getInterior();
 }

 float getShaderDesat() {
 return this->isPlayerExterior() ? this->desat.getExterior() : this->desat.getInterior();
 }

 float getShaderRadius() {
 return this->isPlayerExterior() ? this->radius.getExterior() : this->radius.getInterior();
 }

 float getShaderGradientWidth() {
 return this->isPlayerExterior() ? this->gradientWidth.getExterior() : this->gradientWidth.getInterior();
 }

 float getShaderDarkness() {
 return this->isPlayerExterior() ? this->darkness.getExterior() : this->darkness.getInterior();
 }

 public SearchMode.SearchModeFloat getBlur() {
 return this->blur;
 }

 public SearchMode.SearchModeFloat getDesat() {
 return this->desat;
 }

 public SearchMode.SearchModeFloat getRadius() {
 return this->radius;
 }

 public SearchMode.SearchModeFloat getGradientWidth() {
 return this->gradientWidth;
 }

 public SearchMode.SearchModeFloat getDarkness() {
 return this->darkness;
 }

 void update() {
 if (!this->override) {
 if (this->doFadeIn) {
 this->timer = this->timer + GameTime.getInstance().getTimeDelta();
 this->timer = PZMath.clamp(this->timer, 0.0F, this->parent.fadeTime);
 float float0 = PZMath.clamp(this->timer / this->parent.fadeTime, 0.0F, 1.0F);
 this->blur.update(float0);
 this->desat.update(float0);
 this->radius.update(float0);
 this->darkness.update(float0);
 this->gradientWidth.equalise();
 if (this->timer >= this->parent.fadeTime) {
 this->doFadeIn = false;
 }
 } else if (this->doFadeOut) {
 this->timer = this->timer - GameTime.getInstance().getTimeDelta();
 this->timer = PZMath.clamp(this->timer, 0.0F, this->parent.fadeTime);
 float float1 = PZMath.clamp(this->timer / this->parent.fadeTime, 0.0F, 1.0F);
 this->blur.update(float1);
 this->desat.update(float1);
 this->radius.update(float1);
 this->darkness.update(float1);
 this->gradientWidth.equalise();
 if (this->timer <= 0.0F) {
 this->doFadeOut = false;
 }
 } else {
 if (this->enabled) {
 this->blur.equalise();
 this->desat.equalise();
 this->radius.equalise();
 this->darkness.equalise();
 this->gradientWidth.equalise();
 } else {
 this->blur.reset();
 this->desat.reset();
 this->radius.reset();
 this->darkness.reset();
 this->gradientWidth.equalise();
 }
 }
 }
 }
 }

 public static class SearchModeFloat {
 const float min;
 const float max;
 const float stepsize;
 float exterior;
 float targetExterior;
 float interior;
 float targetInterior;

 private SearchModeFloat(float float0, float float1, float float2) {
 this->min = float0;
 this->max = float1;
 this->stepsize = float2;
 }

 void set(float _exterior, float _targetExterior, float _interior, float _targetInterior) {
 this->setExterior(_exterior);
 this->setTargetExterior(_targetExterior);
 this->setInterior(_interior);
 this->setTargetInterior(_targetInterior);
 }

 void setTargets(float _targetExterior, float _targetInterior) {
 this->setTargetExterior(_targetExterior);
 this->setTargetInterior(_targetInterior);
 }

 float getExterior() {
 return this->exterior;
 }

 void setExterior(float _exterior) {
 this->exterior = _exterior;
 }

 float getTargetExterior() {
 return this->targetExterior;
 }

 void setTargetExterior(float _targetExterior) {
 this->targetExterior = _targetExterior;
 }

 float getInterior() {
 return this->interior;
 }

 void setInterior(float _interior) {
 this->interior = _interior;
 }

 float getTargetInterior() {
 return this->targetInterior;
 }

 void setTargetInterior(float _targetInterior) {
 this->targetInterior = _targetInterior;
 }

 void update(float delta) {
 this->exterior = delta * this->targetExterior;
 this->interior = delta * this->targetInterior;
 }

 void equalise() {
 if (!PZMath.equal(this->exterior, this->targetExterior, 0.001F) {
 this->exterior = PZMath.lerp(this->exterior, this->targetExterior, 0.01F);
 } else {
 this->exterior = this->targetExterior;
 }

 if (!PZMath.equal(this->interior, this->targetInterior, 0.001F) {
 this->interior = PZMath.lerp(this->interior, this->targetInterior, 0.01F);
 } else {
 this->interior = this->targetInterior;
 }
 }

 void reset() {
 this->exterior = 0.0F;
 this->interior = 0.0F;
 }

 float getMin() {
 return this->min;
 }

 float getMax() {
 return this->max;
 }

 float getStepsize() {
 return this->stepsize;
 }
 }
}
} // namespace iso
} // namespace zombie
