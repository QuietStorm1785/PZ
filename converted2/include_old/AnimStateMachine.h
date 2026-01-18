#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   AnimStateMachine.java
namespace zombie {
namespace iso {
namespace sprite {
#include <unordered_map>
class AnimStateMachine {
public:
{
    public AnimStateMachine()
    {
        StateMap = new HashMap();
    }
    public HashMap StateMap;
}
} // namespace
