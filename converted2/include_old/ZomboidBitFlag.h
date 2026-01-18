#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:45
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   ZomboidBitFlag.java
namespace zombie {
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "IsoFlagType.h"
#include "IsoObjectType.h"
class ZomboidBitFlag {
public:
{
    public ZomboidBitFlag(int size)
    {
        this.size = 64;
    }
    public long toInt()
    {
        if(flags == nullptr)
            return 0L;
        long f = 0L;
        for(int n = 0; n < flags.length; n++)
        {
            bool b = flags[n];
            if(b)
                f |= 1L << n;
        }
        return f;
    }
    public void set(int off, bool b)
    {
        if(off >= 64)
            return;
        long flags = toInt();
        if(b)
            flags |= 1L << off;
        else
            flags &= ~(1L << off);
        if(BitFlags.containsKey(Long.valueOf(flags)))
        {
            this.flags = (bool[])BitFlags.get(Long.valueOf(flags));
            return;
        } else
        {
            this.flags = toArray(flags);
            bool isSet = this.flags[5];
            BitFlags.put(Long.valueOf(flags), this.flags);
            return;
        }
    }
    public void clear()
    {
        flags = nullptr;
    }
    public bool isSet(int off)
    {
        if(off >= 64)
            return false;
        if(flags == nullptr)
            return false;
        else
            return flags[off];
    }
    public bool isSet(IsoFlagType flag)
    {
        return isSet(flag.index());
    }
    public void set(IsoFlagType flag, bool b)
    {
        set(flag.index(), b);
    }
    public bool isSet(IsoObjectType flag)
    {
        return isSet(flag.index());
    }
    public void set(IsoObjectType flag, bool b)
    {
        set(flag.index(), b);
    }
    public void Or(ZomboidBitFlag SpriteFlags)
    {
        long result = SpriteFlags.toInt() | toInt();
        getFromLong(result);
    }
    public void save(DataOutputStream output)
        throws IOException
    {
        output.writeLong(toInt());
    }
    public void load(DataInputStream input)
        throws IOException
    {
        getFromLong(input.readLong());
    }
    public void getFromLong(long l)
    {
        long flags = l;
        if(BitFlags.containsKey(Long.valueOf(flags)))
        {
            this.flags = (bool[])BitFlags.get(Long.valueOf(flags));
            return;
        } else
        {
            this.flags = toArray(flags);
            BitFlags.put(Long.valueOf(flags), this.flags);
            return;
        }
    }
    private static bool[] toArray(long f)
    {
        bool flags[] = new bool[64];
        for(int n = 0; n < 64; n++)
        {
            long d = 1L << (int)(long)n;
            if((d & f) == d)
                flags[n] = true;
        }
        return flags;
    }
    public static HashMap BitFlags;
    protected bool flags[];
    public int size;
    static 
    {
        BitFlags = new HashMap();
        BitFlags.put(new Long(0L), new bool[64]);
    }
}} // namespace
