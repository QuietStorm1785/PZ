#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AudioInputStream.java
namespace zombie {
namespace openal {
#include <fstream>
#include <iostream>
class AudioInputStream {
public:
    virtual ~AudioInputStream() = default;
{
    public abstract bool atEnd();
    public abstract void close()
        throws IOException;
    public abstract int getChannels();
    public abstract int getRate();
    public abstract int read()
        throws IOException;
    public abstract int read(byte abyte0[])
        throws IOException;
    public abstract int read(byte abyte0[], int i, int j)
        throws IOException;
}
} // namespace
