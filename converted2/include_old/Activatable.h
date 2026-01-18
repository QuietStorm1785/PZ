#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Activatable.java
namespace zombie {
namespace iso {
namespace objects {
namespace interfaces {
class Activatable {
public:
    virtual ~Activatable() = default;
{
    public abstract bool Activated();
    public abstract void Toggle();
    public abstract std::string getActivatableType();
}
} // namespace
