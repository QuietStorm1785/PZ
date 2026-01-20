#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TFloatArrayList.h"
#include "gnu/trove/stack/TFloatStack.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace stack {
namespace array {


class TFloatArrayStack {
public:
    static const long serialVersionUID = 1L;
    TFloatArrayList _list;
    static const int DEFAULT_CAPACITY = 10;

    public TFloatArrayStack() {
      this(10);
   }

    public TFloatArrayStack(int capacity) {
      this._list = std::make_shared<TFloatArrayList>(capacity);
   }

    public TFloatArrayStack(int capacity, float no_entry_value) {
      this._list = std::make_shared<TFloatArrayList>(capacity, no_entry_value);
   }

    public TFloatArrayStack(TFloatStack stack) {
      if (dynamic_cast<TFloatArrayStack*>(stack) != nullptr) {
    TFloatArrayStack array_stack = (TFloatArrayStack)stack;
         this._list = std::make_shared<TFloatArrayList>(array_stack._list);
      } else {
         throw UnsupportedOperationException("Only support TFloatArrayStack");
      }
   }

    float getNoEntryValue() {
      return this._list.getNoEntryValue();
   }

    void push(float val) {
      this._list.push_back(val);
   }

    float pop() {
      return this._list.removeAt(this._list.size() - 1);
   }

    float peek() {
      return this._list.get(this._list.size() - 1);
   }

    int size() {
      return this._list.size();
   }

    void clear() {
      this._list.clear();
   }

   public float[] toArray() {
      float[] retval = this._list.toArray();
      this.reverse(retval, 0, this.size());
    return retval;
   }

    void toArray(float[] dest) {
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

    void reverse(float[] dest, int from, int to) {
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

    void swap(float[] dest, int i, int j) {
    float tmp = dest[i];
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
    TFloatArrayStack that = (TFloatArrayStack)o;
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
      this._list = (TFloatArrayList)in.readObject();
   }
}
} // namespace array
} // namespace stack
} // namespace trove
} // namespace gnu
