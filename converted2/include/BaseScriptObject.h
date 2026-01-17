#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   BaseScriptObject.java
namespace zombie {
namespace scripting {
namespace objects {
// Referenced classes of package zombie.scripting.objects:
//            ScriptModule
class BaseScriptObject {
public:
{
    public BaseScriptObject()
    {
        module = nullptr;
    }
    public void Load(std::string s, std::string as[])
    {
    }
    public ScriptModule module;
}
} // namespace
