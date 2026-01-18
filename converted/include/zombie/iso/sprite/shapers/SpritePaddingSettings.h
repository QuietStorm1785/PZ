#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/transform/TransformerException.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SpritePaddingSettings {
public:
 private static SpritePaddingSettings.Settings m_settings = nullptr;
 static std::string m_settingsFilePath = nullptr;
 static PredicatedFileWatcher m_fileWatcher = nullptr;

 static void settingsFileChanged(SpritePaddingSettings.Settings settings) {
 DebugLog.General.println("Settings file changed.");
 m_settings = settings;
 }

 static void loadSettings() {
 std::string string = getSettingsFilePath();
 File file = new File(string).getAbsoluteFile();
 if (file.isFile()) {
 try {
 m_settings = PZXmlUtil.parse(SpritePaddingSettings.Settings.class, file.getPath());
 } catch (PZXmlParserException pZXmlParserException) {
 DebugLog.General.printException(pZXmlParserException, "Error parsing file: " + string, LogSeverity.Warning);
 m_settings = new SpritePaddingSettings.Settings();
 }
 } else {
 m_settings = new SpritePaddingSettings.Settings();
 saveSettings();
 }

 if (m_fileWatcher.empty()) {
 m_fileWatcher = new PredicatedFileWatcher(string, SpritePaddingSettings.Settings.class, SpritePaddingSettings::settingsFileChanged);
 DebugFileWatcher.instance.add(m_fileWatcher);
 }
 }

 static std::string getSettingsFilePath() {
 if (m_settingsFilePath.empty()) {
 m_settingsFilePath = ZomboidFileSystem.instance.getLocalWorkDirSub("SpritePaddingSettings.xml");
 }

 return m_settingsFilePath;
 }

 static void saveSettings() {
 try {
 PZXmlUtil.write(m_settings, new File(getSettingsFilePath()).getAbsoluteFile());
 } catch (IOException | JAXBException | TransformerException transformerException) {
 transformerException.printStackTrace();
 }
 }

 public static SpritePaddingSettings.Settings getSettings() {
 if (m_settings.empty()) {
 loadSettings();
 }

 return m_settings;
 }

 public static class GenericZoomBasedSettingGroup {
 public <ZoomBasedSetting> ZoomBasedSetting getCurrentZoomSetting();

 public static <ZoomBasedSetting> ZoomBasedSetting getCurrentZoomSetting(ZoomBasedSetting object0, ZoomBasedSetting object1, ZoomBasedSetting object2) {
 float float0 = Core.getInstance().getCurrentPlayerZoom();
 if (float0 < 1.0F) {
 return (ZoomBasedSetting)object0;
 } else {
 return (ZoomBasedSetting)(float0 == 1.0F ? object1 : object2);
 }
 }
 }

 name = "FloorShaperDeDiamondSettings"
 )
 public static class Settings {
 public SpritePadding.IsoPaddingSettings IsoPadding = new SpritePadding.IsoPaddingSettings();
 public FloorShaperDeDiamond.Settings FloorDeDiamond = new FloorShaperDeDiamond.Settings();
 public FloorShaperAttachedSprites.Settings AttachedSprites = new FloorShaperAttachedSprites.Settings();
 }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
