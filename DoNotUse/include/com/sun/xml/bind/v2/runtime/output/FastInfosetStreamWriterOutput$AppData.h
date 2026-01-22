#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/output/FastInfosetStreamWriterOutput/TablesPerJAXBContext.h"
#include "javax/xml/bind/JAXBContext.h"
#include "org/jvnet/fastinfoset/VocabularyApplicationData.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class FastInfosetStreamWriterOutput {
public:
   const Map<JAXBContext, TablesPerJAXBContext> contexts = std::make_unique<WeakHashMap<>>();
   const Collection<TablesPerJAXBContext> collectionOfContexts = this.contexts.values();

    void clear() {
      for (TablesPerJAXBContext c : this.collectionOfContexts) {
         c.requireClearTables();
      }
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
