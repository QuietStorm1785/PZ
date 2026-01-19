#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {


class ZomboidFileSystem {
:
    virtual ~ZomboidFileSystem() = default;
    void visit(File var1, std::string_view var2);
}
} // namespace zombie
