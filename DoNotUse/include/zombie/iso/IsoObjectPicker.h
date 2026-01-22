#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/IsoObjectPicker/1.h"
#include "zombie/iso/IsoObjectPicker/ClickObject.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/objects/IsoCurtain.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/iso/sprite/IsoDirectionFrame.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <algorithm>

namespace zombie {
namespace iso {


class IsoObjectPicker {
public:
    static const IsoObjectPicker Instance = std::make_shared<IsoObjectPicker>();
   static const std::vector<ClickObject> choices = std::make_unique<std::vector<>>();
    static const Vector2 tempo = std::make_shared<Vector2>();
    static const Vector2 tempo2 = std::make_shared<Vector2>();
   static const Comparator<ClickObject> comp = std::make_unique<1>();
   public ClickObject[] ClickObjectStore = new ClickObject[15000];
    int count = 0;
    int counter = 0;
    int maxcount = 0;
   public const std::vector<ClickObject> ThisFrame = std::make_unique<std::vector<>>();
    bool dirty = true;
    float xOffSinceDirty = 0.0F;
    float yOffSinceDirty = 0.0F;
    bool wasDirty = false;
    ClickObject LastPickObject = nullptr;
    float lx = 0.0F;
    float ly = 0.0F;

    IsoObjectPicker getInstance() {
    return Instance;
   }

    void Add(int var1, int var2, int var3, int var4, IsoGridSquare var5, IsoObject var6, bool var7, float var8, float var9) {
      if (!(var1 + var3 <= this.lx - 32.0F) && !(var1 >= this.lx + 32.0F) && !(var2 + var4 <= this.ly - 32.0F) && !(var2 >= this.ly + 32.0F)) {
         if (this.ThisFrame.size() < 15000) {
            if (!var6.NoPicking) {
               if (dynamic_cast<IsoSurvivor*>(var6) != nullptr) {
    bool var10 = false;
               }

               if (dynamic_cast<IsoDoor*>(var6) != nullptr) {
    bool var11 = false;
               }

               if (var1 <= Core.getInstance().getOffscreenWidth(0)) {
                  if (var2 <= Core.getInstance().getOffscreenHeight(0)) {
                     if (var1 + var3 >= 0) {
                        if (var2 + var4 >= 0) {
    ClickObject var12 = this.ClickObjectStore[this.ThisFrame.size()];
                           this.ThisFrame.push_back(var12);
                           this.count = this.ThisFrame.size();
                           var12.x = var1;
                           var12.y = var2;
                           var12.width = var3;
                           var12.height = var4;
                           var12.square = var5;
                           var12.tile = var6;
                           var12.flip = var7;
                           var12.scaleX = var8;
                           var12.scaleY = var9;
                           if (var12.dynamic_cast<IsoGameCharacter*>(tile) != nullptr) {
                              var12.flip = false;
                           }

                           if (this.count > this.maxcount) {
                              this.maxcount = this.count;
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void Init() {
      this.ThisFrame.clear();
      this.LastPickObject = nullptr;

      for (int var1 = 0; var1 < 15000; var1++) {
         this.ClickObjectStore[var1] = std::make_unique<ClickObject>();
      }
   }

    ClickObject ContextPick(int var1, int var2) {
    float var3 = var1 * Core.getInstance().getZoom(0);
    float var4 = var2 * Core.getInstance().getZoom(0);
      choices.clear();
      this.counter++;

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
    ClickObject var6 = this.ThisFrame.get(var5);
         if ((!(var6.dynamic_cast<IsoPlayer*>(tile) != nullptr) || var6.tile != IsoPlayer.players[0])
            && (
               var6.tile.sprite == nullptr
                  || var6.tile.getTargetAlpha(0) != 0.0F
                     && (
                        !var6.tile.sprite.Properties.Is(IsoFlagType.cutW) && !var6.tile.sprite.Properties.Is(IsoFlagType.cutN)
                           || var6.dynamic_cast<IsoWindow*>(tile) != nullptr
                           || !(var6.tile.getTargetAlpha(0) < 1.0F)
                     )
            )) {
            if (var6.tile != nullptr && var6.tile.sprite != nullptr) {
            }

            if (var3 > var6.x && var4 > var6.y && var3 <= var6.x + var6.width && var4 <= var6.y + var6.height) {
               if (var6.dynamic_cast<IsoPlayer*>(tile) != nullptr) {
                  if (var6.tile.sprite == nullptr
                     || var6.tile.sprite.def == nullptr
                     || var6.tile.sprite.CurrentAnim == nullptr
                     || var6.tile.sprite.CurrentAnim.Frames == nullptr
                     || var6.tile.sprite.def.Frame < 0.0F
                     || var6.tile.sprite.def.Frame >= var6.tile.sprite.CurrentAnim.Frames.size()) {
                     continue;
                  }

    int var7 = (int)(var3 - var6.x);
    int var8 = (int)(var4 - var6.y);
    Texture var9 = ((IsoDirectionFrame)var6.tile.sprite.CurrentAnim.Frames.get((int)var6.tile.sprite.def.Frame)).directions[var6.tile.dir.index()];
    int var10 = Core.TileScale;
                  if (var6.flip) {
                     var8 = (int)(var8 - var9.offsetY);
                     var7 = var9.getWidth() - var8;
                  } else {
                     var7 = (int)(var7 - var9.offsetX * var10);
                     var8 = (int)(var8 - var9.offsetY * var10);
                  }

                  if (var7 >= 0 && var8 >= 0 && var7 <= var9.getWidth() * var10 && var8 <= var9.getHeight() * var10) {
                     var6.lx = (int)var3 - var6.x;
                     var6.ly = (int)var4 - var6.y;
                     this.LastPickObject = var6;
                     choices.clear();
                     choices.push_back(var6);
                     break;
                  }
               }

               if (var6.scaleX == 1.0F && var6.scaleY == 1.0F) {
                  if (var6.tile.isMaskClicked((int)(var3 - var6.x), (int)(var4 - var6.y), var6.flip)) {
                     if (var6.tile.rerouteMask != nullptr) {
                        var6.tile = var6.tile.rerouteMask;
                     }

                     var6.lx = (int)var3 - var6.x;
                     var6.ly = (int)var4 - var6.y;
                     this.LastPickObject = var6;
                     choices.push_back(var6);
                  }
               } else {
    float var15 = var6.x + (var3 - var6.x) / var6.scaleX;
    float var17 = var6.y + (var4 - var6.y) / var6.scaleY;
                  if (var6.tile.isMaskClicked((int)(var15 - var6.x), (int)(var17 - var6.y), var6.flip)) {
                     if (var6.tile.rerouteMask != nullptr) {
                        var6.tile = var6.tile.rerouteMask;
                     }

                     var6.lx = (int)var3 - var6.x;
                     var6.ly = (int)var4 - var6.y;
                     this.LastPickObject = var6;
                     choices.push_back(var6);
                  }
               }
            }
         }
      }

      if (choices.empty()) {
    return nullptr;
      } else {
         for (int var12 = 0; var12 < choices.size(); var12++) {
    ClickObject var13 = choices.get(var12);
            var13.score = var13.calculateScore();
         }

         try {
            Collections.sort(choices, comp);
         } catch (IllegalArgumentException var11) {
            if (Core.bDebug) {
               ExceptionLogger.logException(var11);
            }

    return nullptr;
         }

         return choices.get(choices.size() - 1);
      }
   }

    ClickObject Pick(int var1, int var2) {
    float var3 = var1;
    float var4 = var2;
    float var5 = Core.getInstance().getScreenWidth();
    float var6 = Core.getInstance().getScreenHeight();
    float var7 = var5 * Core.getInstance().getZoom(0);
    float var8 = var6 * Core.getInstance().getZoom(0);
    float var9 = Core.getInstance().getOffscreenWidth(0);
    float var10 = Core.getInstance().getOffscreenHeight(0);
    float var11 = var9 / var7;
    float var12 = var10 / var8;
      var3 -= var5 / 2.0F;
      var4 -= var6 / 2.0F;
      var3 /= var11;
      var4 /= var12;
      var3 += var5 / 2.0F;
      var4 += var6 / 2.0F;
      this.counter++;

      for (int var13 = this.ThisFrame.size() - 1; var13 >= 0; var13--) {
    ClickObject var14 = this.ThisFrame.get(var13);
         if (var14.tile.square != nullptr) {
         }

         if (!(var14.dynamic_cast<IsoPlayer*>(tile) != nullptr) && (var14.tile.sprite == nullptr || var14.tile.getTargetAlpha(0) != 0.0F)) {
            if (var14.tile != nullptr && var14.tile.sprite != nullptr) {
            }

            if (var3 > var14.x && var4 > var14.y && var3 <= var14.x + var14.width && var4 <= var14.y + var14.height) {
               if (var14.dynamic_cast<IsoSurvivor*>(tile) != nullptr) {
    bool var15 = false;
               } else if (var14.tile.isMaskClicked((int)(var3 - var14.x), (int)(var4 - var14.y), var14.flip)) {
                  if (var14.tile.rerouteMask != nullptr) {
                     var14.tile = var14.tile.rerouteMask;
                  }

                  var14.lx = (int)var3 - var14.x;
                  var14.ly = (int)var4 - var14.y;
                  this.LastPickObject = var14;
    return var14;
               }
            }
         }
      }

    return nullptr;
   }

    void StartRender() {
    float var1 = Mouse.getX();
    float var2 = Mouse.getY();
      if (var1 != this.lx || var2 != this.ly) {
         this.dirty = true;
      }

      this.lx = var1;
      this.ly = var2;
      if (this.dirty) {
         this.ThisFrame.clear();
         this.count = 0;
         this.wasDirty = true;
         this.dirty = false;
         this.xOffSinceDirty = 0.0F;
         this.yOffSinceDirty = 0.0F;
      } else {
         this.wasDirty = false;
      }
   }

    IsoMovingObject PickTarget(int var1, int var2) {
    float var3 = var1;
    float var4 = var2;
    float var5 = Core.getInstance().getScreenWidth();
    float var6 = Core.getInstance().getScreenHeight();
    float var7 = var5 * Core.getInstance().getZoom(0);
    float var8 = var6 * Core.getInstance().getZoom(0);
    float var9 = Core.getInstance().getOffscreenWidth(0);
    float var10 = Core.getInstance().getOffscreenHeight(0);
    float var11 = var9 / var7;
    float var12 = var10 / var8;
      var3 -= var5 / 2.0F;
      var4 -= var6 / 2.0F;
      var3 /= var11;
      var4 /= var12;
      var3 += var5 / 2.0F;
      var4 += var6 / 2.0F;
      this.counter++;

      for (int var13 = this.ThisFrame.size() - 1; var13 >= 0; var13--) {
    ClickObject var14 = this.ThisFrame.get(var13);
         if (var14.tile.square != nullptr) {
         }

         if (var14.tile != IsoPlayer.getInstance() && (var14.tile.sprite == nullptr || var14.tile.getTargetAlpha() != 0.0F)) {
            if (var14.tile != nullptr && var14.tile.sprite != nullptr) {
            }

            if (var3 > var14.x
               && var4 > var14.y
               && var3 <= var14.x + var14.width
               && var4 <= var14.y + var14.height
               && var14.dynamic_cast<IsoMovingObject*>(tile) != nullptr
               && var14.tile.isMaskClicked((int)(var3 - var14.x), (int)(var4 - var14.y), var14.flip)) {
               if (var14.tile.rerouteMask != nullptr) {
               }

               var14.lx = (int)(var3 - var14.x);
               var14.ly = (int)(var4 - var14.y);
               this.LastPickObject = var14;
               return (IsoMovingObject)var14.tile;
            }
         }
      }

    return nullptr;
   }

    IsoObject PickDoor(int var1, int var2, bool var3) {
    float var4 = var1 * Core.getInstance().getZoom(0);
    float var5 = var2 * Core.getInstance().getZoom(0);
    int var6 = IsoPlayer.getPlayerIndex();

      for (int var7 = this.ThisFrame.size() - 1; var7 >= 0; var7--) {
    ClickObject var8 = this.ThisFrame.get(var7);
         if (var8.dynamic_cast<IsoDoor*>(tile) != nullptr
            && var8.tile.getTargetAlpha(var6) != 0.0F
            && var3 == var8.tile.getTargetAlpha(var6) < 1.0F
            && var4 >= var8.x
            && var5 >= var8.y
            && var4 < var8.x + var8.width
            && var5 < var8.y + var8.height) {
    int var9 = (int)(var4 - var8.x);
    int var10 = (int)(var5 - var8.y);
            if (var8.tile.isMaskClicked(var9, var10, var8.flip)) {
               return var8.tile;
            }
         }
      }

    return nullptr;
   }

    IsoObject PickWindow(int var1, int var2) {
    float var3 = var1 * Core.getInstance().getZoom(0);
    float var4 = var2 * Core.getInstance().getZoom(0);

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
    ClickObject var6 = this.ThisFrame.get(var5);
         if ((var6.dynamic_cast<IsoWindow*>(tile) != nullptr || var6.dynamic_cast<IsoCurtain*>(tile) != nullptr)
            && (var6.tile.sprite == nullptr || var6.tile.getTargetAlpha() != 0.0F)
            && var3 >= var6.x
            && var4 >= var6.y
            && var3 < var6.x + var6.width
            && var4 < var6.y + var6.height) {
    int var7 = (int)(var3 - var6.x);
    int var8 = (int)(var4 - var6.y);
            if (var6.tile.isMaskClicked(var7, var8, var6.flip)) {
               return var6.tile;
            }

            if (var6.dynamic_cast<IsoWindow*>(tile) != nullptr) {
    bool var9 = false;
    bool var10 = false;

               for (int var11 = var8; var11 >= 0; var11--) {
                  if (var6.tile.isMaskClicked(var7, var11)) {
                     var9 = true;
                     break;
                  }
               }

               for (int var12 = var8; var12 < var6.height; var12++) {
                  if (var6.tile.isMaskClicked(var7, var12)) {
                     var10 = true;
                     break;
                  }
               }

               if (var9 && var10) {
                  return var6.tile;
               }
            }
         }
      }

    return nullptr;
   }

    IsoObject PickWindowFrame(int var1, int var2) {
    float var3 = var1 * Core.getInstance().getZoom(0);
    float var4 = var2 * Core.getInstance().getZoom(0);

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
    ClickObject var6 = this.ThisFrame.get(var5);
         if (IsoWindowFrame.isWindowFrame(var6.tile)
            && (var6.tile.sprite == nullptr || var6.tile.getTargetAlpha() != 0.0F)
            && var3 >= var6.x
            && var4 >= var6.y
            && var3 < var6.x + var6.width
            && var4 < var6.y + var6.height) {
    int var7 = (int)(var3 - var6.x);
    int var8 = (int)(var4 - var6.y);
            if (var6.tile.isMaskClicked(var7, var8, var6.flip)) {
               return var6.tile;
            }

    bool var9 = false;
    bool var10 = false;

            for (int var11 = var8; var11 >= 0; var11--) {
               if (var6.tile.isMaskClicked(var7, var11)) {
                  var9 = true;
                  break;
               }
            }

            for (int var12 = var8; var12 < var6.height; var12++) {
               if (var6.tile.isMaskClicked(var7, var12)) {
                  var10 = true;
                  break;
               }
            }

            if (var9 && var10) {
               return var6.tile;
            }
         }
      }

    return nullptr;
   }

    IsoObject PickThumpable(int var1, int var2) {
    float var3 = var1 * Core.getInstance().getZoom(0);
    float var4 = var2 * Core.getInstance().getZoom(0);

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
    ClickObject var6 = this.ThisFrame.get(var5);
         if (var6.dynamic_cast<IsoThumpable*>(tile) != nullptr var7
            && (var6.tile.sprite == nullptr || var6.tile.getTargetAlpha() != 0.0F)
            && var3 >= var6.x
            && var4 >= var6.y
            && var3 < var6.x + var6.width
            && var4 < var6.y + var6.height) {
    int var8 = (int)(var3 - var6.x);
    int var9 = (int)(var4 - var6.y);
            if (var6.tile.isMaskClicked(var8, var9, var6.flip)) {
               return var6.tile;
            }
         }
      }

    return nullptr;
   }

    IsoObject PickHoppable(int var1, int var2) {
    float var3 = var1 * Core.getInstance().getZoom(0);
    float var4 = var2 * Core.getInstance().getZoom(0);

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
    ClickObject var6 = this.ThisFrame.get(var5);
         if (var6.tile.isHoppable()
            && (var6.tile.sprite == nullptr || var6.tile.getTargetAlpha() != 0.0F)
            && var3 >= var6.x
            && var4 >= var6.y
            && var3 < var6.x + var6.width
            && var4 < var6.y + var6.height) {
    int var7 = (int)(var3 - var6.x);
    int var8 = (int)(var4 - var6.y);
            if (var6.tile.isMaskClicked(var7, var8, var6.flip)) {
               return var6.tile;
            }
         }
      }

    return nullptr;
   }

    IsoObject PickCorpse(int var1, int var2) {
    float var3 = var1 * Core.getInstance().getZoom(0);
    float var4 = var2 * Core.getInstance().getZoom(0);

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
    ClickObject var6 = this.ThisFrame.get(var5);
         if (var3 >= var6.x && var4 >= var6.y && var3 < var6.x + var6.width && var4 < var6.y + var6.height && !(var6.tile.getTargetAlpha() < 1.0F)) {
            if (var6.tile.isMaskClicked((int)(var3 - var6.x), (int)(var4 - var6.y), var6.flip) && !(var6.dynamic_cast<IsoWindow*>(tile) != nullptr)) {
    return nullptr;
            }

            if (var6.dynamic_cast<IsoDeadBody*>(tile) != nullptr && ((IsoDeadBody)var6.tile).isMouseOver(var3, var4)) {
               return var6.tile;
            }
         }
      }

    return nullptr;
   }

    IsoObject PickTree(int var1, int var2) {
    float var3 = var1 * Core.getInstance().getZoom(0);
    float var4 = var2 * Core.getInstance().getZoom(0);

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
    ClickObject var6 = this.ThisFrame.get(var5);
         if (var6.dynamic_cast<IsoTree*>(tile) != nullptr
            && (var6.tile.sprite == nullptr || var6.tile.getTargetAlpha() != 0.0F)
            && var3 >= var6.x
            && var4 >= var6.y
            && var3 < var6.x + var6.width
            && var4 < var6.y + var6.height) {
    int var7 = (int)(var3 - var6.x);
    int var8 = (int)(var4 - var6.y);
            if (var6.tile.isMaskClicked(var7, var8, var6.flip)) {
               return var6.tile;
            }
         }
      }

    return nullptr;
   }

    BaseVehicle PickVehicle(int var1, int var2) {
    float var3 = IsoUtils.XToIso(var1, var2, 0.0F);
    float var4 = IsoUtils.YToIso(var1, var2, 0.0F);

      for (int var5 = 0; var5 < IsoWorld.instance.CurrentCell.getVehicles().size(); var5++) {
    BaseVehicle var6 = (BaseVehicle)IsoWorld.instance.CurrentCell.getVehicles().get(var5);
         if (var6.isInBounds(var3, var4)) {
    return var6;
         }
      }

    return nullptr;
   }
}
} // namespace iso
} // namespace zombie
