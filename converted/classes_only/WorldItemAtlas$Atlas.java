package zombie.core.skinnedmodel.model;

import java.util.ArrayList;
import org.lwjgl.opengl.GL11;
import zombie.core.opengl.RenderThread;
import zombie.core.skinnedmodel.model.WorldItemAtlas.AtlasEntry;
import zombie.core.textures.Texture;
import zombie.core.textures.TextureFBO;

final class WorldItemAtlas$Atlas {
   public final int ENTRY_WID;
   public final int ENTRY_HGT;
   public Texture tex;
   public final ArrayList<AtlasEntry> EntryList;
   public boolean clear;

   public WorldItemAtlas$Atlas(WorldItemAtlas var1, int var2, int var3, int var4, int var5) {
      this.this$0 = var1;
      this.EntryList = new ArrayList<>();
      this.clear = true;
      this.ENTRY_WID = var4;
      this.ENTRY_HGT = var5;
      this.tex = new Texture(var2, var3, 16);
      if (var1.fbo == null) {
         var1.fbo = new TextureFBO(this.tex, false);
      }
   }

   public boolean isFull() {
      int var1 = this.tex.getWidth() / this.ENTRY_WID;
      int var2 = this.tex.getHeight() / this.ENTRY_HGT;
      return this.EntryList.size() >= var1 * var2;
   }

   public AtlasEntry addItem(String var1) {
      int var2 = this.tex.getWidth() / this.ENTRY_WID;
      int var3 = this.EntryList.size();
      int var4 = var3 % var2;
      int var5 = var3 / var2;
      AtlasEntry var6 = new AtlasEntry();
      var6.atlas = this;
      var6.key = var1;
      var6.x = var4 * this.ENTRY_WID;
      var6.y = var5 * this.ENTRY_HGT;
      var6.w = this.ENTRY_WID;
      var6.h = this.ENTRY_HGT;
      var6.tex = this.tex.split(var1, var6.x, this.tex.getHeight() - (var6.y + this.ENTRY_HGT), var6.w, var6.h);
      var6.tex.setName(var1);
      this.EntryList.add(var6);
      return var6;
   }

   public void addEntry(AtlasEntry var1) {
      int var2 = this.tex.getWidth() / this.ENTRY_WID;
      int var3 = this.EntryList.size();
      int var4 = var3 % var2;
      int var5 = var3 / var2;
      var1.atlas = this;
      var1.x = var4 * this.ENTRY_WID;
      var1.y = var5 * this.ENTRY_HGT;
      var1.w = this.ENTRY_WID;
      var1.h = this.ENTRY_HGT;
      var1.tex = this.tex.split(var1.key, var1.x, this.tex.getHeight() - (var1.y + this.ENTRY_HGT), var1.w, var1.h);
      var1.tex.setName(var1.key);
      this.EntryList.add(var1);
   }

   public void Reset() {
      this.EntryList.forEach(AtlasEntry::Reset);
      this.EntryList.clear();
      if (!this.tex.isDestroyed()) {
         RenderThread.invokeOnRenderContext(() -> GL11.glDeleteTextures(this.tex.getID()));
      }

      this.tex = null;
   }
}
