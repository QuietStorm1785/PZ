#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/logger/ZLogger.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/areas/IsoRoom.h"

namespace zombie {


class ZombieSpawnRecorder {
public:
    static const ZombieSpawnRecorder instance = std::make_shared<ZombieSpawnRecorder>();
    ZLogger m_logger;
    const std::stringstream m_stringBuilder = new std::stringstream();

    void init() {
      if (this.m_logger != nullptr) {
         this.m_logger.write("================================================================================");
      } else {
         LoggerManager.init();
         LoggerManager.createLogger("ZombieSpawn", Core.bDebug);
         this.m_logger = LoggerManager.getLogger("ZombieSpawn");
      }
   }

    void quit() {
      if (this.m_logger != nullptr) {
         if (this.m_stringBuilder.length() > 0) {
            this.m_logger.write(this.m_stringBuilder);
            this.m_stringBuilder.setLength(0);
         }
      }
   }

    void record(IsoZombie var1, const std::string& var2) {
      if (var1 != nullptr && var1.getCurrentSquare() != nullptr) {
         if (this.m_logger != nullptr) {
    IsoGridSquare var3 = var1.getCurrentSquare();
            this.m_stringBuilder.append("reason = ");
            this.m_stringBuilder.append(var2);
            this.m_stringBuilder.append(" x,y,z = ");
            this.m_stringBuilder.append(var3.x);
            this.m_stringBuilder.append(',');
            this.m_stringBuilder.append(var3.y);
            this.m_stringBuilder.append(',');
            this.m_stringBuilder.append(var3.z);
    IsoRoom var4 = var3.getRoom();
            if (var4 != nullptr && var4.def != nullptr) {
               this.m_stringBuilder.append(" room = ");
               this.m_stringBuilder.append(var4.def.name);
            }

            this.m_stringBuilder.append(System.lineSeparator());
            if (this.m_stringBuilder.length() >= 1024) {
               this.m_logger.write(this.m_stringBuilder);
               this.m_stringBuilder.setLength(0);
            }
         }
      }
   }

    void record(std::vector<IsoZombie> var1, const std::string& var2) {
      if (var1 != nullptr) {
         for (int var3 = 0; var3 < var1.size(); var3++) {
            this.record((IsoZombie)var1.get(var3), var2);
         }
      }
   }
}
} // namespace zombie
