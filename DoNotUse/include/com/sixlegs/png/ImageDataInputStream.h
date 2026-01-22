#pragma once
#include <cstdint>
#include <vector>
#include <istream>
#include <algorithm>
#include <stdexcept>

namespace com {
namespace sixlegs {
namespace png {

class PngInputStream;
class StateMachine;

class ImageDataInputStream {
public:
   ImageDataInputStream(PngInputStream& in, StateMachine& machine)
      : in_(in), machine_(machine), onebyte_(1), done_(false) {}

   // read single byte, returns -1 on EOF
   int read() {
      return read(onebyte_.data(), 0, 1) == -1 ? -1 : (0xFF & onebyte_[0]);
   }

   // read up to len bytes into buffer (offset 'off'), returns number of bytes read or -1 on EOF
   int read(uint8_t* buf, int off, int len) {
      if (done_) return -1;
      try {
         int total = 0;
         while (total != len && !done_) {
            while (total != len && in_.getRemaining() > 0) {
               int toRead = std::min(len - total, in_.getRemaining());
               in_.read(reinterpret_cast<uint8_t*>(buf + off + total), 0, toRead);
               total += toRead;
            }

            if (in_.getRemaining() <= 0) {
               in_.endChunk(machine_.getType());
               machine_.nextState(in_.startChunk());
               done_ = (machine_.getType() != 1229209940);
            }
         }
         return total;
      } catch (const std::exception&) {
         done_ = true;
         return -1;
      }
   }

private:
   PngInputStream& in_;
   StateMachine& machine_;
   std::vector<uint8_t> onebyte_;
   bool done_;
};

} // namespace png
} // namespace sixlegs
} // namespace com
