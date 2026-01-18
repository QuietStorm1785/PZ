#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
namespace util {
namespace glu {
namespace tessellation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PriorityQ {
public:
 static const int INIT_SIZE = 32;

 static bool LEQ(PriorityQ.Leq var0, void *object1, void *object0) {
 return Geom.VertLeq((GLUvertex)object1, (GLUvertex)object0);
 }

 static PriorityQ pqNewPriorityQ(PriorityQ.Leq leq) {
 return new PriorityQSort(leq);
 }

 void pqDeletePriorityQ();

 boolean pqInit();

 int pqInsert(Object var1);

 Object pqExtractMin();

 void pqDelete(int var1);

 Object pqMinimum();

 boolean pqIsEmpty();

public
 interface Leq { bool leq(void *var1, void *var2); }

public
 static class PQhandleElem {
 void *key;
 int node;
 }

 public static class PQnode {
 int handle;
 }
}
} // namespace tessellation
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
