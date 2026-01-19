#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/PredicatedFileWatcher/IPredicatedDataPacketFileWatcherCallback.h"
#include "zombie/PredicatedFileWatcher/IPredicatedFileWatcherCallback.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"

namespace zombie {


class PredicatedFileWatcher {
:
   private Class<T> m_class;
   private IPredicatedDataPacketFileWatcherCallback<T> m_callback;

    PredicatedFileWatcher$GenericPredicatedFileWatcherCallback(Class<T> var1, IPredicatedDataPacketFileWatcherCallback<T> var2) {
      this.m_class = var1;
      this.m_callback = var2;
   }

    void call(std::string_view var1) {
    void* var2;
      try {
         var2 = PZXmlUtil.parse(this.m_class, var1);
      } catch (PZXmlParserException var4) {
         DebugLog.General.error("Exception thrown. " + var4);
         return;
      }

      this.m_callback.call(var2);
   }
}
} // namespace zombie
