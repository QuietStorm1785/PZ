#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Need.java
namespace zombie {
namespace behaviors {
namespace survivor {
namespace orders {
namespace Needs {
class Need {
public:
{
    public Need(std::string item, int priority)
    {
        numToSatisfy = 1;
        this.item = item;
        this.priority = priority;
    }
    public int priority;
    public std::string item;
    public int numToSatisfy;
}
} // namespace
