#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/localization/LocalizableMessageFactory/ResourceBundleSupplier.h"

namespace com {
namespace sun {
namespace istack {
namespace localization {


class LocalizableMessageFactory {
public:
    const std::string _bundlename;
    const ResourceBundleSupplier _rbSupplier;

    public LocalizableMessageFactory(const std::string& bundlename) {
      this._bundlename = bundlename;
      this._rbSupplier = nullptr;
   }

    public LocalizableMessageFactory(const std::string& bundlename, ResourceBundleSupplier rbSupplier) {
      this._bundlename = bundlename;
      this._rbSupplier = rbSupplier;
   }

    Localizable getMessage(const std::string& key, Object... args) {
      return std::make_shared<LocalizableMessage>(this._bundlename, this._rbSupplier, key, args);
   }
}
} // namespace localization
} // namespace istack
} // namespace sun
} // namespace com
