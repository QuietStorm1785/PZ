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
#include "zombie/core/Color.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/network/GameClient.h"

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class UI_BodyPart : public UIElement {
public:
 float alpha = 1.0F;
 const Color color = new Color(1.0F, 1.0F, 1.0F, 1.0F);
 BodyPartType BodyPartType;
 bool IsFlipped = false;
 float MaxOscilatorRate = 0.58F;
 float MinOscilatorRate = 0.025F;
 float Oscilator = 0.0F;
 float OscilatorRate = 0.02F;
 float OscilatorStep = 0.0F;
 IsoGameCharacter chr;
 bool mouseOver = false;
 Texture scratchTex;
 Texture bandageTex;
 Texture dirtyBandageTex;
 Texture infectionTex;
 Texture deepWoundTex;
 Texture stitchTex;
 Texture biteTex;
 Texture glassTex;
 Texture boneTex;
 Texture splintTex;
 Texture burnTex;
 Texture bulletTex;

 public UI_BodyPart(BodyPartType type, int x, int y, const std::string& part, IsoGameCharacter character, bool RenderFlipped) {
 std::string string = "male";
 if (character.isFemale()) {
 string = "female";
 }

 this->chr = character;
 this->BodyPartType = type;
 this->scratchTex = Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_scratch_" + part);
 this->bandageTex = Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_bandage_" + part);
 this->dirtyBandageTex = Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_bandagedirty_" + part);
 this->infectionTex = Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_infection_" + part);
 this->biteTex = Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_bite_" + part);
 this->deepWoundTex = Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_deepwound_" + part);
 this->stitchTex = Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_stitches_" + part);
 this->glassTex = Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_glass_" + part);
 this->boneTex = Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_bones_" + part);
 this->splintTex = Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_splint_" + part);
 this->burnTex = Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_burn_" + part);
 this->bulletTex = Texture.getSharedTexture("media/ui/BodyDamage/" + string + "_bullet_" + part);
 this->x = x;
 this->y = y;
 this->width = this->scratchTex.getWidth();
 this->height = this->scratchTex.getHeight();
 this->IsFlipped = RenderFlipped;
 }

 void onMouseMoveOutside(double dx, double dy) {
 this->mouseOver = false;
 }

 void render() {
 BodyDamage bodyDamage = this->chr.getBodyDamage();
 if (GameClient.bClient && this->chr instanceof IsoPlayer && !((IsoPlayer)this->chr).isLocalPlayer()) {
 bodyDamage = this->chr.getBodyDamageRemote();
 }

 if (this->infectionTex != nullptr && !bodyDamage.IsBandaged(this->BodyPartType) && bodyDamage.getBodyPart(this->BodyPartType).getWoundInfectionLevel() > 0.0F
 )
 {
 this->DrawTexture(this->infectionTex, 0.0, 0.0, bodyDamage.getBodyPart(this->BodyPartType).getWoundInfectionLevel() / 10.0F);
 }

 if (this->bandageTex != nullptr && bodyDamage.IsBandaged(this->BodyPartType) && bodyDamage.getBodyPart(this->BodyPartType).getBandageLife() > 0.0F) {
 this->DrawTexture(this->bandageTex, 0.0, 0.0, 1.0);
 } else if (this->dirtyBandageTex != nullptr
 && bodyDamage.IsBandaged(this->BodyPartType)
 && bodyDamage.getBodyPart(this->BodyPartType).getBandageLife() <= 0.0F) {
 this->DrawTexture(this->dirtyBandageTex, 0.0, 0.0, 1.0);
 } else if (this->scratchTex != nullptr && bodyDamage.IsScratched(this->BodyPartType) {
 this->DrawTexture(this->scratchTex, 0.0, 0.0, bodyDamage.getBodyPart(this->BodyPartType).getScratchTime() / 20.0F);
 } else if (this->scratchTex != nullptr && bodyDamage.IsCut(this->BodyPartType) {
 this->DrawTexture(this->scratchTex, 0.0, 0.0, bodyDamage.getBodyPart(this->BodyPartType).getCutTime() / 20.0F);
 } else if (this->biteTex != nullptr
 && !bodyDamage.IsBandaged(this->BodyPartType)
 && bodyDamage.IsBitten(this->BodyPartType)
 && bodyDamage.getBodyPart(this->BodyPartType).getBiteTime() >= 0.0F) {
 this->DrawTexture(this->biteTex, 0.0, 0.0, 1.0);
 } else if (this->deepWoundTex != nullptr && bodyDamage.IsDeepWounded(this->BodyPartType) {
 this->DrawTexture(this->deepWoundTex, 0.0, 0.0, bodyDamage.getBodyPart(this->BodyPartType).getDeepWoundTime() / 15.0F);
 } else if (this->stitchTex != nullptr && bodyDamage.IsStitched(this->BodyPartType) {
 this->DrawTexture(this->stitchTex, 0.0, 0.0, 1.0);
 }

 if (this->boneTex != nullptr
 && bodyDamage.getBodyPart(this->BodyPartType).getFractureTime() > 0.0F
 && bodyDamage.getBodyPart(this->BodyPartType).getSplintFactor() == 0.0F) {
 this->DrawTexture(this->boneTex, 0.0, 0.0, 1.0);
 } else if (this->splintTex != nullptr && bodyDamage.getBodyPart(this->BodyPartType).getSplintFactor() > 0.0F) {
 this->DrawTexture(this->splintTex, 0.0, 0.0, 1.0);
 }

 if (this->glassTex != nullptr && bodyDamage.getBodyPart(this->BodyPartType).haveGlass() && !bodyDamage.getBodyPart(this->BodyPartType).bandaged()) {
 this->DrawTexture(this->glassTex, 0.0, 0.0, 1.0);
 }

 if (this->bulletTex != nullptr && bodyDamage.getBodyPart(this->BodyPartType).haveBullet() && !bodyDamage.getBodyPart(this->BodyPartType).bandaged()) {
 this->DrawTexture(this->bulletTex, 0.0, 0.0, 1.0);
 }

 if (this->burnTex != nullptr && bodyDamage.getBodyPart(this->BodyPartType).getBurnTime() > 0.0F && !bodyDamage.getBodyPart(this->BodyPartType).bandaged()) {
 this->DrawTexture(this->burnTex, 0.0, 0.0, bodyDamage.getBodyPart(this->BodyPartType).getBurnTime() / 100.0F);
 }

 super.render();
 }
}
} // namespace ui
} // namespace zombie
