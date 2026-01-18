#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by ChrisWood (Tanglewood Games Limited) on 01/11/2017.
 */
class IsoGridStack {
public:
public
  ArrayList<ArrayList<IsoGridSquare>> Squares;

public
  IsoGridStack(int count) {
    this.Squares = new ArrayList<>(count);

    for (int int0 = 0; int0 < count; int0++) {
      this.Squares.add(new ArrayList<>(5000));
    }
  }
}
} // namespace iso
} // namespace zombie
