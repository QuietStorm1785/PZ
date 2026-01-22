#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TIntList.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace decorator {


class TIntListDecorator : public AbstractList {
public:
    static const long serialVersionUID = 1L;
    TIntList list;

    public TIntListDecorator() {
   }

    public TIntListDecorator(TIntList list) {
      this.list = list;
   }

    TIntList getList() {
      return this.list;
   }

    int size() {
      return this.list.size();
   }

    int get(int index) {
    int value = this.list.get(index);
    return value = = this.list.getNoEntryValue() ? nullptr : value;
   }

    int set(int index, int value) {
    int previous_value = this.list.set(index, value);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void add(int index, int value) {
      this.list.insert(index, value);
   }

    int remove(int index) {
    int previous_value = this.list.removeAt(index);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this.list = (TIntList)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this.list);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
