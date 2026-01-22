#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/iterator/TIntIterator.h"
#include "gnu/trove/list/TIntList.h"
#include "gnu/trove/list/array/TIntArrayList/1.h"
#include "gnu/trove/list/array/TIntArrayList/TIntArrayIterator.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace list {
namespace array {


class TIntArrayList {
public:
    static const long serialVersionUID = 1L;
   protected int[] _data;
    int _pos;
    static const int DEFAULT_CAPACITY = 10;
    int no_entry_value;

    public TIntArrayList() {
      this(10, 0);
   }

    public TIntArrayList(int capacity) {
      this(capacity, 0);
   }

    public TIntArrayList(int capacity, int no_entry_value) {
      this._data = new int[capacity];
      this._pos = 0;
      this.no_entry_value = no_entry_value;
   }

    public TIntArrayList(TIntCollection collection) {
      this(collection.size());
      this.addAll(collection);
   }

    public TIntArrayList(int[] values) {
      this(values.length);
      this.push_back(values);
   }

    protected TIntArrayList(int[] values, int no_entry_value, bool wrap) {
      if (!wrap) {
         throw IllegalStateException("Wrong call");
      } else if (values == nullptr) {
         throw IllegalArgumentException("values can not be nullptr");
      } else {
         this._data = values;
         this._pos = values.length;
         this.no_entry_value = no_entry_value;
      }
   }

    static TIntArrayList wrap(int[] values) {
    return wrap();
   }

    static TIntArrayList wrap(int[] values, int no_entry_value) {
      return std::make_shared<1>(values, no_entry_value, true);
   }

    int getNoEntryValue() {
      return this.no_entry_value;
   }

    void ensureCapacity(int capacity) {
      if (capacity > this._data.length) {
    int newCap = Math.max(this._data.length << 1, capacity);
         int[] tmp = new int[newCap];
         System.arraycopy(this._data, 0, tmp, 0, this._data.length);
         this._data = tmp;
      }
   }

    int size() {
      return this._pos;
   }

    bool isEmpty() {
      return this._pos == 0;
   }

    void trimToSize() {
      if (this._data.length > this.size()) {
         int[] tmp = new int[this.size()];
         this.toArray(tmp, 0, tmp.length);
         this._data = tmp;
      }
   }

    bool add(int val) {
      this.ensureCapacity(this._pos + 1);
      this._data[this._pos++] = val;
    return true;
   }

    void add(int[] vals) {
      this.push_back(vals, 0, vals.length);
   }

    void add(int[] vals, int offset, int length) {
      this.ensureCapacity(this._pos + length);
      System.arraycopy(vals, offset, this._data, this._pos, length);
      this._pos += length;
   }

    void insert(int offset, int value) {
      if (offset == this._pos) {
         this.push_back(value);
      } else {
         this.ensureCapacity(this._pos + 1);
         System.arraycopy(this._data, offset, this._data, offset + 1, this._pos - offset);
         this._data[offset] = value;
         this._pos++;
      }
   }

    void insert(int offset, int[] values) {
      this.insert(offset, values, 0, values.length);
   }

    void insert(int offset, int[] values, int valOffset, int len) {
      if (offset == this._pos) {
         this.push_back(values, valOffset, len);
      } else {
         this.ensureCapacity(this._pos + len);
         System.arraycopy(this._data, offset, this._data, offset + len, this._pos - offset);
         System.arraycopy(values, valOffset, this._data, offset, len);
         this._pos += len;
      }
   }

    int get(int offset) {
      if (offset >= this._pos) {
         throw ArrayIndexOutOfBoundsException(offset);
      } else {
         return this._data[offset];
      }
   }

    int getQuick(int offset) {
      return this._data[offset];
   }

    int set(int offset, int val) {
      if (offset >= this._pos) {
         throw ArrayIndexOutOfBoundsException(offset);
      } else {
    int prev_val = this._data[offset];
         this._data[offset] = val;
    return prev_val;
      }
   }

    int replace(int offset, int val) {
      if (offset >= this._pos) {
         throw ArrayIndexOutOfBoundsException(offset);
      } else {
    int old = this._data[offset];
         this._data[offset] = val;
    return old;
      }
   }

    void set(int offset, int[] values) {
      this.set(offset, values, 0, values.length);
   }

    void set(int offset, int[] values, int valOffset, int length) {
      if (offset >= 0 && offset + length <= this._pos) {
         System.arraycopy(values, valOffset, this._data, offset, length);
      } else {
         throw ArrayIndexOutOfBoundsException(offset);
      }
   }

    void setQuick(int offset, int val) {
      this._data[offset] = val;
   }

    void clear() {
      this.clear(10);
   }

    void clear(int capacity) {
      this._data = new int[capacity];
      this._pos = 0;
   }

    void reset() {
      this._pos = 0;
      Arrays.fill(this._data, this.no_entry_value);
   }

    void resetQuick() {
      this._pos = 0;
   }

    bool remove(int value) {
      for (int index = 0; index < this._pos; index++) {
         if (value == this._data[index]) {
            this.remove(index, 1);
    return true;
         }
      }

    return false;
   }

    int removeAt(int offset) {
    int old = this.get(offset);
      this.remove(offset, 1);
    return old;
   }

    void remove(int offset, int length) {
      if (length != 0) {
         if (offset >= 0 && offset < this._pos) {
            if (offset == 0) {
               System.arraycopy(this._data, length, this._data, 0, this._pos - length);
            } else if (this._pos - length != offset) {
               System.arraycopy(this._data, offset + length, this._data, offset, this._pos - (offset + length));
            }

            this._pos -= length;
         } else {
            throw ArrayIndexOutOfBoundsException(offset);
         }
      }
   }

    TIntIterator iterator() {
      return std::make_shared<TIntArrayIterator>(this, 0);
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<int*>(element) != nullptr)) {
    return false;
         }

    int c = (int)element;
         if (!this.contains(c)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TIntCollection collection) {
      if (this == collection) {
    return true;
      } else {
    TIntIterator iter = collection.iterator();

         while (iter.hasNext()) {
    int element = iter.next();
            if (!this.contains(element)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(int[] array) {
    int i = array.length;

      while (i-- > 0) {
         if (!this.contains(array[i])) {
    return false;
         }
      }

    return true;
   }

    bool addAll(Collection<? extends) {
    bool changed = false;

    for (auto& element : collection)    int e = element;
         if (this.push_back(e)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(TIntCollection collection) {
    bool changed = false;
    TIntIterator iter = collection.iterator();

      while (iter.hasNext()) {
    int element = iter.next();
         if (this.push_back(element)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(int[] array) {
    bool changed = false;

    for (auto& element : array)         if (this.push_back(element)) {
            changed = true;
         }
      }

    return changed;
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TIntIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TIntCollection collection) {
      if (this == collection) {
    return false;
      } else {
    bool modified = false;
    TIntIterator iter = this.iterator();

         while (iter.hasNext()) {
            if (!collection.contains(iter.next())) {
               iter.remove();
               modified = true;
            }
         }

    return modified;
      }
   }

    bool retainAll(int[] array) {
    bool changed = false;
      Arrays.sort(array);
      int[] data = this._data;
    int i = this._pos;

      while (i-- > 0) {
         if (Arrays.binarySearch(array, data[i]) < 0) {
            this.remove(i, 1);
            changed = true;
         }
      }

    return changed;
   }

    bool removeAll(Collection<?> collection) {
    bool changed = false;

    for (auto& element : collection)         if (dynamic_cast<int*>(element) != nullptr) {
    int c = (int)element;
            if (this.remove(c)) {
               changed = true;
            }
         }
      }

    return changed;
   }

    bool removeAll(TIntCollection collection) {
      if (collection == this) {
         this.clear();
    return true;
      } else {
    bool changed = false;
    TIntIterator iter = collection.iterator();

         while (iter.hasNext()) {
    int element = iter.next();
            if (this.remove(element)) {
               changed = true;
            }
         }

    return changed;
      }
   }

    bool removeAll(int[] array) {
    bool changed = false;
    int i = array.length;

      while (i-- > 0) {
         if (this.remove(array[i])) {
            changed = true;
         }
      }

    return changed;
   }

    void transformValues(TIntFunction function) {
    int i = this._pos;

      while (i-- > 0) {
         this._data[i] = function.execute(this._data[i]);
      }
   }

    void reverse() {
      this.reverse(0, this._pos);
   }

    void reverse(int from, int to) {
      if (from != to) {
         if (from > to) {
            throw IllegalArgumentException("from cannot be greater than to");
         } else {
    int i = from;

            for (int j = to - 1; i < j; j--) {
               this.swap(i, j);
               i++;
            }
         }
      }
   }

    void shuffle(Random rand) {
    int i = this._pos;

      while (i-- > 1) {
         this.swap(i, rand.nextInt(i));
      }
   }

    void swap(int i, int j) {
    int tmp = this._data[i];
      this._data[i] = this._data[j];
      this._data[j] = tmp;
   }

    TIntList subList(int begin, int end) {
      if (end < begin) {
         throw IllegalArgumentException("end index " + end + " greater than begin index " + begin);
      } else if (begin < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (end > this._data.length) {
         throw IndexOutOfBoundsException("end index < " + this._data.length);
      } else {
    TIntArrayList list = std::make_shared<TIntArrayList>(end - begin);

         for (int i = begin; i < end; i++) {
            list.push_back(this._data[i]);
         }

    return list;
      }
   }

   public int[] toArray() {
      return this.toArray(0, this._pos);
   }

   public int[] toArray(int offset, int len) {
      int[] rv = new int[len];
      this.toArray(rv, offset, len);
    return rv;
   }

   public int[] toArray(int[] dest) {
    int len = dest.length;
      if (dest.length > this._pos) {
         len = this._pos;
         dest[len] = this.no_entry_value;
      }

      this.toArray(dest, 0, len);
    return dest;
   }

   public int[] toArray(int[] dest, int offset, int len) {
      if (len == 0) {
    return dest;
      } else if (offset >= 0 && offset < this._pos) {
         System.arraycopy(this._data, offset, dest, 0, len);
    return dest;
      } else {
         throw ArrayIndexOutOfBoundsException(offset);
      }
   }

   public int[] toArray(int[] dest, int source_pos, int dest_pos, int len) {
      if (len == 0) {
    return dest;
      } else if (source_pos >= 0 && source_pos < this._pos) {
         System.arraycopy(this._data, source_pos, dest, dest_pos, len);
    return dest;
      } else {
         throw ArrayIndexOutOfBoundsException(source_pos);
      }
   }

    bool equals(void* other) {
      if (other == this) {
    return true;
      } else if (dynamic_cast<TIntArrayList*>(other) != nullptr) {
    TIntArrayList that = (TIntArrayList)other;
         if (that.size() != this.size()) {
    return false;
         } else {
    int i = this._pos;

            while (i-- > 0) {
               if (this._data[i] != that._data[i]) {
    return false;
               }
            }

    return true;
         }
      } else {
    return false;
      }
   }

    int hashCode() {
    int h = 0;
    int i = this._pos;

      while (i-- > 0) {
         h += HashFunctions.hash(this._data[i]);
      }

    return h;
   }

    bool forEach(TIntProcedure procedure) {
      for (int i = 0; i < this._pos; i++) {
         if (!procedure.execute(this._data[i])) {
    return false;
         }
      }

    return true;
   }

    bool forEachDescending(TIntProcedure procedure) {
    int i = this._pos;

      while (i-- > 0) {
         if (!procedure.execute(this._data[i])) {
    return false;
         }
      }

    return true;
   }

    void sort() {
      Arrays.sort(this._data, 0, this._pos);
   }

    void sort(int fromIndex, int toIndex) {
      Arrays.sort(this._data, fromIndex, toIndex);
   }

    void fill(int val) {
      Arrays.fill(this._data, 0, this._pos, val);
   }

    void fill(int fromIndex, int toIndex, int val) {
      if (toIndex > this._pos) {
         this.ensureCapacity(toIndex);
         this._pos = toIndex;
      }

      Arrays.fill(this._data, fromIndex, toIndex, val);
   }

    int binarySearch(int value) {
      return this.binarySearch(value, 0, this._pos);
   }

    int binarySearch(int value, int fromIndex, int toIndex) {
      if (fromIndex < 0) {
         throw ArrayIndexOutOfBoundsException(fromIndex);
      } else if (toIndex > this._pos) {
         throw ArrayIndexOutOfBoundsException(toIndex);
      } else {
    int low = fromIndex;
    int high = toIndex - 1;

         while (low <= high) {
    int mid = low + high >>> 1;
    int midVal = this._data[mid];
            if (midVal < value) {
               low = mid + 1;
            } else {
               if (midVal <= value) {
    return mid;
               }

               high = mid - 1;
            }
         }

         return -(low + 1);
      }
   }

    int indexOf(int value) {
      return this.indexOf(0, value);
   }

    int indexOf(int offset, int value) {
      for (int i = offset; i < this._pos; i++) {
         if (this._data[i] == value) {
    return i;
         }
      }

      return -1;
   }

    int lastIndexOf(int value) {
      return this.lastIndexOf(this._pos, value);
   }

    int lastIndexOf(int offset, int value) {
    int i = offset;

      while (i-- > 0) {
         if (this._data[i] == value) {
    return i;
         }
      }

      return -1;
   }

    bool contains(int value) {
      return this.lastIndexOf(value) >= 0;
   }

    TIntList grep(TIntProcedure condition) {
    TIntArrayList list = std::make_shared<TIntArrayList>();

      for (int i = 0; i < this._pos; i++) {
         if (condition.execute(this._data[i])) {
            list.push_back(this._data[i]);
         }
      }

    return list;
   }

    TIntList inverseGrep(TIntProcedure condition) {
    TIntArrayList list = std::make_shared<TIntArrayList>();

      for (int i = 0; i < this._pos; i++) {
         if (!condition.execute(this._data[i])) {
            list.push_back(this._data[i]);
         }
      }

    return list;
   }

    int max() {
      if (this.size() == 0) {
         throw IllegalStateException("cannot find maximum of an empty list");
      } else {
    int max = int.MIN_VALUE;

         for (int i = 0; i < this._pos; i++) {
            if (this._data[i] > max) {
               max = this._data[i];
            }
         }

    return max;
      }
   }

    int min() {
      if (this.size() == 0) {
         throw IllegalStateException("cannot find minimum of an empty list");
      } else {
    int min = int.MAX_VALUE;

         for (int i = 0; i < this._pos; i++) {
            if (this._data[i] < min) {
               min = this._data[i];
            }
         }

    return min;
      }
   }

    int sum() {
    int sum = 0;

      for (int i = 0; i < this._pos; i++) {
         sum += this._data[i];
      }

    return sum;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
    int i = 0;

      for (int end = this._pos - 1; i < end; i++) {
         buf.append(this._data[i]);
         buf.append(", ");
      }

      if (this.size() > 0) {
         buf.append(this._data[this._pos - 1]);
      }

      buf.append("}");
      return buf;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeInt(this._pos);
      out.writeInt(this.no_entry_value);
    int len = this._data.length;
      out.writeInt(len);

      for (int i = 0; i < len; i++) {
         out.writeInt(this._data[i]);
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._pos = in.readInt();
      this.no_entry_value = in.readInt();
    int len = in.readInt();
      this._data = new int[len];

      for (int i = 0; i < len; i++) {
         this._data[i] = in.readInt();
      }
   }
}
} // namespace array
} // namespace list
} // namespace trove
} // namespace gnu
