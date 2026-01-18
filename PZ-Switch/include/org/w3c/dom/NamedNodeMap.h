#ifndef ORG_W3C_DOM_NAMEDNODEMAP_H
#define ORG_W3C_DOM_NAMEDNODEMAP_H

#include "org/w3c/dom/Node.h"

namespace org { namespace w3c { namespace dom {

class NamedNodeMap {
public:
 int getLength() const { return 0; }
 Node* item(int /*index*/) const { return nullptr; }
};

}}} // namespace org::w3c::dom

#endif // ORG_W3C_DOM_NAMEDNODEMAP_H
