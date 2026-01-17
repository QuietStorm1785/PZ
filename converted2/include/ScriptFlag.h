#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ScriptFlag.java
namespace zombie {
namespace scripting {
namespace objects {
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject
class ScriptFlag : public BaseScriptObject {
public:
{
    public ScriptFlag()
    {
    }
    public void Load(std::string name, std::string strArray[])
    {
        this.name = name;
        value = strArray[0].trim();
    }
    public void SetValue(std::string newVal)
    {
        value = newVal;
    }
    public bool IsValue(std::string test)
    {
        return value == test);
    }
    public std::string name;
    public std::string value;
}
} // namespace
