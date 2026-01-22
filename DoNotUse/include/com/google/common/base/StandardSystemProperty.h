#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


enum class StandardSystemProperty {
   JAVA_VERSION("java.version"),
   JAVA_VENDOR("java.vendor"),
   JAVA_VENDOR_URL("java.vendor.url"),
   JAVA_HOME("java.home"),
   JAVA_VM_SPECIFICATION_VERSION("java.vm.specification.version"),
   JAVA_VM_SPECIFICATION_VENDOR("java.vm.specification.vendor"),
   JAVA_VM_SPECIFICATION_NAME("java.vm.specification.name"),
   JAVA_VM_VERSION("java.vm.version"),
   JAVA_VM_VENDOR("java.vm.vendor"),
   JAVA_VM_NAME("java.vm.name"),
   JAVA_SPECIFICATION_VERSION("java.specification.version"),
   JAVA_SPECIFICATION_VENDOR("java.specification.vendor"),
   JAVA_SPECIFICATION_NAME("java.specification.name"),
   JAVA_CLASS_VERSION("java.class.version"),
   JAVA_CLASS_PATH("java.class.path"),
   JAVA_LIBRARY_PATH("java.library.path"),
   JAVA_IO_TMPDIR("java.io.tmpdir"),
   JAVA_COMPILER("java.compiler"),
   JAVA_EXT_DIRS("java.ext.dirs"),
   OS_NAME("os.name"),
   OS_ARCH("os.arch"),
   OS_VERSION("os.version"),
   FILE_SEPARATOR("file.separator"),
   PATH_SEPARATOR("path.separator"),
   LINE_SEPARATOR("line.separator"),
   USER_NAME("user.name"),
   USER_HOME("user.home"),
   USER_DIR("user.dir");

    const std::string key;

    private StandardSystemProperty(const std::string& key) {
      this.key = key;
   }

    std::string key() {
      return this.key;
   }

    std::string value() {
      return System.getProperty(this.key);
   }

    std::string toString() {
      return this.key() + "=" + this.value();
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
