#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   OggDecoder.java
namespace zombie {
namespace openal {
#include <fstream>
#include <iostream>
#include "ByteBuffer.h"
// Referenced classes of package zombie.openal:
//            OggInputStream, OggData
class OggDecoder {
public:
{
    public OggDecoder()
    {
        convsize = 16384;
        convbuffer = new byte[convsize];
    }
    public OggData getData(InputStream input)
        throws IOException
    {
        if(input == nullptr)
            throw new IOException("Failed to read OGG, source does not exist?");
        ByteArrayOutputStream dataout = new ByteArrayOutputStream();
        OggInputStream oggInput = new OggInputStream(input);
        bool done = false;
        for(; !oggInput.atEnd(); dataout.write(oggInput.read()));
        OggData ogg = new OggData();
        ogg.channels = oggInput.getChannels();
        ogg.rate = oggInput.getRate();
        byte data[] = dataout.toByteArray();
        ogg.data = ByteBuffer.allocateDirect(data.length);
        ogg.data.put(data);
        ogg.data.rewind();
        return ogg;
    }
    private int convsize;
    private byte convbuffer[];
}
} // namespace
