#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URI.h"
#include "java/net/URISyntaxException.h"
#include "org/luaj/kahluafork/compiler/FuncState.h"
#include "org/lwjglx/input/Keyboard.h"
#include "se/krka/kahlua/converter/KahluaConverterManager.h"
#include "se/krka/kahlua/integration/LuaCaller.h"
#include "se/krka/kahlua/integration/LuaReturn.h"
#include "se/krka/kahlua/j2se/J2SEPlatform.h"
#include "se/krka/kahlua/luaj/compiler/LuaCompiler.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "se/krka/kahlua/vm/KahluaThread.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "zombie/Lua/LuaManager/Exposer.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/AttachedItems/AttachedWeaponDefinitions.h"
#include "zombie/characters/HairOutfitDefinitions.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/ZombiesZoneDefinition.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/IndieFileLoader.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/raknet/VoiceManager.h"
#include "zombie/core/skinnedmodel/population/DefaultClothing.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/CoopMaster.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetChecksum.h"
#include "zombie/network/NetChecksum/GroupOfFiles.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/Type.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace Lua {


class LuaManager {
public:
    static KahluaConverterManager converterManager = std::make_shared<KahluaConverterManager>();
    static J2SEPlatform platform = std::make_shared<J2SEPlatform>();
    static KahluaTable env;
    static KahluaThread thread;
    static KahluaThread debugthread;
    static LuaCaller caller = std::make_shared<LuaCaller>(converterManager);
    static LuaCaller debugcaller = std::make_shared<LuaCaller>(converterManager);
    static Exposer exposer;
   public static std::vector<std::string> loaded = std::make_unique<std::vector<>>();
   private static const std::unordered_set<std::string> loading = std::make_unique<std::unordered_set<>>();
   public static std::unordered_map<std::string, Object> loadedReturn = std::make_unique<std::unordered_map<>>();
    static bool checksumDone = false;
   public static std::vector<std::string> loadList = std::make_unique<std::vector<>>();
   static std::vector<std::string> paths = std::make_unique<std::vector<>>();
   private static const std::unordered_map<std::string, Object> luaFunctionMap = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_set<KahluaTable> s_wiping = std::make_unique<std::unordered_set<>>();

    static void outputTable(KahluaTable var0, int var1) {
   }

    static void wipeRecurse(KahluaTable var0) {
      if (!var0.empty()) {
         if (!s_wiping.contains(var0)) {
            s_wiping.push_back(var0);
    KahluaTableIterator var1 = var0.iterator();

            while (var1.advance()) {
    KahluaTable var2 = (KahluaTable)Type.tryCastTo(var1.getValue(), KahluaTable.class);
               if (var2 != nullptr) {
                  wipeRecurse(var2);
               }
            }

            s_wiping.remove(var0);
            var0.wipe();
         }
      }
   }

    static void init() {
      loaded.clear();
      loading.clear();
      loadedReturn.clear();
      paths.clear();
      luaFunctionMap.clear();
      platform = std::make_unique<J2SEPlatform>();
      if (env != nullptr) {
         s_wiping.clear();
         wipeRecurse(env);
      }

      env = platform.newEnvironment();
      converterManager = std::make_unique<KahluaConverterManager>();
      if (thread != nullptr) {
         thread.bReset = true;
      }

      thread = std::make_shared<KahluaThread>(platform, env);
      debugthread = std::make_shared<KahluaThread>(platform, env);
      UIManager.defaultthread = thread;
      caller = std::make_shared<LuaCaller>(converterManager);
      debugcaller = std::make_shared<LuaCaller>(converterManager);
      if (exposer != nullptr) {
         exposer.destroy();
      }

      exposer = std::make_shared<Exposer>(converterManager, platform, env);
      loaded = std::make_unique<std::vector<>>();
      checksumDone = false;
      GameClient.checksum = "";
      GameClient.checksumValid = false;
      KahluaNumberConverter.install(converterManager);
      LuaEventManager.register(platform, env);
      LuaHookManager.register(platform, env);
      if (CoopMaster.instance != nullptr) {
         CoopMaster.instance.register(platform, env);
      }

      if (VoiceManager.instance != nullptr) {
         VoiceManager.instance.LuaRegister(platform, env);
      }

    KahluaTable var0 = env;
      exposer.exposeAll();
      exposer.TypeMap.put("function", LuaClosure.class);
      exposer.TypeMap.put("table", KahluaTable.class);
      outputTable(env, 0);
   }

    static void LoadDir(const std::string& var0) {
   }

    static void LoadDirBase(const std::string& var0) {
      LoadDirBase(var0, false);
   }

    static void LoadDirBase(const std::string& var0, bool var1) {
    std::string var2 = "media/lua/" + var0 + "/";
    File var3 = ZomboidFileSystem.instance.getMediaFile("lua" + File.separator + var0);
      if (!paths.contains(var2)) {
         paths.push_back(var2);
      }

      try {
         searchFolders(ZomboidFileSystem.instance.baseURI, var3);
      } catch (IOException var14) {
         ExceptionLogger.logException(var14);
      }

    std::vector var15 = loadList;
      loadList = std::make_unique<std::vector<>>();
    std::vector var16 = ZomboidFileSystem.instance.getModIDs();

      for (int var4 = 0; var4 < var16.size(); var4++) {
    std::string var5 = ZomboidFileSystem.instance.getModDir((std::string)var16.get(var4));
         if (var5 != nullptr) {
    File var6 = std::make_shared<File>(var5);
    URI var7 = var6.getCanonicalFile().toURI();
    File var8 = ZomboidFileSystem.instance.getCanonicalFile(var6, "media");
    File var9 = ZomboidFileSystem.instance.getCanonicalFile(var8, "lua");
    File var10 = ZomboidFileSystem.instance.getCanonicalFile(var9, var0);
    File var11 = var10;

            try {
               searchFolders(var7, var11);
            } catch (IOException var13) {
               ExceptionLogger.logException(var13);
            }
         }
      }

      Collections.sort(var15);
      Collections.sort(loadList);
      var15.addAll(loadList);
      loadList.clear();
      loadList = var15;
    std::unordered_set var17 = new std::unordered_set();

    for (auto& var19 : loadList)         if (!var17.contains(var19)) {
            var17.push_back(var19);
    std::string var20 = ZomboidFileSystem.instance.getAbsolutePath(var19);
            if (var20 == nullptr) {
               throw IllegalStateException("couldn't find \"" + var19 + "\"");
            }

            if (!var1) {
               RunLua(var20);
            }

            if (!checksumDone && !var19.contains("SandboxVars.lua") && (GameServer.bServer || GameClient.bClient)) {
               NetChecksum.checksummer.addFile(var19, var20);
            }

            if (CoopMaster.instance != nullptr) {
               CoopMaster.instance.update();
            }
         }
      }

      loadList.clear();
   }

    static void initChecksum() {
      if (!checksumDone) {
         if (GameClient.bClient || GameServer.bServer) {
            NetChecksum.checksummer.reset(false);
         }
      }
   }

    static void finishChecksum() {
      if (GameServer.bServer) {
         GameServer.checksum = NetChecksum.checksummer.checksumToString();
         DebugLog.General.println("luaChecksum: " + GameServer.checksum);
      } else {
         if (!GameClient.bClient) {
            return;
         }

         GameClient.checksum = NetChecksum.checksummer.checksumToString();
      }

      GroupOfFiles.finishChecksum();
      checksumDone = true;
   }

    static void LoadDirBase() {
      initChecksum();
      LoadDirBase("shared");
      LoadDirBase("client");
   }

    static void searchFolders(URI var0, File var1) {
      if (var1.isDirectory()) {
         std::string[] var2 = var1.list();

         for (int var3 = 0; var3 < var2.length; var3++) {
            searchFolders(var0, std::make_shared<File>(var1.getCanonicalFile().getAbsolutePath() + File.separator + var2[var3]));
         }
      } else if (var1.getAbsolutePath().toLowerCase().endsWith(".lua")) {
    std::string var4 = ZomboidFileSystem.instance.getRelativeFile(var0, var1.getAbsolutePath());
         var4 = var4.toLowerCase(Locale.ENGLISH);
         loadList.push_back(var4);
      }
   }

    static std::string getLuaCacheDir() {
    std::string var0 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "Lua";
    File var1 = std::make_shared<File>(var0);
      if (!var1.exists()) {
         var1.mkdir();
      }

    return var0;
   }

    static std::string getSandboxCacheDir() {
    std::string var0 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "Sandbox Presets";
    File var1 = std::make_shared<File>(var0);
      if (!var1.exists()) {
         var1.mkdir();
      }

    return var0;
   }

    static void fillContainer(ItemContainer var0, IsoPlayer var1) {
      ItemPickerJava.fillContainer(var0, var1);
   }

    static void updateOverlaySprite(IsoObject var0) {
      ItemPickerJava.updateOverlaySprite(var0);
   }

    static LuaClosure getDotDelimitedClosure(const std::string& var0) {
      std::string[] var1 = var0.split("\\.");
    KahluaTable var2 = env;

      for (int var3 = 0; var3 < var1.length - 1; var3++) {
         var2 = (KahluaTable)env.rawget(var1[var3]);
      }

      return (LuaClosure)var2.rawget(var1[var1.length - 1]);
   }

    static void transferItem(IsoGameCharacter var0, InventoryItem var1, ItemContainer var2, ItemContainer var3) {
    LuaClosure var4 = (LuaClosure)env.rawget("javaTransferItems");
      caller.pcall(thread, var4, new Object[]{var0, var1, var2, var3});
   }

    static void dropItem(InventoryItem var0) {
    LuaClosure var1 = getDotDelimitedClosure("ISInventoryPaneContextMenu.dropItem");
      caller.pcall(thread, var1, var0);
   }

    static IsoGridSquare AdjacentFreeTileFinder(IsoGridSquare var0, IsoPlayer var1) {
    KahluaTable var2 = (KahluaTable)env.rawget("AdjacentFreeTileFinder");
    LuaClosure var3 = (LuaClosure)var2.rawget("Find");
      return (IsoGridSquare)caller.pcall(thread, var3, new Object[]{var0, var1})[1];
   }

    static void* RunLua(const std::string& var0) {
    return RunLua();
   }

    static void* RunLua(const std::string& var0, bool var1) {
    std::string var2 = var0.replace("\\", "/");
      if (loading.contains(var2)) {
         DebugLog.Lua.warn("recursive require(): %s", new Object[]{var2});
    return nullptr;
      } else {
         loading.push_back(var2);

    void* var3;
         try {
            var3 = RunLuaInternal(var0, var1);
         } finally {
            loading.remove(var2);
         }

    return var3;
      }
   }

    static void* RunLuaInternal(const std::string& var0, bool var1) {
      var0 = var0.replace("\\", "/");
      if (loaded.contains(var0)) {
         return loadedReturn.get(var0);
      } else {
         FuncState.currentFile = var0.substr(var0.lastIndexOf(47) + 1);
         FuncState.currentfullFile = var0;
         var0 = ZomboidFileSystem.instance.getString(var0.replace("\\", "/"));
         if (DebugLog.isEnabled(DebugType.Lua)) {
            DebugLog.Lua.println("Loading: " + ZomboidFileSystem.instance.getRelativeFile(var0));
         }

    InputStreamReader var3;
         try {
            var3 = IndieFileLoader.getStreamReader(var0);
         } catch (FileNotFoundException var11) {
            ExceptionLogger.logException(var11);
    return nullptr;
         }

         LuaCompiler.rewriteEvents = var1;

    LuaClosure var4;
         try (BufferedReader var5 = std::make_shared<BufferedReader>(var3)) {
            var4 = LuaCompiler.loadis(var5, var0.substr(var0.lastIndexOf(47) + 1), env);
         } catch (Exception var10) {
            Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, "Error found in LUA file: " + var0, nullptr);
            ExceptionLogger.logException(var10);
            thread.debugException(var10);
    return nullptr;
         }

         luaFunctionMap.clear();
         AttachedWeaponDefinitions.instance.m_dirty = true;
         DefaultClothing.instance.m_dirty = true;
         HairOutfitDefinitions.instance.m_dirty = true;
         ZombiesZoneDefinition.bDirty = true;
    LuaReturn var14 = caller.protectedCall(thread, var4, new Object[0]);
         if (!var14.isSuccess()) {
            Logger.getLogger(IsoWorld.class.getName()).log(Level.SEVERE, var14.getErrorString(), nullptr);
            if (var14.getJavaException() != nullptr) {
               Logger.getLogger(IsoWorld.class.getName()).log(Level.SEVERE, var14.getJavaException(), nullptr);
            }

            Logger.getLogger(IsoWorld.class.getName()).log(Level.SEVERE, var14.getLuaStackTrace(), nullptr);
         }

         loaded.push_back(var0);
    void* var6 = var14.isSuccess() && var14.size() > 0 ? var14.getFirst() : nullptr;
         if (var6 != nullptr) {
            loadedReturn.put(var0, var6);
         } else {
            loadedReturn.remove(var0);
         }

         LuaCompiler.rewriteEvents = false;
    return var6;
      }
   }

    static void* getFunctionObject(const std::string& var0) {
      if (var0 != nullptr && !var0.empty()) {
    void* var1 = luaFunctionMap.get(var0);
         if (var1 != nullptr) {
    return var1;
         } else {
    KahluaTable var2 = env;
            if (var0.contains(".")) {
               std::string[] var3 = var0.split("\\.");

               for (int var4 = 0; var4 < var3.length - 1; var4++) {
    KahluaTable var5 = (KahluaTable)Type.tryCastTo(var2.rawget(var3[var4]), KahluaTable.class);
                  if (var5 == nullptr) {
                     DebugLog.General.error("no such function \"%s\"", new Object[]{var0});
    return nullptr;
                  }

                  var2 = var5;
               }

               var1 = var2.rawget(var3[var3.length - 1]);
            } else {
               var1 = var2.rawget(var0);
            }

            if (!(dynamic_cast<JavaFunction*>(var1) != nullptr) && !(dynamic_cast<LuaClosure*>(var1) != nullptr)) {
               DebugLog.General.error("no such function \"%s\"", new Object[]{var0});
    return nullptr;
            } else {
               luaFunctionMap.put(var0, var1);
    return var1;
            }
         }
      } else {
    return nullptr;
      }
   }

    static void Test() {
   }

    static void* get(void* var0) {
      return env.rawget(var0);
   }

    static void call(const std::string& var0, void* var1) {
      caller.pcall(thread, env.rawget(var0), var1);
   }

    static void exposeKeyboardKeys(KahluaTable var0) {
      if (var0.rawget("Keyboard") instanceof KahluaTable var2) {
         Field[] var3 = Keyboard.class.getFields();

         try {
    for (auto& var7 : var3)               if (Modifier.isStatic(var7.getModifiers())
                  && Modifier.isPublic(var7.getModifiers())
                  && Modifier.isFinal(var7.getModifiers())
                  && var7.getType() == int.class)
                  && var7.getName().startsWith("KEY_")
                  && !var7.getName().endsWith("WIN")) {
                  var2.rawset(var7.getName(), (double)var7.getInt(nullptr));
               }
            }
         } catch (Exception var8) {
         }
      }
   }

    static void exposeLuaCalendar() {
    KahluaTable var0 = (KahluaTable)env.rawget("PZCalendar");
      if (var0 != nullptr) {
         Field[] var1 = Calendar.class.getFields();

         try {
    for (auto& var5 : var1)               if (Modifier.isStatic(var5.getModifiers())
                  && Modifier.isPublic(var5.getModifiers())
                  && Modifier.isFinal(var5.getModifiers())
                  && var5.getType() == int.class)) {
                  var0.rawset(var5.getName(), BoxedStaticValues.toDouble(var5.getInt(nullptr)));
               }
            }
         } catch (Exception var6) {
         }

         env.rawset("Calendar", var0);
      }
   }

    static std::string getHourMinuteJava() {
    std::string var0 = Calendar.getInstance().get(12) + "";
      if (Calendar.getInstance().get(12) < 10) {
         var0 = "0" + var0;
      }

      return Calendar.getInstance().get(11) + ":" + var0;
   }

    static KahluaTable copyTable(KahluaTable var0) {
    return copyTable();
   }

    static KahluaTable copyTable(KahluaTable var0, KahluaTable var1) {
      if (var0 == nullptr) {
         var0 = platform.newTable();
      } else {
         var0.wipe();
      }

      if (var1 != nullptr && !var1.empty()) {
    KahluaTableIterator var2 = var1.iterator();

         while (var2.advance()) {
    void* var3 = var2.getKey();
    void* var4 = var2.getValue();
            if (dynamic_cast<KahluaTable*>(var4) != nullptr) {
               var0.rawset(var3, copyTable(nullptr, (KahluaTable)var4));
            } else {
               var0.rawset(var3, var4);
            }
         }

    return var0;
      } else {
    return var0;
      }
   }
}
} // namespace Lua
} // namespace zombie
