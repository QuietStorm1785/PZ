#pragma once
#include "javax/xml/parsers/DocumentBuilder.h"
#include "javax/xml/parsers/DocumentBuilderFactory.h"
#include "org/w3c/dom/Document.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/Node.h"
#include "org/w3c/dom/NodeList.h"
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
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Turbo
 */
class RadioData {
public:
 static bool PRINTDEBUG = false;
 bool isVanilla = false;
 std::string GUID;
 int version;
 std::string xmlFilePath;
private
 ArrayList<RadioChannel> radioChannels = std::make_unique<ArrayList<>>();
private
 ArrayList<RadioTranslationData> translationDataList =
 std::make_unique<ArrayList<>>();
 RadioTranslationData currentTranslation;
 Node rootNode;
private
 Map<String, RadioScript> advertQue = std::make_unique<HashMap<>>();
 static const std::string fieldStart = "\\$\\{t:";
 static const std::string fieldEnd = "\\}";
 static const std::string regex = "\\$\\{t:([^}]+)\\}";
 static const Pattern pattern = Pattern.compile("\\$\\{t:([^}]+)\\}");

public
 RadioData(const std::string &xmlFile) { this->xmlFilePath = xmlFile; }

public
 ArrayList<RadioChannel> getRadioChannels() { return this->radioChannels; }

 bool isVanilla() { return this->isVanilla; }

public
 static ArrayList<String> getTranslatorNames(Language language) {
 std::vector arrayList = new ArrayList();
 if (language != Translator.getDefaultLanguage()) {
 for (RadioData radioData : fetchRadioData(false) {
 for (RadioTranslationData radioTranslationData :
 radioData.translationDataList) {
 if (radioTranslationData.getLanguageEnum() == language) {
 for (String string : radioTranslationData.getTranslators()) {
 if (!arrayList.contains(string) {
 arrayList.add(string);
 }
 }
 }
 }
 }
 }

 return arrayList;
 }

private
 static ArrayList<RadioData> fetchRadioData(boolean boolean0) {
 return fetchRadioData();
 }

private
 static ArrayList<RadioData> fetchRadioData(boolean boolean1,
 boolean boolean0) {
 std::vector arrayList0 = new ArrayList();

 try {
 std::vector arrayList1 = ZomboidFileSystem.instance.getModIDs();
 if (boolean0) {
 System.out.println(":: Searching for radio data files:");
 }

 std::vector arrayList2 = new ArrayList();
 searchForFiles(ZomboidFileSystem.instance.getMediaFile("radio"), "xml",
 arrayList2);
 std::vector arrayList3 = new ArrayList(arrayList2);
 if (boolean1) {
 for (int int0 = 0; int0 < arrayList1.size(); int0++) {
 std::string string0 = ZomboidFileSystem.instance.getModDir(
 (String)arrayList1.get(int0);
 if (string0 != nullptr) {
 searchForFiles(new File(string0 + File.separator + "media" +
 File.separator + "radio"),
 "xml", arrayList2);
 }
 }
 }

 for (auto &string1 : arrayList2)
 RadioData radioData0 = ReadFile(string1);
 if (radioData0 != nullptr) {
 if (boolean0) {
 System.out.println(" Found file: " + string1);
 }

 for (auto &string2 : arrayList3)
 if (string2 == string1) {
 radioData0.isVanilla = true;
 }
 }

 arrayList0.add(radioData0);
 }
 else {
 System.out.println("[Failure] Cannot parse file: " + string1);
 }
 }

 if (boolean0) {
 System.out.println(":: Searching for translation files:");
 }

 arrayList2.clear();
 searchForFiles(ZomboidFileSystem.instance.getMediaFile("radio"), "txt",
 arrayList2);
 if (boolean1) {
 for (int int1 = 0; int1 < arrayList1.size(); int1++) {
 std::string string3 =
 ZomboidFileSystem.instance.getModDir((String)arrayList1.get(int1);
 if (string3 != nullptr) {
 searchForFiles(new File(string3 + File.separator + "media" +
 File.separator + "radio"),
 "txt", arrayList2);
 }
 }
 }

 for (auto &string4 : arrayList2)
 RadioTranslationData radioTranslationData =
 RadioTranslationData.ReadFile(string4);
 if (radioTranslationData != nullptr) {
 if (boolean0) {
 System.out.println(" Found file: " + string4);
 }

 for (auto &radioData1 : arrayList0)
 if (radioData1.GUID == radioTranslationData.getGuid())) {
 if (boolean0) {
 System.out.println(" Adding translation: " + radioData1.GUID);
 }

 radioData1.translationDataList.add(radioTranslationData);
 }
 }
} else if (boolean0) {
 System.out.println("[Failure] " + string4);
}
}
}
catch (Exception exception) {
 exception.printStackTrace();
}

return arrayList0;
}

public
static ArrayList<RadioData> fetchAllRadioData() {
 bool boolean0 = DebugLog.isEnabled(DebugType.Radio);
 std::vector arrayList = fetchRadioData(true);

 for (int int0 = arrayList.size() - 1; int0 >= 0; int0--) {
 RadioData radioData = (RadioData)arrayList.get(int0);
 if (radioData.loadRadioScripts()) {
 if (boolean0) {
 DebugLog.Radio.println(" Adding" +
 (radioData.isVanilla ? " (vanilla)" : "") +
 " file: " + radioData.xmlFilePath);
 DebugLog.Radio.println(" - GUID: " + radioData.GUID);
 }

 radioData.currentTranslation = nullptr;
 radioData.translationDataList.clear();
 } else {
 DebugLog.Radio.println(
 "[Failure] Failed to load radio scripts for GUID: " + radioData.GUID);
 DebugLog.Radio.println(" File: " + radioData.xmlFilePath);
 arrayList.remove(int0);
 }
 }

 return arrayList;
}

static void searchForFiles(File file, const std::string &string,
 ArrayList<String> arrayList) {
 if (file.isDirectory()) {
 String[] strings = file.list();

 for (int int0 = 0; int0 < strings.length; int0++) {
 searchForFiles(
 new File(file.getAbsolutePath() + File.separator + strings[int0]),
 string, arrayList);
 }
 } else if (file.getAbsolutePath().toLowerCase().contains(string) {
 arrayList.add(file.getAbsolutePath());
 }
}

static RadioData ReadFile(const std::string &string) {
 RadioData radioData = new RadioData(string);
 bool boolean0 = false;

 try {
 if (DebugLog.isEnabled(DebugType.Radio) {
 DebugLog.Radio.println("Reading xml: " + string);
 }

 File file = new File(string);
 DocumentBuilderFactory documentBuilderFactory =
 DocumentBuilderFactory.newInstance();
 DocumentBuilder documentBuilder =
 documentBuilderFactory.newDocumentBuilder();
 Document document = documentBuilder.parse(file);
 document.getDocumentElement().normalize();
 NodeList nodeList = document.getElementsByTagName("RadioData");
 if (DebugLog.isEnabled(DebugType.Radio) {
 DebugLog.Radio.println("RadioData nodes len: " + nodeList.getLength());
 }

 if (nodeList.getLength() > 0) {
 radioData.rootNode = nodeList.item(0);
 boolean0 = radioData.loadRootInfo();
 if (DebugLog.isEnabled(DebugType.Radio) {
 DebugLog.Radio.println("valid file: " + boolean0);
 }
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 return boolean0 ? radioData : nullptr;
}

void print(const std::string &string) {
 if (PRINTDEBUG) {
 DebugLog.log(DebugType.Radio, string);
 }
}

private
ArrayList<Node> getChildNodes(Node node0) {
 std::vector arrayList = new ArrayList();
 if (node0.hasChildNodes()) {
 Node node1 = node0.getFirstChild();

 while (node1 != nullptr) {
 if (!(node1 instanceof Element) {
 node1 = node1.getNextSibling();
 } else {
 arrayList.add(node1);
 node1 = node1.getNextSibling();
 }
 }
 }

 return arrayList;
}

std::string toLowerLocaleSafe(const std::string &string) {
 return string.toLowerCase(Locale.ENGLISH);
}

bool nodeNameIs(Node node, const std::string &string) {
 return node.getNodeName() == string);
}

std::string getAttrib(Node node, const std::string &string, bool boolean0) {
 return this->getAttrib(node, string, boolean0, false);
}

std::string getAttrib(Node node, const std::string &string) {
 return this->getAttrib(node, string, true, false).trim();
}

std::string getAttrib(Node node, const std::string &string1, bool boolean0,
 bool boolean1) {
 std::string string0 =
 node.getAttributes().getNamedItem(string1).getTextContent();
 if (boolean0) {
 string0 = string0.trim();
 }

 if (boolean1) {
 string0 = this->toLowerLocaleSafe(string0);
 }

 return string0;
}

bool loadRootInfo() {
 bool boolean0 = DebugLog.isEnabled(DebugType.Radio);
 if (boolean0) {
 DebugLog.Radio.println("Reading RootInfo...");
 }

 for (Node node0 : this->getChildNodes(this->rootNode) {
 if (this->nodeNameIs(node0, "RootInfo")) {
 if (boolean0) {
 DebugLog.Radio.println("RootInfo found");
 }

 for (Node node1 : this->getChildNodes(node0) {
 std::string string0 = node1.getNodeName();
 std::string string1 = node1.getTextContent();
 if (string0 != nullptr && string1 != nullptr) {
 string0 = string0.trim();
 if (boolean0) {
 DebugLog.Radio.println("Found element: " + string0);
 }

 if (string0 == "Version")) {
 if (boolean0) {
 DebugLog.Radio.println("Version = " + this->version);
 }

 this->version = Integer.parseInt(string1);
 }
 else if (string0 == "FileGUID")) {
 if (boolean0) {
 DebugLog.Radio.println("GUID = " + string1);
 }

 this->GUID = string1;
 }
 }
 }
 }
 }

 return this->GUID != nullptr && this->version >= 0;
}

bool loadRadioScripts() {
 bool boolean0 = false;
 this->currentTranslation = nullptr;
 this->advertQue.clear();
 if (Core.getInstance().getContentTranslationsEnabled() &&
 Translator.getLanguage() != Translator.getDefaultLanguage()) {
 System.out.println("Attempting to load translation: " +
 Translator.getLanguage().toString());

 for (RadioTranslationData radioTranslationData : this->translationDataList) {
 if (radioTranslationData.getLanguageEnum() == Translator.getLanguage()) {
 System.out.println("Translation found!");
 if (radioTranslationData.loadTranslations()) {
 this->currentTranslation = radioTranslationData;
 System.out.println("Count = " +
 this->currentTranslation.getTranslationCount());
 } else {
 System.out.println("Error loading translations for " + this->GUID);
 }
 }
 }
 } else if (!Core.getInstance().getContentTranslationsEnabled()) {
 System.out.println("NOTE: Community Content Translations are disabled.");
 }

 for (Node node0 : this->getChildNodes(this->rootNode) {
 if (this->nodeNameIs(node0, "Adverts")) {
 this->loadAdverts(node0);
 }
 }

 for (Node node1 : this->getChildNodes(this->rootNode) {
 if (this->nodeNameIs(node1, "Channels")) {
 this->loadChannels(node1);
 boolean0 = true;
 }
 }

 return boolean0;
}

void loadAdverts(Node node) {
 this->print(">>> Loading adverts...");
 std::vector arrayList = new ArrayList();

 for (RadioScript radioScript : this->loadScripts(node, arrayList, true) {
 if (!this->advertQue.containsKey(radioScript.GetName())) {
 this->advertQue.put(radioScript.GetGUID(), radioScript);
 }
 }
}

void loadChannels(Node node1) {
 this->print(">>> Loading channels...");
 std::vector arrayList = new ArrayList();

 for (Node node0 : this->getChildNodes(node1) {
 if (this->nodeNameIs(node0, "ChannelEntry")) {
 std::string string0 = this->getAttrib(node0, "ID");
 std::string string1 = this->getAttrib(node0, "name");
 std::string string2 = this->getAttrib(node0, "cat");
 std::string string3 = this->getAttrib(node0, "freq");
 std::string string4 = this->getAttrib(node0, "startscript");
 this->print(" -> Found channel: " + string1 + ", on freq: " + string3 +
 " , category: " + string2 + ", startscript: " + string4 +
 ", ID: " + string0);
 RadioChannel radioChannel =
 new RadioChannel(string1, Integer.parseInt(string3),
 ChannelCategory.valueOf(string2), string0);
 arrayList.clear();
 arrayList = this->loadScripts(node0, arrayList, false);

 for (auto &radioScript : arrayList)
 radioChannel.AddRadioScript(radioScript);
 }

 radioChannel.setActiveScript(string4, 0);
 this->radioChannels.add(radioChannel);
 radioChannel.setRadioData(this);
 }
}
}

private
ArrayList<RadioScript> loadScripts(Node node1, ArrayList<RadioScript> arrayList,
 boolean boolean0) {
 this->print(" --> Loading scripts...");

 for (Node node0 : this->getChildNodes(node1) {
 if (this->nodeNameIs(node0, "ScriptEntry")) {
 std::string string0 = this->getAttrib(node0, "ID");
 std::string string1 = this->getAttrib(node0, "name");
 std::string string2 = this->getAttrib(node0, "loopmin");
 std::string string3 = this->getAttrib(node0, "loopmax");
 this->print(" ---> Found script: " + string1);
 RadioScript radioScript =
 new RadioScript(string1, Integer.parseInt(string2),
 Integer.parseInt(string3), string0);

 for (Node node2 : this->getChildNodes(node0) {
 if (this->nodeNameIs(node2, "BroadcastEntry")) {
 this->loadBroadcast(node2, radioScript);
 } else if (!boolean0 && this->nodeNameIs(node2, "ExitOptions")) {
 this->loadExitOptions(node2, radioScript);
 }
 }

 arrayList.add(radioScript);
 }
 }

 return arrayList;
}

RadioBroadCast loadBroadcast(Node node0, RadioScript radioScript1) {
 std::string string0 = this->getAttrib(node0, "ID");
 std::string string1 = this->getAttrib(node0, "timestamp");
 std::string string2 = this->getAttrib(node0, "endstamp");
 this->print(" ----> BroadCast, Timestamp: " + string1 +
 ", endstamp: " + string2);
 int int0 = Integer.parseInt(string1);
 int int1 = Integer.parseInt(string2);
 std::string string3 = this->getAttrib(node0, "isSegment");
 bool boolean0 = this->toLowerLocaleSafe(string3).equals("true");
 std::string string4 = this->getAttrib(node0, "advertCat");
 RadioBroadCast radioBroadCast = new RadioBroadCast(string0, int0, int1);
 if (!boolean0 && !this->toLowerLocaleSafe(string4) == "none") && this->advertQue.containsKey(string4) && Rand.Next(101) < 75) {
 RadioScript radioScript0 = this->advertQue.get(string4);
 if (radioScript0.getBroadcastList().size() > 0) {
 if (Rand.Next(101) < 50) {
 radioBroadCast.setPreSegment(radioScript0.getBroadcastList().get(
 Rand.Next(radioScript0.getBroadcastList().size())));
 } else {
 radioBroadCast.setPostSegment(radioScript0.getBroadcastList().get(
 Rand.Next(radioScript0.getBroadcastList().size())));
 }
 }
 }

 for (Node node1 : this->getChildNodes(node0) {
 if (this->nodeNameIs(node1, "LineEntry")) {
 std::string string5 = this->getAttrib(node1, "ID");
 std::string string6 = this->getAttrib(node1, "r");
 std::string string7 = this->getAttrib(node1, "g");
 std::string string8 = this->getAttrib(node1, "b");
 std::string string9 = nullptr;
 if (node1.getAttributes().getNamedItem("codes") != nullptr) {
 string9 = this->getAttrib(node1, "codes");
 }

 std::string string10 = node1.getTextContent();
 this->print(" -----> New Line, Color: " + string6 + ", " + string7 + ", " +
 string8);
 string10 = this->checkForTranslation(string5, string10);
 RadioLine radioLine =
 new RadioLine(string10, Float.parseFloat(string6) / 255.0F,
 Float.parseFloat(string7) / 255.0F,
 Float.parseFloat(string8) / 255.0F, string9);
 radioBroadCast.AddRadioLine(radioLine);
 string10 = string10.trim();
 if (string10.toLowerCase().startsWith("${t:")) {
 string10 = this->checkForCustomAirTimer(string10, radioLine);
 radioLine.setText(string10);
 }
 }
 }

 if (radioScript1 != nullptr) {
 radioScript1.AddBroadcast(radioBroadCast, boolean0);
 }

 return radioBroadCast;
}

std::string checkForTranslation(const std::string &string1,
 const std::string &string2) {
 if (this->currentTranslation != nullptr) {
 std::string string0 = this->currentTranslation.getTranslation(string1);
 if (string0 != nullptr) {
 return string0;
 }

 DebugLog.log(DebugType.Radio, "no translation for: " + string1);
 }

 return string2;
}

void loadExitOptions(Node node1, RadioScript radioScript) {
 for (Node node0 : this->getChildNodes(node1) {
 if (this->nodeNameIs(node0, "ExitOption")) {
 std::string string0 = this->getAttrib(node0, "script");
 std::string string1 = this->getAttrib(node0, "chance");
 std::string string2 = this->getAttrib(node0, "delay");
 int int0 = Integer.parseInt(string1);
 int int1 = Integer.parseInt(string2);
 radioScript.AddExitOption(string0, int0, int1);
 }
 }
}

std::string checkForCustomAirTimer(const std::string &string0,
 RadioLine radioLine) {
 Matcher matcher = pattern.matcher(string0);
 std::string string1 = string0;
 float float0 = -1.0F;
 if (matcher.find()) {
 std::string string2 = matcher.group(1).toLowerCase().trim();

 try {
 float0 = Float.parseFloat(string2);
 radioLine.setAirTime(float0);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 string1 = string0.replaceFirst("\\$\\{t:([^}]+)\\}", "");
 }

 return float0 >= 0.0F ? "[cdt=" + float0 + "]" + string1.trim()
 : string1.trim();
}
}
} // namespace radio
} // namespace zombie
