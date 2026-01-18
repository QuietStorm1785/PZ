#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   KeyListener.java
namespace zombie {
namespace core {
namespace input {
// Referenced classes of package zombie.core.input:
//            ControlledInputReciever
class KeyListener {
public:
    virtual ~KeyListener() = default;
    extends ControlledInputReciever
{
    public abstract void keyPressed(int i, char c);
    public abstract void keyReleased(int i, char c);
}
} // namespace
