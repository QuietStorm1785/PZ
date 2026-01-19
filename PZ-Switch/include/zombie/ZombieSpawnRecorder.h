#pragma once
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/logger/ZLogger.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/areas/IsoRoom.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZombieSpawnRecorder {
public:
 static const ZombieSpawnRecorder instance = new ZombieSpawnRecorder();
 ZLogger m_logger;
 const StringBuilder m_stringBuilder = new StringBuilder();

 void init() {
 if (this->m_logger != nullptr) {
 this->m_logger.write("===================================================="
 "============================");
 } else {
 LoggerManager.init();
 LoggerManager.createLogger("ZombieSpawn", Core.bDebug);
 this->m_logger = LoggerManager.getLogger("ZombieSpawn");
 }
 }

 void quit() {
 if (this->m_logger != nullptr) {
 if (this->m_stringBuilder.length() > 0) {
 this->m_logger.write(this->m_stringBuilder.toString());
 this->m_stringBuilder.setLength(0);
 }
 }
 }

 void record(IsoZombie zombie0, std::string_view string) {
 if (zombie0 != nullptr && zombie0.getCurrentSquare() != nullptr) {
 if (this->m_logger != nullptr) {
 IsoGridSquare square = zombie0.getCurrentSquare();
 this->m_stringBuilder.append("reason = ");
 this->m_stringBuilder.append(string);
 this->m_stringBuilder.append(" x,y,z = ");
 this->m_stringBuilder.append(square.x);
 this->m_stringBuilder.append(',');
 this->m_stringBuilder.append(square.y);
 this->m_stringBuilder.append(',');
 this->m_stringBuilder.append(square.z);
 IsoRoom room = square.getRoom();
 if (room != nullptr && room.def != nullptr) {
 this->m_stringBuilder.append(" room = ");
 this->m_stringBuilder.append(room.def.name);
 }

 this->m_stringBuilder.append(System.lineSeparator());
 if (this->m_stringBuilder.length() >= 1024) {
 this->m_logger.write(this->m_stringBuilder.toString());
 this->m_stringBuilder.setLength(0);
 }
 }
 }
 }

 void record(ArrayList<IsoZombie> arrayList, std::string_view string) {
 if (arrayList != nullptr) {
 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 this->record((IsoZombie)arrayList.get(int0), string);
 }
 }
 }
}
} // namespace zombie
