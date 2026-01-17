#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Talker.java
namespace zombie {
namespace characters {
class Talker {
public:
    virtual ~Talker() = default;
{
    public abstract bool IsSpeaking();
    public abstract void Say(std::string s);
    public abstract std::string getTalkerType();
}
} // namespace
