#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/transform/TransformerException.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/iso/sprite/shapers/SpritePaddingSettings/Settings.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {


class SpritePaddingSettings {
public:
    static Settings m_settings = nullptr;
    static std::string m_settingsFilePath = nullptr;
    static PredicatedFileWatcher m_fileWatcher = nullptr;

    static void settingsFileChanged(Settings var0) {
      DebugLog.General.println("Settings file changed.");
      m_settings = var0;
   }

    static void loadSettings() {
    std::string var0 = getSettingsFilePath();
    File var1 = std::make_shared<File>(var0).getAbsoluteFile();
      if (var1.isFile()) {
         try {
            m_settings = (Settings)PZXmlUtil.parse(Settings.class, var1.getPath());
         } catch (PZXmlParserException var3) {
            DebugLog.General.printException(var3, "Error parsing file: " + var0, LogSeverity.Warning);
            m_settings = std::make_unique<Settings>();
         }
      } else {
         m_settings = std::make_unique<Settings>();
         saveSettings();
      }

      if (m_fileWatcher == nullptr) {
         m_fileWatcher = std::make_shared<PredicatedFileWatcher>(var0, Settings.class, SpritePaddingSettings::settingsFileChanged);
         DebugFileWatcher.instance.push_back(m_fileWatcher);
      }
   }

    static std::string getSettingsFilePath() {
      if (m_settingsFilePath == nullptr) {
         m_settingsFilePath = ZomboidFileSystem.instance.getLocalWorkDirSub("SpritePaddingSettings.xml");
      }

    return m_settingsFilePath;
   }

    static void saveSettings() {
      try {
         PZXmlUtil.write(m_settings, std::make_shared<File>(getSettingsFilePath()).getAbsoluteFile());
      } catch (IOException | JAXBException | TransformerException var1) {
         var1.printStackTrace();
      }
   }

    static Settings getSettings() {
      if (m_settings == nullptr) {
         loadSettings();
      }

    return m_settings;
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
