#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace javax {
namespace xml {
namespace bind {


class JAXBContextFactory {
public:
    virtual ~JAXBContextFactory() = default;
    JAXBContext createContext(Class<?>[] var1, ?> var2);

    JAXBContext createContext(const std::string& var1, ClassLoader var2, ?> var3);
}
} // namespace bind
} // namespace xml
} // namespace javax
