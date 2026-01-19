package zombie.iso.objects;

import java.io.IOException;
import zombie.GameWindow;
import zombie.gameStates.GameLoadingState;
import zombie.inventory.types.Moveable;
import zombie.iso.IsoDirections;
import zombie.iso.IsoWorld;
import zombie.iso.sprite.IsoSprite;
import zombie.iso.sprite.IsoSpriteManager;
import zombie.network.GameServer;

final class IsoMannequin$StaticPerPlayer {
   final int playerIndex;
   Moveable _moveable = null;
   Moveable _failedItem = null;
   IsoMannequin _mannequin = null;

   IsoMannequin$StaticPerPlayer(int var1) {
      this.playerIndex = var1;
   }

   void renderMoveableItem(Moveable var1, int var2, int var3, int var4, IsoDirections var5) {
      if (this.checkItem(var1)) {
         if (this._moveable != var1) {
            this._moveable = var1;

            try {
               this._mannequin.getCustomSettingsFromItem(this._moveable);
            } catch (IOException var7) {
            }

            this._mannequin.initOutfit();
            this._mannequin.validateSkinTexture();
            this._mannequin.validatePose();
            this._mannequin.syncModel();
            this._mannequin.perPlayer[this.playerIndex].atlasTex = null;
         }

         this._mannequin.square = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
         if (this._mannequin.square != null) {
            this._mannequin.perPlayer[this.playerIndex].renderDirection = var5;
            IsoMannequin.inf.set(1.0F, 1.0F, 1.0F, 1.0F);
            this._mannequin.render(var2, var3, var4, IsoMannequin.inf, false, false, null);
         }
      }
   }

   IsoDirections getDirectionFromItem(Moveable var1) {
      if (!this.checkItem(var1)) {
         return IsoDirections.S;
      } else {
         this._moveable = null;

         try {
            this._mannequin.getCustomSettingsFromItem(var1);
            return this._mannequin.getDir();
         } catch (Exception var3) {
            return IsoDirections.S;
         }
      }
   }

   boolean checkItem(Moveable var1) {
      if (var1 == null) {
         return false;
      } else {
         String var2 = var1.getWorldSprite();
         IsoSprite var3 = IsoSpriteManager.instance.getSprite(var2);
         if (var3 == null || !IsoMannequin.isMannequinSprite(var3)) {
            return false;
         } else if (var1.getByteData() == null) {
            Thread var4 = Thread.currentThread();
            if (var4 != GameWindow.GameThread && var4 != GameLoadingState.loader && var4 == GameServer.MainThread) {
               return false;
            } else {
               if (this._mannequin == null || this._mannequin.getCell() != IsoWorld.instance.CurrentCell) {
                  this._mannequin = new IsoMannequin(IsoWorld.instance.CurrentCell);
               }

               if (this._failedItem == var1) {
                  return false;
               } else {
                  try {
                     this._mannequin.resetMannequin();
                     this._mannequin.sprite = var3;
                     this._mannequin.initOutfit();
                     this._mannequin.validateSkinTexture();
                     this._mannequin.validatePose();
                     this._mannequin.syncModel();
                     this._mannequin.setCustomSettingsToItem(var1);
                     return true;
                  } catch (IOException var6) {
                     this._failedItem = var1;
                     return false;
                  }
               }
            }
         } else {
            if (this._mannequin == null || this._mannequin.getCell() != IsoWorld.instance.CurrentCell) {
               this._mannequin = new IsoMannequin(IsoWorld.instance.CurrentCell);
            }

            return true;
         }
      }
   }
}
