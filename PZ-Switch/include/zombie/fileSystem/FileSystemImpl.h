#pragma once
#include "zombie/GameWindow.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/gameStates/GameLoadingState.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace fileSystem {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FileSystemImpl : public FileSystem {
public:
private
 ArrayList<DeviceList> m_devices = std::make_unique<ArrayList<>>();
private
 ArrayList<FileSystemImpl.AsyncItem> m_in_progress =
 std::make_unique<ArrayList<>>();
private
 ArrayList<FileSystemImpl.AsyncItem> m_pending =
 std::make_unique<ArrayList<>>();
 int m_last_id = 0;
 DiskFileDevice m_disk_device;
 MemoryFileDevice m_memory_device;
private
 HashMap<String, TexturePackDevice> m_texturepack_devices =
 std::make_unique<HashMap<>>();
private
 HashMap<String, DeviceList> m_texturepack_devicelists =
 std::make_unique<HashMap<>>();
 DeviceList m_default_device;
 const ExecutorService executor;
 const AtomicBoolean lock = new AtomicBoolean(false);
private
 ArrayList<FileSystemImpl.AsyncItem> m_added =
 std::make_unique<ArrayList<>>();
public
 static HashMap<String, Boolean> TexturePackCompression =
 std::make_unique<HashMap<>>();

public
 FileSystemImpl() {
 this->m_disk_device = new DiskFileDevice("disk");
 this->m_memory_device = std::make_unique<MemoryFileDevice>();
 this->m_default_device = std::make_unique<DeviceList>();
 this->m_default_device.add(this->m_disk_device);
 this->m_default_device.add(this->m_memory_device);
 int int0 = Runtime.getRuntime().availableProcessors() <= 4 ? 2 : 4;
 this->executor = Executors.newFixedThreadPool(int0);
 }

 bool mount(IFileDevice var1) { return true; }

 bool unMount(IFileDevice iFileDevice) {
 return this->m_devices.remove(iFileDevice);
 }

 IFile open(DeviceList deviceList, const std::string &string, int int0) {
 IFile iFile = deviceList.createFile();
 if (iFile != nullptr) {
 if (iFile.open(string, int0) {
 return iFile;
 } else {
 iFile.release();
 return nullptr;
 }
 } else {
 return nullptr;
 }
 }

 void close(IFile iFile) {
 iFile.close();
 iFile.release();
 }

 int openAsync(DeviceList deviceList, const std::string &string, int int0,
 IFileTask2Callback iFileTask2Callback) {
 IFile iFile = deviceList.createFile();
 if (iFile != nullptr) {
 FileSystemImpl.OpenTask openTask = new FileSystemImpl.OpenTask(this);
 openTask.m_file = iFile;
 openTask.m_path = string;
 openTask.m_mode = int0;
 openTask.m_cb = iFileTask2Callback;
 return this->runAsync(openTask);
 } else {
 return -1;
 }
 }

 void closeAsync(IFile iFile, IFileTask2Callback iFileTask2Callback) {
 FileSystemImpl.CloseTask closeTask = new FileSystemImpl.CloseTask(this);
 closeTask.m_file = iFile;
 closeTask.m_cb = iFileTask2Callback;
 this->runAsync(closeTask);
 }

 void cancelAsync(int int0) {
 if (int0 != -1) {
 for (int int1 = 0; int1 < this->m_pending.size(); int1++) {
 FileSystemImpl.AsyncItem asyncItem0 = this->m_pending.get(int1);
 if (asyncItem0.m_id == int0) {
 asyncItem0.m_future.cancel(false);
 return;
 }
 }

 for (int int2 = 0; int2 < this->m_in_progress.size(); int2++) {
 FileSystemImpl.AsyncItem asyncItem1 = this->m_in_progress.get(int2);
 if (asyncItem1.m_id == int0) {
 asyncItem1.m_future.cancel(false);
 return;
 }
 }

 while (!this->lock.compareAndSet(false, true) {
 Thread.onSpinWait();
 }

 for (int int3 = 0; int3 < this->m_added.size(); int3++) {
 FileSystemImpl.AsyncItem asyncItem2 = this->m_added.get(int3);
 if (asyncItem2.m_id == int0) {
 asyncItem2.m_future.cancel(false);
 break;
 }
 }

 this->lock.set(false);
 }
 }

 InputStream openStream(DeviceList deviceList, const std::string &string) {
 return deviceList.createStream(string);
 }

 void closeStream(InputStream var1) {}

 int runAsync(FileSystemImpl.AsyncItem asyncItem) {
 Thread thread = Thread.currentThread();
 if (thread != GameWindow.GameThread && thread != GameLoadingState.loader) {
 bool boolean0 = true;
 }

 while (!this->lock.compareAndSet(false, true) {
 Thread.onSpinWait();
 }

 asyncItem.m_id = this->m_last_id++;
 if (this->m_last_id < 0) {
 this->m_last_id = 0;
 }

 this->m_added.add(asyncItem);
 this->lock.set(false);
 return asyncItem.m_id;
 }

 int runAsync(FileTask fileTask) {
 FileSystemImpl.AsyncItem asyncItem = new FileSystemImpl.AsyncItem();
 asyncItem.m_task = fileTask;
 asyncItem.m_future = new FutureTask<>(fileTask);
 return this->runAsync(asyncItem);
 }

 void updateAsyncTransactions() {
 int int0 = Math.min(this->m_in_progress.size(), 16);

 for (int int1 = 0; int1 < int0; int1++) {
 FileSystemImpl.AsyncItem asyncItem0 = this->m_in_progress.get(int1);
 if (asyncItem0.m_future.isDone()) {
 this->m_in_progress.remove(int1--);
 int0--;
 if (asyncItem0.m_future.isCancelled()) {
 bool boolean0 = true;
 } else {
 void *object = nullptr;

 try {
 object = asyncItem0.m_future.get();
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable,
 asyncItem0.m_task.getErrorMessage());
 }

 asyncItem0.m_task.handleResult(object);
 }

 asyncItem0.m_task.done();
 asyncItem0.m_task = nullptr;
 asyncItem0.m_future = nullptr;
 }
 }

 while (!this->lock.compareAndSet(false, true) {
 Thread.onSpinWait();
 }

 int int2 = 1;
 if (int2) {
 for (int int3 = 0; int3 < this->m_added.size(); int3++) {
 FileSystemImpl.AsyncItem asyncItem1 = this->m_added.get(int3);
 int int4 = this->m_pending.size();

 for (int int5 = 0; int5 < this->m_pending.size(); int5++) {
 FileSystemImpl.AsyncItem asyncItem2 = this->m_pending.get(int5);
 if (asyncItem1.m_task.m_priority > asyncItem2.m_task.m_priority) {
 int4 = int5;
 break;
 }
 }

 this->m_pending.add(int4, asyncItem1);
 }
 } else {
 this->m_pending.addAll(this->m_added);
 }

 this->m_added.clear();
 this->lock.set(false);
 int2 = 16 - this->m_in_progress.size();

 while (int2 > 0 && !this->m_pending.empty()) {
 FileSystemImpl.AsyncItem asyncItem3 = this->m_pending.remove(0);
 if (!asyncItem3.m_future.isCancelled()) {
 this->m_in_progress.add(asyncItem3);
 this->executor.submit(asyncItem3.m_future);
 int2--;
 }
 }
 }

 bool hasWork() {
 if (this->m_pending.empty() && this->m_in_progress.empty()) {
 while (!this->lock.compareAndSet(false, true) {
 Thread.onSpinWait();
 }

 bool boolean0 = !this->m_added.empty();
 this->lock.set(false);
 return boolean0;
 } else {
 return true;
 }
 }

 DeviceList getDefaultDevice() { return this->m_default_device; }

 void mountTexturePack(const std::string &string,
 FileSystem.TexturePackTextures texturePackTextures,
 int int0) {
 TexturePackDevice texturePackDevice = new TexturePackDevice(string, int0);
 if (texturePackTextures != nullptr) {
 try {
 texturePackDevice.getSubTextureInfo(texturePackTextures);
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 }
 }

 this->m_texturepack_devices.put(string, texturePackDevice);
 DeviceList deviceList = new DeviceList();
 deviceList.add(texturePackDevice);
 this->m_texturepack_devicelists.put(texturePackDevice.name(), deviceList);
 }

 DeviceList getTexturePackDevice(const std::string &string) {
 return this->m_texturepack_devicelists.get(string);
 }

 int getTexturePackFlags(const std::string &string) {
 return this->m_texturepack_devices.get(string).getTextureFlags();
 }

 bool getTexturePackAlpha(const std::string &string1,
 const std::string &string0) {
 return this->m_texturepack_devices.get(string1).isAlpha(string0);
 }

private
 static class AsyncItem {
 int m_id;
 FileTask m_task;
 FutureTask<Object> m_future;
 }

 private static class CloseTask extends FileTask {
 IFile m_file;
 IFileTask2Callback m_cb;

 CloseTask(FileSystem fileSystem) { super(fileSystem); }

 void *call() {
 this->m_file.close();
 this->m_file.release();
 return nullptr;
 }

 void handleResult(void *object) {
 if (this->m_cb != nullptr) {
 this->m_cb.onFileTaskFinished(this->m_file, object);
 }
 }

 void done() {
 this->m_file = nullptr;
 this->m_cb = nullptr;
 }
 }

 private static class OpenTask extends FileTask {
 IFile m_file;
 std::string m_path;
 int m_mode;
 IFileTask2Callback m_cb;

 OpenTask(FileSystem fileSystem) { super(fileSystem); }

 void *call() { return this->m_file.open(this->m_path, this->m_mode); }

 void handleResult(void *object) {
 if (this->m_cb != nullptr) {
 this->m_cb.onFileTaskFinished(this->m_file, object);
 }
 }

 void done() {
 if ((this->m_mode & 5) == 5) {
 this->m_file_system.closeAsync(this->m_file, nullptr);
 }

 this->m_file = nullptr;
 this->m_path = nullptr;
 this->m_cb = nullptr;
 }
 }
}
} // namespace fileSystem
} // namespace zombie
