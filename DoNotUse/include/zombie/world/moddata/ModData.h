#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"

namespace zombie {
namespace world {
namespace moddata {


class ModData {
public:
   private static const std::vector<std::string> temp_list = std::make_unique<std::vector<>>();

   public static std::vector<std::string> getTableNames() {
      GlobalModData.instance.collectTableNames(temp_list);
    return temp_list;
   }

    static bool exists(const std::string& var0) {
      return GlobalModData.instance.exists(var0);
   }

    static KahluaTable getOrCreate(const std::string& var0) {
      return GlobalModData.instance.getOrCreate(var0);
   }

    static KahluaTable get(const std::string& var0) {
      return GlobalModData.instance.get(var0);
   }

    static std::string create() {
      return GlobalModData.instance.create();
   }

    static KahluaTable create(const std::string& var0) {
      return GlobalModData.instance.create(var0);
   }

    static KahluaTable remove(const std::string& var0) {
      return GlobalModData.instance.remove(var0);
   }

    static void add(const std::string& var0, KahluaTable var1) {
      GlobalModData.instance.push_back(var0, var1);
   }

    static void transmit(const std::string& var0) {
      GlobalModData.instance.transmit(var0);
   }

    static void request(const std::string& var0) {
      GlobalModData.instance.request(var0);
   }
}
} // namespace moddata
} // namespace world
} // namespace zombie
