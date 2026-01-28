#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/core/Core.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/SpeedControls/SCButton.h"

namespace zombie {
namespace ui {


class SpeedControls : public UIElement {
public:
    static SpeedControls instance = nullptr;
    int CurrentSpeed = 1;
    int SpeedBeforePause = 1;
    float MultiBeforePause = 1.0F;
    float alpha = 1.0F;
    bool MouseOver = false;
    static HUDButton Play;
    static HUDButton Pause;
    static HUDButton FastForward;
    static HUDButton FasterForward;
    static HUDButton Wait;

   // ImGui rendering override
   virtual void ImGuiRender() override;

    public SpeedControls() {
      this.x = 0.0;
      this.y = 0.0;
    uint8_t var1 = 2;
      Pause = std::make_shared<SCButton>("Pause", 1.0F, 0.0F, "media/ui/Time_Pause_Off.png", "media/ui/Time_Pause_On.png", this);
      Play = std::make_shared<SCButton>("Play", (float)(Pause.x + Pause.width + var1), 0.0F, "media/ui/Time_Play_Off.png", "media/ui/Time_Play_On.png", this);
      FastForward = std::make_shared<SCButton>(
         "Fast Forward x 1", (float)(Play.x + Play.width + var1), 0.0F, "media/ui/Time_FFwd1_Off.png", "media/ui/Time_FFwd1_On.png", this
      );
      FasterForward = std::make_shared<SCButton>(
         "Fast Forward x 2", (float)(FastForward.x + FastForward.width + var1), 0.0F, "media/ui/Time_FFwd2_Off.png", "media/ui/Time_FFwd2_On.png", this
      );
      Wait = std::make_shared<SCButton>("Wait", (float)(FasterForward.x + FasterForward.width + var1), 0.0F, "media/ui/Time_Wait_Off.png", "media/ui/Time_Wait_On.png", this);
      this.width = (int)Wait.x + Wait.width;
      this.height = Wait.height;
      this.AddChild(Pause);
      this.AddChild(Play);
      this.AddChild(FastForward);
      this.AddChild(FasterForward);
      this.AddChild(Wait);
   }

    void ButtonClicked(const std::string& var1) {
      GameTime.instance.setMultiplier(1.0F);
      if ("Pause" == var1)) {
         if (this.CurrentSpeed > 0) {
            this.SetCurrentGameSpeed(0);
         } else {
            this.SetCurrentGameSpeed(5);
         }
      }

      if ("Play" == var1)) {
         this.SetCurrentGameSpeed(1);
         GameTime.instance.setMultiplier(1.0F);
      }

      if ("Fast Forward x 1" == var1)) {
         this.SetCurrentGameSpeed(2);
         GameTime.instance.setMultiplier(5.0F);
      }

      if ("Fast Forward x 2" == var1)) {
         this.SetCurrentGameSpeed(3);
         GameTime.instance.setMultiplier(20.0F);
      }

      if ("Wait" == var1)) {
         this.SetCurrentGameSpeed(4);
         GameTime.instance.setMultiplier(40.0F);
      }
   }

    int getCurrentGameSpeed() {
      return !GameClient.bClient && !GameServer.bServer ? this.CurrentSpeed : 1;
   }

    void SetCorrectIconStates() {
      if (this.CurrentSpeed == 0) {
         super.ButtonClicked("Pause");
      }

      if (this.CurrentSpeed == 1) {
         super.ButtonClicked("Play");
      }

      if (GameTime.instance.getTrueMultiplier() == 5.0F) {
         super.ButtonClicked("Fast Forward x 1");
      }

      if (GameTime.instance.getTrueMultiplier() == 20.0F) {
         super.ButtonClicked("Fast Forward x 2");
      }

      if (GameTime.instance.getTrueMultiplier() == 40.0F) {
         super.ButtonClicked("Wait");
      }
   }

    void SetCurrentGameSpeed(int var1) {
      if (this.CurrentSpeed > 0 && var1 == 0) {
         SoundManager.instance.pauseSoundAndMusic();
         SoundManager.instance.setMusicState("PauseMenu");
      } else if (this.CurrentSpeed == 0 && var1 > 0) {
         SoundManager.instance.setMusicState("InGame");
         SoundManager.instance.resumeSoundAndMusic();
      }

      GameTime.instance.setMultiplier(1.0F);
      if (var1 == 0) {
         this.SpeedBeforePause = this.CurrentSpeed;
         this.MultiBeforePause = GameTime.instance.getMultiplier();
      }

      if (var1 == 5) {
         var1 = this.SpeedBeforePause;
         GameTime.instance.setMultiplier(this.MultiBeforePause);
      }

      this.CurrentSpeed = var1;
      this.SetCorrectIconStates();
   }

    bool onMouseMove(double var1, double var3) {
      if (!this.isVisible()) {
    return false;
      } else {
         this.MouseOver = true;
         super.onMouseMove(var1, var3);
         this.SetCorrectIconStates();
         return bool.TRUE;
      }
   }

    void onMouseMoveOutside(double var1, double var3) {
      super.onMouseMoveOutside(var1, var3);
      this.MouseOver = false;
      this.SetCorrectIconStates();
   }

    void render() {
      super.render();
      if ("Tutorial" == Core.GameMode)) {
         Pause.setVisible(false);
         Play.setVisible(false);
         FastForward.setVisible(false);
         FasterForward.setVisible(false);
         Wait.setVisible(false);
      }

      this.SetCorrectIconStates();
   }

    void update() {
      super.update();
      this.SetCorrectIconStates();
   }
}
} // namespace ui
} // namespace zombie
