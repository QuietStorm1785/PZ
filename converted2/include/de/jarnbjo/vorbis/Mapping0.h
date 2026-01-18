#pragma once
#include "de/jarnbjo/util/io/BitInputStream.h"
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

class Mapping0 : public Mapping {
public:
private
  int[] magnitudes;
private
  int[] angles;
private
  int[] mux;
private
  int[] submapFloors;
private
  int[] submapResidues;

protected
  Mapping0(VorbisStream vorbisStream, BitInputStream bitInputStream,
           SetupHeader setupHeader) {
    int int0 = 1;
    if (bitInputStream.getBit()) {
      int0 = bitInputStream.getInt(4) + 1;
    }

    int int1 = vorbisStream.getIdentificationHeader().getChannels();
    int int2 = Util.ilog(int1 - 1);
    if (bitInputStream.getBit()) {
      int int3 = bitInputStream.getInt(8) + 1;
      this.magnitudes = new int[int3];
      this.angles = new int[int3];

      for (int int4 = 0; int4 < int3; int4++) {
        this.magnitudes[int4] = bitInputStream.getInt(int2);
        this.angles[int4] = bitInputStream.getInt(int2);
        if (this.magnitudes[int4] == this.angles[int4] ||
            this.magnitudes[int4] >= int1 || this.angles[int4] >= int1) {
          System.err.println(this.magnitudes[int4]);
          System.err.println(this.angles[int4]);
          throw new VorbisFormatException(
              "The channel magnitude and/or angle mismatch.");
        }
      }
    } else {
      this.magnitudes = new int[0];
      this.angles = new int[0];
    }

    if (bitInputStream.getInt(2) != 0) {
      throw new VorbisFormatException(
          "A reserved mapping field has an invalid value.");
    } else {
      this.mux = new int[int1];
      if (int0 > 1) {
        for (int int5 = 0; int5 < int1; int5++) {
          this.mux[int5] = bitInputStream.getInt(4);
          if (this.mux[int5] > int0) {
            throw new VorbisFormatException(
                "A mapping mux value is higher than the number of submaps");
          }
        }
      } else {
        for (int int6 = 0; int6 < int1; int6++) {
          this.mux[int6] = 0;
        }
      }

      this.submapFloors = new int[int0];
      this.submapResidues = new int[int0];
      int int7 = setupHeader.getFloors().length;
      int int8 = setupHeader.getResidues().length;

      for (int int9 = 0; int9 < int0; int9++) {
        bitInputStream.getInt(8);
        this.submapFloors[int9] = bitInputStream.getInt(8);
        this.submapResidues[int9] = bitInputStream.getInt(8);
        if (this.submapFloors[int9] > int7) {
          throw new VorbisFormatException(
              "A mapping floor value is higher than the number of floors.");
        }

        if (this.submapResidues[int9] > int8) {
          throw new VorbisFormatException(
              "A mapping residue value is higher than the number of residues.");
        }
      }
    }
  }

  int getType() { return 0; }

protected
  int[] getAngles() { return this.angles; }

protected
  int[] getMagnitudes() { return this.magnitudes; }

protected
  int[] getMux() { return this.mux; }

protected
  int[] getSubmapFloors() { return this.submapFloors; }

protected
  int[] getSubmapResidues() { return this.submapResidues; }

  int getCouplingSteps() { return this.angles.length; }

  int getSubmaps() { return this.submapFloors.length; }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
