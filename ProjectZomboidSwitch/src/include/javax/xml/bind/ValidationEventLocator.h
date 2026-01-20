#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"
#include "org/w3c/dom/Node.h"

namespace javax {
namespace xml {
namespace bind {


class ValidationEventLocator {
public:
    virtual ~ValidationEventLocator() = default;
    URL getURL();

    int getOffset();

    int getLineNumber();

    int getColumnNumber();

    void* getObject();

    Node getNode();
}
} // namespace bind
} // namespace xml
} // namespace javax
