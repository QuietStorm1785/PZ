#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/ogg/BasicStream.h"
#include "de/jarnbjo/ogg/FileStream.h"
#include "de/jarnbjo/ogg/LogicalOggStream.h"
#include "de/jarnbjo/ogg/OggFormatException.h"
#include "de/jarnbjo/ogg/PhysicalOggStream.h"
#include "de/jarnbjo/ogg/UncachedUrlStream.h"
#include "de/jarnbjo/vorbis/VorbisAudioFileReader/VorbisFormatType.h"
#include "de/jarnbjo/vorbis/VorbisAudioFileReader/VorbisInputStream.h"
#include "java/net/URL.h"
#include "javax/sound/sampled/AudioFileFormat.h"
#include "javax/sound/sampled/AudioFormat.h"
#include "javax/sound/sampled/AudioInputStream.h"
#include "javax/sound/sampled/UnsupportedAudioFileException.h"
#include "javax/sound/sampled/spi/AudioFileReader.h"
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace vorbis {


class VorbisAudioFileReader : public AudioFileReader {
public:
    AudioFileFormat getAudioFileFormat(File var1) {
      try {
         return this.getAudioFileFormat(std::make_shared<FileStream>(std::make_shared<RandomAccessFile>(var1, "r")));
      } catch (OggFormatException var3) {
         throw UnsupportedAudioFileException(var3.getMessage());
      }
   }

    AudioFileFormat getAudioFileFormat(InputStream var1) {
      try {
         return this.getAudioFileFormat(std::make_shared<BasicStream>(var1));
      } catch (OggFormatException var3) {
         throw UnsupportedAudioFileException(var3.getMessage());
      }
   }

    AudioFileFormat getAudioFileFormat(URL var1) {
      try {
         return this.getAudioFileFormat(std::make_shared<UncachedUrlStream>(var1));
      } catch (OggFormatException var3) {
         throw UnsupportedAudioFileException(var3.getMessage());
      }
   }

    AudioFileFormat getAudioFileFormat(PhysicalOggStream var1) {
      try {
    Collection var2 = var1.getLogicalStreams();
         if (var2.size() != 1) {
            throw UnsupportedAudioFileException("Only Ogg files with one logical Vorbis stream are supported.");
         } else {
    LogicalOggStream var3 = (LogicalOggStream)var2.iterator().next();
            if (var3.getFormat() != "audio/x-vorbis") {
               throw UnsupportedAudioFileException("Only Ogg files with one logical Vorbis stream are supported.");
            } else {
    VorbisStream var4 = std::make_shared<VorbisStream>(var3);
    AudioFormat var5 = std::make_shared<AudioFormat>(var4.getIdentificationHeader().getSampleRate(), 16, var4.getIdentificationHeader().getChannels(), true, true);
               return std::make_shared<AudioFileFormat>(VorbisFormatType.getInstance(), var5, -1);
            }
         }
      } catch (OggFormatException var6) {
         throw UnsupportedAudioFileException(var6.getMessage());
      } catch (VorbisFormatException var7) {
         throw UnsupportedAudioFileException(var7.getMessage());
      }
   }

    AudioInputStream getAudioInputStream(File var1) {
      try {
         return this.getAudioInputStream(std::make_shared<FileStream>(std::make_shared<RandomAccessFile>(var1, "r")));
      } catch (OggFormatException var3) {
         throw UnsupportedAudioFileException(var3.getMessage());
      }
   }

    AudioInputStream getAudioInputStream(InputStream var1) {
      try {
         return this.getAudioInputStream(std::make_shared<BasicStream>(var1));
      } catch (OggFormatException var3) {
         throw UnsupportedAudioFileException(var3.getMessage());
      }
   }

    AudioInputStream getAudioInputStream(URL var1) {
      try {
         return this.getAudioInputStream(std::make_shared<UncachedUrlStream>(var1));
      } catch (OggFormatException var3) {
         throw UnsupportedAudioFileException(var3.getMessage());
      }
   }

    AudioInputStream getAudioInputStream(PhysicalOggStream var1) {
      try {
    Collection var2 = var1.getLogicalStreams();
         if (var2.size() != 1) {
            throw UnsupportedAudioFileException("Only Ogg files with one logical Vorbis stream are supported.");
         } else {
    LogicalOggStream var3 = (LogicalOggStream)var2.iterator().next();
            if (var3.getFormat() != "audio/x-vorbis") {
               throw UnsupportedAudioFileException("Only Ogg files with one logical Vorbis stream are supported.");
            } else {
    VorbisStream var4 = std::make_shared<VorbisStream>(var3);
    AudioFormat var5 = std::make_shared<AudioFormat>(var4.getIdentificationHeader().getSampleRate(), 16, var4.getIdentificationHeader().getChannels(), true, true);
               return std::make_shared<AudioInputStream>(std::make_shared<VorbisInputStream>(var4), var5, -1L);
            }
         }
      } catch (OggFormatException var6) {
         throw UnsupportedAudioFileException(var6.getMessage());
      } catch (VorbisFormatException var7) {
         throw UnsupportedAudioFileException(var7.getMessage());
      }
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
