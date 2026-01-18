#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LoadingQueueUI : public UIElement {
public:
 std::string strLoadingQueue;
 std::string strQueuePlace;
 static int placeInQueue = -1;
 Texture arrowBG = nullptr;
 Texture arrowFG = nullptr;
 double timerMultiplierAnim = 0.0;
 int animOffset = -1;

 public LoadingQueueUI() {
 this->strLoadingQueue = Translator.getText("UI_GameLoad_LoadingQueue");
 this->strQueuePlace = Translator.getText("UI_GameLoad_PlaceInQueue");
 this->arrowBG = Texture.getSharedTexture("media/ui/ArrowRight_Disabled.png");
 this->arrowFG = Texture.getSharedTexture("media/ui/ArrowRight.png");
 placeInQueue = -1;
 this->onresize();
 }

 void update() {
 }

 void onresize() {
 this->x = 288.0;
 this->y = 101.0;
 this->width = (float)(Core.getInstance().getScreenWidth() - 2.0 * this->x);
 this->height = (float)(Core.getInstance().getScreenHeight() - 2.0 * this->y);
 }

 void render() {
 this->onresize();
 double double0 = 0.4F;
 double double1 = 0.4F;
 double double2 = 0.4F;
 double double3 = 1.0;
 this->DrawTextureScaledColor(nullptr, 0.0, 0.0, 1.0, (double)this->height, double0, double1, double2, double3);
 this->DrawTextureScaledColor(nullptr, 1.0, 0.0, this->width - 2.0, 1.0, double0, double1, double2, double3);
 this->DrawTextureScaledColor(nullptr, this->width - 1.0, 0.0, 1.0, (double)this->height, double0, double1, double2, double3);
 this->DrawTextureScaledColor(nullptr, 1.0, this->height - 1.0, this->width - 2.0, 1.0, double0, double1, double2, double3);
 this->DrawTextureScaledColor(nullptr, 1.0, 1.0, this->width - 2.0, (double)(this->height - 2.0F), 0.0, 0.0, 0.0, 0.5);
 TextManager.instance.DrawStringCentre(UIFont.Large, this->x + this->width / 2.0F, this->y + 60.0, this->strLoadingQueue, 1.0, 1.0, 1.0, 1.0);
 this->DrawTextureColor(this->arrowBG, (this->width - this->arrowBG.getWidth()) / 2.0F - 15.0F, 120.0, 1.0, 1.0, 1.0, 1.0);
 this->DrawTextureColor(this->arrowBG, (this->width - this->arrowBG.getWidth()) / 2.0F, 120.0, 1.0, 1.0, 1.0, 1.0);
 this->DrawTextureColor(this->arrowBG, (this->width - this->arrowBG.getWidth()) / 2.0F + 15.0F, 120.0, 1.0, 1.0, 1.0, 1.0);
 this->timerMultiplierAnim = this->timerMultiplierAnim + UIManager.getMillisSinceLastRender();
 if (this->timerMultiplierAnim <= 500.0) {
 this->animOffset = Integer.MIN_VALUE;
 } else if (this->timerMultiplierAnim <= 1000.0) {
 this->animOffset = -15;
 } else if (this->timerMultiplierAnim <= 1500.0) {
 this->animOffset = 0;
 } else if (this->timerMultiplierAnim <= 2000.0) {
 this->animOffset = 15;
 } else {
 this->timerMultiplierAnim = 0.0;
 }

 if (this->animOffset != Integer.MIN_VALUE) {
 this->DrawTextureColor(this->arrowFG, (this->width - this->arrowBG.getWidth()) / 2.0F + this->animOffset, 120.0, 1.0, 1.0, 1.0, 1.0);
 }

 if (placeInQueue >= 0) {
 TextManager.instance
 .DrawStringCentre(
 UIFont.Medium, this->x + this->width / 2.0F, this->y + 180.0, String.format(this->strQueuePlace, placeInQueue), 1.0, 1.0, 1.0, 1.0
 );
 }
 }

 void setPlaceInQueue(int _placeInQueue) {
 placeInQueue = _placeInQueue;
 }
}
} // namespace ui
} // namespace zombie
