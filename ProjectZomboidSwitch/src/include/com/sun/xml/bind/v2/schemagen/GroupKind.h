#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ContentModelContainer.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/Particle.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


enum class GroupKind {
   ALL("all"),
   SEQUENCE("sequence"),
   CHOICE("choice");

    const std::string name;

    private GroupKind(const std::string& name) {
      this.name = name;
   }

    Particle write(ContentModelContainer parent) {
      return (Particle)parent._element(this.name, Particle.class);
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
