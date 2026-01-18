#pragma once
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "javax/xml/bind/annotation/XmlElement.h"
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/StringUtils.h"
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

class ClothingDecals {
public:
 name = "group"
 )
 public ArrayList<ClothingDecalGroup> m_Groups = std::make_unique<ArrayList<>>();
 static ClothingDecals instance;
 private
 HashMap<String, ClothingDecals.CachedDecal> m_cachedDecals =
 std::make_unique<HashMap<>>();

 static void init() {
 if (instance != nullptr) {
 throw IllegalStateException(
 "ClothingDecals Already Initialized.");
 } else {
 instance = Parse(
 ZomboidFileSystem.instance.base.getAbsolutePath() +
 File.separator +
 ZomboidFileSystem.processFilePath(
 "media/clothing/clothingDecals.xml", File.separatorChar);
 if (instance != nullptr) {
 for (String string0 : ZomboidFileSystem.instance.getModIDs()) {
 ChooseGameInfo.Mod mod =
 ChooseGameInfo.getAvailableModDetails(string0);
 if (mod != nullptr) {
 std::string string1 =
 ZomboidFileSystem.instance.getModDir(string0);
 ClothingDecals clothingDecals =
 Parse(string1 + File.separator +
 ZomboidFileSystem.processFilePath(
 "media/clothing/clothingDecals.xml",
 File.separatorChar);
 if (clothingDecals != nullptr) {
 for (ClothingDecalGroup clothingDecalGroup0 :
 clothingDecals.m_Groups) {
 ClothingDecalGroup clothingDecalGroup1 =
 instance.FindGroup(clothingDecalGroup0.m_Name);
 if (clothingDecalGroup1.empty()) {
 instance.m_Groups.add(clothingDecalGroup0);
 } else {
 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.println(
 "mod \"%s\" overrides decal group \"%s\"",
 string0, clothingDecalGroup0.m_Name);
 }

 int int0 =
 instance.m_Groups.indexOf(clothingDecalGroup1);
 instance.m_Groups.set(int0, clothingDecalGroup0);
 }
 }
 }
 }
 }
 }
 }
 }

 static void Reset() {
 if (instance != nullptr) {
 instance.m_cachedDecals.clear();
 instance.m_Groups.clear();
 instance = nullptr;
 }
 }

 static ClothingDecals Parse(const std::string &string) {
 try {
 return parse();
 } catch (FileNotFoundException fileNotFoundException) {
 } catch (JAXBException | IOException iOException) {
 ExceptionLogger.logException(iOException);
 }

 return nullptr;
 }

 static ClothingDecals parse(const std::string &string) {
 ClothingDecals clothingDecals;
 try(FileInputStream fileInputStream = new FileInputStream(string) {
 JAXBContext jAXBContext =
 JAXBContext.newInstance(ClothingDecals.class);
 Unmarshaller unmarshaller = jAXBContext.createUnmarshaller();
 clothingDecals =
 (ClothingDecals)unmarshaller.unmarshal(fileInputStream);
 }

 return clothingDecals;
 }

 ClothingDecal getDecal(const std::string &string0) {
 if (StringUtils.isNullOrWhitespace(string0) {
 return nullptr;
 } else {
 ClothingDecals.CachedDecal cachedDecal =
 this->m_cachedDecals.get(string0);
 if (cachedDecal.empty()) {
 cachedDecal = new ClothingDecals.CachedDecal();
 this->m_cachedDecals.put(string0, cachedDecal);
 }

 if (cachedDecal.m_decal != nullptr) {
 return cachedDecal.m_decal;
 } else {
 std::string string1 = ZomboidFileSystem.instance.getString(
 "media/clothing/clothingDecals/" + string0 + ".xml");

 try {
 cachedDecal.m_decal =
 PZXmlUtil.parse(ClothingDecal.class, string1);
 cachedDecal.m_decal.name = string0;
 } catch (PZXmlParserException pZXmlParserException) {
 System.err.println("Failed to load ClothingDecal: " + string1);
 ExceptionLogger.logException(pZXmlParserException);
 return nullptr;
 }

 return cachedDecal.m_decal;
 }
 }
 }

 ClothingDecalGroup FindGroup(const std::string &string) {
 if (StringUtils.isNullOrWhitespace(string) {
 return nullptr;
 } else {
 for (int int0 = 0; int0 < this->m_Groups.size(); int0++) {
 ClothingDecalGroup clothingDecalGroup = this->m_Groups.get(int0);
 if (clothingDecalGroup.m_Name.equalsIgnoreCase(string) {
 return clothingDecalGroup;
 }
 }

 return nullptr;
 }
 }

 std::string getRandomDecal(const std::string &string) {
 ClothingDecalGroup clothingDecalGroup = this->FindGroup(string);
 return clothingDecalGroup = =
 nullptr ? nullptr : clothingDecalGroup.getRandomDecal();
 }

 private
 static class CachedDecal {
 ClothingDecal m_decal;
 }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
