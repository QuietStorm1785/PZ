package zombie.radio;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import zombie.ZomboidFileSystem;
import zombie.core.Core;
import zombie.core.Language;
import zombie.core.Rand;
import zombie.core.Translator;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.radio.scripting.RadioBroadCast;
import zombie.radio.scripting.RadioChannel;
import zombie.radio.scripting.RadioLine;
import zombie.radio.scripting.RadioScript;

public final class RadioData {
   static boolean PRINTDEBUG = false;
   private boolean isVanilla = false;
   private String GUID;
   private int version;
   private String xmlFilePath;
   private final ArrayList<RadioChannel> radioChannels = new ArrayList<>();
   private final ArrayList<RadioTranslationData> translationDataList = new ArrayList<>();
   private RadioTranslationData currentTranslation;
   private Node rootNode;
   private final Map<String, RadioScript> advertQue = new HashMap<>();
   private static final String fieldStart = "\\$\\{t:";
   private static final String fieldEnd = "\\}";
   private static final String regex = "\\$\\{t:([^}]+)\\}";
   private static final Pattern pattern = Pattern.compile("\\$\\{t:([^}]+)\\}");

   public RadioData(String var1) {
      this.xmlFilePath = var1;
   }

   public ArrayList<RadioChannel> getRadioChannels() {
      return this.radioChannels;
   }

   public boolean isVanilla() {
      return this.isVanilla;
   }

   public static ArrayList<String> getTranslatorNames(Language var0) {
      ArrayList var1 = new ArrayList();
      if (var0 != Translator.getDefaultLanguage()) {
         for (RadioData var4 : fetchRadioData(false)) {
            for (RadioTranslationData var6 : var4.translationDataList) {
               if (var6.getLanguageEnum() == var0) {
                  for (String var8 : var6.getTranslators()) {
                     if (!var1.contains(var8)) {
                        var1.add(var8);
                     }
                  }
               }
            }
         }
      }

      return var1;
   }

   private static ArrayList<RadioData> fetchRadioData(boolean var0) {
      return fetchRadioData(var0, DebugLog.isEnabled(DebugType.Radio));
   }

   private static ArrayList<RadioData> fetchRadioData(boolean var0, boolean var1) {
      ArrayList var2 = new ArrayList();

      try {
         ArrayList var3 = ZomboidFileSystem.instance.getModIDs();
         if (var1) {
            System.out.println(":: Searching for radio data files:");
         }

         ArrayList var4 = new ArrayList();
         searchForFiles(ZomboidFileSystem.instance.getMediaFile("radio"), "xml", var4);
         ArrayList var5 = new ArrayList(var4);
         if (var0) {
            for (int var6 = 0; var6 < var3.size(); var6++) {
               String var7 = ZomboidFileSystem.instance.getModDir((String)var3.get(var6));
               if (var7 != null) {
                  searchForFiles(new File(var7 + File.separator + "media" + File.separator + "radio"), "xml", var4);
               }
            }
         }

         for (String var15 : var4) {
            RadioData var8 = ReadFile(var15);
            if (var8 != null) {
               if (var1) {
                  System.out.println(" Found file: " + var15);
               }

               for (String var10 : var5) {
                  if (var10.equals(var15)) {
                     var8.isVanilla = true;
                  }
               }

               var2.add(var8);
            } else {
               System.out.println("[Failure] Cannot parse file: " + var15);
            }
         }

         if (var1) {
            System.out.println(":: Searching for translation files:");
         }

         var4.clear();
         searchForFiles(ZomboidFileSystem.instance.getMediaFile("radio"), "txt", var4);
         if (var0) {
            for (int var13 = 0; var13 < var3.size(); var13++) {
               String var16 = ZomboidFileSystem.instance.getModDir((String)var3.get(var13));
               if (var16 != null) {
                  searchForFiles(new File(var16 + File.separator + "media" + File.separator + "radio"), "txt", var4);
               }
            }
         }

         for (String var17 : var4) {
            RadioTranslationData var18 = RadioTranslationData.ReadFile(var17);
            if (var18 != null) {
               if (var1) {
                  System.out.println(" Found file: " + var17);
               }

               for (RadioData var20 : var2) {
                  if (var20.GUID.equals(var18.getGuid())) {
                     if (var1) {
                        System.out.println(" Adding translation: " + var20.GUID);
                     }

                     var20.translationDataList.add(var18);
                  }
               }
            } else if (var1) {
               System.out.println("[Failure] " + var17);
            }
         }
      } catch (Exception var11) {
         var11.printStackTrace();
      }

      return var2;
   }

   public static ArrayList<RadioData> fetchAllRadioData() {
      boolean var0 = DebugLog.isEnabled(DebugType.Radio);
      ArrayList var1 = fetchRadioData(true);

      for (int var2 = var1.size() - 1; var2 >= 0; var2--) {
         RadioData var3 = (RadioData)var1.get(var2);
         if (var3.loadRadioScripts()) {
            if (var0) {
               DebugLog.Radio.println(" Adding" + (var3.isVanilla ? " (vanilla)" : "") + " file: " + var3.xmlFilePath);
               DebugLog.Radio.println(" - GUID: " + var3.GUID);
            }

            var3.currentTranslation = null;
            var3.translationDataList.clear();
         } else {
            DebugLog.Radio.println("[Failure] Failed to load radio scripts for GUID: " + var3.GUID);
            DebugLog.Radio.println("          File: " + var3.xmlFilePath);
            var1.remove(var2);
         }
      }

      return var1;
   }

   private static void searchForFiles(File var0, String var1, ArrayList<String> var2) {
      if (var0.isDirectory()) {
         String[] var3 = var0.list();

         for (int var4 = 0; var4 < var3.length; var4++) {
            searchForFiles(new File(var0.getAbsolutePath() + File.separator + var3[var4]), var1, var2);
         }
      } else if (var0.getAbsolutePath().toLowerCase().contains(var1)) {
         var2.add(var0.getAbsolutePath());
      }
   }

   private static RadioData ReadFile(String var0) {
      RadioData var1 = new RadioData(var0);
      boolean var2 = false;

      try {
         if (DebugLog.isEnabled(DebugType.Radio)) {
            DebugLog.Radio.println("Reading xml: " + var0);
         }

         File var3 = new File(var0);
         DocumentBuilderFactory var4 = DocumentBuilderFactory.newInstance();
         DocumentBuilder var5 = var4.newDocumentBuilder();
         Document var6 = var5.parse(var3);
         var6.getDocumentElement().normalize();
         NodeList var7 = var6.getElementsByTagName("RadioData");
         if (DebugLog.isEnabled(DebugType.Radio)) {
            DebugLog.Radio.println("RadioData nodes len: " + var7.getLength());
         }

         if (var7.getLength() > 0) {
            var1.rootNode = var7.item(0);
            var2 = var1.loadRootInfo();
            if (DebugLog.isEnabled(DebugType.Radio)) {
               DebugLog.Radio.println("valid file: " + var2);
            }
         }
      } catch (Exception var8) {
         var8.printStackTrace();
      }

      return var2 ? var1 : null;
   }

   private void print(String var1) {
      if (PRINTDEBUG) {
         DebugLog.log(DebugType.Radio, var1);
      }
   }

   private ArrayList<Node> getChildNodes(Node var1) {
      ArrayList var2 = new ArrayList();
      if (var1.hasChildNodes()) {
         Node var3 = var1.getFirstChild();

         while (var3 != null) {
            if (!(var3 instanceof Element)) {
               var3 = var3.getNextSibling();
            } else {
               var2.add(var3);
               var3 = var3.getNextSibling();
            }
         }
      }

      return var2;
   }

   private String toLowerLocaleSafe(String var1) {
      return var1.toLowerCase(Locale.ENGLISH);
   }

   private boolean nodeNameIs(Node var1, String var2) {
      return var1.getNodeName().equals(var2);
   }

   private String getAttrib(Node var1, String var2, boolean var3) {
      return this.getAttrib(var1, var2, var3, false);
   }

   private String getAttrib(Node var1, String var2) {
      return this.getAttrib(var1, var2, true, false).trim();
   }

   private String getAttrib(Node var1, String var2, boolean var3, boolean var4) {
      String var5 = var1.getAttributes().getNamedItem(var2).getTextContent();
      if (var3) {
         var5 = var5.trim();
      }

      if (var4) {
         var5 = this.toLowerLocaleSafe(var5);
      }

      return var5;
   }

   private boolean loadRootInfo() {
      boolean var1 = DebugLog.isEnabled(DebugType.Radio);
      if (var1) {
         DebugLog.Radio.println("Reading RootInfo...");
      }

      for (Node var3 : this.getChildNodes(this.rootNode)) {
         if (this.nodeNameIs(var3, "RootInfo")) {
            if (var1) {
               DebugLog.Radio.println("RootInfo found");
            }

            for (Node var5 : this.getChildNodes(var3)) {
               String var6 = var5.getNodeName();
               String var7 = var5.getTextContent();
               if (var6 != null && var7 != null) {
                  var6 = var6.trim();
                  if (var1) {
                     DebugLog.Radio.println("Found element: " + var6);
                  }

                  if (var6.equals("Version")) {
                     if (var1) {
                        DebugLog.Radio.println("Version = " + this.version);
                     }

                     this.version = Integer.parseInt(var7);
                  } else if (var6.equals("FileGUID")) {
                     if (var1) {
                        DebugLog.Radio.println("GUID = " + var7);
                     }

                     this.GUID = var7;
                  }
               }
            }
         }
      }

      return this.GUID != null && this.version >= 0;
   }

   private boolean loadRadioScripts() {
      boolean var1 = false;
      this.currentTranslation = null;
      this.advertQue.clear();
      if (Core.getInstance().getContentTranslationsEnabled() && Translator.getLanguage() != Translator.getDefaultLanguage()) {
         System.out.println("Attempting to load translation: " + Translator.getLanguage().toString());

         for (RadioTranslationData var3 : this.translationDataList) {
            if (var3.getLanguageEnum() == Translator.getLanguage()) {
               System.out.println("Translation found!");
               if (var3.loadTranslations()) {
                  this.currentTranslation = var3;
                  System.out.println("Count = " + this.currentTranslation.getTranslationCount());
               } else {
                  System.out.println("Error loading translations for " + this.GUID);
               }
            }
         }
      } else if (!Core.getInstance().getContentTranslationsEnabled()) {
         System.out.println("NOTE: Community Content Translations are disabled.");
      }

      for (Node var6 : this.getChildNodes(this.rootNode)) {
         if (this.nodeNameIs(var6, "Adverts")) {
            this.loadAdverts(var6);
         }
      }

      for (Node var7 : this.getChildNodes(this.rootNode)) {
         if (this.nodeNameIs(var7, "Channels")) {
            this.loadChannels(var7);
            var1 = true;
         }
      }

      return var1;
   }

   private void loadAdverts(Node var1) {
      this.print(">>> Loading adverts...");
      ArrayList var2 = new ArrayList();

      for (RadioScript var4 : this.loadScripts(var1, var2, true)) {
         if (!this.advertQue.containsKey(var4.GetName())) {
            this.advertQue.put(var4.GetGUID(), var4);
         }
      }
   }

   private void loadChannels(Node var1) {
      this.print(">>> Loading channels...");
      ArrayList var2 = new ArrayList();

      for (Node var4 : this.getChildNodes(var1)) {
         if (this.nodeNameIs(var4, "ChannelEntry")) {
            String var5 = this.getAttrib(var4, "ID");
            String var6 = this.getAttrib(var4, "name");
            String var7 = this.getAttrib(var4, "cat");
            String var8 = this.getAttrib(var4, "freq");
            String var9 = this.getAttrib(var4, "startscript");
            this.print(" -> Found channel: " + var6 + ", on freq: " + var8 + " , category: " + var7 + ", startscript: " + var9 + ", ID: " + var5);
            RadioChannel var10 = new RadioChannel(var6, Integer.parseInt(var8), ChannelCategory.valueOf(var7), var5);
            var2.clear();
            var2 = this.loadScripts(var4, var2, false);

            for (RadioScript var12 : var2) {
               var10.AddRadioScript(var12);
            }

            var10.setActiveScript(var9, 0);
            this.radioChannels.add(var10);
            var10.setRadioData(this);
         }
      }
   }

   private ArrayList<RadioScript> loadScripts(Node var1, ArrayList<RadioScript> var2, boolean var3) {
      this.print(" --> Loading scripts...");

      for (Node var5 : this.getChildNodes(var1)) {
         if (this.nodeNameIs(var5, "ScriptEntry")) {
            String var6 = this.getAttrib(var5, "ID");
            String var7 = this.getAttrib(var5, "name");
            String var8 = this.getAttrib(var5, "loopmin");
            String var9 = this.getAttrib(var5, "loopmax");
            this.print(" ---> Found script: " + var7);
            RadioScript var10 = new RadioScript(var7, Integer.parseInt(var8), Integer.parseInt(var9), var6);

            for (Node var12 : this.getChildNodes(var5)) {
               if (this.nodeNameIs(var12, "BroadcastEntry")) {
                  this.loadBroadcast(var12, var10);
               } else if (!var3 && this.nodeNameIs(var12, "ExitOptions")) {
                  this.loadExitOptions(var12, var10);
               }
            }

            var2.add(var10);
         }
      }

      return var2;
   }

   private RadioBroadCast loadBroadcast(Node var1, RadioScript var2) {
      String var3 = this.getAttrib(var1, "ID");
      String var4 = this.getAttrib(var1, "timestamp");
      String var5 = this.getAttrib(var1, "endstamp");
      this.print(" ----> BroadCast, Timestamp: " + var4 + ", endstamp: " + var5);
      int var6 = Integer.parseInt(var4);
      int var7 = Integer.parseInt(var5);
      String var8 = this.getAttrib(var1, "isSegment");
      boolean var9 = this.toLowerLocaleSafe(var8).equals("true");
      String var10 = this.getAttrib(var1, "advertCat");
      RadioBroadCast var11 = new RadioBroadCast(var3, var6, var7);
      if (!var9 && !this.toLowerLocaleSafe(var10).equals("none") && this.advertQue.containsKey(var10) && Rand.Next(101) < 75) {
         RadioScript var12 = this.advertQue.get(var10);
         if (var12.getBroadcastList().size() > 0) {
            if (Rand.Next(101) < 50) {
               var11.setPreSegment((RadioBroadCast)var12.getBroadcastList().get(Rand.Next(var12.getBroadcastList().size())));
            } else {
               var11.setPostSegment((RadioBroadCast)var12.getBroadcastList().get(Rand.Next(var12.getBroadcastList().size())));
            }
         }
      }

      for (Node var13 : this.getChildNodes(var1)) {
         if (this.nodeNameIs(var13, "LineEntry")) {
            String var14 = this.getAttrib(var13, "ID");
            String var15 = this.getAttrib(var13, "r");
            String var16 = this.getAttrib(var13, "g");
            String var17 = this.getAttrib(var13, "b");
            String var18 = null;
            if (var13.getAttributes().getNamedItem("codes") != null) {
               var18 = this.getAttrib(var13, "codes");
            }

            String var19 = var13.getTextContent();
            this.print(" -----> New Line, Color: " + var15 + ", " + var16 + ", " + var17);
            var19 = this.checkForTranslation(var14, var19);
            RadioLine var20 = new RadioLine(var19, Float.parseFloat(var15) / 255.0F, Float.parseFloat(var16) / 255.0F, Float.parseFloat(var17) / 255.0F, var18);
            var11.AddRadioLine(var20);
            var19 = var19.trim();
            if (var19.toLowerCase().startsWith("${t:")) {
               var19 = this.checkForCustomAirTimer(var19, var20);
               var20.setText(var19);
            }
         }
      }

      if (var2 != null) {
         var2.AddBroadcast(var11, var9);
      }

      return var11;
   }

   private String checkForTranslation(String var1, String var2) {
      if (this.currentTranslation != null) {
         String var3 = this.currentTranslation.getTranslation(var1);
         if (var3 != null) {
            return var3;
         }

         DebugLog.log(DebugType.Radio, "no translation for: " + var1);
      }

      return var2;
   }

   private void loadExitOptions(Node var1, RadioScript var2) {
      for (Node var4 : this.getChildNodes(var1)) {
         if (this.nodeNameIs(var4, "ExitOption")) {
            String var5 = this.getAttrib(var4, "script");
            String var6 = this.getAttrib(var4, "chance");
            String var7 = this.getAttrib(var4, "delay");
            int var8 = Integer.parseInt(var6);
            int var9 = Integer.parseInt(var7);
            var2.AddExitOption(var5, var8, var9);
         }
      }
   }

   private String checkForCustomAirTimer(String var1, RadioLine var2) {
      Matcher var3 = pattern.matcher(var1);
      String var4 = var1;
      float var5 = -1.0F;
      if (var3.find()) {
         String var6 = var3.group(1).toLowerCase().trim();

         try {
            var5 = Float.parseFloat(var6);
            var2.setAirTime(var5);
         } catch (Exception var8) {
            var8.printStackTrace();
         }

         var4 = var1.replaceFirst("\\$\\{t:([^}]+)\\}", "");
      }

      return var5 >= 0.0F ? "[cdt=" + var5 + "]" + var4.trim() : var4.trim();
   }
}
