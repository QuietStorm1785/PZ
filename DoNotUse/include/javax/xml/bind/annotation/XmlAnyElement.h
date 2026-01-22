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
namespace annotation {


public @interface XmlAnyElement {
    bool lax();

   Class<? : public DomHandler> value() default W3CDomHandler.class;
}
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
