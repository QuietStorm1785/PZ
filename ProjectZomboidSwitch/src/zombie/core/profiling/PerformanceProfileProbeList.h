#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/profiling/PerformanceProfileProbeList/Constructor.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace profiling {


class PerformanceProfileProbeList {
public:
    const std::string m_prefix;
   const Probe[] layers;

   public static PerformanceProfileProbeList<PerformanceProfileProbe> construct(std::string var0, int var1) {
      return new PerformanceProfileProbeList<>(var0, var1, PerformanceProfileProbe.class, PerformanceProfileProbe::new);
   }

   public static <Probe : public PerformanceProfileProbe> PerformanceProfileProbeList<Probe> construct(
      std::string var0, int var1, Class<Probe> var2, Constructor<Probe> var3
   ) {
      return new PerformanceProfileProbeList<>(var0, var1, var2, var3);
   }

    protected PerformanceProfileProbeList(const std::string& var1, int var2, Class<Probe> var3, Constructor<Probe> var4) {
      this.m_prefix = var1;
      this.layers = (Probe[])PZArrayUtil.newInstance(var3, var2 + 1);

      for (int var5 = 0; var5 < var2; var5++) {
         this.layers[var5] = (Probe)var4.get(var1 + "_" + var5);
      }

      this.layers[var2] = (Probe)var4.get(var1 + "_etc");
   }

    int count() {
      return this.layers.length;
   }

    Probe at(int var1) {
      return var1 < this.count() ? this.layers[var1] : this.layers[this.count() - 1];
   }

    Probe start(int var1) {
    PerformanceProfileProbe var2 = this.at(var1);
      var2.start();
      return (Probe)var2;
   }
}
} // namespace profiling
} // namespace core
} // namespace zombie
