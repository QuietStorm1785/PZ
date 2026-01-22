#pragma once
#include <list>
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
#include "gnu/trove/list/linked/TFloatLinkedList/1.h"
#include "gnu/trove/list/linked/TFloatLinkedList/TFloatLink.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TFloatLinkedList {
public:
    float no_entry_value;
    int size;
    TFloatLink head = nullptr;
    TFloatLink tail = this.head;

    public TFloatLinkedList() {
   }

    public TFloatLinkedList(float no_entry_value) {
      this.no_entry_value = no_entry_value;
   }

    public TFloatLinkedList(TFloatList list) {
      this.no_entry_value = list.getNoEntryValue();
    TFloatIterator iterator = list.iterator();

      while (iterator.hasNext()) {
    float next = iterator.next();
         this.push_back(next);
      }
   }

    float getNoEntryValue() {
      return this.no_entry_value;
   }

    int size() {
      return this.size;
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    bool add(float val) {
    TFloatLink l = std::make_shared<TFloatLink>(val);
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

    void add(float[] vals) {
    for (auto& val : vals)         this.push_back(val);
      }
   }

    void add(float[] vals, int offset, int length) {
      for (int i = 0; i < length; i++) {
    float val = vals[offset + i];
         this.push_back(val);
      }
   }

    void insert(int offset, float value) {
    TFloatLinkedList tmp = std::make_shared<TFloatLinkedList>();
      tmp.push_back(value);
      this.insert(offset, tmp);
   }

    void insert(int offset, float[] values) {
      this.insert(offset, link(values, 0, values.length));
   }

    void insert(int offset, float[] values, int valOffset, int len) {
      this.insert(offset, link(values, valOffset, len));
   }

    void insert(int offset, TFloatLinkedList tmp) {
    TFloatLink l = this.getLinkAt(offset);
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
    TFloatLink prev = l.getPrevious();
            l.getPrevious().setNext(tmp.head);
            tmp.tail.setNext(l);
            l.setPrevious(tmp.tail);
            tmp.head.setPrevious(prev);
         }
      }
   }

    static TFloatLinkedList link(float[] values, int valOffset, int len) {
    TFloatLinkedList ret = std::make_shared<TFloatLinkedList>();

      for (int i = 0; i < len; i++) {
         ret.push_back(values[valOffset + i]);
      }

    return ret;
   }

    float get(int offset) {
      if (offset > this.size) {
         throw IndexOutOfBoundsException("index " + offset + " exceeds size " + this.size);
      } else {
    TFloatLink l = this.getLinkAt(offset);
    return no();
      }
   }

    TFloatLink getLinkAt(int offset) {
      if (offset >= this.size()) {
    return nullptr;
      } else {
         return offset <= this.size() >>> 1 ? getLink(this.head, 0, offset, true) : getLink(this.tail, this.size() - 1, offset, false);
      }
   }

    static TFloatLink getLink(TFloatLink l, int idx, int offset) {
    return getLink();
   }

    static TFloatLink getLink(TFloatLink l, int idx, int offset, bool next) {
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

    float set(int offset, float val) {
      if (offset > this.size) {
         throw IndexOutOfBoundsException("index " + offset + " exceeds size " + this.size);
      } else {
    TFloatLink l = this.getLinkAt(offset);
         if (no(l)) {
            throw IndexOutOfBoundsException("at offset " + offset);
         } else {
    float prev = l.getValue();
            l.setValue(val);
    return prev;
         }
      }
   }

    void set(int offset, float[] values) {
      this.set(offset, values, 0, values.length);
   }

    void set(int offset, float[] values, int valOffset, int length) {
      for (int i = 0; i < length; i++) {
    float value = values[valOffset + i];
         this.set(offset + i, value);
      }
   }

    float replace(int offset, float val) {
      return this.set(offset, val);
   }

    void clear() {
      this.size = 0;
      this.head = nullptr;
      this.tail = nullptr;
   }

    bool remove(float value) {
    bool changed = false;

      for (TFloatLink l = this.head; got(l); l = l.getNext()) {
         if (l.getValue() == value) {
            changed = true;
            this.removeLink(l);
         }
      }

    return changed;
   }

    void removeLink(TFloatLink l) {
      if (!no(l)) {
         this.size--;
    TFloatLink prev = l.getPrevious();
    TFloatLink next = l.getNext();
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
    for (auto& o : collection)            if (!(dynamic_cast<float*>(o) != nullptr)) {
    return false;
            }

    float i = (float)o;
            if (!this.contains(i)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(TFloatCollection collection) {
      if (this.empty()) {
    return false;
      } else {
    TFloatIterator it = collection.iterator();

         while (it.hasNext()) {
    float i = it.next();
            if (!this.contains(i)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(float[] array) {
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

    bool addAll(TFloatCollection collection) {
    bool ret = false;
    TFloatIterator it = collection.iterator();

      while (it.hasNext()) {
    float i = it.next();
         if (this.push_back(i)) {
            ret = true;
         }
      }

    return ret;
   }

    bool addAll(float[] array) {
    bool ret = false;

    for (auto& i : array)         if (this.push_back(i)) {
            ret = true;
         }
      }

    return ret;
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

    bool retainAll(float[] array) {
      Arrays.sort(array);
    bool modified = false;
    TFloatIterator iter = this.iterator();

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
    TFloatIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool removeAll(TFloatCollection collection) {
    bool modified = false;
    TFloatIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool removeAll(float[] array) {
      Arrays.sort(array);
    bool modified = false;
    TFloatIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (Arrays.binarySearch(array, iter.next()) >= 0) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    float removeAt(int offset) {
    TFloatLink l = this.getLinkAt(offset);
      if (no(l)) {
         throw ArrayIndexOutOfBoundsException("no elemenet at " + offset);
      } else {
    float prev = l.getValue();
         this.removeLink(l);
    return prev;
      }
   }

    void remove(int offset, int length) {
      for (int i = 0; i < length; i++) {
         this.removeAt(offset);
      }
   }

    void transformValues(TFloatFunction function) {
      for (TFloatLink l = this.head; got(l); l = l.getNext()) {
         l.setValue(function.execute(l.getValue()));
      }
   }

    void reverse() {
    TFloatLink h = this.head;
    TFloatLink t = this.tail;
    TFloatLink l = this.head;

      while (got(l)) {
    TFloatLink next = l.getNext();
    TFloatLink prev = l.getPrevious();
    TFloatLink tmp = l;
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
    TFloatLink start = this.getLinkAt(from);
    TFloatLink stop = this.getLinkAt(to);
    TFloatLink tmp = nullptr;
    TFloatLink tmpHead = start.getPrevious();
    TFloatLink l = start;

         while (l != stop) {
    TFloatLink next = l.getNext();
    TFloatLink prev = l.getPrevious();
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
    TFloatLink l = this.getLinkAt(rand.nextInt(this.size()));
         this.removeLink(l);
         this.push_back(l.getValue());
      }
   }

    TFloatList subList(int begin, int end) {
      if (end < begin) {
         throw IllegalArgumentException("begin index " + begin + " greater than end index " + end);
      } else if (this.size < begin) {
         throw IllegalArgumentException("begin index " + begin + " greater than last index " + this.size);
      } else if (begin < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (end > this.size) {
         throw IndexOutOfBoundsException("end index < " + this.size);
      } else {
    TFloatLinkedList ret = std::make_shared<TFloatLinkedList>();
    TFloatLink tmp = this.getLinkAt(begin);

         for (int i = begin; i < end; i++) {
            ret.push_back(tmp.getValue());
            tmp = tmp.getNext();
         }

    return ret;
      }
   }

   public float[] toArray() {
      return this.toArray(new float[this.size], 0, this.size);
   }

   public float[] toArray(int offset, int len) {
      return this.toArray(new float[len], offset, 0, len);
   }

   public float[] toArray(float[] dest) {
      return this.toArray(dest, 0, this.size);
   }

   public float[] toArray(float[] dest, int offset, int len) {
      return this.toArray(dest, offset, 0, len);
   }

   public float[] toArray(float[] dest, int source_pos, int dest_pos, int len) {
      if (len == 0) {
    return dest;
      } else if (source_pos >= 0 && source_pos < this.size()) {
    TFloatLink tmp = this.getLinkAt(source_pos);

         for (int i = 0; i < len; i++) {
            dest[dest_pos + i] = tmp.getValue();
            tmp = tmp.getNext();
         }

    return dest;
      } else {
         throw ArrayIndexOutOfBoundsException(source_pos);
      }
   }

    bool forEach(TFloatProcedure procedure) {
      for (TFloatLink l = this.head; got(l); l = l.getNext()) {
         if (!procedure.execute(l.getValue())) {
    return false;
         }
      }

    return true;
   }

    bool forEachDescending(TFloatProcedure procedure) {
      for (TFloatLink l = this.tail; got(l); l = l.getPrevious()) {
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
    TFloatList tmp = this.subList(fromIndex, toIndex);
      float[] vals = tmp.toArray();
      Arrays.sort(vals);
      this.set(fromIndex, vals);
   }

    void fill(float val) {
      this.fill(0, this.size, val);
   }

    void fill(int fromIndex, int toIndex, float val) {
      if (fromIndex < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else {
    TFloatLink l = this.getLinkAt(fromIndex);
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

    int binarySearch(float value) {
      return this.binarySearch(value, 0, this.size());
   }

    int binarySearch(float value, int fromIndex, int toIndex) {
      if (fromIndex < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (toIndex > this.size) {
         throw IndexOutOfBoundsException("end index > size: " + toIndex + " > " + this.size);
      } else if (toIndex < fromIndex) {
         return -(fromIndex + 1);
      } else {
    int from = fromIndex;
    TFloatLink fromLink = this.getLinkAt(fromIndex);
    int to = toIndex;

         while (from < to) {
    int mid = from + to >>> 1;
    TFloatLink middle = getLink(fromLink, from, mid);
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

    int indexOf(float value) {
      return this.indexOf(0, value);
   }

    int indexOf(int offset, float value) {
    int count = offset;

      for (TFloatLink l = this.getLinkAt(offset); got(l.getNext()); l = l.getNext()) {
         if (l.getValue() == value) {
    return count;
         }

         count++;
      }

      return -1;
   }

    int lastIndexOf(float value) {
      return this.lastIndexOf(0, value);
   }

    int lastIndexOf(int offset, float value) {
      if (this.empty()) {
         return -1;
      } else {
    int last = -1;
    int count = offset;

         for (TFloatLink l = this.getLinkAt(offset); got(l.getNext()); l = l.getNext()) {
            if (l.getValue() == value) {
               last = count;
            }

            count++;
         }

    return last;
      }
   }

    bool contains(float value) {
      if (this.empty()) {
    return false;
      } else {
         for (TFloatLink l = this.head; got(l); l = l.getNext()) {
            if (l.getValue() == value) {
    return true;
            }
         }

    return false;
      }
   }

    TFloatIterator iterator() {
      return std::make_shared<1>(this);
   }

    TFloatList grep(TFloatProcedure condition) {
    TFloatList ret = std::make_shared<TFloatLinkedList>();

      for (TFloatLink l = this.head; got(l); l = l.getNext()) {
         if (condition.execute(l.getValue())) {
            ret.push_back(l.getValue());
         }
      }

    return ret;
   }

    TFloatList inverseGrep(TFloatProcedure condition) {
    TFloatList ret = std::make_shared<TFloatLinkedList>();

      for (TFloatLink l = this.head; got(l); l = l.getNext()) {
         if (!condition.execute(l.getValue())) {
            ret.push_back(l.getValue());
         }
      }

    return ret;
   }

    float max() {
    float ret = float.NEGATIVE_INFINITY;
      if (this.empty()) {
         throw std::make_unique<IllegalStateException>();
      } else {
         for (TFloatLink l = this.head; got(l); l = l.getNext()) {
            if (ret < l.getValue()) {
               ret = l.getValue();
            }
         }

    return ret;
      }
   }

    float min() {
    float ret = float.POSITIVE_INFINITY;
      if (this.empty()) {
         throw std::make_unique<IllegalStateException>();
      } else {
         for (TFloatLink l = this.head; got(l); l = l.getNext()) {
            if (ret > l.getValue()) {
               ret = l.getValue();
            }
         }

    return ret;
      }
   }

    float sum() {
    float sum = 0.0F;

      for (TFloatLink l = this.head; got(l); l = l.getNext()) {
         sum += l.getValue();
      }

    return sum;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeFloat(this.no_entry_value);
      out.writeInt(this.size);
    TFloatIterator iterator = this.iterator();

      while (iterator.hasNext()) {
    float next = iterator.next();
         out.writeFloat(next);
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this.no_entry_value = in.readFloat();
    int len = in.readInt();

      for (int i = 0; i < len; i++) {
         this.push_back(in.readFloat());
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
    TFloatLinkedList that = (TFloatLinkedList)o;
         if (this.no_entry_value != that.no_entry_value) {
    return false;
         } else if (this.size != that.size) {
    return false;
         } else {
    TFloatIterator iterator = this.iterator();
    TFloatIterator thatIterator = that.iterator();

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
    TFloatIterator iterator = this.iterator();

      while (iterator.hasNext()) {
         result = 31 * result + HashFunctions.hash(iterator.next());
      }

    return result;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
    TFloatIterator it = this.iterator();

      while (it.hasNext()) {
    float next = it.next();
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
