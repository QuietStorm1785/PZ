#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class ILuaVariableSource {
public:
    virtual ~ILuaVariableSource() = default;
    std::string GetVariable(const std::string& var1);

    void SetVariable(const std::string& var1, const std::string& var2);

    void ClearVariable(const std::string& var1);
}
} // namespace characters
} // namespace zombie
