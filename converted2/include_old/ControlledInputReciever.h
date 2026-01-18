#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ControlledInputReciever.java
namespace zombie {
namespace core {
namespace input {
// Referenced classes of package zombie.core.input:
//            Input
class ControlledInputReciever {
public:
    virtual ~ControlledInputReciever() = default;
{
    public abstract void setInput(Input input);
    public abstract bool isAcceptingInput();
    public abstract void inputEnded();
    public abstract void inputStarted();
}
} // namespace
