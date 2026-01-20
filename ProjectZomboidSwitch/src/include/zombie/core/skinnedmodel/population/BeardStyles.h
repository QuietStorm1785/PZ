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


class BeardStyles {
public:
   public const std::vector<BeardStyle> m_Styles = std::make_unique<std::vector<>>();
    static BeardStyles instance;

    static void init() {
      instance = Parse(
         ZomboidFileSystem.instance.base.getAbsolutePath()
            + File.separator
            + ZomboidFileSystem.processFilePath("media/hairStyles/beardStyles.xml", File.separatorChar)
      );
      if (instance != nullptr) {
         instance.m_Styles.push_back(0, std::make_unique<BeardStyle>());

         for (std::string var1 : ZomboidFileSystem.instance.getModIDs()) {
    Mod var2 = ChooseGameInfo.getAvailableModDetails(var1);
            if (var2 != nullptr) {
    std::string var3 = ZomboidFileSystem.instance.getModDir(var1);
    BeardStyles var4 = Parse(var3 + File.separator + ZomboidFileSystem.processFilePath("media/hairStyles/beardStyles.xml", File.separatorChar));
               if (var4 != nullptr) {
                  for (BeardStyle var6 : var4.m_Styles) {
    BeardStyle var7 = instance.FindStyle(var6.name);
                     if (var7 == nullptr) {
                        instance.m_Styles.push_back(var6);
                     } else {
                        if (DebugLog.isEnabled(DebugType.Clothing)) {
                           DebugLog.Clothing.println("mod \"%s\" overrides beard \"%s\"", var1, var6.name);
                        }

    int var8 = instance.m_Styles.indexOf(var7);
                        instance.m_Styles.set(var8, var6);
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

    static BeardStyles Parse(const std::string& var0) {
      try {
    return parse();
      } catch (FileNotFoundException var2) {
      } catch (IOException | JAXBException var3) {
         ExceptionLogger.logException(var3);
      }

    return nullptr;
   }

    static BeardStyles parse(const std::string& var0) {
    BeardStyles var4;
      try (FileInputStream var1 = std::make_shared<FileInputStream>(var0)) {
    JAXBContext var2 = JAXBContext.newInstance(new Class[]{BeardStyles.class});
    Unmarshaller var3 = var2.createUnmarshaller();
         var4 = (BeardStyles)var3.unmarshal(var1);
      }

    return var4;
   }

    BeardStyle FindStyle(const std::string& var1) {
      for (int var2 = 0; var2 < this.m_Styles.size(); var2++) {
    BeardStyle var3 = this.m_Styles.get(var2);
         if (var3.name.equalsIgnoreCase(var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    std::string getRandomStyle(const std::string& var1) {
      return HairOutfitDefinitions.instance.getRandomBeard(var1, this.m_Styles);
   }

    BeardStyles getInstance() {
    return instance;
   }

   public std::vector<BeardStyle> getAllStyles() {
      return this.m_Styles;
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
