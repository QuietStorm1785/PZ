#pragma once
#include "zombie/core/textures/Texture.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
namespace symbols {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class MapSymbolDefinitions {
public:
  static MapSymbolDefinitions instance;
private
  final ArrayList<MapSymbolDefinitions.MapSymbolDefinition> m_symbolList =
      std::make_unique<ArrayList<>>();
private
  final HashMap<String, MapSymbolDefinitions.MapSymbolDefinition> m_symbolByID =
      std::make_unique<HashMap<>>();

  static MapSymbolDefinitions getInstance() {
    if (instance == nullptr) {
      instance = std::make_unique<MapSymbolDefinitions>();
    }

    return instance;
  }

  void addTexture(const std::string &string0, const std::string &string1,
                  int int0, int int1) {
    MapSymbolDefinitions.MapSymbolDefinition mapSymbolDefinition =
        new MapSymbolDefinitions.MapSymbolDefinition();
    mapSymbolDefinition.id = string0;
    mapSymbolDefinition.texturePath = string1;
    mapSymbolDefinition.width = int0;
    mapSymbolDefinition.height = int1;
    this.m_symbolList.add(mapSymbolDefinition);
    this.m_symbolByID.put(string0, mapSymbolDefinition);
  }

  void addTexture(const std::string &string1, const std::string &string0) {
    Texture texture = Texture.getSharedTexture(string0);
    if (texture == nullptr) {
      this.addTexture(string1, string0, 18, 18);
    } else {
      this.addTexture(string1, string0, texture.getWidth(),
                      texture.getHeight());
    }
  }

  int getSymbolCount() { return this.m_symbolList.size(); }

public
  MapSymbolDefinitions.MapSymbolDefinition getSymbolByIndex(int int0) {
    return this.m_symbolList.get(int0);
  }

public
  MapSymbolDefinitions.MapSymbolDefinition getSymbolById(String string) {
    return this.m_symbolByID.get(string);
  }

  static void Reset() {
    if (instance != nullptr) {
      getInstance().m_symbolList.clear();
      getInstance().m_symbolByID.clear();
    }
  }

public
  static final class MapSymbolDefinition {
    std::string id;
    std::string texturePath;
    int width;
    int height;

    std::string getId() { return this.id; }

    std::string getTexturePath() { return this.texturePath; }

    int getWidth() { return this.width; }

    int getHeight() { return this.height; }
  }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
