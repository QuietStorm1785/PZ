#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IUpdater.java
namespace zombie {
namespace interfaces {
class IUpdater {
public:
    virtual ~IUpdater() = default;
{
    public abstract void render();
    public abstract void renderlast();
    public abstract void update();
}
} // namespace
