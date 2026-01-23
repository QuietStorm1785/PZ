
#pragma once
#include <cstdint>
#include <type_traits>
#include <memory>
#include <vector>

namespace zombie {
namespace LuaCpp {

// LuaNumberConverter provides static helpers for converting between Lua numbers (double)
// and various C++ numeric types, using templates for type safety.
class LuaNumberConverter {
public:
    // Convert a Lua number (double) to a C++ numeric type (int, float, etc.).
    template<typename T>
    static T fromLuaToCpp(double value) {
        if constexpr (std::is_same_v<T, int64_t>) return static_cast<int64_t>(value);
        if constexpr (std::is_same_v<T, int>) return static_cast<int>(value);
        if constexpr (std::is_same_v<T, float>) return static_cast<float>(value);
        if constexpr (std::is_same_v<T, uint8_t>) return static_cast<uint8_t>(value);
        if constexpr (std::is_same_v<T, char>) return static_cast<char>(value);
        if constexpr (std::is_same_v<T, int16_t>) return static_cast<int16_t>(value);
        return static_cast<T>(value);
    }

    // Convert a C++ numeric type to a Lua number (double).
    template<typename T>
    static double toLuaFromCpp(T value) {
        return static_cast<double>(value);
    }
};

} // namespace LuaCpp
} // namespace zombie
