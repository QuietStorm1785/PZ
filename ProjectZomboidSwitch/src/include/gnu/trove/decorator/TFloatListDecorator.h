#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TFloatList.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace decorator {


class TFloatListDecorator : public AbstractList {
public:
    static const long serialVersionUID = 1L;
    TFloatList list;

    public TFloatListDecorator() {
   }

    public TFloatListDecorator(TFloatList list) {
      this.list = list;
   }

    TFloatList getList() {
      return this.list;
   }

    int size() {
      return this.list.size();
   }

    float get(int index) {
    float value = this.list.get(index);
    return value = = this.list.getNoEntryValue() ? nullptr : value;
   }

    float set(int index, float value) {
    float previous_value = this.list.set(index, value);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void add(int index, float value) {
      this.list.insert(index, value);
   }

    float remove(int index) {
    float previous_value = this.list.removeAt(index);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this.list = (TFloatList)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this.list);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
