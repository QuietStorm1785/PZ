#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace org {
namespace joml {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class ConfigurationException : public RuntimeException {
public:
 static const long serialVersionUID = -7832356906364070687L;

 public ConfigurationException(const std::string& string, std::exception throwable) {
 super(string, throwable);
 }
}
} // namespace joml
} // namespace org
