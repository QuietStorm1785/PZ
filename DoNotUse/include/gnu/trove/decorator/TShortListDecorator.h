#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TShortList.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace decorator {


class TShortListDecorator : public AbstractList {
public:
    static const long serialVersionUID = 1L;
    TShortList list;

    public TShortListDecorator() {
   }

    public TShortListDecorator(TShortList list) {
      this.list = list;
   }

    TShortList getList() {
      return this.list;
   }

    int size() {
      return this.list.size();
   }

    short get(int index) {
    short value = this.list.get(index);
    return value = = this.list.getNoEntryValue() ? nullptr : value;
   }

    short set(int index, short value) {
    short previous_value = this.list.set(index, value);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void add(int index, short value) {
      this.list.insert(index, value);
   }

    short remove(int index) {
    short previous_value = this.list.removeAt(index);
    return previous_value = = this.list.getNoEntryValue() ? nullptr : previous_value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this.list = (TShortList)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this.list);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
