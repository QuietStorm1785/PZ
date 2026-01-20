#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/adapters/XmlJavaTypeAdapter/DEFAULT.h"

namespace javax {
namespace xml {
namespace bind {
namespace annotation {
namespace adapters {


public @interface XmlJavaTypeAdapter {
   Class<? : public XmlAdapter> value();

    Class type();
}
} // namespace adapters
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
