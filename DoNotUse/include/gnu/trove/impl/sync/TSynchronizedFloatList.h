#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/list/TFloatList.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedFloatList : public TSynchronizedFloatCollection {
public:
    static const long serialVersionUID = -7754090372962971524L;
    const TFloatList list;

    public TSynchronizedFloatList(TFloatList list) {
      super(list);
      this.list = list;
   }

    public TSynchronizedFloatList(TFloatList list, void* mutex) {
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

    float get(int index) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.get(index);
      }
   }

    float set(int index, float element) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.set(index, element);
      }
   }

    void set(int offset, float[] values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.set(offset, values);
      }
   }

    void set(int offset, float[] values, int valOffset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.set(offset, values, valOffset, length);
      }
   }

    float replace(int offset, float val) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.replace(offset, val);
      }
   }

    void remove(int offset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.remove(offset, length);
      }
   }

    float removeAt(int offset) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.removeAt(offset);
      }
   }

    void add(float[] vals) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.push_back(vals);
      }
   }

    void add(float[] vals, int offset, int length) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.push_back(vals, offset, length);
      }
   }

    void insert(int offset, float value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, value);
      }
   }

    void insert(int offset, float[] values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, values);
      }
   }

    void insert(int offset, float[] values, int valOffset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.insert(offset, values, valOffset, len);
      }
   }

    int indexOf(float o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.indexOf(o);
      }
   }

    int lastIndexOf(float o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.lastIndexOf(o);
      }
   }

    TFloatList subList(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return std::make_shared<TSynchronizedFloatList>(this.list.subList(fromIndex, toIndex), this.mutex);
      }
   }

   public float[] toArray(int offset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(offset, len);
      }
   }

   public float[] toArray(float[] dest, int offset, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(dest, offset, len);
      }
   }

   public float[] toArray(float[] dest, int source_pos, int dest_pos, int len) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.toArray(dest, source_pos, dest_pos, len);
      }
   }

    int indexOf(int offset, float value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.indexOf(offset, value);
      }
   }

    int lastIndexOf(int offset, float value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.lastIndexOf(offset, value);
      }
   }

    void fill(float val) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.fill(val);
      }
   }

    void fill(int fromIndex, int toIndex, float val) {
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

    int binarySearch(float value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.binarySearch(value);
      }
   }

    int binarySearch(float value, int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.binarySearch(value, fromIndex, toIndex);
      }
   }

    TFloatList grep(TFloatProcedure condition) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.grep(condition);
      }
   }

    TFloatList inverseGrep(TFloatProcedure condition) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.inverseGrep(condition);
      }
   }

    float max() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.max();
      }
   }

    float min() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.min();
      }
   }

    float sum() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.sum();
      }
   }

    bool forEachDescending(TFloatProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.list.forEachDescending(procedure);
      }
   }

    void transformValues(TFloatFunction function) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.list.transformValues(function);
      }
   }

    void* readResolve() {
      return this.dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<TSynchronizedRandomAccessFloatList>(this.list) : this;
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
