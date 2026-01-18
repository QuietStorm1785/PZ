#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   IListBoxItem.java
namespace zombie {
namespace interfaces {
class IListBoxItem {
public:
    virtual ~IListBoxItem() = default;
{
    public abstract std::string getLabel();
    public abstract std::string getLeftLabel();
    public abstract std::string getRightLabel();
}
} // namespace
