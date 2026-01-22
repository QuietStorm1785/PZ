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
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/skinnedmodel/population/ClothingDecals/CachedDecal.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class ClothingDecals {
public:
   public const std::vector<ClothingDecalGroup> m_Groups = std::make_unique<std::vector<>>();
    static ClothingDecals instance;
   private const std::unordered_map<std::string, CachedDecal> m_cachedDecals = std::make_unique<std::unordered_map<>>();

    static void init() {
      if (instance != nullptr) {
         throw IllegalStateException("ClothingDecals Already Initialized.");
      } else {
         instance = Parse(
            ZomboidFileSystem.instance.base.getAbsolutePath()
               + File.separator
               + ZomboidFileSystem.processFilePath("media/clothing/clothingDecals.xml", File.separatorChar)
         );
         if (instance != nullptr) {
            for (std::string var1 : ZomboidFileSystem.instance.getModIDs()) {
    Mod var2 = ChooseGameInfo.getAvailableModDetails(var1);
               if (var2 != nullptr) {
    std::string var3 = ZomboidFileSystem.instance.getModDir(var1);
                  ClothingDecals var4 = Parse(
                     var3 + File.separator + ZomboidFileSystem.processFilePath("media/clothing/clothingDecals.xml", File.separatorChar)
                  );
                  if (var4 != nullptr) {
                     for (ClothingDecalGroup var6 : var4.m_Groups) {
    ClothingDecalGroup var7 = instance.FindGroup(var6.m_Name);
                        if (var7 == nullptr) {
                           instance.m_Groups.push_back(var6);
                        } else {
                           if (DebugLog.isEnabled(DebugType.Clothing)) {
                              DebugLog.Clothing.println("mod \"%s\" overrides decal group \"%s\"", var1, var6.m_Name);
                           }

    int var8 = instance.m_Groups.indexOf(var7);
                           instance.m_Groups.set(var8, var6);
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

    static ClothingDecals Parse(const std::string& var0) {
      try {
    return parse();
      } catch (FileNotFoundException var2) {
      } catch (JAXBException | IOException var3) {
         ExceptionLogger.logException(var3);
      }

    return nullptr;
   }

    static ClothingDecals parse(const std::string& var0) {
    ClothingDecals var4;
      try (FileInputStream var1 = std::make_shared<FileInputStream>(var0)) {
    JAXBContext var2 = JAXBContext.newInstance(new Class[]{ClothingDecals.class});
    Unmarshaller var3 = var2.createUnmarshaller();
         var4 = (ClothingDecals)var3.unmarshal(var1);
      }

    return var4;
   }

    ClothingDecal getDecal(const std::string& var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
    return nullptr;
      } else {
    CachedDecal var2 = this.m_cachedDecals.get(var1);
         if (var2 == nullptr) {
            var2 = std::make_unique<CachedDecal>();
            this.m_cachedDecals.put(var1, var2);
         }

         if (var2.m_decal != nullptr) {
            return var2.m_decal;
         } else {
    std::string var3 = ZomboidFileSystem.instance.getString("media/clothing/clothingDecals/" + var1 + ".xml");

            try {
               var2.m_decal = (ClothingDecal)PZXmlUtil.parse(ClothingDecal.class, var3);
               var2.m_decal.name = var1;
            } catch (PZXmlParserException var5) {
               System.err.println("Failed to load ClothingDecal: " + var3);
               ExceptionLogger.logException(var5);
    return nullptr;
            }

            return var2.m_decal;
         }
      }
   }

    ClothingDecalGroup FindGroup(const std::string& var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
    return nullptr;
      } else {
         for (int var2 = 0; var2 < this.m_Groups.size(); var2++) {
    ClothingDecalGroup var3 = this.m_Groups.get(var2);
            if (var3.m_Name.equalsIgnoreCase(var1)) {
    return var3;
            }
         }

    return nullptr;
      }
   }

    std::string getRandomDecal(const std::string& var1) {
    ClothingDecalGroup var2 = this.FindGroup(var1);
    return var2 = = nullptr ? nullptr : var2.getRandomDecal();
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
