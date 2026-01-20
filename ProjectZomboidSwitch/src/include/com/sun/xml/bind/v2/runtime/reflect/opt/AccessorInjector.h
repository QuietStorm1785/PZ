#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/Util.h"
#include "com/sun/xml/bind/v2/bytecode/ClassTailor.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {
namespace opt {


class AccessorInjector {
public:
    static const Logger logger = Util.getClassLogger();
    static const bool noOptimize = Util.getSystemProperty(ClassTailor.class.getName() + ".noOptimize") != nullptr;
    static const ClassLoader CLASS_LOADER;

   private static byte[] tailor(std::string templateClassName, std::string newClassName, std::string... replacements) {
    InputStream resource;
      if (CLASS_LOADER != nullptr) {
         resource = CLASS_LOADER.getResourceAsStream(templateClassName + ".class");
      } else {
         resource = ClassLoader.getSystemResourceAsStream(templateClassName + ".class");
      }

    return resource = = nullptr ? nullptr : ClassTailor.tailor(resource, templateClassName, newClassName, replacements);
   }

   static {
      if (noOptimize) {
         logger.info("The optimized code generation is disabled");
      }

      CLASS_LOADER = SecureLoader.getClassClassLoader(AccessorInjector.class);
   }
}
} // namespace opt
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
