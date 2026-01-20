#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace marshaller {

class NamespacePrefixMapper {
public:
   private static const std::string[] EMPTY_STRING = new std::string[0];

   public abstract std::string getPreferredPrefix(std::string var1, std::string var2, boolean var3);

   public std::string[] getPreDeclaredNamespaceUris() {
    return EMPTY_STRING;
   }

   public std::string[] getPreDeclaredNamespaceUris2() {
    return EMPTY_STRING;
   }

   public std::string[] getContextualNamespaceDecls() {
    return EMPTY_STRING;
   }
}
} // namespace marshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
