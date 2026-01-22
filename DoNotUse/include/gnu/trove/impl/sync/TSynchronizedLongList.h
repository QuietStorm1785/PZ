#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/list/TLongList.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedLongList : public TSynchronizedLongCollection {
public:
    static const long serialVersionUID = -7754090372962971524L;
    const TLongList list;

    public TSynchronizedLongList(TLongList list) {
      super(list);
      this.list = list;
   }

    public TSynchronizedLongList(TLongList list, void* mutex) {
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

    long get(int index) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.get(index);
      }
   }

    long set(int index, long element) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.set(index, element);
      }
   }

    void set(int offset, long[] values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.set(offset, values);
      }
   }

    void set(int offset, long[] values, int valOffset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.set(offset, values, valOffset, length);
      }
   }

    long replace(int offset, long val) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.replace(offset, val);
      }
   }

    void remove(int offset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.remove(offset, length);
      }
   }

    long removeAt(int offset) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.removeAt(offset);
      }
   }

    void add(long[] vals) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.push_back(vals);
      }
   }

    void add(long[] vals, int offset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.push_back(vals, offset, length);
      }
   }

    void insert(int offset, long value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, value);
      }
   }

    void insert(int offset, long[] values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, values);
      }
   }

    void insert(int offset, long[] values, int valOffset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, values, valOffset, len);
      }
   }

    int indexOf(long o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.indexOf(o);
      }
   }

    int lastIndexOf(long o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.lastIndexOf(o);
      }
   }

    TLongList subList(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return std::make_shared<TSynchronizedLongList>(this.list.subList(fromIndex, toIndex), this.mutex);
      }
   }

   public long[] toArray(int offset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(offset, len);
      }
   }

   public long[] toArray(long[] dest, int offset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(dest, offset, len);
      }
   }

   public long[] toArray(long[] dest, int source_pos, int dest_pos, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(dest, source_pos, dest_pos, len);
      }
   }

    int indexOf(int offset, long value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.indexOf(offset, value);
      }
   }

    int lastIndexOf(int offset, long value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.lastIndexOf(offset, value);
      }
   }

    void fill(long val) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.fill(val);
      }
   }

    void fill(int fromIndex, int toIndex, long val) {
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

    int binarySearch(long value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.binarySearch(value);
      }
   }

    int binarySearch(long value, int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.binarySearch(value, fromIndex, toIndex);
      }
   }

    TLongList grep(TLongProcedure condition) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.grep(condition);
      }
   }

    TLongList inverseGrep(TLongProcedure condition) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.inverseGrep(condition);
      }
   }

    long max() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.max();
      }
   }

    long min() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.min();
      }
   }

    long sum() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.sum();
      }
   }

    bool forEachDescending(TLongProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.forEachDescending(procedure);
      }
   }

    void transformValues(TLongFunction function) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.transformValues(function);
      }
   }

    void* readResolve() {
      return this.dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessLongList>(this.list) : this;
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
