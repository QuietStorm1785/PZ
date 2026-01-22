#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TDoubleArrayList.h"
#include "gnu/trove/stack/TDoubleStack.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace stack {
namespace array {


class TDoubleArrayStack {
public:
    static const long serialVersionUID = 1L;
    TDoubleArrayList _list;
    static const int DEFAULT_CAPACITY = 10;

    public TDoubleArrayStack() {
      this(10);
   }

    public TDoubleArrayStack(int capacity) {
      this._list = std::make_shared<TDoubleArrayList>(capacity);
   }

    public TDoubleArrayStack(int capacity, double no_entry_value) {
      this._list = std::make_shared<TDoubleArrayList>(capacity, no_entry_value);
   }

    public TDoubleArrayStack(TDoubleStack stack) {
      if (dynamic_cast<TDoubleArrayStack*>(stack) != nullptr) {
    TDoubleArrayStack array_stack = (TDoubleArrayStack)stack;
         this._list = std::make_shared<TDoubleArrayList>(array_stack._list);
      } else {
         throw UnsupportedOperationException("Only support TDoubleArrayStack");
      }
   }

    double getNoEntryValue() {
      return this._list.getNoEntryValue();
   }

    void push(double val) {
      this._list.push_back(val);
   }

    double pop() {
      return this._list.removeAt(this._list.size() - 1);
   }

    double peek() {
      return this._list.get(this._list.size() - 1);
   }

    int size() {
      return this._list.size();
   }

    void clear() {
      this._list.clear();
   }

   public double[] toArray() {
      double[] retval = this._list.toArray();
      this.reverse(retval, 0, this.size());
    return retval;
   }

    void toArray(double[] dest) {
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

    void reverse(double[] dest, int from, int to) {
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

    void swap(double[] dest, int i, int j) {
    double tmp = dest[i];
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
    TDoubleArrayStack that = (TDoubleArrayStack)o;
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
      this._list = (TDoubleArrayList)in.readObject();
   }
}
} // namespace array
} // namespace stack
} // namespace trove
} // namespace gnu
