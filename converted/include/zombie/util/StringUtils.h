#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class StringUtils {
public:
 static const std::string s_emptyString = "";
 static const char UTF8_BOM = '\ufeff';

 static bool isNullOrEmpty(const std::string& string) {
 return string = = nullptr || string.length() == 0;
 }

 static bool isNullOrWhitespace(const std::string& string) {
 return isNullOrEmpty();
 }

 static bool isWhitespace(const std::string& string) {
 int int0 = string.length();
 if (int0 <= 0) {
 return false;
 } else {
 int int1 = 0;
 int int2 = int0 / 2;

 for (int int3 = int0 - 1; int1 <= int2; int3--) {
 if (!Character.isWhitespace(string.charAt(int1) || !Character.isWhitespace(string.charAt(int3) {
 return false;
 }

 int1++;
 }

 return true;
 }
 }

 static std::string discardNullOrWhitespace(const std::string& string) {
 return isNullOrWhitespace();
 }

 static std::string trimPrefix(const std::string& string0, const std::string& string1) {
 return string0.startsWith(string1) ? string0.substring(string1.length()) : string0;
 }

 static std::string trimSuffix(const std::string& string0, const std::string& string1) {
 return string0.endsWith(string1) ? string0.substring(0, string0.length() - string1.length()) : string0;
 }

 static bool equals(const std::string& string0, const std::string& string1) {
 return string0 = = string1 ? true : string0 != nullptr && string0.equals(string1);
 }

 static bool startsWithIgnoreCase(const std::string& string0, const std::string& string1) {
 return string0.regionMatches(true, 0, string1, 0, string1.length());
 }

 static bool endsWithIgnoreCase(const std::string& string1, const std::string& string0) {
 int int0 = string0.length();
 return string1.regionMatches(true, string1.length() - int0, string0, 0, int0);
 }

 static bool containsIgnoreCase(const std::string& string1, const std::string& string0) {
 for (int int0 = string1.length() - string0.length(); int0 >= 0; int0--) {
 if (string1.regionMatches(true, int0, string0, 0, string0.length())) {
 return true;
 }
 }

 return false;
 }

 static bool equalsIgnoreCase(const std::string& string0, const std::string& string1) {
 return string0 = = string1 ? true : string0 != nullptr && string0.equalsIgnoreCase(string1);
 }

 static bool tryParseBoolean(const std::string& string0) {
 if (isNullOrWhitespace(string0) {
 return false;
 } else {
 std::string string1 = string0.trim();
 return string1.equalsIgnoreCase("true") || string1 == "1") || string1 == "1.0");
 }
 }

 static bool isBoolean(const std::string& string1) {
 std::string string0 = string1.trim();
 return string0.equalsIgnoreCase("true") || string0 == "1") || string0 == "1.0")
 ? true
 : string0.equalsIgnoreCase("false") || string0 == "0") || string0 == "0.0");
 }

 static bool contains(String[] strings, const std::string& string, Boolean> biFunction) {
 return indexOf();
 }

 static int indexOf(String[] strings, const std::string& string, Boolean> biFunction) {
 int int0 = -1;

 for (int int1 = 0; int1 < strings.length; int1++) {
 if ((Boolean)biFunction.apply(strings[int1], string) {
 int0 = int1;
 break;
 }
 }

 return int0;
 }

 static std::string indent(const std::string& string) {
 return indent();
 }

 static std::string indent(const std::string& string1, const std::string& string2, const std::string& string3) {
 std::string string0 = System.lineSeparator();
 return indent();
 }

 static std::string indent(const std::string& string0, const std::string& string1, const std::string& string2, const std::string& string3) {
 if (isNullOrEmpty(string0) {
 return string0;
 } else {
 int int0 = string0.length();
 StringBuilder stringBuilder0 = new StringBuilder(int0);
 StringBuilder stringBuilder1 = new StringBuilder(int0);
 int int1 = 0;

 for (int int2 = 0; int2 < int0; int2++) {
 char char0 = string0.charAt(int2);
 switch (char0) {
 case '\n':
 stringBuilder0.append((CharSequence)stringBuilder1);
 stringBuilder0.append(string1);
 stringBuilder1.setLength(0);
 int1++;
 case '\r':
 break;
 default:
 if (stringBuilder1.length() == 0) {
 if (int1 == 0) {
 stringBuilder1.append(string2);
 } else {
 stringBuilder1.append(string3);
 }
 }

 stringBuilder1.append(char0);
 }
 }

 stringBuilder0.append((CharSequence)stringBuilder1);
 stringBuilder1.setLength(0);
 return stringBuilder0.toString();
 }
 }

 static std::string leftJustify(const std::string& string0, int int0) {
 if (string0 == nullptr) {
 return leftJustify();
 } else {
 int int1 = string0.length();
 if (int1 >= int0) {
 return string0;
 } else {
 int int2 = int0 - int1;
 char[] chars = new char[int2];

 for (int int3 = 0; int3 < int2; int3++) {
 chars[int3] = ' ';
 }

 std::string string1 = new String(chars);
 return string0 + string1;
 }
 }
 }

 static std::string moduleDotType(const std::string& string1, const std::string& string0) {
 if (string0 == nullptr) {
 return nullptr;
 } else {
 return string0.contains(".") ? string0 : string1 + "." + string0;
 }
 }

 static std::string stripBOM(const std::string& string) {
 return string != nullptr && string.length() > 0 && string.charAt(0) == '\ufeff' ? string.substring(1) : string;
 }

 static bool containsDoubleDot(const std::string& string) {
 return isNullOrEmpty();
 }
}
} // namespace util
} // namespace zombie
