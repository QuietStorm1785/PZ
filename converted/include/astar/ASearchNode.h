#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace astar {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class ASearchNode {
public:
 double g = 0.0;
 int depth;

 double f() {
 return this->g() + this->h();
 }

 double g() {
 return this->g;
 }

 void setG(double double0) {
 this->g = double0;
 }

 int getDepth() {
 return this->depth;
 }

 void setDepth(int int0) {
 this->depth = int0;
 }
}
} // namespace astar
