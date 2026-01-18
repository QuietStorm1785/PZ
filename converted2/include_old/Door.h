#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Door.java
namespace zombie {
namespace scripting {
namespace objects {
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject
class Door : public BaseScriptObject {
public:
{
    public Door()
    {
    }
    public void Load(std::string name, std::string strArray[])
    {
        this.name = name;
        x = Integer.parseInt(strArray[0].trim());
        y = Integer.parseInt(strArray[1].trim());
        z = Integer.parseInt(strArray[2].trim());
    }
    public int x;
    public int y;
    public int z;
    public std::string name;
}
} // namespace
