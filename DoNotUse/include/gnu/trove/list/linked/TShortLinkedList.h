#pragma once
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/iterator/TShortIterator.h"
#include "gnu/trove/list/TShortList.h"
#include "gnu/trove/list/linked/TShortLinkedList/1.h"
#include "gnu/trove/list/linked/TShortLinkedList/TShortLink.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TShortLinkedList {
public:
    short no_entry_value;
    int size;
    TShortLink head = nullptr;
    TShortLink tail = this.head;

    public TShortLinkedList() {
   }

    public TShortLinkedList(short no_entry_value) {
      this.no_entry_value = no_entry_value;
   }

    public TShortLinkedList(TShortList list) {
      this.no_entry_value = list.getNoEntryValue();
    TShortIterator iterator = list.iterator();

      while (iterator.hasNext()) {
    short next = iterator.next();
         this.push_back(next);
      }
   }

    short getNoEntryValue() {
      return this.no_entry_value;
   }

    int size() {
      return this.size;
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    bool add(short val) {
    TShortLink l = std::make_shared<TShortLink>(val);
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

    void add(short[] vals) {
    for (auto& val : vals)         this.push_back(val);
      }
   }

    void add(short[] vals, int offset, int length) {
      for (int i = 0; i < length; i++) {
    short val = vals[offset + i];
         this.push_back(val);
      }
   }

    void insert(int offset, short value) {
    TShortLinkedList tmp = std::make_shared<TShortLinkedList>();
      tmp.push_back(value);
      this.insert(offset, tmp);
   }

    void insert(int offset, short[] values) {
      this.insert(offset, link(values, 0, values.length));
   }

    void insert(int offset, short[] values, int valOffset, int len) {
      this.insert(offset, link(values, valOffset, len));
   }

    void insert(int offset, TShortLinkedList tmp) {
    TShortLink l = this.getLinkAt(offset);
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
    TShortLink prev = l.getPrevious();
            l.getPrevious().setNext(tmp.head);
            tmp.tail.setNext(l);
            l.setPrevious(tmp.tail);
            tmp.head.setPrevious(prev);
         }
      }
   }

    static TShortLinkedList link(short[] values, int valOffset, int len) {
    TShortLinkedList ret = std::make_shared<TShortLinkedList>();

      for (int i = 0; i < len; i++) {
         ret.push_back(values[valOffset + i]);
      }

    return ret;
   }

    short get(int offset) {
      if (offset > this.size) {
         throw IndexOutOfBoundsException("index " + offset + " exceeds size " + this.size);
      } else {
    TShortLink l = this.getLinkAt(offset);
    return no();
      }
   }

    TShortLink getLinkAt(int offset) {
      if (offset >= this.size()) {
    return nullptr;
      } else {
         return offset <= this.size() >>> 1 ? getLink(this.head, 0, offset, true) : getLink(this.tail, this.size() - 1, offset, false);
      }
   }

    static TShortLink getLink(TShortLink l, int idx, int offset) {
    return getLink();
   }

    static TShortLink getLink(TShortLink l, int idx, int offset, bool next) {
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

    short set(int offset, short val) {
      if (offset > this.size) {
         throw IndexOutOfBoundsException("index " + offset + " exceeds size " + this.size);
      } else {
    TShortLink l = this.getLinkAt(offset);
         if (no(l)) {
            throw IndexOutOfBoundsException("at offset " + offset);
         } else {
    short prev = l.getValue();
            l.setValue(val);
    return prev;
         }
      }
   }

    void set(int offset, short[] values) {
      this.set(offset, values, 0, values.length);
   }

    void set(int offset, short[] values, int valOffset, int length) {
      for (int i = 0; i < length; i++) {
    short value = values[valOffset + i];
         this.set(offset + i, value);
      }
   }

    short replace(int offset, short val) {
      return this.set(offset, val);
   }

    void clear() {
      this.size = 0;
      this.head = nullptr;
      this.tail = nullptr;
   }

    bool remove(short value) {
    bool changed = false;

      for (TShortLink l = this.head; got(l); l = l.getNext()) {
         if (l.getValue() == value) {
            changed = true;
            this.removeLink(l);
         }
      }

    return changed;
   }

    void removeLink(TShortLink l) {
      if (!no(l)) {
         this.size--;
    TShortLink prev = l.getPrevious();
    TShortLink next = l.getNext();
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
    for (auto& o : collection)            if (!(dynamic_cast<int16_t*>(o) != nullptr)) {
    return false;
            }

    short i = (int16_t)o;
            if (!this.contains(i)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(TShortCollection collection) {
      if (this.empty()) {
    return false;
      } else {
    TShortIterator it = collection.iterator();

         while (it.hasNext()) {
    short i = it.next();
            if (!this.contains(i)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(short[] array) {
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

    bool addAll(TShortCollection collection) {
    bool ret = false;
    TShortIterator it = collection.iterator();

      while (it.hasNext()) {
    short i = it.next();
         if (this.push_back(i)) {
            ret = true;
         }
      }

    return ret;
   }

    bool addAll(short[] array) {
    bool ret = false;

    for (auto& i : array)         if (this.push_back(i)) {
            ret = true;
         }
      }

    return ret;
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TShortIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TShortCollection collection) {
    bool modified = false;
    TShortIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(short[] array) {
      Arrays.sort(array);
    bool modified = false;
    TShortIterator iter = this.iterator();

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
    TShortIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool removeAll(TShortCollection collection) {
    bool modified = false;
    TShortIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool removeAll(short[] array) {
      Arrays.sort(array);
    bool modified = false;
    TShortIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (Arrays.binarySearch(array, iter.next()) >= 0) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    short removeAt(int offset) {
    TShortLink l = this.getLinkAt(offset);
      if (no(l)) {
         throw ArrayIndexOutOfBoundsException("no elemenet at " + offset);
      } else {
    short prev = l.getValue();
         this.removeLink(l);
    return prev;
      }
   }

    void remove(int offset, int length) {
      for (int i = 0; i < length; i++) {
         this.removeAt(offset);
      }
   }

    void transformValues(TShortFunction function) {
      for (TShortLink l = this.head; got(l); l = l.getNext()) {
         l.setValue(function.execute(l.getValue()));
      }
   }

    void reverse() {
    TShortLink h = this.head;
    TShortLink t = this.tail;
    TShortLink l = this.head;

      while (got(l)) {
    TShortLink next = l.getNext();
    TShortLink prev = l.getPrevious();
    TShortLink tmp = l;
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
    TShortLink start = this.getLinkAt(from);
    TShortLink stop = this.getLinkAt(to);
    TShortLink tmp = nullptr;
    TShortLink tmpHead = start.getPrevious();
    TShortLink l = start;

         while (l != stop) {
    TShortLink next = l.getNext();
    TShortLink prev = l.getPrevious();
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
    TShortLink l = this.getLinkAt(rand.nextInt(this.size()));
         this.removeLink(l);
         this.push_back(l.getValue());
      }
   }

    TShortList subList(int begin, int end) {
      if (end < begin) {
         throw IllegalArgumentException("begin index " + begin + " greater than end index " + end);
      } else if (this.size < begin) {
         throw IllegalArgumentException("begin index " + begin + " greater than last index " + this.size);
      } else if (begin < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (end > this.size) {
         throw IndexOutOfBoundsException("end index < " + this.size);
      } else {
    TShortLinkedList ret = std::make_shared<TShortLinkedList>();
    TShortLink tmp = this.getLinkAt(begin);

         for (int i = begin; i < end; i++) {
            ret.push_back(tmp.getValue());
            tmp = tmp.getNext();
         }

    return ret;
      }
   }

   public short[] toArray() {
      return this.toArray(new short[this.size], 0, this.size);
   }

   public short[] toArray(int offset, int len) {
      return this.toArray(new short[len], offset, 0, len);
   }

   public short[] toArray(short[] dest) {
      return this.toArray(dest, 0, this.size);
   }

   public short[] toArray(short[] dest, int offset, int len) {
      return this.toArray(dest, offset, 0, len);
   }

   public short[] toArray(short[] dest, int source_pos, int dest_pos, int len) {
      if (len == 0) {
    return dest;
      } else if (source_pos >= 0 && source_pos < this.size()) {
    TShortLink tmp = this.getLinkAt(source_pos);

         for (int i = 0; i < len; i++) {
            dest[dest_pos + i] = tmp.getValue();
            tmp = tmp.getNext();
         }

    return dest;
      } else {
         throw ArrayIndexOutOfBoundsException(source_pos);
      }
   }

    bool forEach(TShortProcedure procedure) {
      for (TShortLink l = this.head; got(l); l = l.getNext()) {
         if (!procedure.execute(l.getValue())) {
    return false;
         }
      }

    return true;
   }

    bool forEachDescending(TShortProcedure procedure) {
      for (TShortLink l = this.tail; got(l); l = l.getPrevious()) {
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
    TShortList tmp = this.subList(fromIndex, toIndex);
      short[] vals = tmp.toArray();
      Arrays.sort(vals);
      this.set(fromIndex, vals);
   }

    void fill(short val) {
      this.fill(0, this.size, val);
   }

    void fill(int fromIndex, int toIndex, short val) {
      if (fromIndex < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else {
    TShortLink l = this.getLinkAt(fromIndex);
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

    int binarySearch(short value) {
      return this.binarySearch(value, 0, this.size());
   }

    int binarySearch(short value, int fromIndex, int toIndex) {
      if (fromIndex < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (toIndex > this.size) {
         throw IndexOutOfBoundsException("end index > size: " + toIndex + " > " + this.size);
      } else if (toIndex < fromIndex) {
         return -(fromIndex + 1);
      } else {
    int from = fromIndex;
    TShortLink fromLink = this.getLinkAt(fromIndex);
    int to = toIndex;

         while (from < to) {
    int mid = from + to >>> 1;
    TShortLink middle = getLink(fromLink, from, mid);
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

    int indexOf(short value) {
      return this.indexOf(0, value);
   }

    int indexOf(int offset, short value) {
    int count = offset;

      for (TShortLink l = this.getLinkAt(offset); got(l.getNext()); l = l.getNext()) {
         if (l.getValue() == value) {
    return count;
         }

         count++;
      }

      return -1;
   }

    int lastIndexOf(short value) {
      return this.lastIndexOf(0, value);
   }

    int lastIndexOf(int offset, short value) {
      if (this.empty()) {
         return -1;
      } else {
    int last = -1;
    int count = offset;

         for (TShortLink l = this.getLinkAt(offset); got(l.getNext()); l = l.getNext()) {
            if (l.getValue() == value) {
               last = count;
            }

            count++;
         }

    return last;
      }
   }

    bool contains(short value) {
      if (this.empty()) {
    return false;
      } else {
         for (TShortLink l = this.head; got(l); l = l.getNext()) {
            if (l.getValue() == value) {
    return true;
            }
         }

    return false;
      }
   }

    TShortIterator iterator() {
      return std::make_shared<1>(this);
   }

    TShortList grep(TShortProcedure condition) {
    TShortList ret = std::make_shared<TShortLinkedList>();

      for (TShortLink l = this.head; got(l); l = l.getNext()) {
         if (condition.execute(l.getValue())) {
            ret.push_back(l.getValue());
         }
      }

    return ret;
   }

    TShortList inverseGrep(TShortProcedure condition) {
    TShortList ret = std::make_shared<TShortLinkedList>();

      for (TShortLink l = this.head; got(l); l = l.getNext()) {
         if (!condition.execute(l.getValue())) {
            ret.push_back(l.getValue());
         }
      }

    return ret;
   }

    short max() {
    short ret = -32768;
      if (this.empty()) {
         throw std::make_unique<IllegalStateException>();
      } else {
         for (TShortLink l = this.head; got(l); l = l.getNext()) {
            if (ret < l.getValue()) {
               ret = l.getValue();
            }
         }

    return ret;
      }
   }

    short min() {
    short ret = 32767;
      if (this.empty()) {
         throw std::make_unique<IllegalStateException>();
      } else {
         for (TShortLink l = this.head; got(l); l = l.getNext()) {
            if (ret > l.getValue()) {
               ret = l.getValue();
            }
         }

    return ret;
      }
   }

    short sum() {
    short sum = 0;

      for (TShortLink l = this.head; got(l); l = l.getNext()) {
         sum += l.getValue();
      }

    return sum;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeShort(this.no_entry_value);
      out.writeInt(this.size);
    TShortIterator iterator = this.iterator();

      while (iterator.hasNext()) {
    short next = iterator.next();
         out.writeShort(next);
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this.no_entry_value = in.readShort();
    int len = in.readInt();

      for (int i = 0; i < len; i++) {
         this.push_back(in.readShort());
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
    TShortLinkedList that = (TShortLinkedList)o;
         if (this.no_entry_value != that.no_entry_value) {
    return false;
         } else if (this.size != that.size) {
    return false;
         } else {
    TShortIterator iterator = this.iterator();
    TShortIterator thatIterator = that.iterator();

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
    TShortIterator iterator = this.iterator();

      while (iterator.hasNext()) {
         result = 31 * result + HashFunctions.hash(iterator.next());
      }

    return result;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
    TShortIterator it = this.iterator();

      while (it.hasNext()) {
    short next = it.next();
         buf.append((int)next);
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
