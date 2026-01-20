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


class ClassInfo {
public:
    virtual ~ClassInfo() = default;
   ClassInfo<T, C> getBaseClass();

    C getClazz();

    std::string getName();

   List<? : public PropertyInfo<T, C>> getProperties();

    bool hasValueProperty();

   PropertyInfo<T, C> getProperty(std::string var1);

    bool hasProperties();

    bool isAbstract();

    bool isOrdered();

    bool isFinal();

    bool hasSubClasses();

    bool hasAttributeWildcard();

    bool inheritsAttributeWildcard();

    bool declaresAttributeWildcard();
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
