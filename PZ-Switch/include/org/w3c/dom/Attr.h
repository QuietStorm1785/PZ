#ifndef ORG_W3C_DOM_ATTR_H
#define ORG_W3C_DOM_ATTR_H

#include "org/w3c/dom/Node.h"

namespace org { namespace w3c { namespace dom {

class Attr : public Node {
public:
 const char* getName() const { return ""; }
};

}}} // namespace org::w3c::dom

#endif // ORG_W3C_DOM_ATTR_H
