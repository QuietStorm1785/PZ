#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/localization/LocalizableMessageFactory/ResourceBundleSupplier.h"
#include <algorithm>

namespace com {
namespace sun {
namespace istack {
namespace localization {


class LocalizableMessage {
public:
    const std::string _bundlename;
    const ResourceBundleSupplier _rbSupplier;
    const std::string _key;
   private const Object[] _args;

    public LocalizableMessage(const std::string& bundlename, const std::string& key, Object... args) {
      this(bundlename, nullptr, key, args);
   }

    public LocalizableMessage(const std::string& bundlename, ResourceBundleSupplier rbSupplier, const std::string& key, Object... args) {
      this._bundlename = bundlename;
      this._rbSupplier = rbSupplier;
      this._key = key;
      if (args == nullptr) {
         args = new Object[0];
      }

      this._args = args;
   }

    std::string getKey() {
      return this._key;
   }

   public Object[] getArguments() {
      return Arrays.copyOf(this._args, this._args.length);
   }

    std::string getResourceBundleName() {
      return this._bundlename;
   }

    ResourceBundle getResourceBundle(Locale locale) {
      return this._rbSupplier == nullptr ? nullptr : this._rbSupplier.getResourceBundle(locale);
   }
}
} // namespace localization
} // namespace istack
} // namespace sun
} // namespace com
