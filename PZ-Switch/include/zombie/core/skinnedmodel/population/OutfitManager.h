#pragma once
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Marshaller.h"
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
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
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class OutfitManager {
public:
public
 ArrayList<Outfit> m_MaleOutfits = std::make_unique<ArrayList<>>();
public
 ArrayList<Outfit> m_FemaleOutfits = std::make_unique<ArrayList<>>();
 static OutfitManager instance;
private
 Hashtable<String, OutfitManager.ClothingItemEntry>
 m_cachedClothingItems = std::make_unique<Hashtable<>>();
private
 ArrayList<IClothingItemListener> m_clothingItemListeners =
 std::make_unique<ArrayList<>>();
private
 TreeMap<String, Outfit> m_femaleOutfitMap =
 new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
private
 TreeMap<String, Outfit> m_maleOutfitMap =
 new TreeMap<>(String.CASE_INSENSITIVE_ORDER);

 static void init() {
 if (instance != nullptr) {
 throw IllegalStateException("OutfitManager Already Initialized.");
 } else {
 instance = tryParse("game", "media/clothing/clothing.xml");
 if (instance != nullptr) {
 instance.loaded();
 }
 }
 }

 static void Reset() {
 if (instance != nullptr) {
 instance.unload();
 instance = nullptr;
 }
 }

 void loaded() {
 for (String string : ZomboidFileSystem.instance.getModIDs()) {
 ChooseGameInfo.Mod mod = ChooseGameInfo.getAvailableModDetails(string);
 if (mod != nullptr) {
 OutfitManager outfitManager0 =
 tryParse(string, "media/clothing/clothing.xml");
 if (outfitManager0 != nullptr) {
 for (Outfit outfit0 : outfitManager0.m_MaleOutfits) {
 Outfit outfit1 = this->FindMaleOutfit(outfit0.m_Name);
 if (outfit1.empty()) {
 this->m_MaleOutfits.add(outfit0);
 } else {
 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.println(
 "mod \"%s\" overrides male outfit \"%s\"", string,
 outfit0.m_Name);
 }

 this->m_MaleOutfits.set(this->m_MaleOutfits.indexOf(outfit1),
 outfit0);
 }

 this->m_maleOutfitMap.put(outfit0.m_Name, outfit0);
 }

 for (Outfit outfit2 : outfitManager0.m_FemaleOutfits) {
 Outfit outfit3 = this->FindFemaleOutfit(outfit2.m_Name);
 if (outfit3.empty()) {
 this->m_FemaleOutfits.add(outfit2);
 } else {
 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.println(
 "mod \"%s\" overrides female outfit \"%s\"", string,
 outfit2.m_Name);
 }

 this->m_FemaleOutfits.set(this->m_FemaleOutfits.indexOf(outfit3),
 outfit2);
 }

 this->m_femaleOutfitMap.put(outfit2.m_Name, outfit2);
 }
 }
 }
 }

 DebugFileWatcher.instance.add(new PredicatedFileWatcher(
 ZomboidFileSystem.instance.getString("media/clothing/clothing.xml"),
 var0->onClothingXmlFileChanged()));
 this->loadAllClothingItems();

 for (Outfit outfit4 : this->m_MaleOutfits) {
 outfit4.m_Immutable = true;

 for (ClothingItemReference clothingItemReference0 : outfit4.m_items) {
 clothingItemReference0.m_Immutable = true;
 }
 }

 for (Outfit outfit5 : this->m_FemaleOutfits) {
 outfit5.m_Immutable = true;

 for (ClothingItemReference clothingItemReference1 : outfit5.m_items) {
 clothingItemReference1.m_Immutable = true;
 }
 }

 Collections.shuffle(this->m_MaleOutfits);
 Collections.shuffle(this->m_FemaleOutfits);
 }

 static void onClothingXmlFileChanged() {
 DebugLog.Clothing.println("OutfitManager.onClothingXmlFileChanged> "
 "Detected change in media/clothing/clothing.xml");
 Reload();
 }

 static void Reload() {
 DebugLog.Clothing.println("Reloading OutfitManager");
 OutfitManager outfitManager = instance;
 instance = tryParse("game", "media/clothing/clothing.xml");
 if (instance != nullptr) {
 instance.loaded();
 }

 if (outfitManager != nullptr && instance != nullptr) {
 instance.onReloaded(outfitManager);
 }
 }

 void onReloaded(OutfitManager outfitManager0) {
 PZArrayUtil.copy(this->m_clothingItemListeners,
 outfitManager0.m_clothingItemListeners);
 outfitManager0.unload();
 this->loadAllClothingItems();
 }

 void unload() {
 for (OutfitManager.ClothingItemEntry clothingItemEntry :
 this->m_cachedClothingItems.values()) {
 DebugFileWatcher.instance.remove(clothingItemEntry.m_fileWatcher);
 }

 this->m_cachedClothingItems.clear();
 this->m_clothingItemListeners.clear();
 }

 void addClothingItemListener(IClothingItemListener iClothingItemListener) {
 if (iClothingItemListener != nullptr) {
 if (!this->m_clothingItemListeners.contains(iClothingItemListener) {
 this->m_clothingItemListeners.add(iClothingItemListener);
 }
 }
 }

 void removeClothingItemListener(IClothingItemListener iClothingItemListener) {
 this->m_clothingItemListeners.remove(iClothingItemListener);
 }

 void invokeClothingItemChangedEvent(const std::string &string) {
 for (IClothingItemListener iClothingItemListener :
 this->m_clothingItemListeners) {
 iClothingItemListener.clothingItemChanged(string);
 }
 }

 Outfit GetRandomOutfit(bool boolean0) {
 Outfit outfit;
 if (boolean0) {
 outfit = PZArrayUtil.pickRandom(this->m_FemaleOutfits);
 } else {
 outfit = PZArrayUtil.pickRandom(this->m_MaleOutfits);
 }

 return outfit;
 }

 Outfit GetRandomNonProfessionalOutfit(bool boolean0) {
 std::string string = "Generic0" + (Rand.Next(5) + 1);
 if (Rand.NextBool(4) {
 if (boolean0) {
 int int0 = Rand.Next(3);
 switch (int0) {
 case 0:
 string = "Mannequin1";
 break;
 case 1:
 string = "Mannequin2";
 break;
 case 2:
 string = "Classy";
 }
 } else {
 int int1 = Rand.Next(3);
 switch (int1) {
 case 0:
 string = "Classy";
 break;
 case 1:
 string = "Tourist";
 break;
 case 2:
 string = "MallSecurity";
 }
 }
 }

 return this->GetSpecificOutfit(boolean0, string);
 }

 Outfit GetSpecificOutfit(bool boolean0, const std::string &string) {
 Outfit outfit;
 if (boolean0) {
 outfit = this->FindFemaleOutfit(string);
 } else {
 outfit = this->FindMaleOutfit(string);
 }

 return outfit;
 }

 static OutfitManager tryParse(const std::string &string0,
 const std::string &string1) {
 try {
 return parse();
 } catch (PZXmlParserException pZXmlParserException) {
 pZXmlParserException.printStackTrace();
 return nullptr;
 }
 }

 static OutfitManager parse(const std::string &string0,
 const std::string &string1) {
 if ("game" == string0) {
 string1 =
 ZomboidFileSystem.instance.base.getAbsolutePath() + File.separator +
 ZomboidFileSystem.processFilePath(string1, File.separatorChar);
 }
 else {
 std::string string2 = ZomboidFileSystem.instance.getModDir(string0);
 string1 = string2 + File.separator +
 ZomboidFileSystem.processFilePath(string1, File.separatorChar);
 }

 if (!new File(string1).exists()) {
 return nullptr;
 } else {
 OutfitManager outfitManager =
 PZXmlUtil.parse(OutfitManager.class, string1);
 if (outfitManager != nullptr) {
 PZArrayUtil.forEach(outfitManager.m_MaleOutfits,
 outfit->outfit.setModID(string0);
 PZArrayUtil.forEach(outfitManager.m_FemaleOutfits,
 outfit->outfit.setModID(string0);
 PZArrayUtil.forEach(
 outfitManager.m_MaleOutfits,
 outfit->outfitManager.m_maleOutfitMap.put(outfit.m_Name, outfit);
 PZArrayUtil.forEach(
 outfitManager.m_FemaleOutfits,
 outfit->outfitManager.m_femaleOutfitMap.put(outfit.m_Name, outfit);
 }

 return outfitManager;
 }
 }

 static void tryWrite(OutfitManager outfitManager, const std::string &string) {
 try {
 write(outfitManager, string);
 } catch (IOException | JAXBException jAXBException) {
 jAXBException.printStackTrace();
 }
 }

 static void write(OutfitManager outfitManager, const std::string &string) {
 try(FileOutputStream fileOutputStream = new FileOutputStream(string) {
 JAXBContext jAXBContext = JAXBContext.newInstance(OutfitManager.class);
 Marshaller marshaller = jAXBContext.createMarshaller();
 marshaller.setProperty("jaxb.formatted.output", Boolean.TRUE);
 marshaller.marshal(outfitManager, fileOutputStream);
 }
 }

 Outfit FindMaleOutfit(const std::string &string) {
 return this->m_maleOutfitMap.get(string);
 }

 Outfit FindFemaleOutfit(const std::string &string) {
 return this->m_femaleOutfitMap.get(string);
 }

 Outfit FindOutfit(ArrayList<Outfit> arrayList, const std::string &string) {
 Outfit outfit0 = nullptr;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 Outfit outfit1 = (Outfit)arrayList.get(int0);
 if (outfit1.m_Name.equalsIgnoreCase(string) {
 outfit0 = outfit1;
 break;
 }
 }

 return outfit0;
 }

 ClothingItem getClothingItem(const std::string &string1) {
 std::string string0 =
 ZomboidFileSystem.instance.getFilePathFromGuid(string1);
 if (string0.empty()) {
 return nullptr;
 } else {
 OutfitManager.ClothingItemEntry clothingItemEntry0 =
 this->m_cachedClothingItems.get(string1);
 if (clothingItemEntry0.empty()) {
 clothingItemEntry0 = new OutfitManager.ClothingItemEntry();
 clothingItemEntry0.m_filePath = string0;
 clothingItemEntry0.m_guid = string1;
 clothingItemEntry0.m_item = nullptr;
 this->m_cachedClothingItems.put(string1, clothingItemEntry0);
 }

 if (clothingItemEntry0.m_item != nullptr) {
 clothingItemEntry0.m_item.m_GUID = string1;
 return clothingItemEntry0.m_item;
 } else {
 try {
 std::string string2 =
 ZomboidFileSystem.instance.resolveFileOrGUID(string0);
 clothingItemEntry0.m_item =
 (ClothingItem)ClothingItemAssetManager.instance.load(
 new AssetPath(string2);
 clothingItemEntry0.m_item.m_Name =
 this->extractClothingItemName(string0);
 clothingItemEntry0.m_item.m_GUID = string1;
 } catch (Exception exception) {
 System.err.println("Failed to load ClothingItem: " + string0);
 ExceptionLogger.logException(exception);
 return nullptr;
 }

 if (clothingItemEntry0.m_fileWatcher.empty()) {
 OutfitManager.ClothingItemEntry clothingItemEntry1 =
 clothingItemEntry0;
 std::string string3 = clothingItemEntry1.m_filePath;
 string3 = ZomboidFileSystem.instance.getString(string3);
 clothingItemEntry0.m_fileWatcher = new PredicatedFileWatcher(
 string3,
 var2x->this->onClothingItemFileChanged(clothingItemEntry1);
 DebugFileWatcher.instance.add(clothingItemEntry0.m_fileWatcher);
 }

 return clothingItemEntry0.m_item;
 }
 }
 }

 std::string extractClothingItemName(const std::string &string1) {
 std::string string0 =
 StringUtils.trimPrefix(string1, "media/clothing/clothingItems/");
 return StringUtils.trimSuffix(string0, ".xml");
 }

 void
 onClothingItemFileChanged(OutfitManager.ClothingItemEntry clothingItemEntry) {
 ClothingItemAssetManager.instance.reload(clothingItemEntry.m_item);
 }

 void onClothingItemStateChanged(ClothingItem clothingItem) {
 if (clothingItem.isReady()) {
 this->invokeClothingItemChangedEvent(clothingItem.m_GUID);
 }
 }

 void loadAllClothingItems() {
 std::vector arrayList = ScriptManager.instance.getAllItems();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 Item item = (Item)arrayList.get(int0);
 if (item.replacePrimaryHand != nullptr) {
 String string0 = ZomboidFileSystem.instance.getGuidFromFilePath(
 "media/clothing/clothingItems/" +
 item.replacePrimaryHand.clothingItemName + ".xml");
 if (string0 != nullptr) {
 item.replacePrimaryHand.clothingItem = this->getClothingItem(string0);
 }
 }

 if (item.replaceSecondHand != nullptr) {
 String string1 = ZomboidFileSystem.instance.getGuidFromFilePath(
 "media/clothing/clothingItems/" +
 item.replaceSecondHand.clothingItemName + ".xml");
 if (string1 != nullptr) {
 item.replaceSecondHand.clothingItem = this->getClothingItem(string1);
 }
 }

 if (!StringUtils.isNullOrWhitespace(item.getClothingItem())) {
 std::string string2 = ZomboidFileSystem.instance.getGuidFromFilePath(
 "media/clothing/clothingItems/" + item.getClothingItem() + ".xml");
 if (string2 != nullptr) {
 ClothingItem clothingItem = this->getClothingItem(string2);
 item.setClothingItemAsset(clothingItem);
 }
 }
 }
 }

 bool isLoadingClothingItems() {
 for (OutfitManager.ClothingItemEntry clothingItemEntry :
 this->m_cachedClothingItems.values()) {
 if (clothingItemEntry.m_item.empty()) {
 return true;
 }
 }

 return false;
 }

 void debugOutfits() {
 this->debugOutfits(this->m_FemaleOutfits);
 this->debugOutfits(this->m_MaleOutfits);
 }

 void debugOutfits(ArrayList<Outfit> arrayList) {
 for (auto &outfit : arrayList)
 this->debugOutfit(outfit);
 }
}

 void debugOutfit(Outfit outfit) {
 std::string string0 = nullptr;

 for (ClothingItemReference clothingItemReference : outfit.m_items) {
 ClothingItem clothingItem =
 this->getClothingItem(clothingItemReference.itemGUID);
 if (clothingItem != nullptr && !clothingItem.empty()) {
 std::string string1 = ScriptManager.instance.getItemTypeForClothingItem(
 clothingItem.m_Name);
 if (string1 != nullptr) {
 Item item = ScriptManager.instance.getItem(string1);
 if (item != nullptr && item.getType() == Item.Type.Container) {
 std::string string2 =
 StringUtils.isNullOrWhitespace(item.getBodyLocation())
 ? item.CanBeEquipped
 : item.getBodyLocation();
 if (string0 != nullptr && string0 == string2) {
 DebugLog.Clothing.warn("outfit \"%s\" has multiple bags",
 outfit.m_Name);
 }

 string0 = string2;
 }
 }
 }
 }
}

private
static class ClothingItemEntry {
 ClothingItem m_item;
 std::string m_guid;
 std::string m_filePath;
 PredicatedFileWatcher m_fileWatcher;
}
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
