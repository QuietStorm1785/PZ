package zombie.Lua;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.luaj.kahluafork.compiler.FuncState;
import org.lwjglx.input.Keyboard;
import se.krka.kahlua.converter.KahluaConverterManager;
import se.krka.kahlua.integration.LuaCaller;
import se.krka.kahlua.integration.LuaReturn;
import se.krka.kahlua.j2se.J2SEPlatform;
import se.krka.kahlua.luaj.compiler.LuaCompiler;
import se.krka.kahlua.vm.JavaFunction;
import se.krka.kahlua.vm.KahluaTable;
import se.krka.kahlua.vm.KahluaTableIterator;
import se.krka.kahlua.vm.KahluaThread;
import se.krka.kahlua.vm.LuaClosure;
import zombie.ZomboidFileSystem;
import zombie.Lua.LuaManager.Exposer;
import zombie.characters.HairOutfitDefinitions;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.characters.ZombiesZoneDefinition;
import zombie.characters.AttachedItems.AttachedWeaponDefinitions;
import zombie.core.BoxedStaticValues;
import zombie.core.IndieFileLoader;
import zombie.core.logger.ExceptionLogger;
import zombie.core.raknet.VoiceManager;
import zombie.core.skinnedmodel.population.DefaultClothing;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.inventory.InventoryItem;
import zombie.inventory.ItemContainer;
import zombie.inventory.ItemPickerJava;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.iso.IsoWorld;
import zombie.network.CoopMaster;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.network.NetChecksum;
import zombie.network.NetChecksum.GroupOfFiles;
import zombie.ui.UIManager;
import zombie.util.Type;

public final class LuaManager {
   public static KahluaConverterManager converterManager = new KahluaConverterManager();
   public static J2SEPlatform platform = new J2SEPlatform();
   public static KahluaTable env;
   public static KahluaThread thread;
   public static KahluaThread debugthread;
   public static LuaCaller caller = new LuaCaller(converterManager);
   public static LuaCaller debugcaller = new LuaCaller(converterManager);
   public static Exposer exposer;
   public static ArrayList<String> loaded = new ArrayList<>();
   private static final HashSet<String> loading = new HashSet<>();
   public static HashMap<String, Object> loadedReturn = new HashMap<>();
   public static boolean checksumDone = false;
   public static ArrayList<String> loadList = new ArrayList<>();
   static ArrayList<String> paths = new ArrayList<>();
   private static final HashMap<String, Object> luaFunctionMap = new HashMap<>();
   private static final HashSet<KahluaTable> s_wiping = new HashSet<>();

   public static void outputTable(KahluaTable var0, int var1) {
   }

   private static void wipeRecurse(KahluaTable var0) {
      if (!var0.isEmpty()) {
         if (!s_wiping.contains(var0)) {
            s_wiping.add(var0);
            KahluaTableIterator var1 = var0.iterator();

            while (var1.advance()) {
               KahluaTable var2 = (KahluaTable)Type.tryCastTo(var1.getValue(), KahluaTable.class);
               if (var2 != null) {
                  wipeRecurse(var2);
               }
            }

            s_wiping.remove(var0);
            var0.wipe();
         }
      }
   }

   public static void init() {
      loaded.clear();
      loading.clear();
      loadedReturn.clear();
      paths.clear();
      luaFunctionMap.clear();
      platform = new J2SEPlatform();
      if (env != null) {
         s_wiping.clear();
         wipeRecurse(env);
      }

      env = platform.newEnvironment();
      converterManager = new KahluaConverterManager();
      if (thread != null) {
         thread.bReset = true;
      }

      thread = new KahluaThread(platform, env);
      debugthread = new KahluaThread(platform, env);
      UIManager.defaultthread = thread;
      caller = new LuaCaller(converterManager);
      debugcaller = new LuaCaller(converterManager);
      if (exposer != null) {
         exposer.destroy();
      }

      exposer = new Exposer(converterManager, platform, env);
      loaded = new ArrayList<>();
      checksumDone = false;
      GameClient.checksum = "";
      GameClient.checksumValid = false;
      KahluaNumberConverter.install(converterManager);
      LuaEventManager.register(platform, env);
      LuaHookManager.register(platform, env);
      if (CoopMaster.instance != null) {
         CoopMaster.instance.register(platform, env);
      }

      if (VoiceManager.instance != null) {
         VoiceManager.instance.LuaRegister(platform, env);
      }

      KahluaTable var0 = env;
      exposer.exposeAll();
      exposer.TypeMap.put("function", LuaClosure.class);
      exposer.TypeMap.put("table", KahluaTable.class);
      outputTable(env, 0);
   }

   public static void LoadDir(String var0) throws URISyntaxException {
   }

   public static void LoadDirBase(String var0) throws Exception {
      LoadDirBase(var0, false);
   }

   public static void LoadDirBase(String var0, boolean var1) throws Exception {
      String var2 = "media/lua/" + var0 + "/";
      File var3 = ZomboidFileSystem.instance.getMediaFile("lua" + File.separator + var0);
      if (!paths.contains(var2)) {
         paths.add(var2);
      }

      try {
         searchFolders(ZomboidFileSystem.instance.baseURI, var3);
      } catch (IOException var14) {
         ExceptionLogger.logException(var14);
      }

      ArrayList var15 = loadList;
      loadList = new ArrayList<>();
      ArrayList var16 = ZomboidFileSystem.instance.getModIDs();

      for (int var4 = 0; var4 < var16.size(); var4++) {
         String var5 = ZomboidFileSystem.instance.getModDir((String)var16.get(var4));
         if (var5 != null) {
            File var6 = new File(var5);
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
      HashSet var17 = new HashSet();

      for (String var19 : loadList) {
         if (!var17.contains(var19)) {
            var17.add(var19);
            String var20 = ZomboidFileSystem.instance.getAbsolutePath(var19);
            if (var20 == null) {
               throw new IllegalStateException("couldn't find \"" + var19 + "\"");
            }

            if (!var1) {
               RunLua(var20);
            }

            if (!checksumDone && !var19.contains("SandboxVars.lua") && (GameServer.bServer || GameClient.bClient)) {
               NetChecksum.checksummer.addFile(var19, var20);
            }

            if (CoopMaster.instance != null) {
               CoopMaster.instance.update();
            }
         }
      }

      loadList.clear();
   }

   public static void initChecksum() throws Exception {
      if (!checksumDone) {
         if (GameClient.bClient || GameServer.bServer) {
            NetChecksum.checksummer.reset(false);
         }
      }
   }

   public static void finishChecksum() {
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

   public static void LoadDirBase() throws Exception {
      initChecksum();
      LoadDirBase("shared");
      LoadDirBase("client");
   }

   public static void searchFolders(URI var0, File var1) throws IOException {
      if (var1.isDirectory()) {
         String[] var2 = var1.list();

         for (int var3 = 0; var3 < var2.length; var3++) {
            searchFolders(var0, new File(var1.getCanonicalFile().getAbsolutePath() + File.separator + var2[var3]));
         }
      } else if (var1.getAbsolutePath().toLowerCase().endsWith(".lua")) {
         String var4 = ZomboidFileSystem.instance.getRelativeFile(var0, var1.getAbsolutePath());
         var4 = var4.toLowerCase(Locale.ENGLISH);
         loadList.add(var4);
      }
   }

   public static String getLuaCacheDir() {
      String var0 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "Lua";
      File var1 = new File(var0);
      if (!var1.exists()) {
         var1.mkdir();
      }

      return var0;
   }

   public static String getSandboxCacheDir() {
      String var0 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "Sandbox Presets";
      File var1 = new File(var0);
      if (!var1.exists()) {
         var1.mkdir();
      }

      return var0;
   }

   public static void fillContainer(ItemContainer var0, IsoPlayer var1) {
      ItemPickerJava.fillContainer(var0, var1);
   }

   public static void updateOverlaySprite(IsoObject var0) {
      ItemPickerJava.updateOverlaySprite(var0);
   }

   public static LuaClosure getDotDelimitedClosure(String var0) {
      String[] var1 = var0.split("\\.");
      KahluaTable var2 = env;

      for (int var3 = 0; var3 < var1.length - 1; var3++) {
         var2 = (KahluaTable)env.rawget(var1[var3]);
      }

      return (LuaClosure)var2.rawget(var1[var1.length - 1]);
   }

   public static void transferItem(IsoGameCharacter var0, InventoryItem var1, ItemContainer var2, ItemContainer var3) {
      LuaClosure var4 = (LuaClosure)env.rawget("javaTransferItems");
      caller.pcall(thread, var4, new Object[]{var0, var1, var2, var3});
   }

   public static void dropItem(InventoryItem var0) {
      LuaClosure var1 = getDotDelimitedClosure("ISInventoryPaneContextMenu.dropItem");
      caller.pcall(thread, var1, var0);
   }

   public static IsoGridSquare AdjacentFreeTileFinder(IsoGridSquare var0, IsoPlayer var1) {
      KahluaTable var2 = (KahluaTable)env.rawget("AdjacentFreeTileFinder");
      LuaClosure var3 = (LuaClosure)var2.rawget("Find");
      return (IsoGridSquare)caller.pcall(thread, var3, new Object[]{var0, var1})[1];
   }

   public static Object RunLua(String var0) {
      return RunLua(var0, false);
   }

   public static Object RunLua(String var0, boolean var1) {
      String var2 = var0.replace("\\", "/");
      if (loading.contains(var2)) {
         DebugLog.Lua.warn("recursive require(): %s", new Object[]{var2});
         return null;
      } else {
         loading.add(var2);

         Object var3;
         try {
            var3 = RunLuaInternal(var0, var1);
         } finally {
            loading.remove(var2);
         }

         return var3;
      }
   }

   private static Object RunLuaInternal(String var0, boolean var1) {
      var0 = var0.replace("\\", "/");
      if (loaded.contains(var0)) {
         return loadedReturn.get(var0);
      } else {
         FuncState.currentFile = var0.substring(var0.lastIndexOf(47) + 1);
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
            return null;
         }

         LuaCompiler.rewriteEvents = var1;

         LuaClosure var4;
         try (BufferedReader var5 = new BufferedReader(var3)) {
            var4 = LuaCompiler.loadis(var5, var0.substring(var0.lastIndexOf(47) + 1), env);
         } catch (Exception var10) {
            Logger.getLogger(LuaManager.class.getName()).log(Level.SEVERE, "Error found in LUA file: " + var0, null);
            ExceptionLogger.logException(var10);
            thread.debugException(var10);
            return null;
         }

         luaFunctionMap.clear();
         AttachedWeaponDefinitions.instance.m_dirty = true;
         DefaultClothing.instance.m_dirty = true;
         HairOutfitDefinitions.instance.m_dirty = true;
         ZombiesZoneDefinition.bDirty = true;
         LuaReturn var14 = caller.protectedCall(thread, var4, new Object[0]);
         if (!var14.isSuccess()) {
            Logger.getLogger(IsoWorld.class.getName()).log(Level.SEVERE, var14.getErrorString(), null);
            if (var14.getJavaException() != null) {
               Logger.getLogger(IsoWorld.class.getName()).log(Level.SEVERE, var14.getJavaException().toString(), null);
            }

            Logger.getLogger(IsoWorld.class.getName()).log(Level.SEVERE, var14.getLuaStackTrace(), null);
         }

         loaded.add(var0);
         Object var6 = var14.isSuccess() && var14.size() > 0 ? var14.getFirst() : null;
         if (var6 != null) {
            loadedReturn.put(var0, var6);
         } else {
            loadedReturn.remove(var0);
         }

         LuaCompiler.rewriteEvents = false;
         return var6;
      }
   }

   public static Object getFunctionObject(String var0) {
      if (var0 != null && !var0.isEmpty()) {
         Object var1 = luaFunctionMap.get(var0);
         if (var1 != null) {
            return var1;
         } else {
            KahluaTable var2 = env;
            if (var0.contains(".")) {
               String[] var3 = var0.split("\\.");

               for (int var4 = 0; var4 < var3.length - 1; var4++) {
                  KahluaTable var5 = (KahluaTable)Type.tryCastTo(var2.rawget(var3[var4]), KahluaTable.class);
                  if (var5 == null) {
                     DebugLog.General.error("no such function \"%s\"", new Object[]{var0});
                     return null;
                  }

                  var2 = var5;
               }

               var1 = var2.rawget(var3[var3.length - 1]);
            } else {
               var1 = var2.rawget(var0);
            }

            if (!(var1 instanceof JavaFunction) && !(var1 instanceof LuaClosure)) {
               DebugLog.General.error("no such function \"%s\"", new Object[]{var0});
               return null;
            } else {
               luaFunctionMap.put(var0, var1);
               return var1;
            }
         }
      } else {
         return null;
      }
   }

   public static void Test() throws IOException {
   }

   public static Object get(Object var0) {
      return env.rawget(var0);
   }

   public static void call(String var0, Object var1) {
      caller.pcall(thread, env.rawget(var0), var1);
   }

   private static void exposeKeyboardKeys(KahluaTable var0) {
      if (var0.rawget("Keyboard") instanceof KahluaTable var2) {
         Field[] var3 = Keyboard.class.getFields();

         try {
            for (Field var7 : var3) {
               if (Modifier.isStatic(var7.getModifiers())
                  && Modifier.isPublic(var7.getModifiers())
                  && Modifier.isFinal(var7.getModifiers())
                  && var7.getType().equals(int.class)
                  && var7.getName().startsWith("KEY_")
                  && !var7.getName().endsWith("WIN")) {
                  var2.rawset(var7.getName(), (double)var7.getInt(null));
               }
            }
         } catch (Exception var8) {
         }
      }
   }

   private static void exposeLuaCalendar() {
      KahluaTable var0 = (KahluaTable)env.rawget("PZCalendar");
      if (var0 != null) {
         Field[] var1 = Calendar.class.getFields();

         try {
            for (Field var5 : var1) {
               if (Modifier.isStatic(var5.getModifiers())
                  && Modifier.isPublic(var5.getModifiers())
                  && Modifier.isFinal(var5.getModifiers())
                  && var5.getType().equals(int.class)) {
                  var0.rawset(var5.getName(), BoxedStaticValues.toDouble(var5.getInt(null)));
               }
            }
         } catch (Exception var6) {
         }

         env.rawset("Calendar", var0);
      }
   }

   public static String getHourMinuteJava() {
      String var0 = Calendar.getInstance().get(12) + "";
      if (Calendar.getInstance().get(12) < 10) {
         var0 = "0" + var0;
      }

      return Calendar.getInstance().get(11) + ":" + var0;
   }

   public static KahluaTable copyTable(KahluaTable var0) {
      return copyTable(null, var0);
   }

   public static KahluaTable copyTable(KahluaTable var0, KahluaTable var1) {
      if (var0 == null) {
         var0 = platform.newTable();
      } else {
         var0.wipe();
      }

      if (var1 != null && !var1.isEmpty()) {
         KahluaTableIterator var2 = var1.iterator();

         while (var2.advance()) {
            Object var3 = var2.getKey();
            Object var4 = var2.getValue();
            if (var4 instanceof KahluaTable) {
               var0.rawset(var3, copyTable(null, (KahluaTable)var4));
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
