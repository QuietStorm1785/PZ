package zombie.erosion.obj;

import java.util.ArrayList;
import zombie.core.Core;
import zombie.debug.DebugLog;
import zombie.iso.IsoDirections;
import zombie.iso.sprite.IsoDirectionFrame;
import zombie.iso.sprite.IsoSprite;
import zombie.iso.sprite.IsoSpriteManager;
import zombie.network.GameServer;

final class ErosionObjSprites$Sprites {
   public final ArrayList<String> sprites = new ArrayList<>();
   private int index = -1;

   public ErosionObjSprites$Sprites(String var1) {
      if (Core.bDebug || GameServer.bServer && GameServer.bDebug) {
         IsoSprite var2 = IsoSpriteManager.instance.getSprite(var1);
         if (var2.CurrentAnim.Frames.size() == 0
            || !GameServer.bServer && ((IsoDirectionFrame)var2.CurrentAnim.Frames.get(0)).getTexture(IsoDirections.N) == null
            || var2.ID < 10000) {
            DebugLog.log("EMPTY SPRITE " + var1);
         }
      }

      this.sprites.add(var1);
   }

   public ErosionObjSprites$Sprites(ArrayList<String> var1) {
      if (Core.bDebug || GameServer.bServer && GameServer.bDebug) {
         for (int var2 = 0; var2 < var1.size(); var2++) {
            IsoSprite var3 = IsoSpriteManager.instance.getSprite((String)var1.get(var2));
            if (var3.CurrentAnim.Frames.size() == 0
               || !GameServer.bServer && ((IsoDirectionFrame)var3.CurrentAnim.Frames.get(0)).getTexture(IsoDirections.N) == null
               || var3.ID < 10000) {
               DebugLog.log("EMPTY SPRITE " + (String)var1.get(var2));
            }
         }
      }

      this.sprites.addAll(var1);
   }

   public String getNext() {
      if (++this.index >= this.sprites.size()) {
         this.index = 0;
      }

      return this.sprites.get(this.index);
   }
}
