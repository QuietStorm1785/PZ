#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class HairStyles {
public:
   public const std::vector<HairStyle> m_MaleStyles = std::make_unique<std::vector<>>();
   public const std::vector<HairStyle> m_FemaleStyles = std::make_unique<std::vector<>>();
    static HairStyles instance;

    static void init() {
      instance = Parse(
         ZomboidFileSystem.instance.base.getAbsolutePath()
            + File.separator
            + ZomboidFileSystem.processFilePath("media/hairStyles/hairStyles.xml", File.separatorChar)
      );
      if (instance != nullptr) {
         for (std::string var1 : ZomboidFileSystem.instance.getModIDs()) {
    Mod var2 = ChooseGameInfo.getAvailableModDetails(var1);
            if (var2 != nullptr) {
    std::string var3 = ZomboidFileSystem.instance.getModDir(var1);
    HairStyles var4 = Parse(var3 + File.separator + ZomboidFileSystem.processFilePath("media/hairStyles/hairStyles.xml", File.separatorChar));
               if (var4 != nullptr) {
                  for (HairStyle var6 : var4.m_FemaleStyles) {
    HairStyle var7 = instance.FindFemaleStyle(var6.name);
                     if (var7 == nullptr) {
                        instance.m_FemaleStyles.push_back(var6);
                     } else {
                        if (DebugLog.isEnabled(DebugType.Clothing)) {
                           DebugLog.Clothing.println("mod \"%s\" overrides hair \"%s\"", var1, var6.name);
                        }

    int var8 = instance.m_FemaleStyles.indexOf(var7);
                        instance.m_FemaleStyles.set(var8, var6);
                     }
                  }

                  for (HairStyle var10 : var4.m_MaleStyles) {
    HairStyle var11 = instance.FindMaleStyle(var10.name);
                     if (var11 == nullptr) {
                        instance.m_MaleStyles.push_back(var10);
                     } else {
                        if (DebugLog.isEnabled(DebugType.Clothing)) {
                           DebugLog.Clothing.println("mod \"%s\" overrides hair \"%s\"", var1, var10.name);
                        }

    int var12 = instance.m_MaleStyles.indexOf(var11);
                        instance.m_MaleStyles.set(var12, var10);
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

    static HairStyles Parse(const std::string& var0) {
      try {
    return parse();
      } catch (FileNotFoundException var2) {
      } catch (IOException | JAXBException var3) {
         ExceptionLogger.logException(var3);
      }

    return nullptr;
   }

    static HairStyles parse(const std::string& var0) {
    HairStyles var4;
      try (FileInputStream var1 = std::make_shared<FileInputStream>(var0)) {
    JAXBContext var2 = JAXBContext.newInstance(new Class[]{HairStyles.class});
    Unmarshaller var3 = var2.createUnmarshaller();
         var4 = (HairStyles)var3.unmarshal(var1);
      }

    return var4;
   }

    HairStyle FindMaleStyle(const std::string& var1) {
      return this.FindStyle(this.m_MaleStyles, var1);
   }

    HairStyle FindFemaleStyle(const std::string& var1) {
      return this.FindStyle(this.m_FemaleStyles, var1);
   }

    HairStyle FindStyle(std::vector<HairStyle> var1, const std::string& var2) {
      for (int var3 = 0; var3 < var1.size(); var3++) {
    HairStyle var4 = (HairStyle)var1.get(var3);
         if (var4.name.equalsIgnoreCase(var2)) {
    return var4;
         }

         if ("" == var2) && var4.name.equalsIgnoreCase("bald")) {
    return var4;
         }
      }

    return nullptr;
   }

    std::string getRandomMaleStyle(const std::string& var1) {
      return HairOutfitDefinitions.instance.getRandomHaircut(var1, this.m_MaleStyles);
   }

    std::string getRandomFemaleStyle(const std::string& var1) {
      return HairOutfitDefinitions.instance.getRandomHaircut(var1, this.m_FemaleStyles);
   }

    HairStyle getAlternateForHat(HairStyle var1, const std::string& var2) {
      if ("nohair".equalsIgnoreCase(var2) || "nohairnobeard".equalsIgnoreCase(var2)) {
    return nullptr;
      } else if (this.m_FemaleStyles.contains(var1)) {
         return this.FindFemaleStyle(var1.getAlternate(var2));
      } else {
         return this.m_MaleStyles.contains(var1) ? this.FindMaleStyle(var1.getAlternate(var2)) : var1;
      }
   }

   public std::vector<HairStyle> getAllMaleStyles() {
      return this.m_MaleStyles;
   }

   public std::vector<HairStyle> getAllFemaleStyles() {
      return this.m_FemaleStyles;
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
