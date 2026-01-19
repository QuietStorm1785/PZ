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


class ImageDataInputStream : public InputStream {
public:
    const PngInputStream in;
    const StateMachine machine;
   private final std::vector<byte> onebyte = std::make_shared<std::array<byte, 1>>();
    bool done;

    public ImageDataInputStream(PngInputStream var1, StateMachine var2) {
      this.in = var1;
      this.machine = var2;
   }

    int read() {
      return this.read(this.onebyte, 0, 1) == -1 ? -1 : 0xFF & this.onebyte[0];
   }

    int read(byte[] var1, int var2, int var3) {
      if (this.done) {
         return -1;
      } else {
         try {
    int var4 = 0;

            while (var4 != var3 && !this.done) {
               while (var4 != var3 && this.in.getRemaining() > 0) {
    int var5 = Math.min(var3 - var4, this.in.getRemaining());
                  this.in.readFully(var1, var2 + var4, var5);
                  var4 += var5;
               }

               if (this.in.getRemaining() <= 0) {
                  this.in.endChunk(this.machine.getType());
                  this.machine.nextState(this.in.startChunk());
                  this.done = this.machine.getType() != 1229209940;
               }
            }

    return var4;
         } catch (EOFException var6) {
            this.done = true;
            return -1;
         }
      }
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
