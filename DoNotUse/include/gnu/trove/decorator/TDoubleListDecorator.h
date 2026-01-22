#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TDoubleList.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace decorator {


class TDoubleListDecorator : public AbstractList {
public:
    static const long serialVersionUID = 1L;
    TDoubleList list;

    public TDoubleListDecorator() {
   }

    public TDoubleListDecorator(TDoubleList list) {
      this.list = list;
   }

    TDoubleList getList() {
      return this.list;
   }

    int size() {
      return this.list.size();
   }

    double get(int index) {
    double value = this.list.get(index);
    return value = = this.list.getNoEntryValue() ? nullptr : value;
   }

    double set(int index, double value) {
    double previous_value = this.list.set(index, value);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void add(int index, double value) {
      this.list.insert(index, value);
   }

    double remove(int index) {
    double previous_value = this.list.removeAt(index);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this.list = (TDoubleList)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this.list);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
