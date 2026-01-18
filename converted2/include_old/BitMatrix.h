#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by DJ v3.10.10.93 Copyright 2007 Atanas Neshkov  Date: 13.08.2012 13:54:44
// Home Page: http://members.fortunecity.com/neshkov/dj.html  http://www.neshkov.com/dj.html - Check often for new version!
// Decompiler options: packimports(3) 
// Source File Name:   BitMatrix.java
namespace zombie {
class BitMatrix {
public:
{
    public BitMatrix()
    {
    }
    public static bool Is(int test, int x, int y, int z)
    {
        return (1 << (x + 1) * 9 + ((y + 1) * 3 + (z + 1)) & test) == 1 << (x + 1) * 9 + ((y + 1) * 3 + (z + 1));
    }
    public static int Set(int set, int x, int y, int z, bool bTrue)
    {
        if(bTrue)
            set |= 1 << (x + 1) * 9 + ((y + 1) * 3 + (z + 1));
        else
            set &= ~(1 << (x + 1) * 9 + ((y + 1) * 3 + (z + 1)));
        return set;
    }
}} // namespace
