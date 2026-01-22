#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"
#include "zombie/worldMap/symbols/MapSymbolDefinitions/MapSymbolDefinition.h"

namespace zombie {
namespace worldMap {
namespace symbols {


class MapSymbolDefinitions {
public:
    static MapSymbolDefinitions instance;
   private const std::vector<MapSymbolDefinition> m_symbolList = std::make_unique<std::vector<>>();
   private const std::unordered_map<std::string, MapSymbolDefinition> m_symbolByID = std::make_unique<std::unordered_map<>>();

    static MapSymbolDefinitions getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<MapSymbolDefinitions>();
      }

    return instance;
   }

    void addTexture(const std::string& var1, const std::string& var2, int var3, int var4) {
    MapSymbolDefinition var5 = std::make_shared<MapSymbolDefinition>();
      var5.id = var1;
      var5.texturePath = var2;
      var5.width = var3;
      var5.height = var4;
      this.m_symbolList.push_back(var5);
      this.m_symbolByID.put(var1, var5);
   }

    void addTexture(const std::string& var1, const std::string& var2) {
    Texture var3 = Texture.getSharedTexture(var2);
      if (var3 == nullptr) {
         this.addTexture(var1, var2, 18, 18);
      } else {
         this.addTexture(var1, var2, var3.getWidth(), var3.getHeight());
      }
   }

    int getSymbolCount() {
      return this.m_symbolList.size();
   }

    MapSymbolDefinition getSymbolByIndex(int var1) {
      return this.m_symbolList.get(var1);
   }

    MapSymbolDefinition getSymbolById(const std::string& var1) {
      return this.m_symbolByID.get(var1);
   }

    static void Reset() {
      if (instance != nullptr) {
         getInstance().m_symbolList.clear();
         getInstance().m_symbolByID.clear();
      }
   }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
