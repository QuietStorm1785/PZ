// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package de.jarnbjo.ogg;

import java.io.IOException;
import java.util.Collection;

public interface PhysicalOggStream {
    Collection getLogicalStreams();

    OggPage getOggPage(int var1) throws OggFormatException, IOException;

    boolean isOpen();

    void close() throws IOException;

    void setTime(long var1) throws OggFormatException, IOException;

    boolean isSeekable();
}
