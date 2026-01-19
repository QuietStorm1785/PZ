package zombie.iso.sprite.shapers;

import java.io.File;
import java.io.IOException;
import javax.xml.bind.JAXBException;
import javax.xml.transform.TransformerException;
import zombie.DebugFileWatcher;
import zombie.PredicatedFileWatcher;
import zombie.ZomboidFileSystem;
import zombie.debug.DebugLog;
import zombie.debug.LogSeverity;
import zombie.iso.sprite.shapers.SpritePaddingSettings.Settings;
import zombie.util.PZXmlParserException;
import zombie.util.PZXmlUtil;

public class SpritePaddingSettings {
   private static Settings m_settings = null;
   private static String m_settingsFilePath = null;
   private static PredicatedFileWatcher m_fileWatcher = null;

   public static void settingsFileChanged(Settings var0) {
      DebugLog.General.println("Settings file changed.");
      m_settings = var0;
   }

   private static void loadSettings() {
      String var0 = getSettingsFilePath();
      File var1 = new File(var0).getAbsoluteFile();
      if (var1.isFile()) {
         try {
            m_settings = (Settings)PZXmlUtil.parse(Settings.class, var1.getPath());
         } catch (PZXmlParserException var3) {
            DebugLog.General.printException(var3, "Error parsing file: " + var0, LogSeverity.Warning);
            m_settings = new Settings();
         }
      } else {
         m_settings = new Settings();
         saveSettings();
      }

      if (m_fileWatcher == null) {
         m_fileWatcher = new PredicatedFileWatcher(var0, Settings.class, SpritePaddingSettings::settingsFileChanged);
         DebugFileWatcher.instance.add(m_fileWatcher);
      }
   }

   private static String getSettingsFilePath() {
      if (m_settingsFilePath == null) {
         m_settingsFilePath = ZomboidFileSystem.instance.getLocalWorkDirSub("SpritePaddingSettings.xml");
      }

      return m_settingsFilePath;
   }

   private static void saveSettings() {
      try {
         PZXmlUtil.write(m_settings, new File(getSettingsFilePath()).getAbsoluteFile());
      } catch (IOException | JAXBException | TransformerException var1) {
         var1.printStackTrace();
      }
   }

   public static Settings getSettings() {
      if (m_settings == null) {
         loadSettings();
      }

      return m_settings;
   }
}
