#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"

namespace zombie {
namespace core {
namespace znet {


class PortMapper {
public:
    static std::string externalAddress = nullptr;

    static void startup() {
   }

    static void shutdown() {
      _cleanup();
   }

    static bool discover() {
      _discover();
    return _igd_found();
   }

    static bool igdFound() {
    return _igd_found();
   }

    static bool addMapping(int var0, int var1, const std::string& var2, const std::string& var3, int var4) {
    return addMapping();
   }

    static bool addMapping(int var0, int var1, const std::string& var2, const std::string& var3, int var4, bool var5) {
    bool var6 = _add_mapping(var0, var1, var2, var3, var4, var5);
      if (!var6 && var4 != 0) {
         DebugLog.log(DebugType.Network, "Failed to add port mapping, retrying with zero lease time");
         var6 = _add_mapping(var0, var1, var2, var3, 0, var5);
      }

    return var6;
   }

    static bool removeMapping(int var0, const std::string& var1) {
    return _remove_mapping();
   }

    static void fetchMappings() {
      _fetch_mappings();
   }

    static int numMappings() {
    return _num_mappings();
   }

    static PortMappingEntry getMapping(int var0) {
    return _get_mapping();
   }

    static std::string getGatewayInfo() {
    return _get_gateway_info();
   }

   public static /* synchronized - TODO: add std::mutex */ std::string getExternalAddress(boolean var0) {
      if (var0 || externalAddress == nullptr) {
         externalAddress = _get_external_address();
      }

    return externalAddress;
   }

    static std::string getExternalAddress() {
    return getExternalAddress();
   }

   private static native void _discover();

   private static native void _cleanup();

   private static native boolean _igd_found();

   private static native boolean _add_mapping(int var0, int var1, std::string var2, std::string var3, int var4, boolean var5);

   private static native boolean _remove_mapping(int var0, std::string var1);

   private static native void _fetch_mappings();

   private static native int _num_mappings();

   private static native PortMappingEntry _get_mapping(int var0);

   private static native std::string _get_gateway_info();

   private static native std::string _get_external_address();
}
} // namespace znet
} // namespace core
} // namespace zombie
