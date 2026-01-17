#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Thumpable.java
namespace zombie {
namespace iso {
namespace objects {
namespace interfaces {
#include "IsoMovingObject.h"
class Thumpable {
public:
    virtual ~Thumpable() = default;
{
    public abstract bool isDestroyed();
    public abstract void Thump(IsoMovingObject isomovingobject);
}
} // namespace
