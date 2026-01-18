#pragma once
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "javax/xml/bind/annotation/XmlElement.h"
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/HairOutfitDefinitions.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BeardStyles {
public:
 name = "style"
 )
 public ArrayList<BeardStyle> m_Styles = std::make_unique<ArrayList<>>();
 static BeardStyles instance;

 static void init() {
 instance = Parse(
 ZomboidFileSystem.instance.base.getAbsolutePath() +
 File.separator +
 ZomboidFileSystem.processFilePath(
 "media/hairStyles/beardStyles.xml", File.separatorChar);
 if (instance != nullptr) {
 instance.m_Styles.add(0, std::make_unique<BeardStyle>());

 for (String string0 : ZomboidFileSystem.instance.getModIDs()) {
 ChooseGameInfo.Mod mod =
 ChooseGameInfo.getAvailableModDetails(string0);
 if (mod != nullptr) {
 std::string string1 =
 ZomboidFileSystem.instance.getModDir(string0);
 BeardStyles beardStyles =
 Parse(string1 + File.separator +
 ZomboidFileSystem.processFilePath(
 "media/hairStyles/beardStyles.xml",
 File.separatorChar);
 if (beardStyles != nullptr) {
 for (BeardStyle beardStyle0 : beardStyles.m_Styles) {
 BeardStyle beardStyle1 =
 instance.FindStyle(beardStyle0.name);
 if (beardStyle1.empty()) {
 instance.m_Styles.add(beardStyle0);
 } else {
 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.println(
 "mod \"%s\" overrides beard \"%s\"", string0,
 beardStyle0.name);
 }

 int int0 = instance.m_Styles.indexOf(beardStyle1);
 instance.m_Styles.set(int0, beardStyle0);
 }
 }
 }
 }
 }
 }
 }

 static void Reset() {
 if (instance != nullptr) {
 instance.m_Styles.clear();
 instance = nullptr;
 }
 }

 static BeardStyles Parse(const std::string &filename) {
 try {
 return parse();
 } catch (FileNotFoundException fileNotFoundException) {
 } catch (IOException | JAXBException jAXBException) {
 ExceptionLogger.logException(jAXBException);
 }

 return nullptr;
 }

 static BeardStyles parse(const std::string &filename) {
 BeardStyles beardStyles;
 try(FileInputStream fileInputStream = new FileInputStream(filename) {
 JAXBContext jAXBContext =
 JAXBContext.newInstance(BeardStyles.class);
 Unmarshaller unmarshaller = jAXBContext.createUnmarshaller();
 beardStyles = (BeardStyles)unmarshaller.unmarshal(fileInputStream);
 }

 return beardStyles;
 }

 BeardStyle FindStyle(const std::string &name) {
 for (int int0 = 0; int0 < this->m_Styles.size(); int0++) {
 BeardStyle beardStyle = this->m_Styles.get(int0);
 if (beardStyle.name.equalsIgnoreCase(name) {
 return beardStyle;
 }
 }

 return nullptr;
 }

 std::string getRandomStyle(const std::string &outfitName) {
 return HairOutfitDefinitions.instance.getRandomBeard(outfitName,
 this->m_Styles);
 }

 BeardStyles getInstance() { return instance; }

 public
 ArrayList<BeardStyle> getAllStyles() { return this->m_Styles; }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
