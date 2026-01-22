#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace interfaces {

class IListBoxItem {
public:
    virtual ~IListBoxItem() = default;
    std::string getLabel();

    std::string getLeftLabel();

    std::string getRightLabel();
}
} // namespace interfaces
} // namespace zombie
