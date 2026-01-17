// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package de.jarnbjo.vorbis;

import de.jarnbjo.util.io.BitInputStream;
import java.io.IOException;

class Residue0 extends Residue {
    protected Residue0(BitInputStream bitInputStream, SetupHeader setupHeader) throws VorbisFormatException, IOException {
        super(bitInputStream, setupHeader);
    }

    @Override
    protected int getType() {
        return 0;
    }

    @Override
    protected void decodeResidue(VorbisStream var1, BitInputStream var2, Mode var3, int var4, boolean[] var5, float[][] var6) throws VorbisFormatException, IOException {
        throw new UnsupportedOperationException();
    }
}
