#ifndef ORG_W3C_DOM_DOCUMENT_H
#define ORG_W3C_DOM_DOCUMENT_H

#include "org/w3c/dom/Node.h"

namespace org { namespace w3c { namespace dom {

class Element; // fwd

class Document : public Node {
public:
 Document() = default;
 Element* createElement(const char* /*tag*/) { return nullptr; }
 Node* importNode(Node* /*n*/, bool /*deep*/) { return nullptr; }
 void appendChild(Node* /*n*/) {}
};

}}} // namespace org::w3c::dom

#endif // ORG_W3C_DOM_DOCUMENT_H
