#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URI.h"
#include "java/security/AccessControlException.h"
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/ZomboidFileSystem/1.h"
#include "zombie/ZomboidFileSystem/IWalkFilesVisitor.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/core/znet/SteamWorkshop.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/gameStates/ChooseGameInfo/PackFile.h"
#include "zombie/gameStates/ChooseGameInfo/TileDef.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/modding/ActiveMods.h"
#include "zombie/modding/ActiveModsFile.h"
#include "zombie/network/CoopMaster.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {


class ZomboidFileSystem {
:
    static const ZomboidFileSystem instance = new ZomboidFileSystem();
   private ArrayList<String> loadList = std::make_unique<ArrayList<>>();
   private Map<String, String> modIdToDir = std::make_unique<HashMap<>>();
   private Map<String, Mod> modDirToMod = std::make_unique<HashMap<>>();
   private ArrayList<String> modFolders;
   private ArrayList<String> modFoldersOrder;
    HashMap<String, String> ActiveFileMap = std::make_unique<HashMap<>>();
   private HashSet<String> AllAbsolutePaths = std::make_unique<HashSet<>>();
    File base;
    URI baseURI;
    File workdir;
    URI workdirURI;
    File localWorkdir;
    File anims;
    URI animsURI;
    File animsX;
    URI animsXURI;
    File animSets;
    URI animSetsURI;
    File actiongroups;
    URI actiongroupsURI;
    File cacheDir;
   private ConcurrentHashMap<String, String> RelativeMap = std::make_unique<ConcurrentHashMap<>>();
    ThreadLocal<Boolean> IgnoreActiveFileMap = ThreadLocal.withInitial(() -> Boolean.FALSE);
   private ConcurrentHashMap<String, URI> CanonicalURIMap = std::make_unique<ConcurrentHashMap<>>();
   private ArrayList<String> mods = std::make_unique<ArrayList<>>();
   private HashSet<String> LoadedPacks = std::make_unique<HashSet<>>();
    FileGuidTable m_fileGuidTable = nullptr;
    bool m_fileGuidTableWatcherActive = false;
    const PredicatedFileWatcher m_modFileWatcher = new PredicatedFileWatcher(this::isModFile, this::onModFileChanged);
   private HashSet<String> m_watchedModFolders = std::make_unique<HashSet<>>();
    long m_modsChangedTime = 0L;

    private ZomboidFileSystem() {
   }

    void init() {
      this.base = new File("./").getAbsoluteFile().getCanonicalFile();
      this.baseURI = this.base.toURI();
      this.workdir = new File(this.base, "media").getAbsoluteFile().getCanonicalFile();
      this.workdirURI = this.workdir.toURI();
      this.localWorkdir = this.base.toPath().relativize(this.workdir.toPath()).toFile();
      this.anims = new File(this.workdir, "anims");
      this.animsURI = this.anims.toURI();
      this.animsX = new File(this.workdir, "anims_X");
      this.animsXURI = this.animsX.toURI();
      this.animSets = new File(this.workdir, "AnimSets");
      this.animSetsURI = this.animSets.toURI();
      this.actiongroups = new File(this.workdir, "actiongroups");
      this.actiongroupsURI = this.actiongroups.toURI();
      this.searchFolders(this.workdir);

      for (int var1 = 0; var1 < this.loadList.size(); var1++) {
    std::string var2 = this.getRelativeFile(this.loadList.get(var1));
    File var3 = new File(this.loadList.get(var1)).getAbsoluteFile();
    std::string var4 = var3.getAbsolutePath();
         if (var3.isDirectory()) {
            var4 = var4 + File.separator;
         }

         this.ActiveFileMap.put(var2.toLowerCase(Locale.ENGLISH), var4);
         this.AllAbsolutePaths.add(var4);
      }

      this.loadList.clear();
   }

    File getCanonicalFile(File var1, std::string_view var2) {
      if (!var1.isDirectory()) {
         return new File(var1, var2);
      } else {
         File[] var3 = var1.listFiles((var1x, var2x) -> var2x.equalsIgnoreCase(var2));
         return var3 != nullptr && var3.length != 0 ? var3[0] : new File(var1, var2);
      }
   }

    std::string getGameModeCacheDir() const {
      if (Core.GameMode == nullptr) {
         Core.GameMode = "Sandbox";
      }

    std::string var1 = this.getSaveDir();
      return var1 + File.separator + Core.GameMode;
   }

    std::string getCurrentSaveDir() const {
      return this.getGameModeCacheDir() + File.separator + Core.GameSaveWorld;
   }

    std::string getFileNameInCurrentSave(std::string_view var1) {
      return this.getCurrentSaveDir() + File.separator + var1;
   }

    std::string getFileNameInCurrentSave(std::string_view var1, std::string_view var2) {
      return this.getFileNameInCurrentSave(var1 + File.separator + var2);
   }

    std::string getFileNameInCurrentSave(std::string_view var1, std::string_view var2, std::string_view var3) {
      return this.getFileNameInCurrentSave(var1 + File.separator + var2 + File.separator + var3);
   }

    File getFileInCurrentSave(std::string_view var1) {
      return new File(this.getFileNameInCurrentSave(var1));
   }

    File getFileInCurrentSave(std::string_view var1, std::string_view var2) {
      return new File(this.getFileNameInCurrentSave(var1, var2));
   }

    File getFileInCurrentSave(std::string_view var1, std::string_view var2, std::string_view var3) {
      return new File(this.getFileNameInCurrentSave(var1, var2, var3));
   }

    std::string getSaveDir() const {
    std::string var1 = this.getCacheDirSub("Saves");
      ensureFolderExists(var1);
    return var1;
   }

    std::string getSaveDirSub(std::string_view var1) {
      return this.getSaveDir() + File.separator + var1;
   }

    std::string getScreenshotDir() const {
    std::string var1 = this.getCacheDirSub("Screenshots");
      ensureFolderExists(var1);
    return var1;
   }

    std::string getScreenshotDirSub(std::string_view var1) {
      return this.getScreenshotDir() + File.separator + var1;
   }

    void setCacheDir(std::string_view var1) {
      var1 = var1.replace("/", File.separator);
      this.cacheDir = new File(var1).getAbsoluteFile();
      ensureFolderExists(this.cacheDir);
   }

    std::string getCacheDir() const {
      if (this.cacheDir == nullptr) {
    std::string var1 = System.getProperty("deployment.user.cachedir");
         if (var1 == nullptr || System.getProperty("os.name").startsWith("Win")) {
            var1 = System.getProperty("user.home");
         }

    std::string var2 = var1 + File.separator + "Zomboid";
         this.setCacheDir(var2);
      }

      return this.cacheDir.getPath();
   }

    std::string getCacheDirSub(std::string_view var1) {
      return this.getCacheDir() + File.separator + var1;
   }

    std::string getMessagingDir() const {
    std::string var1 = this.getCacheDirSub("messaging");
      ensureFolderExists(var1);
    return var1;
   }

    std::string getMessagingDirSub(std::string_view var1) {
      return this.getMessagingDir() + File.separator + var1;
   }

    File getMediaRootFile() const {
      assert this.workdir != nullptr;

      return this.workdir;
   }

    std::string getMediaRootPath() const {
      return this.workdir.getPath();
   }

    File getMediaFile(std::string_view var1) {
      assert this.workdir != nullptr;

      return new File(this.workdir, var1);
   }

    std::string getMediaPath(std::string_view var1) {
      return this.getMediaFile(var1).getPath();
   }

    std::string getAbsoluteWorkDir() const {
      return this.workdir.getPath();
   }

    std::string getLocalWorkDir() const {
      return this.localWorkdir.getPath();
   }

    std::string getLocalWorkDirSub(std::string_view var1) {
      return this.getLocalWorkDir() + File.separator + var1;
   }

    std::string getAnimSetsPath() const {
      return this.animSets.getPath();
   }

    std::string getActionGroupsPath() const {
      return this.actiongroups.getPath();
   }

    static bool ensureFolderExists(std::string_view var0) {
    return ensureFolderExists(new File(var0);
   }

    static bool ensureFolderExists(File var0) {
      return var0.exists() || var0.mkdirs();
   }

    void searchFolders(File var1) {
      if (!GameServer.bServer) {
         Thread.yield();
         Core.getInstance().DoFrameReady();
      }

      if (var1.isDirectory()) {
    std::string var2 = var1.getAbsolutePath().replace("\\", "/").replace("./", "");
         if (var2.contains("media/maps/")) {
            this.loadList.add(var2);
         }

         String[] var3 = var1.list();

         for (int var4 = 0; var4 < var3.length; var4++) {
            this.searchFolders(new File(var1.getAbsolutePath() + File.separator + var3[var4]));
         }
      } else {
         this.loadList.add(var1.getAbsolutePath().replace("\\", "/").replace("./", ""));
      }
   }

    Object[] getAllPathsContaining(String var1) {
    std::vector var2 = new ArrayList();

      for (Entry var4 : this.ActiveFileMap.entrySet()) {
         if (((String)var4.getKey()).contains(var1)) {
            var2.add((String)var4.getValue());
         }
      }

      return var2.toArray();
   }

    Object[] getAllPathsContaining(String var1, String var2) {
    std::vector var3 = new ArrayList();

      for (Entry var5 : this.ActiveFileMap.entrySet()) {
         if (((String)var5.getKey()).contains(var1) && ((String)var5.getKey()).contains(var2)) {
            var3.add((String)var5.getValue());
         }
      }

      return var3.toArray();
   }

    synchronized String getString(String var1) {
      if (this.IgnoreActiveFileMap.get()) {
    return var1;
      } else {
    std::string var2 = var1.toLowerCase(Locale.ENGLISH);
    std::string var3 = this.RelativeMap.get(var2);
         if (var3 != nullptr) {
            var2 = var3;
         } else {
    std::string var6 = this.getRelativeFile(var1);
            var2 = var6.toLowerCase(Locale.ENGLISH);
            this.RelativeMap.put(var2, var2);
         }

    std::string var7 = this.ActiveFileMap.get(var2);
         return var7 != nullptr ? var7 : var1;
      }
   }

    synchronized boolean isKnownFile(String var1) {
      if (this.AllAbsolutePaths.contains(var1)) {
    return true;
      } else {
    std::string var2 = var1.toLowerCase(Locale.ENGLISH);
    std::string var3 = this.RelativeMap.get(var2);
         if (var3 != nullptr) {
            var2 = var3;
         } else {
    std::string var6 = this.getRelativeFile(var1);
            var2 = var6.toLowerCase(Locale.ENGLISH);
            this.RelativeMap.put(var2, var2);
         }

    std::string var7 = this.ActiveFileMap.get(var2);
         return var7 != nullptr;
      }
   }

    std::string getAbsolutePath(std::string_view var1) {
    std::string var2 = var1.toLowerCase(Locale.ENGLISH);
      return this.ActiveFileMap.get(var2);
   }

    void Reset() {
      this.loadList.clear();
      this.ActiveFileMap.clear();
      this.AllAbsolutePaths.clear();
      this.CanonicalURIMap.clear();
      this.modIdToDir.clear();
      this.modDirToMod.clear();
      this.mods.clear();
      this.modFolders = nullptr;
      ActiveMods.Reset();
      if (this.m_fileGuidTable != nullptr) {
         this.m_fileGuidTable.clear();
         this.m_fileGuidTable = nullptr;
      }
   }

    File getCanonicalFile(File var1) {
      try {
         return var1.getCanonicalFile();
      } catch (Exception var3) {
         return var1.getAbsoluteFile();
      }
   }

    File getCanonicalFile(std::string_view var1) {
      return this.getCanonicalFile(new File(var1));
   }

    std::string getCanonicalPath(File var1) {
      try {
         return var1.getCanonicalPath();
      } catch (Exception var3) {
         return var1.getAbsolutePath();
      }
   }

    std::string getCanonicalPath(std::string_view var1) {
      return this.getCanonicalPath(new File(var1));
   }

    URI getCanonicalURI(std::string_view var1) {
    URI var2 = this.CanonicalURIMap.get(var1);
      if (var2 == nullptr) {
         var2 = this.getCanonicalFile(var1).toURI();
         this.CanonicalURIMap.put(var1, var2);
      }

    return var2;
   }

    void resetModFolders() {
      this.modFolders = nullptr;
   }

    void getInstalledItemModsFolders(ArrayList<String> var1) {
      if (SteamUtils.isSteamModeEnabled()) {
         String[] var2 = SteamWorkshop.instance.GetInstalledItemFolders();
         if (var2 != nullptr) {
    for (auto& var6 : var2)    File var7 = new File(var6 + File.separator + "mods");
               if (var7.exists()) {
                  var1.add(var7.getAbsolutePath());
               }
            }
         }
      }
   }

    void getStagedItemModsFolders(ArrayList<String> var1) {
      if (SteamUtils.isSteamModeEnabled()) {
    std::vector var2 = SteamWorkshop.instance.getStageFolders();

         for (int var3 = 0; var3 < var2.size(); var3++) {
    File var4 = new File((String)var2.get(var3) + File.separator + "Contents" + File.separator + "mods");
            if (var4.exists()) {
               var1.add(var4.getAbsolutePath());
            }
         }
      }
   }

    void getAllModFoldersAux(std::string_view var1, List<String> var2) {
    1 var3 = new 1(this);
    Path var4 = FileSystems.getDefault().getPath(var1);
      if (Files.exists(var4)) {
         try (DirectoryStream var5 = Files.newDirectoryStream(var4, var3)) {
    for (auto& var7 : var5)               if (var7.getFileName().toString().toLowerCase() == "examplemod")) {
                  DebugLog.Mod.println("refusing to list " + var7.getFileName());
               } else {
    std::string var8 = var7.toAbsolutePath().toString();
                  if (!this.m_watchedModFolders.contains(var8)) {
                     this.m_watchedModFolders.add(var8);
                     DebugFileWatcher.instance.addDirectory(var8);
    Path var9 = var7.resolve("media");
                     if (Files.exists(var9)) {
                        DebugFileWatcher.instance.addDirectoryRecurse(var9.toAbsolutePath().toString());
                     }
                  }

                  var2.add(var8);
               }
            }
         } catch (Exception var12) {
            var12.printStackTrace();
         }
      }
   }

    void setModFoldersOrder(std::string_view var1) {
      this.modFoldersOrder = new ArrayList<>(Arrays.asList(var1.split(",")));
   }

    void getAllModFolders(List<String> var1) {
      if (this.modFolders == nullptr) {
         this.modFolders = std::make_unique<ArrayList<>>();
         if (this.modFoldersOrder == nullptr) {
            this.setModFoldersOrder("workshop,steam,mods");
         }

    std::vector var2 = new ArrayList();

         for (int var3 = 0; var3 < this.modFoldersOrder.size(); var3++) {
    std::string var4 = this.modFoldersOrder.get(var3);
            if ("workshop" == var4)) {
               this.getStagedItemModsFolders(var2);
            }

            if ("steam" == var4)) {
               this.getInstalledItemModsFolders(var2);
            }

            if ("mods" == var4)) {
               var2.add(Core.getMyDocumentFolder() + File.separator + "mods");
            }
         }

         for (int var5 = 0; var5 < var2.size(); var5++) {
    std::string var6 = (String)var2.get(var5);
            if (!this.m_watchedModFolders.contains(var6)) {
               this.m_watchedModFolders.add(var6);
               DebugFileWatcher.instance.addDirectory(var6);
            }

            this.getAllModFoldersAux(var6, this.modFolders);
         }

         DebugFileWatcher.instance.add(this.m_modFileWatcher);
      }

      var1.clear();
      var1.addAll(this.modFolders);
   }

    ArrayList<Mod> getWorkshopItemMods(long var1) {
    std::vector var3 = new ArrayList();
      if (!SteamUtils.isSteamModeEnabled()) {
    return var3;
      } else {
    std::string var4 = SteamWorkshop.instance.GetItemInstallFolder(var1);
         if (var4 == nullptr) {
    return var3;
         } else {
    File var5 = new File(var4 + File.separator + "mods");
            if (var5.exists() && var5.isDirectory()) {
               File[] var6 = var5.listFiles();

    for (auto& var10 : var6)                  if (var10.isDirectory()) {
    Mod var11 = ChooseGameInfo.readModInfo(var10.getAbsolutePath());
                     if (var11 != nullptr) {
                        var3.add(var11);
                     }
                  }
               }

    return var3;
            } else {
    return var3;
            }
         }
      }
   }

    Mod searchForModInfo(File var1, std::string_view var2, ArrayList<Mod> var3) {
      if (var1.isDirectory()) {
         String[] var4 = var1.list();
         if (var4 == nullptr) {
    return nullptr;
         }

         for (int var5 = 0; var5 < var4.length; var5++) {
    File var6 = new File(var1.getAbsolutePath() + File.separator + var4[var5]);
    Mod var7 = this.searchForModInfo(var6, var2, var3);
            if (var7 != nullptr) {
    return var7;
            }
         }
      } else if (var1.getAbsolutePath().endsWith("mod.info")) {
    Mod var8 = ChooseGameInfo.readModInfo(var1.getAbsoluteFile().getParent());
         if (var8 == nullptr) {
    return nullptr;
         }

         if (!StringUtils.isNullOrWhitespace(var8.getId())) {
            this.modIdToDir.put(var8.getId(), var8.getDir());
            var3.add(var8);
         }

         if (var8.getId() == var2)) {
    return var8;
         }
      }

    return nullptr;
   }

    void loadMod(std::string_view var1) {
      if (this.getModDir(var1) != nullptr) {
         if (CoopMaster.instance != nullptr) {
            CoopMaster.instance.update();
         }

         DebugLog.Mod.println("loading " + var1);
    File var2 = new File(this.getModDir(var1));
    URI var3 = var2.toURI();
         this.loadList.clear();
         this.searchFolders(var2);

         for (int var4 = 0; var4 < this.loadList.size(); var4++) {
    std::string var5 = this.getRelativeFile(var3, this.loadList.get(var4));
            var5 = var5.toLowerCase(Locale.ENGLISH);
            if (this.ActiveFileMap.containsKey(var5) && !var5.endsWith("mod.info") && !var5.endsWith("poster.png")) {
               DebugLog.Mod.println("mod \"" + var1 + "\" overrides " + var5);
            }

    std::string var6 = new File(this.loadList.get(var4)).getAbsolutePath();
            this.ActiveFileMap.put(var5, var6);
            this.AllAbsolutePaths.add(var6);
         }

         this.loadList.clear();
      }
   }

   private ArrayList<String> readLoadedDotTxt() {
    std::string var1 = Core.getMyDocumentFolder() + File.separator + "mods" + File.separator + "loaded.txt";
    File var2 = new File(var1);
      if (!var2.exists()) {
    return nullptr;
      } else {
    std::vector var3 = new ArrayList();

         try (
    FileReader var4 = new FileReader(var1);
    BufferedReader var5 = new BufferedReader(var4);
         ) {
            for (String var6 = var5.readLine(); var6 != nullptr; var6 = var5.readLine()) {
               var6 = var6.trim();
               if (!var6.isEmpty()) {
                  var3.add(var6);
               }
            }
         } catch (Exception var13) {
            ExceptionLogger.logException(var13);
            var3 = nullptr;
         }

         try {
            var2.delete();
         } catch (Exception var8) {
            ExceptionLogger.logException(var8);
         }

    return var3;
      }
   }

    ActiveMods readDefaultModsTxt() {
    ActiveMods var1 = ActiveMods.getById("default");
    std::vector var2 = this.readLoadedDotTxt();
      if (var2 != nullptr) {
         var1.getMods().addAll(var2);
         this.saveModsFile();
      }

      var1.clear();
    std::string var3 = Core.getMyDocumentFolder() + File.separator + "mods" + File.separator + "default.txt";

      try {
    ActiveModsFile var4 = new ActiveModsFile();
         if (var4.read(var3, var1)) {
         }
      } catch (Exception var5) {
         ExceptionLogger.logException(var5);
      }

    return var1;
   }

    void loadMods(std::string_view var1) {
      if (Core.OptionModsEnabled) {
         if (GameClient.bClient) {
    std::vector var6 = new ArrayList();
            this.loadTranslationMods(var6);
            var6.addAll(GameClient.instance.ServerMods);
            this.loadMods(var6);
         } else {
    ActiveMods var2 = ActiveMods.getById(var1);
            if (!"default".equalsIgnoreCase(var1)) {
               ActiveMods.setLoadedMods(var2);
               this.loadMods(var2.getMods());
            } else {
               try {
                  var2 = this.readDefaultModsTxt();
                  var2.checkMissingMods();
                  var2.checkMissingMaps();
                  ActiveMods.setLoadedMods(var2);
                  this.loadMods(var2.getMods());
               } catch (Exception var4) {
                  ExceptionLogger.logException(var4);
               }
            }
         }
      }
   }

    bool isTranslationMod(std::string_view var1) {
    Mod var2 = ChooseGameInfo.getAvailableModDetails(var1);
      if (var2 == nullptr) {
    return false;
      } else {
    bool var3 = false;
    File var4 = new File(var2.getDir());
    URI var5 = var4.toURI();
         this.loadList.clear();
         this.searchFolders(var4);

         for (int var6 = 0; var6 < this.loadList.size(); var6++) {
    std::string var7 = this.getRelativeFile(var5, this.loadList.get(var6));
            if (var7.endsWith(".lua")) {
    return false;
            }

            if (var7.startsWith("media/maps/")) {
    return false;
            }

            if (var7.startsWith("media/scripts/")) {
    return false;
            }

            if (var7.startsWith("media/lua/")) {
               if (!var7.startsWith("media/lua/shared/Translate/")) {
    return false;
               }

               var3 = true;
            }
         }

         this.loadList.clear();
    return var3;
      }
   }

    void loadTranslationMods(ArrayList<String> var1) {
      if (GameClient.bClient) {
    ActiveMods var2 = this.readDefaultModsTxt();
    std::vector var3 = new ArrayList();
         if (this.loadModsAux(var2.getMods(), var3) == nullptr) {
    for (auto& var5 : var3)               if (this.isTranslationMod(var5)) {
                  DebugLog.Mod.println("loading translation mod \"" + var5 + "\"");
                  if (!var1.contains(var5)) {
                     var1.add(var5);
                  }
               }
            }
         }
      }
   }

    std::string loadModAndRequired(std::string_view var1, ArrayList<String> var2) {
      if (var1.isEmpty()) {
    return nullptr;
      } else if (var1.toLowerCase() == "examplemod")) {
         DebugLog.Mod.warn("refusing to load " + var1);
    return nullptr;
      } else if (var2.contains(var1)) {
    return nullptr;
      } else {
    Mod var3 = ChooseGameInfo.getAvailableModDetails(var1);
         if (var3 == nullptr) {
            if (GameServer.bServer) {
               GameServer.ServerMods.remove(var1);
            }

            DebugLog.Mod.warn("required mod \"" + var1 + "\" not found");
    return var1;
         } else {
            if (var3.getRequire() != nullptr) {
    std::string var4 = this.loadModsAux(var3.getRequire(), var2);
               if (var4 != nullptr) {
    return var4;
               }
            }

            var2.add(var1);
    return nullptr;
         }
      }
   }

    std::string loadModsAux(ArrayList<String> var1, ArrayList<String> var2) {
    for (auto& var4 : var1)    std::string var5 = this.loadModAndRequired(var4, var2);
         if (var5 != nullptr) {
    return var5;
         }
      }

    return nullptr;
   }

    void loadMods(ArrayList<String> var1) {
      this.mods.clear();

    for (auto& var3 : var1)         this.loadModAndRequired(var3, this.mods);
      }

      for (String var5 : this.mods) {
         this.loadMod(var5);
      }
   }

    ArrayList<String> getModIDs() {
      return this.mods;
   }

    std::string getModDir(std::string_view var1) {
      return this.modIdToDir.get(var1);
   }

    Mod getModInfoForDir(std::string_view var1) {
    Mod var2 = this.modDirToMod.get(var1);
      if (var2 == nullptr) {
         var2 = new Mod(var1);
         this.modDirToMod.put(var1, var2);
      }

    return var2;
   }

    std::string getRelativeFile(File var1) {
      return this.getRelativeFile(this.baseURI, var1.getAbsolutePath());
   }

    std::string getRelativeFile(std::string_view var1) {
      return this.getRelativeFile(this.baseURI, var1);
   }

    std::string getRelativeFile(URI var1, File var2) {
      return this.getRelativeFile(var1, var2.getAbsolutePath());
   }

    std::string getRelativeFile(URI var1, std::string_view var2) {
    URI var3 = this.getCanonicalURI(var2);
    URI var4 = this.getCanonicalURI(var1.getPath()).relativize(var3);
      if (var4 == var3)) {
    return var2;
      } else {
    std::string var5 = var4.getPath();
         if (var2.endsWith("/") && !var5.endsWith("/")) {
            var5 = var5 + "/";
         }

    return var5;
      }
   }

    std::string getAnimName(URI var1, File var2) {
    std::string var3 = this.getRelativeFile(var1, var2);
    std::string var4 = var3.toLowerCase(Locale.ENGLISH);
    int var5 = var4.lastIndexOf(46);
      if (var5 > -1) {
         var4 = var4.substring(0, var5);
      }

      if (var4.startsWith("anims/")) {
         var4 = var4.substring("anims/".length());
      } else if (var4.startsWith("anims_x/")) {
         var4 = var4.substring("anims_x/".length());
      }

    return var4;
   }

    std::string resolveRelativePath(std::string_view var1, std::string_view var2) {
    Path var3 = Paths.get(var1);
    Path var4 = var3.getParent();
    Path var5 = var4.resolve(var2);
    std::string var6 = var5.toString();
      return this.getRelativeFile(var6);
   }

    void saveModsFile() {
      try {
         ensureFolderExists(Core.getMyDocumentFolder() + File.separator + "mods");
    std::string var1 = Core.getMyDocumentFolder() + File.separator + "mods" + File.separator + "default.txt";
    ActiveModsFile var2 = new ActiveModsFile();
         var2.write(var1, ActiveMods.getById("default"));
      } catch (Exception var3) {
         ExceptionLogger.logException(var3);
      }
   }

    void loadModPackFiles() {
      for (String var2 : this.mods) {
         try {
    Mod var3 = ChooseGameInfo.getAvailableModDetails(var2);
            if (var3 != nullptr) {
               for (PackFile var5 : var3.getPacks()) {
    std::string var6 = this.getRelativeFile("media/texturepacks/" + var5.name + ".pack");
                  var6 = var6.toLowerCase(Locale.ENGLISH);
                  if (!this.ActiveFileMap.containsKey(var6)) {
                     DebugLog.Mod.warn("pack file \"" + var5.name + "\" needed by " + var2 + " not found");
                  } else {
    std::string var7 = instance.getString("media/texturepacks/" + var5.name + ".pack");
                     if (!this.LoadedPacks.contains(var7)) {
                        GameWindow.LoadTexturePack(var5.name, var5.flags, var2);
                        this.LoadedPacks.add(var7);
                     }
                  }
               }
            }
         } catch (Exception var8) {
            ExceptionLogger.logException(var8);
         }
      }

      GameWindow.setTexturePackLookup();
   }

    void loadModTileDefs() {
    std::unordered_set var1 = new HashSet();

      for (String var3 : this.mods) {
         try {
    Mod var4 = ChooseGameInfo.getAvailableModDetails(var3);
            if (var4 != nullptr) {
               for (TileDef var6 : var4.getTileDefs()) {
                  if (var1.contains(var6.fileNumber)) {
                     DebugLog.Mod.error("tiledef fileNumber " + var6.fileNumber + " used by more than one mod");
                  } else {
    std::string var7 = var6.name;
    std::string var8 = this.getRelativeFile("media/" + var7 + ".tiles");
                     var8 = var8.toLowerCase(Locale.ENGLISH);
                     if (!this.ActiveFileMap.containsKey(var8)) {
                        DebugLog.Mod.error("tiledef file \"" + var6.name + "\" needed by " + var3 + " not found");
                     } else {
                        var7 = this.ActiveFileMap.get(var8);
                        IsoWorld.instance.LoadTileDefinitions(IsoSpriteManager.instance, var7, var6.fileNumber);
                        var1.add(var6.fileNumber);
                     }
                  }
               }
            }
         } catch (Exception var9) {
            var9.printStackTrace();
         }
      }
   }

    void loadModTileDefPropertyStrings() {
    std::unordered_set var1 = new HashSet();

      for (String var3 : this.mods) {
         try {
    Mod var4 = ChooseGameInfo.getAvailableModDetails(var3);
            if (var4 != nullptr) {
               for (TileDef var6 : var4.getTileDefs()) {
                  if (var1.contains(var6.fileNumber)) {
                     DebugLog.Mod.error("tiledef fileNumber " + var6.fileNumber + " used by more than one mod");
                  } else {
    std::string var7 = var6.name;
    std::string var8 = this.getRelativeFile("media/" + var7 + ".tiles");
                     var8 = var8.toLowerCase(Locale.ENGLISH);
                     if (!this.ActiveFileMap.containsKey(var8)) {
                        DebugLog.Mod.error("tiledef file \"" + var6.name + "\" needed by " + var3 + " not found");
                     } else {
                        var7 = this.ActiveFileMap.get(var8);
                        IsoWorld.instance.LoadTileDefinitionsPropertyStrings(IsoSpriteManager.instance, var7, var6.fileNumber);
                        var1.add(var6.fileNumber);
                     }
                  }
               }
            }
         } catch (Exception var9) {
            var9.printStackTrace();
         }
      }
   }

    void loadFileGuidTable() {
    File var1 = instance.getMediaFile("fileGuidTable.xml");

      try (FileInputStream var2 = new FileInputStream(var1)) {
    JAXBContext var3 = JAXBContext.newInstance(new Class[]{FileGuidTable.class});
    Unmarshaller var4 = var3.createUnmarshaller();
         this.m_fileGuidTable = (FileGuidTable)var4.unmarshal(var2);
         this.m_fileGuidTable.setModID("game");
      } catch (IOException | JAXBException var16) {
         System.err.println("Failed to load file Guid table.");
         ExceptionLogger.logException(var16);
         return;
      }

      try {
    JAXBContext var18 = JAXBContext.newInstance(new Class[]{FileGuidTable.class});
    Unmarshaller var19 = var18.createUnmarshaller();

         for (String var5 : this.getModIDs()) {
    Mod var6 = ChooseGameInfo.getAvailableModDetails(var5);
            if (var6 != nullptr) {
               try (FileInputStream var7 = new FileInputStream(this.getModDir(var5) + "/media/fileGuidTable.xml")) {
    FileGuidTable var8 = (FileGuidTable)var19.unmarshal(var7);
                  var8.setModID(var5);
                  this.m_fileGuidTable.mergeFrom(var8);
               } catch (FileNotFoundException var13) {
               } catch (Exception var14) {
                  ExceptionLogger.logException(var14);
               }
            }
         }
      } catch (Exception var17) {
         ExceptionLogger.logException(var17);
      }

      this.m_fileGuidTable.loaded();
      if (!this.m_fileGuidTableWatcherActive) {
         DebugFileWatcher.instance.add(new PredicatedFileWatcher("media/fileGuidTable.xml", var1x -> this.loadFileGuidTable()));
         this.m_fileGuidTableWatcherActive = true;
      }
   }

    FileGuidTable getFileGuidTable() const {
      if (this.m_fileGuidTable == nullptr) {
         this.loadFileGuidTable();
      }

      return this.m_fileGuidTable;
   }

    std::string getFilePathFromGuid(std::string_view var1) {
    FileGuidTable var2 = this.getFileGuidTable();
      return var2 != nullptr ? var2.getFilePathFromGuid(var1) : nullptr;
   }

    std::string getGuidFromFilePath(std::string_view var1) {
    FileGuidTable var2 = this.getFileGuidTable();
      return var2 != nullptr ? var2.getGuidFromFilePath(var1) : nullptr;
   }

    std::string resolveFileOrGUID(std::string_view var1) {
    std::string var2 = var1;
    std::string var3 = this.getFilePathFromGuid(var1);
      if (var3 != nullptr) {
         var2 = var3;
      }

    std::string var4 = var2.toLowerCase(Locale.ENGLISH);
      return this.ActiveFileMap.containsKey(var4) ? this.ActiveFileMap.get(var4) : var2;
   }

    bool isValidFilePathGuid(std::string_view var1) {
      return this.getFilePathFromGuid(var1) != nullptr;
   }

    static File[] listAllDirectories(String var0, FileFilter var1, boolean var2) {
    File var3 = new File(var0).getAbsoluteFile();
    return listAllDirectories();
   }

    static File[] listAllDirectories(File var0, FileFilter var1, boolean var2) {
      if (!var0.isDirectory()) {
         return new File[0];
      } else {
    std::vector var3 = new ArrayList();
         listAllDirectoriesInternal(var0, var1, var2, var3);
         return var3.toArray(new File[0]);
      }
   }

    static void listAllDirectoriesInternal(File var0, FileFilter var1, bool var2, ArrayList<File> var3) {
      File[] var4 = var0.listFiles();
      if (var4 != nullptr) {
    for (auto& var8 : var4)            if (!var8.isFile() && var8.isDirectory()) {
               if (var1.accept(var8)) {
                  var3.add(var8);
               }

               if (var2) {
                  listAllFilesInternal(var8, var1, true, var3);
               }
            }
         }
      }
   }

    static File[] listAllFiles(String var0, FileFilter var1, boolean var2) {
    File var3 = new File(var0).getAbsoluteFile();
    return listAllFiles();
   }

    static File[] listAllFiles(File var0, FileFilter var1, boolean var2) {
      if (!var0.isDirectory()) {
         return new File[0];
      } else {
    std::vector var3 = new ArrayList();
         listAllFilesInternal(var0, var1, var2, var3);
         return var3.toArray(new File[0]);
      }
   }

    static void listAllFilesInternal(File var0, FileFilter var1, bool var2, ArrayList<File> var3) {
      File[] var4 = var0.listFiles();
      if (var4 != nullptr) {
    for (auto& var8 : var4)            if (var8.isFile()) {
               if (var1.accept(var8)) {
                  var3.add(var8);
               }
            } else if (var8.isDirectory() && var2) {
               listAllFilesInternal(var8, var1, true, var3);
            }
         }
      }
   }

    void walkGameAndModFiles(std::string_view var1, bool var2, IWalkFilesVisitor var3) {
      this.walkGameAndModFilesInternal(this.base, var1, var2, var3);
    std::vector var4 = this.getModIDs();

      for (int var5 = 0; var5 < var4.size(); var5++) {
    std::string var6 = this.getModDir((String)var4.get(var5));
         if (var6 != nullptr) {
            this.walkGameAndModFilesInternal(new File(var6), var1, var2, var3);
         }
      }
   }

    void walkGameAndModFilesInternal(File var1, std::string_view var2, bool var3, IWalkFilesVisitor var4) {
    File var5 = new File(var1, var2);
      if (var5.isDirectory()) {
         File[] var6 = var5.listFiles();
         if (var6 != nullptr) {
    for (auto& var10 : var6)               var4.visit(var10, var2);
               if (var3 && var10.isDirectory()) {
                  this.walkGameAndModFilesInternal(var1, var2 + "/" + var10.getName(), true, var4);
               }
            }
         }
      }
   }

    String[] resolveAllDirectories(String var1, FileFilter var2, boolean var3) {
    std::vector var4 = new ArrayList();
      this.walkGameAndModFiles(var1, var3, (var2x, var3x) -> {
         if (var2x.isDirectory() && var2.accept(var2x)) {
    std::string var4x = var3x + "/" + var2x.getName();
            if (!var4.contains(var4x)) {
               var4.add(var4x);
            }
         }
      });
      return var4.toArray(new String[0]);
   }

    String[] resolveAllFiles(String var1, FileFilter var2, boolean var3) {
    std::vector var4 = new ArrayList();
      this.walkGameAndModFiles(var1, var3, (var2x, var3x) -> {
         if (var2x.isFile() && var2.accept(var2x)) {
    std::string var4x = var3x + "/" + var2x.getName();
            if (!var4.contains(var4x)) {
               var4.add(var4x);
            }
         }
      });
      return var4.toArray(new String[0]);
   }

    std::string normalizeFolderPath(std::string_view var1) {
      var1 = var1.toLowerCase(Locale.ENGLISH).replace('\\', '/');
      var1 = var1 + "/";
      return var1.replace("///", "/").replace("//", "/");
   }

    static std::string processFilePath(std::string_view var0, char var1) {
      if (var1 != '\\') {
         var0 = var0.replace('\\', var1);
      }

      if (var1 != '/') {
         var0 = var0.replace('/', var1);
      }

    return var0;
   }

    bool tryDeleteFile(std::string_view var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
    return false;
      } else {
         try {
            return this.deleteFile(var1);
         } catch (AccessControlException | IOException var3) {
            ExceptionLogger.logException(var3, String.format("Failed to delete file: \"%s\"", var1), DebugLog.FileIO, LogSeverity.General);
    return false;
         }
      }
   }

    bool deleteFile(std::string_view var1) {
    File var2 = new File(var1).getAbsoluteFile();
      if (!var2.isFile()) {
         throw FileNotFoundException(String.format("File path not found: \"%s\"", var1));
      } else if (var2.delete()) {
         DebugLog.FileIO.debugln("File deleted successfully: \"%s\"", var1);
    return true;
      } else {
         DebugLog.FileIO.debugln("Failed to delete file: \"%s\"", var1);
    return false;
      }
   }

    void update() {
      if (this.m_modsChangedTime != 0L) {
    long var1 = System.currentTimeMillis();
         if (this.m_modsChangedTime <= var1) {
            this.m_modsChangedTime = 0L;
            this.modFolders = nullptr;
            this.modIdToDir.clear();
            this.modDirToMod.clear();
            ChooseGameInfo.Reset();

            for (String var4 : this.getModIDs()) {
               ChooseGameInfo.getModDetails(var4);
            }

            LuaEventManager.triggerEvent("OnModsModified");
         }
      }
   }

    bool isModFile(std::string_view var1) {
      if (this.m_modsChangedTime > 0L) {
    return false;
      } else if (this.modFolders == nullptr) {
    return false;
      } else {
         var1 = var1.toLowerCase().replace('\\', '/');
         if (var1.endsWith("/mods/default.txt")) {
    return false;
         } else {
            for (int var2 = 0; var2 < this.modFolders.size(); var2++) {
    std::string var3 = this.modFolders.get(var2).toLowerCase().replace('\\', '/');
               if (var1.startsWith(var3)) {
    return true;
               }
            }

    return false;
         }
      }
   }

    void onModFileChanged(std::string_view var1) {
      this.m_modsChangedTime = System.currentTimeMillis() + 2000L;
   }

    void cleanMultiplayerSaves() {
      DebugLog.FileIO.println("Start cleaning save fs");
    std::string var1 = this.getSaveDir();
    std::string var2 = var1 + File.separator + "Multiplayer" + File.separator;
    File var3 = new File(var2);
      if (!var3.exists()) {
         var3.mkdir();
      }

      try {
         File[] var4 = var3.listFiles();

    for (auto& var8 : var4)            DebugLog.FileIO.println("Checking " + var8.getAbsoluteFile() + " dir");
            if (var8.isDirectory()) {
    File var9 = new File(var8.toString() + File.separator + "map.bin");
               if (var9.exists()) {
                  DebugLog.FileIO.println("Processing " + var8.getAbsoluteFile() + " dir");

                  try {
    Stream var10 = Files.walk(var8.toPath());
                     var10.forEach(var0 -> {
                        if (var0.getFileName().toString().matches("map_\\d+_\\d+.bin")) {
                           DebugLog.FileIO.println("Delete " + var0.getFileName().toString());
                           var0.toFile().delete();
                        }
                     });
                  } catch (IOException var11) {
                     throw RuntimeException(var11);
                  }
               }
            }
         }
      } catch (RuntimeException var12) {
         var12.printStackTrace();
      }
   }

    void resetDefaultModsForNewRelease(std::string_view var1) {
      ensureFolderExists(this.getCacheDirSub("mods"));
    std::string var2 = this.getCacheDirSub("mods") + File.separator + "reset-mods-" + var1 + ".txt";
    File var3 = new File(var2);
      if (!var3.exists()) {
         try (
    FileWriter var4 = new FileWriter(var3);
    BufferedWriter var5 = new BufferedWriter(var4);
         ) {
    std::string var6 = "If this file does not exist, default.txt will be reset to empty (no mods active).";
            var5.write(var6);
         } catch (Exception var12) {
            ExceptionLogger.logException(var12);
            return;
         }

    ActiveMods var13 = ActiveMods.getById("default");
         var13.clear();
         this.saveModsFile();
      }
   }
}
} // namespace zombie
