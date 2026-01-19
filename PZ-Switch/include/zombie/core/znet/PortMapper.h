#pragma once
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PortMapper {
public:
 static std::string externalAddress = nullptr;

 static void startup() {}

 static void shutdown() { _cleanup(); }

 static bool discover() {
 _discover();
 return _igd_found();
 }

 static bool igdFound() { return _igd_found(); }

 static bool addMapping(int int0, int int1, std::string_view string0,
 std::string_view string1, int int2) {
 return addMapping();
 }

 static bool addMapping(int int0, int int1, std::string_view string0,
 std::string_view string1, int int2, bool boolean1) {
 bool boolean0 = _add_mapping(int0, int1, string0, string1, int2, boolean1);
 if (!boolean0 && int2 != 0) {
 DebugLog.log(DebugType.Network,
 "Failed to add port mapping, retrying with zero lease time");
 boolean0 = _add_mapping(int0, int1, string0, string1, 0, boolean1);
 }

 return boolean0;
 }

 static bool removeMapping(int int0, std::string_view string) {
 return _remove_mapping();
 }

 static void fetchMappings() { _fetch_mappings(); }

 static int numMappings() { return _num_mappings(); }

 static PortMappingEntry getMapping(int int0) { return _get_mapping(); }

 static std::string getGatewayInfo() { return _get_gateway_info(); }

public
 static String getExternalAddress(boolean boolean0) {
 if (boolean0 || externalAddress.empty()) {
 externalAddress = _get_external_address();
 }

 return externalAddress;
 }

 static std::string getExternalAddress() { return getExternalAddress(); }

private
 static void _discover();

private
 static void _cleanup();

private
 static boolean _igd_found();

private
 static boolean _add_mapping(int var0, int var1, String var2,
 String var3, int var4, boolean var5);

private
 static boolean _remove_mapping(int var0, String var1);

private
 static void _fetch_mappings();

private
 static int _num_mappings();

private
 static PortMappingEntry _get_mapping(int var0);

private
 static String _get_gateway_info();

private
 static String _get_external_address();
}
} // namespace znet
} // namespace core
} // namespace zombie
