#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/iterator/TByteIterator.h"
#include "gnu/trove/list/TByteList.h"
#include "gnu/trove/list/array/TByteArrayList/1.h"
#include "gnu/trove/list/array/TByteArrayList/TByteArrayIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace list {
namespace array {


class TByteArrayList {
public:
    static const long serialVersionUID = 1L;
   protected byte[] _data;
    int _pos;
    static const int DEFAULT_CAPACITY = 10;
    uint8_t no_entry_value;

    public TByteArrayList() {
      this(10, (byte)0);
   }

    public TByteArrayList(int capacity) {
      this(capacity, (byte)0);
   }

    public TByteArrayList(int capacity, uint8_t no_entry_value) {
      this._data = new byte[capacity];
      this._pos = 0;
      this.no_entry_value = no_entry_value;
   }

    public TByteArrayList(TByteCollection collection) {
      this(collection.size());
      this.addAll(collection);
   }

    public TByteArrayList(byte[] values) {
      this(values.length);
      this.push_back(values);
   }

    protected TByteArrayList(byte[] values, uint8_t no_entry_value, bool wrap) {
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

    static TByteArrayList wrap(byte[] values) {
    return wrap();
   }

    static TByteArrayList wrap(byte[] values, uint8_t no_entry_value) {
      return std::make_shared<1>(values, no_entry_value, true);
   }

    uint8_t getNoEntryValue() {
      return this.no_entry_value;
   }

    void ensureCapacity(int capacity) {
      if (capacity > this._data.length) {
    int newCap = Math.max(this._data.length << 1, capacity);
         byte[] tmp = new byte[newCap];
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
         byte[] tmp = new byte[this.size()];
         this.toArray(tmp, 0, tmp.length);
         this._data = tmp;
      }
   }

    bool add(uint8_t val) {
      this.ensureCapacity(this._pos + 1);
      this._data[this._pos++] = val;
    return true;
   }

    void add(byte[] vals) {
      this.push_back(vals, 0, vals.length);
   }

    void add(byte[] vals, int offset, int length) {
      this.ensureCapacity(this._pos + length);
      System.arraycopy(vals, offset, this._data, this._pos, length);
      this._pos += length;
   }

    void insert(int offset, uint8_t value) {
      if (offset == this._pos) {
         this.push_back(value);
      } else {
         this.ensureCapacity(this._pos + 1);
         System.arraycopy(this._data, offset, this._data, offset + 1, this._pos - offset);
         this._data[offset] = value;
         this._pos++;
      }
   }

    void insert(int offset, byte[] values) {
      this.insert(offset, values, 0, values.length);
   }

    void insert(int offset, byte[] values, int valOffset, int len) {
      if (offset == this._pos) {
         this.push_back(values, valOffset, len);
      } else {
         this.ensureCapacity(this._pos + len);
         System.arraycopy(this._data, offset, this._data, offset + len, this._pos - offset);
         System.arraycopy(values, valOffset, this._data, offset, len);
         this._pos += len;
      }
   }

    uint8_t get(int offset) {
      if (offset >= this._pos) {
         throw ArrayIndexOutOfBoundsException(offset);
      } else {
         return this._data[offset];
      }
   }

    uint8_t getQuick(int offset) {
      return this._data[offset];
   }

    uint8_t set(int offset, uint8_t val) {
      if (offset >= this._pos) {
         throw ArrayIndexOutOfBoundsException(offset);
      } else {
    uint8_t prev_val = this._data[offset];
         this._data[offset] = val;
    return prev_val;
      }
   }

    uint8_t replace(int offset, uint8_t val) {
      if (offset >= this._pos) {
         throw ArrayIndexOutOfBoundsException(offset);
      } else {
    uint8_t old = this._data[offset];
         this._data[offset] = val;
    return old;
      }
   }

    void set(int offset, byte[] values) {
      this.set(offset, values, 0, values.length);
   }

    void set(int offset, byte[] values, int valOffset, int length) {
      if (offset >= 0 && offset + length <= this._pos) {
         System.arraycopy(values, valOffset, this._data, offset, length);
      } else {
         throw ArrayIndexOutOfBoundsException(offset);
      }
   }

    void setQuick(int offset, uint8_t val) {
      this._data[offset] = val;
   }

    void clear() {
      this.clear(10);
   }

    void clear(int capacity) {
      this._data = new byte[capacity];
      this._pos = 0;
   }

    void reset() {
      this._pos = 0;
      Arrays.fill(this._data, this.no_entry_value);
   }

    void resetQuick() {
      this._pos = 0;
   }

    bool remove(uint8_t value) {
      for (int index = 0; index < this._pos; index++) {
         if (value == this._data[index]) {
            this.remove(index, 1);
    return true;
         }
      }

    return false;
   }

    uint8_t removeAt(int offset) {
    uint8_t old = this.get(offset);
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

    TByteIterator iterator() {
      return std::make_shared<TByteArrayIterator>(this, 0);
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<uint8_t*>(element) != nullptr)) {
    return false;
         }

    uint8_t c = (uint8_t)element;
         if (!this.contains(c)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TByteCollection collection) {
      if (this == collection) {
    return true;
      } else {
    TByteIterator iter = collection.iterator();

         while (iter.hasNext()) {
    uint8_t element = iter.next();
            if (!this.contains(element)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(byte[] array) {
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

    for (auto& element : collection)    uint8_t e = element;
         if (this.push_back(e)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(TByteCollection collection) {
    bool changed = false;
    TByteIterator iter = collection.iterator();

      while (iter.hasNext()) {
    uint8_t element = iter.next();
         if (this.push_back(element)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(byte[] array) {
    bool changed = false;

    for (auto& element : array)         if (this.push_back(element)) {
            changed = true;
         }
      }

    return changed;
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TByteIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TByteCollection collection) {
      if (this == collection) {
    return false;
      } else {
    bool modified = false;
    TByteIterator iter = this.iterator();

         while (iter.hasNext()) {
            if (!collection.contains(iter.next())) {
               iter.remove();
               modified = true;
            }
         }

    return modified;
      }
   }

    bool retainAll(byte[] array) {
    bool changed = false;
      Arrays.sort(array);
      byte[] data = this._data;
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

    for (auto& element : collection)         if (dynamic_cast<uint8_t*>(element) != nullptr) {
    uint8_t c = (uint8_t)element;
            if (this.remove(c)) {
               changed = true;
            }
         }
      }

    return changed;
   }

    bool removeAll(TByteCollection collection) {
      if (collection == this) {
         this.clear();
    return true;
      } else {
    bool changed = false;
    TByteIterator iter = collection.iterator();

         while (iter.hasNext()) {
    uint8_t element = iter.next();
            if (this.remove(element)) {
               changed = true;
            }
         }

    return changed;
      }
   }

    bool removeAll(byte[] array) {
    bool changed = false;
    int i = array.length;

      while (i-- > 0) {
         if (this.remove(array[i])) {
            changed = true;
         }
      }

    return changed;
   }

    void transformValues(TByteFunction function) {
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
    uint8_t tmp = this._data[i];
      this._data[i] = this._data[j];
      this._data[j] = tmp;
   }

    TByteList subList(int begin, int end) {
      if (end < begin) {
         throw IllegalArgumentException("end index " + end + " greater than begin index " + begin);
      } else if (begin < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (end > this._data.length) {
         throw IndexOutOfBoundsException("end index < " + this._data.length);
      } else {
    TByteArrayList list = std::make_shared<TByteArrayList>(end - begin);

         for (int i = begin; i < end; i++) {
            list.push_back(this._data[i]);
         }

    return list;
      }
   }

   public byte[] toArray() {
      return this.toArray(0, this._pos);
   }

   public byte[] toArray(int offset, int len) {
      byte[] rv = new byte[len];
      this.toArray(rv, offset, len);
    return rv;
   }

   public byte[] toArray(byte[] dest) {
    int len = dest.length;
      if (dest.length > this._pos) {
         len = this._pos;
         dest[len] = this.no_entry_value;
      }

      this.toArray(dest, 0, len);
    return dest;
   }

   public byte[] toArray(byte[] dest, int offset, int len) {
      if (len == 0) {
    return dest;
      } else if (offset >= 0 && offset < this._pos) {
         System.arraycopy(this._data, offset, dest, 0, len);
    return dest;
      } else {
         throw ArrayIndexOutOfBoundsException(offset);
      }
   }

   public byte[] toArray(byte[] dest, int source_pos, int dest_pos, int len) {
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
      } else if (dynamic_cast<TByteArrayList*>(other) != nullptr) {
    TByteArrayList that = (TByteArrayList)other;
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

    bool forEach(TByteProcedure procedure) {
      for (int i = 0; i < this._pos; i++) {
         if (!procedure.execute(this._data[i])) {
    return false;
         }
      }

    return true;
   }

    bool forEachDescending(TByteProcedure procedure) {
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

    void fill(uint8_t val) {
      Arrays.fill(this._data, 0, this._pos, val);
   }

    void fill(int fromIndex, int toIndex, uint8_t val) {
      if (toIndex > this._pos) {
         this.ensureCapacity(toIndex);
         this._pos = toIndex;
      }

      Arrays.fill(this._data, fromIndex, toIndex, val);
   }

    int binarySearch(uint8_t value) {
      return this.binarySearch(value, 0, this._pos);
   }

    int binarySearch(uint8_t value, int fromIndex, int toIndex) {
      if (fromIndex < 0) {
         throw ArrayIndexOutOfBoundsException(fromIndex);
      } else if (toIndex > this._pos) {
         throw ArrayIndexOutOfBoundsException(toIndex);
      } else {
    int low = fromIndex;
    int high = toIndex - 1;

         while (low <= high) {
    int mid = low + high >>> 1;
    uint8_t midVal = this._data[mid];
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

    int indexOf(uint8_t value) {
      return this.indexOf(0, value);
   }

    int indexOf(int offset, uint8_t value) {
      for (int i = offset; i < this._pos; i++) {
         if (this._data[i] == value) {
    return i;
         }
      }

      return -1;
   }

    int lastIndexOf(uint8_t value) {
      return this.lastIndexOf(this._pos, value);
   }

    int lastIndexOf(int offset, uint8_t value) {
    int i = offset;

      while (i-- > 0) {
         if (this._data[i] == value) {
    return i;
         }
      }

      return -1;
   }

    bool contains(uint8_t value) {
      return this.lastIndexOf(value) >= 0;
   }

    TByteList grep(TByteProcedure condition) {
    TByteArrayList list = std::make_shared<TByteArrayList>();

      for (int i = 0; i < this._pos; i++) {
         if (condition.execute(this._data[i])) {
            list.push_back(this._data[i]);
         }
      }

    return list;
   }

    TByteList inverseGrep(TByteProcedure condition) {
    TByteArrayList list = std::make_shared<TByteArrayList>();

      for (int i = 0; i < this._pos; i++) {
         if (!condition.execute(this._data[i])) {
            list.push_back(this._data[i]);
         }
      }

    return list;
   }

    uint8_t max() {
      if (this.size() == 0) {
         throw IllegalStateException("cannot find maximum of an empty list");
      } else {
    uint8_t max = -128;

         for (int i = 0; i < this._pos; i++) {
            if (this._data[i] > max) {
               max = this._data[i];
            }
         }

    return max;
      }
   }

    uint8_t min() {
      if (this.size() == 0) {
         throw IllegalStateException("cannot find minimum of an empty list");
      } else {
    uint8_t min = 127;

         for (int i = 0; i < this._pos; i++) {
            if (this._data[i] < min) {
               min = this._data[i];
            }
         }

    return min;
      }
   }

    uint8_t sum() {
    uint8_t sum = 0;

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
      out.writeByte(this.no_entry_value);
    int len = this._data.length;
      out.writeInt(len);

      for (int i = 0; i < len; i++) {
         out.writeByte(this._data[i]);
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._pos = in.readInt();
      this.no_entry_value = in.readByte();
    int len = in.readInt();
      this._data = new byte[len];

      for (int i = 0; i < len; i++) {
         this._data[i] = in.readByte();
      }
   }
}
} // namespace array
} // namespace list
} // namespace trove
} // namespace gnu
