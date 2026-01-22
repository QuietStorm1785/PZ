#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
namespace debug {


class GenericNameWeightRecordingFrame : public GenericNameValueRecordingFrame {
public:
   private float[] m_weights = new float[0];

    public GenericNameWeightRecordingFrame(const std::string& var1) {
      super(var1, "_weights");
   }

    void onColumnAdded() {
      this.m_weights = PZArrayUtil.push_back(this.m_weights, 0.0F);
   }

    void logWeight(const std::string& var1, int var2, float var3) {
    int var4 = this.getOrCreateColumn(var1, var2);
      this.m_weights[var4] = this.m_weights[var4] + var3;
   }

    int getOrCreateColumn(const std::string& var1, int var2) {
    std::string var3 = var2 != 0 ? var2 + ":" : "";
    std::string var4 = std::string.format("%s%s", var3, var1);
    int var5 = super.getOrCreateColumn(var4);
      if (this.m_weights[var5] == 0.0F) {
    return var5;
      } else {
    int var6 = 1;

         while (true) {
    std::string var7 = std::string.format("%s%s-%d", var3, var1, var6);
            var5 = super.getOrCreateColumn(var7);
            if (this.m_weights[var5] == 0.0F) {
    return var5;
            }

            var6++;
         }
      }
   }

    float getWeightAt(int var1) {
      return this.m_weights[var1];
   }

    std::string getValueAt(int var1) {
      return std::string.valueOf(this.getWeightAt(var1));
   }

    void reset() {
    int var1 = 0;

      for (int var2 = this.m_weights.length; var1 < var2; var1++) {
         this.m_weights[var1] = 0.0F;
      }
   }
}
} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
