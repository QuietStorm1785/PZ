#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AlphaColorIndex.java
namespace zombie {
namespace core {
namespace textures {
#include <fstream>
#include <iostream>
class AlphaColorIndex {
public:
    implements Serializable
{
    AlphaColorIndex(int red, int green, int blue, int alpha)
    {
        this.red = (byte)red;
        this.green = (byte)green;
        this.blue = (byte)blue;
        this.alpha = (byte)alpha;
    }
    byte alpha;
    byte blue;
    byte green;
    byte red;
}
} // namespace
