#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ImageDataInputStream : public InputStream {
public:
 const PngInputStream in;
 const StateMachine machine;
 private byte[] onebyte = new byte[1];
 bool done;

 public ImageDataInputStream(PngInputStream pngInputStream, StateMachine stateMachine) {
 this->in = pngInputStream;
 this->machine = stateMachine;
 }

 int read() {
 return this->read(this->onebyte, 0, 1) == -1 ? -1 : 0xFF & this->onebyte[0];
 }

 int read(byte[] bytes, int int3, int int1) {
 if (this->done) {
 return -1;
 } else {
 try {
 int int0 = 0;

 while (int0 != int1 && !this->done) {
 while (int0 != int1 && this->in.getRemaining() > 0) {
 int int2 = Math.min(int1 - int0, this->in.getRemaining());
 this->in.readFully(bytes, int3 + int0, int2);
 int0 += int2;
 }

 if (this->in.getRemaining() <= 0) {
 this->in.endChunk(this->machine.getType());
 this->machine.nextState(this->in.startChunk());
 this->done = this->machine.getType() != 1229209940;
 }
 }

 return int0;
 } catch (EOFException eOFException) {
 this->done = true;
 return -1;
 }
 }
 }
}
} // namespace png
} // namespace sixlegs
} // namespace com
