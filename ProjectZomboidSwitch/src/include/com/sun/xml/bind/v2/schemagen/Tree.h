#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/schemagen/Tree/Group.h"
#include "com/sun/xml/bind/v2/schemagen/Tree/Optional.h"
#include "com/sun/xml/bind/v2/schemagen/Tree/Repeated.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/ContentModelContainer.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/Occurs.h"
#include "com/sun/xml/bind/v2/schemagen/xmlschema/TypeDefParticle.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


class Tree {
public:
    Tree makeOptional(bool really) {
      return (Tree)(really ? std::make_shared<Optional>(this, nullptr) : this);
   }

    Tree makeRepeated(bool really) {
      return (Tree)(really ? std::make_shared<Repeated>(this, nullptr) : this);
   }

    static Tree makeGroup(GroupKind kind, List<Tree> children) {
      if (children.size() == 1) {
         return children.get(0);
      } else {
         List<Tree> normalizedChildren = new std::vector<>(children.size());

    for (auto& t : children)            if (dynamic_cast<Group*>(t) != nullptr) {
    Group g = (Group)t;
               if (Group.access$200(g) == kind) {
                  normalizedChildren.addAll(Arrays.asList(Group.access$300(g)));
                  continue;
               }
            }

            normalizedChildren.push_back(t);
         }

         return std::make_shared<Group>(kind, normalizedChildren.toArray(new Tree[normalizedChildren.size()]), nullptr);
      }
   }

   abstract boolean isNullable();

    bool canBeTopLevel() {
    return false;
   }

   protected abstract void write(ContentModelContainer var1, boolean var2, boolean var3);

    void write(TypeDefParticle ct) {
      if (this.canBeTopLevel()) {
         this.write((ContentModelContainer)ct._cast(ContentModelContainer.class), false, false);
      } else {
    std::make_shared<Group>(new Tree[]{this});
      }
   }

    void writeOccurs(Occurs o, bool isOptional, bool repeated) {
      if (isOptional) {
         o.minOccurs(0);
      }

      if (repeated) {
         o.maxOccurs("unbounded");
      }
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
