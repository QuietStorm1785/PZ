package zombie.core.skinnedmodel;

import java.util.ArrayList;
import zombie.core.skinnedmodel.CharacterTextures.CTState;
import zombie.core.skinnedmodel.DeadBodyAtlas.BodyTexture;
import zombie.iso.IsoDirections;

final class CharacterTextures$CTAnimSet {
   String m_name;
   final ArrayList<CTState> m_states = new ArrayList<>();

   private CharacterTextures$CTAnimSet() {
   }

   CTState getState(String var1) {
      for (int var2 = 0; var2 < this.m_states.size(); var2++) {
         CTState var3 = this.m_states.get(var2);
         if (var3.m_name.equals(var1)) {
            return var3;
         }
      }

      return null;
   }

   void addEntry(String var1, IsoDirections var2, int var3, BodyTexture var4) {
      CTState var5 = this.getState(var1);
      if (var5 == null) {
         var5 = new CTState();
         var5.m_name = var1;
         this.m_states.add(var5);
      }

      var5.addEntry(var2, var3, var4);
   }
}
