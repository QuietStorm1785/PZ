#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/parsers/DocumentBuilder.h"
#include "javax/xml/parsers/DocumentBuilderFactory.h"
#include "javax/xml/parsers/ParserConfigurationException.h"
#include "org/w3c/dom/Document.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/Node.h"
#include "org/w3c/dom/NodeList.h"
#include "org/xml/sax/SAXException.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RadioXmlReader {
public:
 bool printDebug = false;
 private ArrayList<RadioGlobal> globalQueue;
 private ArrayList<RadioChannel> channelQueue;
 private Map<String, ArrayList<RadioBroadCast>> advertQue;
 const std::string charsNormal = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
 const std::string charsEncrypt = "UVWKLMABCDEFGXYZHIJOPQRSTNuvwklmabcdefgxyzhijopqrstn";
 std::string radioVersion = "1.0";
 float version = 1.0F;
 float formatVersion = 1.0F;
 private Map<String, String> radioFileSettings = std::make_unique<HashMap<>>();

 public RadioXmlReader() {
 this(false);
 }

 public RadioXmlReader(bool boolean0) {
 this->printDebug = boolean0;
 }

 static RadioData ReadFileHeader(const std::string& var0) {
 new RadioXmlReader();
 return nullptr;
 }

 void readfileheader(const std::string& string) {
 File file = new File(string);
 DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
 DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
 Document document = documentBuilder.parse(file);
 document.getDocumentElement().normalize();
 NodeList nodeList = document.getElementsByTagName("RadioData");
 if (nodeList.getLength() > 0) {
 Node node0 = nodeList.item(0);
 Node node1 = nullptr;

 for (Node node2 : this->getChildNodes(node0) {
 if (this->nodeNameIs(node2, "RootInfo")) {
 node1 = node2;
 break;
 }
 }

 this->loadRootInfo(node1);
 }
 }

 static bool LoadFile(const std::string& string) {
 RadioXmlReader radioXmlReader = new RadioXmlReader(ZomboidRadio.DEBUG_XML);

 try {
 radioXmlReader.start(string);
 } catch (Exception exception) {
 DebugLog.log(DebugType.Radio, "Error loading radio system: " + exception.getMessage());
 exception.printStackTrace();
 bool boolean0 = false;
 } finally {
 DebugLog.log(DebugType.Radio, "RadioSystem online.");
 return true;
 }
 }

 public static ArrayList<String> LoadTranslatorNames(String string) {
 std::vector arrayList0 = new ArrayList();
 RadioXmlReader radioXmlReader = new RadioXmlReader(ZomboidRadio.DEBUG_XML);

 try {
 std::vector arrayList1 = radioXmlReader.readTranslatorNames(string);
 arrayList0 = arrayList1;
 } catch (Exception exception) {
 DebugLog.log(DebugType.Radio, "Error reading translator names: " + exception.getMessage());
 exception.printStackTrace();
 } finally {
 DebugLog.log(DebugType.Radio, "Returning translator names.");
 return arrayList0;
 }
 }

 void print(const std::string& string) {
 if (this->printDebug) {
 DebugLog.log(DebugType.Radio, string);
 }
 }

 private ArrayList<Node> getChildNodes(Node node0) {
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

 bool nodeNameIs(Node node, const std::string& string) {
 return node.getNodeName() == string);
 }

 std::string getAttrib(Node node, const std::string& string, bool boolean0) {
 return this->getAttrib(node, string, boolean0, false);
 }

 std::string getAttrib(Node node, const std::string& string) {
 return this->getAttrib(node, string, true, false).trim();
 }

 std::string getAttrib(Node node, const std::string& string1, bool boolean0, bool boolean1) {
 std::string string0 = node.getAttributes().getNamedItem(string1).getTextContent();
 if (boolean0) {
 string0 = string0.trim();
 }

 if (boolean1) {
 string0 = string0.toLowerCase();
 }

 return string0;
 }

 RadioGlobal getGlobalFromQueue(const std::string& string) {
 for (RadioGlobal radioGlobal : this->globalQueue) {
 if (radioGlobal != nullptr && radioGlobal.getName() == string) {
 return radioGlobal;
 }
 }

 return nullptr;
 }

 RadioGlobal createGlobal(const std::string& string0, const std::string& string1) {
 return this->createGlobal("", string0, string1);
 }

 RadioGlobal createGlobal(const std::string& string2, const std::string& string1, const std::string& string0) {
 if (string2 != nullptr && string1 != nullptr && string0 != nullptr) {
 RadioGlobalType radioGlobalType = RadioGlobalType.valueOf(string1.trim());
 switch (radioGlobalType) {
 case String:
 return new RadioGlobalString(string2, string0);
 case Integer:
 return new RadioGlobalInt(string2, Integer.parseInt(string0.trim()));
 case Float:
 return new RadioGlobalFloat(string2, Float.parseFloat(string0.trim()));
 case Boolean:
 return new RadioGlobalBool(string2, Boolean.parseBoolean(string0.trim().toLowerCase()));
 default:
 return nullptr;
 }
 } else {
 return nullptr;
 }
 }

 private ArrayList<String> readTranslatorNames(String string0) throws ParserConfigurationException, IOException, SAXException {
 File file = new File(string0);
 DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
 DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
 Document document = documentBuilder.parse(file);
 document.getDocumentElement().normalize();
 std::vector arrayList = new ArrayList();
 NodeList nodeList = document.getElementsByTagName("TranslationData");
 if (nodeList.getLength() > 0) {
 Node node0 = nodeList.item(0);

 label37:
 for (Node node1 : this->getChildNodes(node0) {
 if (this->nodeNameIs(node1, "RootInfo")) {
 for (Node node2 : this->getChildNodes(node1) {
 if (this->nodeNameIs(node2, "Translators")) {
 for (Node node3 : this->getChildNodes(node2) {
 std::string string1 = this->getAttrib(node3, "name", true, false);
 if (string1 != nullptr) {
 arrayList.add(string1);
 }
 }
 break label37;
 }
 }
 break;
 }
 }
 }

 return arrayList;
 }

 void start(const std::string& string) {
 File file = new File(string);
 this->print("RadioDataFile: " + file.getAbsolutePath());
 DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
 DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
 Document document = documentBuilder.parse(file);
 document.getDocumentElement().normalize();
 this->globalQueue = std::make_unique<ArrayList<>>();
 this->channelQueue = std::make_unique<ArrayList<>>();
 this->advertQue = std::make_unique<HashMap<>>();
 NodeList nodeList = document.getElementsByTagName("RadioData");
 if (nodeList.getLength() > 0) {
 Node node0 = nodeList.item(0);
 Node node1 = nullptr;

 for (Node node2 : this->getChildNodes(node0) {
 if (this->nodeNameIs(node2, "RootInfo")) {
 node1 = node2;
 break;
 }
 }

 this->loadRootInfo(node1);

 for (Node node3 : this->getChildNodes(node0) {
 if (this->nodeNameIs(node3, "Globals")) {
 this->loadGlobals(node3);
 } else if (this->nodeNameIs(node3, "Adverts")) {
 this->loadAdverts(node3);
 } else if (this->nodeNameIs(node3, "Channels")) {
 this->loadChannels(node3);
 }
 }
 }

 RadioGlobalsManager radioGlobalsManager = RadioGlobalsManager.getInstance();

 for (RadioGlobal radioGlobal : this->globalQueue) {
 radioGlobalsManager.addGlobal(radioGlobal.getName(), radioGlobal);
 }

 RadioScriptManager radioScriptManager = RadioScriptManager.getInstance();

 for (RadioChannel radioChannel : this->channelQueue) {
 radioScriptManager.AddChannel(radioChannel, false);
 }
 }

 void loadRootInfo(Node node0) {
 this->print(">>> Loading root info...");
 if (node0.empty()) {
 this->print(" -> root info not found, default version = " + this->radioVersion);
 this->radioFileSettings.put("Version", this->radioVersion);
 } else {
 this->print(" -> Reading RootInfo");

 for (Node node1 : this->getChildNodes(node0) {
 std::string string0 = node1.getNodeName();
 std::string string1 = node1.getTextContent();
 if (string0 != nullptr && string1 != nullptr) {
 this->print(" -> " + string0 + " = " + string1);
 this->radioFileSettings.put(string0, string1);
 if (string0 == "Version")) {
 this->radioVersion = string1;
 this->version = Float.parseFloat(this->radioVersion);
 }
 }
 }
 }
 }

 void loadGlobals(Node node1) {
 this->print(">>> Loading globals...");

 for (Node node0 : this->getChildNodes(node1) {
 if (this->nodeNameIs(node0, "GlobalEntry")) {
 std::string string0 = this->getAttrib(node0, "name");
 std::string string1 = this->getAttrib(node0, "type");
 std::string string2 = node0.getTextContent();
 this->print(" -> Found global, name: " + string0 + ", type: " + string1 + ", value: " + string2);
 RadioGlobal radioGlobal = this->createGlobal(string0, string1, string2);
 if (radioGlobal != nullptr) {
 this->globalQueue.add(radioGlobal);
 } else {
 this->print(" -> Error adding Global, name: " + string0 + ", type: " + string1 + ", value: " + string2);
 }
 }
 }
 }

 void loadAdverts(Node node1) {
 this->print(">>> Loading adverts...");

 for (Node node0 : this->getChildNodes(node1) {
 if (this->nodeNameIs(node0, "AdvertCategory")) {
 std::string string = this->getAttrib(node0, "name");
 if (!this->advertQue.containsKey(string) {
 this->advertQue.put(string, std::make_unique<ArrayList<>>());
 }

 this->print(" -> Found category: " + string);

 for (Node node2 : this->getChildNodes(node0) {
 RadioBroadCast radioBroadCast = this->loadBroadcast(node2, nullptr);
 this->advertQue.get(string).add(radioBroadCast);
 }
 }
 }
 }

 void loadChannels(Node node1) {
 this->print(">>> Loading channels...");

 for (Node node0 : this->getChildNodes(node1) {
 if (this->nodeNameIs(node0, "ChannelEntry")) {
 std::string string0 = this->getAttrib(node0, "name");
 std::string string1 = this->getAttrib(node0, "cat");
 std::string string2 = this->getAttrib(node0, "freq");
 std::string string3 = this->getAttrib(node0, "startscript");
 this->print(" -> Found channel: " + string0 + ", on freq: " + string2 + " , category: " + string1 + ", startscript: " + string3);
 RadioChannel radioChannel = new RadioChannel(string0, Integer.parseInt(string2), ChannelCategory.valueOf(string1);
 this->loadScripts(node0, radioChannel);
 radioChannel.setActiveScript(string3, 0);
 this->channelQueue.add(radioChannel);
 }
 }
 }

 void loadScripts(Node node1, RadioChannel radioChannel) {
 this->print(" --> Loading scripts...");

 for (Node node0 : this->getChildNodes(node1) {
 if (this->nodeNameIs(node0, "ScriptEntry")) {
 std::string string0 = this->getAttrib(node0, "name");
 std::string string1 = this->getAttrib(node0, "loopmin");
 std::string string2 = this->getAttrib(node0, "loopmin");
 this->print(" ---> Found script: " + string0);
 RadioScript radioScript = new RadioScript(string0, Integer.parseInt(string1), Integer.parseInt(string2);

 for (Node node2 : this->getChildNodes(node0) {
 if (this->nodeNameIs(node2, "BroadcastEntry")) {
 this->loadBroadcast(node2, radioScript);
 } else if (this->nodeNameIs(node2, "ExitOptions")) {
 this->loadExitOptions(node2, radioScript);
 }
 }

 radioChannel.AddRadioScript(radioScript);
 }
 }
 }

 RadioBroadCast loadBroadcast(Node node0, RadioScript radioScript) {
 std::string string0 = this->getAttrib(node0, "ID");
 std::string string1 = this->getAttrib(node0, "timestamp");
 std::string string2 = this->getAttrib(node0, "endstamp");
 this->print(" ----> BroadCast, Timestamp: " + string1 + ", endstamp: " + string2);
 int int0 = Integer.parseInt(string1);
 int int1 = Integer.parseInt(string2);
 std::string string3 = this->getAttrib(node0, "preCat");
 int int2 = Integer.parseInt(this->getAttrib(node0, "preChance"));
 std::string string4 = this->getAttrib(node0, "postCat");
 int int3 = Integer.parseInt(this->getAttrib(node0, "postChance"));
 RadioBroadCast radioBroadCast = new RadioBroadCast(string0, int0, int1);
 if (!string3 == "none") && this->advertQue.containsKey(string3) {
 int int4 = Rand.Next(101);
 int int5 = this->advertQue.get(string3).size();
 if (int5 > 0 && int4 <= int2) {
 radioBroadCast.setPreSegment(this->advertQue.get(string3).get(Rand.Next(int5));
 }
 }

 if (!string4 == "none") && this->advertQue.containsKey(string4) {
 int int6 = Rand.Next(101);
 int int7 = this->advertQue.get(string4).size();
 if (int7 > 0 && int6 <= int3) {
 radioBroadCast.setPostSegment(this->advertQue.get(string4).get(Rand.Next(int7));
 }
 }

 for (Node node1 : this->getChildNodes(node0) {
 if (this->nodeNameIs(node1, "LineEntry")) {
 std::string string5 = this->getAttrib(node1, "r");
 std::string string6 = this->getAttrib(node1, "g");
 std::string string7 = this->getAttrib(node1, "b");
 std::string string8 = nullptr;
 std::string string9 = node1.getTextContent();
 this->print(" -----> New Line, Color: " + string5 + ", " + string6 + ", " + string7);

 for (Node node2 : this->getChildNodes(node1) {
 if (this->nodeNameIs(node2, "LineEffects")) {
 string8 = "";

 for (Node node3 : this->getChildNodes(node1) {
 if (this->nodeNameIs(node3, "Effect")) {
 std::string string10 = this->getAttrib(node3, "tag");
 std::string string11 = this->getAttrib(node3, "value");
 string8 = string8 + string10 + "=" + string11 + ",";
 }
 }
 break;
 }
 }

 string9 = this->simpleDecrypt(string9);
 RadioLine radioLine = new RadioLine(
 string9, Float.parseFloat(string5) / 255.0F, Float.parseFloat(string6) / 255.0F, Float.parseFloat(string7) / 255.0F, string8
 );
 radioBroadCast.AddRadioLine(radioLine);
 }
 }

 if (radioScript != nullptr) {
 radioScript.AddBroadcast(radioBroadCast);
 }

 return radioBroadCast;
 }

 std::string simpleDecrypt(const std::string& string1) {
 std::string string0 = "";

 for (int int0 = 0; int0 < string1.length(); int0++) {
 char char0 = string1.charAt(int0);
 if ("UVWKLMABCDEFGXYZHIJOPQRSTNuvwklmabcdefgxyzhijopqrstn".indexOf(char0) != -1) {
 string0 = string0
 + "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz".charAt("UVWKLMABCDEFGXYZHIJOPQRSTNuvwklmabcdefgxyzhijopqrstn".indexOf(char0);
 } else {
 string0 = string0 + char0;
 }
 }

 return string0;
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
}
} // namespace radio
} // namespace zombie
