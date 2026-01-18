#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace javax {
namespace vecmath {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VecMathI18N {
public:
 static std::string getString(const std::string &string1) {
 std::string string0;
 try {
 string0 = ResourceBundle.getBundle("javax.vecmath.ExceptionStrings")
 .getString(string1);
 } catch (MissingResourceException missingResourceException) {
 System.err.println("VecMathI18N: Error looking up: " + string1);
 string0 = string1;
 }

 return string0;
 }
}
} // namespace vecmath
} // namespace javax
