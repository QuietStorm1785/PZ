#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <vector>
#include <cstdint>
#include <memory>
#include <fstream>
#include <iostream>
#include <cmath>

namespace de {
namespace jarnbjo {
namespace util {
namespace audio {


// C++ equivalent for AudioInputStream
class AudioInputStream {
public:
   virtual int read(std::vector<uint8_t>& buffer, size_t offset, size_t length) = 0;
   virtual ~AudioInputStream() = default;
};

class FadeableAudioInputStream : public AudioInputStream {
public:
   std::shared_ptr<AudioInputStream> stream;
   bool fading = false;
   double phi = 0.0;

   FadeableAudioInputStream(std::shared_ptr<AudioInputStream> inputStream)
      : stream(inputStream) {}

   void fadeOut() {
      fading = true;
      phi = 0.0;
   }

   int read(std::vector<uint8_t>& buffer) {
      return read(buffer, 0, buffer.size());
   }

   int read(std::vector<uint8_t>& buffer, size_t offset, size_t length) override {
      int bytesRead = stream->read(buffer, offset, length);
      if (fading && bytesRead > 0) {
         // assume 16-bit stereo little-endian samples
         size_t end = offset + static_cast<size_t>(bytesRead);
         for (size_t i = offset; i + 3 < end; i += 4) {
             int16_t left = static_cast<int16_t>(static_cast<uint8_t>(buffer[i]) | (static_cast<int16_t>(static_cast<uint8_t>(buffer[i+1])) << 8));
             int16_t right = static_cast<int16_t>(static_cast<uint8_t>(buffer[i+2]) | (static_cast<int16_t>(static_cast<uint8_t>(buffer[i+3])) << 8));
             if (phi < M_PI_2) phi += 1.5e-5; // ramp phi
             double gain = std::cos(phi);
             int32_t nl = static_cast<int32_t>(left * gain);
             int32_t nr = static_cast<int32_t>(right * gain);
             buffer[i] = static_cast<uint8_t>(nl & 0xFF);
             buffer[i+1] = static_cast<uint8_t>((nl >> 8) & 0xFF);
             buffer[i+2] = static_cast<uint8_t>(nr & 0xFF);
             buffer[i+3] = static_cast<uint8_t>((nr >> 8) & 0xFF);
         }
      }
      return bytesRead;
   }
}
} // namespace audio
} // namespace util
} // namespace jarnbjo
} // namespace de
