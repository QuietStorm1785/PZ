package zombie.core;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.regex.Matcher;
import se.krka.kahlua.vm.KahluaTable;
import zombie.ZomboidFileSystem;
import zombie.Lua.LuaManager;
import zombie.characters.skills.PerkFactory;
import zombie.core.Translator.News;
import zombie.core.logger.ExceptionLogger;
import zombie.debug.DebugLog;
import zombie.debug.DebugOptions;
import zombie.scripting.ScriptManager;
import zombie.scripting.objects.Item;
import zombie.util.StringUtils;

public final class Translator {
   private static ArrayList<Language> availableLanguage = null;
   public static boolean debug = false;
   private static FileWriter debugFile = null;
   private static boolean debugErrors = false;
   private static final HashSet<String> debugItemEvolvedRecipeName = new HashSet<>();
   private static final HashSet<String> debugItem = new HashSet<>();
   private static final HashSet<String> debugMultiStageBuild = new HashSet<>();
   private static final HashSet<String> debugRecipe = new HashSet<>();
   private static final HashMap<String, String> moodles = new HashMap<>();
   private static final HashMap<String, String> ui = new HashMap<>();
   private static final HashMap<String, String> survivalGuide = new HashMap<>();
   private static final HashMap<String, String> contextMenu = new HashMap<>();
   private static final HashMap<String, String> farming = new HashMap<>();
   private static final HashMap<String, String> recipe = new HashMap<>();
   private static final HashMap<String, String> igui = new HashMap<>();
   private static final HashMap<String, String> sandbox = new HashMap<>();
   private static final HashMap<String, String> tooltip = new HashMap<>();
   private static final HashMap<String, String> challenge = new HashMap<>();
   private static final HashSet<String> missing = new HashSet<>();
   private static ArrayList<String> azertyLanguages = null;
   private static final HashMap<String, String> news = new HashMap<>();
   private static final HashMap<String, String> stash = new HashMap<>();
   private static final HashMap<String, String> multiStageBuild = new HashMap<>();
   private static final HashMap<String, String> moveables = new HashMap<>();
   private static final HashMap<String, String> makeup = new HashMap<>();
   private static final HashMap<String, String> gameSound = new HashMap<>();
   private static final HashMap<String, String> dynamicRadio = new HashMap<>();
   private static final HashMap<String, String> items = new HashMap<>();
   private static final HashMap<String, String> itemName = new HashMap<>();
   private static final HashMap<String, String> itemEvolvedRecipeName = new HashMap<>();
   private static final HashMap<String, String> recordedMedia = new HashMap<>();
   private static final HashMap<String, String> recordedMedia_EN = new HashMap<>();
   public static Language language = null;
   private static final String newsHeader = "<IMAGE:media/ui/dot.png> <SIZE:small> ";

   public static void loadFiles() {
      language = null;
      availableLanguage = null;
      File var0 = new File(ZomboidFileSystem.instance.getCacheDir() + File.separator + "translationProblems.txt");
      if (debug) {
         try {
            if (debugFile != null) {
               debugFile.close();
            }

            debugFile = new FileWriter(var0);
         } catch (IOException var2) {
            var2.printStackTrace();
         }
      }

      moodles.clear();
      ui.clear();
      survivalGuide.clear();
      items.clear();
      itemName.clear();
      contextMenu.clear();
      farming.clear();
      recipe.clear();
      igui.clear();
      sandbox.clear();
      tooltip.clear();
      challenge.clear();
      news.clear();
      missing.clear();
      stash.clear();
      multiStageBuild.clear();
      moveables.clear();
      makeup.clear();
      gameSound.clear();
      dynamicRadio.clear();
      itemEvolvedRecipeName.clear();
      recordedMedia.clear();
      DebugLog.log("translator: language is " + getLanguage());
      debugErrors = false;
      fillMapFromFile("Tooltip", tooltip);
      fillMapFromFile("IG_UI", igui);
      fillMapFromFile("Recipes", recipe);
      fillMapFromFile("Farming", farming);
      fillMapFromFile("ContextMenu", contextMenu);
      fillMapFromFile("SurvivalGuide", survivalGuide);
      fillMapFromFile("UI", ui);
      fillMapFromFile("Items", items);
      fillMapFromFile("ItemName", itemName);
      fillMapFromFile("Moodles", moodles);
      fillMapFromFile("Sandbox", sandbox);
      fillMapFromFile("Challenge", challenge);
      fillMapFromFile("Stash", stash);
      fillMapFromFile("MultiStageBuild", multiStageBuild);
      fillMapFromFile("Moveables", moveables);
      fillMapFromFile("MakeUp", makeup);
      fillMapFromFile("GameSound", gameSound);
      fillMapFromFile("DynamicRadio", dynamicRadio);
      fillMapFromFile("EvolvedRecipeName", itemEvolvedRecipeName);
      fillMapFromFile("Recorded_Media", recordedMedia);
      fillNewsFromFile(news);
      if (debug) {
         if (debugErrors) {
            DebugLog.log("translator: errors detected, please see " + var0.getAbsolutePath());
         }

         debugItemEvolvedRecipeName.clear();
         debugItem.clear();
         debugMultiStageBuild.clear();
         debugRecipe.clear();
      }

      PerkFactory.initTranslations();
   }

   private static void fillNewsFromFile(HashMap<String, String> var0) {
      HashMap var1 = new HashMap();
      ArrayList var2 = ZomboidFileSystem.instance.getModIDs();

      for (int var3 = 0; var3 < var2.size(); var3++) {
         String var4 = ZomboidFileSystem.instance.getModDir((String)var2.get(var3));
         if (var4 != null) {
            tryFillNewsFromFile(var4, var0, var1, getLanguage());
            if (getLanguage() != getDefaultLanguage()) {
               tryFillNewsFromFile(var4, var0, var1, getDefaultLanguage());
            }
         }
      }

      tryFillNewsFromFile(".", var0, var1, getLanguage());
      if (getLanguage() != getDefaultLanguage()) {
         tryFillNewsFromFile(".", var0, var1, getDefaultLanguage());
      }

      for (News var6 : var1.values()) {
         var0.put("News_" + var6.version + "_Disclaimer", var6.toRichText());
      }

      var1.clear();
   }

   private static void tryFillNewsFromFile(String var0, HashMap<String, String> var1, HashMap<String, News> var2, Language var3) {
      File var4 = new File(
         var0
            + File.separator
            + "media"
            + File.separator
            + "lua"
            + File.separator
            + "shared"
            + File.separator
            + "Translate"
            + File.separator
            + var3
            + File.separator
            + "News_"
            + var3
            + ".txt"
      );
      if (var4.exists()) {
         doNews(var4, var2, var3);
      }
   }

   private static void doNews(File var0, HashMap<String, News> var1, Language var2) {
      try (
         FileInputStream var3 = new FileInputStream(var0);
         InputStreamReader var4 = new InputStreamReader(var3, Charset.forName(var2.charset()));
         BufferedReader var5 = new BufferedReader(var4);
      ) {
         News var6 = null;
         ArrayList var7 = null;

         String var8;
         while ((var8 = var5.readLine()) != null) {
            if (!var8.trim().isEmpty()) {
               if (var8.startsWith("[VERSION]")) {
                  String var9 = var8.replaceFirst("\\[VERSION\\]", "").trim();
                  if (var1.containsKey(var9)) {
                     var6 = null;
                     var7 = null;
                  } else {
                     var1.put(var9, var6 = new News(var9));
                     var7 = null;
                  }
               }

               if (var6 != null) {
                  if (var8.startsWith("[SECTION]")) {
                     String var17 = var8.replaceFirst("\\[SECTION\\]", "").trim();
                     var7 = var6.getOrCreateSectionList(var17);
                  } else if (var8.startsWith("[NEWS]")) {
                     var7 = var6.getOrCreateSectionList("[New]");
                  } else if (var8.startsWith("[BALANCE]")) {
                     var7 = var6.getOrCreateSectionList("[Balance]");
                  } else if (var8.startsWith("[BUG FIX]")) {
                     var7 = var6.getOrCreateSectionList("[Bug Fix]");
                  } else if (var7 != null) {
                     addNewsLine(var8, var7);
                  }
               }
            }
         }
      } catch (Exception var16) {
         ExceptionLogger.logException(var16);
      }
   }

   private static void addNewsLine(String var0, ArrayList<String> var1) {
      if (var0.startsWith("[BOLD]")) {
         var0 = var0.replaceFirst("\\[BOLD\\]", "<IMAGE:media/ui/dot.png> <SIZE:medium>");
         var1.add(var0 + " <LINE> ");
      } else if (var0.startsWith("[DOT2]")) {
         var0 = var0.replaceFirst("\\[DOT2\\]", "<IMAGE:media/ui/dot2.png> <SIZE:small>");
         var1.add(var0 + " <LINE> ");
      } else if (var0.startsWith("[NODOT]")) {
         var0 = var0.replaceFirst("\\[NODOT\\]", " <SIZE:small> ");
         var0 = var0 + " <LINE> ";
         var1.add(var0);
      } else {
         byte var2 = 7;
         var1.add("<IMAGE:media/ui/dot.png> <SIZE:small> " + " <INDENT:%d> ".formatted(21 - var2) + var0 + " <INDENT:0> <LINE> ");
      }
   }

   public static ArrayList<String> getNewsVersions() {
      ArrayList var0 = new ArrayList();
      var0.addAll(news.keySet());

      for (int var1 = 0; var1 < var0.size(); var1++) {
         String var2 = (String)var0.get(var1);
         var2 = var2.replace("News_", "");
         var2 = var2.replace("_Disclaimer", "");
         var0.set(var1, var2);
      }

      Collections.sort(var0);
      return var0;
   }

   private static void tryFillMapFromFile(String var0, String var1, HashMap<String, String> var2, Language var3) {
      File var4 = new File(
         var0
            + File.separator
            + "media"
            + File.separator
            + "lua"
            + File.separator
            + "shared"
            + File.separator
            + "Translate"
            + File.separator
            + var3
            + File.separator
            + var1
            + "_"
            + var3
            + ".txt"
      );
      if (var4.exists()) {
         parseFile(var4, var2, var3);
      }
   }

   private static void tryFillMapFromMods(String var0, HashMap<String, String> var1, Language var2) {
      ArrayList var3 = ZomboidFileSystem.instance.getModIDs();

      for (int var4 = var3.size() - 1; var4 >= 0; var4--) {
         String var5 = ZomboidFileSystem.instance.getModDir((String)var3.get(var4));
         if (var5 != null) {
            tryFillMapFromFile(var5, var0, var1, var2);
         }
      }
   }

   public static void addLanguageToList(Language var0, ArrayList<Language> var1) {
      if (var0 != null) {
         if (!var1.contains(var0)) {
            var1.add(var0);
            if (var0.base() != null) {
               var0 = Languages.instance.getByName(var0.base());
               addLanguageToList(var0, var1);
            }
         }
      }
   }

   private static void fillMapFromFile(String var0, HashMap<String, String> var1) {
      ArrayList var2 = new ArrayList();
      addLanguageToList(getLanguage(), var2);
      addLanguageToList(getDefaultLanguage(), var2);

      for (int var3 = 0; var3 < var2.size(); var3++) {
         Language var4 = (Language)var2.get(var3);
         tryFillMapFromMods(var0, var1, var4);
         tryFillMapFromFile(ZomboidFileSystem.instance.base.getPath(), var0, var1, var4);
      }

      var2.clear();
   }

   private static void parseFile(File var0, HashMap<String, String> var1, Language var2) {
      String var3 = null;

      try (
         FileInputStream var4 = new FileInputStream(var0);
         InputStreamReader var5 = new InputStreamReader(var4, Charset.forName(var2.charset()));
         BufferedReader var6 = new BufferedReader(var5);
      ) {
         var6.readLine();
         boolean var7 = false;
         String var8 = "";
         String var9 = "";
         int var10 = 1;
         String var11 = var0.getName().replace("_" + getDefaultLanguage(), "_" + getLanguage());

         while ((var3 = var6.readLine()) != null) {
            var10++;

            try {
               if (var3.contains("=") && var3.contains("\"")) {
                  if (var3.trim().startsWith("Recipe_")) {
                     var8 = var3.split("=")[0].replaceAll("Recipe_", "").replaceAll("_", " ").trim();
                     var9 = var3.split("=")[1];
                     var9 = var9.substring(var9.indexOf("\"") + 1, var9.lastIndexOf("\""));
                  } else if (var3.trim().startsWith("DisplayName")) {
                     String[] var12 = var3.split("=");
                     if (var3.trim().startsWith("DisplayName_")) {
                        var8 = var12[0].replaceAll("DisplayName_", "").trim();
                     } else {
                        var8 = var12[0].replaceAll("DisplayName", "").trim();
                     }

                     if ("Anti_depressants".equals(var8)) {
                        var8 = "Antidepressants";
                     }

                     var9 = var12[1];
                     var9 = var9.substring(var9.indexOf("\"") + 1, var9.lastIndexOf("\""));
                  } else if (var3.trim().startsWith("EvolvedRecipeName_")) {
                     String[] var24 = var3.split("=");
                     var8 = var24[0].replaceAll("EvolvedRecipeName_", "").trim();
                     var9 = var24[1];
                     int var13 = var9.indexOf("\"");
                     int var14 = var9.lastIndexOf("\"");
                     var9 = var9.substring(var13 + 1, var14);
                  } else if (var3.trim().startsWith("ItemName_")) {
                     String[] var25 = var3.split("=");
                     var8 = var25[0].replaceAll("ItemName_", "").trim();
                     var9 = var25[1];
                     int var27 = var9.indexOf("\"");
                     int var28 = var9.lastIndexOf("\"");
                     var9 = var9.substring(var27 + 1, var28);
                  } else {
                     var8 = var3.split("=")[0].trim();
                     var9 = var3.substring(var3.indexOf("=") + 1);
                     var9 = var9.substring(var9.indexOf("\"") + 1, var9.lastIndexOf("\""));
                     if (var3.contains("..")) {
                        var7 = true;
                     }
                  }
               } else if (var3.contains("--") || var3.trim().isEmpty() || !var3.trim().endsWith("..") && !var7) {
                  var7 = false;
               } else {
                  var7 = true;
                  var9 = var9 + var3.substring(var3.indexOf("\"") + 1, var3.lastIndexOf("\""));
               }

               if (!var7 || !var3.trim().endsWith("..")) {
                  if (!var8.isEmpty()) {
                     if (!var1.containsKey(var8)) {
                        var1.put(var8, var9);
                        if (var1 == recordedMedia && var2 == getDefaultLanguage()) {
                           recordedMedia_EN.put(var8, var9);
                        }

                        if (debug && var2 == getDefaultLanguage() && getLanguage() != getDefaultLanguage()) {
                           if (var11 != null) {
                              debugwrite(var11 + "\r\n");
                              var11 = null;
                           }

                           debugwrite("\t" + var8 + " = \"" + var9 + "\",\r\n");
                           debugErrors = true;
                        }
                     } else if (debug && var2 == getDefaultLanguage() && getLanguage() != getDefaultLanguage()) {
                        String var26 = (String)var1.get(var8);
                        if (countSubstitutions(var26) != countSubstitutions(var9)) {
                           debugwrite(
                              "wrong number of % substitutions in "
                                 + var8
                                 + "    "
                                 + getDefaultLanguage()
                                 + "=\""
                                 + var9
                                 + "\"    "
                                 + getLanguage()
                                 + "=\""
                                 + var26
                                 + "\"\r\n"
                           );
                           debugErrors = true;
                        }
                     }
                  }

                  var7 = false;
                  var9 = "";
                  var8 = "";
               }
            } catch (Exception var18) {
               if (debug) {
                  if (var11 != null) {
                     debugwrite(var11 + "\r\n");
                     var11 = null;
                  }

                  debugwrite("line " + var10 + ": " + var8 + " = " + var9 + "\r\n");
                  if (debugFile != null) {
                     var18.printStackTrace(new PrintWriter(debugFile));
                  }

                  debugwrite("\r\n");
                  debugErrors = true;
               }
            }
         }
      } catch (Exception var22) {
         var22.printStackTrace();
      }
   }

   public static String getText(String var0) {
      return getTextInternal(var0, false);
   }

   public static String getTextOrNull(String var0) {
      return getTextInternal(var0, true);
   }

   private static String getTextInternal(String var0, boolean var1) {
      if (ui == null) {
         loadFiles();
      }

      String var2 = null;
      if (var0.startsWith("UI_")) {
         var2 = ui.get(var0);
      } else if (var0.startsWith("Moodles_")) {
         var2 = moodles.get(var0);
      } else if (var0.startsWith("SurvivalGuide_")) {
         var2 = survivalGuide.get(var0);
      } else if (var0.startsWith("Farming_")) {
         var2 = farming.get(var0);
      } else if (var0.startsWith("IGUI_")) {
         var2 = igui.get(var0);
      } else if (var0.startsWith("ContextMenu_")) {
         var2 = contextMenu.get(var0);
      } else if (var0.startsWith("GameSound_")) {
         var2 = gameSound.get(var0);
      } else if (var0.startsWith("Sandbox_")) {
         var2 = sandbox.get(var0);
      } else if (var0.startsWith("Tooltip_")) {
         var2 = tooltip.get(var0);
      } else if (var0.startsWith("Challenge_")) {
         var2 = challenge.get(var0);
      } else if (var0.startsWith("MakeUp")) {
         var2 = makeup.get(var0);
      } else if (var0.startsWith("News_")) {
         var2 = news.get(var0);
      } else if (var0.startsWith("Stash_")) {
         var2 = stash.get(var0);
      } else if (var0.startsWith("RM_")) {
         var2 = recordedMedia.get(var0);
      }

      String var3 = Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "*" : null;
      if (var2 == null) {
         if (var1) {
            return null;
         }

         if (!missing.contains(var0)) {
            if (Core.bDebug) {
               DebugLog.log("ERROR: Missing translation \"" + var0 + "\"");
            }

            if (debug) {
               debugwrite("ERROR: Missing translation \"" + var0 + "\"\r\n");
            }

            missing.add(var0);
         }

         var2 = var0;
         var3 = Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "!" : null;
      }

      if (var2.contains("<br>")) {
         return var2.replaceAll("<br>", "\n");
      } else {
         return var3 == null ? var2 : var3 + var2;
      }
   }

   private static int countSubstitutions(String var0) {
      int var1 = 0;
      if (var0.contains("%1")) {
         var1++;
      }

      if (var0.contains("%2")) {
         var1++;
      }

      if (var0.contains("%3")) {
         var1++;
      }

      if (var0.contains("%4")) {
         var1++;
      }

      return var1;
   }

   private static String subst(String var0, String var1, Object var2) {
      if (var2 != null) {
         if (var2 instanceof Double) {
            double var3 = (Double)var2;
            var0 = var0.replaceAll(var1, var3 == (long)var3 ? Long.toString((long)var3) : var2.toString());
         } else {
            var0 = var0.replaceAll(var1, Matcher.quoteReplacement(var2.toString()));
         }
      }

      return var0;
   }

   public static String getText(String var0, Object var1) {
      String var2 = getText(var0);
      return subst(var2, "%1", var1);
   }

   public static String getText(String var0, Object var1, Object var2) {
      String var3 = getText(var0);
      var3 = subst(var3, "%1", var1);
      return subst(var3, "%2", var2);
   }

   public static String getText(String var0, Object var1, Object var2, Object var3) {
      String var4 = getText(var0);
      var4 = subst(var4, "%1", var1);
      var4 = subst(var4, "%2", var2);
      return subst(var4, "%3", var3);
   }

   public static String getText(String var0, Object var1, Object var2, Object var3, Object var4) {
      String var5 = getText(var0);
      var5 = subst(var5, "%1", var1);
      var5 = subst(var5, "%2", var2);
      var5 = subst(var5, "%3", var3);
      return subst(var5, "%4", var4);
   }

   public static String getTextOrNull(String var0, Object var1) {
      String var2 = getTextOrNull(var0);
      return var2 == null ? null : subst(var2, "%1", var1);
   }

   public static String getTextOrNull(String var0, Object var1, Object var2) {
      String var3 = getTextOrNull(var0);
      if (var3 == null) {
         return null;
      } else {
         var3 = subst(var3, "%1", var1);
         return subst(var3, "%2", var2);
      }
   }

   public static String getTextOrNull(String var0, Object var1, Object var2, Object var3) {
      String var4 = getTextOrNull(var0);
      if (var4 == null) {
         return null;
      } else {
         var4 = subst(var4, "%1", var1);
         var4 = subst(var4, "%2", var2);
         return subst(var4, "%3", var3);
      }
   }

   public static String getTextOrNull(String var0, Object var1, Object var2, Object var3, Object var4) {
      String var5 = getTextOrNull(var0);
      if (var5 == null) {
         return null;
      } else {
         var5 = subst(var5, "%1", var1);
         var5 = subst(var5, "%2", var2);
         var5 = subst(var5, "%3", var3);
         return subst(var5, "%4", var4);
      }
   }

   private static String getDefaultText(String var0) {
      return changeSomeStuff((String)((KahluaTable)LuaManager.env.rawget(var0.split("_")[0] + "_" + getDefaultLanguage().name())).rawget(var0));
   }

   private static String changeSomeStuff(String var0) {
      return var0;
   }

   public static void setLanguage(Language var0) {
      if (var0 == null) {
         var0 = getDefaultLanguage();
      }

      language = var0;
   }

   public static void setLanguage(int var0) {
      Language var1 = Languages.instance.getByIndex(var0);
      setLanguage(var1);
   }

   public static Language getLanguage() {
      if (language == null) {
         String var0 = Core.getInstance().getOptionLanguageName();
         if (!StringUtils.isNullOrWhitespace(var0)) {
            language = Languages.instance.getByName(var0);
         }
      }

      if (language == null) {
         language = Languages.instance.getByName(System.getProperty("user.language").toUpperCase());
      }

      if (language == null) {
         language = getDefaultLanguage();
      }

      return language;
   }

   public static String getCharset() {
      return getLanguage().charset();
   }

   public static ArrayList<Language> getAvailableLanguage() {
      if (availableLanguage == null) {
         availableLanguage = new ArrayList<>();

         for (int var0 = 0; var0 < Languages.instance.getNumLanguages(); var0++) {
            availableLanguage.add(Languages.instance.getByIndex(var0));
         }
      }

      return availableLanguage;
   }

   public static String getDisplayItemName(String var0) {
      Object var1 = null;
      var1 = items.get(var0.replaceAll(" ", "_").replaceAll("-", "_"));
      return (String)(var1 == null ? var0 : var1);
   }

   public static String getItemNameFromFullType(String var0) {
      if (!var0.contains(".")) {
         throw new IllegalArgumentException("fullType must contain \".\" i.e. module.type");
      } else {
         String var1 = itemName.get(var0);
         if (var1 == null) {
            if (debug && getLanguage() != getDefaultLanguage() && !debugItem.contains(var0)) {
               debugItem.add(var0);
            }

            Item var2 = ScriptManager.instance.getItem(var0);
            if (var2 == null) {
               var1 = var0;
            } else {
               var1 = var2.getDisplayName();
            }

            itemName.put(var0, var1);
         }

         return var1;
      }
   }

   public static void setDefaultItemEvolvedRecipeName(String var0, String var1) {
      if (getLanguage() == getDefaultLanguage()) {
         if (!var0.contains(".")) {
            throw new IllegalArgumentException("fullType must contain \".\" i.e. module.type");
         } else if (!itemEvolvedRecipeName.containsKey(var0)) {
            itemEvolvedRecipeName.put(var0, var1);
         }
      }
   }

   public static String getItemEvolvedRecipeName(String var0) {
      if (!var0.contains(".")) {
         throw new IllegalArgumentException("fullType must contain \".\" i.e. module.type");
      } else {
         String var1 = itemEvolvedRecipeName.get(var0);
         if (var1 == null) {
            if (debug && getLanguage() != getDefaultLanguage() && !debugItemEvolvedRecipeName.contains(var0)) {
               debugItemEvolvedRecipeName.add(var0);
            }

            Item var2 = ScriptManager.instance.getItem(var0);
            if (var2 == null) {
               var1 = var0;
            } else {
               var1 = var2.getDisplayName();
            }

            itemEvolvedRecipeName.put(var0, var1);
         }

         return var1;
      }
   }

   public static String getMoveableDisplayName(String var0) {
      String var1 = var0.replaceAll(" ", "_").replaceAll("-", "_").replaceAll("'", "").replaceAll("\\.", "");
      String var2 = moveables.get(var1);
      if (var2 == null) {
         return Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "!" + var0 : var0;
      } else {
         return Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "*" + var2 : var2;
      }
   }

   public static String getMoveableDisplayNameOrNull(String var0) {
      String var1 = var0.replaceAll(" ", "_").replaceAll("-", "_").replaceAll("'", "").replaceAll("\\.", "");
      String var2 = moveables.get(var1);
      if (var2 == null) {
         return null;
      } else {
         return Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "*" + var2 : var2;
      }
   }

   public static String getMultiStageBuild(String var0) {
      String var1 = multiStageBuild.get("MultiStageBuild_" + var0);
      if (var1 == null) {
         if (debug && getLanguage() != getDefaultLanguage() && !debugMultiStageBuild.contains(var0)) {
            debugMultiStageBuild.add(var0);
         }

         return var0;
      } else {
         return var1;
      }
   }

   public static String getRecipeName(String var0) {
      String var1 = null;
      var1 = recipe.get(var0);
      if (var1 != null && !var1.isEmpty()) {
         return var1;
      } else {
         if (debug && getLanguage() != getDefaultLanguage() && !debugRecipe.contains(var0)) {
            debugRecipe.add(var0);
         }

         return var0;
      }
   }

   public static Language getDefaultLanguage() {
      return Languages.instance.getDefaultLanguage();
   }

   public static void debugItemEvolvedRecipeNames() {
      if (debug && !debugItemEvolvedRecipeName.isEmpty()) {
         debugwrite("EvolvedRecipeName_" + getLanguage() + ".txt\r\n");
         ArrayList var0 = new ArrayList();
         var0.addAll(debugItemEvolvedRecipeName);
         Collections.sort(var0);

         for (String var2 : var0) {
            debugwrite("\tEvolvedRecipeName_" + var2 + " = \"" + itemEvolvedRecipeName.get(var2) + "\",\r\n");
         }

         debugItemEvolvedRecipeName.clear();
      }
   }

   public static void debugItemNames() {
      if (debug && !debugItem.isEmpty()) {
         debugwrite("ItemName_" + getLanguage() + ".txt\r\n");
         ArrayList var0 = new ArrayList();
         var0.addAll(debugItem);
         Collections.sort(var0);

         for (String var2 : var0) {
            debugwrite("\tItemName_" + var2 + " = \"" + itemName.get(var2) + "\",\r\n");
         }

         debugItem.clear();
      }
   }

   public static void debugMultiStageBuildNames() {
      if (debug && !debugMultiStageBuild.isEmpty()) {
         debugwrite("MultiStageBuild_" + getLanguage() + ".txt\r\n");
         ArrayList var0 = new ArrayList();
         var0.addAll(debugMultiStageBuild);
         Collections.sort(var0);

         for (String var2 : var0) {
            debugwrite("\tMultiStageBuild_" + var2 + " = \"\",\r\n");
         }

         debugMultiStageBuild.clear();
      }
   }

   public static void debugRecipeNames() {
      if (debug && !debugRecipe.isEmpty()) {
         debugwrite("Recipes_" + getLanguage() + ".txt\r\n");
         ArrayList var0 = new ArrayList();
         var0.addAll(debugRecipe);
         Collections.sort(var0);

         for (String var2 : var0) {
            debugwrite("\tRecipe_" + var2.replace(" ", "_") + " = \"\",\r\n");
         }

         debugRecipe.clear();
      }
   }

   private static void debugwrite(String var0) {
      if (debugFile != null) {
         try {
            debugFile.write(var0);
            debugFile.flush();
         } catch (IOException var2) {
         }
      }
   }

   public static ArrayList<String> getAzertyMap() {
      if (azertyLanguages == null) {
         azertyLanguages = new ArrayList<>();
         azertyLanguages.add("FR");
      }

      return azertyLanguages;
   }

   public static String getRadioText(String var0) {
      String var1 = dynamicRadio.get(var0);
      return var1 == null ? var0 : var1;
   }

   public static String getTextMediaEN(String var0) {
      if (ui == null) {
         loadFiles();
      }

      String var1 = null;
      if (var0.startsWith("RM_")) {
         var1 = recordedMedia_EN.get(var0);
      }

      String var2 = Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "*" : null;
      if (var1 == null) {
         if (!missing.contains(var0) && Core.bDebug) {
            if (Core.bDebug) {
               DebugLog.log("ERROR: Missing translation \"" + var0 + "\"");
            }

            if (debug) {
               debugwrite("ERROR: Missing translation \"" + var0 + "\"\r\n");
            }

            missing.add(var0);
         }

         var1 = var0;
         var2 = Core.bDebug && DebugOptions.instance.TranslationPrefix.getValue() ? "!" : null;
      }

      if (var1.contains("<br>")) {
         return var1.replaceAll("<br>", "\n");
      } else {
         return var2 == null ? var1 : var2 + var1;
      }
   }
}
