#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace org {
namespace luaj {
namespace kahluafork {
namespace compiler {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class ExpDesc {
public:
 int k;
 int info;
 int aux;
 double _nval;
 bool has_nval;
 int t;
 int f;

 void setNval(double double0) {
 this->_nval = double0;
 this->has_nval = true;
 }

 double nval() {
 return this->has_nval ? this->_nval : this->info;
 }

 void init(int int0, int int1) {
 this->f = -1;
 this->t = -1;
 this->k = int0;
 this->info = int1;
 }

 bool hasjumps() {
 return this->t != this->f;
 }

 bool isnumeral() {
 return this->k == 5 && this->t == -1 && this->f == -1;
 }

 void setvalue(ExpDesc expDesc0) {
 this->k = expDesc0.k;
 this->_nval = expDesc0._nval;
 this->has_nval = expDesc0.has_nval;
 this->info = expDesc0.info;
 this->aux = expDesc0.aux;
 this->t = expDesc0.t;
 this->f = expDesc0.f;
 }
}
} // namespace compiler
} // namespace kahluafork
} // namespace luaj
} // namespace org
