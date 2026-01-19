package zombie.core.skinnedmodel;

import zombie.core.skinnedmodel.CharacterTextures.CTEntry;
import zombie.core.skinnedmodel.CharacterTextures.CTEntryList;
import zombie.core.skinnedmodel.DeadBodyAtlas.BodyTexture;
import zombie.iso.IsoDirections;

final class CharacterTextures$CTState {
   String m_name;
   final CTEntryList[] m_entries = new CTEntryList[IsoDirections.values().length];

   CharacterTextures$CTState() {
      for (int var1 = 0; var1 < this.m_entries.length; var1++) {
         this.m_entries[var1] = new CTEntryList();
      }
   }

   CTEntry getEntry(IsoDirections var1, int var2) {
      CTEntryList var3 = this.m_entries[var1.index()];

      for (int var4 = 0; var4 < var3.size(); var4++) {
         CTEntry var5 = (CTEntry)var3.get(var4);
         if (var5.m_frame == var2) {
            return var5;
         }
      }

      return null;
   }

   void addEntry(IsoDirections var1, int var2, BodyTexture var3) {
      CTEntryList var4 = this.m_entries[var1.index()];
      CTEntry var5 = new CTEntry();
      var5.m_frame = var2;
      var5.m_texture = var3;
      var4.add(var5);
   }
}
