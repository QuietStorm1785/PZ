#pragma once
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/iterator/TCharIterator.h"
#include "gnu/trove/list/TCharList.h"
#include "gnu/trove/list/linked/TCharLinkedList/1.h"
#include "gnu/trove/list/linked/TCharLinkedList/TCharLink.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TCharLinkedList {
public:
    char no_entry_value;
    int size;
    TCharLink head = nullptr;
    TCharLink tail = this.head;

    public TCharLinkedList() {
   }

    public TCharLinkedList(char no_entry_value) {
      this.no_entry_value = no_entry_value;
   }

    public TCharLinkedList(TCharList list) {
      this.no_entry_value = list.getNoEntryValue();
    TCharIterator iterator = list.iterator();

      while (iterator.hasNext()) {
    char next = iterator.next();
         this.push_back(next);
      }
   }

    char getNoEntryValue() {
      return this.no_entry_value;
   }

    int size() {
      return this.size;
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    bool add(char val) {
    TCharLink l = std::make_shared<TCharLink>(val);
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

    void add(char[] vals) {
    for (auto& val : vals)         this.push_back(val);
      }
   }

    void add(char[] vals, int offset, int length) {
      for (int i = 0; i < length; i++) {
    char val = vals[offset + i];
         this.push_back(val);
      }
   }

    void insert(int offset, char value) {
    TCharLinkedList tmp = std::make_shared<TCharLinkedList>();
      tmp.push_back(value);
      this.insert(offset, tmp);
   }

    void insert(int offset, char[] values) {
      this.insert(offset, link(values, 0, values.length));
   }

    void insert(int offset, char[] values, int valOffset, int len) {
      this.insert(offset, link(values, valOffset, len));
   }

    void insert(int offset, TCharLinkedList tmp) {
    TCharLink l = this.getLinkAt(offset);
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
    TCharLink prev = l.getPrevious();
            l.getPrevious().setNext(tmp.head);
            tmp.tail.setNext(l);
            l.setPrevious(tmp.tail);
            tmp.head.setPrevious(prev);
         }
      }
   }

    static TCharLinkedList link(char[] values, int valOffset, int len) {
    TCharLinkedList ret = std::make_shared<TCharLinkedList>();

      for (int i = 0; i < len; i++) {
         ret.push_back(values[valOffset + i]);
      }

    return ret;
   }

    char get(int offset) {
      if (offset > this.size) {
         throw IndexOutOfBoundsException("index " + offset + " exceeds size " + this.size);
      } else {
    TCharLink l = this.getLinkAt(offset);
    return no();
      }
   }

    TCharLink getLinkAt(int offset) {
      if (offset >= this.size()) {
    return nullptr;
      } else {
         return offset <= this.size() >>> 1 ? getLink(this.head, 0, offset, true) : getLink(this.tail, this.size() - 1, offset, false);
      }
   }

    static TCharLink getLink(TCharLink l, int idx, int offset) {
    return getLink();
   }

    static TCharLink getLink(TCharLink l, int idx, int offset, bool next) {
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

    char set(int offset, char val) {
      if (offset > this.size) {
         throw IndexOutOfBoundsException("index " + offset + " exceeds size " + this.size);
      } else {
    TCharLink l = this.getLinkAt(offset);
         if (no(l)) {
            throw IndexOutOfBoundsException("at offset " + offset);
         } else {
    char prev = l.getValue();
            l.setValue(val);
    return prev;
         }
      }
   }

    void set(int offset, char[] values) {
      this.set(offset, values, 0, values.length);
   }

    void set(int offset, char[] values, int valOffset, int length) {
      for (int i = 0; i < length; i++) {
    char value = values[valOffset + i];
         this.set(offset + i, value);
      }
   }

    char replace(int offset, char val) {
      return this.set(offset, val);
   }

    void clear() {
      this.size = 0;
      this.head = nullptr;
      this.tail = nullptr;
   }

    bool remove(char value) {
    bool changed = false;

      for (TCharLink l = this.head; got(l); l = l.getNext()) {
         if (l.getValue() == value) {
            changed = true;
            this.removeLink(l);
         }
      }

    return changed;
   }

    void removeLink(TCharLink l) {
      if (!no(l)) {
         this.size--;
    TCharLink prev = l.getPrevious();
    TCharLink next = l.getNext();
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
    for (auto& o : collection)            if (!(dynamic_cast<char*>(o) != nullptr)) {
    return false;
            }

    char i = (char)o;
            if (!this.contains(i)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(TCharCollection collection) {
      if (this.empty()) {
    return false;
      } else {
    TCharIterator it = collection.iterator();

         while (it.hasNext()) {
    char i = it.next();
            if (!this.contains(i)) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(char[] array) {
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

    bool addAll(TCharCollection collection) {
    bool ret = false;
    TCharIterator it = collection.iterator();

      while (it.hasNext()) {
    char i = it.next();
         if (this.push_back(i)) {
            ret = true;
         }
      }

    return ret;
   }

    bool addAll(char[] array) {
    bool ret = false;

    for (auto& i : array)         if (this.push_back(i)) {
            ret = true;
         }
      }

    return ret;
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TCharIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TCharCollection collection) {
    bool modified = false;
    TCharIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(char[] array) {
      Arrays.sort(array);
    bool modified = false;
    TCharIterator iter = this.iterator();

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
    TCharIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool removeAll(TCharCollection collection) {
    bool modified = false;
    TCharIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool removeAll(char[] array) {
      Arrays.sort(array);
    bool modified = false;
    TCharIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (Arrays.binarySearch(array, iter.next()) >= 0) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    char removeAt(int offset) {
    TCharLink l = this.getLinkAt(offset);
      if (no(l)) {
         throw ArrayIndexOutOfBoundsException("no elemenet at " + offset);
      } else {
    char prev = l.getValue();
         this.removeLink(l);
    return prev;
      }
   }

    void remove(int offset, int length) {
      for (int i = 0; i < length; i++) {
         this.removeAt(offset);
      }
   }

    void transformValues(TCharFunction function) {
      for (TCharLink l = this.head; got(l); l = l.getNext()) {
         l.setValue(function.execute(l.getValue()));
      }
   }

    void reverse() {
    TCharLink h = this.head;
    TCharLink t = this.tail;
    TCharLink l = this.head;

      while (got(l)) {
    TCharLink next = l.getNext();
    TCharLink prev = l.getPrevious();
    TCharLink tmp = l;
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
    TCharLink start = this.getLinkAt(from);
    TCharLink stop = this.getLinkAt(to);
    TCharLink tmp = nullptr;
    TCharLink tmpHead = start.getPrevious();
    TCharLink l = start;

         while (l != stop) {
    TCharLink next = l.getNext();
    TCharLink prev = l.getPrevious();
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
    TCharLink l = this.getLinkAt(rand.nextInt(this.size()));
         this.removeLink(l);
         this.push_back(l.getValue());
      }
   }

    TCharList subList(int begin, int end) {
      if (end < begin) {
         throw IllegalArgumentException("begin index " + begin + " greater than end index " + end);
      } else if (this.size < begin) {
         throw IllegalArgumentException("begin index " + begin + " greater than last index " + this.size);
      } else if (begin < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (end > this.size) {
         throw IndexOutOfBoundsException("end index < " + this.size);
      } else {
    TCharLinkedList ret = std::make_shared<TCharLinkedList>();
    TCharLink tmp = this.getLinkAt(begin);

         for (int i = begin; i < end; i++) {
            ret.push_back(tmp.getValue());
            tmp = tmp.getNext();
         }

    return ret;
      }
   }

   public char[] toArray() {
      return this.toArray(new char[this.size], 0, this.size);
   }

   public char[] toArray(int offset, int len) {
      return this.toArray(new char[len], offset, 0, len);
   }

   public char[] toArray(char[] dest) {
      return this.toArray(dest, 0, this.size);
   }

   public char[] toArray(char[] dest, int offset, int len) {
      return this.toArray(dest, offset, 0, len);
   }

   public char[] toArray(char[] dest, int source_pos, int dest_pos, int len) {
      if (len == 0) {
    return dest;
      } else if (source_pos >= 0 && source_pos < this.size()) {
    TCharLink tmp = this.getLinkAt(source_pos);

         for (int i = 0; i < len; i++) {
            dest[dest_pos + i] = tmp.getValue();
            tmp = tmp.getNext();
         }

    return dest;
      } else {
         throw ArrayIndexOutOfBoundsException(source_pos);
      }
   }

    bool forEach(TCharProcedure procedure) {
      for (TCharLink l = this.head; got(l); l = l.getNext()) {
         if (!procedure.execute(l.getValue())) {
    return false;
         }
      }

    return true;
   }

    bool forEachDescending(TCharProcedure procedure) {
      for (TCharLink l = this.tail; got(l); l = l.getPrevious()) {
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
    TCharList tmp = this.subList(fromIndex, toIndex);
      char[] vals = tmp.toArray();
      Arrays.sort(vals);
      this.set(fromIndex, vals);
   }

    void fill(char val) {
      this.fill(0, this.size, val);
   }

    void fill(int fromIndex, int toIndex, char val) {
      if (fromIndex < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else {
    TCharLink l = this.getLinkAt(fromIndex);
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

    int binarySearch(char value) {
      return this.binarySearch(value, 0, this.size());
   }

    int binarySearch(char value, int fromIndex, int toIndex) {
      if (fromIndex < 0) {
         throw IndexOutOfBoundsException("begin index can not be < 0");
      } else if (toIndex > this.size) {
         throw IndexOutOfBoundsException("end index > size: " + toIndex + " > " + this.size);
      } else if (toIndex < fromIndex) {
         return -(fromIndex + 1);
      } else {
    int from = fromIndex;
    TCharLink fromLink = this.getLinkAt(fromIndex);
    int to = toIndex;

         while (from < to) {
    int mid = from + to >>> 1;
    TCharLink middle = getLink(fromLink, from, mid);
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

    int indexOf(char value) {
      return this.indexOf(0, value);
   }

    int indexOf(int offset, char value) {
    int count = offset;

      for (TCharLink l = this.getLinkAt(offset); got(l.getNext()); l = l.getNext()) {
         if (l.getValue() == value) {
    return count;
         }

         count++;
      }

      return -1;
   }

    int lastIndexOf(char value) {
      return this.lastIndexOf(0, value);
   }

    int lastIndexOf(int offset, char value) {
      if (this.empty()) {
         return -1;
      } else {
    int last = -1;
    int count = offset;

         for (TCharLink l = this.getLinkAt(offset); got(l.getNext()); l = l.getNext()) {
            if (l.getValue() == value) {
               last = count;
            }

            count++;
         }

    return last;
      }
   }

    bool contains(char value) {
      if (this.empty()) {
    return false;
      } else {
         for (TCharLink l = this.head; got(l); l = l.getNext()) {
            if (l.getValue() == value) {
    return true;
            }
         }

    return false;
      }
   }

    TCharIterator iterator() {
      return std::make_shared<1>(this);
   }

    TCharList grep(TCharProcedure condition) {
    TCharList ret = std::make_shared<TCharLinkedList>();

      for (TCharLink l = this.head; got(l); l = l.getNext()) {
         if (condition.execute(l.getValue())) {
            ret.push_back(l.getValue());
         }
      }

    return ret;
   }

    TCharList inverseGrep(TCharProcedure condition) {
    TCharList ret = std::make_shared<TCharLinkedList>();

      for (TCharLink l = this.head; got(l); l = l.getNext()) {
         if (!condition.execute(l.getValue())) {
            ret.push_back(l.getValue());
         }
      }

    return ret;
   }

    char max() {
    char ret = 0;
      if (this.empty()) {
         throw std::make_unique<IllegalStateException>();
      } else {
         for (TCharLink l = this.head; got(l); l = l.getNext()) {
            if (ret < l.getValue()) {
               ret = l.getValue();
            }
         }

    return ret;
      }
   }

    char min() {
    char ret = '\uffff';
      if (this.empty()) {
         throw std::make_unique<IllegalStateException>();
      } else {
         for (TCharLink l = this.head; got(l); l = l.getNext()) {
            if (ret > l.getValue()) {
               ret = l.getValue();
            }
         }

    return ret;
      }
   }

    char sum() {
    char sum = 0;

      for (TCharLink l = this.head; got(l); l = l.getNext()) {
         sum += l.getValue();
      }

    return sum;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeChar(this.no_entry_value);
      out.writeInt(this.size);
    TCharIterator iterator = this.iterator();

      while (iterator.hasNext()) {
    char next = iterator.next();
         out.writeChar(next);
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this.no_entry_value = in.readChar();
    int len = in.readInt();

      for (int i = 0; i < len; i++) {
         this.push_back(in.readChar());
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
    TCharLinkedList that = (TCharLinkedList)o;
         if (this.no_entry_value != that.no_entry_value) {
    return false;
         } else if (this.size != that.size) {
    return false;
         } else {
    TCharIterator iterator = this.iterator();
    TCharIterator thatIterator = that.iterator();

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
    TCharIterator iterator = this.iterator();

      while (iterator.hasNext()) {
         result = 31 * result + HashFunctions.hash(iterator.next());
      }

    return result;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
    TCharIterator it = this.iterator();

      while (it.hasNext()) {
    char next = it.next();
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
