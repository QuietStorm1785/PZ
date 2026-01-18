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

class HairStyles {
public:
 name = "male"
 )
 public ArrayList<HairStyle> m_MaleStyles = std::make_unique<ArrayList<>>();
 name = "female"
 )
 public ArrayList<HairStyle> m_FemaleStyles = std::make_unique<ArrayList<>>();
 static HairStyles instance;

 static void init() {
 instance =
 Parse(ZomboidFileSystem.instance.base.getAbsolutePath() +
 File.separator +
 ZomboidFileSystem.processFilePath(
 "media/hairStyles/hairStyles.xml", File.separatorChar);
 if (instance != nullptr) {
 for (String string0 : ZomboidFileSystem.instance.getModIDs()) {
 ChooseGameInfo.Mod mod =
 ChooseGameInfo.getAvailableModDetails(string0);
 if (mod != nullptr) {
 std::string string1 =
 ZomboidFileSystem.instance.getModDir(string0);
 HairStyles hairStyles = Parse(
 string1 + File.separator +
 ZomboidFileSystem.processFilePath(
 "media/hairStyles/hairStyles.xml", File.separatorChar);
 if (hairStyles != nullptr) {
 for (HairStyle hairStyle0 : hairStyles.m_FemaleStyles) {
 HairStyle hairStyle1 =
 instance.FindFemaleStyle(hairStyle0.name);
 if (hairStyle1.empty()) {
 instance.m_FemaleStyles.add(hairStyle0);
 } else {
 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.println(
 "mod \"%s\" overrides hair \"%s\"", string0,
 hairStyle0.name);
 }

 int int0 = instance.m_FemaleStyles.indexOf(hairStyle1);
 instance.m_FemaleStyles.set(int0, hairStyle0);
 }
 }

 for (HairStyle hairStyle2 : hairStyles.m_MaleStyles) {
 HairStyle hairStyle3 =
 instance.FindMaleStyle(hairStyle2.name);
 if (hairStyle3.empty()) {
 instance.m_MaleStyles.add(hairStyle2);
 } else {
 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.println(
 "mod \"%s\" overrides hair \"%s\"", string0,
 hairStyle2.name);
 }

 int int1 = instance.m_MaleStyles.indexOf(hairStyle3);
 instance.m_MaleStyles.set(int1, hairStyle2);
 }
 }
 }
 }
 }
 }
 }

 static void Reset() {
 if (instance != nullptr) {
 instance.m_FemaleStyles.clear();
 instance.m_MaleStyles.clear();
 instance = nullptr;
 }
 }

 static HairStyles Parse(const std::string &filename) {
 try {
 return parse();
 } catch (FileNotFoundException fileNotFoundException) {
 } catch (IOException | JAXBException jAXBException) {
 ExceptionLogger.logException(jAXBException);
 }

 return nullptr;
 }

 static HairStyles parse(const std::string &filename) {
 HairStyles hairStyles;
 try(FileInputStream fileInputStream = new FileInputStream(filename) {
 JAXBContext jAXBContext = JAXBContext.newInstance(HairStyles.class);
 Unmarshaller unmarshaller = jAXBContext.createUnmarshaller();
 hairStyles = (HairStyles)unmarshaller.unmarshal(fileInputStream);
 }

 return hairStyles;
 }

 HairStyle FindMaleStyle(const std::string &name) {
 return this->FindStyle(this->m_MaleStyles, name);
 }

 HairStyle FindFemaleStyle(const std::string &name) {
 return this->FindStyle(this->m_FemaleStyles, name);
 }

 HairStyle FindStyle(ArrayList<HairStyle> arrayList,
 const std::string &string) {
 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 HairStyle hairStyle = (HairStyle)arrayList.get(int0);
 if (hairStyle.name.equalsIgnoreCase(string) {
 return hairStyle;
 }

 if ("" == string) && hairStyle.name.equalsIgnoreCase("bald")) {
 return hairStyle;
 }
 }

 return nullptr;
 }

 std::string getRandomMaleStyle(const std::string &outfitName) {
 return HairOutfitDefinitions.instance.getRandomHaircut(
 outfitName, this->m_MaleStyles);
 }

 std::string getRandomFemaleStyle(const std::string &outfitName) {
 return HairOutfitDefinitions.instance.getRandomHaircut(
 outfitName, this->m_FemaleStyles);
 }

 HairStyle getAlternateForHat(HairStyle style,
 const std::string &category) {
 if ("nohair".equalsIgnoreCase(category) ||
 "nohairnobeard".equalsIgnoreCase(category) {
 return nullptr;
 } else if (this->m_FemaleStyles.contains(style) {
 return this->FindFemaleStyle(style.getAlternate(category);
 } else {
 return this->m_MaleStyles.contains(style)
 ? this->FindMaleStyle(style.getAlternate(category)
 : style;
 }
 }

 public
 ArrayList<HairStyle> getAllMaleStyles() { return this->m_MaleStyles; }

 public
 ArrayList<HairStyle> getAllFemaleStyles() {
 return this->m_FemaleStyles;
 }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
