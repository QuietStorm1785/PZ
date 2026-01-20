#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/filesystem.hpp>
#include "java/text/SimpleDateFormat.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/backup/ZipBackup/BackupTypes.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/network/CoopSlave.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace core {
namespace backup {


class ZipBackup {
public:
    static const int compressionMethod = 0;
    // Note: ZIP operations now use Boost.Iostreams instead of Apache Commons ParallelScatterZipCreator
    static void* scatterZipCreator; // Placeholder - use Boost.Iostreams for actual implementation
    static long lastBackupTime;

    static void onStartup();
    static void onVersion();
    static void onPeriod();
    static void makeBackupFile(const std::string& var0, BackupTypes var1);
    static void rotateBackupFile(BackupTypes var0);
    static std::string getBackupReadme(const std::string& var0);
    static int getWorldVersion(const std::string& var0);
    static void putTextFile(const std::string& var0, const std::string& var1);
    static std::string getStringFromZip(const std::string& var0);
    static void zipTextFile(const std::string& var0, const std::string& var1);
         var6.setComment(getBackupReadme(var0));
         zipFile("options.ini", "options.ini");
         zipFile("popman-options.ini", "popman-options.ini");
         zipFile("latestSave.ini", "latestSave.ini");
         zipFile("debug-options.ini", "debug-options.ini");
         zipFile("sounds.ini", "sounds.ini");
         zipFile("gamepadBinding.config", "gamepadBinding.config");
         zipDir("mods", "mods");
         zipDir("Lua", "Lua");
         zipDir("db", "db");
         zipDir("Server", "Server");
         /* synchronized - TODO: add std::mutex */ (IsoChunk.WriteLock) {
            zipDir("Saves" + File.separator + "Multiplayer" + File.separator + var0, "Saves" + File.separator + "Multiplayer" + File.separator + var0);

            try {
               scatterZipCreator.writeTo(var6);
               DebugLog.log(scatterZipCreator.getStatisticsMessage());
               var6.close();
               var5.close();
            } catch (IOException var14) {
               var14.printStackTrace();
            }
         }
      } catch (Exception var17) {
         var17.printStackTrace();
         if (var5 != nullptr) {
            try {
               var5.close();
            } catch (IOException var13) {
               var13.printStackTrace();
            }
         }
      }

      DebugLog.log("Backup made in " + (System.currentTimeMillis() - var3) + " ms");
   }

    static void rotateBackupFile(BackupTypes var0) {
    int var1 = ServerOptions.getInstance().BackupsCount.getValue() - 1;
      if (var1 > 0) {
         Path var2 = Paths.get(
            ZomboidFileSystem.instance.getCacheDir() + File.separator + "backups" + File.separator + var0 + File.separator + "backup_" + (var1 + 1) + ".zip"
         );

         try {
            Files.deleteIfExists(var2);
         } catch (IOException var8) {
            var8.printStackTrace();
         }

         for (int var3 = var1; var3 > 0; var3--) {
            Path var4 = Paths.get(
               ZomboidFileSystem.instance.getCacheDir() + File.separator + "backups" + File.separator + var0 + File.separator + "backup_" + var3 + ".zip"
            );
            Path var5 = Paths.get(
               ZomboidFileSystem.instance.getCacheDir() + File.separator + "backups" + File.separator + var0 + File.separator + "backup_" + (var3 + 1) + ".zip"
            );

            try {
               Files.move(var4, var5);
            } catch (Exception var7) {
            }
         }
      }
   }

    static std::string getBackupReadme(const std::string& var0) {
    SimpleDateFormat var1 = std::make_shared<SimpleDateFormat>("yyyy-MM-dd 'at' HH:mm:ss z");
    Date var2 = std::make_shared<Date>(System.currentTimeMillis());
      var1.format(var2);
    int var3 = getWorldVersion(var0);
    std::string var4 = "";
      if (var3 == -2) {
         var4 = "World isn't exist";
      } else if (var3 == -1) {
         var4 = "World version cannot be determined";
      } else {
         var4 = std::string.valueOf(var3);
      }

      return "Backup time: "
         + var1.format(var2)
         + "\nServerName: "
         + var0
         + "\nCurrent server version:"
         + Core.getInstance().getGameVersion()
         + "\nCurrent world version:195\nWorld version in this backup is:"
         + var4;
   }

    static int getWorldVersion(const std::string& var0) {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDir() + File.separator + "Multiplayer" + File.separator + var0 + File.separator + "map_t.bin");
      if (var1.exists()) {
         try {
    uint8_t var15;
            try (
    FileInputStream var2 = std::make_shared<FileInputStream>(var1);
    DataInputStream var3 = std::make_shared<DataInputStream>(var2);
            ) {
    uint8_t var4 = var3.readByte();
    uint8_t var5 = var3.readByte();
    uint8_t var6 = var3.readByte();
    uint8_t var7 = var3.readByte();
               if (var4 == 71 && var5 == 77 && var6 == 84 && var7 == 77) {
                  return var3.readInt();
               }

               var15 = -1;
            }

    return var15;
         } catch (Exception var14) {
            var14.printStackTrace();
         }
      }

      return -2;
   }

    static void putTextFile(const std::string& var0, const std::string& var1) {
      try {
    Path var2 = Paths.get(var0);
         Files.createDirectories(var2.getParent());

         try {
            Files.delete(var2);
         } catch (Exception var4) {
         }

         Files.write(var2, var1.getBytes());
      } catch (Exception var5) {
         var5.printStackTrace();
      }
   }

    static std::string getStringFromZip(const std::string& var0) {
    std::string var1 = nullptr;

      try {
    Path var2 = Paths.get(var0);
         if (Files.exists(var2)) {
    std::vector var3 = Files.readAllLines(var2);
            var1 = (std::string)var3.get(0);
         }
      } catch (Exception var4) {
         var4.printStackTrace();
      }

    return var1;
   }

    static void zipTextFile(const std::string& var0, const std::string& var1) {
    InputStreamSupplier var2 = () -> std::make_shared<ByteArrayInputStream>(var1.getBytes(StandardCharsets.UTF_8));
    ZipArchiveEntry var3 = std::make_shared<ZipArchiveEntry>(var0);
      var3.setMethod(0);
      scatterZipCreator.addArchiveEntry(var3, var2);
   }

    static void zipFile(const std::string& var0, const std::string& var1) {
    Path var2 = Paths.get(ZomboidFileSystem.instance.getCacheDir() + File.separator + var1);
      if (Files.exists(var2)) {
         InputStreamSupplier var3 = () -> {
    InputStream var1x = nullptr;

            try {
               var1x = Files.newInputStream(var2);
            } catch (IOException var3x) {
               var3x.printStackTrace();
            }

    return var1x;
         };
    ZipArchiveEntry var4 = std::make_shared<ZipArchiveEntry>(var0);
         var4.setMethod(0);
         scatterZipCreator.addArchiveEntry(var4, var3);
      }
   }

    static void zipDir(const std::string& var0, const std::string& var1) {
    Path var2 = Paths.get(ZomboidFileSystem.instance.getCacheDir() + File.separator + var1);
      if (Files.exists(var2)) {
         try {
    File var3 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + var1);
            if (var3.isDirectory()) {
    Iterator var4 = Arrays.asList(var3.listFiles()).iterator();
    int var5 = var3.getAbsolutePath().length() + 1;

               while (var4.hasNext()) {
    File var6 = (File)var4.next();
                  if (!var6.isDirectory()) {
    std::string var7 = var6.getAbsolutePath().substr(var5);
                     InputStreamSupplier var8 = () -> {
    InputStream var1x = nullptr;

                        try {
                           var1x = Files.newInputStream(var6.toPath());
                        } catch (IOException var3x) {
                           var3x.printStackTrace();
                        }

    return var1x;
                     };
    ZipArchiveEntry var9 = std::make_shared<ZipArchiveEntry>(var0 + File.separator + var7);
                     var9.setMethod(0);
                     scatterZipCreator.addArchiveEntry(var9, var8);
                  }
               }
            }
         } catch (Exception var10) {
            var10.printStackTrace();
         }
      }
   }
}
} // namespace backup
} // namespace core
} // namespace zombie
