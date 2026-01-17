#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   InputListener.java
namespace zombie {
namespace core {
namespace input {
// Referenced classes of package zombie.core.input:
//            MouseListener, KeyListener, ControllerListener
class InputListener {
public:
    virtual ~InputListener() = default;
    extends MouseListener, KeyListener, ControllerListener
{
}
} // namespace
