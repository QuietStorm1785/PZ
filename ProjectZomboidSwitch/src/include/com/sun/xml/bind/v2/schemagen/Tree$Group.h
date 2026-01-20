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


class Tree {
public:
    const GroupKind kind;
   private const Tree[] children;

   private Tree$Group(GroupKind kind, Tree... children) {
      this.kind = kind;
      this.children = children;
   }

    bool canBeTopLevel() {
    return true;
   }

    bool isNullable() {
      if (this.kind == GroupKind.CHOICE) {
         for (Tree t : this.children) {
            if (t.isNullable()) {
    return true;
            }
         }

    return false;
      } else {
         for (Tree tx : this.children) {
            if (!tx.isNullable()) {
    return false;
            }
         }

    return true;
      }
   }

    void write(ContentModelContainer parent, bool isOptional, bool repeated) {
    Particle c = this.kind.write(parent);
      this.writeOccurs(c, isOptional, repeated);

      for (Tree child : this.children) {
         child.write(c, false, false);
      }
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
