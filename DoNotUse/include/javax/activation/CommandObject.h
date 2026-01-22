#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class CommandObject {
public:
    virtual ~CommandObject() = default;
    void setCommandContext(const std::string& var1, DataHandler var2);
}
} // namespace activation
} // namespace javax
