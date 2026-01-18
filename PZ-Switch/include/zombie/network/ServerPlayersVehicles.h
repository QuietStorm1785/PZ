#pragma once
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/savefile/ServerPlayerDB.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ServerPlayersVehicles {
public:
 static const ServerPlayersVehicles instance = new ServerPlayersVehicles();
private
 ServerPlayersVehicles.SPVThread m_thread = nullptr;

 void init() {
 this->m_thread = new ServerPlayersVehicles.SPVThread();
 this->m_thread.setName("ServerPlayersVehicles");
 this->m_thread.setDaemon(true);
 this->m_thread.start();
 }

 void stop() {
 if (this->m_thread != nullptr) {
 this->m_thread.m_bStop = true;

 while (this->m_thread.isAlive()) {
 try {
 Thread.sleep(100L);
 } catch (InterruptedException interruptedException) {
 }
 }

 this->m_thread = nullptr;
 }
 }

private
 static class SPVThread extends Thread {
 bool m_bStop = false;

 void run() {
 while (!this->m_bStop) {
 try {
 this->runInner();
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 }
 }
 }

 void runInner() {
 ServerPlayerDB.getInstance().process();
 VehiclesDB2.instance.updateWorldStreamer();

 try {
 Thread.sleep(500L);
 } catch (InterruptedException interruptedException) {
 }
 }
 }
}
} // namespace network
} // namespace zombie
