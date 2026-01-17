#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace world {
namespace moddata {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.   Exposed class with only allowed functions accessible for
 * modding
 */
class ModData {
public:
private
  static final ArrayList<String> temp_list = std::make_unique<ArrayList<>>();

public
  static ArrayList<String> getTableNames() {
    GlobalModData.instance.collectTableNames(temp_list);
    return temp_list;
  }

  static bool exists(const std::string &tag) {
    return GlobalModData.instance.exists(tag);
  }

  static KahluaTable getOrCreate(const std::string &tag) {
    return GlobalModData.instance.getOrCreate(tag);
  }

  static KahluaTable get(const std::string &tag) {
    return GlobalModData.instance.get(tag);
  }

  static std::string create() { return GlobalModData.instance.create(); }

  static KahluaTable create(const std::string &tag) {
    return GlobalModData.instance.create(tag);
  }

  static KahluaTable remove(const std::string &tag) {
    return GlobalModData.instance.remove(tag);
  }

  static void add(const std::string &tag, KahluaTable table) {
    GlobalModData.instance.add(tag, table);
  }

  static void transmit(const std::string &tag) {
    GlobalModData.instance.transmit(tag);
  }

  static void request(const std::string &tag) {
    GlobalModData.instance.request(tag);
  }
}
} // namespace moddata
} // namespace world
} // namespace zombie
