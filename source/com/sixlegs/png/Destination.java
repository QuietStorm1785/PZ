// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package com.sixlegs.png;

import java.awt.image.WritableRaster;

abstract class Destination {
    public abstract void setPixels(int var1, int var2, int var3, int[] var4);

    public abstract void setPixel(int var1, int var2, int[] var3);

    public abstract void getPixel(int var1, int var2, int[] var3);

    public abstract WritableRaster getRaster();

    public abstract int getSourceWidth();

    public abstract void done();
}
