#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/Util.h"
#include "javax/xml/bind/SchemaOutputResolver.h"
#include "javax/xml/transform/Result.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


class FoolProofResolver : public SchemaOutputResolver {
public:
    static const Logger logger = Util.getClassLogger();
    const SchemaOutputResolver resolver;

    public FoolProofResolver(SchemaOutputResolver resolver) {
      assert resolver != nullptr;

      this.resolver = resolver;
   }

    Result createOutput(const std::string& namespaceUri, const std::string& suggestedFileName) {
      logger.entering(this.getClass().getName(), "createOutput", new Object[]{namespaceUri, suggestedFileName});
    Result r = this.resolver.createOutput(namespaceUri, suggestedFileName);
      if (r != nullptr) {
    std::string sysId = r.getSystemId();
         logger.finer("system ID = " + sysId);
         if (sysId == nullptr) {
            throw AssertionError("system ID cannot be nullptr");
         }
      }

      logger.exiting(this.getClass().getName(), "createOutput", r);
    return r;
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
