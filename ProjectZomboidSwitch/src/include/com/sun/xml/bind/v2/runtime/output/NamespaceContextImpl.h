#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/istack/Nullable.h"
#include "com/sun/xml/bind/marshaller/NamespacePrefixMapper.h"
#include "com/sun/xml/bind/v2/runtime/NamespaceContext2.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/output/NamespaceContextImpl/1.h"
#include "com/sun/xml/bind/v2/runtime/output/NamespaceContextImpl/Element.h"
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class NamespaceContextImpl {
public:
    const XMLSerializer owner;
   private std::string[] prefixes = new std::string[4];
   private std::string[] nsUris = new std::string[4];
    int size;
    Element current;
    const Element top;
    NamespacePrefixMapper prefixMapper;
    bool collectionMode;
    static const NamespacePrefixMapper defaultNamespacePrefixMapper = std::make_shared<1>();

    public NamespaceContextImpl(XMLSerializer owner) {
      this.prefixMapper = defaultNamespacePrefixMapper;
      this.owner = owner;
      this.current = this.top = std::make_shared<Element>(this, this, nullptr, nullptr);
      this.put("http://www.w3.org/XML/1998/namespace", "xml");
   }

    void setPrefixMapper(NamespacePrefixMapper mapper) {
      if (mapper == nullptr) {
         mapper = defaultNamespacePrefixMapper;
      }

      this.prefixMapper = mapper;
   }

    NamespacePrefixMapper getPrefixMapper() {
      return this.prefixMapper;
   }

    void reset() {
      this.current = this.top;
      this.size = 1;
      this.collectionMode = false;
   }

    int declareNsUri(const std::string& uri, const std::string& preferedPrefix, bool requirePrefix) {
      preferedPrefix = this.prefixMapper.getPreferredPrefix(uri, preferedPrefix, requirePrefix);
      if (uri.length() == 0) {
         for (int i = this.size - 1; i >= 0; i--) {
            if (this.nsUris[i].length() == 0) {
    return i;
            }

            if (this.prefixes[i].length() == 0) {
               if ($assertionsDisabled || Element.access$100(this.current) == -1 && Element.access$200(this.current) == -1) {
    std::string oldUri = this.nsUris[i];
                  std::string[] knownURIs = this.owner.nameList.namespaceURIs;
                  if (Element.access$300(this.current) <= i) {
                     this.nsUris[i] = "";
    int subst = this.put(oldUri, nullptr);

                     for (int j = knownURIs.length - 1; j >= 0; j--) {
                        if (knownURIs[j] == oldUri)) {
                           this.owner.knownUri2prefixIndexMap[j] = subst;
                           break;
                        }
                     }

                     if (Element.access$400(this.current) != nullptr) {
                        this.current.setTagName(subst, Element.access$400(this.current), this.current.getOuterPeer());
                     }

    return i;
                  }

                  for (int jx = knownURIs.length - 1; jx >= 0; jx--) {
                     if (knownURIs[jx] == oldUri)) {
                        Element.access$102(this.current, i);
                        Element.access$202(this.current, jx);
                        this.owner.knownUri2prefixIndexMap[jx] = this.size;
                        break;
                     }
                  }

                  if (Element.access$400(this.current) != nullptr) {
                     this.current.setTagName(this.size, Element.access$400(this.current), this.current.getOuterPeer());
                  }

                  this.put(this.nsUris[i], nullptr);
                  return this.put("", "");
               }

               throw std::make_unique<AssertionError>();
            }
         }

         return this.put("", "");
      } else {
         for (int i = this.size - 1; i >= 0; i--) {
    std::string p = this.prefixes[i];
            if (this.nsUris[i] == uri) && (!requirePrefix || p.length() > 0)) {
    return i;
            }

            if (p == preferedPrefix)) {
               preferedPrefix = nullptr;
            }
         }

         if (preferedPrefix == nullptr && requirePrefix) {
            preferedPrefix = this.makeUniquePrefix();
         }

         return this.put(uri, preferedPrefix);
      }
   }

    int force(@NotNull std::string, @NotNull std::string) {
      for (int i = this.size - 1; i >= 0; i--) {
         if (this.prefixes[i] == prefix)) {
            if (this.nsUris[i] == uri)) {
    return i;
            }
            break;
         }
      }

      return this.put(uri, prefix);
   }

    int put(@NotNull std::string, @Nullable std::string) {
      if (this.size == this.nsUris.length) {
         std::string[] u = new std::string[this.nsUris.length * 2];
         std::string[] p = new std::string[this.prefixes.length * 2];
         System.arraycopy(this.nsUris, 0, u, 0, this.nsUris.length);
         System.arraycopy(this.prefixes, 0, p, 0, this.prefixes.length);
         this.nsUris = u;
         this.prefixes = p;
      }

      if (prefix == nullptr) {
         if (this.size == 1) {
            prefix = "";
         } else {
            prefix = this.makeUniquePrefix();
         }
      }

      this.nsUris[this.size] = uri;
      this.prefixes[this.size] = prefix;
      return this.size++;
   }

    std::string makeUniquePrefix() {
    std::string prefix = new std::stringstream(5).append("ns").append(this.size);

      while (this.getNamespaceURI(prefix) != nullptr) {
         prefix = prefix + '_';
      }

    return prefix;
   }

    Element getCurrent() {
      return this.current;
   }

    int getPrefixIndex(const std::string& uri) {
      for (int i = this.size - 1; i >= 0; i--) {
         if (this.nsUris[i] == uri)) {
    return i;
         }
      }

      throw std::make_unique<IllegalStateException>();
   }

    std::string getPrefix(int prefixIndex) {
      return this.prefixes[prefixIndex];
   }

    std::string getNamespaceURI(int prefixIndex) {
      return this.nsUris[prefixIndex];
   }

    std::string getNamespaceURI(const std::string& prefix) {
      for (int i = this.size - 1; i >= 0; i--) {
         if (this.prefixes[i] == prefix)) {
            return this.nsUris[i];
         }
      }

    return nullptr;
   }

    std::string getPrefix(const std::string& uri) {
      if (this.collectionMode) {
         return this.declareNamespace(uri, nullptr, false);
      } else {
         for (int i = this.size - 1; i >= 0; i--) {
            if (this.nsUris[i] == uri)) {
               return this.prefixes[i];
            }
         }

    return nullptr;
      }
   }

   public Iterator<std::string> getPrefixes(std::string uri) {
    std::string prefix = this.getPrefix(uri);
    return prefix = = nullptr ? Collections.<std::string>emptySet().iterator() : Collections.singleton(uri).iterator();
   }

    std::string declareNamespace(const std::string& namespaceUri, const std::string& preferedPrefix, bool requirePrefix) {
    int idx = this.declareNsUri(namespaceUri, preferedPrefix, requirePrefix);
      return this.getPrefix(idx);
   }

    int count() {
      return this.size;
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
