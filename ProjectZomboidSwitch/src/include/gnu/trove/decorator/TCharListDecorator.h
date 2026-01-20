#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TCharList.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace decorator {


class TCharListDecorator : public AbstractList {
public:
    static const long serialVersionUID = 1L;
    TCharList list;

    public TCharListDecorator() {
   }

    public TCharListDecorator(TCharList list) {
      this.list = list;
   }

    TCharList getList() {
      return this.list;
   }

    int size() {
      return this.list.size();
   }

    char get(int index) {
    char value = this.list.get(index);
    return value = = this.list.getNoEntryValue() ? nullptr : value;
   }

    char set(int index, char value) {
    char previous_value = this.list.set(index, value);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void add(int index, char value) {
      this.list.insert(index, value);
   }

    char remove(int index) {
    char previous_value = this.list.removeAt(index);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this.list = (TCharList)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this.list);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
