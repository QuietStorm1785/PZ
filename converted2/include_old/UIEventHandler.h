#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   UIEventHandler.java
namespace zombie {
namespace ui {
class UIEventHandler {
public:
    virtual ~UIEventHandler() = default;
{
    public abstract void DoubleClick(std::string s, int i, int j);
    public abstract void ModalClick(std::string s, std::string s1);
    public abstract void Selected(std::string s, int i, int j);
}
} // namespace
