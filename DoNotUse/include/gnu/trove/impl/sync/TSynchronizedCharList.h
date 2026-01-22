#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/list/TCharList.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedCharList : public TSynchronizedCharCollection {
public:
    static const long serialVersionUID = -7754090372962971524L;
    const TCharList list;

    public TSynchronizedCharList(TCharList list) {
      super(list);
      this.list = list;
   }

    public TSynchronizedCharList(TCharList list, void* mutex) {
      super(list, mutex);
      this.list = list;
   }

    bool equals(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list == o);
      }
   }

    int hashCode() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.hashCode();
      }
   }

    char get(int index) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.get(index);
      }
   }

    char set(int index, char element) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.set(index, element);
      }
   }

    void set(int offset, char[] values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.set(offset, values);
      }
   }

    void set(int offset, char[] values, int valOffset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.set(offset, values, valOffset, length);
      }
   }

    char replace(int offset, char val) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.replace(offset, val);
      }
   }

    void remove(int offset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.remove(offset, length);
      }
   }

    char removeAt(int offset) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.removeAt(offset);
      }
   }

    void add(char[] vals) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.push_back(vals);
      }
   }

    void add(char[] vals, int offset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.push_back(vals, offset, length);
      }
   }

    void insert(int offset, char value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, value);
      }
   }

    void insert(int offset, char[] values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, values);
      }
   }

    void insert(int offset, char[] values, int valOffset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, values, valOffset, len);
      }
   }

    int indexOf(char o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.indexOf(o);
      }
   }

    int lastIndexOf(char o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.lastIndexOf(o);
      }
   }

    TCharList subList(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return std::make_shared<TSynchronizedCharList>(this.list.subList(fromIndex, toIndex), this.mutex);
      }
   }

   public char[] toArray(int offset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(offset, len);
      }
   }

   public char[] toArray(char[] dest, int offset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(dest, offset, len);
      }
   }

   public char[] toArray(char[] dest, int source_pos, int dest_pos, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(dest, source_pos, dest_pos, len);
      }
   }

    int indexOf(int offset, char value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.indexOf(offset, value);
      }
   }

    int lastIndexOf(int offset, char value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.lastIndexOf(offset, value);
      }
   }

    void fill(char val) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.fill(val);
      }
   }

    void fill(int fromIndex, int toIndex, char val) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.fill(fromIndex, toIndex, val);
      }
   }

    void reverse() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.reverse();
      }
   }

    void reverse(int from, int to) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.reverse(from, to);
      }
   }

    void shuffle(Random rand) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.shuffle(rand);
      }
   }

    void sort() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.sort();
      }
   }

    void sort(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.sort(fromIndex, toIndex);
      }
   }

    int binarySearch(char value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.binarySearch(value);
      }
   }

    int binarySearch(char value, int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.binarySearch(value, fromIndex, toIndex);
      }
   }

    TCharList grep(TCharProcedure condition) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.grep(condition);
      }
   }

    TCharList inverseGrep(TCharProcedure condition) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.inverseGrep(condition);
      }
   }

    char max() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.max();
      }
   }

    char min() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.min();
      }
   }

    char sum() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.sum();
      }
   }

    bool forEachDescending(TCharProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.forEachDescending(procedure);
      }
   }

    void transformValues(TCharFunction function) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.transformValues(function);
      }
   }

    void* readResolve() {
      return this.dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessCharList>(this.list) : this;
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
