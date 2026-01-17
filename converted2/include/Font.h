#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Font.java
namespace zombie {
namespace core {
namespace fonts {
#include "Color.h"
class Font {
public:
    virtual ~Font() = default;
{
    public abstract void drawString(float f, float f1, std::string s);
    public abstract void drawString(float f, float f1, std::string s, Color color);
    public abstract void drawString(float f, float f1, std::string s, Color color, int i, int j);
    public abstract int getHeight(std::string s);
    public abstract int getWidth(std::string s);
    public abstract int getLineHeight();
}
} // namespace
