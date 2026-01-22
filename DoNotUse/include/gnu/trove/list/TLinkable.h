#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace list {


class TLinkable {
public:
    virtual ~TLinkable() = default;
    long serialVersionUID = 997545054865482562L;

    T getNext();

    T getPrevious();

    void setNext(T var1);

    void setPrevious(T var1);
}
} // namespace list
} // namespace trove
} // namespace gnu
