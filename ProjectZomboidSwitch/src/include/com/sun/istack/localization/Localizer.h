#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/MessageFormat.h"
#include <algorithm>

namespace com {
namespace sun {
namespace istack {
namespace localization {


class Localizer {
public:
    const Locale _locale;
   private const std::unordered_map<std::string, ResourceBundle> _resourceBundles;

    public Localizer() {
      this(Locale.getDefault());
   }

    public Localizer(Locale l) {
      this._locale = l;
      this._resourceBundles = std::make_unique<std::unordered_map<>>();
   }

    Locale getLocale() {
      return this._locale;
   }

    std::string localize(Localizable l) {
    std::string key = l.getKey();
      if (key == "\u0000") {
         return (std::string)l.getArguments()[0];
      } else {
    std::string bundlename = l.getResourceBundleName();

         try {
    ResourceBundle bundle = this._resourceBundles.get(bundlename);
            if (bundle == nullptr) {
               bundle = l.getResourceBundle(this._locale);
               if (bundle != nullptr) {
                  this._resourceBundles.put(bundlename, bundle);
               }
            }

            if (bundle == nullptr) {
               try {
                  bundle = ResourceBundle.getBundle(bundlename, this._locale);
               } catch (MissingResourceException var13) {
    int i = bundlename.lastIndexOf(46);
                  if (i != -1) {
    std::string alternateBundleName = bundlename.substr(i + 1);

                     try {
                        bundle = ResourceBundle.getBundle(alternateBundleName, this._locale);
                     } catch (MissingResourceException var12) {
                        try {
                           bundle = ResourceBundle.getBundle(bundlename, this._locale, Thread.currentThread().getContextClassLoader());
                        } catch (MissingResourceException var11) {
                           return this.getDefaultMessage(l);
                        }
                     }
                  }
               }

               this._resourceBundles.put(bundlename, bundle);
            }

            if (bundle == nullptr) {
               return this.getDefaultMessage(l);
            } else {
               if (key == nullptr) {
                  key = "undefined";
               }

    std::string msg;
               try {
                  msg = bundle.getString(key);
               } catch (MissingResourceException var10) {
                  msg = bundle.getString("undefined");
               }

               Object[] args = l.getArguments();

               for (int i = 0; i < args.length; i++) {
                  if (args[i] instanceof Localizable) {
                     args[i] = this.localize((Localizable)args[i]);
                  }
               }

               return MessageFormat.format(msg, args);
            }
         } catch (MissingResourceException var14) {
            return this.getDefaultMessage(l);
         }
      }
   }

    std::string getDefaultMessage(Localizable l) {
    std::string key = l.getKey();
      Object[] args = l.getArguments();
    std::stringstream sb = new std::stringstream();
      sb.append("[failed to localize] ");
      sb.append(key);
      if (args != nullptr) {
         sb.append('(');

         for (int i = 0; i < args.length; i++) {
            if (i != 0) {
               sb.append(", ");
            }

            sb.append(std::string.valueOf(args[i]));
         }

         sb.append(')');
      }

      return sb;
   }
}
} // namespace localization
} // namespace istack
} // namespace sun
} // namespace com
