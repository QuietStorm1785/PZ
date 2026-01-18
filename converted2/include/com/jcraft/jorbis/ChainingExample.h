#pragma once
#include "zombie/debug/DebugLog.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace jcraft {
namespace jorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ChainingExample {
public:
  static void main(String[] strings) {
    VorbisFile vorbisFile = null;

    try {
      if (strings.length > 0) {
        vorbisFile = new VorbisFile(strings[0]);
      } else {
        vorbisFile = new VorbisFile(System.in, nullptr, -1);
      }
    } catch (Exception exception) {
      System.err.println(exception);
      return;
    }

    if (vorbisFile.seekable()) {
      DebugLog.log("Input bitstream contained " + vorbisFile.streams() +
                   " logical bitstream section(s).");
      DebugLog.log("Total bitstream playing time: " +
                   vorbisFile.time_total(-1) + " seconds\n");
    } else {
      DebugLog.log("Standard input was not seekable.");
      DebugLog.log("First logical bitstream information:\n");
    }

    for (int int0 = 0; int0 < vorbisFile.streams(); int0++) {
      Info info = vorbisFile.getInfo(int0);
      DebugLog.log("\tlogical bitstream section " + (int0 + 1) +
                   " information:");
      DebugLog.log("\t\t" + info.rate + "Hz " + info.channels +
                   " channels bitrate " + vorbisFile.bitrate(int0) / 1000 +
                   "kbps serial number=" + vorbisFile.serialnumber(int0));
      System.out.print("\t\tcompressed length: " + vorbisFile.raw_total(int0) +
                       " bytes ");
      DebugLog.log(" play time: " + vorbisFile.time_total(int0) + "s");
      Comment comment = vorbisFile.getComment(int0);
      DebugLog.log(comment);
    }
  }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
