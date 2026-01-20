#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TFloatSetDecorator/1.h"
#include "gnu/trove/set/TFloatSet.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TFloatSetDecorator : public AbstractSet {
public:
    static const long serialVersionUID = 1L;
    TFloatSet _set;

    public TFloatSetDecorator() {
   }

    public TFloatSetDecorator(TFloatSet set) {
      this._set = set;
   }

    TFloatSet getSet() {
      return this._set;
   }

    bool add(float value) {
      return value != nullptr && this._set.push_back(value);
   }

    bool equals(void* other) {
      if (this._set == other)) {
    return true;
      } else if (dynamic_cast<Set*>(other) != nullptr) {
    std::unordered_set that = (Set)other;
         if (that.size() != this._set.size()) {
    return false;
         } else {
    Iterator it = that.iterator();
    int i = that.size();

            while (i-- > 0) {
    void* val = it.next();
               if (!(dynamic_cast<float*>(val) != nullptr)) {
    return false;
               }

    float v = (float)val;
               if (!this._set.contains(v)) {
    return false;
               }
            }

    return true;
         }
      } else {
    return false;
      }
   }

    void clear() {
      this._set.clear();
   }

    bool remove(void* value) {
      return dynamic_cast<float*>(value) != nullptr && this._set.remove((float)value);
   }

   public Iterator<float> iterator() {
      return std::make_shared<1>(this);
   }

    int size() {
      return this._set.size();
   }

    bool isEmpty() {
      return this._set.size() == 0;
   }

    bool contains(void* o) {
      return !(dynamic_cast<float*>(o) != nullptr) ? false : this._set.contains((float)o);
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._set = (TFloatSet)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._set);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
