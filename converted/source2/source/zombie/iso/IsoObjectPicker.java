package zombie.iso;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoSurvivor;
import zombie.core.Core;
import zombie.core.logger.ExceptionLogger;
import zombie.core.textures.Texture;
import zombie.input.Mouse;
import zombie.iso.IsoObjectPicker.1;
import zombie.iso.IsoObjectPicker.ClickObject;
import zombie.iso.SpriteDetails.IsoFlagType;
import zombie.iso.objects.IsoCurtain;
import zombie.iso.objects.IsoDeadBody;
import zombie.iso.objects.IsoDoor;
import zombie.iso.objects.IsoThumpable;
import zombie.iso.objects.IsoTree;
import zombie.iso.objects.IsoWindow;
import zombie.iso.objects.IsoWindowFrame;
import zombie.iso.sprite.IsoDirectionFrame;
import zombie.vehicles.BaseVehicle;

public final class IsoObjectPicker {
   public static final IsoObjectPicker Instance = new IsoObjectPicker();
   static final ArrayList<ClickObject> choices = new ArrayList<>();
   static final Vector2 tempo = new Vector2();
   static final Vector2 tempo2 = new Vector2();
   static final Comparator<ClickObject> comp = new 1();
   public ClickObject[] ClickObjectStore = new ClickObject[15000];
   public int count = 0;
   public int counter = 0;
   public int maxcount = 0;
   public final ArrayList<ClickObject> ThisFrame = new ArrayList<>();
   public boolean dirty = true;
   public float xOffSinceDirty = 0.0F;
   public float yOffSinceDirty = 0.0F;
   public boolean wasDirty = false;
   ClickObject LastPickObject = null;
   float lx = 0.0F;
   float ly = 0.0F;

   public IsoObjectPicker getInstance() {
      return Instance;
   }

   public void Add(int var1, int var2, int var3, int var4, IsoGridSquare var5, IsoObject var6, boolean var7, float var8, float var9) {
      if (!(var1 + var3 <= this.lx - 32.0F) && !(var1 >= this.lx + 32.0F) && !(var2 + var4 <= this.ly - 32.0F) && !(var2 >= this.ly + 32.0F)) {
         if (this.ThisFrame.size() < 15000) {
            if (!var6.NoPicking) {
               if (var6 instanceof IsoSurvivor) {
                  boolean var10 = false;
               }

               if (var6 instanceof IsoDoor) {
                  boolean var11 = false;
               }

               if (var1 <= Core.getInstance().getOffscreenWidth(0)) {
                  if (var2 <= Core.getInstance().getOffscreenHeight(0)) {
                     if (var1 + var3 >= 0) {
                        if (var2 + var4 >= 0) {
                           ClickObject var12 = this.ClickObjectStore[this.ThisFrame.size()];
                           this.ThisFrame.add(var12);
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
                           if (var12.tile instanceof IsoGameCharacter) {
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

   public void Init() {
      this.ThisFrame.clear();
      this.LastPickObject = null;

      for (int var1 = 0; var1 < 15000; var1++) {
         this.ClickObjectStore[var1] = new ClickObject();
      }
   }

   public ClickObject ContextPick(int var1, int var2) {
      float var3 = var1 * Core.getInstance().getZoom(0);
      float var4 = var2 * Core.getInstance().getZoom(0);
      choices.clear();
      this.counter++;

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
         ClickObject var6 = this.ThisFrame.get(var5);
         if ((!(var6.tile instanceof IsoPlayer) || var6.tile != IsoPlayer.players[0])
            && (
               var6.tile.sprite == null
                  || var6.tile.getTargetAlpha(0) != 0.0F
                     && (
                        !var6.tile.sprite.Properties.Is(IsoFlagType.cutW) && !var6.tile.sprite.Properties.Is(IsoFlagType.cutN)
                           || var6.tile instanceof IsoWindow
                           || !(var6.tile.getTargetAlpha(0) < 1.0F)
                     )
            )) {
            if (var6.tile != null && var6.tile.sprite != null) {
            }

            if (var3 > var6.x && var4 > var6.y && var3 <= var6.x + var6.width && var4 <= var6.y + var6.height) {
               if (var6.tile instanceof IsoPlayer) {
                  if (var6.tile.sprite == null
                     || var6.tile.sprite.def == null
                     || var6.tile.sprite.CurrentAnim == null
                     || var6.tile.sprite.CurrentAnim.Frames == null
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
                     choices.add(var6);
                     break;
                  }
               }

               if (var6.scaleX == 1.0F && var6.scaleY == 1.0F) {
                  if (var6.tile.isMaskClicked((int)(var3 - var6.x), (int)(var4 - var6.y), var6.flip)) {
                     if (var6.tile.rerouteMask != null) {
                        var6.tile = var6.tile.rerouteMask;
                     }

                     var6.lx = (int)var3 - var6.x;
                     var6.ly = (int)var4 - var6.y;
                     this.LastPickObject = var6;
                     choices.add(var6);
                  }
               } else {
                  float var15 = var6.x + (var3 - var6.x) / var6.scaleX;
                  float var17 = var6.y + (var4 - var6.y) / var6.scaleY;
                  if (var6.tile.isMaskClicked((int)(var15 - var6.x), (int)(var17 - var6.y), var6.flip)) {
                     if (var6.tile.rerouteMask != null) {
                        var6.tile = var6.tile.rerouteMask;
                     }

                     var6.lx = (int)var3 - var6.x;
                     var6.ly = (int)var4 - var6.y;
                     this.LastPickObject = var6;
                     choices.add(var6);
                  }
               }
            }
         }
      }

      if (choices.isEmpty()) {
         return null;
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

            return null;
         }

         return choices.get(choices.size() - 1);
      }
   }

   public ClickObject Pick(int var1, int var2) {
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
         if (var14.tile.square != null) {
         }

         if (!(var14.tile instanceof IsoPlayer) && (var14.tile.sprite == null || var14.tile.getTargetAlpha(0) != 0.0F)) {
            if (var14.tile != null && var14.tile.sprite != null) {
            }

            if (var3 > var14.x && var4 > var14.y && var3 <= var14.x + var14.width && var4 <= var14.y + var14.height) {
               if (var14.tile instanceof IsoSurvivor) {
                  boolean var15 = false;
               } else if (var14.tile.isMaskClicked((int)(var3 - var14.x), (int)(var4 - var14.y), var14.flip)) {
                  if (var14.tile.rerouteMask != null) {
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

      return null;
   }

   public void StartRender() {
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

   public IsoMovingObject PickTarget(int var1, int var2) {
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
         if (var14.tile.square != null) {
         }

         if (var14.tile != IsoPlayer.getInstance() && (var14.tile.sprite == null || var14.tile.getTargetAlpha() != 0.0F)) {
            if (var14.tile != null && var14.tile.sprite != null) {
            }

            if (var3 > var14.x
               && var4 > var14.y
               && var3 <= var14.x + var14.width
               && var4 <= var14.y + var14.height
               && var14.tile instanceof IsoMovingObject
               && var14.tile.isMaskClicked((int)(var3 - var14.x), (int)(var4 - var14.y), var14.flip)) {
               if (var14.tile.rerouteMask != null) {
               }

               var14.lx = (int)(var3 - var14.x);
               var14.ly = (int)(var4 - var14.y);
               this.LastPickObject = var14;
               return (IsoMovingObject)var14.tile;
            }
         }
      }

      return null;
   }

   public IsoObject PickDoor(int var1, int var2, boolean var3) {
      float var4 = var1 * Core.getInstance().getZoom(0);
      float var5 = var2 * Core.getInstance().getZoom(0);
      int var6 = IsoPlayer.getPlayerIndex();

      for (int var7 = this.ThisFrame.size() - 1; var7 >= 0; var7--) {
         ClickObject var8 = this.ThisFrame.get(var7);
         if (var8.tile instanceof IsoDoor
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

      return null;
   }

   public IsoObject PickWindow(int var1, int var2) {
      float var3 = var1 * Core.getInstance().getZoom(0);
      float var4 = var2 * Core.getInstance().getZoom(0);

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
         ClickObject var6 = this.ThisFrame.get(var5);
         if ((var6.tile instanceof IsoWindow || var6.tile instanceof IsoCurtain)
            && (var6.tile.sprite == null || var6.tile.getTargetAlpha() != 0.0F)
            && var3 >= var6.x
            && var4 >= var6.y
            && var3 < var6.x + var6.width
            && var4 < var6.y + var6.height) {
            int var7 = (int)(var3 - var6.x);
            int var8 = (int)(var4 - var6.y);
            if (var6.tile.isMaskClicked(var7, var8, var6.flip)) {
               return var6.tile;
            }

            if (var6.tile instanceof IsoWindow) {
               boolean var9 = false;
               boolean var10 = false;

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

      return null;
   }

   public IsoObject PickWindowFrame(int var1, int var2) {
      float var3 = var1 * Core.getInstance().getZoom(0);
      float var4 = var2 * Core.getInstance().getZoom(0);

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
         ClickObject var6 = this.ThisFrame.get(var5);
         if (IsoWindowFrame.isWindowFrame(var6.tile)
            && (var6.tile.sprite == null || var6.tile.getTargetAlpha() != 0.0F)
            && var3 >= var6.x
            && var4 >= var6.y
            && var3 < var6.x + var6.width
            && var4 < var6.y + var6.height) {
            int var7 = (int)(var3 - var6.x);
            int var8 = (int)(var4 - var6.y);
            if (var6.tile.isMaskClicked(var7, var8, var6.flip)) {
               return var6.tile;
            }

            boolean var9 = false;
            boolean var10 = false;

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

      return null;
   }

   public IsoObject PickThumpable(int var1, int var2) {
      float var3 = var1 * Core.getInstance().getZoom(0);
      float var4 = var2 * Core.getInstance().getZoom(0);

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
         ClickObject var6 = this.ThisFrame.get(var5);
         if (var6.tile instanceof IsoThumpable var7
            && (var6.tile.sprite == null || var6.tile.getTargetAlpha() != 0.0F)
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

      return null;
   }

   public IsoObject PickHoppable(int var1, int var2) {
      float var3 = var1 * Core.getInstance().getZoom(0);
      float var4 = var2 * Core.getInstance().getZoom(0);

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
         ClickObject var6 = this.ThisFrame.get(var5);
         if (var6.tile.isHoppable()
            && (var6.tile.sprite == null || var6.tile.getTargetAlpha() != 0.0F)
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

      return null;
   }

   public IsoObject PickCorpse(int var1, int var2) {
      float var3 = var1 * Core.getInstance().getZoom(0);
      float var4 = var2 * Core.getInstance().getZoom(0);

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
         ClickObject var6 = this.ThisFrame.get(var5);
         if (var3 >= var6.x && var4 >= var6.y && var3 < var6.x + var6.width && var4 < var6.y + var6.height && !(var6.tile.getTargetAlpha() < 1.0F)) {
            if (var6.tile.isMaskClicked((int)(var3 - var6.x), (int)(var4 - var6.y), var6.flip) && !(var6.tile instanceof IsoWindow)) {
               return null;
            }

            if (var6.tile instanceof IsoDeadBody && ((IsoDeadBody)var6.tile).isMouseOver(var3, var4)) {
               return var6.tile;
            }
         }
      }

      return null;
   }

   public IsoObject PickTree(int var1, int var2) {
      float var3 = var1 * Core.getInstance().getZoom(0);
      float var4 = var2 * Core.getInstance().getZoom(0);

      for (int var5 = this.ThisFrame.size() - 1; var5 >= 0; var5--) {
         ClickObject var6 = this.ThisFrame.get(var5);
         if (var6.tile instanceof IsoTree
            && (var6.tile.sprite == null || var6.tile.getTargetAlpha() != 0.0F)
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

      return null;
   }

   public BaseVehicle PickVehicle(int var1, int var2) {
      float var3 = IsoUtils.XToIso(var1, var2, 0.0F);
      float var4 = IsoUtils.YToIso(var1, var2, 0.0F);

      for (int var5 = 0; var5 < IsoWorld.instance.CurrentCell.getVehicles().size(); var5++) {
         BaseVehicle var6 = (BaseVehicle)IsoWorld.instance.CurrentCell.getVehicles().get(var5);
         if (var6.isInBounds(var3, var4)) {
            return var6;
         }
      }

      return null;
   }
}
