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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GenericNameWeightRecordingFrame : public GenericNameValueRecordingFrame {
public:
 private float[] m_weights = new float[0];

 public GenericNameWeightRecordingFrame(const std::string& string) {
 super(string, "_weights");
 }

 void onColumnAdded() {
 this->m_weights = PZArrayUtil.add(this->m_weights, 0.0F);
 }

 void logWeight(const std::string& string, int int1, float float0) {
 int int0 = this->getOrCreateColumn(string, int1);
 this->m_weights[int0] = this->m_weights[int0] + float0;
 }

 int getOrCreateColumn(const std::string& string2, int int0) {
 std::string string0 = int0 != 0 ? int0 + ":" : "";
 std::string string1 = String.format("%s%s", string0, string2);
 int int1 = super.getOrCreateColumn(string1);
 if (this->m_weights[int1] == 0.0F) {
 return int1;
 } else {
 int int2 = 1;

 while (true) {
 std::string string3 = String.format("%s%s-%d", string0, string2, int2);
 int1 = super.getOrCreateColumn(string3);
 if (this->m_weights[int1] == 0.0F) {
 return int1;
 }

 int2++;
 }
 }
 }

 float getWeightAt(int int0) {
 return this->m_weights[int0];
 }

 std::string getValueAt(int int0) {
 return String.valueOf(this->getWeightAt(int0);
 }

 void reset() {
 int int0 = 0;

 for (int int1 = this->m_weights.length; int0 < int1; int0++) {
 this->m_weights[int0] = 0.0F;
 }
 }
}
} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
