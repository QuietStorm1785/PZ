#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TByteArrayList.h"
#include "gnu/trove/stack/TByteStack.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace stack {
namespace array {


class TByteArrayStack {
public:
    static const long serialVersionUID = 1L;
    TByteArrayList _list;
    static const int DEFAULT_CAPACITY = 10;

    public TByteArrayStack() {
      this(10);
   }

    public TByteArrayStack(int capacity) {
      this._list = std::make_shared<TByteArrayList>(capacity);
   }

    public TByteArrayStack(int capacity, uint8_t no_entry_value) {
      this._list = std::make_shared<TByteArrayList>(capacity, no_entry_value);
   }

    public TByteArrayStack(TByteStack stack) {
      if (dynamic_cast<TByteArrayStack*>(stack) != nullptr) {
    TByteArrayStack array_stack = (TByteArrayStack)stack;
         this._list = std::make_shared<TByteArrayList>(array_stack._list);
      } else {
         throw UnsupportedOperationException("Only support TByteArrayStack");
      }
   }

    uint8_t getNoEntryValue() {
      return this._list.getNoEntryValue();
   }

    void push(uint8_t val) {
      this._list.push_back(val);
   }

    uint8_t pop() {
      return this._list.removeAt(this._list.size() - 1);
   }

    uint8_t peek() {
      return this._list.get(this._list.size() - 1);
   }

    int size() {
      return this._list.size();
   }

    void clear() {
      this._list.clear();
   }

   public byte[] toArray() {
      byte[] retval = this._list.toArray();
      this.reverse(retval, 0, this.size());
    return retval;
   }

    void toArray(byte[] dest) {
    int size = this.size();
    int start = size - dest.length;
      if (start < 0) {
         start = 0;
      }

    int length = Math.min(size, dest.length);
      this._list.toArray(dest, start, length);
      this.reverse(dest, 0, length);
      if (dest.length > size) {
         dest[size] = this._list.getNoEntryValue();
      }
   }

    void reverse(byte[] dest, int from, int to) {
      if (from != to) {
         if (from > to) {
            throw IllegalArgumentException("from cannot be greater than to");
         } else {
    int i = from;

            for (int j = to - 1; i < j; j--) {
               this.swap(dest, i, j);
               i++;
            }
         }
      }
   }

    void swap(byte[] dest, int i, int j) {
    uint8_t tmp = dest[i];
      dest[i] = dest[j];
      dest[j] = tmp;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");

      for (int i = this._list.size() - 1; i > 0; i--) {
         buf.append(this._list.get(i));
         buf.append(", ");
      }

      if (this.size() > 0) {
         buf.append(this._list.get(0));
      }

      buf.append("}");
      return buf;
   }

    bool equals(void* o) {
      if (this == o) {
    return true;
      } else if (o != nullptr && this.getClass() == o.getClass()) {
    TByteArrayStack that = (TByteArrayStack)o;
         return this._list == that._list);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this._list.hashCode();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._list);
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._list = (TByteArrayList)in.readObject();
   }
}
} // namespace array
} // namespace stack
} // namespace trove
} // namespace gnu
