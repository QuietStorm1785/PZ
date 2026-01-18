#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimatedModel.h"
#include "zombie/core/skinnedmodel/population/IClothingItemListener.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/util/StringUtils.h"
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

class UI3DModel : public UIElement {
public:
  const AnimatedModel animatedModel = new AnimatedModel();
  IsoDirections dir = IsoDirections.E;
  bool bDoExt = false;
  long nextExt = -1L;
private
  final UI3DModel.Drawer[] drawers = new UI3DModel.Drawer[3];
  float zoom = 0.0F;
  float yOffset = 0.0F;
  float xOffset = 0.0F;

public
  UI3DModel(KahluaTable table) {
    super(table);

    for (int int0 = 0; int0 < this.drawers.length; int0++) {
      this.drawers[int0] = new UI3DModel.Drawer();
    }

    if (OutfitManager.instance != nullptr) {
      OutfitManager.instance.addClothingItemListener(this);
    }
  }

  void render() {
    if (this.isVisible()) {
      super.render();
      if (this.Parent == nullptr || this.Parent.maxDrawHeight == -1 ||
          !(this.Parent.maxDrawHeight <= this.y)) {
        if (this.bDoExt) {
          long long0 = System.currentTimeMillis();
          if (this.nextExt < 0L) {
            this.nextExt = long0 + Rand.Next(5000, 10000);
          }

          if (this.nextExt < long0) {
            this.animatedModel.getActionContext().reportEvent("EventDoExt");
            this.animatedModel.setVariable("Ext", Rand.Next(0, 6) + 1);
            this.nextExt = -1L;
          }
        }

        this.animatedModel.update();
        UI3DModel.Drawer drawer =
            this.drawers[SpriteRenderer.instance.getMainStateIndex()];
        drawer.init(this.getAbsoluteX().intValue(),
                    this.getAbsoluteY().intValue());
        SpriteRenderer.instance.drawGeneric(drawer);
      }
    }
  }

  void setDirection(IsoDirections _dir) {
    this.dir = _dir;
    this.animatedModel.setAngle(_dir.ToVector());
  }

  IsoDirections getDirection() { return this.dir; }

  void setAnimate(bool animate) { this.animatedModel.setAnimate(animate); }

  void setAnimSetName(const std::string &name) {
    this.animatedModel.setAnimSetName(name);
  }

  void setDoRandomExtAnimations(bool doExt) { this.bDoExt = doExt; }

  void setIsometric(bool iso) { this.animatedModel.setIsometric(iso); }

  void setOutfitName(const std::string &outfitName, bool female, bool zombie) {
    this.animatedModel.setOutfitName(outfitName, female, zombie);
  }

  void setCharacter(IsoGameCharacter character) {
    this.animatedModel.setCharacter(character);
  }

  void setSurvivorDesc(SurvivorDesc survivorDesc) {
    this.animatedModel.setSurvivorDesc(survivorDesc);
  }

  void setState(const std::string &state) {
    this.animatedModel.setState(state);
  }

  void reportEvent(const std::string &event) {
    if (!StringUtils.isNullOrWhitespace(event)) {
      this.animatedModel.getActionContext().reportEvent(event);
    }
  }

  void clothingItemChanged(const std::string &itemGuid) {
    this.animatedModel.clothingItemChanged(itemGuid);
  }

  void setZoom(float newZoom) { this.zoom = newZoom; }

  void setYOffset(float newYOffset) { this.yOffset = newYOffset; }

  void setXOffset(float newXOffset) { this.xOffset = newXOffset; }

private
  final class Drawer extends TextureDraw.GenericDrawer {
    int absX;
    int absY;
    float m_animPlayerAngle;
    bool bRendered;

    void init(int arg0, int arg1) {
      this.absX = arg0;
      this.absY = arg1;
      this.m_animPlayerAngle =
          UI3DModel.this.animatedModel.getAnimationPlayer().getRenderedAngle();
      this.bRendered = false;
      float float0 =
          UI3DModel.this.animatedModel.isIsometric() ? -0.45F : -0.5F;
      if (UI3DModel.this.yOffset != 0.0F) {
        float0 = UI3DModel.this.yOffset;
      }

      UI3DModel.this.animatedModel.setOffset(UI3DModel.this.xOffset, float0,
                                             0.0F);
      UI3DModel.this.animatedModel.renderMain();
    }

    void render() {
      float float0 = UI3DModel.this.animatedModel.isIsometric() ? 22.0F : 25.0F;
      if (UI3DModel.this.zoom > 0.0F) {
        float0 -= UI3DModel.this.zoom;
      }

      UI3DModel.this.animatedModel.DoRender(
          this.absX, Core.height - this.absY - (int)UI3DModel.this.height,
          (int)UI3DModel.this.width, (int)UI3DModel.this.height, float0,
          this.m_animPlayerAngle);
      this.bRendered = true;
    }

    void postRender() {
      UI3DModel.this.animatedModel.postRender(this.bRendered);
    }
  }
}
} // namespace ui
} // namespace zombie
