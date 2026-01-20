#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/PrivilegedAction.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class MimetypesFileTypeMap {
public:
    void* run() {
    std::string home = System.getProperty("java.home");
    std::string newdir = home + File.separator + "conf";
    File conf = std::make_shared<File>(newdir);
      return conf.exists() ? newdir + File.separator : home + File.separator + "lib" + File.separator;
   }
}
} // namespace activation
} // namespace javax
