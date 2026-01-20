#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ContentModelContainer.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


class Tree {
public:
    const Tree body;

   private Tree$Repeated(Tree body) {
      this.body = body;
   }

    bool isNullable() {
      return this.body.isNullable();
   }

    Tree makeRepeated(bool really) {
    return this;
   }

    void write(ContentModelContainer parent, bool isOptional, bool repeated) {
      this.body.write(parent, isOptional, true);
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
