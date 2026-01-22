#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/util/io/BitInputStream.h"
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace vorbis {


class SetupHeader {
public:
    static const long HEADER = 126896460427126L;
   private CodeBook[] codeBooks;
   private Floor[] floors;
   private Residue[] residues;
   private Mapping[] mappings;
   private Mode[] modes;

    public SetupHeader(VorbisStream var1, BitInputStream var2) {
      if (var2.getLong(48) != 126896460427126L) {
         throw VorbisFormatException("The setup header has an illegal leading.");
      } else {
    int var3 = var2.getInt(8) + 1;
         this.codeBooks = new CodeBook[var3];

         for (int var4 = 0; var4 < this.codeBooks.length; var4++) {
            this.codeBooks[var4] = std::make_shared<CodeBook>(var2);
         }

    int var10 = var2.getInt(6) + 1;

         for (int var5 = 0; var5 < var10; var5++) {
            if (var2.getInt(16) != 0) {
               throw VorbisFormatException("Time domain transformation != 0");
            }
         }

    int var11 = var2.getInt(6) + 1;
         this.floors = new Floor[var11];

         for (int var6 = 0; var6 < var11; var6++) {
            this.floors[var6] = Floor.createInstance(var2, this);
         }

    int var12 = var2.getInt(6) + 1;
         this.residues = new Residue[var12];

         for (int var7 = 0; var7 < var12; var7++) {
            this.residues[var7] = Residue.createInstance(var2, this);
         }

    int var13 = var2.getInt(6) + 1;
         this.mappings = new Mapping[var13];

         for (int var8 = 0; var8 < var13; var8++) {
            this.mappings[var8] = Mapping.createInstance(var1, var2, this);
         }

    int var14 = var2.getInt(6) + 1;
         this.modes = new Mode[var14];

         for (int var9 = 0; var9 < var14; var9++) {
            this.modes[var9] = std::make_shared<Mode>(var2, this);
         }

         if (!var2.getBit()) {
            throw VorbisFormatException("The setup header framing bit is incorrect.");
         }
      }
   }

   public CodeBook[] getCodeBooks() {
      return this.codeBooks;
   }

   public Floor[] getFloors() {
      return this.floors;
   }

   public Residue[] getResidues() {
      return this.residues;
   }

   public Mapping[] getMappings() {
      return this.mappings;
   }

   public Mode[] getModes() {
      return this.modes;
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
