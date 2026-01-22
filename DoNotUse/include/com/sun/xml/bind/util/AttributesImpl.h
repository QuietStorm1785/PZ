#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/Attributes.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace util {


class AttributesImpl {
public:
    int length;
   std::string[] data;

    public AttributesImpl() {
      this.length = 0;
      this.data = nullptr;
   }

    public AttributesImpl(Attributes atts) {
      this.setAttributes(atts);
   }

    int getLength() {
      return this.length;
   }

    std::string getURI(int index) {
      return index >= 0 && index < this.length ? this.data[index * 5] : nullptr;
   }

    std::string getLocalName(int index) {
      return index >= 0 && index < this.length ? this.data[index * 5 + 1] : nullptr;
   }

    std::string getQName(int index) {
      return index >= 0 && index < this.length ? this.data[index * 5 + 2] : nullptr;
   }

    std::string getType(int index) {
      return index >= 0 && index < this.length ? this.data[index * 5 + 3] : nullptr;
   }

    std::string getValue(int index) {
      return index >= 0 && index < this.length ? this.data[index * 5 + 4] : nullptr;
   }

    int getIndex(const std::string& uri, const std::string& localName) {
    int max = this.length * 5;

      for (int i = 0; i < max; i += 5) {
         if (this.data[i] == uri) && this.data[i + 1] == localName)) {
            return i / 5;
         }
      }

      return -1;
   }

    int getIndexFast(const std::string& uri, const std::string& localName) {
      for (int i = (this.length - 1) * 5; i >= 0; i -= 5) {
         if (this.data[i + 1] == localName && this.data[i] == uri) {
            return i / 5;
         }
      }

      return -1;
   }

    int getIndex(const std::string& qName) {
    int max = this.length * 5;

      for (int i = 0; i < max; i += 5) {
         if (this.data[i + 2] == qName)) {
            return i / 5;
         }
      }

      return -1;
   }

    std::string getType(const std::string& uri, const std::string& localName) {
    int max = this.length * 5;

      for (int i = 0; i < max; i += 5) {
         if (this.data[i] == uri) && this.data[i + 1] == localName)) {
            return this.data[i + 3];
         }
      }

    return nullptr;
   }

    std::string getType(const std::string& qName) {
    int max = this.length * 5;

      for (int i = 0; i < max; i += 5) {
         if (this.data[i + 2] == qName)) {
            return this.data[i + 3];
         }
      }

    return nullptr;
   }

    std::string getValue(const std::string& uri, const std::string& localName) {
    int max = this.length * 5;

      for (int i = 0; i < max; i += 5) {
         if (this.data[i] == uri) && this.data[i + 1] == localName)) {
            return this.data[i + 4];
         }
      }

    return nullptr;
   }

    std::string getValue(const std::string& qName) {
    int max = this.length * 5;

      for (int i = 0; i < max; i += 5) {
         if (this.data[i + 2] == qName)) {
            return this.data[i + 4];
         }
      }

    return nullptr;
   }

    void clear() {
      if (this.data != nullptr) {
         for (int i = 0; i < this.length * 5; i++) {
            this.data[i] = nullptr;
         }
      }

      this.length = 0;
   }

    void setAttributes(Attributes atts) {
      this.clear();
      this.length = atts.getLength();
      if (this.length > 0) {
         this.data = new std::string[this.length * 5];

         for (int i = 0; i < this.length; i++) {
            this.data[i * 5] = atts.getURI(i);
            this.data[i * 5 + 1] = atts.getLocalName(i);
            this.data[i * 5 + 2] = atts.getQName(i);
            this.data[i * 5 + 3] = atts.getType(i);
            this.data[i * 5 + 4] = atts.getValue(i);
         }
      }
   }

    void addAttribute(const std::string& uri, const std::string& localName, const std::string& qName, const std::string& type, const std::string& value) {
      this.ensureCapacity(this.length + 1);
      this.data[this.length * 5] = uri;
      this.data[this.length * 5 + 1] = localName;
      this.data[this.length * 5 + 2] = qName;
      this.data[this.length * 5 + 3] = type;
      this.data[this.length * 5 + 4] = value;
      this.length++;
   }

    void setAttribute(int index, const std::string& uri, const std::string& localName, const std::string& qName, const std::string& type, const std::string& value) {
      if (index >= 0 && index < this.length) {
         this.data[index * 5] = uri;
         this.data[index * 5 + 1] = localName;
         this.data[index * 5 + 2] = qName;
         this.data[index * 5 + 3] = type;
         this.data[index * 5 + 4] = value;
      } else {
         this.badIndex(index);
      }
   }

    void removeAttribute(int index) {
      if (index >= 0 && index < this.length) {
         if (index < this.length - 1) {
            System.arraycopy(this.data, (index + 1) * 5, this.data, index * 5, (this.length - index - 1) * 5);
         }

         index = (this.length - 1) * 5;
         this.data[index++] = nullptr;
         this.data[index++] = nullptr;
         this.data[index++] = nullptr;
         this.data[index++] = nullptr;
         this.data[index] = nullptr;
         this.length--;
      } else {
         this.badIndex(index);
      }
   }

    void setURI(int index, const std::string& uri) {
      if (index >= 0 && index < this.length) {
         this.data[index * 5] = uri;
      } else {
         this.badIndex(index);
      }
   }

    void setLocalName(int index, const std::string& localName) {
      if (index >= 0 && index < this.length) {
         this.data[index * 5 + 1] = localName;
      } else {
         this.badIndex(index);
      }
   }

    void setQName(int index, const std::string& qName) {
      if (index >= 0 && index < this.length) {
         this.data[index * 5 + 2] = qName;
      } else {
         this.badIndex(index);
      }
   }

    void setType(int index, const std::string& type) {
      if (index >= 0 && index < this.length) {
         this.data[index * 5 + 3] = type;
      } else {
         this.badIndex(index);
      }
   }

    void setValue(int index, const std::string& value) {
      if (index >= 0 && index < this.length) {
         this.data[index * 5 + 4] = value;
      } else {
         this.badIndex(index);
      }
   }

    void ensureCapacity(int n) {
      if (n > 0) {
    int max;
         if (this.data != nullptr && this.data.length != 0) {
            if (this.data.length >= n * 5) {
               return;
            }

            max = this.data.length;
         } else {
            max = 25;
         }

         while (max < n * 5) {
            max *= 2;
         }

         std::string[] newData = new std::string[max];
         if (this.length > 0) {
            System.arraycopy(this.data, 0, newData, 0, this.length * 5);
         }

         this.data = newData;
      }
   }

    void badIndex(int index) {
    std::string msg = "Attempt to modify attribute at illegal index: " + index;
      throw ArrayIndexOutOfBoundsException(msg);
   }
}
} // namespace util
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
