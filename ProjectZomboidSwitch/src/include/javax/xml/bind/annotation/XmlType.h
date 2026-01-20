#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlType/DEFAULT.h"

namespace javax {
namespace xml {
namespace bind {
namespace annotation {


public @interface XmlType {
    std::string name();

   std::string[] propOrder() default {""};

    std::string namespace();

    Class factoryClass();

    std::string factoryMethod();
}
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
