#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/Language.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/radio/scripting/RadioBroadCast.h"
#include "zombie/radio/scripting/RadioChannel.h"
#include "zombie/radio/scripting/RadioLine.h"
#include "zombie/radio/scripting/RadioScript.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace radio {


class RadioData {
public:
    static bool PRINTDEBUG = false;
    bool isVanilla = false;
    std::string GUID;
    int version;
    std::string xmlFilePath;
   private const std::vector<RadioChannel> radioChannels = std::make_unique<std::vector<>>();
   private const std::vector<RadioTranslationData> translationDataList = std::make_unique<std::vector<>>();
    RadioTranslationData currentTranslation;
    Node rootNode;
   private const Map<std::string, RadioScript> advertQue = std::make_unique<std::unordered_map<>>();
    static const std::string fieldStart = "\\$\\{t:";
    static const std::string fieldEnd = "\\}";
    static const std::string regex = "\\$\\{t:([^}]+)\\}";
    static const Pattern pattern = Pattern.compile("\\$\\{t:([^}]+)\\}");

    public RadioData(const std::string& var1) {
      this.xmlFilePath = var1;
   }

   public std::vector<RadioChannel> getRadioChannels() {
      return this.radioChannels;
   }

    bool isVanilla() {
      return this.isVanilla;
   }

   public static std::vector<std::string> getTranslatorNames(Language var0) {
    std::vector var1 = new std::vector();
      if (var0 != Translator.getDefaultLanguage()) {
         for (RadioData var4 : fetchRadioData(false)) {
            for (RadioTranslationData var6 : var4.translationDataList) {
               if (var6.getLanguageEnum() == var0) {
                  for (std::string var8 : var6.getTranslators()) {
                     if (!var1.contains(var8)) {
                        var1.push_back(var8);
                     }
                  }
               }
            }
         }
      }

    return var1;
   }

   private static std::vector<RadioData> fetchRadioData(boolean var0) {
    return fetchRadioData();
   }

   private static std::vector<RadioData> fetchRadioData(boolean var0, boolean var1) {
    std::vector var2 = new std::vector();

      try {
    std::vector var3 = ZomboidFileSystem.instance.getModIDs();
         if (var1) {
            System.out.println(":: Searching for radio data files:");
         }

    std::vector var4 = new std::vector();
         searchForFiles(ZomboidFileSystem.instance.getMediaFile("radio"), "xml", var4);
    std::vector var5 = new std::vector(var4);
         if (var0) {
            for (int var6 = 0; var6 < var3.size(); var6++) {
    std::string var7 = ZomboidFileSystem.instance.getModDir((std::string)var3.get(var6));
               if (var7 != nullptr) {
                  searchForFiles(std::make_shared<File>(var7 + File.separator + "media" + File.separator + "radio"), "xml", var4);
               }
            }
         }

    for (auto& var15 : var4)    RadioData var8 = ReadFile(var15);
            if (var8 != nullptr) {
               if (var1) {
                  System.out.println(" Found file: " + var15);
               }

    for (auto& var10 : var5)                  if (var10 == var15)) {
                     var8.isVanilla = true;
                  }
               }

               var2.push_back(var8);
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
    std::string var16 = ZomboidFileSystem.instance.getModDir((std::string)var3.get(var13));
               if (var16 != nullptr) {
                  searchForFiles(std::make_shared<File>(var16 + File.separator + "media" + File.separator + "radio"), "txt", var4);
               }
            }
         }

    for (auto& var17 : var4)    RadioTranslationData var18 = RadioTranslationData.ReadFile(var17);
            if (var18 != nullptr) {
               if (var1) {
                  System.out.println(" Found file: " + var17);
               }

    for (auto& var20 : var2)                  if (var20.GUID == var18.getGuid())) {
                     if (var1) {
                        System.out.println(" Adding translation: " + var20.GUID);
                     }

                     var20.translationDataList.push_back(var18);
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

   public static std::vector<RadioData> fetchAllRadioData() {
    bool var0 = DebugLog.isEnabled(DebugType.Radio);
    std::vector var1 = fetchRadioData(true);

      for (int var2 = var1.size() - 1; var2 >= 0; var2--) {
    RadioData var3 = (RadioData)var1.get(var2);
         if (var3.loadRadioScripts()) {
            if (var0) {
               DebugLog.Radio.println(" Adding" + (var3.isVanilla ? " (vanilla)" : "") + " file: " + var3.xmlFilePath);
               DebugLog.Radio.println(" - GUID: " + var3.GUID);
            }

            var3.currentTranslation = nullptr;
            var3.translationDataList.clear();
         } else {
            DebugLog.Radio.println("[Failure] Failed to load radio scripts for GUID: " + var3.GUID);
            DebugLog.Radio.println("          File: " + var3.xmlFilePath);
            var1.remove(var2);
         }
      }

    return var1;
   }

    static void searchForFiles(File var0, const std::string& var1, std::vector<std::string> var2) {
      if (var0.isDirectory()) {
         std::string[] var3 = var0.list();

         for (int var4 = 0; var4 < var3.length; var4++) {
            searchForFiles(std::make_shared<File>(var0.getAbsolutePath() + File.separator + var3[var4]), var1, var2);
         }
      } else if (var0.getAbsolutePath().toLowerCase().contains(var1)) {
         var2.push_back(var0.getAbsolutePath());
      }
   }

    static RadioData ReadFile(const std::string& var0) {
    RadioData var1 = std::make_shared<RadioData>(var0);
    bool var2 = false;

      try {
         if (DebugLog.isEnabled(DebugType.Radio)) {
            DebugLog.Radio.println("Reading xml: " + var0);
         }

    File var3 = std::make_shared<File>(var0);
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

      return var2 ? var1 : nullptr;
   }

    void print(const std::string& var1) {
      if (PRINTDEBUG) {
         DebugLog.log(DebugType.Radio, var1);
      }
   }

   private std::vector<Node> getChildNodes(Node var1) {
    std::vector var2 = new std::vector();
      if (var1.hasChildNodes()) {
    Node var3 = var1.getFirstChild();

         while (var3 != nullptr) {
            if (!(dynamic_cast<Element*>(var3) != nullptr)) {
               var3 = var3.getNextSibling();
            } else {
               var2.push_back(var3);
               var3 = var3.getNextSibling();
            }
         }
      }

    return var2;
   }

    std::string toLowerLocaleSafe(const std::string& var1) {
      return var1.toLowerCase(Locale.ENGLISH);
   }

    bool nodeNameIs(Node var1, const std::string& var2) {
      return var1.getNodeName() == var2);
   }

    std::string getAttrib(Node var1, const std::string& var2, bool var3) {
      return this.getAttrib(var1, var2, var3, false);
   }

    std::string getAttrib(Node var1, const std::string& var2) {
      return this.getAttrib(var1, var2, true, false).trim();
   }

    std::string getAttrib(Node var1, const std::string& var2, bool var3, bool var4) {
    std::string var5 = var1.getAttributes().getNamedItem(var2).getTextContent();
      if (var3) {
         var5 = var5.trim();
      }

      if (var4) {
         var5 = this.toLowerLocaleSafe(var5);
      }

    return var5;
   }

    bool loadRootInfo() {
    bool var1 = DebugLog.isEnabled(DebugType.Radio);
      if (var1) {
         DebugLog.Radio.println("Reading RootInfo...");
      }

      for (Node var3 : this.getChildNodes(this.rootNode)) {
         if (this.nodeNameIs(var3, "RootInfo")) {
            if (var1) {
               DebugLog.Radio.println("RootInfo found");
            }

            for (Node var5 : this.getChildNodes(var3)) {
    std::string var6 = var5.getNodeName();
    std::string var7 = var5.getTextContent();
               if (var6 != nullptr && var7 != nullptr) {
                  var6 = var6.trim();
                  if (var1) {
                     DebugLog.Radio.println("Found element: " + var6);
                  }

                  if (var6 == "Version")) {
                     if (var1) {
                        DebugLog.Radio.println("Version = " + this.version);
                     }

                     this.version = int.parseInt(var7);
                  } else if (var6 == "FileGUID")) {
                     if (var1) {
                        DebugLog.Radio.println("GUID = " + var7);
                     }

                     this.GUID = var7;
                  }
               }
            }
         }
      }

      return this.GUID != nullptr && this.version >= 0;
   }

    bool loadRadioScripts() {
    bool var1 = false;
      this.currentTranslation = nullptr;
      this.advertQue.clear();
      if (Core.getInstance().getContentTranslationsEnabled() && Translator.getLanguage() != Translator.getDefaultLanguage()) {
         System.out.println("Attempting to load translation: " + Translator.getLanguage());

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

    void loadAdverts(Node var1) {
      this.print(">>> Loading adverts...");
    std::vector var2 = new std::vector();

      for (RadioScript var4 : this.loadScripts(var1, var2, true)) {
         if (!this.advertQue.containsKey(var4.GetName())) {
            this.advertQue.put(var4.GetGUID(), var4);
         }
      }
   }

    void loadChannels(Node var1) {
      this.print(">>> Loading channels...");
    std::vector var2 = new std::vector();

      for (Node var4 : this.getChildNodes(var1)) {
         if (this.nodeNameIs(var4, "ChannelEntry")) {
    std::string var5 = this.getAttrib(var4, "ID");
    std::string var6 = this.getAttrib(var4, "name");
    std::string var7 = this.getAttrib(var4, "cat");
    std::string var8 = this.getAttrib(var4, "freq");
    std::string var9 = this.getAttrib(var4, "startscript");
            this.print(" -> Found channel: " + var6 + ", on freq: " + var8 + " , category: " + var7 + ", startscript: " + var9 + ", ID: " + var5);
    RadioChannel var10 = std::make_shared<RadioChannel>(var6, int.parseInt(var8), ChannelCategory.valueOf(var7), var5);
            var2.clear();
            var2 = this.loadScripts(var4, var2, false);

    for (auto& var12 : var2)               var10.AddRadioScript(var12);
            }

            var10.setActiveScript(var9, 0);
            this.radioChannels.push_back(var10);
            var10.setRadioData(this);
         }
      }
   }

   private std::vector<RadioScript> loadScripts(Node var1, std::vector<RadioScript> var2, boolean var3) {
      this.print(" --> Loading scripts...");

      for (Node var5 : this.getChildNodes(var1)) {
         if (this.nodeNameIs(var5, "ScriptEntry")) {
    std::string var6 = this.getAttrib(var5, "ID");
    std::string var7 = this.getAttrib(var5, "name");
    std::string var8 = this.getAttrib(var5, "loopmin");
    std::string var9 = this.getAttrib(var5, "loopmax");
            this.print(" ---> Found script: " + var7);
    RadioScript var10 = std::make_shared<RadioScript>(var7, int.parseInt(var8), int.parseInt(var9), var6);

            for (Node var12 : this.getChildNodes(var5)) {
               if (this.nodeNameIs(var12, "BroadcastEntry")) {
                  this.loadBroadcast(var12, var10);
               } else if (!var3 && this.nodeNameIs(var12, "ExitOptions")) {
                  this.loadExitOptions(var12, var10);
               }
            }

            var2.push_back(var10);
         }
      }

    return var2;
   }

    RadioBroadCast loadBroadcast(Node var1, RadioScript var2) {
    std::string var3 = this.getAttrib(var1, "ID");
    std::string var4 = this.getAttrib(var1, "timestamp");
    std::string var5 = this.getAttrib(var1, "endstamp");
      this.print(" ----> BroadCast, Timestamp: " + var4 + ", endstamp: " + var5);
    int var6 = int.parseInt(var4);
    int var7 = int.parseInt(var5);
    std::string var8 = this.getAttrib(var1, "isSegment");
    bool var9 = this.toLowerLocaleSafe(var8) == "true");
    std::string var10 = this.getAttrib(var1, "advertCat");
    RadioBroadCast var11 = std::make_shared<RadioBroadCast>(var3, var6, var7);
      if (!var9 && !this.toLowerLocaleSafe(var10) == "none") && this.advertQue.containsKey(var10) && Rand.Next(101) < 75) {
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
    std::string var14 = this.getAttrib(var13, "ID");
    std::string var15 = this.getAttrib(var13, "r");
    std::string var16 = this.getAttrib(var13, "g");
    std::string var17 = this.getAttrib(var13, "b");
    std::string var18 = nullptr;
            if (var13.getAttributes().getNamedItem("codes") != nullptr) {
               var18 = this.getAttrib(var13, "codes");
            }

    std::string var19 = var13.getTextContent();
            this.print(" -----> New Line, Color: " + var15 + ", " + var16 + ", " + var17);
            var19 = this.checkForTranslation(var14, var19);
    RadioLine var20 = std::make_shared<RadioLine>(var19, float.parseFloat(var15) / 255.0F, float.parseFloat(var16) / 255.0F, float.parseFloat(var17) / 255.0F, var18);
            var11.AddRadioLine(var20);
            var19 = var19.trim();
            if (var19.toLowerCase().startsWith("${t:")) {
               var19 = this.checkForCustomAirTimer(var19, var20);
               var20.setText(var19);
            }
         }
      }

      if (var2 != nullptr) {
         var2.AddBroadcast(var11, var9);
      }

    return var11;
   }

    std::string checkForTranslation(const std::string& var1, const std::string& var2) {
      if (this.currentTranslation != nullptr) {
    std::string var3 = this.currentTranslation.getTranslation(var1);
         if (var3 != nullptr) {
    return var3;
         }

         DebugLog.log(DebugType.Radio, "no translation for: " + var1);
      }

    return var2;
   }

    void loadExitOptions(Node var1, RadioScript var2) {
      for (Node var4 : this.getChildNodes(var1)) {
         if (this.nodeNameIs(var4, "ExitOption")) {
    std::string var5 = this.getAttrib(var4, "script");
    std::string var6 = this.getAttrib(var4, "chance");
    std::string var7 = this.getAttrib(var4, "delay");
    int var8 = int.parseInt(var6);
    int var9 = int.parseInt(var7);
            var2.AddExitOption(var5, var8, var9);
         }
      }
   }

    std::string checkForCustomAirTimer(const std::string& var1, RadioLine var2) {
    Matcher var3 = pattern.matcher(var1);
    std::string var4 = var1;
    float var5 = -1.0F;
      if (var3.find()) {
    std::string var6 = var3.group(1).toLowerCase().trim();

         try {
            var5 = float.parseFloat(var6);
            var2.setAirTime(var5);
         } catch (Exception var8) {
            var8.printStackTrace();
         }

         var4 = var1.replaceFirst("\\$\\{t:([^}]+)\\}", "");
      }

      return var5 >= 0.0F ? "[cdt=" + var5 + "]" + var4.trim() : var4.trim();
   }
}
} // namespace radio
} // namespace zombie
