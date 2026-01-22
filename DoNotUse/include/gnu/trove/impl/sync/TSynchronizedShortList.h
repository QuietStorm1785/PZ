#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/list/TShortList.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedShortList : public TSynchronizedShortCollection {
public:
    static const long serialVersionUID = -7754090372962971524L;
    const TShortList list;

    public TSynchronizedShortList(TShortList list) {
      super(list);
      this.list = list;
   }

    public TSynchronizedShortList(TShortList list, void* mutex) {
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

    short get(int index) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.get(index);
      }
   }

    short set(int index, short element) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.set(index, element);
      }
   }

    void set(int offset, short[] values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.set(offset, values);
      }
   }

    void set(int offset, short[] values, int valOffset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.set(offset, values, valOffset, length);
      }
   }

    short replace(int offset, short val) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.replace(offset, val);
      }
   }

    void remove(int offset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.remove(offset, length);
      }
   }

    short removeAt(int offset) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.removeAt(offset);
      }
   }

    void add(short[] vals) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.push_back(vals);
      }
   }

    void add(short[] vals, int offset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.push_back(vals, offset, length);
      }
   }

    void insert(int offset, short value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, value);
      }
   }

    void insert(int offset, short[] values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, values);
      }
   }

    void insert(int offset, short[] values, int valOffset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, values, valOffset, len);
      }
   }

    int indexOf(short o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.indexOf(o);
      }
   }

    int lastIndexOf(short o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.lastIndexOf(o);
      }
   }

    TShortList subList(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return std::make_shared<TSynchronizedShortList>(this.list.subList(fromIndex, toIndex), this.mutex);
      }
   }

   public short[] toArray(int offset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(offset, len);
      }
   }

   public short[] toArray(short[] dest, int offset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(dest, offset, len);
      }
   }

   public short[] toArray(short[] dest, int source_pos, int dest_pos, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(dest, source_pos, dest_pos, len);
      }
   }

    int indexOf(int offset, short value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.indexOf(offset, value);
      }
   }

    int lastIndexOf(int offset, short value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.lastIndexOf(offset, value);
      }
   }

    void fill(short val) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.fill(val);
      }
   }

    void fill(int fromIndex, int toIndex, short val) {
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

    int binarySearch(short value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.binarySearch(value);
      }
   }

    int binarySearch(short value, int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.binarySearch(value, fromIndex, toIndex);
      }
   }

    TShortList grep(TShortProcedure condition) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.grep(condition);
      }
   }

    TShortList inverseGrep(TShortProcedure condition) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.inverseGrep(condition);
      }
   }

    short max() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.max();
      }
   }

    short min() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.min();
      }
   }

    short sum() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.sum();
      }
   }

    bool forEachDescending(TShortProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.forEachDescending(procedure);
      }
   }

    void transformValues(TShortFunction function) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.transformValues(function);
      }
   }

    void* readResolve() {
      return this.dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessShortList>(this.list) : this;
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
