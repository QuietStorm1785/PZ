#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TLongList.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace decorator {


class TLongListDecorator : public AbstractList {
public:
    static const long serialVersionUID = 1L;
    TLongList list;

    public TLongListDecorator() {
   }

    public TLongListDecorator(TLongList list) {
      this.list = list;
   }

    TLongList getList() {
      return this.list;
   }

    int size() {
      return this.list.size();
   }

    long get(int index) {
    long value = this.list.get(index);
    return value = = this.list.getNoEntryValue() ? nullptr : value;
   }

    long set(int index, long value) {
    long previous_value = this.list.set(index, value);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void add(int index, long value) {
      this.list.insert(index, value);
   }

    long remove(int index) {
    long previous_value = this.list.removeAt(index);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this.list = (TLongList)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this.list);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
