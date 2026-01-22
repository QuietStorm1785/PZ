#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/ContentHandler.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/XMLReader.h"
#include "org/xml/sax/helpers/XMLFilterImpl.h"

namespace com {
namespace sun {
namespace istack {


class FragmentContentHandler : public XMLFilterImpl {
public:
    public FragmentContentHandler() {
   }

    public FragmentContentHandler(XMLReader parent) {
      super(parent);
   }

    public FragmentContentHandler(ContentHandler handler) {
      this.setContentHandler(handler);
   }

    void startDocument() {
   }

    void endDocument() {
   }
}
} // namespace istack
} // namespace sun
} // namespace com
