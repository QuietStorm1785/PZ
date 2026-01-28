#pragma once
#include <queue>
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


class LoadingQueueUI : public UIElement {
public:
    std::string strLoadingQueue;
    std::string strQueuePlace;
    static int placeInQueue = -1;
    Texture arrowBG = nullptr;
    Texture arrowFG = nullptr;
    double timerMultiplierAnim = 0.0;
    int animOffset = -1;

   // ImGui rendering override
   virtual void ImGuiRender() override;

    public LoadingQueueUI() {
      this.strLoadingQueue = Translator.getText("UI_GameLoad_LoadingQueue");
      this.strQueuePlace = Translator.getText("UI_GameLoad_PlaceInQueue");
      this.arrowBG = Texture.getSharedTexture("media/ui/ArrowRight_Disabled.png");
      this.arrowFG = Texture.getSharedTexture("media/ui/ArrowRight.png");
      placeInQueue = -1;
      this.onresize();
   }

    void update() {
   }

    void onresize() {
      this.x = 288.0;
      this.y = 101.0;
      this.width = (float)(Core.getInstance().getScreenWidth() - 2.0 * this.x);
      this.height = (float)(Core.getInstance().getScreenHeight() - 2.0 * this.y);
   }

    void render() {
      this.onresize();
    double var1 = 0.4F;
    double var3 = 0.4F;
    double var5 = 0.4F;
    double var7 = 1.0;
      this.DrawTextureScaledColor(nullptr, 0.0, 0.0, 1.0, (double)this.height, var1, var3, var5, var7);
      this.DrawTextureScaledColor(nullptr, 1.0, 0.0, this.width - 2.0, 1.0, var1, var3, var5, var7);
      this.DrawTextureScaledColor(nullptr, this.width - 1.0, 0.0, 1.0, (double)this.height, var1, var3, var5, var7);
      this.DrawTextureScaledColor(nullptr, 1.0, this.height - 1.0, this.width - 2.0, 1.0, var1, var3, var5, var7);
      this.DrawTextureScaledColor(nullptr, 1.0, 1.0, this.width - 2.0, (double)(this.height - 2.0F), 0.0, 0.0, 0.0, 0.5);
      TextManager.instance.DrawStringCentre(UIFont.Large, this.x + this.width / 2.0F, this.y + 60.0, this.strLoadingQueue, 1.0, 1.0, 1.0, 1.0);
      this.DrawTextureColor(this.arrowBG, (this.width - this.arrowBG.getWidth()) / 2.0F - 15.0F, 120.0, 1.0, 1.0, 1.0, 1.0);
      this.DrawTextureColor(this.arrowBG, (this.width - this.arrowBG.getWidth()) / 2.0F, 120.0, 1.0, 1.0, 1.0, 1.0);
      this.DrawTextureColor(this.arrowBG, (this.width - this.arrowBG.getWidth()) / 2.0F + 15.0F, 120.0, 1.0, 1.0, 1.0, 1.0);
      this.timerMultiplierAnim = this.timerMultiplierAnim + UIManager.getMillisSinceLastRender();
      if (this.timerMultiplierAnim <= 500.0) {
         this.animOffset = int.MIN_VALUE;
      } else if (this.timerMultiplierAnim <= 1000.0) {
         this.animOffset = -15;
      } else if (this.timerMultiplierAnim <= 1500.0) {
         this.animOffset = 0;
      } else if (this.timerMultiplierAnim <= 2000.0) {
         this.animOffset = 15;
      } else {
         this.timerMultiplierAnim = 0.0;
      }

      if (this.animOffset != int.MIN_VALUE) {
         this.DrawTextureColor(this.arrowFG, (this.width - this.arrowBG.getWidth()) / 2.0F + this.animOffset, 120.0, 1.0, 1.0, 1.0, 1.0);
      }

      if (placeInQueue >= 0) {
         TextManager.instance
            .DrawStringCentre(UIFont.Medium, this.x + this.width / 2.0F, this.y + 180.0, std::string.format(this.strQueuePlace, placeInQueue), 1.0, 1.0, 1.0, 1.0);
      }
   }

    void setPlaceInQueue(int var1) {
      placeInQueue = var1;
   }
}
} // namespace ui
} // namespace zombie
