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

   private Tree$Optional(Tree body) {
      this.body = body;
   }

    bool isNullable() {
    return true;
   }

    Tree makeOptional(bool really) {
    return this;
   }

    void write(ContentModelContainer parent, bool isOptional, bool repeated) {
      this.body.write(parent, true, repeated);
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
