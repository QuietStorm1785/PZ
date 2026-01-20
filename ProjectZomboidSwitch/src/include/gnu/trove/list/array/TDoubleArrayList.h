#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/iterator/TDoubleIterator.h"
#include "gnu/trove/list/TDoubleList.h"
#include "gnu/trove/list/array/TDoubleArrayList/1.h"
#include "gnu/trove/list/array/TDoubleArrayList/TDoubleArrayIterator.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace list {
namespace array {


class TDoubleArrayList {
public:
    static const long serialVersionUID = 1L;
   protected double[] _data;
    int _pos;
    static const int DEFAULT_CAPACITY = 10;
    double no_entry_value;

    public TDoubleArrayList() {
      this(10, 0.0);
   }

    public TDoubleArrayList(int capacity) {
      this(capacity, 0.0);
   }

    public TDoubleArrayList(int capacity, double no_entry_value) {
      this._data = new double[capacity];
      this._pos = 0;
      this.no_entry_value = no_entry_value;
   }

    public TDoubleArrayList(TDoubleCollection collection) {
      this(collection.size());
      this.addAll(collection);
   }

    public TDoubleArrayList(double[] values) {
      this(values.length);
      this.push_back(values);
   }

    protected TDoubleArrayList(double[] values, double no_entry_value, bool wrap) {
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

    static TDoubleArrayList wrap(double[] values) {
    return wrap();
   }

    static TDoubleArrayList wrap(double[] values, double no_entry_value) {
      return std::make_shared<1>(values, no_entry_value, true);
   }

    double getNoEntryValue() {
      return this.no_entry_value;
   }

    void ensureCapacity(int capacity) {
      if (capacity > this._data.length) {
    int newCap = Math.max(this._data.length << 1, capacity);
         double[] tmp = new double[newCap];
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
         double[] tmp = new double[this.size()];
         this.toArray(tmp, 0, tmp.length);
         this._data = tmp;
      }
   }

    bool add(double val) {
      this.ensureCapacity(this._pos + 1);
      this._data[this._pos++] = val;
    return true;
   }

    void add(double[] vals) {
      this.push_back(vals, 0, vals.length);
   }

    void add(double[] vals, int offset, int length) {
      this.ensureCapacity(this._pos + length);
      System.arraycopy(vals, offset, this._data, this._pos, length);
      this._pos += length;
   }

    void insert(int offset, double value) {
      if (offset == this._pos) {
         this.push_back(value);
      } else {
         this.ensureCapacity(this._pos + 1);
         System.arraycopy(this._data, offset, this._data, offset + 1, this._pos - offset);
         this._data[offset] = value;
         this._pos++;
      }
   }

    void insert(int offset, double[] values) {
      this.insert(offset, values, 0, values.length);
   }

    void insert(int offset, double[] values, int valOffset, int len) {
      if (offset == this._pos) {
         this.push_back(values, valOffset, len);
      } else {
         this.ensureCapacity(this._pos + len);
         System.arraycopy(this._data, offset, this._data, offset + len, this._pos - offset);
         System.arraycopy(values, valOffset, this._data, offset, len);
         this._pos += len;
      }
   }

    double get(int offset) {
      if (offset >= this._pos) {
         throw ArrayIndexOutOfBoundsException(offset);
      } else {
         return this._data[offset];
      }
   }

    double getQuick(int offset) {
      return this._data[offset];
   }

    double set(int offset, double val) {
      if (offset >= this._pos) {
         throw ArrayIndexOutOfBoundsException(offset);
      } else {
    double prev_val = this._data[offset];
         this._data[offset] = val;
    return prev_val;
      }
   }

    double replace(int offset, double val) {
      if (offset >= this._pos) {
         throw ArrayIndexOutOfBoundsException(offset);
      } else {
    double old = this._data[offset];
         this._data[offset] = val;
    return old;
      }
   }

    void set(int offset, double[] values) {
      this.set(offset, values, 0, values.length);
   }

    void set(int offset, double[] values, int valOffset, int length) {
      if (offset >= 0 && offset + length <= this._pos) {
         System.arraycopy(values, valOffset, this._data, offset, length);
      } else {
         throw ArrayIndexOutOfBoundsException(offset);
      }
   }

    void setQuick(int offset, double val) {
      this._data[offset] = val;
   }

    void clear() {
      this.clear(10);
   }

    void clear(int capacity) {
      this._data = new double[capacity];
      this._pos = 0;
   }

    void reset() {
      this._pos = 0;
      Arrays.fill(this._data, this.no_entry_value);
   }

    void resetQuick() {
      this._pos = 0;
   }

    bool remove(double value) {
      for (int index = 0; index < this._pos; index++) {
         if (value == this._data[index]) {
            this.remove(index, 1);
    return true;
         }
      }

    return false;
   }

    double removeAt(int offset) {
    double old = this.get(offset);
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

    TDoubleIterator iterator() {
      return std::make_shared<TDoubleArrayIterator>(this, 0);
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<double*>(element) != nullptr)) {
    return false;
         }

    double c = (double)element;
         if (!this.contains(c)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TDoubleCollection collection) {
      if (this == collection) {
    return true;
      } else {
    TDoubleIterator iter = collection.iterator();

         while (iter.hasNext()) {
    double element = iter.next();
            if (!this.contains(element)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(double[] array) {
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

    for (auto& element : collection)    double e = element;
         if (this.push_back(e)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(TDoubleCollection collection) {
    bool changed = false;
    TDoubleIterator iter = collection.iterator();

      while (iter.hasNext()) {
    double element = iter.next();
         if (this.push_back(element)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(double[] array) {
    bool changed = false;

    for (auto& element : array)         if (this.push_back(element)) {
            changed = true;
         }
      }

    return changed;
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TDoubleIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TDoubleCollection collection) {
      if (this == collection) {
    return false;
      } else {
    bool modified = false;
    TDoubleIterator iter = this.iterator();

         while (iter.hasNext()) {
            if (!collection.contains(iter.next())) {
               iter.remove();
               modified = true;
            }
         }

    return modified;
      }
   }

    bool retainAll(double[] array) {
    bool changed = false;
      Arrays.sort(array);
      double[] data = this._data;
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

    for (auto& element : collection)         if (dynamic_cast<double*>(element) != nullptr) {
    double c = (double)element;
            if (this.remove(c)) {
               changed = true;
            }
         }
      }

    return changed;
   }

    bool removeAll(TDoubleCollection collection) {
      if (collection == this) {
         this.clear();
    return true;
      } else {
    bool changed = false;
    TDoubleIterator iter = collection.iterator();

         while (iter.hasNext()) {
    double element = iter.next();
            if (this.remove(element)) {
               changed = true;
            }
         }

    return changed;
      }
   }

    bool removeAll(double[] array) {
    bool changed = false;
    int i = array.length;

      while (i-- > 0) {
         if (this.remove(array[i])) {
            changed = true;
         }
      }

    return changed;
   }

    void transformValues(TDoubleFunction function) {
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
    double tmp = this._data[i];
      this._data[i] = this._data[j];
      this._data[j] = tmp;
   }

    TDoubleList subList(int begin, int end) {
      if (end < begin) {
         throw IllegalArgumentException("end index " + end + " greater than begin index " + begin);
      } else if (begin < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (end > this._data.length) {
         throw IndexOutOfBoundsException("end index < " + this._data.length);
      } else {
    TDoubleArrayList list = std::make_shared<TDoubleArrayList>(end - begin);

         for (int i = begin; i < end; i++) {
            list.push_back(this._data[i]);
         }

    return list;
      }
   }

   public double[] toArray() {
      return this.toArray(0, this._pos);
   }

   public double[] toArray(int offset, int len) {
      double[] rv = new double[len];
      this.toArray(rv, offset, len);
    return rv;
   }

   public double[] toArray(double[] dest) {
    int len = dest.length;
      if (dest.length > this._pos) {
         len = this._pos;
         dest[len] = this.no_entry_value;
      }

      this.toArray(dest, 0, len);
    return dest;
   }

   public double[] toArray(double[] dest, int offset, int len) {
      if (len == 0) {
    return dest;
      } else if (offset >= 0 && offset < this._pos) {
         System.arraycopy(this._data, offset, dest, 0, len);
    return dest;
      } else {
         throw ArrayIndexOutOfBoundsException(offset);
      }
   }

   public double[] toArray(double[] dest, int source_pos, int dest_pos, int len) {
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
      } else if (dynamic_cast<TDoubleArrayList*>(other) != nullptr) {
    TDoubleArrayList that = (TDoubleArrayList)other;
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

    bool forEach(TDoubleProcedure procedure) {
      for (int i = 0; i < this._pos; i++) {
         if (!procedure.execute(this._data[i])) {
    return false;
         }
      }

    return true;
   }

    bool forEachDescending(TDoubleProcedure procedure) {
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

    void fill(double val) {
      Arrays.fill(this._data, 0, this._pos, val);
   }

    void fill(int fromIndex, int toIndex, double val) {
      if (toIndex > this._pos) {
         this.ensureCapacity(toIndex);
         this._pos = toIndex;
      }

      Arrays.fill(this._data, fromIndex, toIndex, val);
   }

    int binarySearch(double value) {
      return this.binarySearch(value, 0, this._pos);
   }

    int binarySearch(double value, int fromIndex, int toIndex) {
      if (fromIndex < 0) {
         throw ArrayIndexOutOfBoundsException(fromIndex);
      } else if (toIndex > this._pos) {
         throw ArrayIndexOutOfBoundsException(toIndex);
      } else {
    int low = fromIndex;
    int high = toIndex - 1;

         while (low <= high) {
    int mid = low + high >>> 1;
    double midVal = this._data[mid];
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

    int indexOf(double value) {
      return this.indexOf(0, value);
   }

    int indexOf(int offset, double value) {
      for (int i = offset; i < this._pos; i++) {
         if (this._data[i] == value) {
    return i;
         }
      }

      return -1;
   }

    int lastIndexOf(double value) {
      return this.lastIndexOf(this._pos, value);
   }

    int lastIndexOf(int offset, double value) {
    int i = offset;

      while (i-- > 0) {
         if (this._data[i] == value) {
    return i;
         }
      }

      return -1;
   }

    bool contains(double value) {
      return this.lastIndexOf(value) >= 0;
   }

    TDoubleList grep(TDoubleProcedure condition) {
    TDoubleArrayList list = std::make_shared<TDoubleArrayList>();

      for (int i = 0; i < this._pos; i++) {
         if (condition.execute(this._data[i])) {
            list.push_back(this._data[i]);
         }
      }

    return list;
   }

    TDoubleList inverseGrep(TDoubleProcedure condition) {
    TDoubleArrayList list = std::make_shared<TDoubleArrayList>();

      for (int i = 0; i < this._pos; i++) {
         if (!condition.execute(this._data[i])) {
            list.push_back(this._data[i]);
         }
      }

    return list;
   }

    double max() {
      if (this.size() == 0) {
         throw IllegalStateException("cannot find maximum of an empty list");
      } else {
    double max = double.NEGATIVE_INFINITY;

         for (int i = 0; i < this._pos; i++) {
            if (this._data[i] > max) {
               max = this._data[i];
            }
         }

    return max;
      }
   }

    double min() {
      if (this.size() == 0) {
         throw IllegalStateException("cannot find minimum of an empty list");
      } else {
    double min = double.POSITIVE_INFINITY;

         for (int i = 0; i < this._pos; i++) {
            if (this._data[i] < min) {
               min = this._data[i];
            }
         }

    return min;
      }
   }

    double sum() {
    double sum = 0.0;

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
      out.writeDouble(this.no_entry_value);
    int len = this._data.length;
      out.writeInt(len);

      for (int i = 0; i < len; i++) {
         out.writeDouble(this._data[i]);
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._pos = in.readInt();
      this.no_entry_value = in.readDouble();
    int len = in.readInt();
      this._data = new double[len];

      for (int i = 0; i < len; i++) {
         this._data[i] = in.readDouble();
      }
   }
}
} // namespace array
} // namespace list
} // namespace trove
} // namespace gnu
