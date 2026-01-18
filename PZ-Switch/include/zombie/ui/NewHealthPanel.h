#pragma once
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/network/GameClient.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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

 void SetCharacter(IsoGameCharacter chr) { this->ParentChar = chr; }

public
 NewHealthPanel(int x, int y, IsoGameCharacter ParentCharacter) {
 super(x, y, 10, 10, true);
 this->ParentChar = ParentCharacter;
 this->ResizeToFitY = false;
 this->visible = false;
 instance = this;
 uint8_t byte0 = 2;
 this->HealthIcon = Texture.getSharedTexture("media/ui/Heart_On.png", byte0);
 this->HealthBarBack = Texture.getSharedTexture(
 "media/ui/BodyDamage/DamageBar_Vert.png", byte0);
 this->HealthBar = Texture.getSharedTexture(
 "media/ui/BodyDamage/DamageBar_Vert_Fill.png", byte0);
 std::string string = "male";
 if (ParentCharacter.isFemale()) {
 string = "female";
 }

 this->BodyOutline =
 Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_base.png");
 this->width = 300.0F;
 this->height = 270 + this->titleRight.getHeight() + 5;
 this->Hand_L = new UI_BodyPart(BodyPartType.Hand_L, 0, 0, "hand_left.png",
 this->ParentChar, false);
 this->Hand_R = new UI_BodyPart(BodyPartType.Hand_R, 0, 0, "hand_right.png",
 this->ParentChar, false);
 this->ForeArm_L =
 new UI_BodyPart(BodyPartType.ForeArm_L, 0, 0, "lowerarm_left.png",
 this->ParentChar, false);
 this->ForeArm_R =
 new UI_BodyPart(BodyPartType.ForeArm_R, 0, 0, "lowerarm_right.png",
 this->ParentChar, false);
 this->UpperArm_L =
 new UI_BodyPart(BodyPartType.UpperArm_L, 0, 0, "upperarm_left.png",
 this->ParentChar, false);
 this->UpperArm_R =
 new UI_BodyPart(BodyPartType.UpperArm_R, 0, 0, "upperarm_right.png",
 this->ParentChar, false);
 this->Torso_Upper = new UI_BodyPart(BodyPartType.Torso_Upper, 0, 0,
 "chest.png", this->ParentChar, false);
 this->Torso_Lower = new UI_BodyPart(BodyPartType.Torso_Lower, 0, 0,
 "abdomen.png", this->ParentChar, false);
 this->Head = new UI_BodyPart(BodyPartType.Head, 0, 0, "head.png",
 this->ParentChar, false);
 this->Neck = new UI_BodyPart(BodyPartType.Neck, 0, 0, "neck.png",
 this->ParentChar, false);
 this->Groin = new UI_BodyPart(BodyPartType.Groin, 0, 0, "groin.png",
 this->ParentChar, false);
 this->UpperLeg_L =
 new UI_BodyPart(BodyPartType.UpperLeg_L, 0, 0, "upperleg_left.png",
 this->ParentChar, false);
 this->UpperLeg_R =
 new UI_BodyPart(BodyPartType.UpperLeg_R, 0, 0, "upperleg_right.png",
 this->ParentChar, false);
 this->LowerLeg_L =
 new UI_BodyPart(BodyPartType.LowerLeg_L, 0, 0, "lowerleg_left.png",
 this->ParentChar, false);
 this->LowerLeg_R =
 new UI_BodyPart(BodyPartType.LowerLeg_R, 0, 0, "lowerleg_right.png",
 this->ParentChar, false);
 this->Foot_L = new UI_BodyPart(BodyPartType.Foot_L, 0, 0, "foot_left.png",
 this->ParentChar, false);
 this->Foot_R = new UI_BodyPart(BodyPartType.Foot_R, 0, 0, "foot_right.png",
 this->ParentChar, false);
 this->AddChild(this->Hand_L);
 this->AddChild(this->Hand_R);
 this->AddChild(this->ForeArm_L);
 this->AddChild(this->ForeArm_R);
 this->AddChild(this->UpperArm_L);
 this->AddChild(this->UpperArm_R);
 this->AddChild(this->Torso_Upper);
 this->AddChild(this->Torso_Lower);
 this->AddChild(this->Head);
 this->AddChild(this->Neck);
 this->AddChild(this->Groin);
 this->AddChild(this->UpperLeg_L);
 this->AddChild(this->UpperLeg_R);
 this->AddChild(this->LowerLeg_L);
 this->AddChild(this->LowerLeg_R);
 this->AddChild(this->Foot_L);
 this->AddChild(this->Foot_R);
 }

 void render() {
 if (this->isVisible()) {
 this->DrawTexture(this->BodyOutline, 0.0, 0.0, this->alpha);
 this->Hand_L.render();
 this->Hand_R.render();
 this->ForeArm_L.render();
 this->ForeArm_R.render();
 this->UpperArm_L.render();
 this->UpperArm_R.render();
 this->Torso_Upper.render();
 this->Torso_Lower.render();
 this->Head.render();
 this->Neck.render();
 this->Groin.render();
 this->UpperLeg_L.render();
 this->UpperLeg_R.render();
 this->LowerLeg_L.render();
 this->LowerLeg_R.render();
 this->Foot_L.render();
 this->Foot_R.render();
 BodyDamage bodyDamage = this->ParentChar.getBodyDamage();
 if (GameClient.bClient && this->ParentChar instanceof
 IsoPlayer && !((IsoPlayer)this->ParentChar).isLocalPlayer()) {
 bodyDamage = this->ParentChar.getBodyDamageRemote();
 }

 float float0 = (100.0F - bodyDamage.getHealth()) * 1.7F;
 this->DrawTexture(this->HealthIcon, 126.0, 200.0, this->alpha);
 this->DrawTextureScaled(this->HealthBarBack, 130.0, 25.0, 18.0, 172.0,
 this->alpha);
 this->DrawTextureScaled(this->HealthBar, 130.0, 26 + (int)float0, 18.0,
 170 - (int)float0, this->alpha);
 double double0 = 0.15;
 double double1 = 1.0;
 this->DrawTextureScaledColor(nullptr, 130.0, 25.0, 18.0, 1.0, double0,
 double0, double0, double1);
 this->DrawTextureScaledColor(nullptr, 130.0, 25.0, 1.0, 172.0, double0,
 double0, double0, double1);
 this->DrawTextureScaledColor(nullptr, 147.0, 25.0, 1.0, 172.0, double0,
 double0, double0, double1);
 if (Core.bDebug && DebugOptions.instance.UIRenderOutline.getValue()) {
 double double2 = -this->getXScroll();
 double double3 = -this->getYScroll();
 this->DrawTextureScaledColor(nullptr, double2, double3, 1.0,
 (double)this->height, 1.0, 1.0, 1.0, 0.5);
 this->DrawTextureScaledColor(nullptr, double2 + 1.0, double3,
 this->width - 2.0, 1.0, 1.0, 1.0, 1.0, 0.5);
 this->DrawTextureScaledColor(nullptr, double2 + this->width - 1.0,
 double3, 1.0, (double)this->height, 1.0, 1.0,
 1.0, 0.5);
 this->DrawTextureScaledColor(nullptr, double2 + 1.0,
 double3 + this->height - 1.0,
 this->width - 2.0, 1.0, 1.0, 1.0, 1.0, 0.5);
 }
 }
 }

 void update() {
 if (this->isVisible()) {
 super.update();
 }
 }

 std::string getDamageStatusString() {
 BodyDamage bodyDamage = this->ParentChar.getBodyDamage();
 if (GameClient.bClient && this->ParentChar instanceof
 IsoPlayer && !((IsoPlayer)this->ParentChar).isLocalPlayer()) {
 bodyDamage = this->ParentChar.getBodyDamageRemote();
 }

 if (bodyDamage.getHealth() == 100.0F) {
 return Translator.getText("IGUI_health_ok");
 } else if (bodyDamage.getHealth() > 90.0F) {
 return Translator.getText("IGUI_health_Slight_damage");
 } else if (bodyDamage.getHealth() > 80.0F) {
 return Translator.getText("IGUI_health_Very_Minor_damage");
 } else if (bodyDamage.getHealth() > 70.0F) {
 return Translator.getText("IGUI_health_Minor_damage");
 } else if (bodyDamage.getHealth() > 60.0F) {
 return Translator.getText("IGUI_health_Moderate_damage");
 } else if (bodyDamage.getHealth() > 50.0F) {
 return Translator.getText("IGUI_health_Severe_damage");
 } else if (bodyDamage.getHealth() > 40.0F) {
 return Translator.getText("IGUI_health_Very_Severe_damage");
 } else if (bodyDamage.getHealth() > 20.0F) {
 return Translator.getText("IGUI_health_Crital_damage");
 } else if (bodyDamage.getHealth() > 10.0F) {
 return Translator.getText("IGUI_health_Highly_Crital_damage");
 } else {
 return bodyDamage.getHealth() > 0.0F
 ? Translator.getText("IGUI_health_Terminal_damage")
 : Translator.getText("IGUI_health_Deceased");
 }
 }
}
} // namespace ui
} // namespace zombie
