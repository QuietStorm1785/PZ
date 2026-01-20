#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/sound/sampled/AudioFileFormat/Type.h"

namespace de {
namespace jarnbjo {
namespace vorbis {


class VorbisAudioFileReader {
public:
   private static const VorbisAudioFileReader$VorbisFormatType instance = new VorbisAudioFileReader$VorbisFormatType();

   private VorbisAudioFileReader$VorbisFormatType() {
      super("VORBIS", "ogg");
   }

    static Type getInstance() {
    return instance;
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
