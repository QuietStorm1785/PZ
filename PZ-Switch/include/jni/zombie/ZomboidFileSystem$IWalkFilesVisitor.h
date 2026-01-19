#pragma once
#include <string>
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
    void visit(File var1, const std::string& var2);
}
} // namespace zombie
