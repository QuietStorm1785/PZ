#pragma once
#include "zombie/util/list/PZArrayUtil.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace profiling {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PerformanceProfileProbeList {
public:
 const std::string m_prefix;
 Probe[] layers;

public
 static PerformanceProfileProbeList<PerformanceProfileProbe>
 construct(String string, int int0) {
 return new PerformanceProfileProbeList<>(string, int0,
 PerformanceProfileProbe.class,
 PerformanceProfileProbe::new);
 }

public
 static<Probe extends PerformanceProfileProbe>
 PerformanceProfileProbeList<Probe>
 construct(String string, int int0, Class<Probe> clazz,
 PerformanceProfileProbeList.Constructor<Probe> constructor) {
 return new PerformanceProfileProbeList<>(string, int0, clazz, constructor);
 }

protected
 PerformanceProfileProbeList(
 std::string_view string, int int0, Class<Probe> clazz,
 PerformanceProfileProbeList.Constructor<Probe> constructor) {
 this->m_prefix = string;
 this->layers = (Probe[])PZArrayUtil.newInstance(clazz, int0 + 1);

 for (int int1 = 0; int1 < int0; int1++) {
 this->layers[int1] = (Probe)constructor.get(string + "_" + int1);
 }

 this->layers[int0] = (Probe)constructor.get(string + "_etc");
 }

 int count() { return this->layers.length; }

 Probe at(int int0) {
 return int0 < this->count() ? this->layers[int0]
 : this->layers[this->count() - 1];
 }

 Probe start(int int0) {
 PerformanceProfileProbe performanceProfileProbe = this->at(int0);
 performanceProfileProbe.start();
 return (Probe)performanceProfileProbe;
 }

public
 interface Constructor<Probe extends PerformanceProfileProbe> {
 Probe get(std::string_view var1);
 }
}
} // namespace profiling
} // namespace core
} // namespace zombie
