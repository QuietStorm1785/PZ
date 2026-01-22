#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/list/TIntList.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedIntList : public TSynchronizedIntCollection {
public:
    static const long serialVersionUID = -7754090372962971524L;
    const TIntList list;

    public TSynchronizedIntList(TIntList list) {
      super(list);
      this.list = list;
   }

    public TSynchronizedIntList(TIntList list, void* mutex) {
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

    int get(int index) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.get(index);
      }
   }

    int set(int index, int element) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.set(index, element);
      }
   }

    void set(int offset, int[] values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.set(offset, values);
      }
   }

    void set(int offset, int[] values, int valOffset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.set(offset, values, valOffset, length);
      }
   }

    int replace(int offset, int val) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.replace(offset, val);
      }
   }

    void remove(int offset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.remove(offset, length);
      }
   }

    int removeAt(int offset) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.removeAt(offset);
      }
   }

    void add(int[] vals) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.push_back(vals);
      }
   }

    void add(int[] vals, int offset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.push_back(vals, offset, length);
      }
   }

    void insert(int offset, int value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, value);
      }
   }

    void insert(int offset, int[] values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, values);
      }
   }

    void insert(int offset, int[] values, int valOffset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, values, valOffset, len);
      }
   }

    int indexOf(int o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.indexOf(o);
      }
   }

    int lastIndexOf(int o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.lastIndexOf(o);
      }
   }

    TIntList subList(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return std::make_shared<TSynchronizedIntList>(this.list.subList(fromIndex, toIndex), this.mutex);
      }
   }

   public int[] toArray(int offset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(offset, len);
      }
   }

   public int[] toArray(int[] dest, int offset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(dest, offset, len);
      }
   }

   public int[] toArray(int[] dest, int source_pos, int dest_pos, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(dest, source_pos, dest_pos, len);
      }
   }

    int indexOf(int offset, int value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.indexOf(offset, value);
      }
   }

    int lastIndexOf(int offset, int value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.lastIndexOf(offset, value);
      }
   }

    void fill(int val) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.fill(val);
      }
   }

    void fill(int fromIndex, int toIndex, int val) {
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

    int binarySearch(int value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.binarySearch(value);
      }
   }

    int binarySearch(int value, int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.binarySearch(value, fromIndex, toIndex);
      }
   }

    TIntList grep(TIntProcedure condition) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.grep(condition);
      }
   }

    TIntList inverseGrep(TIntProcedure condition) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.inverseGrep(condition);
      }
   }

    int max() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.max();
      }
   }

    int min() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.min();
      }
   }

    int sum() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.sum();
      }
   }

    bool forEachDescending(TIntProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.forEachDescending(procedure);
      }
   }

    void transformValues(TIntFunction function) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.transformValues(function);
      }
   }

    void* readResolve() {
      return this.dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessIntList>(this.list) : this;
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
