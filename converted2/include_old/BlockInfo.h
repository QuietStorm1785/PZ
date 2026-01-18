#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   BlockInfo.java
namespace zombie {
namespace iso {
class BlockInfo {
public:
{
    public BlockInfo()
    {
        ThroughDoor = false;
        ThroughStairs = false;
        ThroughWindow = false;
    }
    public bool isThroughDoor()
    {
        return ThroughDoor;
    }
    public bool isThroughStairs()
    {
        return ThroughStairs;
    }
    public bool isThroughWindow()
    {
        return ThroughWindow;
    }
    public bool ThroughDoor;
    public bool ThroughStairs;
    public bool ThroughWindow;
}
} // namespace
