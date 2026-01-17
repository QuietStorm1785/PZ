#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   DeferredResource.java
namespace zombie {
namespace loading {
#include <fstream>
#include <iostream>
class DeferredResource {
public:
    virtual ~DeferredResource() = default;
{
    public abstract std::string getDescription();
    public abstract void load()
        throws IOException;
}
} // namespace
