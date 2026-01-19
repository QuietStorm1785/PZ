package zombie.gameStates;

import java.util.ArrayList;
import zombie.core.textures.Texture;

public final class ChooseGameInfo$Map {
   private String dir;
   private Texture thumb;
   private String title;
   private ArrayList<String> lotsDir;
   private String desc;
   private boolean bFixed2x;

   public String getDirectory() {
      return this.dir;
   }

   public void setDirectory(String var1) {
      this.dir = var1;
   }

   public Texture getThumbnail() {
      return this.thumb;
   }

   public void setThumbnail(Texture var1) {
      this.thumb = var1;
   }

   public String getTitle() {
      return this.title;
   }

   public void setTitle(String var1) {
      this.title = var1;
   }

   public ArrayList<String> getLotDirectories() {
      return this.lotsDir;
   }

   public String getDescription() {
      return this.desc;
   }

   public void setDescription(String var1) {
      this.desc = var1;
   }

   public boolean isFixed2x() {
      return this.bFixed2x;
   }

   public void setFixed2x(boolean var1) {
      this.bFixed2x = var1;
   }
}
