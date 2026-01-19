package zombie.gameStates;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.logging.Level;
import java.util.logging.Logger;
import zombie.ZomboidFileSystem;
import zombie.core.Core;
import zombie.core.GameVersion;
import zombie.core.IndieFileLoader;
import zombie.core.Language;
import zombie.core.Translator;
import zombie.core.logger.ExceptionLogger;
import zombie.core.textures.Texture;
import zombie.core.textures.TextureID;
import zombie.debug.DebugLog;
import zombie.gameStates.ChooseGameInfo.Map;
import zombie.gameStates.ChooseGameInfo.Mod;
import zombie.util.StringUtils;

public final class ChooseGameInfo {
   private static final HashMap<String, Map> Maps = new HashMap<>();
   private static final HashMap<String, Mod> Mods = new HashMap<>();
   private static final HashSet<String> MissingMods = new HashSet<>();
   private static final ArrayList<String> tempStrings = new ArrayList<>();

   private ChooseGameInfo() {
   }

   public static void Reset() {
      Maps.clear();
      Mods.clear();
      MissingMods.clear();
   }

   private static void readTitleDotTxt(Map var0, String var1, Language var2) throws IOException {
      String var3 = "media/lua/shared/Translate/" + var2.toString() + "/" + var1 + "/title.txt";
      File var4 = new File(ZomboidFileSystem.instance.getString(var3));

      try (
         FileInputStream var5 = new FileInputStream(var4);
         InputStreamReader var6 = new InputStreamReader(var5, Charset.forName(var2.charset()));
         BufferedReader var7 = new BufferedReader(var6);
      ) {
         String var8 = var7.readLine();
         var8 = StringUtils.stripBOM(var8);
         if (!StringUtils.isNullOrWhitespace(var8)) {
            var0.title = var8.trim();
         }
      } catch (FileNotFoundException var16) {
      }
   }

   private static void readDescriptionDotTxt(Map var0, String var1, Language var2) throws IOException {
      String var3 = "media/lua/shared/Translate/" + var2.toString() + "/" + var1 + "/description.txt";
      File var4 = new File(ZomboidFileSystem.instance.getString(var3));

      try (
         FileInputStream var5 = new FileInputStream(var4);
         InputStreamReader var6 = new InputStreamReader(var5, Charset.forName(var2.charset()));
         BufferedReader var7 = new BufferedReader(var6);
      ) {
         var0.desc = "";
         boolean var9 = true;

         String var8;
         while ((var8 = var7.readLine()) != null) {
            if (var9) {
               var8 = StringUtils.stripBOM(var8);
               var9 = false;
            }

            var0.desc = var0.desc + var8;
         }
      } catch (FileNotFoundException var16) {
      }
   }

   public static Map getMapDetails(String var0) {
      if (Maps.containsKey(var0)) {
         return Maps.get(var0);
      } else {
         File var1 = new File(ZomboidFileSystem.instance.getString("media/maps/" + var0 + "/map.info"));
         if (!var1.exists()) {
            return null;
         } else {
            Map var2 = new Map();
            var2.dir = new File(var1.getParent()).getAbsolutePath();
            var2.title = var0;
            var2.lotsDir = new ArrayList();

            try {
               FileReader var3 = new FileReader(var1.getAbsolutePath());
               BufferedReader var4 = new BufferedReader(var3);
               String var5 = null;

               try {
                  while ((var5 = var4.readLine()) != null) {
                     var5 = var5.trim();
                     if (var5.startsWith("title=")) {
                        var2.title = var5.replace("title=", "");
                     } else if (var5.startsWith("lots=")) {
                        var2.lotsDir.add(var5.replace("lots=", "").trim());
                     } else if (var5.startsWith("description=")) {
                        if (var2.desc == null) {
                           var2.desc = "";
                        }

                        var2.desc = var2.desc + var5.replace("description=", "");
                     } else if (var5.startsWith("fixed2x=")) {
                        var2.bFixed2x = Boolean.parseBoolean(var5.replace("fixed2x=", "").trim());
                     }
                  }
               } catch (IOException var9) {
                  Logger.getLogger(ChooseGameInfo.class.getName()).log(Level.SEVERE, null, var9);
               }

               var4.close();
               var2.thumb = Texture.getSharedTexture(var2.dir + "/thumb.png");
               ArrayList var6 = new ArrayList();
               Translator.addLanguageToList(Translator.getLanguage(), var6);
               Translator.addLanguageToList(Translator.getDefaultLanguage(), var6);

               for (int var7 = var6.size() - 1; var7 >= 0; var7--) {
                  Language var8 = (Language)var6.get(var7);
                  readTitleDotTxt(var2, var0, var8);
                  readDescriptionDotTxt(var2, var0, var8);
               }
            } catch (Exception var10) {
               ExceptionLogger.logException(var10);
               return null;
            }

            Maps.put(var0, var2);
            return var2;
         }
      }
   }

   public static Mod getModDetails(String var0) {
      if (MissingMods.contains(var0)) {
         return null;
      } else if (Mods.containsKey(var0)) {
         return Mods.get(var0);
      } else {
         String var1 = ZomboidFileSystem.instance.getModDir(var0);
         if (var1 == null) {
            ArrayList var2 = tempStrings;
            ZomboidFileSystem.instance.getAllModFolders(var2);
            ArrayList var3 = new ArrayList();

            for (int var4 = 0; var4 < var2.size(); var4++) {
               File var5 = new File((String)var2.get(var4), "mod.info");
               var3.clear();
               Mod var6 = ZomboidFileSystem.instance.searchForModInfo(var5, var0, var3);

               for (int var7 = 0; var7 < var3.size(); var7++) {
                  Mod var8 = (Mod)var3.get(var7);
                  Mods.putIfAbsent(var8.getId(), var8);
               }

               if (var6 != null) {
                  return var6;
               }
            }
         }

         Mod var9 = readModInfo(var1);
         if (var9 == null) {
            MissingMods.add(var0);
         }

         return var9;
      }
   }

   public static Mod getAvailableModDetails(String var0) {
      Mod var1 = getModDetails(var0);
      return var1 != null && var1.isAvailable() ? var1 : null;
   }

   public static Mod readModInfo(String var0) {
      Mod var1 = readModInfoAux(var0);
      if (var1 != null) {
         Mod var2 = Mods.get(var1.getId());
         if (var2 == null) {
            Mods.put(var1.getId(), var1);
         } else if (var2 != var1) {
            ZomboidFileSystem.instance.getAllModFolders(tempStrings);
            int var3 = tempStrings.indexOf(var1.getDir());
            int var4 = tempStrings.indexOf(var2.getDir());
            if (var3 < var4) {
               Mods.put(var1.getId(), var1);
            }
         }
      }

      return var1;
   }

   private static Mod readModInfoAux(String var0) {
      if (var0 != null) {
         Mod var1 = ZomboidFileSystem.instance.getModInfoForDir(var0);
         if (var1.bRead) {
            return var1.bValid ? var1 : null;
         }

         var1.bRead = true;
         String var2 = var0 + File.separator + "mod.info";
         File var3 = new File(var2);
         if (!var3.exists()) {
            DebugLog.Mod.warn("can't find \"" + var2 + "\"");
            return null;
         }

         var1.setId(var3.getParentFile().getName());

         try (
            InputStreamReader var4 = IndieFileLoader.getStreamReader(var2);
            BufferedReader var5 = new BufferedReader(var4);
         ) {
            while (true) {
               String var6;
               if ((var6 = var5.readLine()) == null) {
                  if (var1.getUrl() == null) {
                     var1.setUrl("");
                  }
                  break;
               }

               if (var6.contains("name=")) {
                  var1.name = var6.replace("name=", "");
               } else if (var6.contains("poster=")) {
                  String var25 = var6.replace("poster=", "");
                  if (!StringUtils.isNullOrWhitespace(var25)) {
                     var1.posters.add(var0 + File.separator + var25);
                  }
               } else if (var6.contains("description=")) {
                  var1.desc = var1.desc + var6.replace("description=", "");
               } else if (var6.contains("require=")) {
                  var1.setRequire(new ArrayList<>(Arrays.asList(var6.replace("require=", "").split(","))));
               } else if (var6.contains("id=")) {
                  var1.setId(var6.replace("id=", ""));
               } else if (var6.contains("url=")) {
                  var1.setUrl(var6.replace("url=", ""));
               } else if (var6.contains("pack=")) {
                  String var24 = var6.replace("pack=", "").trim();
                  if (var24.isEmpty()) {
                     DebugLog.Mod.error("pack= line requires a file name");
                     return null;
                  }

                  int var28 = TextureID.bUseCompressionOption ? 4 : 0;
                  var28 |= 64;
                  int var33 = var24.indexOf("type=");
                  if (var33 != -1) {
                     String var34 = var24.substring(var33 + "type=".length());
                     byte var40 = -1;
                     switch (var34.hashCode()) {
                        case 3732:
                           if (var34.equals("ui")) {
                              var40 = 0;
                           }
                        default:
                           switch (var40) {
                              case 0:
                                 var28 = 2;
                                 break;
                              default:
                                 DebugLog.Mod.error("unknown pack type=" + var34);
                           }

                           int var38 = var24.indexOf(32);
                           var24 = var24.substring(0, var38).trim();
                     }
                  }

                  String var35 = var24;
                  String var39 = "";
                  if (var24.endsWith(".floor")) {
                     var35 = var24.substring(0, var24.lastIndexOf(46));
                     var39 = ".floor";
                     var28 &= -5;
                  }

                  int var41 = Core.getInstance().getOptionTexture2x() ? 2 : 1;
                  if (Core.SafeModeForced) {
                     var41 = 1;
                  }

                  if (var41 == 2) {
                     File var13 = new File(var0 + File.separator + "media" + File.separator + "texturepacks" + File.separator + var35 + "2x" + var39 + ".pack");
                     if (var13.isFile()) {
                        DebugLog.Mod.printf("2x version of %s.pack found.\n", new Object[]{var24});
                        var24 = var35 + "2x" + var39;
                     } else {
                        var13 = new File(var0 + File.separator + "media" + File.separator + "texturepacks" + File.separator + var24 + "2x.pack");
                        if (var13.isFile()) {
                           DebugLog.Mod.printf("2x version of %s.pack found.\n", new Object[]{var24});
                           var24 = var24 + "2x";
                        } else {
                           DebugLog.Mod.printf("2x version of %s.pack not found.\n", new Object[]{var24});
                        }
                     }
                  }

                  var1.addPack(var24, var28);
               } else if (var6.contains("tiledef=")) {
                  String[] var23 = var6.replace("tiledef=", "").trim().split("\\s+");
                  if (var23.length != 2) {
                     DebugLog.Mod.error("tiledef= line requires file name and file number");
                     return null;
                  }

                  String var8 = var23[0];

                  int var32;
                  try {
                     var32 = Integer.parseInt(var23[1]);
                  } catch (NumberFormatException var18) {
                     DebugLog.Mod.error("tiledef= line requires file name and file number");
                     return null;
                  }

                  byte var10 = 100;
                  short var36 = 8190;
                  var36 = 16382;
                  if (var32 < var10 || var32 > var36) {
                     DebugLog.Mod
                        .error("tiledef=%s %d file number must be from %d to %d", new Object[]{var8, var32, Integer.valueOf(var10), Integer.valueOf(var36)});
                     return null;
                  }

                  var1.addTileDef(var8, var32);
               } else if (var6.startsWith("versionMax=")) {
                  String var22 = var6.replace("versionMax=", "").trim();
                  if (!var22.isEmpty()) {
                     try {
                        var1.versionMax = GameVersion.parse(var22);
                     } catch (Exception var16) {
                        DebugLog.Mod.error("invalid versionMax: " + var16.getMessage());
                        return null;
                     }
                  }
               } else if (var6.startsWith("versionMin=")) {
                  String var7 = var6.replace("versionMin=", "").trim();
                  if (!var7.isEmpty()) {
                     try {
                        var1.versionMin = GameVersion.parse(var7);
                     } catch (Exception var17) {
                        DebugLog.Mod.error("invalid versionMin: " + var17.getMessage());
                        return null;
                     }
                  }
               }
            }

            var1.bValid = true;
            return var1;
         } catch (Exception var21) {
            ExceptionLogger.logException(var21);
         }
      }

      return null;
   }
}
