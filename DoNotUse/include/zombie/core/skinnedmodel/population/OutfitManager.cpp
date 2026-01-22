#pragma once
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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
#include "zombie/core/skinnedmodel/population/OutfitManager/ClothingItemEntry.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class OutfitManager {
public:
   public std::vector<Outfit> m_MaleOutfits = std::make_unique<std::vector<>>();
   public std::vector<Outfit> m_FemaleOutfits = std::make_unique<std::vector<>>();
    static OutfitManager instance;
   private const Hashtable<std::string, ClothingItemEntry> m_cachedClothingItems = std::make_unique<Hashtable<>>();
   private const std::vector<IClothingItemListener> m_clothingItemListeners = std::make_unique<std::vector<>>();
   private const std::map<std::string, Outfit> m_femaleOutfitMap = new std::map<>(std::string.CASE_INSENSITIVE_ORDER);
   private const std::map<std::string, Outfit> m_maleOutfitMap = new std::map<>(std::string.CASE_INSENSITIVE_ORDER);

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
      for (std::string var2 : ZomboidFileSystem.instance.getModIDs()) {
    Mod var3 = ChooseGameInfo.getAvailableModDetails(var2);
         if (var3 != nullptr) {
    OutfitManager var4 = tryParse(var2, "media/clothing/clothing.xml");
            if (var4 != nullptr) {
               for (Outfit var6 : var4.m_MaleOutfits) {
    Outfit var7 = this.FindMaleOutfit(var6.m_Name);
                  if (var7 == nullptr) {
                     this.m_MaleOutfits.push_back(var6);
                  } else {
                     if (DebugLog.isEnabled(DebugType.Clothing)) {
                        DebugLog.Clothing.println("mod \"%s\" overrides male outfit \"%s\"", var2, var6.m_Name);
                     }

                     this.m_MaleOutfits.set(this.m_MaleOutfits.indexOf(var7), var6);
                  }

                  this.m_maleOutfitMap.put(var6.m_Name, var6);
               }

               for (Outfit var17 : var4.m_FemaleOutfits) {
    Outfit var18 = this.FindFemaleOutfit(var17.m_Name);
                  if (var18 == nullptr) {
                     this.m_FemaleOutfits.push_back(var17);
                  } else {
                     if (DebugLog.isEnabled(DebugType.Clothing)) {
                        DebugLog.Clothing.println("mod \"%s\" overrides female outfit \"%s\"", var2, var17.m_Name);
                     }

                     this.m_FemaleOutfits.set(this.m_FemaleOutfits.indexOf(var18), var17);
                  }

                  this.m_femaleOutfitMap.put(var17.m_Name, var17);
               }
            }
         }
      }

      DebugFileWatcher.instance
         .push_back(std::make_shared<PredicatedFileWatcher>(ZomboidFileSystem.instance.getString("media/clothing/clothing.xml"), var0 -> onClothingXmlFileChanged()));
      this.loadAllClothingItems();

      for (Outfit var10 : this.m_MaleOutfits) {
         var10.m_Immutable = true;

         for (ClothingItemReference var14 : var10.m_items) {
            var14.m_Immutable = true;
         }
      }

      for (Outfit var11 : this.m_FemaleOutfits) {
         var11.m_Immutable = true;

         for (ClothingItemReference var15 : var11.m_items) {
            var15.m_Immutable = true;
         }
      }

      Collections.shuffle(this.m_MaleOutfits);
      Collections.shuffle(this.m_FemaleOutfits);
   }

    static void onClothingXmlFileChanged() {
      DebugLog.Clothing.println("OutfitManager.onClothingXmlFileChanged> Detected change in media/clothing/clothing.xml");
      Reload();
   }

    static void Reload() {
      DebugLog.Clothing.println("Reloading OutfitManager");
    OutfitManager var0 = instance;
      instance = tryParse("game", "media/clothing/clothing.xml");
      if (instance != nullptr) {
         instance.loaded();
      }

      if (var0 != nullptr && instance != nullptr) {
         instance.onReloaded(var0);
      }
   }

    void onReloaded(OutfitManager var1) {
      PZArrayUtil.copy(this.m_clothingItemListeners, var1.m_clothingItemListeners);
      var1.unload();
      this.loadAllClothingItems();
   }

    void unload() {
      for (ClothingItemEntry var2 : this.m_cachedClothingItems.values()) {
         DebugFileWatcher.instance.remove(var2.m_fileWatcher);
      }

      this.m_cachedClothingItems.clear();
      this.m_clothingItemListeners.clear();
   }

    void addClothingItemListener(IClothingItemListener var1) {
      if (var1 != nullptr) {
         if (!this.m_clothingItemListeners.contains(var1)) {
            this.m_clothingItemListeners.push_back(var1);
         }
      }
   }

    void removeClothingItemListener(IClothingItemListener var1) {
      this.m_clothingItemListeners.remove(var1);
   }

    void invokeClothingItemChangedEvent(const std::string& var1) {
      for (IClothingItemListener var3 : this.m_clothingItemListeners) {
         var3.clothingItemChanged(var1);
      }
   }

    Outfit GetRandomOutfit(bool var1) {
    Outfit var2;
      if (var1) {
         var2 = (Outfit)PZArrayUtil.pickRandom(this.m_FemaleOutfits);
      } else {
         var2 = (Outfit)PZArrayUtil.pickRandom(this.m_MaleOutfits);
      }

    return var2;
   }

    Outfit GetRandomNonProfessionalOutfit(bool var1) {
    std::string var2 = "Generic0" + (Rand.Next(5) + 1);
      if (Rand.NextBool(4)) {
         if (var1) {
    int var3 = Rand.Next(3);
            switch (var3) {
               case 0:
                  var2 = "Mannequin1";
                  break;
               case 1:
                  var2 = "Mannequin2";
                  break;
               case 2:
                  var2 = "Classy";
            }
         } else {
    int var4 = Rand.Next(3);
            switch (var4) {
               case 0:
                  var2 = "Classy";
                  break;
               case 1:
                  var2 = "Tourist";
                  break;
               case 2:
                  var2 = "MallSecurity";
            }
         }
      }

      return this.GetSpecificOutfit(var1, var2);
   }

    Outfit GetSpecificOutfit(bool var1, const std::string& var2) {
    Outfit var3;
      if (var1) {
         var3 = this.FindFemaleOutfit(var2);
      } else {
         var3 = this.FindMaleOutfit(var2);
      }

    return var3;
   }

    static OutfitManager tryParse(const std::string& var0, const std::string& var1) {
      try {
    return parse();
      } catch (PZXmlParserException var3) {
         var3.printStackTrace();
    return nullptr;
      }
   }

    static OutfitManager parse(const std::string& var0, const std::string& var1) {
      if ("game" == var0)) {
         var1 = ZomboidFileSystem.instance.base.getAbsolutePath() + File.separator + ZomboidFileSystem.processFilePath(var1, File.separatorChar);
      } else {
    std::string var2 = ZomboidFileSystem.instance.getModDir(var0);
         var1 = var2 + File.separator + ZomboidFileSystem.processFilePath(var1, File.separatorChar);
      }

      if (!std::make_shared<File>(var1).exists()) {
    return nullptr;
      } else {
    OutfitManager var4 = (OutfitManager)PZXmlUtil.parse(OutfitManager.class, var1);
         if (var4 != nullptr) {
            PZArrayUtil.forEach(var4.m_MaleOutfits, var1x -> var1x.setModID(var0));
            PZArrayUtil.forEach(var4.m_FemaleOutfits, var1x -> var1x.setModID(var0));
            PZArrayUtil.forEach(var4.m_MaleOutfits, var1x -> var4.m_maleOutfitMap.put(var1x.m_Name, var1x));
            PZArrayUtil.forEach(var4.m_FemaleOutfits, var1x -> var4.m_femaleOutfitMap.put(var1x.m_Name, var1x));
         }

    return var4;
      }
   }

    static void tryWrite(OutfitManager var0, const std::string& var1) {
      try {
         write(var0, var1);
      } catch (IOException | JAXBException var3) {
         var3.printStackTrace();
      }
   }

    static void write(OutfitManager var0, const std::string& var1) {
      try (FileOutputStream var2 = std::make_shared<FileOutputStream>(var1)) {
    JAXBContext var3 = JAXBContext.newInstance(new Class[]{OutfitManager.class});
    Marshaller var4 = var3.createMarshaller();
         var4.setProperty("jaxb.formatted.output", bool.TRUE);
         var4.marshal(var0, var2);
      }
   }

    Outfit FindMaleOutfit(const std::string& var1) {
      return this.m_maleOutfitMap.get(var1);
   }

    Outfit FindFemaleOutfit(const std::string& var1) {
      return this.m_femaleOutfitMap.get(var1);
   }

    Outfit FindOutfit(std::vector<Outfit> var1, const std::string& var2) {
    Outfit var3 = nullptr;

      for (int var4 = 0; var4 < var1.size(); var4++) {
    Outfit var5 = (Outfit)var1.get(var4);
         if (var5.m_Name.equalsIgnoreCase(var2)) {
            var3 = var5;
            break;
         }
      }

    return var3;
   }

    ClothingItem getClothingItem(const std::string& var1) {
    std::string var2 = ZomboidFileSystem.instance.getFilePathFromGuid(var1);
      if (var2 == nullptr) {
    return nullptr;
      } else {
    ClothingItemEntry var3 = this.m_cachedClothingItems.get(var1);
         if (var3 == nullptr) {
            var3 = std::make_unique<ClothingItemEntry>();
            var3.m_filePath = var2;
            var3.m_guid = var1;
            var3.m_item = nullptr;
            this.m_cachedClothingItems.put(var1, var3);
         }

         if (var3.m_item != nullptr) {
            var3.m_item.m_GUID = var1;
            return var3.m_item;
         } else {
            try {
    std::string var4 = ZomboidFileSystem.instance.resolveFileOrGUID(var2);
               var3.m_item = (ClothingItem)ClothingItemAssetManager.instance.load(std::make_shared<AssetPath>(var4));
               var3.m_item.m_Name = this.extractClothingItemName(var2);
               var3.m_item.m_GUID = var1;
            } catch (Exception var6) {
               System.err.println("Failed to load ClothingItem: " + var2);
               ExceptionLogger.logException(var6);
    return nullptr;
            }

            if (var3.m_fileWatcher == nullptr) {
    ClothingItemEntry var7 = var3;
    std::string var5 = var7.m_filePath;
               var5 = ZomboidFileSystem.instance.getString(var5);
               var3.m_fileWatcher = std::make_shared<PredicatedFileWatcher>(var5, var2x -> this.onClothingItemFileChanged(var7));
               DebugFileWatcher.instance.push_back(var3.m_fileWatcher);
            }

            return var3.m_item;
         }
      }
   }

    std::string extractClothingItemName(const std::string& var1) {
    std::string var2 = StringUtils.trimPrefix(var1, "media/clothing/clothingItems/");
      return StringUtils.trimSuffix(var2, ".xml");
   }

    void onClothingItemFileChanged(ClothingItemEntry var1) {
      ClothingItemAssetManager.instance.reload(var1.m_item);
   }

    void onClothingItemStateChanged(ClothingItem var1) {
      if (var1.isReady()) {
         this.invokeClothingItemChangedEvent(var1.m_GUID);
      }
   }

    void loadAllClothingItems() {
    std::vector var1 = ScriptManager.instance.getAllItems();

      for (int var2 = 0; var2 < var1.size(); var2++) {
    Item var3 = (Item)var1.get(var2);
         if (var3.replacePrimaryHand != nullptr) {
    std::string var4 = ZomboidFileSystem.instance.getGuidFromFilePath("media/clothing/clothingItems/" + var3.replacePrimaryHand.clothingItemName + ".xml");
            if (var4 != nullptr) {
               var3.replacePrimaryHand.clothingItem = this.getClothingItem(var4);
            }
         }

         if (var3.replaceSecondHand != nullptr) {
    std::string var6 = ZomboidFileSystem.instance.getGuidFromFilePath("media/clothing/clothingItems/" + var3.replaceSecondHand.clothingItemName + ".xml");
            if (var6 != nullptr) {
               var3.replaceSecondHand.clothingItem = this.getClothingItem(var6);
            }
         }

         if (!StringUtils.isNullOrWhitespace(var3.getClothingItem())) {
    std::string var7 = ZomboidFileSystem.instance.getGuidFromFilePath("media/clothing/clothingItems/" + var3.getClothingItem() + ".xml");
            if (var7 != nullptr) {
    ClothingItem var5 = this.getClothingItem(var7);
               var3.setClothingItemAsset(var5);
            }
         }
      }
   }

    bool isLoadingClothingItems() {
      for (ClothingItemEntry var2 : this.m_cachedClothingItems.values()) {
         if (var2.m_item.empty()) {
    return true;
         }
      }

    return false;
   }

    void debugOutfits() {
      this.debugOutfits(this.m_FemaleOutfits);
      this.debugOutfits(this.m_MaleOutfits);
   }

    void debugOutfits(std::vector<Outfit> var1) {
    for (auto& var3 : var1)         this.debugOutfit(var3);
      }
   }

    void debugOutfit(Outfit var1) {
    std::string var2 = nullptr;

      for (ClothingItemReference var4 : var1.m_items) {
    ClothingItem var5 = this.getClothingItem(var4.itemGUID);
         if (var5 != nullptr && !var5.empty()) {
    std::string var6 = ScriptManager.instance.getItemTypeForClothingItem(var5.m_Name);
            if (var6 != nullptr) {
    Item var7 = ScriptManager.instance.getItem(var6);
               if (var7 != nullptr && var7.getType() == Type.Container) {
    std::string var8 = StringUtils.isNullOrWhitespace(var7.getBodyLocation()) ? var7.CanBeEquipped : var7.getBodyLocation();
                  if (var2 != nullptr && var2 == var8)) {
                     DebugLog.Clothing.warn("outfit \"%s\" has multiple bags", new Object[]{var1.m_Name});
                  }

                  var2 = var8;
               }
            }
         }
      }
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
