#pragma once
#include "de/jarnbjo/ogg/BasicStream.h"
#include "de/jarnbjo/ogg/EndOfOggStreamException.h"
#include "de/jarnbjo/ogg/FileStream.h"
#include "de/jarnbjo/ogg/LogicalOggStream.h"
#include "de/jarnbjo/ogg/OggFormatException.h"
#include "de/jarnbjo/ogg/PhysicalOggStream.h"
#include "de/jarnbjo/ogg/UncachedUrlStream.h"
#include "java/net/URL.h"
#include "javax/sound/sampled/AudioFileFormat.h"
#include "javax/sound/sampled/AudioFileFormat/Type.h"
#include "javax/sound/sampled/AudioFormat.h"
#include "javax/sound/sampled/AudioInputStream.h"
#include "javax/sound/sampled/UnsupportedAudioFileException.h"
#include "javax/sound/sampled/spi/AudioFileReader.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace de {
namespace jarnbjo {
namespace vorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VorbisAudioFileReader : public AudioFileReader {
public:
  AudioFileFormat getAudioFileFormat(File file) {
    try {
      return this.getAudioFileFormat(
          new FileStream(new RandomAccessFile(file, "r")));
    } catch (OggFormatException oggFormatException) {
      throw new UnsupportedAudioFileException(oggFormatException.getMessage());
    }
  }

  AudioFileFormat getAudioFileFormat(InputStream inputStream) {
    try {
      return this.getAudioFileFormat(new BasicStream(inputStream));
    } catch (OggFormatException oggFormatException) {
      throw new UnsupportedAudioFileException(oggFormatException.getMessage());
    }
  }

  AudioFileFormat getAudioFileFormat(URL url) {
    try {
      return this.getAudioFileFormat(new UncachedUrlStream(url));
    } catch (OggFormatException oggFormatException) {
      throw new UnsupportedAudioFileException(oggFormatException.getMessage());
    }
  }

  AudioFileFormat getAudioFileFormat(PhysicalOggStream physicalOggStream) {
    try {
      Collection collection = physicalOggStream.getLogicalStreams();
      if (collection.size() != 1) {
        throw new UnsupportedAudioFileException(
            "Only Ogg files with one logical Vorbis stream are supported.");
      } else {
        LogicalOggStream logicalOggStream =
            (LogicalOggStream)collection.iterator().next();
        if (logicalOggStream.getFormat() != "audio/x-vorbis") {
          throw new UnsupportedAudioFileException(
              "Only Ogg files with one logical Vorbis stream are supported.");
        } else {
          VorbisStream vorbisStream = new VorbisStream(logicalOggStream);
          AudioFormat audioFormat = new AudioFormat(
              vorbisStream.getIdentificationHeader().getSampleRate(), 16,
              vorbisStream.getIdentificationHeader().getChannels(), true, true);
          return new AudioFileFormat(
              VorbisAudioFileReader.VorbisFormatType.getInstance(), audioFormat,
              -1);
        }
      }
    } catch (OggFormatException oggFormatException) {
      throw new UnsupportedAudioFileException(oggFormatException.getMessage());
    } catch (VorbisFormatException vorbisFormatException) {
      throw new UnsupportedAudioFileException(
          vorbisFormatException.getMessage());
    }
  }

  AudioInputStream getAudioInputStream(File file) {
    try {
      return this.getAudioInputStream(
          new FileStream(new RandomAccessFile(file, "r")));
    } catch (OggFormatException oggFormatException) {
      throw new UnsupportedAudioFileException(oggFormatException.getMessage());
    }
  }

  AudioInputStream getAudioInputStream(InputStream inputStream) {
    try {
      return this.getAudioInputStream(new BasicStream(inputStream));
    } catch (OggFormatException oggFormatException) {
      throw new UnsupportedAudioFileException(oggFormatException.getMessage());
    }
  }

  AudioInputStream getAudioInputStream(URL url) {
    try {
      return this.getAudioInputStream(new UncachedUrlStream(url));
    } catch (OggFormatException oggFormatException) {
      throw new UnsupportedAudioFileException(oggFormatException.getMessage());
    }
  }

  AudioInputStream getAudioInputStream(PhysicalOggStream physicalOggStream) {
    try {
      Collection collection = physicalOggStream.getLogicalStreams();
      if (collection.size() != 1) {
        throw new UnsupportedAudioFileException(
            "Only Ogg files with one logical Vorbis stream are supported.");
      } else {
        LogicalOggStream logicalOggStream =
            (LogicalOggStream)collection.iterator().next();
        if (logicalOggStream.getFormat() != "audio/x-vorbis") {
          throw new UnsupportedAudioFileException(
              "Only Ogg files with one logical Vorbis stream are supported.");
        } else {
          VorbisStream vorbisStream = new VorbisStream(logicalOggStream);
          AudioFormat audioFormat = new AudioFormat(
              vorbisStream.getIdentificationHeader().getSampleRate(), 16,
              vorbisStream.getIdentificationHeader().getChannels(), true, true);
          return new AudioInputStream(
              new VorbisAudioFileReader.VorbisInputStream(vorbisStream),
              audioFormat, -1L);
        }
      }
    } catch (OggFormatException oggFormatException) {
      throw new UnsupportedAudioFileException(oggFormatException.getMessage());
    } catch (VorbisFormatException vorbisFormatException) {
      throw new UnsupportedAudioFileException(
          vorbisFormatException.getMessage());
    }
  }

public
  static class VorbisFormatType extends Type {
  private
    static final VorbisAudioFileReader.VorbisFormatType instance =
        new VorbisAudioFileReader.VorbisFormatType();

  private
    VorbisFormatType() { super("VORBIS", "ogg"); }

    static Type getInstance() { return instance; }
  }

  public static class VorbisInputStream extends InputStream {
    VorbisStream source;
  private
    byte[] buffer = new byte[8192];

  public
    VorbisInputStream(VorbisStream vorbisStream) { this.source = vorbisStream; }

    int read() { return 0; }

    int read(byte[] bytes) { return this.read(bytes, 0, bytes.length); }

    int read(byte[] bytes, int int0, int int1) {
      try {
        return this.source.readPcm(bytes, int0, int1);
      } catch (EndOfOggStreamException endOfOggStreamException) {
        return -1;
      }
    }
  }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
