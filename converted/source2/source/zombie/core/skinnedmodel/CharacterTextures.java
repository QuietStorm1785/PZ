package zombie.core.skinnedmodel;

import java.util.ArrayList;
import zombie.core.skinnedmodel.CharacterTextures.CTAnimSet;
import zombie.core.skinnedmodel.CharacterTextures.CTEntry;
import zombie.core.skinnedmodel.CharacterTextures.CTState;
import zombie.core.skinnedmodel.DeadBodyAtlas.BodyTexture;
import zombie.iso.IsoDirections;

public final class CharacterTextures {
   final ArrayList<CTAnimSet> m_animSets = new ArrayList<>();

   CTAnimSet getAnimSet(String var1) {
      for (int var2 = 0; var2 < this.m_animSets.size(); var2++) {
         CTAnimSet var3 = this.m_animSets.get(var2);
         if (var3.m_name.equals(var1)) {
            return var3;
         }
      }

      return null;
   }

   BodyTexture getTexture(String var1, String var2, IsoDirections var3, int var4) {
      CTAnimSet var5 = this.getAnimSet(var1);
      if (var5 == null) {
         return null;
      } else {
         CTState var6 = var5.getState(var2);
         if (var6 == null) {
            return null;
         } else {
            CTEntry var7 = var6.getEntry(var3, var4);
            return var7 == null ? null : var7.m_texture;
         }
      }
   }

   void addTexture(String var1, String var2, IsoDirections var3, int var4, BodyTexture var5) {
      CTAnimSet var6 = this.getAnimSet(var1);
      if (var6 == null) {
         var6 = new CTAnimSet();
         var6.m_name = var1;
         this.m_animSets.add(var6);
      }

      var6.addEntry(var2, var3, var4, var5);
   }

   void clear() {
      this.m_animSets.clear();
   }
}
