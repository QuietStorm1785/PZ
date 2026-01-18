#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   LuaUIWindow.java
namespace zombie {
namespace ui {
#include "LuaCaller.h"
#include "KahluaTable.h"
#include "LuaManager.h"
// Referenced classes of package zombie.ui:
//            NewWindow
class LuaUIWindow : public NewWindow {
public:
{
    public LuaUIWindow(int x, int y, int wid, int hei, bool hasClose, KahluaTable table)
    {
        super(x, y, wid, hei, hasClose);
        ResizeToFitY = false;
        this.table = table;
    }
    public void ButtonClicked(std::string name)
    {
        super.ButtonClicked(name);
        Object o[];
        if(getTable().rawget("onButtonClicked") != nullptr)
            o = LuaManager.caller.pcall(LuaManager.thread, getTable().rawget("onButtonClicked"), new Object[] {
                table, name
            });
    }
}
} // namespace
