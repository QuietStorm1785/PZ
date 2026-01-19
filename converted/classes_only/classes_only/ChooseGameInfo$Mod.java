package zombie.gameStates;

import java.io.File;
import java.util.ArrayList;
import zombie.core.Core;
import zombie.core.GameVersion;
import zombie.core.logger.ExceptionLogger;
import zombie.core.textures.Texture;
import zombie.core.znet.SteamWorkshop;
import zombie.debug.DebugLog;
import zombie.gameStates.ChooseGameInfo.PackFile;
import zombie.gameStates.ChooseGameInfo.TileDef;
import zombie.util.StringUtils;

public final class ChooseGameInfo$Mod {
   public String dir;
   public final File baseFile;
   public final File mediaFile;
   public final File actionGroupsFile;
   public final File animSetsFile;
   public final File animsXFile;
   private final ArrayList<String> posters = new ArrayList<>();
   public Texture tex;
   private ArrayList<String> require;
   private String name = "Unnamed Mod";
   private String desc = "";
   private String id;
   private String url;
   private String workshopID;
   private boolean bAvailableDone = false;
   private boolean available = true;
   private GameVersion versionMin;
   private GameVersion versionMax;
   private final ArrayList<PackFile> packs = new ArrayList<>();
   private final ArrayList<TileDef> tileDefs = new ArrayList<>();
   private boolean bRead = false;
   private boolean bValid = false;

   public ChooseGameInfo$Mod(String var1) {
      this.dir = var1;
      File var2 = new File(var1).getAbsoluteFile();

      try {
         var2 = var2.getCanonicalFile();
      } catch (Exception var4) {
         ExceptionLogger.logException(var4);
      }

      this.baseFile = var2;
      this.mediaFile = new File(var2, "media");
      this.actionGroupsFile = new File(this.mediaFile, "actiongroups");
      this.animSetsFile = new File(this.mediaFile, "AnimSets");
      this.animsXFile = new File(this.mediaFile, "anims_X");
      File var3 = var2.getParentFile();
      if (var3 != null) {
         var3 = var3.getParentFile();
         if (var3 != null) {
            this.workshopID = SteamWorkshop.instance.getIDFromItemInstallFolder(var3.getAbsolutePath());
         }
      }
   }

   public Texture getTexture() {
      if (this.tex == null) {
         String var1 = this.posters.isEmpty() ? null : this.posters.get(0);
         if (!StringUtils.isNullOrWhitespace(var1)) {
            this.tex = Texture.getSharedTexture(var1);
         }

         if (this.tex == null || this.tex.isFailure()) {
            if (Core.bDebug && this.tex == null) {
               DebugLog.Mod.println("failed to load poster " + (var1 == null ? this.id : var1));
            }

            this.tex = Texture.getWhite();
         }
      }

      return this.tex;
   }

   public void setTexture(Texture var1) {
      this.tex = var1;
   }

   public int getPosterCount() {
      return this.posters.size();
   }

   public String getPoster(int var1) {
      return var1 >= 0 && var1 < this.posters.size() ? this.posters.get(var1) : null;
   }

   public String getName() {
      return this.name;
   }

   public void setName(String var1) {
      this.name = var1;
   }

   public String getDir() {
      return this.dir;
   }

   public String getDescription() {
      return this.desc;
   }

   public ArrayList<String> getRequire() {
      return this.require;
   }

   public void setRequire(ArrayList<String> var1) {
      this.require = var1;
   }

   public String getId() {
      return this.id;
   }

   public void setId(String var1) {
      this.id = var1;
   }

   public boolean isAvailable() {
      if (this.bAvailableDone) {
         return this.available;
      } else {
         this.bAvailableDone = true;
         if (!this.isAvailableSelf()) {
            this.available = false;
            return false;
         } else {
            ChooseGameInfo.tempStrings.clear();
            ChooseGameInfo.tempStrings.add(this.getId());
            if (!this.isAvailableRequired(ChooseGameInfo.tempStrings)) {
               this.available = false;
               return false;
            } else {
               this.available = true;
               return true;
            }
         }
      }
   }

   private boolean isAvailableSelf() {
      GameVersion var1 = Core.getInstance().getGameVersion();
      return this.versionMin != null && this.versionMin.isGreaterThan(var1) ? false : this.versionMax == null || !this.versionMax.isLessThan(var1);
   }

   private boolean isAvailableRequired(ArrayList<String> var1) {
      if (this.require != null && !this.require.isEmpty()) {
         for (int var2 = 0; var2 < this.require.size(); var2++) {
            String var3 = this.require.get(var2).trim();
            if (!var1.contains(var3)) {
               var1.add(var3);
               ChooseGameInfo$Mod var4 = ChooseGameInfo.getModDetails(var3);
               if (var4 == null) {
                  return false;
               }

               if (!var4.isAvailableSelf()) {
                  return false;
               }

               if (!var4.isAvailableRequired(var1)) {
                  return false;
               }
            }
         }

         return true;
      } else {
         return true;
      }
   }

   @Deprecated
   public void setAvailable(boolean var1) {
   }

   public String getUrl() {
      return this.url == null ? "" : this.url;
   }

   public void setUrl(String var1) {
      if (var1.startsWith("http://theindiestone.com")
         || var1.startsWith("http://www.theindiestone.com")
         || var1.startsWith("http://pz-mods.net")
         || var1.startsWith("http://www.pz-mods.net")) {
         this.url = var1;
      }
   }

   public GameVersion getVersionMin() {
      return this.versionMin;
   }

   public GameVersion getVersionMax() {
      return this.versionMax;
   }

   public void addPack(String var1, int var2) {
      this.packs.add(new PackFile(var1, var2));
   }

   public void addTileDef(String var1, int var2) {
      this.tileDefs.add(new TileDef(var1, var2));
   }

   public ArrayList<PackFile> getPacks() {
      return this.packs;
   }

   public ArrayList<TileDef> getTileDefs() {
      return this.tileDefs;
   }

   public String getWorkshopID() {
      return this.workshopID;
   }
}
