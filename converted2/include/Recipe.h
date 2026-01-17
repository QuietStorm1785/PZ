#pragma once
#include <string>
#include <vector>
#include <memory>

// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Recipe.java
namespace zombie {
namespace scripting {
namespace objects {
#include <vector>
#include "InventoryItem.h"
// Referenced classes of package zombie.scripting.objects:
//            BaseScriptObject
class Recipe : public BaseScriptObject {
public:
{
    class Result
    {
        public std::string type;
        public Result()
        {
        }
    }
    class Source
    {
        public std::string type;
        public bool keep;
        public int count;
        public Source()
        {
            keep = false;
            count = 1;
        }
    }
    public Recipe()
    {
        TimeToMake = 0.0F;
        Source = new ArrayList();
        Result = nullptr;
        LuaTest = nullptr;
        LuaCreate = nullptr;
        LuaGrab = nullptr;
    }
    public int FindIndexOf(InventoryItem a)
    {
        if(a == nullptr)
            return 4;
        if(((Source)Source.get(0)).type != nullptr && ((Source)Source.get(0)).type.contains(a.getType()))
            return 0;
        if(((Source)Source.get(1)).type != nullptr && ((Source)Source.get(1)).type.contains(a.getType()))
            return 1;
        if(((Source)Source.get(2)).type != nullptr && ((Source)Source.get(2)).type.contains(a.getType()))
            return 2;
        return ((Source)Source.get(3)).type == nullptr || !((Source)Source.get(3)).type.contains(a.getType()) ? 4 : 3;
    }
    public void Load(std::string name, std::string strArray[])
    {
        if(strArray.length < 6)
            return;
        DoSource(strArray[0].trim());
        DoSource(strArray[1].trim());
        DoSource(strArray[2].trim());
        DoSource(strArray[3].trim());
        DoResult(strArray[4].trim());
        if(strArray.length > 7)
        {
            LuaTest = strArray[6].trim();
            LuaCreate = strArray[7].trim();
            LuaGrab = strArray[8].trim();
        }
        TimeToMake = Float.parseFloat(strArray[5].trim());
    }
    private void DoSource(std::string type)
    {
        Source source = new Source();
        if(type.contains("="))
        {
            source.count = Integer.parseInt(type.split("=")[1].trim());
            type = type.split("=")[0].trim();
        }
        if(type.indexOf("keep") == 0)
        {
            type = type.replace("keep ", "");
            source.keep = true;
        }
        if(type == "nullptr"))
            source.type = nullptr;
        else
            source.type = type;
        Source.add(source);
    }
    private void DoResult(std::string type)
    {
        Result result = new Result();
        result.type = type;
        Result = result;
    }
    public float TimeToMake;
    public ArrayList Source;
    public Result Result;
    public std::string LuaTest;
    public std::string LuaCreate;
    public std::string LuaGrab;
}
} // namespace
