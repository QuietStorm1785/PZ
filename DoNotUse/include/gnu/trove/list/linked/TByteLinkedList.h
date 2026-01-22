#pragma once
#include <list>
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
#include "gnu/trove/list/linked/TByteLinkedList/1.h"
#include "gnu/trove/list/linked/TByteLinkedList/TByteLink.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TByteLinkedList {
public:
    uint8_t no_entry_value;
    int size;
    TByteLink head = nullptr;
    TByteLink tail = this.head;

    public TByteLinkedList() {
   }

    public TByteLinkedList(uint8_t no_entry_value) {
      this.no_entry_value = no_entry_value;
   }

    public TByteLinkedList(TByteList list) {
      this.no_entry_value = list.getNoEntryValue();
    TByteIterator iterator = list.iterator();

      while (iterator.hasNext()) {
    uint8_t next = iterator.next();
         this.push_back(next);
      }
   }

    uint8_t getNoEntryValue() {
      return this.no_entry_value;
   }

    int size() {
      return this.size;
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    bool add(uint8_t val) {
    TByteLink l = std::make_shared<TByteLink>(val);
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

    void add(byte[] vals) {
    for (auto& val : vals)         this.push_back(val);
      }
   }

    void add(byte[] vals, int offset, int length) {
      for (int i = 0; i < length; i++) {
    uint8_t val = vals[offset + i];
         this.push_back(val);
      }
   }

    void insert(int offset, uint8_t value) {
    TByteLinkedList tmp = std::make_shared<TByteLinkedList>();
      tmp.push_back(value);
      this.insert(offset, tmp);
   }

    void insert(int offset, byte[] values) {
      this.insert(offset, link(values, 0, values.length));
   }

    void insert(int offset, byte[] values, int valOffset, int len) {
      this.insert(offset, link(values, valOffset, len));
   }

    void insert(int offset, TByteLinkedList tmp) {
    TByteLink l = this.getLinkAt(offset);
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
    TByteLink prev = l.getPrevious();
            l.getPrevious().setNext(tmp.head);
            tmp.tail.setNext(l);
            l.setPrevious(tmp.tail);
            tmp.head.setPrevious(prev);
         }
      }
   }

    static TByteLinkedList link(byte[] values, int valOffset, int len) {
    TByteLinkedList ret = std::make_shared<TByteLinkedList>();

      for (int i = 0; i < len; i++) {
         ret.push_back(values[valOffset + i]);
      }

    return ret;
   }

    uint8_t get(int offset) {
      if (offset > this.size) {
         throw IndexOutOfBoundsException("index " + offset + " exceeds size " + this.size);
      } else {
    TByteLink l = this.getLinkAt(offset);
    return no();
      }
   }

    TByteLink getLinkAt(int offset) {
      if (offset >= this.size()) {
    return nullptr;
      } else {
         return offset <= this.size() >>> 1 ? getLink(this.head, 0, offset, true) : getLink(this.tail, this.size() - 1, offset, false);
      }
   }

    static TByteLink getLink(TByteLink l, int idx, int offset) {
    return getLink();
   }

    static TByteLink getLink(TByteLink l, int idx, int offset, bool next) {
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

    uint8_t set(int offset, uint8_t val) {
      if (offset > this.size) {
         throw IndexOutOfBoundsException("index " + offset + " exceeds size " + this.size);
      } else {
    TByteLink l = this.getLinkAt(offset);
         if (no(l)) {
            throw IndexOutOfBoundsException("at offset " + offset);
         } else {
    uint8_t prev = l.getValue();
            l.setValue(val);
    return prev;
         }
      }
   }

    void set(int offset, byte[] values) {
      this.set(offset, values, 0, values.length);
   }

    void set(int offset, byte[] values, int valOffset, int length) {
      for (int i = 0; i < length; i++) {
    uint8_t value = values[valOffset + i];
         this.set(offset + i, value);
      }
   }

    uint8_t replace(int offset, uint8_t val) {
      return this.set(offset, val);
   }

    void clear() {
      this.size = 0;
      this.head = nullptr;
      this.tail = nullptr;
   }

    bool remove(uint8_t value) {
    bool changed = false;

      for (TByteLink l = this.head; got(l); l = l.getNext()) {
         if (l.getValue() == value) {
            changed = true;
            this.removeLink(l);
         }
      }

    return changed;
   }

    void removeLink(TByteLink l) {
      if (!no(l)) {
         this.size--;
    TByteLink prev = l.getPrevious();
    TByteLink next = l.getNext();
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
    for (auto& o : collection)            if (!(dynamic_cast<uint8_t*>(o) != nullptr)) {
    return false;
            }

    uint8_t i = (uint8_t)o;
            if (!this.contains(i)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(TByteCollection collection) {
      if (this.empty()) {
    return false;
      } else {
    TByteIterator it = collection.iterator();

         while (it.hasNext()) {
    uint8_t i = it.next();
            if (!this.contains(i)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(byte[] array) {
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

    bool addAll(TByteCollection collection) {
    bool ret = false;
    TByteIterator it = collection.iterator();

      while (it.hasNext()) {
    uint8_t i = it.next();
         if (this.push_back(i)) {
            ret = true;
         }
      }

    return ret;
   }

    bool addAll(byte[] array) {
    bool ret = false;

    for (auto& i : array)         if (this.push_back(i)) {
            ret = true;
         }
      }

    return ret;
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

    bool retainAll(byte[] array) {
      Arrays.sort(array);
    bool modified = false;
    TByteIterator iter = this.iterator();

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
    TByteIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool removeAll(TByteCollection collection) {
    bool modified = false;
    TByteIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool removeAll(byte[] array) {
      Arrays.sort(array);
    bool modified = false;
    TByteIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (Arrays.binarySearch(array, iter.next()) >= 0) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    uint8_t removeAt(int offset) {
    TByteLink l = this.getLinkAt(offset);
      if (no(l)) {
         throw ArrayIndexOutOfBoundsException("no elemenet at " + offset);
      } else {
    uint8_t prev = l.getValue();
         this.removeLink(l);
    return prev;
      }
   }

    void remove(int offset, int length) {
      for (int i = 0; i < length; i++) {
         this.removeAt(offset);
      }
   }

    void transformValues(TByteFunction function) {
      for (TByteLink l = this.head; got(l); l = l.getNext()) {
         l.setValue(function.execute(l.getValue()));
      }
   }

    void reverse() {
    TByteLink h = this.head;
    TByteLink t = this.tail;
    TByteLink l = this.head;

      while (got(l)) {
    TByteLink next = l.getNext();
    TByteLink prev = l.getPrevious();
    TByteLink tmp = l;
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
    TByteLink start = this.getLinkAt(from);
    TByteLink stop = this.getLinkAt(to);
    TByteLink tmp = nullptr;
    TByteLink tmpHead = start.getPrevious();
    TByteLink l = start;

         while (l != stop) {
    TByteLink next = l.getNext();
    TByteLink prev = l.getPrevious();
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
    TByteLink l = this.getLinkAt(rand.nextInt(this.size()));
         this.removeLink(l);
         this.push_back(l.getValue());
      }
   }

    TByteList subList(int begin, int end) {
      if (end < begin) {
         throw IllegalArgumentException("begin index " + begin + " greater than end index " + end);
      } else if (this.size < begin) {
         throw IllegalArgumentException("begin index " + begin + " greater than last index " + this.size);
      } else if (begin < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (end > this.size) {
         throw IndexOutOfBoundsException("end index < " + this.size);
      } else {
    TByteLinkedList ret = std::make_shared<TByteLinkedList>();
    TByteLink tmp = this.getLinkAt(begin);

         for (int i = begin; i < end; i++) {
            ret.push_back(tmp.getValue());
            tmp = tmp.getNext();
         }

    return ret;
      }
   }

   public byte[] toArray() {
      return this.toArray(new byte[this.size], 0, this.size);
   }

   public byte[] toArray(int offset, int len) {
      return this.toArray(new byte[len], offset, 0, len);
   }

   public byte[] toArray(byte[] dest) {
      return this.toArray(dest, 0, this.size);
   }

   public byte[] toArray(byte[] dest, int offset, int len) {
      return this.toArray(dest, offset, 0, len);
   }

   public byte[] toArray(byte[] dest, int source_pos, int dest_pos, int len) {
      if (len == 0) {
    return dest;
      } else if (source_pos >= 0 && source_pos < this.size()) {
    TByteLink tmp = this.getLinkAt(source_pos);

         for (int i = 0; i < len; i++) {
            dest[dest_pos + i] = tmp.getValue();
            tmp = tmp.getNext();
         }

    return dest;
      } else {
         throw ArrayIndexOutOfBoundsException(source_pos);
      }
   }

    bool forEach(TByteProcedure procedure) {
      for (TByteLink l = this.head; got(l); l = l.getNext()) {
         if (!procedure.execute(l.getValue())) {
    return false;
         }
      }

    return true;
   }

    bool forEachDescending(TByteProcedure procedure) {
      for (TByteLink l = this.tail; got(l); l = l.getPrevious()) {
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
    TByteList tmp = this.subList(fromIndex, toIndex);
      byte[] vals = tmp.toArray();
      Arrays.sort(vals);
      this.set(fromIndex, vals);
   }

    void fill(uint8_t val) {
      this.fill(0, this.size, val);
   }

    void fill(int fromIndex, int toIndex, uint8_t val) {
      if (fromIndex < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else {
    TByteLink l = this.getLinkAt(fromIndex);
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

    int binarySearch(uint8_t value) {
      return this.binarySearch(value, 0, this.size());
   }

    int binarySearch(uint8_t value, int fromIndex, int toIndex) {
      if (fromIndex < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (toIndex > this.size) {
         throw IndexOutOfBoundsException("end index > size: " + toIndex + " > " + this.size);
      } else if (toIndex < fromIndex) {
         return -(fromIndex + 1);
      } else {
    int from = fromIndex;
    TByteLink fromLink = this.getLinkAt(fromIndex);
    int to = toIndex;

         while (from < to) {
    int mid = from + to >>> 1;
    TByteLink middle = getLink(fromLink, from, mid);
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

    int indexOf(uint8_t value) {
      return this.indexOf(0, value);
   }

    int indexOf(int offset, uint8_t value) {
    int count = offset;

      for (TByteLink l = this.getLinkAt(offset); got(l.getNext()); l = l.getNext()) {
         if (l.getValue() == value) {
    return count;
         }

         count++;
      }

      return -1;
   }

    int lastIndexOf(uint8_t value) {
      return this.lastIndexOf(0, value);
   }

    int lastIndexOf(int offset, uint8_t value) {
      if (this.empty()) {
         return -1;
      } else {
    int last = -1;
    int count = offset;

         for (TByteLink l = this.getLinkAt(offset); got(l.getNext()); l = l.getNext()) {
            if (l.getValue() == value) {
               last = count;
            }

            count++;
         }

    return last;
      }
   }

    bool contains(uint8_t value) {
      if (this.empty()) {
    return false;
      } else {
         for (TByteLink l = this.head; got(l); l = l.getNext()) {
            if (l.getValue() == value) {
    return true;
            }
         }

    return false;
      }
   }

    TByteIterator iterator() {
      return std::make_shared<1>(this);
   }

    TByteList grep(TByteProcedure condition) {
    TByteList ret = std::make_shared<TByteLinkedList>();

      for (TByteLink l = this.head; got(l); l = l.getNext()) {
         if (condition.execute(l.getValue())) {
            ret.push_back(l.getValue());
         }
      }

    return ret;
   }

    TByteList inverseGrep(TByteProcedure condition) {
    TByteList ret = std::make_shared<TByteLinkedList>();

      for (TByteLink l = this.head; got(l); l = l.getNext()) {
         if (!condition.execute(l.getValue())) {
            ret.push_back(l.getValue());
         }
      }

    return ret;
   }

    uint8_t max() {
    uint8_t ret = -128;
      if (this.empty()) {
         throw std::make_unique<IllegalStateException>();
      } else {
         for (TByteLink l = this.head; got(l); l = l.getNext()) {
            if (ret < l.getValue()) {
               ret = l.getValue();
            }
         }

    return ret;
      }
   }

    uint8_t min() {
    uint8_t ret = 127;
      if (this.empty()) {
         throw std::make_unique<IllegalStateException>();
      } else {
         for (TByteLink l = this.head; got(l); l = l.getNext()) {
            if (ret > l.getValue()) {
               ret = l.getValue();
            }
         }

    return ret;
      }
   }

    uint8_t sum() {
    uint8_t sum = 0;

      for (TByteLink l = this.head; got(l); l = l.getNext()) {
         sum += l.getValue();
      }

    return sum;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeByte(this.no_entry_value);
      out.writeInt(this.size);
    TByteIterator iterator = this.iterator();

      while (iterator.hasNext()) {
    uint8_t next = iterator.next();
         out.writeByte(next);
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this.no_entry_value = in.readByte();
    int len = in.readInt();

      for (int i = 0; i < len; i++) {
         this.push_back(in.readByte());
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
    TByteLinkedList that = (TByteLinkedList)o;
         if (this.no_entry_value != that.no_entry_value) {
    return false;
         } else if (this.size != that.size) {
    return false;
         } else {
    TByteIterator iterator = this.iterator();
    TByteIterator thatIterator = that.iterator();

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
    TByteIterator iterator = this.iterator();

      while (iterator.hasNext()) {
         result = 31 * result + HashFunctions.hash(iterator.next());
      }

    return result;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
    TByteIterator it = this.iterator();

      while (it.hasNext()) {
    uint8_t next = it.next();
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
