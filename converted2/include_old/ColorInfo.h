#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ColorInfo.java
namespace zombie {
namespace core {
namespace textures {
class ColorInfo {
public:
{
    public ColorInfo()
    {
        a = 1.0F;
        b = 1.0F;
        g = 1.0F;
        r = 1.0F;
        r = 1.0F;
        g = 1.0F;
        b = 1.0F;
        a = 1.0F;
    }
    public ColorInfo(float R, float G, float B, float A)
    {
        a = 1.0F;
        b = 1.0F;
        g = 1.0F;
        r = 1.0F;
        r = R;
        g = G;
        b = B;
        a = A;
    }
    public float a;
    public float b;
    public float g;
    public float r;
}
} // namespace
