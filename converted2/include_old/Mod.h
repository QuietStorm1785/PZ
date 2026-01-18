#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Mod.java
namespace zombie {
namespace modding {
#include "IListBoxItem.h"
class Mod {
public:
    implements IListBoxItem
{
    public Mod()
    {
    }
    public void Mod()
    {
    }
    public std::string getLabel()
    {
        return name;
    }
    public std::string getLeftLabel()
    {
        return nullptr;
    }
    public std::string getRightLabel()
    {
        return nullptr;
    }
    public std::string name;
    public std::string temp;
}
} // namespace
