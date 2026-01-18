#pragma once
#include "zombie/GameTime.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/Mouse.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace gameStates {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TISLogoState : public GameState {
public:
 float alpha = 0.0F;
 float alphaStep = 0.02F;
 float logoDisplayTime = 20.0F;
 int screenNumber = 1;
 int stage = 0;
 float targetAlpha = 0.0F;
 bool bNoRender = false;
private
 TISLogoState.LogoElement logoTIS = new TISLogoState.LogoElement(
 "media/ui/TheIndieStoneLogo_Lineart_White.png");
private
 TISLogoState.LogoElement logoFMOD =
 new TISLogoState.LogoElement("media/ui/FMODLogo.png");
private
 TISLogoState.LogoElement logoGA =
 new TISLogoState.LogoElement("media/ui/GA-1280-white.png");
private
 TISLogoState.LogoElement logoNW =
 new TISLogoState.LogoElement("media/ui/NW_Logo_Combined.png");
 static const int SCREEN_TIS = 1;
 static const int SCREEN_OTHER = 2;
 static const int STAGE_FADING_IN_LOGO = 0;
 static const int STAGE_HOLDING_LOGO = 1;
 static const int STAGE_FADING_OUT_LOGO = 2;
 static const int STAGE_EXIT = 3;

 void enter() {
 UIManager.bSuspend = true;
 this->alpha = 0.0F;
 this->targetAlpha = 1.0F;
 }

 void exit() { UIManager.bSuspend = false; }

 void render() {
 if (this->bNoRender) {
 Core.getInstance().StartFrame();
 SpriteRenderer.instance.renderi(nullptr, 0, 0,
 Core.getInstance().getOffscreenWidth(0),
 Core.getInstance().getOffscreenHeight(0),
 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
 Core.getInstance().EndFrame();
 } else {
 Core.getInstance().StartFrame();
 Core.getInstance().EndFrame();
 bool boolean0 = UIManager.useUIFBO;
 UIManager.useUIFBO = false;
 Core.getInstance().StartFrameUI();
 SpriteRenderer.instance.renderi(nullptr, 0, 0,
 Core.getInstance().getOffscreenWidth(0),
 Core.getInstance().getOffscreenHeight(0),
 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
 if (this->screenNumber == 1) {
 this->logoTIS.centerOnScreen();
 this->logoTIS.render(this->alpha);
 }

 if (this->screenNumber == 2) {
 this->renderAttribution();
 }

 Core.getInstance().EndFrameUI();
 UIManager.useUIFBO = boolean0;
 }
 }

 void renderAttribution() {
 int int0 = Core.getInstance().getScreenWidth();
 int int1 = Core.getInstance().getScreenHeight();
 uint8_t byte0 = 50;
 uint8_t byte1 = 3;
 int int2 = (int1 - (byte1 + 1) * byte0) / 3;
 Texture texture = this->logoGA.m_texture;
 if (texture != nullptr && texture.isReady()) {
 int int3 =
 (int)((float)(texture.getWidth() * int2) / texture.getHeight());
 int int4 = (int0 - int3) / 2;
 this->logoGA.setPos(int4, byte0);
 this->logoGA.setSize(int3, int2);
 this->logoGA.render(this->alpha);
 }

 int int5 = byte0 + int2 + byte0;
 int5 = (int)(int5 + int2 * 0.15F);
 texture = this->logoNW.m_texture;
 if (texture != nullptr && texture.isReady()) {
 float float0 = 0.5F;
 int int6 =
 (int)(texture.getWidth() * float0 * int2 / texture.getHeight());
 int int7 = (int)(int2 * float0);
 int int8 = (int0 - int6) / 2;
 int int9 = (int2 - int7) / 2;
 this->logoNW.setPos(int8, int5 + int9);
 this->logoNW.setSize(int6, int7);
 this->logoNW.render(this->alpha);
 }

 int5 += int2 + byte0;
 texture = this->logoFMOD.m_texture;
 if (texture != nullptr && texture.isReady()) {
 float float1 = 0.35F;
 int int10 = TextManager.instance.getFontHeight(UIFont.Small);
 int int11 = (int)(int2 * float1 - 16.0F - int10);
 int int12 =
 (int)(texture.getWidth() * ((float)int11 / texture.getHeight()));
 int int13 = (int0 - int12) / 2;
 int int14 = (int2 - int11) / 2;
 int int15 = int5 + int14 + int11 + 16;
 this->logoFMOD.setPos(int13, int5 + int14);
 this->logoFMOD.setSize(int12, int11);
 this->logoFMOD.render(this->alpha);
 std::string string =
 "Made with FMOD Studio by Firelight Technologies Pty Ltd.";
 TextManager.instance.DrawStringCentre(int0 / 2.0, int15, string, 1.0, 1.0,
 1.0, this->alpha);
 }
 }

public
 GameStateMachine.StateAction update() {
 if (Mouse.isLeftDown() || GameKeyboard.isKeyDown(28) ||
 GameKeyboard.isKeyDown(57) || GameKeyboard.isKeyDown(1) {
 this->stage = 3;
 }

 if (this->stage == 0) {
 this->targetAlpha = 1.0F;
 if (this->alpha == 1.0F) {
 this->stage = 1;
 this->logoDisplayTime = 20.0F;
 }
 }

 if (this->stage == 1) {
 this->logoDisplayTime =
 this->logoDisplayTime - GameTime.getInstance().getMultiplier() / 1.6F;
 if (this->logoDisplayTime <= 0.0F) {
 this->stage = 2;
 }
 }

 if (this->stage == 2) {
 this->targetAlpha = 0.0F;
 if (this->alpha == 0.0F) {
 if (this->screenNumber == 1) {
 this->screenNumber = 2;
 this->stage = 0;
 } else {
 this->stage = 3;
 }
 }
 }

 if (this->stage == 3) {
 this->targetAlpha = 0.0F;
 if (this->alpha == 0.0F) {
 this->bNoRender = true;
 return GameStateMachine.StateAction.Continue;
 }
 }

 if (this->alpha < this->targetAlpha) {
 this->alpha =
 this->alpha + this->alphaStep * GameTime.getInstance().getMultiplier();
 if (this->alpha > this->targetAlpha) {
 this->alpha = this->targetAlpha;
 }
 } else if (this->alpha > this->targetAlpha) {
 this->alpha =
 this->alpha - this->alphaStep * GameTime.getInstance().getMultiplier();
 if (this->stage == 3) {
 this->alpha = this->alpha -
 this->alphaStep * GameTime.getInstance().getMultiplier();
 }

 if (this->alpha < this->targetAlpha) {
 this->alpha = this->targetAlpha;
 }
 }

 return GameStateMachine.StateAction.Remain;
 }

private
 static class LogoElement {
 Texture m_texture;
 int m_x;
 int m_y;
 int m_width;
 int m_height;

 LogoElement(String string) {
 this->m_texture = Texture.getSharedTexture(string);
 if (this->m_texture != nullptr) {
 this->m_width = this->m_texture.getWidth();
 this->m_height = this->m_texture.getHeight();
 }
 }

 void centerOnScreen() {
 this->m_x = (Core.getInstance().getScreenWidth() - this->m_width) / 2;
 this->m_y = (Core.getInstance().getScreenHeight() - this->m_height) / 2;
 }

 void setPos(int int0, int int1) {
 this->m_x = int0;
 this->m_y = int1;
 }

 void setSize(int int0, int int1) {
 this->m_width = int0;
 this->m_height = int1;
 }

 void render(float float0) {
 if (this->m_texture != nullptr && this->m_texture.isReady()) {
 SpriteRenderer.instance.renderi(this->m_texture, this->m_x, this->m_y,
 this->m_width, this->m_height, 1.0F, 1.0F,
 1.0F, float0, nullptr);
 }
 }
 }
}
} // namespace gameStates
} // namespace zombie
