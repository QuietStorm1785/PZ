#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/gameStates/IngameState.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace ui {


class ModalDialog : public NewWindow {
public:
    bool bYes = false;
    std::string Name;
    UIEventHandler handler = nullptr;
    bool Clicked = false;

    public ModalDialog(const std::string& var1, const std::string& var2, bool var3) {
      super(Core.getInstance().getOffscreenWidth(0) / 2, Core.getInstance().getOffscreenHeight(0) / 2, 470, 10, false);
      this.Name = var1;
      this.ResizeToFitY = false;
      this.IgnoreLossControl = true;
    TextBox var4 = std::make_shared<TextBox>(UIFont.Medium, 0, 0, 450, var2);
      var4.Centred = true;
      var4.ResizeParent = true;
      var4.update();
      this.Nest(var4, 20, 10, 20, 10);
      this.update();
      this.height *= 1.3F;
      if (var3) {
         this.AddChild(std::make_shared<DialogButton>(this, this.getWidth().intValue() / 2 - 40, this.getHeight().intValue() - 18, "Yes", "Yes"));
         this.AddChild(std::make_shared<DialogButton>(this, this.getWidth().intValue() / 2 + 40, this.getHeight().intValue() - 18, "No", "No"));
      } else {
         this.AddChild(std::make_shared<DialogButton>(this, this.getWidth().intValue() / 2, this.getHeight().intValue() - 18, "Ok", "Ok"));
      }

      this.x = this.x - this.width / 2.0F;
      this.y = this.y - this.height / 2.0F;
   }

    void ButtonClicked(const std::string& var1) {
      if (this.handler != nullptr) {
         this.handler.ModalClick(this.Name, var1);
         this.setVisible(false);
      } else {
         if (var1 == "Ok")) {
            UIManager.getSpeedControls().SetCurrentGameSpeed(4);
            this.Clicked(var1);
            this.Clicked = true;
            this.bYes = true;
            this.setVisible(false);
            IngameState.instance.Paused = false;
         }

         if (var1 == "Yes")) {
            UIManager.getSpeedControls().SetCurrentGameSpeed(4);
            this.Clicked(var1);
            this.Clicked = true;
            this.bYes = true;
            this.setVisible(false);
            IngameState.instance.Paused = false;
         }

         if (var1 == "No")) {
            UIManager.getSpeedControls().SetCurrentGameSpeed(4);
            this.Clicked(var1);
            this.Clicked = true;
            this.bYes = false;
            this.setVisible(false);
            IngameState.instance.Paused = false;
         }
      }
   }

    void Clicked(const std::string& var1) {
      if (this.Name == "Sleep") && var1 == "Yes")) {
    float var2 = 12.0F * IsoPlayer.getInstance().getStats().fatigue;
         if (var2 < 7.0F) {
            var2 = 7.0F;
         }

         var2 += GameTime.getInstance().getTimeOfDay();
         if (var2 >= 24.0F) {
            var2 -= 24.0F;
         }

         IsoPlayer.getInstance().setForceWakeUpTime((int)var2);
         IsoPlayer.getInstance().setAsleepTime(0.0F);
         TutorialManager.instance.StealControl = true;
         IsoPlayer.getInstance().setAsleep(true);
         UIManager.setbFadeBeforeUI(true);
         UIManager.FadeOut(4.0);
         UIManager.getSpeedControls().SetCurrentGameSpeed(3);

         try {
            GameWindow.save(true);
         } catch (FileNotFoundException var4) {
            Logger.getLogger(ModalDialog.class.getName()).log(Level.SEVERE, nullptr, var4);
         } catch (IOException var5) {
            Logger.getLogger(ModalDialog.class.getName()).log(Level.SEVERE, nullptr, var5);
         }
      }

      UIManager.Modal.setVisible(false);
   }
}
} // namespace ui
} // namespace zombie
