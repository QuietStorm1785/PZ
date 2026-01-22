#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/MessageFormat.h"
#include <algorithm>

namespace javax {
namespace xml {
namespace bind {


class Messages {
public:
    static const std::string PROVIDER_NOT_FOUND = "ContextFinder.ProviderNotFound";
    static const std::string DEFAULT_PROVIDER_NOT_FOUND = "ContextFinder.DefaultProviderNotFound";
    static const std::string COULD_NOT_INSTANTIATE = "ContextFinder.CouldNotInstantiate";
    static const std::string CANT_FIND_PROPERTIES_FILE = "ContextFinder.CantFindPropertiesFile";
    static const std::string CANT_MIX_PROVIDERS = "ContextFinder.CantMixProviders";
    static const std::string MISSING_PROPERTY = "ContextFinder.MissingProperty";
    static const std::string NO_PACKAGE_IN_CONTEXTPATH = "ContextFinder.NoPackageInContextPath";
    static const std::string NAME_VALUE = "PropertyException.NameValue";
    static const std::string CONVERTER_MUST_NOT_BE_NULL = "DatatypeConverter.ConverterMustNotBeNull";
    static const std::string ILLEGAL_CAST = "JAXBContext.IllegalCast";
    static const std::string ERROR_LOAD_CLASS = "ContextFinder.ErrorLoadClass";
    static const std::string JAXB_CLASSES_NOT_OPEN = "JAXBClasses.notOpen";

    static std::string format(const std::string& property) {
    return format();
   }

    static std::string format(const std::string& property, void* arg1) {
    return format(new Object[]{arg1});
   }

    static std::string format(const std::string& property, void* arg1, void* arg2) {
    return format(new Object[]{arg1);
   }

    static std::string format(const std::string& property, void* arg1, void* arg2, void* arg3) {
    return format(new Object[]{arg1);
   }

    static std::string format(const std::string& property, Object[] args) {
    std::string text = ResourceBundle.getBundle(Messages.class.getName()).getString(property);
      return MessageFormat.format(text, args);
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
