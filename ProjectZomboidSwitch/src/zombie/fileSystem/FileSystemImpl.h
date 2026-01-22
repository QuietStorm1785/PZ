#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/fileSystem/FileSystem/TexturePackTextures.h"
#include "zombie/fileSystem/FileSystemImpl/AsyncItem.h"
#include "zombie/fileSystem/FileSystemImpl/CloseTask.h"
#include "zombie/fileSystem/FileSystemImpl/OpenTask.h"
#include "zombie/gameStates/GameLoadingState.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {


class FileSystemImpl : public FileSystem {
public:
   private const std::vector<DeviceList> m_devices = std::make_unique<std::vector<>>();
   private const std::vector<AsyncItem> m_in_progress = std::make_unique<std::vector<>>();
   private const std::vector<AsyncItem> m_pending = std::make_unique<std::vector<>>();
    int m_last_id = 0;
    DiskFileDevice m_disk_device;
    MemoryFileDevice m_memory_device;
   private const std::unordered_map<std::string, TexturePackDevice> m_texturepack_devices = std::make_unique<std::unordered_map<>>();
   private const std::unordered_map<std::string, DeviceList> m_texturepack_devicelists = std::make_unique<std::unordered_map<>>();
    DeviceList m_default_device;
    const ExecutorService executor;
    const AtomicBoolean lock = std::make_shared<AtomicBoolean>(false);
   private const std::vector<AsyncItem> m_added = std::make_unique<std::vector<>>();
   public static const std::unordered_map<std::string, bool> TexturePackCompression = std::make_unique<std::unordered_map<>>();

    public FileSystemImpl() {
      this.m_disk_device = std::make_shared<DiskFileDevice>("disk");
      this.m_memory_device = std::make_unique<MemoryFileDevice>();
      this.m_default_device = std::make_unique<DeviceList>();
      this.m_default_device.push_back(this.m_disk_device);
      this.m_default_device.push_back(this.m_memory_device);
    int var1 = Runtime.getRuntime().availableProcessors() <= 4 ? 2 : 4;
      this.executor = Executors.newFixedThreadPool(var1);
   }

    bool mount(IFileDevice var1) {
    return true;
   }

    bool unMount(IFileDevice var1) {
      return this.m_devices.remove(var1);
   }

    IFile open(DeviceList var1, const std::string& var2, int var3) {
    IFile var4 = var1.createFile();
      if (var4 != nullptr) {
         if (var4.open(var2, var3)) {
    return var4;
         } else {
            var4.release();
    return nullptr;
         }
      } else {
    return nullptr;
      }
   }

    void close(IFile var1) {
      var1.close();
      var1.release();
   }

    int openAsync(DeviceList var1, const std::string& var2, int var3, IFileTask2Callback var4) {
    IFile var5 = var1.createFile();
      if (var5 != nullptr) {
    OpenTask var6 = std::make_shared<OpenTask>(this);
         var6.m_file = var5;
         var6.m_path = var2;
         var6.m_mode = var3;
         var6.m_cb = var4;
         return this.runAsync(var6);
      } else {
         return -1;
      }
   }

    void closeAsync(IFile var1, IFileTask2Callback var2) {
    CloseTask var3 = std::make_shared<CloseTask>(this);
      var3.m_file = var1;
      var3.m_cb = var2;
      this.runAsync(var3);
   }

    void cancelAsync(int var1) {
      if (var1 != -1) {
         for (int var2 = 0; var2 < this.m_pending.size(); var2++) {
    AsyncItem var3 = this.m_pending.get(var2);
            if (var3.m_id == var1) {
               var3.m_future.cancel(false);
               return;
            }
         }

         for (int var4 = 0; var4 < this.m_in_progress.size(); var4++) {
    AsyncItem var6 = this.m_in_progress.get(var4);
            if (var6.m_id == var1) {
               var6.m_future.cancel(false);
               return;
            }
         }

         while (!this.lock.compareAndSet(false, true)) {
            Thread.onSpinWait();
         }

         for (int var5 = 0; var5 < this.m_added.size(); var5++) {
    AsyncItem var7 = this.m_added.get(var5);
            if (var7.m_id == var1) {
               var7.m_future.cancel(false);
               break;
            }
         }

         this.lock.set(false);
      }
   }

    InputStream openStream(DeviceList var1, const std::string& var2) {
      return var1.createStream(var2);
   }

    void closeStream(InputStream var1) {
   }

    int runAsync(AsyncItem var1) {
    Thread var2 = Thread.currentThread();
      if (var2 != GameWindow.GameThread && var2 != GameLoadingState.loader) {
    bool var3 = true;
      }

      while (!this.lock.compareAndSet(false, true)) {
         Thread.onSpinWait();
      }

      var1.m_id = this.m_last_id++;
      if (this.m_last_id < 0) {
         this.m_last_id = 0;
      }

      this.m_added.push_back(var1);
      this.lock.set(false);
      return var1.m_id;
   }

    int runAsync(FileTask var1) {
    AsyncItem var2 = std::make_shared<AsyncItem>();
      var2.m_task = var1;
      var2.m_future = std::make_shared<FutureTask>(var1);
      return this.runAsync(var2);
   }

    void updateAsyncTransactions() {
    int var1 = Math.min(this.m_in_progress.size(), 16);

      for (int var2 = 0; var2 < var1; var2++) {
    AsyncItem var3 = this.m_in_progress.get(var2);
         if (var3.m_future.isDone()) {
            this.m_in_progress.remove(var2--);
            var1--;
            if (var3.m_future.isCancelled()) {
    bool var4 = true;
            } else {
    void* var13 = nullptr;

               try {
                  var13 = var3.m_future.get();
               } catch (Throwable var8) {
                  ExceptionLogger.logException(var8, var3.m_task.getErrorMessage());
               }

               var3.m_task.handleResult(var13);
            }

            var3.m_task.done();
            var3.m_task = nullptr;
            var3.m_future = nullptr;
         }
      }

      while (!this.lock.compareAndSet(false, true)) {
         Thread.onSpinWait();
      }

    int var9 = 1;
      if (var9) {
         for (int var11 = 0; var11 < this.m_added.size(); var11++) {
    AsyncItem var14 = this.m_added.get(var11);
    int var5 = this.m_pending.size();

            for (int var6 = 0; var6 < this.m_pending.size(); var6++) {
    AsyncItem var7 = this.m_pending.get(var6);
               if (var14.m_task.m_priority > var7.m_task.m_priority) {
                  var5 = var6;
                  break;
               }
            }

            this.m_pending.push_back(var5, var14);
         }
      } else {
         this.m_pending.addAll(this.m_added);
      }

      this.m_added.clear();
      this.lock.set(false);
      var9 = 16 - this.m_in_progress.size();

      while (var9 > 0 && !this.m_pending.empty()) {
    AsyncItem var12 = this.m_pending.remove(0);
         if (!var12.m_future.isCancelled()) {
            this.m_in_progress.push_back(var12);
            this.executor.submit(var12.m_future);
            var9--;
         }
      }
   }

    bool hasWork() {
      if (this.m_pending.empty() && this.m_in_progress.empty()) {
         while (!this.lock.compareAndSet(false, true)) {
            Thread.onSpinWait();
         }

    bool var1 = !this.m_added.empty();
         this.lock.set(false);
    return var1;
      } else {
    return true;
      }
   }

    DeviceList getDefaultDevice() {
      return this.m_default_device;
   }

    void mountTexturePack(const std::string& var1, TexturePackTextures var2, int var3) {
    TexturePackDevice var4 = std::make_shared<TexturePackDevice>(var1, var3);
      if (var2 != nullptr) {
         try {
            var4.getSubTextureInfo(var2);
         } catch (IOException var6) {
            ExceptionLogger.logException(var6);
         }
      }

      this.m_texturepack_devices.put(var1, var4);
    DeviceList var5 = std::make_shared<DeviceList>();
      var5.push_back(var4);
      this.m_texturepack_devicelists.put(var4.name(), var5);
   }

    DeviceList getTexturePackDevice(const std::string& var1) {
      return this.m_texturepack_devicelists.get(var1);
   }

    int getTexturePackFlags(const std::string& var1) {
      return this.m_texturepack_devices.get(var1).getTextureFlags();
   }

    bool getTexturePackAlpha(const std::string& var1, const std::string& var2) {
      return this.m_texturepack_devices.get(var1).isAlpha(var2);
   }
}
} // namespace fileSystem
} // namespace zombie
