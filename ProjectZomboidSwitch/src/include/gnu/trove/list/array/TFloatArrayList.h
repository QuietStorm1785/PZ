#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/iterator/TFloatIterator.h"
#include "gnu/trove/list/TFloatList.h"
#include "gnu/trove/list/array/TFloatArrayList/1.h"
#include "gnu/trove/list/array/TFloatArrayList/TFloatArrayIterator.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace list {
namespace array {


class TFloatArrayList {
public:
    static const long serialVersionUID = 1L;
   protected float[] _data;
    int _pos;
    static const int DEFAULT_CAPACITY = 10;
    float no_entry_value;

    public TFloatArrayList() {
      this(10, 0.0F);
   }

    public TFloatArrayList(int capacity) {
      this(capacity, 0.0F);
   }

    public TFloatArrayList(int capacity, float no_entry_value) {
      this._data = new float[capacity];
      this._pos = 0;
      this.no_entry_value = no_entry_value;
   }

    public TFloatArrayList(TFloatCollection collection) {
      this(collection.size());
      this.addAll(collection);
   }

    public TFloatArrayList(float[] values) {
      this(values.length);
      this.push_back(values);
   }

    protected TFloatArrayList(float[] values, float no_entry_value, bool wrap) {
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

    static TFloatArrayList wrap(float[] values) {
    return wrap();
   }

    static TFloatArrayList wrap(float[] values, float no_entry_value) {
      return std::make_shared<1>(values, no_entry_value, true);
   }

    float getNoEntryValue() {
      return this.no_entry_value;
   }

    void ensureCapacity(int capacity) {
      if (capacity > this._data.length) {
    int newCap = Math.max(this._data.length << 1, capacity);
         float[] tmp = new float[newCap];
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
         float[] tmp = new float[this.size()];
         this.toArray(tmp, 0, tmp.length);
         this._data = tmp;
      }
   }

    bool add(float val) {
      this.ensureCapacity(this._pos + 1);
      this._data[this._pos++] = val;
    return true;
   }

    void add(float[] vals) {
      this.push_back(vals, 0, vals.length);
   }

    void add(float[] vals, int offset, int length) {
      this.ensureCapacity(this._pos + length);
      System.arraycopy(vals, offset, this._data, this._pos, length);
      this._pos += length;
   }

    void insert(int offset, float value) {
      if (offset == this._pos) {
         this.push_back(value);
      } else {
         this.ensureCapacity(this._pos + 1);
         System.arraycopy(this._data, offset, this._data, offset + 1, this._pos - offset);
         this._data[offset] = value;
         this._pos++;
      }
   }

    void insert(int offset, float[] values) {
      this.insert(offset, values, 0, values.length);
   }

    void insert(int offset, float[] values, int valOffset, int len) {
      if (offset == this._pos) {
         this.push_back(values, valOffset, len);
      } else {
         this.ensureCapacity(this._pos + len);
         System.arraycopy(this._data, offset, this._data, offset + len, this._pos - offset);
         System.arraycopy(values, valOffset, this._data, offset, len);
         this._pos += len;
      }
   }

    float get(int offset) {
      if (offset >= this._pos) {
         throw ArrayIndexOutOfBoundsException(offset);
      } else {
         return this._data[offset];
      }
   }

    float getQuick(int offset) {
      return this._data[offset];
   }

    float set(int offset, float val) {
      if (offset >= this._pos) {
         throw ArrayIndexOutOfBoundsException(offset);
      } else {
    float prev_val = this._data[offset];
         this._data[offset] = val;
    return prev_val;
      }
   }

    float replace(int offset, float val) {
      if (offset >= this._pos) {
         throw ArrayIndexOutOfBoundsException(offset);
      } else {
    float old = this._data[offset];
         this._data[offset] = val;
    return old;
      }
   }

    void set(int offset, float[] values) {
      this.set(offset, values, 0, values.length);
   }

    void set(int offset, float[] values, int valOffset, int length) {
      if (offset >= 0 && offset + length <= this._pos) {
         System.arraycopy(values, valOffset, this._data, offset, length);
      } else {
         throw ArrayIndexOutOfBoundsException(offset);
      }
   }

    void setQuick(int offset, float val) {
      this._data[offset] = val;
   }

    void clear() {
      this.clear(10);
   }

    void clear(int capacity) {
      this._data = new float[capacity];
      this._pos = 0;
   }

    void reset() {
      this._pos = 0;
      Arrays.fill(this._data, this.no_entry_value);
   }

    void resetQuick() {
      this._pos = 0;
   }

    bool remove(float value) {
      for (int index = 0; index < this._pos; index++) {
         if (value == this._data[index]) {
            this.remove(index, 1);
    return true;
         }
      }

    return false;
   }

    float removeAt(int offset) {
    float old = this.get(offset);
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

    TFloatIterator iterator() {
      return std::make_shared<TFloatArrayIterator>(this, 0);
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<float*>(element) != nullptr)) {
    return false;
         }

    float c = (float)element;
         if (!this.contains(c)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TFloatCollection collection) {
      if (this == collection) {
    return true;
      } else {
    TFloatIterator iter = collection.iterator();

         while (iter.hasNext()) {
    float element = iter.next();
            if (!this.contains(element)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(float[] array) {
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

    for (auto& element : collection)    float e = element;
         if (this.push_back(e)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(TFloatCollection collection) {
    bool changed = false;
    TFloatIterator iter = collection.iterator();

      while (iter.hasNext()) {
    float element = iter.next();
         if (this.push_back(element)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(float[] array) {
    bool changed = false;

    for (auto& element : array)         if (this.push_back(element)) {
            changed = true;
         }
      }

    return changed;
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TFloatIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TFloatCollection collection) {
      if (this == collection) {
    return false;
      } else {
    bool modified = false;
    TFloatIterator iter = this.iterator();

         while (iter.hasNext()) {
            if (!collection.contains(iter.next())) {
               iter.remove();
               modified = true;
            }
         }

    return modified;
      }
   }

    bool retainAll(float[] array) {
    bool changed = false;
      Arrays.sort(array);
      float[] data = this._data;
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

    for (auto& element : collection)         if (dynamic_cast<float*>(element) != nullptr) {
    float c = (float)element;
            if (this.remove(c)) {
               changed = true;
            }
         }
      }

    return changed;
   }

    bool removeAll(TFloatCollection collection) {
      if (collection == this) {
         this.clear();
    return true;
      } else {
    bool changed = false;
    TFloatIterator iter = collection.iterator();

         while (iter.hasNext()) {
    float element = iter.next();
            if (this.remove(element)) {
               changed = true;
            }
         }

    return changed;
      }
   }

    bool removeAll(float[] array) {
    bool changed = false;
    int i = array.length;

      while (i-- > 0) {
         if (this.remove(array[i])) {
            changed = true;
         }
      }

    return changed;
   }

    void transformValues(TFloatFunction function) {
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
    float tmp = this._data[i];
      this._data[i] = this._data[j];
      this._data[j] = tmp;
   }

    TFloatList subList(int begin, int end) {
      if (end < begin) {
         throw IllegalArgumentException("end index " + end + " greater than begin index " + begin);
      } else if (begin < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (end > this._data.length) {
         throw IndexOutOfBoundsException("end index < " + this._data.length);
      } else {
    TFloatArrayList list = std::make_shared<TFloatArrayList>(end - begin);

         for (int i = begin; i < end; i++) {
            list.push_back(this._data[i]);
         }

    return list;
      }
   }

   public float[] toArray() {
      return this.toArray(0, this._pos);
   }

   public float[] toArray(int offset, int len) {
      float[] rv = new float[len];
      this.toArray(rv, offset, len);
    return rv;
   }

   public float[] toArray(float[] dest) {
    int len = dest.length;
      if (dest.length > this._pos) {
         len = this._pos;
         dest[len] = this.no_entry_value;
      }

      this.toArray(dest, 0, len);
    return dest;
   }

   public float[] toArray(float[] dest, int offset, int len) {
      if (len == 0) {
    return dest;
      } else if (offset >= 0 && offset < this._pos) {
         System.arraycopy(this._data, offset, dest, 0, len);
    return dest;
      } else {
         throw ArrayIndexOutOfBoundsException(offset);
      }
   }

   public float[] toArray(float[] dest, int source_pos, int dest_pos, int len) {
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
      } else if (dynamic_cast<TFloatArrayList*>(other) != nullptr) {
    TFloatArrayList that = (TFloatArrayList)other;
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

    bool forEach(TFloatProcedure procedure) {
      for (int i = 0; i < this._pos; i++) {
         if (!procedure.execute(this._data[i])) {
    return false;
         }
      }

    return true;
   }

    bool forEachDescending(TFloatProcedure procedure) {
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

    void fill(float val) {
      Arrays.fill(this._data, 0, this._pos, val);
   }

    void fill(int fromIndex, int toIndex, float val) {
      if (toIndex > this._pos) {
         this.ensureCapacity(toIndex);
         this._pos = toIndex;
      }

      Arrays.fill(this._data, fromIndex, toIndex, val);
   }

    int binarySearch(float value) {
      return this.binarySearch(value, 0, this._pos);
   }

    int binarySearch(float value, int fromIndex, int toIndex) {
      if (fromIndex < 0) {
         throw ArrayIndexOutOfBoundsException(fromIndex);
      } else if (toIndex > this._pos) {
         throw ArrayIndexOutOfBoundsException(toIndex);
      } else {
    int low = fromIndex;
    int high = toIndex - 1;

         while (low <= high) {
    int mid = low + high >>> 1;
    float midVal = this._data[mid];
            if (midVal < value) {
               low = mid + 1;
            } else {
               if (!(midVal > value)) {
    return mid;
               }

               high = mid - 1;
            }
         }

         return -(low + 1);
      }
   }

    int indexOf(float value) {
      return this.indexOf(0, value);
   }

    int indexOf(int offset, float value) {
      for (int i = offset; i < this._pos; i++) {
         if (this._data[i] == value) {
    return i;
         }
      }

      return -1;
   }

    int lastIndexOf(float value) {
      return this.lastIndexOf(this._pos, value);
   }

    int lastIndexOf(int offset, float value) {
    int i = offset;

      while (i-- > 0) {
         if (this._data[i] == value) {
    return i;
         }
      }

      return -1;
   }

    bool contains(float value) {
      return this.lastIndexOf(value) >= 0;
   }

    TFloatList grep(TFloatProcedure condition) {
    TFloatArrayList list = std::make_shared<TFloatArrayList>();

      for (int i = 0; i < this._pos; i++) {
         if (condition.execute(this._data[i])) {
            list.push_back(this._data[i]);
         }
      }

    return list;
   }

    TFloatList inverseGrep(TFloatProcedure condition) {
    TFloatArrayList list = std::make_shared<TFloatArrayList>();

      for (int i = 0; i < this._pos; i++) {
         if (!condition.execute(this._data[i])) {
            list.push_back(this._data[i]);
         }
      }

    return list;
   }

    float max() {
      if (this.size() == 0) {
         throw IllegalStateException("cannot find maximum of an empty list");
      } else {
    float max = float.NEGATIVE_INFINITY;

         for (int i = 0; i < this._pos; i++) {
            if (this._data[i] > max) {
               max = this._data[i];
            }
         }

    return max;
      }
   }

    float min() {
      if (this.size() == 0) {
         throw IllegalStateException("cannot find minimum of an empty list");
      } else {
    float min = float.POSITIVE_INFINITY;

         for (int i = 0; i < this._pos; i++) {
            if (this._data[i] < min) {
               min = this._data[i];
            }
         }

    return min;
      }
   }

    float sum() {
    float sum = 0.0F;

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
      out.writeFloat(this.no_entry_value);
    int len = this._data.length;
      out.writeInt(len);

      for (int i = 0; i < len; i++) {
         out.writeFloat(this._data[i]);
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._pos = in.readInt();
      this.no_entry_value = in.readFloat();
    int len = in.readInt();
      this._data = new float[len];

      for (int i = 0; i < len; i++) {
         this._data[i] = in.readFloat();
      }
   }
}
} // namespace array
} // namespace list
} // namespace trove
} // namespace gnu
