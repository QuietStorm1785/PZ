#ifndef ORG_W3C_DOM_ELEMENT_H
#define ORG_W3C_DOM_ELEMENT_H

#include "org/w3c/dom/Node.h"

namespace org { namespace w3c { namespace dom {

class Element : public Node {
public:
 Element() = default;
 const char* getTagName() const { return ""; }
 const char* getAttribute(const char* /*name*/) const { return ""; }
 void setAttributeNode(Node* /*attr*/) {}
};

}}} // namespace org::w3c::dom

#endif // ORG_W3C_DOM_ELEMENT_H
