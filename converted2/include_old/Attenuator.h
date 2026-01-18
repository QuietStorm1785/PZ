#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Attenuator.java
namespace zombie {
namespace core {
namespace sound {
class Attenuator {
public:
    virtual ~Attenuator() = default;
{
    public abstract float getAttenuation(float f, float f1);
    public abstract float getXPosition(float f, float f1, float f2);
    public abstract float getYPosition(float f, float f1, float f2);
    public abstract float getZPosition(float f, float f1, float f2);
}
} // namespace
