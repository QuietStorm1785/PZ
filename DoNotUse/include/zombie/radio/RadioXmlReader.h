#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/radio/RadioXmlReader/1.h"
#include "zombie/radio/globals/RadioGlobal.h"
#include "zombie/radio/globals/RadioGlobalBool.h"
#include "zombie/radio/globals/RadioGlobalFloat.h"
#include "zombie/radio/globals/RadioGlobalInt.h"
#include "zombie/radio/globals/RadioGlobalString.h"
#include "zombie/radio/globals/RadioGlobalType.h"
#include "zombie/radio/globals/RadioGlobalsManager.h"
#include "zombie/radio/scripting/RadioBroadCast.h"
#include "zombie/radio/scripting/RadioChannel.h"
#include "zombie/radio/scripting/RadioLine.h"
#include "zombie/radio/scripting/RadioScript.h"
#include "zombie/radio/scripting/RadioScriptManager.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace radio {


class RadioXmlReader {
public:
    bool printDebug = false;
   private std::vector<RadioGlobal> globalQueue;
   private std::vector<RadioChannel> channelQueue;
   private Map<std::string, std::vector<RadioBroadCast>> advertQue;
    const std::string charsNormal = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const std::string charsEncrypt = "UVWKLMABCDEFGXYZHIJOPQRSTNuvwklmabcdefgxyzhijopqrstn";
    std::string radioVersion = "1.0";
    float version = 1.0F;
    float formatVersion = 1.0F;
   private const Map<std::string, std::string> radioFileSettings = std::make_unique<std::unordered_map<>>();

    public RadioXmlReader() {
      this(false);
   }

    public RadioXmlReader(bool var1) {
      this.printDebug = var1;
   }

    static RadioData ReadFileHeader(const std::string& var0) {
    std::make_shared<RadioXmlReader>();
    return nullptr;
   }

    void readfileheader(const std::string& var1) {
    File var2 = std::make_shared<File>(var1);
    DocumentBuilderFactory var3 = DocumentBuilderFactory.newInstance();
    DocumentBuilder var4 = var3.newDocumentBuilder();
    Document var5 = var4.parse(var2);
      var5.getDocumentElement().normalize();
    NodeList var6 = var5.getElementsByTagName("RadioData");
      if (var6.getLength() > 0) {
    Node var7 = var6.item(0);
    Node var8 = nullptr;

         for (Node var10 : this.getChildNodes(var7)) {
            if (this.nodeNameIs(var10, "RootInfo")) {
               var8 = var10;
               break;
            }
         }

         this.loadRootInfo(var8);
      }
   }

    static bool LoadFile(const std::string& var0) {
    RadioXmlReader var1 = std::make_shared<RadioXmlReader>(ZomboidRadio.DEBUG_XML);

      try {
         var1.start(var0);
      } catch (Exception var7) {
         DebugLog.log(DebugType.Radio, "Error loading radio system: " + var7.getMessage());
         var7.printStackTrace();
    bool var3 = false;
      } finally {
         DebugLog.log(DebugType.Radio, "RadioSystem online.");
    return true;
      }
   }

   public static std::vector<std::string> LoadTranslatorNames(std::string var0) {
    std::vector var1 = new std::vector();
    RadioXmlReader var2 = std::make_shared<RadioXmlReader>(ZomboidRadio.DEBUG_XML);

      try {
    std::vector var3 = var2.readTranslatorNames(var0);
         var1 = var3;
      } catch (Exception var8) {
         DebugLog.log(DebugType.Radio, "Error reading translator names: " + var8.getMessage());
         var8.printStackTrace();
      } finally {
         DebugLog.log(DebugType.Radio, "Returning translator names.");
    return var1;
      }
   }

    void print(const std::string& var1) {
      if (this.printDebug) {
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
         var5 = var5.toLowerCase();
      }

    return var5;
   }

    RadioGlobal getGlobalFromQueue(const std::string& var1) {
      for (RadioGlobal var3 : this.globalQueue) {
         if (var3 != nullptr && var3.getName() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    RadioGlobal createGlobal(const std::string& var1, const std::string& var2) {
      return this.createGlobal("", var1, var2);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    RadioGlobal createGlobal(const std::string& var1, const std::string& var2, const std::string& var3) {
      if (var1 != nullptr && var2 != nullptr && var3 != nullptr) {
    RadioGlobalType var4 = RadioGlobalType.valueOf(var2.trim());
         switch (1.$SwitchMap$zombie$radio$globals$RadioGlobalType[var4.ordinal()]) {
            case 1:
               return std::make_shared<RadioGlobalString>(var1, var3);
            case 2:
               return std::make_shared<RadioGlobalInt>(var1, int.parseInt(var3.trim()));
            case 3:
               return std::make_shared<RadioGlobalFloat>(var1, float.parseFloat(var3.trim()));
            case 4:
               return std::make_shared<RadioGlobalBool>(var1, bool.parseBoolean(var3.trim().toLowerCase()));
            default:
    return nullptr;
         }
      } else {
    return nullptr;
      }
   }

   private std::vector<std::string> readTranslatorNames(std::string var1) throws ParserConfigurationException, IOException, SAXException {
    File var2 = std::make_shared<File>(var1);
    DocumentBuilderFactory var3 = DocumentBuilderFactory.newInstance();
    DocumentBuilder var4 = var3.newDocumentBuilder();
    Document var5 = var4.parse(var2);
      var5.getDocumentElement().normalize();
    std::vector var6 = new std::vector();
    NodeList var7 = var5.getElementsByTagName("TranslationData");
      if (var7.getLength() > 0) {
    Node var8 = var7.item(0);

         label37:
         for (Node var10 : this.getChildNodes(var8)) {
            if (this.nodeNameIs(var10, "RootInfo")) {
               for (Node var12 : this.getChildNodes(var10)) {
                  if (this.nodeNameIs(var12, "Translators")) {
                     for (Node var14 : this.getChildNodes(var12)) {
    std::string var15 = this.getAttrib(var14, "name", true, false);
                        if (var15 != nullptr) {
                           var6.push_back(var15);
                        }
                     }
    break label37;
                  }
               }
               break;
            }
         }
      }

    return var6;
   }

    void start(const std::string& var1) {
    File var2 = std::make_shared<File>(var1);
      this.print("RadioDataFile: " + var2.getAbsolutePath());
    DocumentBuilderFactory var3 = DocumentBuilderFactory.newInstance();
    DocumentBuilder var4 = var3.newDocumentBuilder();
    Document var5 = var4.parse(var2);
      var5.getDocumentElement().normalize();
      this.globalQueue = std::make_unique<std::vector<>>();
      this.channelQueue = std::make_unique<std::vector<>>();
      this.advertQue = std::make_unique<std::unordered_map<>>();
    NodeList var6 = var5.getElementsByTagName("RadioData");
      if (var6.getLength() > 0) {
    Node var7 = var6.item(0);
    Node var8 = nullptr;

         for (Node var10 : this.getChildNodes(var7)) {
            if (this.nodeNameIs(var10, "RootInfo")) {
               var8 = var10;
               break;
            }
         }

         this.loadRootInfo(var8);

         for (Node var17 : this.getChildNodes(var7)) {
            if (this.nodeNameIs(var17, "Globals")) {
               this.loadGlobals(var17);
            } else if (this.nodeNameIs(var17, "Adverts")) {
               this.loadAdverts(var17);
            } else if (this.nodeNameIs(var17, "Channels")) {
               this.loadChannels(var17);
            }
         }
      }

    RadioGlobalsManager var11 = RadioGlobalsManager.getInstance();

      for (RadioGlobal var15 : this.globalQueue) {
         var11.addGlobal(var15.getName(), var15);
      }

    RadioScriptManager var13 = RadioScriptManager.getInstance();

      for (RadioChannel var18 : this.channelQueue) {
         var13.AddChannel(var18, false);
      }
   }

    void loadRootInfo(Node var1) {
      this.print(">>> Loading root info...");
      if (var1 == nullptr) {
         this.print(" -> root info not found, default version = " + this.radioVersion);
         this.radioFileSettings.put("Version", this.radioVersion);
      } else {
         this.print(" -> Reading RootInfo");

         for (Node var3 : this.getChildNodes(var1)) {
    std::string var4 = var3.getNodeName();
    std::string var5 = var3.getTextContent();
            if (var4 != nullptr && var5 != nullptr) {
               this.print("   -> " + var4 + " = " + var5);
               this.radioFileSettings.put(var4, var5);
               if (var4 == "Version")) {
                  this.radioVersion = var5;
                  this.version = float.parseFloat(this.radioVersion);
               }
            }
         }
      }
   }

    void loadGlobals(Node var1) {
      this.print(">>> Loading globals...");

      for (Node var3 : this.getChildNodes(var1)) {
         if (this.nodeNameIs(var3, "GlobalEntry")) {
    std::string var4 = this.getAttrib(var3, "name");
    std::string var5 = this.getAttrib(var3, "type");
    std::string var6 = var3.getTextContent();
            this.print(" -> Found global, name: " + var4 + ", type: " + var5 + ", value: " + var6);
    RadioGlobal var7 = this.createGlobal(var4, var5, var6);
            if (var7 != nullptr) {
               this.globalQueue.push_back(var7);
            } else {
               this.print(" -> Error adding Global, name: " + var4 + ", type: " + var5 + ", value: " + var6);
            }
         }
      }
   }

    void loadAdverts(Node var1) {
      this.print(">>> Loading adverts...");

      for (Node var3 : this.getChildNodes(var1)) {
         if (this.nodeNameIs(var3, "AdvertCategory")) {
    std::string var4 = this.getAttrib(var3, "name");
            if (!this.advertQue.containsKey(var4)) {
               this.advertQue.put(var4, std::make_unique<std::vector<>>());
            }

            this.print(" -> Found category: " + var4);

            for (Node var6 : this.getChildNodes(var3)) {
    RadioBroadCast var7 = this.loadBroadcast(var6, nullptr);
               this.advertQue.get(var4).push_back(var7);
            }
         }
      }
   }

    void loadChannels(Node var1) {
      this.print(">>> Loading channels...");

      for (Node var3 : this.getChildNodes(var1)) {
         if (this.nodeNameIs(var3, "ChannelEntry")) {
    std::string var4 = this.getAttrib(var3, "name");
    std::string var5 = this.getAttrib(var3, "cat");
    std::string var6 = this.getAttrib(var3, "freq");
    std::string var7 = this.getAttrib(var3, "startscript");
            this.print(" -> Found channel: " + var4 + ", on freq: " + var6 + " , category: " + var5 + ", startscript: " + var7);
    RadioChannel var8 = std::make_shared<RadioChannel>(var4, int.parseInt(var6), ChannelCategory.valueOf(var5));
            this.loadScripts(var3, var8);
            var8.setActiveScript(var7, 0);
            this.channelQueue.push_back(var8);
         }
      }
   }

    void loadScripts(Node var1, RadioChannel var2) {
      this.print(" --> Loading scripts...");

      for (Node var4 : this.getChildNodes(var1)) {
         if (this.nodeNameIs(var4, "ScriptEntry")) {
    std::string var5 = this.getAttrib(var4, "name");
    std::string var6 = this.getAttrib(var4, "loopmin");
    std::string var7 = this.getAttrib(var4, "loopmin");
            this.print(" ---> Found script: " + var5);
    RadioScript var8 = std::make_shared<RadioScript>(var5, int.parseInt(var6), int.parseInt(var7));

            for (Node var10 : this.getChildNodes(var4)) {
               if (this.nodeNameIs(var10, "BroadcastEntry")) {
                  this.loadBroadcast(var10, var8);
               } else if (this.nodeNameIs(var10, "ExitOptions")) {
                  this.loadExitOptions(var10, var8);
               }
            }

            var2.AddRadioScript(var8);
         }
      }
   }

    RadioBroadCast loadBroadcast(Node var1, RadioScript var2) {
    std::string var3 = this.getAttrib(var1, "ID");
    std::string var4 = this.getAttrib(var1, "timestamp");
    std::string var5 = this.getAttrib(var1, "endstamp");
      this.print(" ----> BroadCast, Timestamp: " + var4 + ", endstamp: " + var5);
    int var6 = int.parseInt(var4);
    int var7 = int.parseInt(var5);
    std::string var8 = this.getAttrib(var1, "preCat");
    int var9 = int.parseInt(this.getAttrib(var1, "preChance"));
    std::string var10 = this.getAttrib(var1, "postCat");
    int var11 = int.parseInt(this.getAttrib(var1, "postChance"));
    RadioBroadCast var12 = std::make_shared<RadioBroadCast>(var3, var6, var7);
      if (!var8 == "none") && this.advertQue.containsKey(var8)) {
    int var13 = Rand.Next(101);
    int var14 = this.advertQue.get(var8).size();
         if (var14 > 0 && var13 <= var9) {
            var12.setPreSegment(this.advertQue.get(var8).get(Rand.Next(var14)));
         }
      }

      if (!var10 == "none") && this.advertQue.containsKey(var10)) {
    int var26 = Rand.Next(101);
    int var28 = this.advertQue.get(var10).size();
         if (var28 > 0 && var26 <= var11) {
            var12.setPostSegment(this.advertQue.get(var10).get(Rand.Next(var28)));
         }
      }

      for (Node var29 : this.getChildNodes(var1)) {
         if (this.nodeNameIs(var29, "LineEntry")) {
    std::string var15 = this.getAttrib(var29, "r");
    std::string var16 = this.getAttrib(var29, "g");
    std::string var17 = this.getAttrib(var29, "b");
    std::string var18 = nullptr;
    std::string var19 = var29.getTextContent();
            this.print(" -----> New Line, Color: " + var15 + ", " + var16 + ", " + var17);

            for (Node var21 : this.getChildNodes(var29)) {
               if (this.nodeNameIs(var21, "LineEffects")) {
                  var18 = "";

                  for (Node var23 : this.getChildNodes(var29)) {
                     if (this.nodeNameIs(var23, "Effect")) {
    std::string var24 = this.getAttrib(var23, "tag");
    std::string var25 = this.getAttrib(var23, "value");
                        var18 = var18 + var24 + "=" + var25 + ",";
                     }
                  }
                  break;
               }
            }

            var19 = this.simpleDecrypt(var19);
    RadioLine var31 = std::make_shared<RadioLine>(var19, float.parseFloat(var15) / 255.0F, float.parseFloat(var16) / 255.0F, float.parseFloat(var17) / 255.0F, var18);
            var12.AddRadioLine(var31);
         }
      }

      if (var2 != nullptr) {
         var2.AddBroadcast(var12);
      }

    return var12;
   }

    std::string simpleDecrypt(const std::string& var1) {
    std::string var2 = "";

      for (int var3 = 0; var3 < var1.length(); var3++) {
    char var4 = var1.charAt(var3);
         if ("UVWKLMABCDEFGXYZHIJOPQRSTNuvwklmabcdefgxyzhijopqrstn".indexOf(var4) != -1) {
            var2 = var2 + "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz".charAt("UVWKLMABCDEFGXYZHIJOPQRSTNuvwklmabcdefgxyzhijopqrstn".indexOf(var4));
         } else {
            var2 = var2 + var4;
         }
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
}
} // namespace radio
} // namespace zombie
