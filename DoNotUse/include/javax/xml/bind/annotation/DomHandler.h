#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/transform/Result.h"
#include "javax/xml/transform/Source.h"

namespace javax {
namespace xml {
namespace bind {
namespace annotation {


class DomHandler {
public:
    virtual ~DomHandler() = default;
    ResultT createUnmarshaller(ValidationEventHandler var1);

    ElementT getElement(ResultT var1);

    Source marshal(ElementT var1, ValidationEventHandler var2);
}
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
