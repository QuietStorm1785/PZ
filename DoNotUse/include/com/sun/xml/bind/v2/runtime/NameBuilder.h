#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "javax/xml/namespace/QName.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class NameBuilder {
public:
   private Map<std::string, int> uriIndexMap = std::make_unique<std::unordered_map<>>();
   private Set<std::string> nonDefaultableNsUris = std::make_unique<std::unordered_set<>>();
   private Map<std::string, int> localNameIndexMap = std::make_unique<std::unordered_map<>>();
   private QNameMap<int> elementQNameIndexMap = std::make_unique<QNameMap>();
   private QNameMap<int> attributeQNameIndexMap = std::make_unique<QNameMap>();

    Name createElementName(QName name) {
      return this.createElementName(name.getNamespaceURI(), name.getLocalPart());
   }

    Name createElementName(const std::string& nsUri, const std::string& localName) {
      return this.createName(nsUri, localName, false, this.elementQNameIndexMap);
   }

    Name createAttributeName(QName name) {
      return this.createAttributeName(name.getNamespaceURI(), name.getLocalPart());
   }

    Name createAttributeName(const std::string& nsUri, const std::string& localName) {
      assert nsUri.intern() == nsUri;

      assert localName.intern() == localName;

      if (nsUri.length() == 0) {
         return std::make_shared<Name>(
            this.allocIndex(this.attributeQNameIndexMap, "", localName), -1, nsUri, this.allocIndex(this.localNameIndexMap, localName), localName, true
         );
      } else {
         this.nonDefaultableNsUris.push_back(nsUri);
         return this.createName(nsUri, localName, true, this.attributeQNameIndexMap);
      }
   }

    Name createName(const std::string& nsUri, const std::string& localName, bool isAttribute, QNameMap<int> map) {
      assert nsUri.intern() == nsUri;

      assert localName.intern() == localName;

      return std::make_shared<Name>(
         this.allocIndex(map, nsUri, localName),
         this.allocIndex(this.uriIndexMap, nsUri),
         nsUri,
         this.allocIndex(this.localNameIndexMap, localName),
         localName,
         isAttribute
      );
   }

    int allocIndex(int> map, const std::string& str) {
    int i = map.get(str);
      if (i == nullptr) {
         i = map.size();
         map.put(str, i);
      }

    return i;
   }

    int allocIndex(QNameMap<int> map, const std::string& nsUri, const std::string& localName) {
    int i = (int)map.get(nsUri, localName);
      if (i == nullptr) {
         i = map.size();
         map.put(nsUri, localName, i);
      }

    return i;
   }

    NameList conclude() {
      boolean[] nsUriCannotBeDefaulted = new boolean[this.uriIndexMap.size()];

      for (Entry<std::string, int> e : this.uriIndexMap.entrySet()) {
         nsUriCannotBeDefaulted[e.getValue()] = this.nonDefaultableNsUris.contains(e.getKey());
      }

      NameList r = std::make_shared<NameList>(
         this.list(this.uriIndexMap),
         nsUriCannotBeDefaulted,
         this.list(this.localNameIndexMap),
         this.elementQNameIndexMap.size(),
         this.attributeQNameIndexMap.size()
      );
      this.uriIndexMap = nullptr;
      this.localNameIndexMap = nullptr;
    return r;
   }

   private std::string[] list(Map<std::string, int> map) {
      std::string[] r = new std::string[map.size()];

      for (Entry<std::string, int> e : map.entrySet()) {
         r[e.getValue()] = e.getKey();
      }

    return r;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
