#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParticlesArray {
public:
 bool needToUpdate;
 int ParticleSystemsCount = 0;
 int ParticleSystemsLast = 0;

 public ParticlesArray() {
 this->ParticleSystemsCount = 0;
 this->ParticleSystemsLast = 0;
 this->needToUpdate = true;
 }

 public synchronized int addParticle(E object) {
 if (object == nullptr) {
 return -1;
 } else if (this->size() == this->ParticleSystemsCount) {
 this->add((E)object);
 this->ParticleSystemsCount++;
 this->needToUpdate = true;
 return this->size() - 1;
 } else {
 for (int int0 = this->ParticleSystemsLast; int0 < this->size(); int0++) {
 if (this->get(int0) == nullptr) {
 this->ParticleSystemsLast = int0;
 this->set(int0, (E)object);
 this->ParticleSystemsCount++;
 this->needToUpdate = true;
 return int0;
 }
 }

 for (int int1 = 0; int1 < this->ParticleSystemsLast; int1++) {
 if (this->get(int1) == nullptr) {
 this->ParticleSystemsLast = int1;
 this->set(int1, (E)object);
 this->ParticleSystemsCount++;
 this->needToUpdate = true;
 return int1;
 }
 }

 DebugLog.log("ERROR: ParticlesArray.addParticle has unknown error");
 return -1;
 }
 }

 public synchronized boolean deleteParticle(int int0) {
 if (int0 >= 0 && int0 < this->size() && this->get(int0) != nullptr) {
 this->set(int0, nullptr);
 this->ParticleSystemsCount--;
 this->needToUpdate = true;
 return true;
 } else {
 return false;
 }
 }

 public synchronized void defragmentParticle() {
 this->needToUpdate = false;
 if (this->ParticleSystemsCount != this->size() && this->size() != 0) {
 int int0 = -1;

 for (int int1 = 0; int1 < this->size(); int1++) {
 if (this->get(int1) == nullptr) {
 int0 = int1;
 break;
 }
 }

 for (int int2 = this->size() - 1; int2 >= 0; int2--) {
 if (this->get(int2) != nullptr) {
 this->set(int0, this->get(int2);
 this->set(int2, nullptr);

 for (int int3 = int0; int3 < this->size(); int3++) {
 if (this->get(int3) == nullptr) {
 int0 = int3;
 break;
 }
 }

 if (int0 + 1 >= int2) {
 this->ParticleSystemsLast = int0;
 break;
 }
 }
 }
 }
 }

 public synchronized int getCount() {
 return this->ParticleSystemsCount;
 }

 public synchronized boolean getNeedToUpdate() {
 return this->needToUpdate;
 }
}
} // namespace iso
} // namespace zombie
