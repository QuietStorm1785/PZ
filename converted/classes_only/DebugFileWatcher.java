package zombie;

import java.io.IOException;
import java.nio.file.FileSystem;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.util.ArrayList;
import java.util.HashMap;
import zombie.DebugFileWatcher.1;
import zombie.core.logger.ExceptionLogger;

public final class DebugFileWatcher {
   private final HashMap<Path, String> m_watchedFiles = new HashMap<>();
   private final HashMap<WatchKey, Path> m_watchkeyMapping = new HashMap<>();
   private final ArrayList<PredicatedFileWatcher> m_predicateWatchers = new ArrayList<>();
   private final ArrayList<PredicatedFileWatcher> m_predicateWatchersInvoking = new ArrayList<>();
   private final FileSystem m_fs = FileSystems.getDefault();
   private WatchService m_watcher;
   private boolean m_predicateWatchersInvokingDirty = true;
   private long m_modificationTime = -1L;
   private final ArrayList<String> m_modifiedFiles = new ArrayList<>();
   public static final DebugFileWatcher instance = new DebugFileWatcher();

   private DebugFileWatcher() {
   }

   public void init() {
      try {
         this.m_watcher = this.m_fs.newWatchService();
         this.registerDirRecursive(this.m_fs.getPath(ZomboidFileSystem.instance.getMediaRootPath()));
         this.registerDirRecursive(this.m_fs.getPath(ZomboidFileSystem.instance.getMessagingDir()));
      } catch (IOException var2) {
         this.m_watcher = null;
      }
   }

   private void registerDirRecursive(Path var1) {
      try {
         Files.walkFileTree(var1, new 1(this));
      } catch (IOException var3) {
         ExceptionLogger.logException(var3);
         this.m_watcher = null;
      }
   }

   private void registerDir(Path var1) {
      try {
         WatchKey var2 = var1.register(this.m_watcher, StandardWatchEventKinds.ENTRY_MODIFY, StandardWatchEventKinds.ENTRY_CREATE);
         this.m_watchkeyMapping.put(var2, var1);
      } catch (IOException var3) {
         ExceptionLogger.logException(var3);
         this.m_watcher = null;
      }
   }

   private void addWatchedFile(String var1) {
      if (var1 != null) {
         this.m_watchedFiles.put(this.m_fs.getPath(var1), var1);
      }
   }

   public void add(PredicatedFileWatcher var1) {
      if (!this.m_predicateWatchers.contains(var1)) {
         this.addWatchedFile(var1.getPath());
         this.m_predicateWatchers.add(var1);
         this.m_predicateWatchersInvokingDirty = true;
      }
   }

   public void addDirectory(String var1) {
      if (var1 != null) {
         this.registerDir(this.m_fs.getPath(var1));
      }
   }

   public void addDirectoryRecurse(String var1) {
      if (var1 != null) {
         this.registerDirRecursive(this.m_fs.getPath(var1));
      }
   }

   public void remove(PredicatedFileWatcher var1) {
      this.m_predicateWatchers.remove(var1);
   }

   public void update() {
      if (this.m_watcher != null) {
         for (WatchKey var1 = this.m_watcher.poll(); var1 != null; var1 = this.m_watcher.poll()) {
            try {
               Path var2 = this.m_watchkeyMapping.getOrDefault(var1, null);

               for (WatchEvent var4 : var1.pollEvents()) {
                  if (var4.kind() == StandardWatchEventKinds.ENTRY_MODIFY) {
                     Path var6 = (Path)var4.context();
                     Path var7 = var2.resolve(var6);
                     String var8 = this.m_watchedFiles.getOrDefault(var7, var7.toString());
                     this.m_modificationTime = System.currentTimeMillis();
                     if (!this.m_modifiedFiles.contains(var8)) {
                        this.m_modifiedFiles.add(var8);
                     }
                  } else if (var4.kind() == StandardWatchEventKinds.ENTRY_CREATE) {
                     Path var16 = (Path)var4.context();
                     Path var17 = var2.resolve(var16);
                     if (Files.isDirectory(var17)) {
                        this.registerDirRecursive(var17);
                     } else {
                        String var18 = this.m_watchedFiles.getOrDefault(var17, var17.toString());
                        this.m_modificationTime = System.currentTimeMillis();
                        if (!this.m_modifiedFiles.contains(var18)) {
                           this.m_modifiedFiles.add(var18);
                        }
                     }
                  }
               }
            } finally {
               if (!var1.reset()) {
                  this.m_watchkeyMapping.remove(var1);
               }
            }
         }

         if (!this.m_modifiedFiles.isEmpty()) {
            if (this.m_modificationTime + 2000L <= System.currentTimeMillis()) {
               for (int var12 = this.m_modifiedFiles.size() - 1; var12 >= 0; var12--) {
                  String var13 = this.m_modifiedFiles.remove(var12);
                  this.swapWatcherArrays();

                  for (PredicatedFileWatcher var15 : this.m_predicateWatchersInvoking) {
                     var15.onModified(var13);
                  }
               }
            }
         }
      }
   }

   private void swapWatcherArrays() {
      if (this.m_predicateWatchersInvokingDirty) {
         this.m_predicateWatchersInvoking.clear();
         this.m_predicateWatchersInvoking.addAll(this.m_predicateWatchers);
         this.m_predicateWatchersInvokingDirty = false;
      }
   }
}
