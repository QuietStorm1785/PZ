#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace collect {

class Multiset {
public:
    virtual ~Multiset() = default;
    E getElement();

    int getCount();

    bool equals(void* var1);

    int hashCode();

    std::string toString();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
