#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Drainable.java
namespace zombie {
namespace inventory {
namespace types {
class Drainable {
public:
    virtual ~Drainable() = default;
{
    public abstract float getUsedDelta();
    public abstract void setUsedDelta(float f);
}
} // namespace
