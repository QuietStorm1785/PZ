#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace javax {
namespace activation {

class DataContentHandlerFactory {
public:
    virtual ~DataContentHandlerFactory() = default;
    DataContentHandler createDataContentHandler(const std::string& var1);
}
} // namespace activation
} // namespace javax
