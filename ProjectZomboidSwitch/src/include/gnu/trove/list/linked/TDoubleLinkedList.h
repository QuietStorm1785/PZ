#pragma once
#include <list>
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
#include "gnu/trove/list/linked/TDoubleLinkedList/1.h"
#include "gnu/trove/list/linked/TDoubleLinkedList/TDoubleLink.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TDoubleLinkedList {
public:
    double no_entry_value;
    int size;
    TDoubleLink head = nullptr;
    TDoubleLink tail = this.head;

    public TDoubleLinkedList() {
   }

    public TDoubleLinkedList(double no_entry_value) {
      this.no_entry_value = no_entry_value;
   }

    public TDoubleLinkedList(TDoubleList list) {
      this.no_entry_value = list.getNoEntryValue();
    TDoubleIterator iterator = list.iterator();

      while (iterator.hasNext()) {
    double next = iterator.next();
         this.push_back(next);
      }
   }

    double getNoEntryValue() {
      return this.no_entry_value;
   }

    int size() {
      return this.size;
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    bool add(double val) {
    TDoubleLink l = std::make_shared<TDoubleLink>(val);
      if (no(this.head)) {
         this.head = l;
         this.tail = l;
      } else {
         l.setPrevious(this.tail);
         this.tail.setNext(l);
         this.tail = l;
      }

      this.size++;
    return true;
   }

    void add(double[] vals) {
    for (auto& val : vals)         this.push_back(val);
      }
   }

    void add(double[] vals, int offset, int length) {
      for (int i = 0; i < length; i++) {
    double val = vals[offset + i];
         this.push_back(val);
      }
   }

    void insert(int offset, double value) {
    TDoubleLinkedList tmp = std::make_shared<TDoubleLinkedList>();
      tmp.push_back(value);
      this.insert(offset, tmp);
   }

    void insert(int offset, double[] values) {
      this.insert(offset, link(values, 0, values.length));
   }

    void insert(int offset, double[] values, int valOffset, int len) {
      this.insert(offset, link(values, valOffset, len));
   }

    void insert(int offset, TDoubleLinkedList tmp) {
    TDoubleLink l = this.getLinkAt(offset);
      this.size = this.size + tmp.size;
      if (l == this.head) {
         tmp.tail.setNext(this.head);
         this.head.setPrevious(tmp.tail);
         this.head = tmp.head;
      } else {
         if (no(l)) {
            if (this.size == 0) {
               this.head = tmp.head;
               this.tail = tmp.tail;
            } else {
               this.tail.setNext(tmp.head);
               tmp.head.setPrevious(this.tail);
               this.tail = tmp.tail;
            }
         } else {
    TDoubleLink prev = l.getPrevious();
            l.getPrevious().setNext(tmp.head);
            tmp.tail.setNext(l);
            l.setPrevious(tmp.tail);
            tmp.head.setPrevious(prev);
         }
      }
   }

    static TDoubleLinkedList link(double[] values, int valOffset, int len) {
    TDoubleLinkedList ret = std::make_shared<TDoubleLinkedList>();

      for (int i = 0; i < len; i++) {
         ret.push_back(values[valOffset + i]);
      }

    return ret;
   }

    double get(int offset) {
      if (offset > this.size) {
         throw IndexOutOfBoundsException("index " + offset + " exceeds size " + this.size);
      } else {
    TDoubleLink l = this.getLinkAt(offset);
    return no();
      }
   }

    TDoubleLink getLinkAt(int offset) {
      if (offset >= this.size()) {
    return nullptr;
      } else {
         return offset <= this.size() >>> 1 ? getLink(this.head, 0, offset, true) : getLink(this.tail, this.size() - 1, offset, false);
      }
   }

    static TDoubleLink getLink(TDoubleLink l, int idx, int offset) {
    return getLink();
   }

    static TDoubleLink getLink(TDoubleLink l, int idx, int offset, bool next) {
    int i = idx;

      while (got(l)) {
         if (i == offset) {
    return l;
         }

         i += next ? 1 : -1;
         l = next ? l.getNext() : l.getPrevious();
      }

    return nullptr;
   }

    double set(int offset, double val) {
      if (offset > this.size) {
         throw IndexOutOfBoundsException("index " + offset + " exceeds size " + this.size);
      } else {
    TDoubleLink l = this.getLinkAt(offset);
         if (no(l)) {
            throw IndexOutOfBoundsException("at offset " + offset);
         } else {
    double prev = l.getValue();
            l.setValue(val);
    return prev;
         }
      }
   }

    void set(int offset, double[] values) {
      this.set(offset, values, 0, values.length);
   }

    void set(int offset, double[] values, int valOffset, int length) {
      for (int i = 0; i < length; i++) {
    double value = values[valOffset + i];
         this.set(offset + i, value);
      }
   }

    double replace(int offset, double val) {
      return this.set(offset, val);
   }

    void clear() {
      this.size = 0;
      this.head = nullptr;
      this.tail = nullptr;
   }

    bool remove(double value) {
    bool changed = false;

      for (TDoubleLink l = this.head; got(l); l = l.getNext()) {
         if (l.getValue() == value) {
            changed = true;
            this.removeLink(l);
         }
      }

    return changed;
   }

    void removeLink(TDoubleLink l) {
      if (!no(l)) {
         this.size--;
    TDoubleLink prev = l.getPrevious();
    TDoubleLink next = l.getNext();
         if (got(prev)) {
            prev.setNext(next);
         } else {
            this.head = next;
         }

         if (got(next)) {
            next.setPrevious(prev);
         } else {
            this.tail = prev;
         }

         l.setNext(nullptr);
         l.setPrevious(nullptr);
      }
   }

    bool containsAll(Collection<?> collection) {
      if (this.empty()) {
    return false;
      } else {
    for (auto& o : collection)            if (!(dynamic_cast<double*>(o) != nullptr)) {
    return false;
            }

    double i = (double)o;
            if (!this.contains(i)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(TDoubleCollection collection) {
      if (this.empty()) {
    return false;
      } else {
    TDoubleIterator it = collection.iterator();

         while (it.hasNext()) {
    double i = it.next();
            if (!this.contains(i)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(double[] array) {
      if (this.empty()) {
    return false;
      } else {
    for (auto& i : array)            if (!this.contains(i)) {
    return false;
            }
         }

    return true;
      }
   }

    bool addAll(Collection<? extends) {
    bool ret = false;

    for (auto& v : collection)         if (this.push_back(v)) {
            ret = true;
         }
      }

    return ret;
   }

    bool addAll(TDoubleCollection collection) {
    bool ret = false;
    TDoubleIterator it = collection.iterator();

      while (it.hasNext()) {
    double i = it.next();
         if (this.push_back(i)) {
            ret = true;
         }
      }

    return ret;
   }

    bool addAll(double[] array) {
    bool ret = false;

    for (auto& i : array)         if (this.push_back(i)) {
            ret = true;
         }
      }

    return ret;
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

    bool retainAll(double[] array) {
      Arrays.sort(array);
    bool modified = false;
    TDoubleIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (Arrays.binarySearch(array, iter.next()) < 0) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool removeAll(Collection<?> collection) {
    bool modified = false;
    TDoubleIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool removeAll(TDoubleCollection collection) {
    bool modified = false;
    TDoubleIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool removeAll(double[] array) {
      Arrays.sort(array);
    bool modified = false;
    TDoubleIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (Arrays.binarySearch(array, iter.next()) >= 0) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    double removeAt(int offset) {
    TDoubleLink l = this.getLinkAt(offset);
      if (no(l)) {
         throw ArrayIndexOutOfBoundsException("no elemenet at " + offset);
      } else {
    double prev = l.getValue();
         this.removeLink(l);
    return prev;
      }
   }

    void remove(int offset, int length) {
      for (int i = 0; i < length; i++) {
         this.removeAt(offset);
      }
   }

    void transformValues(TDoubleFunction function) {
      for (TDoubleLink l = this.head; got(l); l = l.getNext()) {
         l.setValue(function.execute(l.getValue()));
      }
   }

    void reverse() {
    TDoubleLink h = this.head;
    TDoubleLink t = this.tail;
    TDoubleLink l = this.head;

      while (got(l)) {
    TDoubleLink next = l.getNext();
    TDoubleLink prev = l.getPrevious();
    TDoubleLink tmp = l;
         l = l.getNext();
         tmp.setNext(prev);
         tmp.setPrevious(next);
      }

      this.head = t;
      this.tail = h;
   }

    void reverse(int from, int to) {
      if (from > to) {
         throw IllegalArgumentException("from > to : " + from + ">" + to);
      } else {
    TDoubleLink start = this.getLinkAt(from);
    TDoubleLink stop = this.getLinkAt(to);
    TDoubleLink tmp = nullptr;
    TDoubleLink tmpHead = start.getPrevious();
    TDoubleLink l = start;

         while (l != stop) {
    TDoubleLink next = l.getNext();
    TDoubleLink prev = l.getPrevious();
            tmp = l;
            l = l.getNext();
            tmp.setNext(prev);
            tmp.setPrevious(next);
         }

         if (got(tmp)) {
            tmpHead.setNext(tmp);
            stop.setPrevious(tmpHead);
         }

         start.setNext(stop);
         stop.setPrevious(start);
      }
   }

    void shuffle(Random rand) {
      for (int i = 0; i < this.size; i++) {
    TDoubleLink l = this.getLinkAt(rand.nextInt(this.size()));
         this.removeLink(l);
         this.push_back(l.getValue());
      }
   }

    TDoubleList subList(int begin, int end) {
      if (end < begin) {
         throw IllegalArgumentException("begin index " + begin + " greater than end index " + end);
      } else if (this.size < begin) {
         throw IllegalArgumentException("begin index " + begin + " greater than last index " + this.size);
      } else if (begin < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (end > this.size) {
         throw IndexOutOfBoundsException("end index < " + this.size);
      } else {
    TDoubleLinkedList ret = std::make_shared<TDoubleLinkedList>();
    TDoubleLink tmp = this.getLinkAt(begin);

         for (int i = begin; i < end; i++) {
            ret.push_back(tmp.getValue());
            tmp = tmp.getNext();
         }

    return ret;
      }
   }

   public double[] toArray() {
      return this.toArray(new double[this.size], 0, this.size);
   }

   public double[] toArray(int offset, int len) {
      return this.toArray(new double[len], offset, 0, len);
   }

   public double[] toArray(double[] dest) {
      return this.toArray(dest, 0, this.size);
   }

   public double[] toArray(double[] dest, int offset, int len) {
      return this.toArray(dest, offset, 0, len);
   }

   public double[] toArray(double[] dest, int source_pos, int dest_pos, int len) {
      if (len == 0) {
    return dest;
      } else if (source_pos >= 0 && source_pos < this.size()) {
    TDoubleLink tmp = this.getLinkAt(source_pos);

         for (int i = 0; i < len; i++) {
            dest[dest_pos + i] = tmp.getValue();
            tmp = tmp.getNext();
         }

    return dest;
      } else {
         throw ArrayIndexOutOfBoundsException(source_pos);
      }
   }

    bool forEach(TDoubleProcedure procedure) {
      for (TDoubleLink l = this.head; got(l); l = l.getNext()) {
         if (!procedure.execute(l.getValue())) {
    return false;
         }
      }

    return true;
   }

    bool forEachDescending(TDoubleProcedure procedure) {
      for (TDoubleLink l = this.tail; got(l); l = l.getPrevious()) {
         if (!procedure.execute(l.getValue())) {
    return false;
         }
      }

    return true;
   }

    void sort() {
      this.sort(0, this.size);
   }

    void sort(int fromIndex, int toIndex) {
    TDoubleList tmp = this.subList(fromIndex, toIndex);
      double[] vals = tmp.toArray();
      Arrays.sort(vals);
      this.set(fromIndex, vals);
   }

    void fill(double val) {
      this.fill(0, this.size, val);
   }

    void fill(int fromIndex, int toIndex, double val) {
      if (fromIndex < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else {
    TDoubleLink l = this.getLinkAt(fromIndex);
         if (toIndex > this.size) {
            for (int i = fromIndex; i < this.size; i++) {
               l.setValue(val);
               l = l.getNext();
            }

            for (int i = this.size; i < toIndex; i++) {
               this.push_back(val);
            }
         } else {
            for (int i = fromIndex; i < toIndex; i++) {
               l.setValue(val);
               l = l.getNext();
            }
         }
      }
   }

    int binarySearch(double value) {
      return this.binarySearch(value, 0, this.size());
   }

    int binarySearch(double value, int fromIndex, int toIndex) {
      if (fromIndex < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (toIndex > this.size) {
         throw IndexOutOfBoundsException("end index > size: " + toIndex + " > " + this.size);
      } else if (toIndex < fromIndex) {
         return -(fromIndex + 1);
      } else {
    int from = fromIndex;
    TDoubleLink fromLink = this.getLinkAt(fromIndex);
    int to = toIndex;

         while (from < to) {
    int mid = from + to >>> 1;
    TDoubleLink middle = getLink(fromLink, from, mid);
            if (middle.getValue() == value) {
    return mid;
            }

            if (middle.getValue() < value) {
               from = mid + 1;
               fromLink = middle.next;
            } else {
               to = mid - 1;
            }
         }

         return -(from + 1);
      }
   }

    int indexOf(double value) {
      return this.indexOf(0, value);
   }

    int indexOf(int offset, double value) {
    int count = offset;

      for (TDoubleLink l = this.getLinkAt(offset); got(l.getNext()); l = l.getNext()) {
         if (l.getValue() == value) {
    return count;
         }

         count++;
      }

      return -1;
   }

    int lastIndexOf(double value) {
      return this.lastIndexOf(0, value);
   }

    int lastIndexOf(int offset, double value) {
      if (this.empty()) {
         return -1;
      } else {
    int last = -1;
    int count = offset;

         for (TDoubleLink l = this.getLinkAt(offset); got(l.getNext()); l = l.getNext()) {
            if (l.getValue() == value) {
               last = count;
            }

            count++;
         }

    return last;
      }
   }

    bool contains(double value) {
      if (this.empty()) {
    return false;
      } else {
         for (TDoubleLink l = this.head; got(l); l = l.getNext()) {
            if (l.getValue() == value) {
    return true;
            }
         }

    return false;
      }
   }

    TDoubleIterator iterator() {
      return std::make_shared<1>(this);
   }

    TDoubleList grep(TDoubleProcedure condition) {
    TDoubleList ret = std::make_shared<TDoubleLinkedList>();

      for (TDoubleLink l = this.head; got(l); l = l.getNext()) {
         if (condition.execute(l.getValue())) {
            ret.push_back(l.getValue());
         }
      }

    return ret;
   }

    TDoubleList inverseGrep(TDoubleProcedure condition) {
    TDoubleList ret = std::make_shared<TDoubleLinkedList>();

      for (TDoubleLink l = this.head; got(l); l = l.getNext()) {
         if (!condition.execute(l.getValue())) {
            ret.push_back(l.getValue());
         }
      }

    return ret;
   }

    double max() {
    double ret = double.NEGATIVE_INFINITY;
      if (this.empty()) {
         throw std::make_unique<IllegalStateException>();
      } else {
         for (TDoubleLink l = this.head; got(l); l = l.getNext()) {
            if (ret < l.getValue()) {
               ret = l.getValue();
            }
         }

    return ret;
      }
   }

    double min() {
    double ret = double.POSITIVE_INFINITY;
      if (this.empty()) {
         throw std::make_unique<IllegalStateException>();
      } else {
         for (TDoubleLink l = this.head; got(l); l = l.getNext()) {
            if (ret > l.getValue()) {
               ret = l.getValue();
            }
         }

    return ret;
      }
   }

    double sum() {
    double sum = 0.0;

      for (TDoubleLink l = this.head; got(l); l = l.getNext()) {
         sum += l.getValue();
      }

    return sum;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeDouble(this.no_entry_value);
      out.writeInt(this.size);
    TDoubleIterator iterator = this.iterator();

      while (iterator.hasNext()) {
    double next = iterator.next();
         out.writeDouble(next);
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this.no_entry_value = in.readDouble();
    int len = in.readInt();

      for (int i = 0; i < len; i++) {
         this.push_back(in.readDouble());
      }
   }

    static bool got(void* ref) {
      return ref != nullptr;
   }

    static bool no(void* ref) {
    return ref = = nullptr;
   }

    bool equals(void* o) {
      if (this == o) {
    return true;
      } else if (o != nullptr && this.getClass() == o.getClass()) {
    TDoubleLinkedList that = (TDoubleLinkedList)o;
         if (this.no_entry_value != that.no_entry_value) {
    return false;
         } else if (this.size != that.size) {
    return false;
         } else {
    TDoubleIterator iterator = this.iterator();
    TDoubleIterator thatIterator = that.iterator();

            while (iterator.hasNext()) {
               if (!thatIterator.hasNext()) {
    return false;
               }

               if (iterator.next() != thatIterator.next()) {
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
    int result = HashFunctions.hash(this.no_entry_value);
      result = 31 * result + this.size;
    TDoubleIterator iterator = this.iterator();

      while (iterator.hasNext()) {
         result = 31 * result + HashFunctions.hash(iterator.next());
      }

    return result;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
    TDoubleIterator it = this.iterator();

      while (it.hasNext()) {
    double next = it.next();
         buf.append(next);
         if (it.hasNext()) {
            buf.append(", ");
         }
      }

      buf.append("}");
      return buf;
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
