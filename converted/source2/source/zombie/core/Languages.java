package zombie.core;

import java.io.File;
import java.nio.file.DirectoryStream;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.DirectoryStream.Filter;
import java.util.ArrayList;
import zombie.ZomboidFileSystem;
import zombie.core.logger.ExceptionLogger;
import zombie.gameStates.ChooseGameInfo;
import zombie.gameStates.ChooseGameInfo.Mod;
import zombie.util.Lambda;
import zombie.util.list.PZArrayUtil;

public final class Languages {
   public static final Languages instance = new Languages();
   private final ArrayList<Language> m_languages = new ArrayList<>();
   private Language m_defaultLanguage = new Language(0, "EN", "English", "UTF-8", null, false);

   public Languages() {
      this.m_languages.add(this.m_defaultLanguage);
   }

   public void init() {
      this.m_languages.clear();
      this.m_defaultLanguage = new Language(0, "EN", "English", "UTF-8", null, false);
      this.m_languages.add(this.m_defaultLanguage);
      this.loadTranslateDirectory(ZomboidFileSystem.instance.getMediaPath("lua/shared/Translate"));

      for (String var2 : ZomboidFileSystem.instance.getModIDs()) {
         Mod var3 = ChooseGameInfo.getAvailableModDetails(var2);
         if (var3 != null) {
            File var4 = new File(var3.getDir(), "media/lua/shared/Translate");
            if (var4.isDirectory()) {
               this.loadTranslateDirectory(var4.getAbsolutePath());
            }
         }
      }
   }

   public Language getDefaultLanguage() {
      return this.m_defaultLanguage;
   }

   public int getNumLanguages() {
      return this.m_languages.size();
   }

   public Language getByIndex(int var1) {
      return var1 >= 0 && var1 < this.m_languages.size() ? this.m_languages.get(var1) : null;
   }

   public Language getByName(String var1) {
      return (Language)PZArrayUtil.find(this.m_languages, Lambda.predicate(var1, (var0, var1x) -> var0.name().equalsIgnoreCase(var1x)));
   }

   public int getIndexByName(String var1) {
      return PZArrayUtil.indexOf(this.m_languages, Lambda.predicate(var1, (var0, var1x) -> var0.name().equalsIgnoreCase(var1x)));
   }

   private void loadTranslateDirectory(String var1) {
      Filter var2 = var0 -> Files.isDirectory(var0) && Files.exists(var0.resolve("language.txt"));
      Path var3 = FileSystems.getDefault().getPath(var1);
      if (Files.exists(var3)) {
         try (DirectoryStream var4 = Files.newDirectoryStream(var3, var2)) {
            for (Path var6 : var4) {
               LanguageFileData var7 = this.loadLanguageDirectory(var6.toAbsolutePath());
               if (var7 != null) {
                  int var8 = this.getIndexByName(var7.name);
                  if (var8 == -1) {
                     Language var9 = new Language(this.m_languages.size(), var7.name, var7.text, var7.charset, var7.base, var7.azerty);
                     this.m_languages.add(var9);
                  } else {
                     Language var13 = new Language(var8, var7.name, var7.text, var7.charset, var7.base, var7.azerty);
                     this.m_languages.set(var8, var13);
                     if (var7.name.equals(this.m_defaultLanguage.name())) {
                        this.m_defaultLanguage = var13;
                     }
                  }
               }
            }
         } catch (Exception var12) {
            ExceptionLogger.logException(var12);
         }
      }
   }

   private LanguageFileData loadLanguageDirectory(Path var1) {
      String var2 = var1.getFileName().toString();
      LanguageFileData var3 = new LanguageFileData();
      var3.name = var2;
      LanguageFile var4 = new LanguageFile();
      String var5 = var1.resolve("language.txt").toString();
      return !var4.read(var5, var3) ? null : var3;
   }
}
