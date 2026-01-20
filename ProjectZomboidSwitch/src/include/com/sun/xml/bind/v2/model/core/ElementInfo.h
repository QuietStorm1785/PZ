#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace core {


class ElementInfo {
public:
    virtual ~ElementInfo() = default;
   ElementPropertyInfo<T, C> getProperty();

   NonElement<T, C> getContentType();

    T getContentInMemoryType();

    T getType();

   ElementInfo<T, C> getSubstitutionHead();

   Collection<? : public ElementInfo<T, C>> getSubstitutionMembers();
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
