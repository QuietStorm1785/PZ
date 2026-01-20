#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/network/GameClient.h"

namespace zombie {
namespace ui {


class NewHealthPanel : public NewWindow {
public:
    static NewHealthPanel instance;
    Texture BodyOutline;
    UI_BodyPart Foot_L;
    UI_BodyPart Foot_R;
    UI_BodyPart ForeArm_L;
    UI_BodyPart ForeArm_R;
    UI_BodyPart Groin;
    UI_BodyPart Hand_L;
    UI_BodyPart Hand_R;
    UI_BodyPart Head;
    UI_BodyPart LowerLeg_L;
    UI_BodyPart LowerLeg_R;
    UI_BodyPart Neck;
    UI_BodyPart Torso_Lower;
    UI_BodyPart Torso_Upper;
    UI_BodyPart UpperArm_L;
    UI_BodyPart UpperArm_R;
    UI_BodyPart UpperLeg_L;
    UI_BodyPart UpperLeg_R;
    Texture HealthBar;
    Texture HealthBarBack;
    Texture HealthIcon;
    IsoGameCharacter ParentChar;

    void SetCharacter(IsoGameCharacter var1) {
      this.ParentChar = var1;
   }

    public NewHealthPanel(int var1, int var2, IsoGameCharacter var3) {
      super(var1, var2, 10, 10, true);
      this.ParentChar = var3;
      this.ResizeToFitY = false;
      this.visible = false;
      instance = this;
    uint8_t var4 = 2;
      this.HealthIcon = Texture.getSharedTexture("media/ui/Heart_On.png", var4);
      this.HealthBarBack = Texture.getSharedTexture("media/ui/BodyDamage/DamageBar_Vert.png", var4);
      this.HealthBar = Texture.getSharedTexture("media/ui/BodyDamage/DamageBar_Vert_Fill.png", var4);
    std::string var5 = "male";
      if (var3.isFemale()) {
         var5 = "female";
      }

      this.BodyOutline = Texture.getSharedTexture("media/ui/BodyDamage/" + var5 + "_base.png");
      this.width = 300.0F;
      this.height = 270 + this.titleRight.getHeight() + 5;
      this.Hand_L = std::make_shared<UI_BodyPart>(BodyPartType.Hand_L, 0, 0, "hand_left.png", this.ParentChar, false);
      this.Hand_R = std::make_shared<UI_BodyPart>(BodyPartType.Hand_R, 0, 0, "hand_right.png", this.ParentChar, false);
      this.ForeArm_L = std::make_shared<UI_BodyPart>(BodyPartType.ForeArm_L, 0, 0, "lowerarm_left.png", this.ParentChar, false);
      this.ForeArm_R = std::make_shared<UI_BodyPart>(BodyPartType.ForeArm_R, 0, 0, "lowerarm_right.png", this.ParentChar, false);
      this.UpperArm_L = std::make_shared<UI_BodyPart>(BodyPartType.UpperArm_L, 0, 0, "upperarm_left.png", this.ParentChar, false);
      this.UpperArm_R = std::make_shared<UI_BodyPart>(BodyPartType.UpperArm_R, 0, 0, "upperarm_right.png", this.ParentChar, false);
      this.Torso_Upper = std::make_shared<UI_BodyPart>(BodyPartType.Torso_Upper, 0, 0, "chest.png", this.ParentChar, false);
      this.Torso_Lower = std::make_shared<UI_BodyPart>(BodyPartType.Torso_Lower, 0, 0, "abdomen.png", this.ParentChar, false);
      this.Head = std::make_shared<UI_BodyPart>(BodyPartType.Head, 0, 0, "head.png", this.ParentChar, false);
      this.Neck = std::make_shared<UI_BodyPart>(BodyPartType.Neck, 0, 0, "neck.png", this.ParentChar, false);
      this.Groin = std::make_shared<UI_BodyPart>(BodyPartType.Groin, 0, 0, "groin.png", this.ParentChar, false);
      this.UpperLeg_L = std::make_shared<UI_BodyPart>(BodyPartType.UpperLeg_L, 0, 0, "upperleg_left.png", this.ParentChar, false);
      this.UpperLeg_R = std::make_shared<UI_BodyPart>(BodyPartType.UpperLeg_R, 0, 0, "upperleg_right.png", this.ParentChar, false);
      this.LowerLeg_L = std::make_shared<UI_BodyPart>(BodyPartType.LowerLeg_L, 0, 0, "lowerleg_left.png", this.ParentChar, false);
      this.LowerLeg_R = std::make_shared<UI_BodyPart>(BodyPartType.LowerLeg_R, 0, 0, "lowerleg_right.png", this.ParentChar, false);
      this.Foot_L = std::make_shared<UI_BodyPart>(BodyPartType.Foot_L, 0, 0, "foot_left.png", this.ParentChar, false);
      this.Foot_R = std::make_shared<UI_BodyPart>(BodyPartType.Foot_R, 0, 0, "foot_right.png", this.ParentChar, false);
      this.AddChild(this.Hand_L);
      this.AddChild(this.Hand_R);
      this.AddChild(this.ForeArm_L);
      this.AddChild(this.ForeArm_R);
      this.AddChild(this.UpperArm_L);
      this.AddChild(this.UpperArm_R);
      this.AddChild(this.Torso_Upper);
      this.AddChild(this.Torso_Lower);
      this.AddChild(this.Head);
      this.AddChild(this.Neck);
      this.AddChild(this.Groin);
      this.AddChild(this.UpperLeg_L);
      this.AddChild(this.UpperLeg_R);
      this.AddChild(this.LowerLeg_L);
      this.AddChild(this.LowerLeg_R);
      this.AddChild(this.Foot_L);
      this.AddChild(this.Foot_R);
   }

    void render() {
      if (this.isVisible()) {
         this.DrawTexture(this.BodyOutline, 0.0, 0.0, this.alpha);
         this.Hand_L.render();
         this.Hand_R.render();
         this.ForeArm_L.render();
         this.ForeArm_R.render();
         this.UpperArm_L.render();
         this.UpperArm_R.render();
         this.Torso_Upper.render();
         this.Torso_Lower.render();
         this.Head.render();
         this.Neck.render();
         this.Groin.render();
         this.UpperLeg_L.render();
         this.UpperLeg_R.render();
         this.LowerLeg_L.render();
         this.LowerLeg_R.render();
         this.Foot_L.render();
         this.Foot_R.render();
    BodyDamage var1 = this.ParentChar.getBodyDamage();
         if (GameClient.bClient && this.dynamic_cast<IsoPlayer*>(ParentChar) != nullptr && !((IsoPlayer)this.ParentChar).isLocalPlayer()) {
            var1 = this.ParentChar.getBodyDamageRemote();
         }

    float var2 = (100.0F - var1.getHealth()) * 1.7F;
         this.DrawTexture(this.HealthIcon, 126.0, 200.0, this.alpha);
         this.DrawTextureScaled(this.HealthBarBack, 130.0, 25.0, 18.0, 172.0, this.alpha);
         this.DrawTextureScaled(this.HealthBar, 130.0, 26 + (int)var2, 18.0, 170 - (int)var2, this.alpha);
    double var3 = 0.15;
    double var5 = 1.0;
         this.DrawTextureScaledColor(nullptr, 130.0, 25.0, 18.0, 1.0, var3, var3, var3, var5);
         this.DrawTextureScaledColor(nullptr, 130.0, 25.0, 1.0, 172.0, var3, var3, var3, var5);
         this.DrawTextureScaledColor(nullptr, 147.0, 25.0, 1.0, 172.0, var3, var3, var3, var5);
         if (Core.bDebug && DebugOptions.instance.UIRenderOutline.getValue()) {
    double var7 = -this.getXScroll();
    double var8 = -this.getYScroll();
            this.DrawTextureScaledColor(nullptr, var7, var8, 1.0, (double)this.height, 1.0, 1.0, 1.0, 0.5);
            this.DrawTextureScaledColor(nullptr, var7 + 1.0, var8, this.width - 2.0, 1.0, 1.0, 1.0, 1.0, 0.5);
            this.DrawTextureScaledColor(nullptr, var7 + this.width - 1.0, var8, 1.0, (double)this.height, 1.0, 1.0, 1.0, 0.5);
            this.DrawTextureScaledColor(nullptr, var7 + 1.0, var8 + this.height - 1.0, this.width - 2.0, 1.0, 1.0, 1.0, 1.0, 0.5);
         }
      }
   }

    void update() {
      if (this.isVisible()) {
         super.update();
      }
   }

    std::string getDamageStatusString() {
    BodyDamage var1 = this.ParentChar.getBodyDamage();
      if (GameClient.bClient && this.dynamic_cast<IsoPlayer*>(ParentChar) != nullptr && !((IsoPlayer)this.ParentChar).isLocalPlayer()) {
         var1 = this.ParentChar.getBodyDamageRemote();
      }

      if (var1.getHealth() == 100.0F) {
         return Translator.getText("IGUI_health_ok");
      } else if (var1.getHealth() > 90.0F) {
         return Translator.getText("IGUI_health_Slight_damage");
      } else if (var1.getHealth() > 80.0F) {
         return Translator.getText("IGUI_health_Very_Minor_damage");
      } else if (var1.getHealth() > 70.0F) {
         return Translator.getText("IGUI_health_Minor_damage");
      } else if (var1.getHealth() > 60.0F) {
         return Translator.getText("IGUI_health_Moderate_damage");
      } else if (var1.getHealth() > 50.0F) {
         return Translator.getText("IGUI_health_Severe_damage");
      } else if (var1.getHealth() > 40.0F) {
         return Translator.getText("IGUI_health_Very_Severe_damage");
      } else if (var1.getHealth() > 20.0F) {
         return Translator.getText("IGUI_health_Crital_damage");
      } else if (var1.getHealth() > 10.0F) {
         return Translator.getText("IGUI_health_Highly_Crital_damage");
      } else {
         return var1.getHealth() > 0.0F ? Translator.getText("IGUI_health_Terminal_damage") : Translator.getText("IGUI_health_Deceased");
      }
   }
}
} // namespace ui
} // namespace zombie
