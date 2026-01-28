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


class UI_BodyPart : public UIElement {
public:
    float alpha = 1.0F;
    const Color color = std::make_shared<Color>(1.0F, 1.0F, 1.0F, 1.0F);
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

   // ImGui rendering override
   virtual void ImGuiRender() override;

    public UI_BodyPart(BodyPartType var1, int var2, int var3, const std::string& var4, IsoGameCharacter var5, bool var6) {
    std::string var7 = "male";
      if (var5.isFemale()) {
         var7 = "female";
      }

      this.chr = var5;
      this.BodyPartType = var1;
      this.scratchTex = Texture.getSharedTexture("media/ui/BodyDamage/" + var7 + "_scratch_" + var4);
      this.bandageTex = Texture.getSharedTexture("media/ui/BodyDamage/" + var7 + "_bandage_" + var4);
      this.dirtyBandageTex = Texture.getSharedTexture("media/ui/BodyDamage/" + var7 + "_bandagedirty_" + var4);
      this.infectionTex = Texture.getSharedTexture("media/ui/BodyDamage/" + var7 + "_infection_" + var4);
      this.biteTex = Texture.getSharedTexture("media/ui/BodyDamage/" + var7 + "_bite_" + var4);
      this.deepWoundTex = Texture.getSharedTexture("media/ui/BodyDamage/" + var7 + "_deepwound_" + var4);
      this.stitchTex = Texture.getSharedTexture("media/ui/BodyDamage/" + var7 + "_stitches_" + var4);
      this.glassTex = Texture.getSharedTexture("media/ui/BodyDamage/" + var7 + "_glass_" + var4);
      this.boneTex = Texture.getSharedTexture("media/ui/BodyDamage/" + var7 + "_bones_" + var4);
      this.splintTex = Texture.getSharedTexture("media/ui/BodyDamage/" + var7 + "_splint_" + var4);
      this.burnTex = Texture.getSharedTexture("media/ui/BodyDamage/" + var7 + "_burn_" + var4);
      this.bulletTex = Texture.getSharedTexture("media/ui/BodyDamage/" + var7 + "_bullet_" + var4);
      this.x = var2;
      this.y = var3;
      this.width = this.scratchTex.getWidth();
      this.height = this.scratchTex.getHeight();
      this.IsFlipped = var6;
   }

    void onMouseMoveOutside(double var1, double var3) {
      this.mouseOver = false;
   }

    void render() {
    BodyDamage var1 = this.chr.getBodyDamage();
      if (GameClient.bClient && this.dynamic_cast<IsoPlayer*>(chr) != nullptr && !((IsoPlayer)this.chr).isLocalPlayer()) {
         var1 = this.chr.getBodyDamageRemote();
      }

      if (this.infectionTex != nullptr && !var1.IsBandaged(this.BodyPartType) && var1.getBodyPart(this.BodyPartType).getWoundInfectionLevel() > 0.0F) {
         this.DrawTexture(this.infectionTex, 0.0, 0.0, var1.getBodyPart(this.BodyPartType).getWoundInfectionLevel() / 10.0F);
      }

      if (this.bandageTex != nullptr && var1.IsBandaged(this.BodyPartType) && var1.getBodyPart(this.BodyPartType).getBandageLife() > 0.0F) {
         this.DrawTexture(this.bandageTex, 0.0, 0.0, 1.0);
      } else if (this.dirtyBandageTex != nullptr && var1.IsBandaged(this.BodyPartType) && var1.getBodyPart(this.BodyPartType).getBandageLife() <= 0.0F) {
         this.DrawTexture(this.dirtyBandageTex, 0.0, 0.0, 1.0);
      } else if (this.scratchTex != nullptr && var1.IsScratched(this.BodyPartType)) {
         this.DrawTexture(this.scratchTex, 0.0, 0.0, var1.getBodyPart(this.BodyPartType).getScratchTime() / 20.0F);
      } else if (this.scratchTex != nullptr && var1.IsCut(this.BodyPartType)) {
         this.DrawTexture(this.scratchTex, 0.0, 0.0, var1.getBodyPart(this.BodyPartType).getCutTime() / 20.0F);
      } else if (this.biteTex != nullptr
         && !var1.IsBandaged(this.BodyPartType)
         && var1.IsBitten(this.BodyPartType)
         && var1.getBodyPart(this.BodyPartType).getBiteTime() >= 0.0F) {
         this.DrawTexture(this.biteTex, 0.0, 0.0, 1.0);
      } else if (this.deepWoundTex != nullptr && var1.IsDeepWounded(this.BodyPartType)) {
         this.DrawTexture(this.deepWoundTex, 0.0, 0.0, var1.getBodyPart(this.BodyPartType).getDeepWoundTime() / 15.0F);
      } else if (this.stitchTex != nullptr && var1.IsStitched(this.BodyPartType)) {
         this.DrawTexture(this.stitchTex, 0.0, 0.0, 1.0);
      }

      if (this.boneTex != nullptr && var1.getBodyPart(this.BodyPartType).getFractureTime() > 0.0F && var1.getBodyPart(this.BodyPartType).getSplintFactor() == 0.0F
         )
       {
         this.DrawTexture(this.boneTex, 0.0, 0.0, 1.0);
      } else if (this.splintTex != nullptr && var1.getBodyPart(this.BodyPartType).getSplintFactor() > 0.0F) {
         this.DrawTexture(this.splintTex, 0.0, 0.0, 1.0);
      }

      if (this.glassTex != nullptr && var1.getBodyPart(this.BodyPartType).haveGlass() && !var1.getBodyPart(this.BodyPartType).bandaged()) {
         this.DrawTexture(this.glassTex, 0.0, 0.0, 1.0);
      }

      if (this.bulletTex != nullptr && var1.getBodyPart(this.BodyPartType).haveBullet() && !var1.getBodyPart(this.BodyPartType).bandaged()) {
         this.DrawTexture(this.bulletTex, 0.0, 0.0, 1.0);
      }

      if (this.burnTex != nullptr && var1.getBodyPart(this.BodyPartType).getBurnTime() > 0.0F && !var1.getBodyPart(this.BodyPartType).bandaged()) {
         this.DrawTexture(this.burnTex, 0.0, 0.0, var1.getBodyPart(this.BodyPartType).getBurnTime() / 100.0F);
      }

      super.render();
   }
}
} // namespace ui
} // namespace zombie
