#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TIntProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TLinkedHashSet {
public:
    const ObjectOutput output;
    std::ios_base::failure ioException;

   TLinkedHashSet$WriteProcedure(TLinkedHashSet var1, ObjectOutput output) {
      this.this$0 = var1;
      this.output = output;
   }

    std::ios_base::failure getIoException() {
      return this.ioException;
   }

    bool execute(int value) {
      try {
         this.output.writeObject(this.this$0._set[value]);
    return true;
      } catch (IOException var3) {
         this.ioException = var3;
    return false;
      }
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
