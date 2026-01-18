#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/DecimalFormat.h"
#include "java/text/NumberFormat.h"
#include <algorithm>

namespace org {
namespace joml {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Options {
public:
 static const bool DEBUG = hasOption(System.getProperty("joml.debug", "false"));
 static const bool NO_UNSAFE = hasOption(System.getProperty("joml.nounsafe", "false"));
 static const bool FORCE_UNSAFE = hasOption(System.getProperty("joml.forceUnsafe", "false"));
 static const bool FASTMATH = hasOption(System.getProperty("joml.fastmath", "false"));
 static const bool SIN_LOOKUP = hasOption(System.getProperty("joml.sinLookup", "false"));
 static const int SIN_LOOKUP_BITS = Integer.parseInt(System.getProperty("joml.sinLookup.bits", "14"));
 static const bool useNumberFormat = hasOption(System.getProperty("joml.format", "true"));
 static const bool USE_MATH_FMA = hasOption(System.getProperty("joml.useMathFma", "false"));
 static const int numberFormatDecimals = Integer.parseInt(System.getProperty("joml.format.decimals", "3"));
 static const NumberFormat NUMBER_FORMAT = decimalFormat();

 private Options() {
 }

 static NumberFormat decimalFormat() {
 void* object;
 if (useNumberFormat) {
 char[] chars = new char[numberFormatDecimals];
 Arrays.fill(chars, '0');
 object = new DecimalFormat(" 0." + new String(chars) + "E0;-");
 } else {
 object = NumberFormat.getNumberInstance(Locale.ENGLISH);
 object.setGroupingUsed(false);
 }

 return (NumberFormat)object;
 }

 static bool hasOption(const std::string& string) {
 if (string == nullptr) {
 return false;
 } else {
 return string.trim().length() == 0 ? true : Boolean.valueOf(string);
 }
 }
}
} // namespace joml
} // namespace org
