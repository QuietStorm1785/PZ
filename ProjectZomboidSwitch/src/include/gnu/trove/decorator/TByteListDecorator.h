#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TByteList.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace decorator {


class TByteListDecorator : public AbstractList {
public:
    static const long serialVersionUID = 1L;
    TByteList list;

    public TByteListDecorator() {
   }

    public TByteListDecorator(TByteList list) {
      this.list = list;
   }

    TByteList getList() {
      return this.list;
   }

    int size() {
      return this.list.size();
   }

    uint8_t get(int index) {
    uint8_t value = this.list.get(index);
    return value = = this.list.getNoEntryValue() ? nullptr : value;
   }

    uint8_t set(int index, uint8_t value) {
    uint8_t previous_value = this.list.set(index, value);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void add(int index, uint8_t value) {
      this.list.insert(index, value);
   }

    uint8_t remove(int index) {
    uint8_t previous_value = this.list.removeAt(index);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this.list = (TByteList)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this.list);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
