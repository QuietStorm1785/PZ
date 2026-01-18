#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PZXmlParserException : public Exception {
public:
public
 PZXmlParserException() {}

public
 PZXmlParserException(const std::string &string) { super(string); }

public
 PZXmlParserException(const std::string &string, std::exception throwable) {
 super(string, throwable);
 }

public
 PZXmlParserException(std::exception throwable) { super(throwable); }

 std::string toString() {
 std::string string0 = super.toString();
 std::string string1 = string0;
 std::exception throwable = this->getCause();
 if (throwable != nullptr) {
 string1 = string0 + System.lineSeparator() +
 " Caused by:" + System.lineSeparator() + " " +
 throwable.toString();
 }

 return string1;
 }
}
} // namespace util
} // namespace zombie
